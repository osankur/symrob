#ifndef __TCHECKER_SYNC_PRODUCT_HH__
#define __TCHECKER_SYNC_PRODUCT_HH__

#include <ostream>
#include <vector>

#include <boost/container/flat_set.hpp>

#include "base/ptr.hh"
#include "base/range.hh"
#include "syntax/layout.hh"
#include "syntax/locs_edges.hh"
#include "syntax/synchro.hh"
#include "syntax/system_fwd.hh"


/*!
  \file sync_product.h
  \brief Synchronization of processes in a system

  Synchronized locations and edges are represented by tuples of process
  locations (see syntax::vloc_t) and tuples of process edges
  (see syntax::vedge_t) respectively.

  Depending on the synchronization policy, process edges may be synchronized on
  events. A synchronizer (see syntax::synchronizer_t) defines such a policy and
  provides an iterator over synchronized (or asynchronous) edges.
*/

namespace syntax {

  // Synchronization
  
  /*!
    \brief Range of synchronized edges
  */
  typedef range_t<vedge_t const &> vedge_range_t;


  /*!
    \class synchronizer_t
    \brief Set of synchronization vectors
   */
  class synchronizer_t {
  public:
    /*!
      \brief Destructor
    */
    virtual ~synchronizer_t();

    /*!
      \brief Accessor to synchronized edges
      \param vloc : tuple of process locations (source state)
      \param l : layout (source state)
      \return Range of all synchronized edges enabled from vloc. It is not
      checked whether synchronized edges are enabled w.r.t. layout.
    */
    virtual sp_t<vedge_range_t>
    outgoing_edges(vloc_t const & vloc, layout_t const & layout) const = 0;
  };




  /*!
    \class synchronized_product_t
    \brief Synchronized product of processes
   */
  class synchronized_product_t : public synchronizer_t {
  public:
    /*!
      \brief Synchronization vector
    */
    typedef boost::container::flat_map<proc_id_t,
				       sync_label_t const *> sync_vector_t;

    /*!
      \brief Constructor
      \post The set of synchronized vectors is empty
    */
    synchronized_product_t(system_t const & system);

    /*!
      \brief Destructor
     */
    virtual ~synchronized_product_t();

    /*!
      \brief see synchronizer_t::vedges
      \return Return a range that contains a synchronized edge for every
      synchronization vector enabled in vloc, and a single-process
      synchronized edge for every asynchronous edge enabled in vloc
     */
    virtual sp_t<vedge_range_t>
    outgoing_edges(vloc_t const & vloc, layout_t const & layout) const;

    /*!
      \brief Range of synchonization vectors
    */
    typedef container_range_t< std::vector<sync_vector_t> const,
			       std::vector<sync_vector_t>::const_iterator,
			       sync_vector_t const & > sync_range_t;

    /*!
      \brief Accessor
      \return The range of synchronization vectors with const dereference
      access
    */
    sync_range_t syncs() const;

    /*!
      \brief Vector declaration
      \param events : synchronized events. Should follow the syntax:
      P1.a,P2.b,...,Pk.z (see parse_id_list and parse_dot_separated_ids for
      more details)
      \post The vector described by events has been declared
      \throw std::invalid_argument : if less than two processes are involved
      \throw std::invalid_argument : if one of the process name or event name
      is a reserved name
      \throw std::invalid_argument : if one process has more than one
      synchronization in events
      \throw std::invalid_argument : if a synchronized event is unknown to the
      corresponding process
    */
    void add_sync(std::string const & events);

    /*!
      \brief Vector declaration
      \param v : vector to declare
      \post v has been added to declared vectors
     */
    void add_sync(sync_vector_t const & v);

    /*!
      \brief Displays declared vectors
      \post All declared vectors has been output to os
     */
    virtual void output (std::ostream & os) const;
  private:
    system_t const & _system;                 /*!< Underlying system */
    std::vector<sync_vector_t> _decl_vectors; /*!< Declared vectors */
    /*!< Asynchronous edges */
    boost::container::flat_set<edge_t const *> _async_edges;
  };



  /*!
    \class asynchronous_product_t
    \brief Asynchronous product of processes
   */
  class asynchronous_product_t : public synchronizer_t {
  public:
    /*!
      \brief Constructor
    */
    asynchronous_product_t();
    
    /*!
      \brief Destructor
    */
    virtual ~asynchronous_product_t();

    /*!
      \brief see synchronizer_t::vedges
      \return Return a range that contains a synchronized edge for every
      synchronization vector enabled in vloc, and a single-process
      synchronized edge for every asynchronous edge enabled in vloc
     */
    virtual sp_t<vedge_range_t>
    outgoing_edges(vloc_t const & vloc, layout_t const & layout) const;
  };

} // namespace syntax

#endif // __TCHECKER_SYNC_PRODUCT_HH__
