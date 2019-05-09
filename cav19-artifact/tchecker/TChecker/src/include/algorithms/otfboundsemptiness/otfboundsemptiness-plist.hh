#ifndef __TCHECKER_ALGORITHMS_OTF_BOUNDS_EMPTINESS_PLIST_HH__
#define __TCHECKER_ALGORITHMS_OTF_BOUNDS_EMPTINESS_PLIST_HH__

#include <functional>
#include <list>

#include "base/ptr.hh"
#include "base/singleton.hh"
#include "syntax/ta.hh"

/*!
  \file otfboundsemptiness-plist.hh
  \brief Propagation list for emptiness algorithms with on-the-fly clock
  bounds computation
*/

namespace algorithms {

  namespace otfboundsemptiness {

    /*!
      \class propagation_list_data_t
      \brief Propagated data for on-the-fly bounds generic algorithm. Yields
      access to the node from which bounds are propagated (from), to the node
      to which they are propagated (to), and to the propagation edge (vedge).

      If the propagation edge points to nullptr, then it is a copy edge and
      the bounds are simply copied from node "from" to node "to"

      vedge stores a pointer to a vedge in the ASG. This pointer should not be
      deleted
      
      \tparam NODE : type of nodes
    */
    template <class NODE>
    class propagation_list_data_t {
    public:
      /*!
	\brief Constructor
       */
      propagation_list_data_t() : from(nullptr), to(nullptr), vedge(nullptr) {
      }


      /*!
	\brief Destructor
      */
      /* IMPLEMENTATION NOTE: do not delete nodes */
      virtual ~propagation_list_data_t() {
	// IMPLEMENTATION NOTE: do not delete vedge that is managed by ASG
      }


      /*!
	\brief Clears the data
	\post from, to and edge point to nullptr
      */
      virtual void clear() {
	from = nullptr;
	to = nullptr;
	vedge = nullptr;
	// IMPLEMENTATION NOTE: do not delete vedge that is managed by ASG
      }


      /*!
	\brief Copy propagation predicate
	\return True if it is a copy propagation, false otherwise
       */
      virtual bool is_copy() const {
	return ( vedge == nullptr );
      }

      
      /*!
	\brief Merge pdatas
	\param pdata : data to merge
	\pre pdata can be merged in this (checked by assertion)
	\post pdata has been merged into this
       */
      void merge(propagation_list_data_t<NODE> const & pdata) {
	assert(mergeable(pdata));
      }

      
      /*!
	\brief Checks if propagation data can be merged
	\param pdata : data to merge
	\post True of pdata can be merged in this, false otherwise
       */
      bool mergeable(propagation_list_data_t<NODE> const & pdata) {
	return ( (from == pdata.from) &&
		 (to == pdata.to) &&
		 (* vedge == * pdata.vedge) );
      }


      /*!
	\brief Propagation predicate
	\return True if data needs propagation, false otherwise
       */
      virtual bool needs_propagation() const = 0;


      /*!< Propagate from node */
      NODE * from;
      /*!< Propagate to node */
      NODE * to;
      /*!< Propagation edge (copy if nullptr), DO NOT DELETE */
      syntax::vedge_t const * vedge;
    };


    /*!
      \brief Makes propagation data an edge propagation
      \tparam NODE : type of nodes
      \tparam PDATA : type of propagation data, should inherit from
      propagation_list_data_t<NODE>
      \param pdata : propagation data
      \param from : source node
      \param to : target node
      \param vedge : propagation edge
      \pre vedge points to an edge (checked by assertion)
      \post pdata has from node "from", to node "to" and it stores a pointer
      to propagation edge "vedge"
     */
    template <class NODE, class PDATA>
    void make_edge_propagation(PDATA & pdata, NODE * from, NODE * to,
			       syntax::vedge_t const * vedge) {
      assert( vedge != nullptr );
      /* static_assert( std::is_base_of( propagation_list_data_t<NODE>,
	 PDATA ) ); */
      pdata.from = from;
      pdata.to = to;
      pdata.vedge = vedge;
    }


