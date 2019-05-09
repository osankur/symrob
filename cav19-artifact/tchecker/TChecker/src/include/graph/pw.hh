#ifndef __TCHECKER_PW_HH__
#define __TCHECKER_PW_HH__

#include <functional>
#include <limits>
#include <stdexcept>
#include <vector>

#include <boost/functional/hash.hpp>
#include <boost/unordered_map.hpp>

#include "base/intrusive_list.hh"
#include "base/singleton.hh"
#include "base/stats.hh"
#include "graph/nodescmp.hh"
#include "syntax/ta.hh"

/*!
  \file pw.hh
  \brief Passed-waiting list of nodes
 */

namespace graph {


  /* Nodes */

  /*!
    \brief Nodes for passed list (see graph::passed_t)
  */
  struct ptag {};
  typedef intrusive_list_hook_t<ptag> p_node_t;

  /*!
    \brief Nodes for waiting list (see graph::waiting_t)
  */
  struct wtag {};
  typedef intrusive_list_hook_t<wtag> w_node_t;
  
  /*!
    \class pw_node_t
    \brief Nodes for passed-waiting list (see graph::pw_generic_t)
  */
  class pw_node_t : public p_node_t, public w_node_t {
  public:
  };




  /* Passed-waiting list */

  /* IMPLEMENTATION NOTE: pw_generic_t is a generic implementation of a
     passed-waiting list that is parametrized by an implementation of the
     passed list and by an implementation of the waiting list. The class
     pw_t below is specialized for given implementations (the ones needed in
     TChecker). The class pw_t, which only as the type of nodes as a template
     parameter, is needed by pw_factory_t (see below) and by the algorithms.
  */

  

  /*!
    \class pw_generic_t
    \brief Generic passed-waiting list of nodes

    A passed-waiting list stored passed nodes and waiting nodes in a single
    data structure. This allows to iterate and remove nodes from both lists
    at the same time. A passed-waiting list is parametrized by a predicate, leq,
    on nodes. The predicate is used to detect if a node to insert in the
    structure is covered by some node already in the structure. If not, it is
    then used to detect if a newly inserted node covers some node in the
    structure. The structure guarantees that if a node is covered, it is not
    inserted, and if a node is inserted, then all the nodes that it covers are
    removed.

    The passed-waiting list is an intrusive data structure. Hence a method
    clear_and_delete() that deletes all the nodes stored in the structure is
    provided to safely clear the list.

    This generic passed-waiting list is parametrized by a passed list (P) and
    a waiting list (W) that allow to implement different strategies for
    passed nodes and waiting nodes.

    \tparam NODE : type of nodes. The passed-waiting list manipulates pointers
    on NODE. It must inherit from pw_node_t.
    \tparam P : type of passed list (see graph::passed_t), must handle nodes of
    type NODE
    \tparam W : type of waiting list (see graph::waiting_t), must handle nodes
    of type NODE
  */
  template <class NODE, class P, class W>
  class pw_generic_t : protected P, protected W {

    /* static_assert( std::is_base_of(pw_node_t, NODE) ); */

  public:
    /*!
      \brief Constructor
      \param leq : predicate on nodes for checking node covering on insertion
    */
    pw_generic_t(graph::nodes_binpred_t<NODE> const & leq) : _leq(leq) {
    }


    /*!
      \brief Destructor
    */
    virtual ~pw_generic_t() = default;


    /*!
      \brief Clears the passed-waiting list and deletes all nodes
      \post All the nodes in the passed-waiting list have been deleted. The
      passed-waiting is empty.
     */
    virtual void clear_and_delete() {
      // Don't delete in W as nodes are shared with P
      this->W::clear();

      this->P::clear_and_delete();
    }


    /*!
      \brief Emptiness predicate
      \return True if the passed-waiting list is empty, false otherwise
    */
    virtual bool empty() const {
      return ( this->W::empty() && (this->P::size() == 0) );
    }


    /*!
      \brief Inserts a node in the passed-waiting list
      \param node : node to insert
      \param covering_node : node in the passed-waiting list that covers node
      (if any)
      \param covered_nodes : nodes from the passed-waiting list that are
      covered by node (if any)
      \return True if node has been inserted, false otherwise
      \post If node has been inserted, then covering = nullptr and all the
      nodes covered by node have been removed from the passed-waiting list and
      added to covered_nodes. The caller is expected to handle those nodes
      (delete, etc). If node has not been inserted, then covering_node points
      to a node in the passed-waiting list that covers node and no node has
      been added to covered_nodes
    */    
    virtual bool insert(NODE * node, NODE * & covering_node,
			std::vector<NODE *> & covered_nodes) {
      // Initialization
      covering_node = nullptr;

      // Gets nodes that can compare to node
      typename P::node_range_t * node_range = this->P::range(node);

      // No such node, then simply insert node
      if (node_range == nullptr) {

	this->W::insert(node);
	this->P::insert(node);
	return true;
      }

      // Otherwise, checks if node is covered (wrt _leq)
      for (NODE * n : *node_range) {
	if (this->_leq(node, n)) { // node is covered by n
	  assert(node != n);
	  covering_node = n;
	  return false;
	}
      }

      // node is not covered, collect all nodes that node is covering (wrt _leq)
      typename P::node_range_iterator it = node_range->begin();
      while (it != node_range->end()) {
	NODE * n = *it;

	if (this->_leq(n, node)) { // node is covering n
	  assert(node != n);

	  if (this->W::find(n)) // constant time check
	    this->W::erase(n);

	  it = this->P::erase(*node_range, it);

	  covered_nodes.push_back(n);
	}
	else  // node is not covering n, continue with the next one in range
	  ++it;
      }

      // Inserts node
      this->W::insert(node);

      this->P::insert(node, *node_range);

      return true;
    }


