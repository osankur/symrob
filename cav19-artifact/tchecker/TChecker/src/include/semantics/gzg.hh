#ifndef __TCHECKER_GZG_H__
#define __TCHECKER_GZG_H__

#include <ostream>
#include <utility>

#include "base/clockset.hh"
#include "base/singleton.hh"
#include "semantics/zg.hh"
#include "symbolic/constraints.hh"
#include "syntax/system.hh"

/*!
  \brief gzg.hh
  \brief Guessing zone graphs
 */

namespace semantics {

  /*!
    \namespace gzg
    \brief Guessing zone graphs
  */
  namespace gzg {

    // State
    
    /*!
      \class state_t
      \brief State of a guessing zone graph. It is made of a state of a zone
      graph (semantics::zg::state_t) and a guess set
    */
    class state_t : public semantics::zg::state_t {
    public:
      /*!
        \brief Constructor
      */
      state_t();

      /*!
        \brief Constructor
        \param ta_state : state of a timed automaton
        \param zone : pointer to a zone
        \param guess : guess set
        \post this has been initialized to represent (ta_state, zone,
        guess). It stores a pointer to zone.
      */
      state_t(syntax::state_t const & ta_state,
              symbolic::zone_t * zone,
              clock_bitset_t const & guess);

      /*!
        \brief Copy constructor
        \param s : state to copy
        \post this has been initialized to a copy of s
      */
      state_t(state_t const & s);

      /*!
        \brief Destructor
       */
      ~state_t() = default;

      /*!
        \brief Assignment operator
        \param s : state to assign from
        \post this has been assigned s
       */
      state_t & operator = (state_t const & s);

      /*!
        \brief Accessor
        \return The guess set in the state
      */
      clock_bitset_t const & guess() const;

      /*!
        \brief Equality predicate
        \return True if this and s are equal (i.e. same
        zg_t::state and same guess set), false otherwise
      */
      bool operator == (const state_t & s) const;

      /*!
        \brief Hash function
        \return Hash code built from underlying zg_t::state_t and guess set
      */
      size_t hash() const;

      /*!
        \brief Clear-state predicate
        \return True if this has an empty guess set, false otherwise
      */
      bool clear() const;

      /*!
        \brief Output function
        \param os : output stream
        \post this has been output to os
      */
      void output(std::ostream & os) const;


      clock_bitset_t _guess; /*!< Guess set */
    };


    
    // Range of edges

    /*!
      \brief Predicate checking tau transitions
      \param vedge : tuple of edges to check
      \return True if vedge is a tau transition, false otherwise
     */
    bool tau(syntax::vedge_t const & vedge);


    /*!
      \class tau_range_t
      \brief Range over a single tau edge
    */
    class tau_range_t : public range_t<syntax::vedge_t const &> {
    public:
      /*!
        \brief Constructor
        \post this points to tau edge
      */
      tau_range_t();

      /*!
        \brief Constructor
        \param skip_tau : whether the tau edge should be skipped
        \post this points to tau edge if !skip_tau, after the tau edge
        otherwise
      */
      tau_range_t(bool skip_tau);

      /*!
        \brief Copy constructor
        \param r : range to copy
        \post this is a copy of r
      */
      tau_range_t(tau_range_t const & r);

      /*!
        \brief Destructor
      */
      virtual ~tau_range_t();

      /*!
        \brief see range_t::first
        \post this points to tau edge
      */
      virtual void first();

      /*!
        \brief see range_t::current
        \pre not at_end()
        \return tau edge (i.e. tau() returns true on current value)
      */
      virtual syntax::vedge_t const & current();

      /*!
        \brief see range_t::advance
        \pre not at_end()
        \post this points after the tau edge
      */
      virtual void advance();

      /*!
        \brief see range_t::at_end
        \return true if this points after the tau edge, false otherwise
      */
      virtual bool at_end();
    private:
      bool _skip_tau;                     /*!< Skip tau edge (empty range)? */
      bool _at_end;                       /*!< Range at end? */
      static syntax::vedge_t _tau_vedge;  /*!< tau edge */
    };


