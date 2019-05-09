#ifndef __TCHECKER_INTRUSIVE_LIST__
#define __TCHECKER_INTRUSIVE_LIST__

#include <ostream>
#include <stdexcept>

#include "base/cast.hh"

/*!
  \file intrusive_list.hh
  \brief Intrusive list
*/



/* Hooks */

/*!
  \struct default_tag
  \brief Default hook tag
 */
struct default_tag {
};


/*!
  \class intrusive_list_hook_t
  \brief Hook for using intrusive_list_t

  Objects need to inherit from intrusive_list_hook_t in order to be stored
  in intrusive_list_t. An object can be stored in several lists at the same
  time using different tags.

  \tparam TAG : hook tag
*/
template <class TAG = default_tag>
class intrusive_list_hook_t : public TAG {
public:
  /*!
    \brief Constructor
    \post The instance is not linked
  */
  intrusive_list_hook_t() : pred(nullptr), next(nullptr) {
  }

  /*!
    \brief Copy-constructor
    \param h : hook to build from
    \post The instance has the same links as h
  */
  intrusive_list_hook_t(intrusive_list_hook_t const & h) : pred(h.pred),
							   next(h.next) {
  }

  /*!
    \brief Assignment operator
    \param h : hook to assign from
    \return The instance after assignement
    \post The instance has the same links as h    
   */
  intrusive_list_hook_t & operator = (intrusive_list_hook_t const & h) {
    if (this != &h) {
      pred = h.pred;
      next = h.next;
    }
    return *this;
  }

  /*!
    \brief Swap hooks
    \param h : hook to swap
    \post The links of h have been swapped with the instance's links
  */
  void swap(intrusive_list_hook_t & h) {
    intrusive_list_hook_t<TAG> * tmp = pred;
    pred = h.pred;
    h.pred = tmp;

    tmp = next;
    next = h.next;
    h.next = tmp;
  }

  /*!
    \brief Linked predicate
    \return True if the instance is linked, false otherwise
  */
  bool linked() const {
    return ( (pred != nullptr) || (next != nullptr) );
  }

  /*!
    \brief Unlink operation
    \post The instance is not linked
  */
  void unlink() {
    pred = nullptr;
    next = nullptr;
  }

  intrusive_list_hook_t<TAG> * pred;   /*!< Link to the pred hook */
  intrusive_list_hook_t<TAG> * next;   /*!< Link to the next hook */
};



/* List */


/*!
  \class intrusive_list_t
  \brief Intrusive list

  IMPLEMENTATION NOTE: hooks are not allocated nor deleted by the list.
  Methods with disposers are provided to allow deleting elements (or whatever
  makes sense) in erasing functions. A disposer is an object that implements
  an operator (for some type T):
                     void operator() (T * t) const;

  \tparam T : type of pointed values
  \tparam TAG : tag on hooks used by the list
  \pre T must derive from intrusive_list_hook_t<TAG>
 */
template <class T, class TAG = default_tag>
class intrusive_list_t {
public:
  /*!
    \class iterator
    \brief Iterator on intrusive list
  */
  class iterator {
  public:
    /*!
      \brief Constructor
    */
    iterator() : _p(nullptr) {
    }

    /*!
      \brief Constructor
      \param p : hook to iterate from
      \post The instance refers to p
    */
    iterator(intrusive_list_hook_t<TAG> * const p) : _p(p) {
    }

    /*!
      \brief Copy-constructor
      \param it : iterator to build from
      \post The instance refers to the same hook as it
    */
    iterator(iterator const & it) : _p(it._p) {
    }

    /*!
      \brief Assignment operator
      \param it : iterator to assign from
      \return The instance after assignment
      \post The instance refers to the same hook as it
    */
    iterator & operator = (const iterator & it) {
      if (this != &it)
	_p = it._p;
      return *this;
    }