    virtual bool insert_function(NODE * node, NODE * & covering_node,
                        std::vector<NODE *> & covered_nodes, std::function<void(NODE *)> f) {
      // Initialization
      covering_node = nullptr;

      // Gets nodes that can compare to node
      typename P::node_range_t * node_range = this->P::range(node);

      // No such node, then simply insert node
      if (node_range == nullptr) {

	this->W::insert(node);
	this->P::insert(node);
	f(node);

	return true;
      }

      // Otherwise, checks if node is covered (wrt _leq)
      for (NODE * n : *node_range) {
        if (this->_leq(node, n)) { // node is covered by n
          assert(node != n);

          covering_node = n;
          return false;
        }
      }

      f(node);
      // node is not covered, collect all nodes that node is covering (wrt _leq)
      typename P::node_range_iterator it = node_range->begin();
      while (it != node_range->end()) {
        NODE * n = *it;
	if (this->_leq(n, node)) { // node is covering n
	  assert(node != n);
	  if (this->W::find(n)) // constant time check
	    this->W::erase(n);

	  it = this->P::erase(*node_range, it);

	  covered_nodes.push_back(n);
	}
	else  // node is not covering n, continue with the next one in range
	  ++it;
      }

      // Inserts node
      this->W::insert(node);
      this->P::insert(node, *node_range);

      return true;
    }

    virtual bool insert_passed(NODE * node, NODE * & covering_node,
                        std::vector<NODE *> & covered_nodes) {


      // Initialization
      covering_node = nullptr;

      // Gets nodes that can compare to node
      typename P::node_range_t * node_range = this->P::range(node);
      // No such node, then simply insert node
      if (node_range == nullptr) {
        this->P::insert(node);
        return true;
      }
      // Otherwise, checks if node is covered (wrt _leq)
      for (NODE * n : *node_range) {
        if (this->_leq(node, n)) { // node is covered by n
          assert(node != n);
          covering_node = n;
          return false;
        }
      }

      // node is not covered, collect all nodes that node is covering (wrt _leq)
      typename P::node_range_iterator it = node_range->begin();
      while (it != node_range->end()) {
        NODE * n = *it;

	if (this->_leq(n, node)) { // node is covering n
	  assert(node != n);

	  if (this->W::find(n)) // constant time check
	    this->W::erase(n);

	  it = this->P::erase(*node_range, it);

	  covered_nodes.push_back(n);
	}
	else  // node is not covering n, continue with the next one in range
	  ++it;
      }

      // Inserts node
      this->P::insert(node, *node_range);

      return true;
    }
    virtual bool insert_passed_function(NODE * node, NODE * & covering_node,
                        std::vector<NODE *> & covered_nodes,  std::function<void(NODE *)> f) {


      // Initialization
      covering_node = nullptr;

      // Gets nodes that can compare to node
      typename P::node_range_t * node_range = this->P::range(node);

      // No such node, then simply insert node
      if (node_range == nullptr) {
        this->P::insert(node);
        f(node);
        return true;
      }

      // Otherwise, checks if node is covered (wrt _leq)
      for (NODE * n : *node_range) {
        if (this->_leq(node, n)) { // node is covered by n
          assert(node != n);
          covering_node = n;
          return false;
        }
      }
      f(node);
      // node is not covered, collect all nodes that node is covering (wrt _leq)
      typename P::node_range_iterator it = node_range->begin();
      while (it != node_range->end()) {
        NODE * n = *it;

	if (this->_leq(n, node)) { // node is covering n
	  assert(node != n);

	  if (this->W::find(n)) // constant time check
	    this->W::erase(n);

	  it = this->P::erase(*node_range, it);

	  covered_nodes.push_back(n);
	}
	else  // node is not covering n, continue with the next one in range
	  ++it;
      }

      // Inserts node
      this->P::insert(node, *node_range);

      return true;
    }
    virtual bool remove(NODE * node) {



        if (this->P::find(node)) {

        this->P::erase(node);

        if (this->W::find(node)) // constant time check
           this->W::erase(node);
        return true;}
     else return false;
    }

    /*!
      \brief Covering check
      \param node : node to check for covering
      \param covering : covering node (if any)
      \param leq : covering predicate
      \return True if node is covered by some node in the structure wrt to
      leq, false otherwise
      \post If node is covered, then covering has been set to a covering node,
      otherwise, covering is meaningless
    */
    virtual bool cover(NODE * node, NODE * & covering,
		       graph::nodes_binpred_t<NODE> const & leq) const {
      return this->P::cover(node, covering, leq);
    }


    /*!
      \brief Outputs stats on the structure
      \param os : output stream
      \param level : stats level
      \post Statistics on the list of passed nodes of level at most 'level'
      have been output to os
     */
    virtual void stats(std::ostream & os, unsigned level) {
      this->P::stats(os, level);
    }


    /*!
      \brief Inserts a node in the waiting list only

      Notice that node is only inserted in the waiting list, not in the passed
      list

      \param node : node to insert
      \pre node is not already in the waiting list (checked by assertion)
      \post node has been inserted in the waiting list
    */
    virtual void winsert(NODE * node) {
      assert( ! this->W::find(node) );
      this->W::insert(node);
    }
    
    
    /*!
      \brief Emptiness predicate on the waiting list
      \return True if the list of waiting nodes is empty, false otherwise
    */
    virtual bool wempty() const {
      return this->W::empty();
    }