    /*!
      \brief Type of guessing zone graph edge range
     */
    typedef chain_range_t< tau_range_t,
    syntax::ta_edge_range_t > edge_range_t;




    // Guessing zone graph

    /*!
      \class data_t
      \brief Data used by guessing zone graph operational semantics
     */
    class data_t {
    public:
      /*!
        \brief Constructor
        \param relevant_clocks : set of clocks that are checked for zero
        \param guess : guess set in state
        \post this stores a const reference on relevant_clocks and a reference
        on guess
       */
      data_t(clock_bitset_t const & relevant_clocks, clock_bitset_t & guess);

      /*!< Relevant clocks (i.e. checked for 0 in the model */
      clock_bitset_t const & relevant_clocks;
      /*!< Guess set */
      clock_bitset_t & guess;
    };



    /*!
      \class operations_dbm_t
      \brief Basic operations needed to compute operational semantics as a
      guessing zone graph
      
      The guessing zone graph is used to determine in which state time can
      elapse. States are equipped with a set of clocks (called the guess set). A
      transition is enabled if no clock out of the guess state is checked for 0.
      This is ensured by the redefined on_guard event. All the other events
      are the same as in semantics::operations_dbm_t.
    */
    class operations_dbm_t : public semantics::operations_dbm_t<data_t &> {
    public:
      /*!
        \brief Constructor
        \param model : model (i.e. timed automaton) for which operations are
        built
      */
      operations_dbm_t(syntax::model_t & model);

      /*!
        \brief Destructor
      */
      ~operations_dbm_t();

      /*!
        \brief see semantics::operations_dbm_t::on_guard
        \param data : extra data (relevant clocks and guess set)
        \return True if it applying the guard and x>0 for all relevant clocks
        not in guess yields a non-empty zone, false otherwise
        \pre d.guess is current guess set and g.relevant_clocks is the set
        of relevant clocks
      */
      bool on_guard(syntax::vedge_t const & vedge, raw_t * z, cindex_t dim,
                    data_t & d);
    protected:
      raw_t * _dbm;   /*!< Used to check consistency of the guess sets */
    };


    
    
    
    /*!
      \class operational_dbm_t
      \brief Operational semantics that implements the guessing zone graph
      semantics on DBMs
      \tparam OPERATIONAL_DBM : an operational semantics on DBMs. It is
      expected to derive from semantics::operational_dbm_t and to use extra
      data of type data_t (see above)
    */
    template <class OPERATIONAL_DBM>
    class operational_dbm_t : public OPERATIONAL_DBM {
    public:
      /*!
        \brief Constructor
        \param model : model (i.e. timed automaton) for which operational
        semantics is built
      */
      operational_dbm_t(syntax::model_t & model) : OPERATIONAL_DBM(model) {
      }

      /*!
        \brief Destructor
      */
      virtual ~operational_dbm_t()  = default;

      /*!
        \brief Initial zone computation (see semantics::operational_dbm_t)
        \return True if it yields a non-empty zone, false otherwise
        \pre d.relevant_clocks is the set of relevant clocks in the model
        \post z is the initial zone of _model in state s according to
        OPERATIONAL_DBM. d.guess has been set to the relevant clocks that can
        be equal to 0 (for some valuation) in z. z and d are meaningless if
        the operation yields an empty zone.
      */
      virtual bool initial(syntax::state_t const & s, raw_t * z, cindex_t dim,
                           data_t & d) {
        if ( ! this->OPERATIONAL_DBM::initial(s, z, dim, d) )
          return false;

        compute_clocks_zero(z, dim, d);

        return true;
      }

