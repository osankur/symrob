#ifndef __TCHECKER_LOCS_EDGES_HH__
#define __TCHECKER_LOCS_EDGES_HH__

#include <cstddef>
#include <string>
#include <vector>

#include "base/clockset.hh"
#include "base/labelset.hh"
#include "base/range.hh"
#include "symbolic/constraints.hh"
#include "syntax/layout.hh"
#include "syntax/synchro.hh"
#include "syntax/system_fwd.hh"

/*!
  \file locs_edges.hh
  \brief Definition of locations, edges, tuples of locations and tuples
  of edges
*/

namespace syntax {
  
  // Forward declarations
  
  class edge_t;

  
  // Locations
  
  /*!
    \class loc_t
    \brief A process location
  */
  class loc_t {
  public:
    /*!
      \typedef unsigned char flags_t
      \brief Type of location flags
    */
    typedef unsigned char flags_t;
    
    static const flags_t NO        = 0;  /*!< Normal location */
    static const flags_t INIT      = 1;  /*!< Initial location */
    static const flags_t COMMITTED = 2;  /*!< Committed location (UPPAAL) */
    static const flags_t URGENT    = 4;  /*!< Urgent location (UPPAAL) */

    /*!
      \brief Constructor
      \param pid : identifier of the process that owns the location
      \param name : name of the location
      \param inv : invariant of the location
      \param lassert : assertion on layout
      \param labels : labels of the location
      \param flags : flags of the location
      \thow std::invalid_argument if given an empty name
      \thow std::invalid_argument if flags is both COMMITTED and URGENT
    */
    loc_t(proc_id_t pid,
	  std::string const & name,
	  symbolic::constraint_collection_t const & inv,
	  layout_predicate_t const & lassert,
	  labels_t const & labels,
	  flags_t flags);

    /*!
      \brief Copy constructor
      \param loc : location to copy from
    */
    loc_t(loc_t const & loc);
    
    /*!
      \brief Destructor
    */
    ~loc_t();
    
    /*!
      \brief Assignement operator
      \param loc : location to assign from
      \return Location that has been assigned loc to
    */
    loc_t & operator = (loc_t const & loc);

    /*!
      \brief Accessor
      \return Identifier of the process that owns the location
    */
    proc_id_t pid() const;

    /*!
      \brief Accessor
      \return Name of the location
    */
    std::string const & name() const;
    
    /*!
      \brief Accessor
      \return Invariant on clocks
    */
    symbolic::constraint_collection_t const & inv() const;
    
    /*!
      \brief Accessor
      \return Assertion on layout
    */
    layout_predicate_t const & lassert() const;

    /*!
      \brief Accessor
      \return Labels
    */
    labels_t const & labels() const;

    /*!
      \brief Accessor
      \return Flags
    */
    flags_t flags() const;

    /*!
      \brief Adds outgoing edge
      \param edge : outgoing edge
      \post edge has been added to this' outgoing edges
      \throw std::invalid_argument if this is not the source location of edge
     */
    void add_outgoing_edge(edge_t const * edge);

    /*!
      \brief Adds incoming edge
      \param edge : incoming edge
      \post edge has been added to this' incoming edges
      \throw std::invalid_argument if this is not the target location of edge
     */
    void add_incoming_edge(edge_t const * edge);

    /*!
      \brief Range of edges
    */
    typedef container_range_t< std::vector<edge_t const *> const,
			       std::vector<edge_t const *>::const_iterator,
			       edge_t const * > edge_range_t;

    /*!
      \brief Accessor
      \return Range of outgoing edges
     */
    edge_range_t outgoing_edges() const;

    /*!
      \brief Accessor
      \return Range of incoming edges
    */
    edge_range_t incoming_edges() const;
  private:
    proc_id_t _pid;                               /*!< Owner's PID */
    std::string _name;                            /*!< Location name */
    symbolic::constraint_collection_t _inv;       /*!< Invariant on clocks */
    layout_predicate_t _lassert;                  /*!< Assertion on layout */
    labels_t _labels;                             /*!< Labels */
    flags_t _flags;                               /*!< Flags */
    std::vector<edge_t const *> _outgoing_edges;  /*!< Outgoing edges */
    std::vector<edge_t const *> _incoming_edges;  /*!< Incoming edges */
  };

  


  // Edges