    /*!
      \brief Accessor to the first waiting node that pops the node out of the
      waiting list
      \return The first node in the waiting list if not empty
      \pre The waiting list is not empty
      \post The first waiting node has been removed from the waiting list
    */    
    virtual NODE * wnext() {
      return this->W::next();
    }


    /*!
      \brief Predicate that tells if a node is in the waiting list
      \param node : node to find
      \return True if node is in the waiting list, false otherwise
      \post The membership test is done in O(1)
     */
    virtual bool wfind(NODE * node) const {
      return this->W::find(node);
    }


    /*!
      \brief Predicate that tells if a node is in the passed list
      \param node : node to find
      \return True if node is in the passed list, false otherwise
      \post The membership test is done in O(1)
     */
    virtual bool pfind(NODE * node) const {
      return this->P::find(node);
    }


    /*!
      \brief Accessor to the size of the passed list
      \return The number of passed nodes
    */
    virtual size_t psize() const {
      return this->P::size();
    }


    /*!
      \brief Type of iterators over the passed list
    */
    typedef typename P::iterator piterator;


    /*!
      \brief Iterator on the passed list
      \return Reference to first node in the passed list if any, or the
      passed-the-end value otherwise
      \warning Iterators should not be used to alter the passed list, nor the
      nodes in the passed list. Theyr should only be used to inspect the list
    */
    piterator pbegin() {
      return this->P::begin();
    }


    /*!
      \brief Iterator on the passed list
      \return Reference the passed-the-end value of the passed list
      \warning Iterators should not be used to alter the passed list, nor the
      nodes in the passed list. Theyr should only be used to inspect the list
    */
    piterator pend() {
      return this->P::end();
    }
  protected:
    /*!< Covering predicate on nodes */
    graph::nodes_binpred_t<NODE> const & _leq;
  };




  /* List of passed nodes */

  /*!
    \class passed_t
    \brief List of passed nodes implemented by a map (key,list) were key
    is computed from nodes (using HASH and EQUAL) and list contains all the
    nodes with the same key
    \tparam NODE : type of nodes stored in the structure. NODE must derive
    from p_node_t
    \taparm KEY : type of keys
    \tparam NODE_TO_KEY : computation of a node's key. Must derive from
    std::unary_function<NODE const &, KEY>. Must have a default constructor
    \tparam HASH : hash function on KEY
    \taparm EQUAL : equality predicate on KEY
   */
  template < class NODE,
	     class KEY,
	     class NODE_TO_KEY,
	     class HASH = boost::hash<KEY>,
	     class EQUAL = std::equal_to<KEY> >
  class passed_t {

    /* static_assert( std::is_base_of(p_node_t, NODE) ); */
    /* static_assert( std::is_base_of(unary_function<NODE const &, KEY>,
                                      NODE_TO_KEY) ); */

  public:
    /*!
      \brief Type of the passed map
     */
    typedef typename boost::unordered_map< KEY,
					   intrusive_list_t< NODE, ptag > *,
					   HASH,
					   EQUAL > passed_map_t;

    /*!
      \brief Type of a node's range
     */
    typedef intrusive_list_t<NODE, ptag> node_range_t;

    /*!
      \brief Type of a node's range iterator
    */
    typedef typename intrusive_list_t<NODE, ptag>::iterator node_range_iterator;


    /*!
      \brief Constructor
    */
    passed_t() : _size(0) {
    }


    /*!
      \brief Destructor
      \post No destructors are called on nodes.
    */
    ~passed_t() {
      // Clear and delete the lists (node are not deleted)
      for (auto it : _passed) {
	it.second->clear();
	delete it.second;
      }
      _passed.clear();
    }


    /*!
      \brief Clears the passed list
      \post The passed list is empty. No destructors are called on nodes
     */
    void clear() {
      for (auto it : _passed) {
	it.second->clear();
	delete it.second;
      }
      _passed.clear();
      _size = 0;
    }


    /*!
      \brief Clears the passed list and delete the nodes
      \post All the nodes in the structure have been deleted. The passed list
      is empty
     */
    void clear_and_delete() {
      for (auto it : _passed) {

	it.second->clear_and_dispose( [] (NODE * n) { delete n; } );

	delete it.second;
      }

      _passed.clear();
      _size = 0;
    }


    /*!
      \brief Accessor to the list of nodes with the same key as node
      \param node : reference node
      \return The list of nodes in the passed list which have the same key
      as node. The returned value is nullptr if there is no such node
    */
    node_range_t * range(NODE * node) const {
      auto it = _passed.find( _node_to_key(*node) );
      
      // Return an empty list if node is not found
      if (it == _passed.end())
	return nullptr;
      
      return it->second;
    }


    /*!
      \brief Erases a node from the passed list
      \param node : node to erase
      \pre node is stored in the structure and its key has not be modified
      since it was inserted in the structure
      \post node has been erased from the passed list. No destructors are
      called.
      \throw std::logic_error : if node cannot be found in the structure
     */
    void erase(NODE * node) {
      // Gets the list of nodes with the same key as node
      auto it = _passed.find( _node_to_key(*node) );
      if (it == _passed.end())
	throw std::logic_error("*** passed_t::erase: node not stored");

      // Erases the node and updates the size
      it->second->erase(node);

      --_size;
    }