      /*!
        \brief Next zone computation (see semantics::operational_dbm_t)
        \return True if it yields an non-empty zone, false otherwise
        \pre d.guess is the guess set is state src and d.relevant_clocks is
        the set of relevant clocks in the model
        \post z has been applied transition vedge and time elapse (if enabled),
        according to OPERATIONAL_DBM. d.guess has been set to the set of
        relevant clocks that can be equal to 0 (for some valuation) in z.
        z and d are meaningless if the operation yields an empty zone.
      */
      virtual bool next(syntax::state_t const & src, raw_t * z, cindex_t dim,
                        syntax::vedge_t const & vedge,
                        syntax::state_t const & tgt,
                        data_t & d) {
        if ( ! this->OPERATIONAL_DBM::next(src, z, dim, vedge, tgt, d) )
          return false;

        compute_clocks_zero(z, dim, d);

        return true;
      }
    protected:
      /*!
        \brief Computes the set of relevant clocks that can be equal to 0 (for
        some valuation) in z
        \param z : zone (DBM)
        \param dim : dimension of z
        \param d : extra data (relevant clocks and guess set), see data_t above
        \pre z is an allocated raw_t[dim * dim]
        \post d.guess has been set to the set of relevant clocks that can be
        equal to 0 (for some valuation) in z
      */
      void compute_clocks_zero(raw_t const * z, cindex_t dim, data_t & d){
        d.guess.clear();
        for (clock_id_t cid : d.relevant_clocks)
          if (z[cid] == dbm_LE_ZERO)  // 0-cid <= 0 (i.e. cid >= 0)
            d.guess.add(cid);
      }
    };





    /*!
      \class gzg_t
      \brief Guessing zone graph
      \tparam OPERATIONAL_ZONE : operational semantics on zones with extra
      data of type data_t (see semantics::operational_zone_t)
    */
    template <class OPERATIONAL_ZONE>
    class gzg_t : public semantics::semantics_t<state_t, edge_range_t> {
    public:
      /*!
        \brief Constructor
        \param model : underlying model
        \post A guessing zone graph has been built that defines the semantics
        of model according to OPERATIONAL_ZONE
      */
      gzg_t(syntax::model_t & model)
        : semantics::semantics_t<state_t, edge_range_t>(model),
          _operational(model),
          _relevant_clocks()
      {
        _compute_relevant_clocks();
      }
      
      /*!
        \brief Destructor
      */
      virtual ~gzg_t() = default;
      
      /*!
        \brief Next state computation (see graph::ts_t::next)
        \post nexts is the successor of state s along vedge. The
        status of nexts indicates if vedge is enabled from state s.
      */
      virtual void next(state_t const & s, syntax::vedge_t const & vedge,
                        state_t & nexts) {
        if ( tau(vedge) ) // tau transition
          _next_tau(s, nexts);
        else { // non tau transition
            _model.ta().next(s, vedge, nexts);
            _next(s, vedge, nexts);
          }
      }

      /*!
        \brief Outgoing edges computation (see graph::ts_t::edge_range)
        \return A range over the edges enabled from the vloc in state s.
      */
      virtual edge_range_t outgoing_edges(state_t const & s) {
        auto ta_r = _model.ta().outgoing_edges(s);

        // no tau edge if guess set already empty
        bool skip_tau = s.guess().empty();

        return edge_range_t( tau_range_t(skip_tau), ta_r );
      }

      /*!
        \brief Outputs stats
        \param level : stats level
        \post Stats of underlying operational semantics have been output to
        std::cout (level >= 2)
      */
      virtual void stats(unsigned level) const {
        _operational.stats(level);
      }
    protected:
      /*!
        \brief Initial state computation (see semantics::semantics_t::_initial)
        \post The zone and the guess set in s have been initialized
      */
      virtual void _initial(state_t & s) {
        s._guess.empty();

        // Don't do anything if s is already not valid
        if (s.syntax::state_t::status() == graph::STATE_STATUS_OK) {
            data_t d(_relevant_clocks, s._guess);
            s._zone = _operational.initial(s, d);
          }
        else
          s._zone = nullptr;
      }