    /*!
      \brief Next hook
      \return The instance after increment
      \post The instance refers to the next hook
      \throw std::invalid_argument : when the iterator is invalid (i.e. nullptr)
    */
    iterator & operator ++ () {
      if (_p == nullptr)
	throw std::invalid_argument
	  ("*** intrusive_list_t::iterator::++: null pointer");
      _p = _p->next;
      return *this;
    }

    /*!
      \brief Equality predicate
      \param it : iterator to compare to
      \return True if the instance refers to the same hook as it, false
      otherwise
    */
    bool operator == (iterator const & it) const {
      return (_p == it._p);
    }

    /*!
      \brief Dis-equality predicate
      \param it : iterator to compare to
      \return True if the instance does not refer to the same hook as it, false
      otherwise
    */
    bool operator != (iterator const & it) const {
      return (_p != it._p);
    }

    /*!
      \brief Dereference operator
      \return The value referenced to by the instance
    */
    T * operator * () const {
      return CAST(T *, _p);
    }
  private:
    intrusive_list_hook_t<TAG> * _p;   /*!< Pointer to hook */
  };


  /*!
    \brief Accessor to an iterator
    \return An iterator refering to the first element in the list if the list
    is not empty, and to the end of the list if it is empty
  */
  iterator begin() {
    return iterator(_head);
  }
  
  /*!
    \brief Accessor to an iterator
    \return An iterator refering to the fictuous element after the last element
    in the list
  */
  iterator end() {
    if (_tail == nullptr)
      return iterator(_tail);
    else
      return iterator(_tail->next);
  }


  /*!
    \typedef const iterator const_iterator
    \brief Constant iterator
  */
  typedef const iterator const_iterator;

  /*!
    \brief Accessor to a constant iterator
    \return An iterator refering to the first element in the list if the list
    is not empty, and to the end of the list if it is empty
  */
  const_iterator begin() const {
    return const_iterator(_head);
  }
  
  /*!
    \brief Accessor to a constant iterator
    \return An iterator refering to the fictuous element after the last element
    in the list
  */
  const_iterator end() const {
    if (_tail == nullptr)
      return const_iterator(_tail);
    else
      return const_iterator(_tail->next);
  }

  /*!
    \brief Constructor
    \post The instance is an empty list
  */
  intrusive_list_t() : _head(nullptr), _tail(nullptr) {
  }

  /*!
    \brief Copy constructor
    \param l : intrusive list to copy
    \post All the elements are SHARED by the new instance and by list l: they
    are not copied
  */
  intrusive_list_t(intrusive_list_t const & l) : _head(l._head),
						 _tail(l._tail) {
  }

  /*!
    \brief Move constructor
    \param l : intrusive list to copy
    \post The new instance is the list of elements in l, and l has been emptied
  */
  intrusive_list_t(intrusive_list_t && l) : _head(l._head),
					    _tail(l._tail) {
    l._head = nullptr;
    l._tail = nullptr;
  }

  /*!
    \brief Assignement operator
    \param l : intrusive list to assign form
    \post The instance has first been cleared (all its elements have been
    unchained), then it has been assigned the elements in l, and finally l
    has been emptied
   */
  intrusive_list_t & operator = (intrusive_list_t const & l) {
    if (this != &l) {
      clear();
      _head = l._head;
      _tail = l._tail;
    }
    
    return *this;
  }

  /*!
    \brief Move assignement operator
    \param l : intrusive list to assign form
    \post The instance has first been cleared (all its elements have been
    unchained), then it has been assigned the elements in l, and finally l
    has been emptied
   */
  intrusive_list_t & operator = (intrusive_list_t && l) {
    if (this != &l) {
      clear();
      _head = l._head;
      _tail = l._tail;
      l._head = nullptr;
      l._tail = nullptr;
    }

    return *this;
  }

  /*!
    \brief Destructor
    \post The list has NOT BEEN CLEARED hence elements may be let dangling.
    It cannot be cleared automatically has copy-construction and assignment
    share list elements.
  */
  ~intrusive_list_t() = default;