    /*!
      \brief Erases a node from the passed list and updates iterator
      \param range : node range which is iterated by it
      \param it : iterator pointing to the node to erase
      \return an iterator to the next node in the node range
      \pre it is an iterator over range. it can be dereferenced (not checked)
      \post the node referenced by it has been erased from range, hence from
      the passed list. No destructors are called.
      \throw std::logic_error : if the nod ereferenced by it cannot be found
      in the structure
     */
    node_range_iterator erase(node_range_t & range,
			      node_range_iterator const & it) {
      if ( ! range.find(*it) ) // constant time check
	throw std::logic_error("*** passed_t::erase: node not stored");

      // Erases the node and updates the size
      -- _size;
      return range.erase(it);
    }


    /*!
      \brief Inserts a node in the passed list
      \param node : node to insert
      \pre node is not already in the structure (not checked)
      \post node has been inserted in the structure
      \throw std::runtime_error if insertion failed
     */
    void insert(NODE * node) {
      auto it = _passed.find( _node_to_key(*node) );

      // Insert node in the right list (if any)
      if (it != _passed.end()) {
        assert(!it->second->find(node));
	insert(node, * it->second);
	return;
      }
      
      // Otherwise, inserts node in a new list and inserts the list
      intrusive_list_t<NODE, ptag> * l = new intrusive_list_t<NODE, ptag>();
      assert( l != nullptr );

      l->push_back(node);
      
      auto it_insert =
	_passed.insert( std::make_pair( _node_to_key(*node), l ) );

      if ( ! it_insert.second )
	throw std::runtime_error("*** passed_t::insert: failed");
      
      ++ _size; // increment only when insertion succeeds (don't use insert)
    }

    
    /*!
      \brief Inserts a node into a given node range in the passed list
      \param node : node to insert
      \param range : range to insert in
      \pre node is not already in the structure (not checked)
      \post node has been inserted in range
     */
    void insert(NODE * node, node_range_t & range) {
      range.push_back(node);
      ++ _size;
    }


    /*!
      \brief Checks if a node is in the passed list
      \param node : node to check
      \return True if node is in the passed list, false otherwise
      \post The check is done in O(1)
     */
    bool find(NODE * node) const {

      auto it = _passed.find( _node_to_key(*node) );

      if (it == _passed.end())
	return false;

      return it->second->find(node);
    }


    /*!
      \brief Node covering check
      \param node : node to check
      \param covering_node : covering node (if any)
      \param leq : covering predicate
      \return True if node is covered by some node in the structure wrt
      leq, false otherwise
      \post If node is covered, then covering_node is set to a covering node,
      otherwise, covering_node is meaningless
     */
    bool cover(NODE * node, NODE * & covering_node,
	       graph::nodes_binpred_t<NODE> const & leq) const {
      auto it = _passed.find( _node_to_key(*node) );
      
      // Not covered if no other node with same key
      if (it == _passed.end()) {
	covering_node = nullptr;
	return false;
      }

      // Otherwise, compare the nodes with same key
      for (NODE * n : * it->second) {
	if (leq(node, n)) {
	  assert( node != n );
	  covering_node = n;
	  return true;
	}
      }
      
      // Node is not covered
      covering_node = nullptr;
      return false;
    }


    /*!
      \brief Accessor
      \return Size of the structure (number of stored nodes)
    */
    const size_t size() const {
      return _size;
    }


    /*!
      \brief Outputs stats on the structure
      \param os : output stream
      \param level : stats level
      \post Statistics on the passed list of at most level 'level'
      have been output to os
    */
    void stats(std::ostream & os, unsigned level) {
      // Level 0
      os << stats::PW_SIZE << _size
	 << std::endl;

      // Level 1
      if (level < 1)
	return;

      os << stats::PW_KEYS_TOTAL << _passed.size()
	 << std::endl;

      // Level 2
      if (level < 2)
	return;

      // Stats on nodes' list
      stats::sample_analyzer_t<unsigned> acc;
      for (auto it = _passed.begin(); it != _passed.end(); ++it)
	acc( it->second->size() ); // accumulate lists size

      os << stats::PW_LSIZE_MIN << boost::accumulators::min(acc) << std::endl
	 << stats::PW_LSIZE_MAX << boost::accumulators::max(acc) << std::endl
	 << stats::PW_LSIZE_AVG << boost::accumulators::mean(acc)
	 << std::endl;

      boost::accumulators::impl::frequency_accumulator<unsigned>::result_type
	d = boost::accumulators::frequency(acc);
      for (std::pair<unsigned, unsigned> const & p : d)
	os << stats::PW_LSIZE_FREQ << p.first << " : " << p.second
	   << std::endl;
    }


    /*!
      \class iterator
      \brief Iterator over a passed list
     */
    class iterator : public std::iterator<std::forward_iterator_tag, NODE *> {
    public:
      /*!
	\brief Constructor
	\param map_it : iterator position
	\param map_end : iterator to the passed-the-end value of the passed
	list
	\post this refers to the first node from map_it in the passed list
	if any, or to the passed-the-end value otherwise
       */
      iterator(typename passed_map_t::iterator map_it,
	       typename passed_map_t::iterator map_end) : _map_it(map_it),
							  _map_end(map_end) {
	// Jumps over empty lists
	while ( (_map_it != _map_end) &&
		(_map_it->second->begin() == _map_it->second->end()) )
	  ++_map_it;
	
	// _list_it is left uninitialized if map_it refers to the passed-the-end
	// value which is consistent with all operator below
	if (_map_it != _map_end)
	  _list_it = _map_it->second->begin();
      }