      /*!
        \brief Successor state computation (see semantics::semantics_t::_next)
        \post The zone in nexts has been initialized to the successor of the
        zone in s along vedge
      */
      virtual void _next(state_t const & s, syntax::vedge_t const & vedge,
                         state_t & nexts) {
        // Don't compute the zone if nexts is already not valid
        if (nexts.syntax::state_t::status() == graph::STATE_STATUS_OK) {
            // Computes zone and clocks that can be zero after vedge
            clock_bitset_t guess(s._guess);
            data_t d(_relevant_clocks, guess);

            nexts._zone = _operational.next(s, d, * s.zone(), vedge,
                                            nexts); // syntax::state_t part of it

            // Computes next guess set
            nexts._guess = s.guess();
            for (syntax::edge_t const * edge : vedge)
              nexts._guess |= edge->reset();
            nexts._guess &= guess; // NB: guess = relevant clocks that can be 0
          }
        else
          nexts._zone = nullptr;
      }

      /*!
        \brief Successor state computation for tau transition
        \param s : source state
        \param nexts : successor state
        \post nexts is identical to s except the guess set that is empty
       */
      virtual void _next_tau(state_t const & s, state_t & nexts) {
        nexts = s;
        nexts._guess.clear();
      }
      
      /*!
        \brief Computes the set of relevant clocks in _model
        \post _relevant_clocks is the set of clocks that are checked for 0 in
        _model
      */
      void _compute_relevant_clocks() {
        _relevant_clocks.clear();

        syntax::system_t const & system = this->_model.system();

        // Gets all clocks checked for 0 in an invariant
        for (auto r = system.locations(); ! r.at_end(); r.advance()) {
            syntax::loc_t const * loc = r.current();
            _add_relevant_clocks( loc->inv() );
          }

        // Gets all clocks checked for 0 in a guard
        for (auto r = system.edges(); ! r.at_end(); r.advance()) {
            syntax::edge_t const * edge  = r.current();
            _add_relevant_clocks(edge->guard());
          }
      }

      /*!
        \brief Adds relevant clocks from a constraint collection
        \param cc : constraint collection to consider
        \post All the clocks that are checked for zero in cc have been added to
        _relevant_clocks
      */
      void _add_relevant_clocks(symbolic::constraint_collection_t const & cc) {
        for (symbolic::constraint_t const & c : cc)
          if (c.zero_check())
            _relevant_clocks.add(c.i); // c.i <= 0 is a zero check
      }
      virtual void pre(state_t const & src,
                       raw_t * z,
                       syntax::vedge_t const & vedge,
                       state_t const & tgt) override {

      }
      OPERATIONAL_ZONE _operational;   /*!< Underlying operational semantics */
      clock_bitset_t _relevant_clocks; /*!< Clocks checked for 0 in _model */
    };



    
    /* Specialization of gzg_t for various operational semantics */
    

    // Elapsed-last semantics on DBMs

    /* Guessing zone graph with elapsed-last semantics on DBMS
     */
    typedef gzg_t
    <semantics::operational_zone_dbm_t
    <operational_dbm_t
    <semantics::operational_el_dbm_t<operations_dbm_t> > > >
    gzg_el_dbm_t;
    
    /* Guessing zone graph with elapsed-last ExtraLU+,global bounds semantics
       on DBMS
     */
    typedef gzg_t
    <semantics::operational_zone_dbm_t
    <operational_dbm_t
    <semantics::operational_exlug_dbm_t
    <semantics::operational_el_dbm_t<operations_dbm_t> > > > >
    gzg_el_exlug_dbm_t;
    
    /* Guessing zone graph with elapsed-last ExtraLU+,local bounds semantics
       on DBMS
     */
    typedef gzg_t
    <semantics::operational_zone_dbm_t
    <operational_dbm_t
    <semantics::operational_exlul_dbm_t
    <semantics::operational_el_dbm_t<operations_dbm_t> > > > >
    gzg_el_exlul_dbm_t;

