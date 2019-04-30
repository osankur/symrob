#ifndef __TCHECKER_ZG_HH__
#define __TCHECKER_ZG_HH__

#include <ostream>
#include <stdexcept>

#include "base/singleton.hh"
#include "semantics/operational.hh"
#include "semantics/semantics.hh"
#include "symbolic/zone.hh"
#include "syntax/model.hh"

#include <dbm/print.h>
/*!
  \file zg.hh
  \brief Zone graphs
*/

namespace semantics {

  /*!
    \namespace zg
    \brief Zone graphs
  */
  namespace zg {

    // State

    /*!
      \class state_t
      \brief State of a zone graph. It is made of a state of an automaton and
      a zone
    */
    class state_t : public syntax::state_t {
    public:
      /*!
        \brief Constructor
      */
      state_t();

      /*!
        \brief Constructor
        \param ta_state : state of the timed automaton
        \param zone : pointer on a zone
        \post this has been initialized to the state (ta_state, zone). It
        stores a pointer to zone
      */
      state_t(syntax::state_t const & ta_state, symbolic::zone_t * zone);

      /*!
        \brief Copy-constructor
        \param s : state to copy from
        \post this has been initialized to a copy of s
      */
      state_t(state_t const & s);

      /*!
        \brief Destructor
      */
      ~state_t();

      /*!
        \brief Assignment operator
        \param s : state to assign from
        \post this has been assigned s
      */
      state_t & operator = (state_t const & s);
      
      /*!
        \brief Accessor
        \return Const pointer to the zone
      */
      symbolic::zone_t const * zone() const;

      /*!
        \brief Equality predicate
        \return True if this and s are equal (i.e. same
        syntax::state_t and same zone), false otherwise
        \pre the zone pointers in this and in s are not nullptr (checked
        by assertion)
      */
      bool operator == (state_t const & s) const;

      /*!
        \brief Hash function
        \return Hash code built from underlying syntax::state_t and the zone
        \pre the zone pointer is not nullptr (checked by assertion)
      */
      size_t hash() const;

      /*!
        \brief Status of state
        \return status of underlying syntax::state_t augmented with status
        of the zone pointer. Flag graph::STATE_STATUS_NO_ZONE is set if
        the zone pointer is nullptr
      */
      unsigned status() const;

      /*!
        \brief Output function
        \param os : output stream
        \post The state has been output to os
        \pre the zone pointer is not nullptr (checked by assertion)
      */
      void output(std::ostream & os) const;

      
      symbolic::zone_t const * _zone;   /*!< The zone in the state */
    };




    // Edge range

    typedef syntax::ta_edge_range_t edge_range_t;



    // Zone graph

    /*!
      \class no_data_t
      \brief Data given to operational semantics. No extra data needed for a
      zone graph
     */
    class no_data_t {
    };



    /*!
      \class zg_t
      \brief Zone graph
      \tparam OPERATIONAL_ZONE : operational semantics on zones
      (see semantics::operational_zone_t)
    */
    template <class OPERATIONAL_ZONE>
    class zg_t : public semantics::semantics_t<state_t, edge_range_t> {
    public:
      /*!
        \brief Constructor
        \param model : underlying model
        \post A zone graph has been built that defines the semantics of model
        according to OPERATIONAL_ZONE
      */
      zg_t(syntax::model_t & model)
        : semantics::semantics_t<state_t, edge_range_t>(model),
          _operational(model) {
      }

      /*!
        \brief Destructor
      */
      virtual ~zg_t() = default;

      /*!
        \brief Next state computation (see graph::ts_t::next)
        \post nexts is the successor of state s along vedge. The
        status of nexts indicates if vedge is enabled from state s.
      */
      virtual void next(state_t const & s, syntax::vedge_t const & vedge,
                        state_t & nexts) {
        _model.ta().next(s, vedge, nexts);
        _next(s, vedge, nexts);
      }