      /*!
	\brief Copy constructor
	\param it : iterator to copy
	\post this is a copy of if
      */
      iterator(iterator const & it) : _map_it(it._map_it),
				      _list_it(it._list_it) {
      }

      /*!
	\brief Assignement operator
	\param it : operator to assign from
	\post this is a copy of it
       */
      iterator & operator = (iterator const & it) {
	if (this != &it) {
	  _map_it = it._map_it;
	  _list_it = it._list_it;
	}
	return (*this);
      }

      /*!
	\brief Jumps to next node in the passed list
	\return An iterator to the next node if any
	\pre this does not point to the passed-the-end value (not checked)
	\post this has been updated to point to the next node if any, or to
	the passed-the-end value otherwise
      */
      iterator & operator ++ () {
	// Goes to next node in current list
	++_list_it;

	// If no such element
	if (_list_it == _map_it->second->end()) {
	  // Jumps over next empty lists
	  do {
	    ++_map_it;
	  }
	  while ( (_map_it != _map_end) &&
		  (_map_it->second->begin() == _map_it->second->end()) );

	  // If found a non-empty list, start from its first node
	  if (_map_it != _map_end)
	    _list_it = _map_it->second->begin();
	}

	return (*this);
      }

      /*!
	\brief Equality predicate
	\param it : iterator to compare to
	\return True if this is equal to it, false otherwise
       */
      bool operator == (iterator const & it) const {
	return ( (_map_it == it._map_it) && ( (_map_it == _map_end) ||
					      (_list_it == it._list_it) ) );
      }

      /*!
	\brief Disequality predicate
	\param it : iterator to compare to
	\return True if this is different from it, false otherwise
       */
      bool operator != (iterator const & it) const {
	return ( ! (*this == it) );
      }

      /*!
	\brief Access to current node
	\return Current node
	\pre this does not point to the passed-the-end value (not checked)
       */
      NODE const * operator * () const {
	return (* _list_it);
      }      
    private:
      /*!< Iterator in the map */
      typename passed_map_t::iterator _map_it;
      /*!< Iterator to the end of the map */
      typename passed_map_t::iterator _map_end;
      /*!< Iterator in current list in the map */
      typename node_range_t::iterator _list_it;
    };

    /*!
      \brief Iterator
      \return Reference to first node in the passed list if any, or the
      passed-the-end value otherwise
    */
    iterator begin() {
      return iterator(_passed.begin(), _passed.end());
    }

    /*!
      \brief Iterator
      \return Reference to the passed-the-end value
     */
    iterator end() {
      return iterator(_passed.end(), _passed.end());
    }
  protected:
    /*!< Set of passed nodes */
    boost::unordered_map< KEY,
			  intrusive_list_t< NODE, ptag > *,
			  HASH,
			  EQUAL > _passed;

    /*!< Size of the structure (number of stored nodes) */
    size_t _size;

    /*!< Computation of keys from nodes */
    NODE_TO_KEY _node_to_key;
  };



  // Specialisation to syntax::state_t based nodes 

  /*!
    \class syntax_state_node_to_key_t
    \tparam NODE : type of nodes. It must derive from syntax::state_t
    \brief Generates a key from a node, which is the hash code of underlying
    syntax::state_t
  */
  template <class NODE>
  class syntax_state_node_to_key_t
    : public std::unary_function<NODE const &, size_t> {

    /* static_assert( std::is_base_of(syntax::state_t, NODE) ); */

  public:
    /*!
      \brief Key computation
      \param n : node to consider
      \return The key of node n, that is, the hash code of underlying
      syntax::state_t
     */
    size_t operator() (NODE const & n) const {
      return n.syntax::state_t::hash();
    }
  };



  /*!
    \class syntax_state_node_hash_t
    \brief Hasher for syntax::state_t keys (identity function)
   */
  class syntax_state_node_hash_t
    : public std::unary_function<size_t, size_t> {
  public:
    /*!
      \brief Hash operator
      \param k : key to hash
      \return The key itself
     */
    size_t operator () (size_t const & k) const {
      return k;
    }
  };


  /* IMPLEMENTATION NOTE: we use the hash code of underlying syntax::state_t
     as a KEY. Distinct syntax::state_t may lead to collision, that is, they
     may have the same hash code. However, the KEY is used to restrict the set
     of nodes that have to be considered when searching for a given node. The
     node comparator that is used for searching should check that the nodes
     under comparison have the same syntax::state_t
  */


  /*!
    \class syntax_state_passed_t
    \brief Specialization of graph::passed_t to syntax::state_t keys
    \tparam NODE : type of nodes stored in the passed node structure
   */
  template <class NODE>
  class syntax_state_node_passed_t
    : public passed_t<NODE,
		      size_t,
		      syntax_state_node_to_key_t<NODE>,
		      syntax_state_node_hash_t> {
  };




  /* List of waiting nodes */

  /*!
    \class waiting_t
    \brief List of waiting nodes. Implementation as an intrusive list. Nodes
    are always taken from the head of the list. Different waiting policies
    can be implemented depending on how node are inserted (see _insert)
    \tparam NODE : type of stored nodes. It should derive from w_node_t
   */
  template <class NODE>
  class waiting_t {

    /* static_assert( std::is_base_of(w_node_t, NODE) ); */

  public:
    /*!
      \brief Destructor
    */
    virtual ~waiting_t() = default;


    /*!
      \brief Clears the waiting list
      \post The waiting list is empty. No destructors are called on nodes.
     */
    void clear() {
      _w.clear();
    }