    /* Guessing zone graph with elapsed-last ExtraM+,global bounds semantics
       on DBMS
     */
    typedef gzg_t
    <semantics::operational_zone_dbm_t
    <operational_dbm_t
    <semantics::operational_exmg_dbm_t
    <semantics::operational_el_dbm_t<operations_dbm_t> > > > >
    gzg_el_exmg_dbm_t;

    /* Guessing zone graph with elapsed-last ExtraM+,local bounds semantics
       on DBMS
     */
    typedef gzg_t
    <semantics::operational_zone_dbm_t
    <operational_dbm_t
    <semantics::operational_exml_dbm_t
    <semantics::operational_el_dbm_t<operations_dbm_t> > > > >
    gzg_el_exml_dbm_t;



    // Elapsed-last lazy-invariant semantics on DBMs

    /* Guessing zone graph with elapsed-last lazy-invariant semantics on DBMS
     */
    typedef gzg_t
    <semantics::operational_zone_dbm_t
    <operational_dbm_t
    <semantics::operational_el_lazyinv_dbm_t<operations_dbm_t> > > >
    gzg_el_lazyinv_dbm_t;
    
    /* Guessing zone graph with elapsed-last lazy-invariant ExtraLU+,global
       bounds semantics on DBMS
     */
    typedef gzg_t
    <semantics::operational_zone_dbm_t
    <operational_dbm_t
    <semantics::operational_exlug_dbm_t
    <semantics::operational_el_lazyinv_dbm_t<operations_dbm_t> > > > >
    gzg_el_lazyinv_exlug_dbm_t;
    
    /* Guessing zone graph with elapsed-last lazy-invariant ExtraLU+,local
       bounds semantics on DBMS
     */
    typedef gzg_t
    <semantics::operational_zone_dbm_t
    <operational_dbm_t
    <semantics::operational_exlul_dbm_t
    <semantics::operational_el_lazyinv_dbm_t<operations_dbm_t> > > > >
    gzg_el_lazyinv_exlul_dbm_t;

    /* Guessing zone graph with elapsed-last lazy-invariant ExtraM+,global
       bounds semantics on DBMS
     */
    typedef gzg_t
    <semantics::operational_zone_dbm_t
    <operational_dbm_t
    <semantics::operational_exmg_dbm_t
    <semantics::operational_el_lazyinv_dbm_t<operations_dbm_t> > > > >
    gzg_el_lazyinv_exmg_dbm_t;

    /* Guessing zone graph with elapsed-last lazy-invariant ExtraM+,local bounds
       semantics on DBMS
     */
    typedef gzg_t
    <semantics::operational_zone_dbm_t
    <operational_dbm_t
    <semantics::operational_exml_dbm_t
    <semantics::operational_el_lazyinv_dbm_t<operations_dbm_t> > > > >
    gzg_el_lazyinv_exml_dbm_t;




    // Elapsed-last semantics on Shared DBMs

    /* Guessing zone graph with elapsed-last semantics on Shared DBMS
     */
    typedef gzg_t
    <semantics::operational_zone_shdbm_t
    <operational_dbm_t
    <semantics::operational_el_dbm_t<operations_dbm_t> > > >
    gzg_el_shdbm_t;
    
    /* Guessing zone graph with elapsed-last ExtraLU+,global bounds semantics
       on Shared DBMS
     */
    typedef gzg_t
    <semantics::operational_zone_shdbm_t
    <operational_dbm_t
    <semantics::operational_exlug_dbm_t
    <semantics::operational_el_dbm_t<operations_dbm_t> > > > >
    gzg_el_exlug_shdbm_t;
    
    /* Guessing zone graph with elapsed-last ExtraLU+,local bounds semantics
       on Shared DBMS
     */
    typedef gzg_t
    <semantics::operational_zone_shdbm_t
    <operational_dbm_t
    <semantics::operational_exlul_dbm_t
    <semantics::operational_el_dbm_t<operations_dbm_t> > > > >
    gzg_el_exlul_shdbm_t;