    /*!
      \brief Makes propagation data a copy propagation
      \tparam NODE : type of nodes
      \tparam PDATA : type of propagation data, should inherit from
      propagation_list_data_t<NODE>
      \param pdata : propagation data
      \param from : source node
      \param to : target node
      \post pdata has from node "from", to node "to" and is a copy propagation
      data
     */
    template <class NODE, class PDATA>
    void make_copy_propagation(PDATA & pdata, NODE * from, NODE * to) {
      /* static_assert( std::is_base_of( propagation_list_data_t<NODE>,
	 PDATA ) ); */

      pdata.from = from;
      pdata.to = to;
      pdata.vedge = nullptr;
    }

    

    /* Generic propagation list */

    /*!
      \class propagation_list_t
      \brief A list that stores propagation data
      \tparam PDATA : type of data propagated, should derive from
      propagation_list_data_t<NODE>
     */
    template <class PDATA> class propagation_list_t {

      /* static_assert( PDATA derives from propagation_list_data_t<NODE> ) */

    public:
      /*!
	\brief Destructor
       */
      virtual ~propagation_list_t() = default;

      /*!
	\brief Pushes propagation data in the list
	\param pdata : propagation to push
	\post pdata has been pushed to the list
       */
      virtual void push(PDATA & pdata) = 0;

      /*!
	\brief Returns and pops top data from the list
	\return The top data from the list
	\pre the list is not empty
	\post the top data has been popped from the list
       */
      virtual PDATA pop() = 0;

      /*!
	\brief Checks if the list is empty
	\return True when the list is empty, false otherwise
       */
      virtual bool empty() const = 0;
    };




    /* FIFO propagation list */


    /*!
      \class fifo_propagation_list_t
      \brief A list that stores propagation data implementing FIFO policy
      \tparam PDATA : type of data propagated, should derive from
      propagation_list_data_t<NODE>
     */
    template <class PDATA>
    class fifo_propagation_list_t : public propagation_list_t<PDATA>,
				    private std::list<PDATA> {

      /* static_assert( PDATA derives from propagation_list_data_t<NODE> ) */

    public:
      /*!
	\brief Destructor
       */
      virtual ~fifo_propagation_list_t() = default;

      /*!
	\brief see propagation_list_t::push
       */
      virtual void push(PDATA & pdata) {
	this->std::list<PDATA>::push_back(pdata);
      }

      /*!
	\brief see propagation_list_t::pop
       */
      virtual PDATA pop() {
	PDATA d = this->std::list<PDATA>::front();
	this->std::list<PDATA>::pop_front();
	return d;
      }

      /*!
	\brief see propagation_list_t::empty
       */
      virtual bool empty() const {
	return this->std::list<PDATA>::empty();
      }
    };



    /* SORTED propagation list */


    /*!
      \brief Predicate over propagation data for sorted propagation list
      \tparam PDATA: type of propagation data
    */
    template <class PDATA>
    using pdata_predicate_t = std::function<bool(PDATA const &, PDATA const &)>;