    /*!
      \brief Checks if a node is in the waiting list
      \param node : node to check
      \return True if node is in the waiting list, false otherwise
     */
    bool find(NODE * node) const {
      return _w.find(node);
    }


    /*!
      \brief Insert node
      \param node : node to insert
    */
    void insert(NODE * node) {
      _insert(node);
    }


    /*!
      \brief Erase a node
      \param node : node to erase
      \post node has been erased from the waiting list. No destructors are
      called.
     */
    void erase(NODE * node) {
      assert( find(node) );
      _w.erase(node);
    }


    /*!
      \brief Replace a node by another node
      \param node_to_replace : node to replace
      \param node : node to insert in replacement
      \pre node is in the waiting list
      \post node_to_replace has been replaced by node in the waiting list.
      No destructors are called.
     */
    void replace(NODE * node_to_replace, NODE * node) {
      assert( find(node_to_replace) );
      _replace(node_to_replace, node);
    }


    /*!
      \brief Emptiness predicate
      \return True is the waiting list is empty, false otherwise
     */
    bool empty() const {
      return _w.empty();
    }


    /*!
      \brief Accessor to the first node in the waiting list that pops the
      node out of the list
      \return The first node in the waiting list (if any)
      \pre The list is not empty (checked by assertion)
      \post The node at the head of the list has been removed
     */
    NODE * next() {
      assert( ! _w.empty() );
      return _next();
    }
  protected:
    /*!
      \brief see waiting_t::insert
      \note The waiting policy is defined by _insert and _next. By default, the
      nodes are always taken at the haed of the list (see next())
    */
    virtual void _insert(NODE * node) = 0;

    /*!
      \brief see waiting_t::replace
      \warning Replacing a node by another should follow the overal policy of
      the waiting list (see _insert())
    */
    virtual void _replace(NODE * node_to_replace, NODE * node) {
      _w.replace(node_to_replace, node);
    }

    /*!
      \brief see waiting_t::next
     */
    virtual NODE * _next() {
      NODE * n = _w.front();
      _w.pop_front();
      return n;
    }

    /*!< List of waiting nodes */
    intrusive_list_t< NODE, wtag > _w;
  };




  /* Specializations of the passed-waiting list */


  /*!
    \class pw_t
    \brief Passed-waiting list of nodes

    This is a specialization of pw_generic_t using syntax_state_node_passed_t
    (see above) and waiting_t (see above). The insertion policy (method
    _insert from waiting_t) is not defined here. The class should be specialized
    for every policy needed.
    
    \tparam NODE : type of nodes. The passed-waiting list manipulates pointers
    on nodes. NODE must inherit from pw_node_t.
  */
  template <class NODE>
  class pw_t : public pw_generic_t< NODE,
				    syntax_state_node_passed_t<NODE>,
				    waiting_t<NODE> > {
  public:
    /*!
      \brief Constructor (see pw_generic_t::pw_generic_t)
    */
    pw_t(graph::nodes_binpred_t<NODE> const & leq)
      : pw_generic_t< NODE,
		      syntax_state_node_passed_t<NODE>,
		      waiting_t<NODE> >(leq) {
    }


    /*!
      \brief Destructor
    */
    virtual ~pw_t() = default;
  };



  /*!
    \class fifo_pw_t
    \brief Passed-waiting list with FIFO policy on waiting nodes
    \tparam NODE : type of nodes stored in the list
   */
  template <class NODE>
  class fifo_pw_t : public pw_t<NODE> {
  public:
    /*!
      \brief Constructor (see pw_t::pw_t)
    */
    fifo_pw_t(graph::nodes_binpred_t<NODE> const & leq) : pw_t<NODE>(leq) {
    }

    /*!
      \brief Destructor
    */
    virtual ~fifo_pw_t() = default;
  protected:
    /*!
      \brief Insert node (see waiting_t::_insert)
      \param node : node to insert
      \pre node is not in the list already (checked by assertion)
      \post node has been inserted at the end of the list which yields
      a FIFO policy as nodes are taken from the head
    */
    virtual void _insert(NODE * node) {
      assert( ! this->wfind(node) );
      this->_w.push_back(node);
    }

    // IMPLEMENTATION NOTE: default methods _replace and _next are consistent
    // with FIFO policy
  };



  /*!
    \class lifo_pw_t
    \brief Passed-waiting list with LIFO policy on waiting nodes
    \tparam NODE : type of nodes stored in the list
   */
  template <class NODE>
  class lifo_pw_t : public pw_t<NODE> {
  public:
    /*!
      \brief Constructor (see pw_t::pw_t)
    */
    lifo_pw_t(graph::nodes_binpred_t<NODE> const & leq) : pw_t<NODE>(leq) {
    }

    /*!
      \brief Destructor
    */
    virtual ~lifo_pw_t() = default;
  protected:
    /*!
      \brief Insert node (see waiting_t::_insert)
      \param node : node to insert
      \pre node is not in the list already (checked by assertion)
      \post node has been inserted at the head of the list which yields
      a LIFO policy as nodes are taken from the head
    */
    virtual void _insert(NODE * node) {
      assert( ! this->wfind(node) );
      this->_w.push_front(node);
    }

    // IMPLEMENTATION NOTE: default methods _replace and _next are consistent
    // with LIFO policy
  };