      /*!
        \brief Outgoing edges computation (see graph::ts_t::outgoing_edges)
        \return A range over the edges enabled from the vloc in state s
      */
      virtual edge_range_t outgoing_edges(state_t const & s) {
        return _model.ta().outgoing_edges(s);
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
        \post The zone in s has been initialized
       */
      virtual void _initial(state_t & s) {
        // Don't compute the zone if s is already not valid
        if (s.syntax::state_t::status() == graph::STATE_STATUS_OK)
          s._zone = _operational.initial(s, _data);
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
        if (nexts.syntax::state_t::status() == graph::STATE_STATUS_OK)
          nexts._zone = _operational.next(s, _data, * s.zone(), vedge,
                                          nexts); // syntax::state_t part of it
        else
          nexts._zone = nullptr;
      }
      
      virtual void pre(state_t const & src,
                       raw_t * z,
                       syntax::vedge_t const & vedge,
                       state_t const & tgt) override {
        cindex_t dim = src._zone->dim();
        _operational.pre(src, _data, z, vedge, tgt, dim);
      }
      OPERATIONAL_ZONE _operational; /*!< Underlying operational semantics */
      no_data_t _data;               /*!< No extra data */
    };



    
    /* Specialization of zg_t for various operational semantics */


    /* Operations on DBMs without extra data
     */
    typedef semantics::operations_dbm_t<no_data_t> operations_dbm_t;


    // Elapsed-last semantics on DBMs

    /* Zone graph with elapsed-last semantics on DBMS
     */
    typedef zg_t
    <semantics::operational_zone_dbm_t
    <semantics::operational_el_dbm_t<operations_dbm_t> > >
    zg_el_dbm_t;
    
    /* Zone graph with elapsed-last ExtraLU+,global bounds semantics on DBMS
     */
    typedef zg_t
    <semantics::operational_zone_dbm_t
    <semantics::operational_exlug_dbm_t
    <semantics::operational_el_dbm_t<operations_dbm_t> > > >
    zg_el_exlug_dbm_t;
    
    /* Zone graph with elapsed-last ExtraLU+,local bounds semantics on DBMS
     */
    typedef zg_t
    <semantics::operational_zone_dbm_t
    <semantics::operational_exlul_dbm_t
    <semantics::operational_el_dbm_t<operations_dbm_t> > > >
    zg_el_exlul_dbm_t;

    /* Zone graph with elapsed-last ExtraM+,global bounds semantics on DBMS
     */
    typedef zg_t
    <semantics::operational_zone_dbm_t
    <semantics::operational_exmg_dbm_t
    <semantics::operational_el_dbm_t<operations_dbm_t> > > >
    zg_el_exmg_dbm_t;

    /* Zone graph with elapsed-last ExtraM+,local bounds semantics on DBMS
     */
    typedef zg_t
    <semantics::operational_zone_dbm_t
    <semantics::operational_exml_dbm_t
    <semantics::operational_el_dbm_t<operations_dbm_t> > > >
    zg_el_exml_dbm_t;



    // Elapsed-last lazy-invariant semantics on DBMs

    /* Zone graph with elapsed-last lazy-invariant semantics on DBMS
     */
    typedef zg_t
    <semantics::operational_zone_dbm_t
    <semantics::operational_el_lazyinv_dbm_t<operations_dbm_t> > >
    zg_el_lazyinv_dbm_t;
    
    /* Zone graph with elapsed-last lazy-invariant ExtraLU+,global bounds
       semantics on DBMS
     */
    typedef zg_t
    <semantics::operational_zone_dbm_t
    <semantics::operational_exlug_dbm_t
    <semantics::operational_el_lazyinv_dbm_t<operations_dbm_t> > > >
    zg_el_lazyinv_exlug_dbm_t;
    
    /* Zone graph with elapsed-last lazy-invariant ExtraLU+,local bounds
       semantics on DBMS
     */
    typedef zg_t
    <semantics::operational_zone_dbm_t
    <semantics::operational_exlul_dbm_t
    <semantics::operational_el_lazyinv_dbm_t<operations_dbm_t> > > >
    zg_el_lazyinv_exlul_dbm_t;

    /* Zone graph with elapsed-last lazy-invariant ExtraM+,global bounds
       semantics on DBMS
     */
    typedef zg_t
    <semantics::operational_zone_dbm_t
    <semantics::operational_exmg_dbm_t
    <semantics::operational_el_lazyinv_dbm_t<operations_dbm_t> > > >
    zg_el_lazyinv_exmg_dbm_t;