  /*!
    \brief Emptiness predicate
    \return True if the list is empty, false otherwise
  */
  bool empty() const {
    return ( (_head == _tail) && (_head == nullptr) );
  }

  /*!
    \brief Computes the size of the list (linear time)
    \return The number of elements stored in the list
  */
  size_t size() const {
    size_t size = 0;
    for (auto it = begin(); it != end(); ++it)
      ++size;
    return size;
  }

  /*!
    \brief Membership predicate (constant time)
    \param p : element to check
    \return True if p is in the list, false otherwise
  */
  bool find(T * const p) const {
    intrusive_list_hook_t<TAG> * _p = CAST(intrusive_list_hook_t<TAG> *, p);
    // p is in the list if it either linked, or unlinked but both the head
    // and the tail of a 1-element list
    return ( _p->linked() ||
	     ( (_head == _p) && (_tail == _p) ) );
  }

  /*!
    \brief Accessor
    \return The front element in the list
    \throw std::logic_error : when the list is empty
  */
  T * front() const {
    if (_head == nullptr)
      throw std::logic_error("*** intrusive_list_t::front: empty list");
    return CAST(T *, _head);
  }

  /*!
    \brief Accessor
    \return The back element in the list
    \throw std::logic_error : when the list is empty
  */
  T * back() const {
    if (_tail == nullptr)
      throw std::logic_error("*** intrusive_list_t::back: empty list");
    return CAST(T *, _tail);
  }

  /*!
    \brief Inserts an element at the head of the list
    \param p : element to insert
    \post p has been added at the head of the list
  */
  void push_front(T * p) {
    insert(begin(), p);
  }

  /*!
    \brief Removes the front element from the list
    \post The front element of the list has been removed. The new head of the
    list if the former second element (if any). No destructors are called.
    \throw std::logic_error : when the list is empty
  */
  void pop_front() {
    if (empty())
      throw std::logic_error("*** intrusive_list_t::pop_front: empty list");
    erase(_head);
  }

  /*!
    \brief Inserts an element at the end of the list
    \param p : element to insert
    \post p has been added at the end of the list
  */
  void push_back(T * p) {
    insert(end(), p);
  }

  /*!
    \brief Removes the last element from the list
    \post The last element of the list has been removed. The new tail of the
    list if the former second-to-last element (if any). No destructors are
    called.
    \throw std::logic_error : when the list is empty
  */
  void pop_back() {
    if (empty())
      throw std::logic_error("*** intrusive_list_t::pop_back: empty list");
    erase(_tail);
  }

  /*!
    \brief Inserts an element in the list
    \param it : refers to the insertion position
    \param p : element to insert
    \return An iterator to the newly inserted element
    \pre it is a valid iterator
    \post p has been inserted in position pos in the list
  */
  iterator insert(iterator it, T * p) {
    intrusive_list_hook_t<TAG> * _it = CAST(intrusive_list_hook_t<TAG> *, *it);
    intrusive_list_hook_t<TAG> * _p = CAST(intrusive_list_hook_t<TAG> *, p);
    return insert(_it, _p);
  }

  /*!
    \brief Erases an element from the list
    \param it : refers to the element to remove
    \return A reference to the element that follows it in the list
    \pre it is a valid iterator
    \post The element refered to by it has been removed from the list. No
    destructors are called.
  */
  iterator erase(iterator it) {
    intrusive_list_hook_t<TAG> * _it = CAST(intrusive_list_hook_t<TAG> *, *it);
    return erase(_it);
  }

  /*!
    \brief Erases an element from the list and disposes of the element
    \tparam DISPOSER : type of disposer
    \param it : refers to the element to remove and dispose
    \param disposer : a disposer
    \return A reference to the element that follows it in the list
    \pre it is a valid iterator
    \post The element refered to by it has been removed from the list, then
    disposer() has been called on the removed element. No destructors are
    called.
  */
  template <class DISPOSER>
  iterator erase_and_dispose(iterator it, DISPOSER disposer) {
    intrusive_list_hook_t<TAG> * _it = CAST(intrusive_list_hook_t<TAG> *, *it);
    auto itn = erase(_it);
    disposer(*it);
    return itn;
  }