  /*!
    \class increasing_pw_t
    \brief Passed-waiting list with waiting nodes sorted in increasing order
    \tparam NODE : type of nodes stored in the list
   */
  template <class NODE>
  class increasing_pw_t : public pw_t<NODE> {
  public:
    /*!
      \brief Constructor (see pw_t::pw_t)
      \param lt : less-than predicate on nodes for sorting the waiting list
      \post this stores a reference on lt
     */
    increasing_pw_t(graph::nodes_binpred_t<NODE> const & leq,
		    graph::nodes_binpred_t<NODE> const & lt)
      : pw_t<NODE>(leq), _lt(lt) {
    }

    /*!
      \brief Destructor
    */
    virtual ~increasing_pw_t() = default;
  protected:
    /*!
      \brief Insert node (see waiting::_insert)
      \param node : node to insert
      \pre node is not in the list already (checked by assertion) and the
      list is sorted in increasing order wrt given predicate lt (not checked)
      \post node has been inserted in the list in such a way that it is
      sorted in increasing order wrt given predicate lt
      \throw std::logic_error : if the list appears to not be sorted (may not
      detect all cases)
    */
    virtual void _insert(NODE * node) {
      assert( ! this->wfind(node) );

      if ( this->_w.empty() || _lt(node, this->_w.front()) ) // Insert first?
	this->_w.push_front(node);
      else if ( _lt(this->_w.back(), node) ) // Insert last?
	this->_w.push_back(node);
      else { // Insert at the right place
	auto it = ++ this->_w.begin();
	while ( (it != this->_w.end()) && _lt(*it, node) )
	  ++it;

	if (it == this->_w.end()) // Sanity check
	  throw std::logic_error
	    ("*** increasing_waiting_t::_insert: not sorted");

	this->_w.insert(it, node);
      }
    }


    /*!
      \brief see waiting_t::replace
      \post node_to_replace has been removed and node has been inserted in
      such a way that the waiting list is sorted in increasing order wrt
      given predicate lt. No destructors are called.
    */
    virtual void _replace(NODE * node_to_replace, NODE * node) {
      this->_w.erase(node_to_replace);
      this->_insert(node);
    }

    /*<! Sorting predicate (less-than) */
    graph::nodes_binpred_t<NODE> const & _lt;
  };




  /*!
    \class decreasing_pw_t
    \brief Passed-waiting list with waiting nodes sorted in decreasing order
    \tparam NODE : type of nodes stored in the list
   */

  template <class NODE>
  class decreasing_pw_t : public pw_t<NODE> {
  public:
    /*!
      \brief Constructor (see pw_t::pw_t)
      \param lt : less-than predicate on nodes for sorting the waiting list
      \post this stores a reference on lt
     */
    decreasing_pw_t(graph::nodes_binpred_t<NODE> const & leq,
		    graph::nodes_binpred_t<NODE> const & lt)
      : pw_t<NODE>(leq), _lt(lt) {
    }

    /*!
      \brief Destructor
    */

    virtual ~decreasing_pw_t() = default;    
  protected:
    /*!
      \brief Insert node (see waiting::_insert)
      \param node : node to insert
      \pre node is not in the list already (checked by assertion) and the
      list is sorted in decreasing order wrt given predicate lt (not checked)
      \post node has been inserted in the list in such a way that it is
      sorted in decreasing order wrt given predicate lt
      \throw std::logic_error : if the list appears to not be sorted (may not
      detect all cases)
    */
    virtual void _insert(NODE * node) {
      assert( ! this->wfind(node) );

      if ( this->_w.empty() || _lt(this->_w.front(), node) ) // Insert first?
	this->_w.push_front(node);
      else if ( _lt(node, this->_w.back()) ) // Insert last?
	this->_w.push_back(node);
      else { // Insert at the right place
	auto it = ++ this->_w.begin();
	while ( (it != this->_w.end()) && _lt(node, *it) )
	  ++it;

	if (it == this->_w.end()) // Sanity check
	  throw std::logic_error
	    ("*** decreasing_waiting_t::_insert: not sorted");

	this->_w.insert(it, node);
      }
    }


    /*!
      \brief see waiting_t::replace
      \post node_to_replace has been removed and node has been inserted in
      such a way that the waiting list is sorted in decreasing order wrt
      given predicate lt. No destructors are called.
    */
    virtual void _replace(NODE * node_to_replace, NODE * node) {
      this->_w.erase(node_to_replace);
      this->_insert(node);
    }

    /*<! Sorting predicate (less-than) */
    graph::nodes_binpred_t<NODE> const & _lt;
  };



  /*!
    \class bzfifo_pw_t
    \brief Passed-waiting list with FIFO + biggest-zone-first policy on waiting
    nodes
    \tparam NODE : type of nodes stored in the list
   */
  template <class NODE>
  class bzfifo_pw_t : public fifo_pw_t<NODE> {
  public:
    /*!
      \brief Constructor (see pw_t::pw_t)
    */
    bzfifo_pw_t(graph::nodes_binpred_t<NODE> const & leq)
      : fifo_pw_t<NODE>(leq) {
    }

    /*!
      \brief Destructor
    */
    virtual ~bzfifo_pw_t() = default;
  protected:
    /*!
      \brief Accessor to the next waiting node (see waiting_t::_next)
      \return The first node wrt FIFO order with a zone that is maximal wrt all 
      other waiting nodes
      \pre the waiting list is not empty (not checked)
     */
    virtual NODE * _next() {
      auto it_max = this->_w.begin();

      for (auto it = this->_w.begin(); it != this->_w.end(); ++it)
	if ( graph::nodes_zone_leq<NODE>(*it_max, *it) &&
	     ( ! graph::nodes_zone_eq<NODE>(*it_max, *it) ) )
	  it_max = it;

      NODE * n = *it_max;
      this->_w.erase(it_max);
      return n;
    }