    /* Zone graph with elapsed-last lazy-invariant ExtraM+,local bounds
       semantics on DBMS
     */
    typedef zg_t
    <semantics::operational_zone_dbm_t
    <semantics::operational_exml_dbm_t
    <semantics::operational_el_lazyinv_dbm_t<operations_dbm_t> > > >
    zg_el_lazyinv_exml_dbm_t;




    // Elapsed-last semantics on Shared DBMs

    /* Zone graph with elapsed-last semantics on Shared DBMS
     */
    typedef zg_t
    <semantics::operational_zone_shdbm_t
    <semantics::operational_el_dbm_t<operations_dbm_t> > >
    zg_el_shdbm_t;
    
    /* Zone graph with elapsed-last ExtraLU+,global bounds semantics on
       Shared DBMS
     */
    typedef zg_t
    <semantics::operational_zone_shdbm_t
    <semantics::operational_exlug_dbm_t
    <semantics::operational_el_dbm_t<operations_dbm_t> > > >
    zg_el_exlug_shdbm_t;
    
    /* Zone graph with elapsed-last ExtraLU+,local bounds semantics on
       Shared DBMS
     */
    typedef zg_t
    <semantics::operational_zone_shdbm_t
    <semantics::operational_exlul_dbm_t
    <semantics::operational_el_dbm_t<operations_dbm_t> > > >
    zg_el_exlul_shdbm_t;

    /* Zone graph with elapsed-last ExtraM+,global bounds semantics on
       Shared DBMS
     */
    typedef zg_t
    <semantics::operational_zone_shdbm_t
    <semantics::operational_exmg_dbm_t
    <semantics::operational_el_dbm_t<operations_dbm_t> > > >
    zg_el_exmg_shdbm_t;

    /* Zone graph with elapsed-last ExtraM+,local bounds semantics on
       Shared DBMS
     */
    typedef zg_t
    <semantics::operational_zone_shdbm_t
    <semantics::operational_exml_dbm_t
    <semantics::operational_el_dbm_t<operations_dbm_t> > > >
    zg_el_exml_shdbm_t;



    // Elapsed-last lazy-invariant semantics on Shared DBMs

    /* Zone graph with elapsed-last lazy-invariant semantics on Shared DBMS
     */
    typedef zg_t
    <semantics::operational_zone_shdbm_t
    <semantics::operational_el_lazyinv_dbm_t<operations_dbm_t> > >
    zg_el_lazyinv_shdbm_t;
    
    /* Zone graph with elapsed-last lazy-invariant ExtraLU+,global bounds
       semantics on Shared DBMS
     */
    typedef zg_t
    <semantics::operational_zone_shdbm_t
    <semantics::operational_exlug_dbm_t
    <semantics::operational_el_lazyinv_dbm_t<operations_dbm_t> > > >
    zg_el_lazyinv_exlug_shdbm_t;
    
    /* Zone graph with elapsed-last lazy-invariant ExtraLU+,local bounds
       semantics on Shared DBMS
     */
    typedef zg_t
    <semantics::operational_zone_shdbm_t
    <semantics::operational_exlul_dbm_t
    <semantics::operational_el_lazyinv_dbm_t<operations_dbm_t> > > >
    zg_el_lazyinv_exlul_shdbm_t;

    /* Zone graph with elapsed-last lazy-invariant ExtraM+,global bounds
       semantics on Shared DBMS
     */
    typedef zg_t
    <semantics::operational_zone_shdbm_t
    <semantics::operational_exmg_dbm_t
    <semantics::operational_el_lazyinv_dbm_t<operations_dbm_t> > > >
    zg_el_lazyinv_exmg_shdbm_t;

    /* Zone graph with elapsed-last lazy-invariant ExtraM+,local bounds
       semantics on Shared DBMS
     */
    typedef zg_t
    <semantics::operational_zone_dbm_t
    <semantics::operational_exml_dbm_t
    <semantics::operational_el_lazyinv_dbm_t<operations_dbm_t> > > >
    zg_el_lazyinv_exml_shdbm_t;





    // Elapsed-last semantics on min graphs