  /*!
    \brief Erases an element from the list
    \param p : element to remove
    \return A reference to the element that follows p in the list
    \pre p is an element in the list (not checked)
    \post p has been removed from the list. No destructors are called.
  */
  iterator erase(T * p) {
    intrusive_list_hook_t<TAG> * _p = CAST(intrusive_list_hook_t<TAG> *, p);
    return erase(_p);
  }

  /*!
    \brief Erases an element from the list and disposes of the element
    \tparam DISPOSER : type of disposer
    \param p : element to remove and dispose
    \param disposer : a disposer
    \return A reference to the element that follows p in the list
    \pre p is an element in the list (not checked)
    \post p has been removed from the list, then disposer() has been called
    on p. No destructors are called.
  */
  template <class DISPOSER>
  iterator erase_and_dispose(T * p, DISPOSER disposer) {
    intrusive_list_hook_t<TAG> * _p = CAST(intrusive_list_hook_t<TAG> *, p);
    auto it = erase(_p);
    disposer(p);
    return it;
  }

  /*!
    \brief Replaces an element by another one
    \param it : refers to the element to replace
    \param p : element to insert
    \return An iterator to the newly inserted element
    \pre it is a valid iterator
    \post p has been inserted in the list in position it, and the element
    referenced by it has been unlinked. No destructors are called.
  */
  iterator replace(iterator it, T * p) {
    intrusive_list_hook_t<TAG> * _it = CAST(intrusive_list_hook_t<TAG> *, *it);
    intrusive_list_hook_t<TAG> * _p = CAST(intrusive_list_hook_t<TAG> *, p);
    return replace(_it, _p);
  }

  /*!
    \brief Replaces an element by another one and disposes of the old one
    \tparam DISPOSE : type of disposer
    \param it : refers to the element to replace and dispose
    \param p : element to insert
    \param disposer : a disposer
    \return An iterator to the newly inserted element
    \pre it is a valid iterator
    \post p has been inserted in the list in position it, and the element
    referenced by it has been unlinked and disposed. No destructors are
    called.
  */
  template <class DISPOSER>
  iterator replace_and_dispose(iterator it, T * p, DISPOSER disposer) {
    intrusive_list_hook_t<TAG> * _it = CAST(intrusive_list_hook_t<TAG> *, *it);
    intrusive_list_hook_t<TAG> * _p = CAST(intrusive_list_hook_t<TAG> *, p);
    auto itp = replace(_it, _p);
    disposer(*it);
    return itp;
  }

  /*!
    \brief Replaces an element by another one
    \param r : element to replace
    \param p : element to insert
    \return An iterator to the newly inserted element
    \pre r is in the list
    \post p has been inserted in the list as a replacement for r, and r has
    been unlinked. No destructors are called.
  */
  iterator replace(T * r, T * p) {
    intrusive_list_hook_t<TAG> * _r = CAST(intrusive_list_hook_t<TAG> *, r);
    intrusive_list_hook_t<TAG> * _p = CAST(intrusive_list_hook_t<TAG> *, p);
    return replace(_r, _p);
  }

  /*!
    \brief Replaces an element by another one and disposes of the old one
    \tparam DISPOSER : type of disposer
    \param r : element to replace and dispose
    \param p : element to insert
    \param disposer : a disposer
    \return An iterator to the newly inserted element
    \pre r is in the list
    \post p has been inserted in the list as a replacement for r, and r has
    been unlinked, then disposer() has been called on r. No destructors are
    called.
  */
  template <class DISPOSER>
  iterator replace_and_dispose(T * r, T * p, DISPOSER disposer) {
    intrusive_list_hook_t<TAG> * _r = CAST(intrusive_list_hook_t<TAG> *, r);
    intrusive_list_hook_t<TAG> * _p = CAST(intrusive_list_hook_t<TAG> *, p);
    auto it = replace(_r, _p);
    disposer(r);
    return it;
  }