    /* Guessing zone graph with elapsed-last ExtraM+,global bounds semantics
       on Shared DBMS
     */
    typedef gzg_t
    <semantics::operational_zone_shdbm_t
    <operational_dbm_t
    <semantics::operational_exmg_dbm_t
    <semantics::operational_el_dbm_t<operations_dbm_t> > > > >
    gzg_el_exmg_shdbm_t;

    /* Guessing zone graph with elapsed-last ExtraM+,local bounds semantics
       on Shared DBMS
     */
    typedef gzg_t
    <semantics::operational_zone_shdbm_t
    <operational_dbm_t
    <semantics::operational_exml_dbm_t
    <semantics::operational_el_dbm_t<operations_dbm_t> > > > >
    gzg_el_exml_shdbm_t;



    // Elapsed-last lazy-invariant semantics on Shared DBMs

    /* Guessing zone graph with elapsed-last lazy-invariant semantics on
       Shared DBMS
     */
    typedef gzg_t
    <semantics::operational_zone_shdbm_t
    <operational_dbm_t
    <semantics::operational_el_lazyinv_dbm_t<operations_dbm_t> > > >
    gzg_el_lazyinv_shdbm_t;
    
    /* Guessing zone graph with elapsed-last lazy-invariant ExtraLU+,global
       bounds semantics on Shared DBMS
     */
    typedef gzg_t
    <semantics::operational_zone_shdbm_t
    <operational_dbm_t
    <semantics::operational_exlug_dbm_t
    <semantics::operational_el_lazyinv_dbm_t<operations_dbm_t> > > > >
    gzg_el_lazyinv_exlug_shdbm_t;
    
    /* Guessing zone graph with elapsed-last lazy-invariant ExtraLU+,local
       bounds semantics on Shared DBMS
     */
    typedef gzg_t
    <semantics::operational_zone_shdbm_t
    <operational_dbm_t
    <semantics::operational_exlul_dbm_t
    <semantics::operational_el_lazyinv_dbm_t<operations_dbm_t> > > > >
    gzg_el_lazyinv_exlul_shdbm_t;

    /* Guessing zone graph with elapsed-last lazy-invariant ExtraM+,global
       bounds semantics on Shared DBMS
     */
    typedef gzg_t
    <semantics::operational_zone_shdbm_t
    <operational_dbm_t
    <semantics::operational_exmg_dbm_t
    <semantics::operational_el_lazyinv_dbm_t<operations_dbm_t> > > > >
    gzg_el_lazyinv_exmg_shdbm_t;

    /* Guessing zone graph with elapsed-last lazy-invariant ExtraM+,local bounds
       semantics on Shared DBMS
     */
    typedef gzg_t
    <semantics::operational_zone_shdbm_t
    <operational_dbm_t
    <semantics::operational_exml_dbm_t
    <semantics::operational_el_lazyinv_dbm_t<operations_dbm_t> > > > >
    gzg_el_lazyinv_exml_shdbm_t;





    // Elapsed-last semantics on min graphs

    /* Guessing zone graph with elapsed-last semantics on min graphs
     */
    typedef gzg_t
    <semantics::operational_zone_mg_t
    <operational_dbm_t
    <semantics::operational_el_dbm_t<operations_dbm_t> > > >
    gzg_el_mg_t;
    
    /* Guessing zone graph with elapsed-last ExtraLU+,global bounds semantics
       on min graphs
     */
    typedef gzg_t
    <semantics::operational_zone_mg_t
    <operational_dbm_t
    <semantics::operational_exlug_dbm_t
    <semantics::operational_el_dbm_t<operations_dbm_t> > > > >
    gzg_el_exlug_mg_t;
    
    /* Guessing zone graph with elapsed-last ExtraLU+,local bounds semantics
       on min graphs
     */
    typedef gzg_t
    <semantics::operational_zone_mg_t
    <operational_dbm_t
    <semantics::operational_exlul_dbm_t
    <semantics::operational_el_dbm_t<operations_dbm_t> > > > >
    gzg_el_exlul_mg_t;

