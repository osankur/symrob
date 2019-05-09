#ifndef __TCHECKER_GRAPH_HH__
#define __TCHECKER_GRAPH_HH__

#include <ostream>

/*!
  \namespace graph
  \brief Graphs explored by algorithms
 */
namespace graph {

  /*!
    \class node_t
    \brief Node in a graph
   */
  class node_t {
  public:
    /*!
      \brief Constructor
      \post The node has been initialized with identifier 0 and search number
      0
    */
    node_t();

    /*!
      \brief Destructor
    */
    virtual ~node_t();

    /*!
      \brief Output of node
      \param os : output stream
      \post The search number has been output
    */
    virtual void output(std::ostream & os) const;


    unsigned id;       /*!< Node identifier */
    /* IMPLEMENTATION NOTE: algorithms are expected to define unique node
       identifiers. Notice that addresses in memory are usually not convenient
       since a node can be deleted and its address re-used by another node
    */
    unsigned snumber;  /*!< Search number (index in search order) */
  };



  /*!
    \class state_node_t
    \brief Node in a graph that stores a state from underlying transition
    system
    \tparam STATE : state from the underlying transition system
   */
  template <class STATE>
  class state_node_t : public node_t, public STATE {
  public:
    /*!
      \brief Type of underlying state
    */
    typedef STATE state_t;
    
    /*!
      \brief Constructor
      \post The node has been initialized
    */
    state_node_t() = default;

    /*!
      \brief Output the node
      \param os : output stream
      \post Search number and underlying state have been output to os
    */
    void output(std::ostream & os) const {
      this->node_t::output(os);
      this->STATE::output(os);
    }
  };


  /*!
    \brief Hash function compatible with boost library
    \tparam STATE : type of state in node
    \param n : node to hash
    \return The hash code of underlying state in node n
  */
  template <class STATE>
  size_t hash_value(state_node_t<STATE> const & n) {
    return n.STATE::hash();
  }

} // end of namespace graph

#endif // __TCHECKER_GRAPH_HH__
