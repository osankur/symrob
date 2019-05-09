#ifndef __TCHECKER_ALGORITHMS_EXPLORE_HH__
#define __TCHECKER_ALGORITHMS_EXPLORE_HH__

#include <stack>
#include <utility>

#include "algorithms/algorithms.hh"
#include "algorithms/algorithms-options.hh"
#include "algorithms/runnable.hh"
#include "base/stats.hh"
#include "graph/graph.hh"
#include "graph/reachset.hh"
#include "graph/stats.hh"
#include "graph/ts.hh"

/*!
  \file explore.hh
  \brief State-space exploration algorithms
*/

namespace algorithms {

  /*!
    \namespace explore
    \brief State-space exploration algorithms
  */

  namespace explore {

    /*!
      \class node_t
      \brief Node for state-space exploration algorithms
      \tparam STATE : type of underlying state
    */
    template <class STATE>
    class node_t : public graph::state_node_t<STATE> {
    public:
    };


    
    /*!
      \class stats_t
      \brief Provides counters for statistics
     */
    class stats_t {
    public:
      /*!
        \brief Constructor
        \post All counters have been initialized to 0
       */
      stats_t();

      /*!
        \brief Initializes all counters
        \post All counters have been initialized to 0
       */
      void initialize();

      /*!
        \brief Outputs the stats
        \param os : output stream
        \param level : stats level
        \post Stats of level at most 'level' have been output to os
       */
      void output(std::ostream & os, unsigned level) const;

      unsigned nodes_count;         /*!< Total number of nodes */
      unsigned visited_nodes_count; /*!< Number of visited nodes */
    };



    /*!
      \class explore_t
      \brief State-space exploration algorithm
      \tparam STATE : type of states
      \tparam EDGE_RANGE : type of ranges of edges
    */
    template <class STATE,
              class EDGE_RANGE>
    class explore_t
        : public algorithms::runnable_t,
        public algorithms::graph_output_owner_t {
    protected:
      /*!< Fully instantiated type of nodes */
      typedef algorithms::explore::node_t<STATE> node_t;
      
      /*!< State-space of _graph */
      graph::reachset_t< node_t,
      EDGE_RANGE,
      graph::ts_t<STATE, EDGE_RANGE> >
      _reachset;
      
      /*!< Algorithm's options */
      algorithms::options_t const & _algorithm_options;
      
      /*!< Stats */
      stats_t _stats;
      
      /*!
        \brief Exploration algorithm
      */
      void explore() {
        std::stack< sp_t<node_t> > todo;
        sp_t<node_t> current, next;

        // Initialization
        _stats.initialize();

        this->_go->start();
        this->_go->title("Reachability graph");

        // Start from initial node
        current = _reachset.initial();

        if (current->status() == graph::STATE_STATUS_OK) {
            ++ _stats.nodes_count;
            current->id = _stats.nodes_count;
            todo.push(current);
          }

        while (! todo.empty()) {
            // Visit top node
            current = todo.top();
            todo.pop();

            ++ _stats.visited_nodes_count;
            current->snumber = _stats.visited_nodes_count;
            this->_go->node(*current);

            // Gets next nodes and visit them
            for (auto r = _reachset.outgoing_edges(current); ! r.at_end();
                 r.advance()) {
                typename EDGE_RANGE::reference edge = r.current();
                next = _reachset.next(current, edge);

                if (next->status() != graph::STATE_STATUS_OK) // skip invalid states
                  continue;

                if (next->id == 0) { // next has not been visited yet
                    ++ _stats.nodes_count;
                    next->id = _stats.nodes_count;
                    todo.push(next);
                  }

                this->_go->edge(*current, *next);
              }
          }

        // Output stats, etc.
        stats(_algorithm_options.stats_level);
        dump();

        this->_go->end();
      }
      
      
      /*!
        \brief Outputs stats
        \param level : stats level
        \post Stats on number of visited nodes and automaton states
        have been output to std::cout
       */
      virtual void stats(unsigned level) {
        // Visited nodes, etc
        _stats.output(std::cout, level);

        // Automaton states stats
        graph::stats_states(std::cout, level, _reachset.begin(),
                            _reachset.end(),
                            [] (sp_t<node_t> const & node) {
          return node.get();
        } );
      }


      /*!
        \brief Displays the state-space
      */
      void dump() {
        if (_algorithm_options.go_flags == graph::OUTPUT_NO)
          return;

        this->_go->layer(graph::L_NEW); // Change to new layer
        this->_go->title("Reachable state-space");

        for (sp_t<node_t> const & n : _reachset)
          this->_go->node(*n);

        this->_go->layer(graph::L_BACKGROUND);
      }
    public:
      /*!
        \brief Constructor
        \param ts : transition system to explore
        \param options : algorithm settings
        \throw std::runtime_error : if the check flag is set in options
      */
      explore_t(graph::ts_t<STATE, EDGE_RANGE> & ts,
                algorithms::options_t const & options)
        : algorithms::graph_output_owner_t(* options.os, options.go_flags),
          _reachset(ts),
          _algorithm_options(options)
      {
        // This algorithm cannot check correctness of the outcome
        if (options.check_flag)
          throw std::runtime_error
            ("*** algorithms::explore::algorithm_t: cannot check outcome");
      }

      /*!
        \brief Destructor
       */
      virtual ~explore_t() = default;

      /*!
        \brief Runs the algorithm
        \return True (meaningless)
      */
      bool run() {
        explore();
        return true;
      }
    };




    /*!
      \class factory_t
      \brief Factory for exploration algorithms
     */
    class factory_t : public singleton_t< factory_t > {
      
      friend class singleton_t< factory_t >; // Grants access to cons/des

    public:
      /*!
        \brief Builds a new graph exploration algorithm
        \param system_builder : model builder to build the transition system
        \param options : algorithm settings
        \return A pointer to a graph exploration algorithm corresponding to
        the type of graph in options
        \post Memory allocated for the algorithm should be released by the
        caller
        \throw std::logic_error : if the type of transition system is not
        supported
       */
      algorithms::runnable_t *
      new_algorithm(syntax::system_builder_t & system_builder,
                    algorithms::options_t const & options);
    private:
      /*!
        \brief Constructor (made private)
       */
      factory_t();

      /*!
        \brief Destructor (made private)
       */
      ~factory_t();
    };


  } // end of namespace explore

} // end of namespace algorithms

#endif // __TCHECKER_ALGORITHMS_EXPLORE_HH__