    /* Guessing zone graph with elapsed-last ExtraM+,global bounds semantics
       on min graphs
     */
    typedef gzg_t
    <semantics::operational_zone_mg_t
    <operational_dbm_t
    <semantics::operational_exmg_dbm_t
    <semantics::operational_el_dbm_t<operations_dbm_t> > > > >
    gzg_el_exmg_mg_t;

    /* Guessing zone graph with elapsed-last ExtraM+,local bounds semantics
       on min graphs
     */
    typedef gzg_t
    <semantics::operational_zone_mg_t
    <operational_dbm_t
    <semantics::operational_exml_dbm_t
    <semantics::operational_el_dbm_t<operations_dbm_t> > > > >
    gzg_el_exml_mg_t;



    // Elapsed-last lazy-invariant semantics on min graphs

    /* Guessing zone graph with elapsed-last lazy-invariant semantics on min
       graphs
     */
    typedef gzg_t
    <semantics::operational_zone_mg_t
    <operational_dbm_t
    <semantics::operational_el_lazyinv_dbm_t<operations_dbm_t> > > >
    gzg_el_lazyinv_mg_t;
    
    /* Guessing zone graph with elapsed-last lazy-invariant ExtraLU+,global
       bounds semantics on min graphs
     */
    typedef gzg_t
    <semantics::operational_zone_mg_t
    <operational_dbm_t
    <semantics::operational_exlug_dbm_t
    <semantics::operational_el_lazyinv_dbm_t<operations_dbm_t> > > > >
    gzg_el_lazyinv_exlug_mg_t;
    
    /* Guessing zone graph with elapsed-last lazy-invariant ExtraLU+,local
       bounds semantics on min graphs
     */
    typedef gzg_t
    <semantics::operational_zone_mg_t
    <operational_dbm_t
    <semantics::operational_exlul_dbm_t
    <semantics::operational_el_lazyinv_dbm_t<operations_dbm_t> > > > >
    gzg_el_lazyinv_exlul_mg_t;

    /* Guessing zone graph with elapsed-last lazy-invariant ExtraM+,global
       bounds semantics on min graphs
     */
    typedef gzg_t
    <semantics::operational_zone_mg_t
    <operational_dbm_t
    <semantics::operational_exmg_dbm_t
    <semantics::operational_el_lazyinv_dbm_t<operations_dbm_t> > > > >
    gzg_el_lazyinv_exmg_mg_t;

    /* Guessing zone graph with elapsed-last lazy-invariant ExtraM+,local bounds
       semantics on min graphs
     */
    typedef gzg_t
    <semantics::operational_zone_mg_t
    <operational_dbm_t
    <semantics::operational_exml_dbm_t
    <semantics::operational_el_lazyinv_dbm_t<operations_dbm_t> > > > >
    gzg_el_lazyinv_exml_mg_t;



    
    /* Guessing zone graph factory */

    /*!
      \brief Type of guessing zone graph
     */
    typedef semantics::semantics_t<state_t, edge_range_t>
    guessing_zone_graph_t;


    /*!
      \class factory_t
      \brief Factory of zone graphs
     */
    class  factory_t : public singleton_t<factory_t> {

      friend class singleton_t<factory_t>;  // Grants access to cons/Des

    public:
      /*!
        \brief Builds a new guessing zone graph
        \param model : timed automaton
        \param flags : type of zone graph to build
        \return A pointer to a new guessing zone graph over model
        of type required by flags
        \throw std::logic_error : if flags is invalid
      */
      guessing_zone_graph_t * new_guessing_zone_graph(syntax::model_t & model,
                                                      sem_flags_t flags =
          SEM_DEFAULT);
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

  } // end of namespace gzg
  
} // end of namespace semantics

#endif // __TCHECKER_GZG_H__