    /*!
      \class sorted_propagation_list_t
      \brief A list that stores propagation data implementing smallest pdata
      first
      \tparam PDATA : type of data propagated, should derive from
      propagation_list_data_t<NODE>
     */
    template <class PDATA>
    class sorted_propagation_list_t : public propagation_list_t<PDATA>,
				      private std::list<PDATA> {

      /* static_assert( PDATA derives from propagation_list_data_t<NODE> ) */

    public:
      /*!
	\brief Constructor
	\param lt : less-than predicate to sort pdata
	\post this stores a reference to lt
      */
      sorted_propagation_list_t(pdata_predicate_t<PDATA> const & lt) : _lt(lt) {
      }

      /*!
	\brief Destructor
       */
      virtual ~sorted_propagation_list_t() = default;

      /*!
	\brief see propagation_list_t::push
       */
      virtual void push(PDATA & pdata) {
	for (auto it = this->std::list<PDATA>::begin();
	     it != this->std::list<PDATA>::end(); ++it) {
	  PDATA & p = *it;

	  // Merge if possible
	  if ( p.mergeable(pdata) ) {
	    p.merge(pdata);
	    return;
	  }
	  else if ( _lt(pdata, p) ) { // pdata should be inserted here
	    this->std::list<PDATA>::insert(it, pdata);
	    return;
	  }
	}

	// pdata is not less-than any element in the list: insert at the end
	this->std::list<PDATA>::push_back(pdata);
      }

      /*!
	\brief see propagation_list_t::pop
       */
      virtual PDATA pop() {
	PDATA d = this->std::list<PDATA>::front();
	this->std::list<PDATA>::pop_front();
	return d;
      }

      /*!
	\brief see propagation_list_t::empty
       */
      virtual bool empty() const {
	return this->std::list<PDATA>::empty();
      }
    private:
      /*!< Less-than predicate over pdata */
      pdata_predicate_t<PDATA> const & _lt;
    };



    /* Propagation list factory */

    /*!
      \brief Setup flags for propagation lists
     */
    typedef char plist_flags_t;

    const plist_flags_t PLIST_FIFO   = 0; /*!< FIFO propagation list */
    const plist_flags_t PLIST_SORTED = 1; /*!< Sorted propagation list */

    /*!< Default propagation list */
    const plist_flags_t PLIST_DEFAULT = PLIST_FIFO;

    
    /*!
      \class plist_factory_t
      \brief Propagation list factory
     */
    class plist_factory_t : public singleton_t< plist_factory_t > {
      
      friend class singleton_t< plist_factory_t >; // Grants access to cons/des

    public:
      /*!
	\brief Builds a new propagation list (except sorted propagation list)
	\tparam PDATA : type of propagation data. Should derive from
	propagation_list_data_t
	\param flags : type of propagation list to build
	\return A new propagation list with type required by flags
	\throw std::logic_error : if flags is invalid
       */
      template <class PDATA>
      propagation_list_t<PDATA> * new_plist(plist_flags_t flags=PLIST_DEFAULT) {
	propagation_list_t<PDATA> * plist = nullptr;

	switch (flags) {
	case PLIST_FIFO:
	  plist = new fifo_propagation_list_t<PDATA>();
	  break;
	default:
	  throw std::logic_error
	    ("*** algorithms::otfboundsemptiness::plist_factory_t::new_plist: "
	     "invalid flags");
	  break;
	}

	return plist;
      }

      /*!
	\brief Builds a new propagation list (including sorted propagation list)
	\tparam PDATA : type of propagation data. Should derive from
	propagation_list_data_t
	\param lt : less-than predicate to sort the list
	\param flags : type of propagation list to build
	\return A new propagation list with type required by flags
	\throw std::logic_error : if flags is invalid
       */
      template <class PDATA>
      propagation_list_t<PDATA> * new_plist(pdata_predicate_t<PDATA> const & lt,
					    plist_flags_t flags=PLIST_DEFAULT) {
	propagation_list_t<PDATA> * plist = nullptr;

	switch (flags) {
	case PLIST_SORTED:
	  plist = new sorted_propagation_list_t<PDATA>(lt);
	  break;
	default:
	  plist = new_plist<PDATA>(flags);
	  break;
	}

	return plist;
      }
    private:
      /*!
	\brief Constructor (private)
      */
      plist_factory_t() = default;

      /*!
	\brief Destructor (private)
       */
      ~plist_factory_t() = default;
    };

  } // end of namespace otfboundsemptiness

} // end of namespace algorithms

#endif // __TCHECKER_ALGORITHMS_OTF_BOUNDS_EMPTINESS_PLIST_HH__