  /*!
    \brief Clears the list
    \post The list is empty and all the elements in the list have been
    unlinked. No destructors are called.
  */
  void clear() {
    clear_and_dispose( [] (T * t) {} ); // lambda t. skip
  }

  /*!
    \brief Clears the list and disposes of its elements
    \tparam DISPOSER : type of disposer
    \param disposer : a disposer
    \post The list is empty and all the elements in the list have been
    unlinked, then disposed. No destructors are called.
  */
  template <class DISPOSER>
  void clear_and_dispose(DISPOSER disposer) {
    if (empty())
      return;

    // Unlink all elments
    auto p = _head;
    while (p != nullptr) {
      _head = p->next;
      p->unlink();
      disposer( CAST(T *, p) );
      p = _head;
    }

    // Empty list
    _head = nullptr;
    _tail = nullptr;
  }
  
  /*!
    \brief Outputs the list (debug mode)
    \post The head link, the tail link, and the links between the hooks in the
    list have been output
  */
  void output(std::ostream & os) const {
    os << "head: " << _head << std::endl;
    os << "tail: " << _tail << std::endl;
    for (T * p : *this) {
      intrusive_list_hook_t<TAG> * _p = CAST(intrusive_list_hook_t<TAG> *, p);
      os << "@: " << _p
	 << "  pred: " << _p->pred
	 << "  next: " << _p->next
	 << std::endl;
    }
  }
protected:
  /*!
    \brief Inserts an element in the list. Internal function that manipulates
    hooks directly
    \param pos : refers to the insertion position
    \param p : element to insert
    \return An iterator to the newly inserted element
    \pre pos is a hook in the list (not checked)
    \post p has been inserted before hook pos in the list
  */
  iterator insert(intrusive_list_hook_t<TAG> * pos,
		  intrusive_list_hook_t<TAG> * p) {
    // Links p
    p->next = pos;

    if (pos == nullptr)
      p->pred = _tail;
    else
      p->pred = pos->pred;

    // Update link for p's pred (if any)
    if (p->pred != nullptr)
      p->pred->next = p;

    // Update the link for p's next (if any)
    if (p->next != nullptr)
      p->next->pred = p;

    // Moves _head if p is the new front element
    if (_head == pos)
      _head = p;

    // Moves _tail if p is the new back element
    if (pos == nullptr)
      _tail = p;

    return iterator(p);
  }

  /*!
    \brief Erases an element from the list
    \param p : element to remove
    \return A reference to the element that follows it in the list
    \pre p is a hook in the list (not checked)
    \post p has been removed from the list. No destructors are called.
  */
  iterator erase(intrusive_list_hook_t<TAG> * p) {
    iterator it(p->next);

    // Links p's pred and next (if any)
    if (p->pred != nullptr)
      p->pred->next = p->next;

    if (p->next != nullptr)
      p->next->pred = p->pred;

    // Moves _head and _tail if needed
    if (_head == p)
      _head = p->next;
    
    if (_tail == p)
      _tail = p->pred;

    // Unlink p
    p->unlink();

    return it;
  }

  /*!
    \brief Replaces an element by another one
    \param to_replace : element to replace
    \param p : element to insert
    \return An iterator to the newly inserted element
    \pre to_replace is in the list
    \post p has been inserted in the list as a replacement for to_replace,
    and to_replace has been unlinked. No destructors are called.
  */
  iterator replace(intrusive_list_hook_t<TAG> * to_replace,
		   intrusive_list_hook_t<TAG> * p) {
    iterator it = insert(to_replace, p);
    erase(to_replace);
    return it;
  }

  intrusive_list_hook_t<TAG> * _head;   /*!< Pointer to list head */
  intrusive_list_hook_t<TAG> * _tail;   /*!< Pointer to list tail */
};

#endif // __TCHECKER_INTRUSIVE_LIST__