    /* Zone graph with elapsed-last semantics on min graphs
     */
    typedef zg_t
    <semantics::operational_zone_mg_t
    <semantics::operational_el_dbm_t<operations_dbm_t> > >
    zg_el_mg_t;
    
    /* Zone graph with elapsed-last ExtraLU+,global bounds semantics on min
       graphs
     */
    typedef zg_t
    <semantics::operational_zone_mg_t
    <semantics::operational_exlug_dbm_t
    <semantics::operational_el_dbm_t<operations_dbm_t> > > >
    zg_el_exlug_mg_t;
    
    /* Zone graph with elapsed-last ExtraLU+,local bounds semantics on min
       graphs
     */
    typedef zg_t
    <semantics::operational_zone_mg_t
    <semantics::operational_exlul_dbm_t
    <semantics::operational_el_dbm_t<operations_dbm_t> > > >
    zg_el_exlul_mg_t;

    /* Zone graph with elapsed-last ExtraM+,global bounds semantics on min
       graphs
     */
    typedef zg_t
    <semantics::operational_zone_mg_t
    <semantics::operational_exmg_dbm_t
    <semantics::operational_el_dbm_t<operations_dbm_t> > > >
    zg_el_exmg_mg_t;

    /* Zone graph with elapsed-last ExtraM+,local bounds semantics on min
       graphs
     */
    typedef zg_t
    <semantics::operational_zone_mg_t
    <semantics::operational_exml_dbm_t
    <semantics::operational_el_dbm_t<operations_dbm_t> > > >
    zg_el_exml_mg_t;



    // Elapsed-last lazy-invariant semantics on min graphs

    /* Zone graph with elapsed-last lazy-invariant semantics on min graphs
     */
    typedef zg_t
    <semantics::operational_zone_mg_t
    <semantics::operational_el_lazyinv_dbm_t<operations_dbm_t> > >
    zg_el_lazyinv_mg_t;
    
    /* Zone graph with elapsed-last lazy-invariant ExtraLU+,global bounds
       semantics on min graphs
     */
    typedef zg_t
    <semantics::operational_zone_mg_t
    <semantics::operational_exlug_dbm_t
    <semantics::operational_el_lazyinv_dbm_t<operations_dbm_t> > > >
    zg_el_lazyinv_exlug_mg_t;
    
    /* Zone graph with elapsed-last lazy-invariant ExtraLU+,local bounds
       semantics on min graphs
     */
    typedef zg_t
    <semantics::operational_zone_mg_t
    <semantics::operational_exlul_dbm_t
    <semantics::operational_el_lazyinv_dbm_t<operations_dbm_t> > > >
    zg_el_lazyinv_exlul_mg_t;

    /* Zone graph with elapsed-last lazy-invariant ExtraM+,global bounds
       semantics on min graphs
     */
    typedef zg_t
    <semantics::operational_zone_mg_t
    <semantics::operational_exmg_dbm_t
    <semantics::operational_el_lazyinv_dbm_t<operations_dbm_t> > > >
    zg_el_lazyinv_exmg_mg_t;

    /* Zone graph with elapsed-last lazy-invariant ExtraM+,local bounds
       semantics on min graphs
     */
    typedef zg_t
    <semantics::operational_zone_mg_t
    <semantics::operational_exml_dbm_t
    <semantics::operational_el_lazyinv_dbm_t<operations_dbm_t> > > >
    zg_el_lazyinv_exml_mg_t;



    
    /* Zone graph factory */

    /*!
      \brief Type of zone graph
     */
    typedef semantics::semantics_t<state_t, edge_range_t>
    zone_graph_t;
    

    /*!
      \class factory_t
      \brief Factory of zone graphs
     */
    class factory_t : public singleton_t<factory_t> {

      friend class singleton_t<factory_t>;  // Grants access to cons/Des

    public:
      /*!
        \brief Builds a new zone graph
        \param model : timed automaton
        \param flags : type of zone graph to build
        \return A shared pointer to the new zone graph over model of type
        required by flags
        \throw std::logic_error : if flags is invalid
      */
      zone_graph_t * new_zone_graph(syntax::model_t & model,
                                    sem_flags_t flags = SEM_DEFAULT);
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

  } // end of namespace zg

} // end of namespace semantics


#endif // __TCHECKER_ZG_HH__