  /*!
    \class edge_t
    \brief A process edge
  */
  class edge_t {
  public:
    /*!
      \brief Constructor
      \param pid : identifier of process owning the edge
      \param src : source location
      \param tgt : target location
      \param guard : guard on clocks
      \param reset : clocks to be reset on the edge
      \param event : synchronization event
      \param lguard : guard on layout
      \param lupdate : update to apply on layout
      \post Stores pointers to *src, *tgt and *event
    */
    edge_t(proc_id_t pid,
	   loc_t const * src,
	   loc_t const * tgt,
	   symbolic::constraint_collection_t const & guard,
	   clocks_t const & reset,
	   sync_label_t const * event,
	   layout_predicate_t const & lguard,
	   layout_update_t const & lupdate);

    /*!
      \brief Copy constructor
      \param e : edge to copy from
    */
    edge_t(edge_t const & e);

    /*!
      \brief Destructor
    */
    ~edge_t();

    /*!
      \brief Assignement operator
      \param e : edge to assign from
      \return The edge that has been assigned e
      \post e has bee nassigend to the instance
    */
    edge_t & operator = (edge_t const & e);

    /*!
      \brief Accessor
      \return Identifier of process owning the edge
    */
    proc_id_t pid() const;

    /*!
      \brief Accessor
      \return Pointer to source location
    */
    loc_t const * src() const;

    /*!
      \brief Accessor
      \return Pointer to target location
    */
    loc_t const * tgt() const;

    /*!
      \brief Accessor
      \return The guard on clocks
    */
    symbolic::constraint_collection_t const & guard() const;

    /*!
      \brief Accessor
      \return The set of clocks to reset
    */
    clocks_t const & reset() const;

    /*!
      \brief Accessor
      \return Synchronization event
    */
    sync_label_t const * event() const;

    /*!
      \brief Accessor
      \return The guard on layout
    */
    layout_predicate_t const & lguard() const;

    /*!
      \brief Accessor
      \return The update to apply to layout
    */
    layout_update_t const & lupdate() const;
  private:
    proc_id_t _pid;                           /*!< Owner ID */
    loc_t const * _src;                       /*!< Source location */
    loc_t const * _tgt;                       /*!< Target location */
    symbolic::constraint_collection_t _guard; /*!< Guard on clocks */
    clocks_t _reset;                          /*!< Clocks to reset */
    sync_label_t const * _event;              /*!< Synchronization event */
    layout_predicate_t _lguard;               /*!< Guard on layout */
    layout_update_t _lupdate;                 /*!< Update on layout */
  };



  // Tuples of locations
  
  /*!
    \class vloc_t
    \brief Tuple of locations
  */
  class vloc_t : public std::vector<loc_t const *> {
  public:
    /*!
      \brief Constructor
      \param n : dimension of the tuple of locations
      \post A tuple of size n has been allocated
    */
    vloc_t(size_type n);
    
    /*!
      \brief Copy-constructor
      \param vloc : tuple of locations to copy
      \post A tuple has been allocated an initialized to vloc
    */
    vloc_t(vloc_t const & vloc);

    /*!
      \brief Destructor
    */
    ~vloc_t();

    /*!
      \brief Hash function
      \return Hash code of the tuple of location ids
    */
    size_t hash() const;

    /*!
      \brief Output function
      \param os : output stream
      \post The tuple of location ids has been output to os
    */
    void output(std::ostream & os) const;

    /*!
      \brief Accessor to memory footprint
      \return Approximate memory footprint of the tuple of locations
     */
    std::size_t memsize() const;

    /*!
      \brief Accesor to flag
      \return Combined flags of locations in vloc
    */
    loc_t::flags_t flags() const;
  };



  // Tuples of edges

  /*!
    \class vedge_t
    \brief Tuple of synchronized edges
  */
  class vedge_t : public std::vector<edge_t const *> {
  public:
    /*!
      \brief Constructor
      \post empty tuple of edges
    */
    vedge_t();

    /*!
      \brief Constructor
      \param n : number of synchronized edges
      \post The tuple of edges is empty and has capacity to store n pointers to
      edges. The pointers have been initialized to nullptr.
    */
    vedge_t(size_type n);

    /*!
      \brief Constructor
      \param edge : an edge
      \post this only contains edge
    */
    vedge_t(edge_t const * edge);

    /*!
      \brief Copy-constructor
      \param v : tuple of edges to build from
    */
    vedge_t(vedge_t const & v);

    /*!
      \brief Destructor
    */
    ~vedge_t();
    
    /*!
      \brief Hash function
      \return Hash code of the tuple of edges
    */
    size_t hash() const;

    /*!
      \brief Output function
      \param os : output stream
      \post The tuple of edges has been output to os
    */
    void output(std::ostream & os) const;

    /*!
      \brief Accessor to memory footprint
      \return Approximate memory footprint of the tuple of edges
     */
    std::size_t memsize() const;
  };

} // namespace syntax

#endif // __TCHECKER_LOCS_EDGES_HH__