    // IMPLEMENTATION NOTE: methods _insert and _replace from fifo_pw_t are
    // consistent with FIFO + Biggest-zone-first policy
  };



  /*!
    \class bzlifo_pw_t
    \brief Passed-waiting list with LIFO + biggest-zone-first policy on waiting
    nodes
    \tparam NODE : type of nodes stored in the list
   */
  template <class NODE>
  class bzlifo_pw_t : public lifo_pw_t<NODE> {
  public:
    /*!
      \brief Constructor (see pw_t::pw_t)
    */
    bzlifo_pw_t(graph::nodes_binpred_t<NODE> const & leq)
      : lifo_pw_t<NODE>(leq) {
    }

    /*!
      \brief Destructor
    */
    virtual ~bzlifo_pw_t() = default;
  protected:
    /*!
      \brief Accessor to the next waiting node (see waiting_t::_next)
      \return The first node wrt LIFO order with a zone that is maximal wrt all 
      other waiting nodes
      \pre the waiting list is not empty (not checked)
     */
    virtual NODE * _next() {
      auto it_max = this->_w.begin();

      for (auto it = this->_w.begin(); it != this->_w.end(); ++it)
	if ( graph::nodes_zone_leq<NODE>(*it_max, *it) &&
	     ( ! graph::nodes_zone_eq<NODE>(*it_max, *it) ) )
	  it_max = it;

      NODE * n = *it_max;
      this->_w.erase(it_max);
      return n;
    }

    // IMPLEMENTATION NOTE: methods _insert and _replace from lifo_pw_t are
    // consistent with LIFO + Biggest-zone-first policy
  };




  /* Passed-waiting list factory */

  /*!
    \brief Setup flags for passed-waiting lists
   */
  typedef char pw_flags_t;

  const pw_flags_t PW_FIFO   = 0; /*!< FIFO passed-waiting list */
  const pw_flags_t PW_LIFO   = 1; /*!< LIFO passed-waiting list */
  const pw_flags_t PW_INC    = 2; /*!< Increasing passed-waiting list */
  const pw_flags_t PW_DEC    = 3; /*!< Decreasing passed-waiting list */
  const pw_flags_t PW_BZFIFO = 4; /*!< FIFO + biggest-zone first PW list */
  const pw_flags_t PW_BZLIFO = 5; /*!< FIFO + biggest-zone first PW list */

  /*!< Default passed-waiting list (FIFO) */
  const pw_flags_t PW_DEFAULT = PW_FIFO;


  /*!
    \class pw_factory_t
    \brief Passed-waiting list factory.

    NB: IT ONLY BUILDS syntax::state_t BASED PASSED-WAITING LISTS
  */
  class pw_factory_t : public singleton_t< pw_factory_t > {

    /* static_assert( NODE derives from syntax::state_t ) */

    friend class singleton_t< pw_factory_t >;  // Grants access to cons/Des

  public:
    /*!
      \brief Builds a new passed-waiting list (except sorted waiting lists)
      \tparam NODE : type of nodes. Should derive from syntax::state_t
      \param leq : see graph::pw_t
      \param flags : type of passed-waiting list to build
      \return A new passed waiting list made from leq. It has the type required 
      by flags
      \throw std::logic_error : if flags is invalid
     */
    template <class NODE>
    pw_t<NODE> * new_pw(graph::nodes_binpred_t<NODE> const & leq,
			pw_flags_t flags = PW_DEFAULT) {
      /* static_assert( std::is_base_of(syntax::state_t, NODE) ); */

      pw_t<NODE> * pw;

      switch (flags) {
      case PW_FIFO:
	pw  = new fifo_pw_t<NODE>(leq);
	break;
      case PW_LIFO:
	pw  = new lifo_pw_t<NODE>(leq);
	break;
      case PW_BZFIFO:
	pw = new bzfifo_pw_t<NODE>(leq);
	break;
      case PW_BZLIFO:
	pw = new bzlifo_pw_t<NODE>(leq);
	break;
      default:
	throw std::logic_error("*** graph::pw_factory_t: invalid flags");
      }
      
      return pw;
    }


    /*!
      \brief Builds a new passed-waiting list (including sorted waiting list)
      \tparam NODE : type of nodes. Should derive from syntax::state_t
      \param leq : see graph::pw_t
      \param lt : less-than predicate on nodes for sorting the waiting list
      \param flags : type of passed-waiting list to build
      \return A new passed waiting list made from leq and lt. It has the type
      required by flags
      \throw std::logic_error : if flags is invalid
     */
    template <class NODE>
    pw_t<NODE> * new_pw(graph::nodes_binpred_t<NODE> const & leq,
			graph::nodes_binpred_t<NODE> const & lt,
			pw_flags_t flags = PW_DEFAULT) {
      /* static_assert( std::is_base_of(syntax::state_t, NODE) ); */

      pw_t<NODE> * pw;

      switch (flags) {
      case PW_INC:
	pw = new increasing_pw_t<NODE>(leq, lt);
	break;
      case PW_DEC:
	pw = new decreasing_pw_t<NODE>(leq, lt);
	break;
      default:
	pw = new_pw<NODE>(leq, flags);
	break;
      }
      
      return pw;
    }
  private:
    /*!
      \brief Constructor (made private)
    */
    pw_factory_t() = default;

    /*!
      \brief Destructor (made private)
    */
    ~pw_factory_t() = default;
  };

} // end of namespace graph

#endif // __TCHECKER_PW_HH__
