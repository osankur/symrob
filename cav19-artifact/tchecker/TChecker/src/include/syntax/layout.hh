#ifndef __TCHECKER_LAYOUT_HH__
#define __TCHECKER_LAYOUT_HH__

#include <functional>
#include <ostream>

#include "base/cast.hh"

/*!
  \file layout.hh
  \brief Memory layouts for systems of timed processes

  Layouts are used to store discrete variables in a model (see
  syntax::system_t). They are implemented by deriving from class
  syntax::layout_t.

  Predicates and updates have type syntax::layout_predicate_t and
  syntax::layout_update_t respectively. True predicate (syntax::layout_true),
  false predicate (syntax::layout_false) and identity update
  (syntax::layout_id) are provided.

  Models instantiate layouts using a syntax::layout_allocator_t
  instance. An allocator must be provided for each new type of
  layout. Specializing class syntax::layout_T_alloc_t should be
  sufficient in most cases. An allocator for default layout
  (syntax::layout_t) is provided (syntax::layout_alloc).
*/

/*!
  \namespace syntax
  \brief Syntax of timed automata
*/
namespace syntax {

  /*!
    \class layout_t
    \brief Basic memory layout

    A memory layout is a collection of discrete variables intended to be
    manipulated by the timed processes in a system (see syntax::system_t). This
    basic layout does not contain any discrete value. A system designer should
    inherit from this class to define a system's layout.

    It is expected that sizeof() returns the size of the memory used by the
    layout
  */
  class layout_t {
  public:
    /*!
      \brief Constructor
    */
    layout_t();

    /*!
      \brief Copy-constructor
    */
    layout_t(layout_t const & l);

    /*!
      \brief Destructor
    */
    virtual ~layout_t();

    /*!
      \brief Equality predicate
      \param l : the layout to compare
      \return True if layout equals l, false otherwise      
    */
    virtual bool operator == (layout_t const & l) const;

    /*!
      \brief Hash function
      \return Hash code of layout
    */
    virtual std::size_t hash() const;

    /*!
      \brief Output function
      \post Layout has been output to os
    */
    virtual void output(std::ostream & os) const;

    /*!
      \brief Initial valuation
      \post Layout has been set to its initial valuation
    */
    virtual void initial();
  };


  /*!
    \brief Hash function compliant with boost library
    \param l : the layout to hash
    \return Hash code for l
  */
  std::size_t hash_value(layout_t const & l);


  
  /*!
    \brief Predicate on layouts
  */
  typedef std::function< bool(layout_t const & l) > layout_predicate_t;
    
  /*!
    \brief Predicate on layouts that always returns true
  */
  bool layout_true(layout_t const & l);

  /*!
    \brief Predicate on layouts that always returns false
  */
  bool layout_false(layout_t const & l);




  /*!
    \brief Updates layouts
  */
  typedef std::function< void(layout_t & l) > layout_update_t;

  /*!
    \brief Identity update
  */
  void layout_id(layout_t & l);



  
  /*!
    \class layout_alloc_t
    \brief Allocator of layouts
  */
  class layout_alloc_t {
  public:
    /*!
      \brief Destructor
    */
    virtual ~layout_alloc_t();

    /*!
      \brief Allocation operator
      \return A pointer to a layout
      \post Memory has been allocated for the new layout. It should be
      deleted by the receiver
    */
    virtual layout_t * operator() () const = 0;

    /*!
      \brief Allocation operator by copy
      \param l : layout to copy
      \return A pointer to a copy of layout l
      \post Memory has been allocated for the new layout. It should be
      deleted by the receiver
    */
    virtual layout_t * operator() (layout_t const * l) const = 0;
  };



  /*!
    \class layout_T_alloc_t
    \brief Allocator of layouts of type T
    \tparam T : type of layouts to allocate, should be a derivative of layout_t
  */
  template <class T> 
  class layout_T_alloc_t : public layout_alloc_t {
  public:
    /*!
      \brief Destructor
    */
    virtual ~layout_T_alloc_t() = default;

    /*!
      \brief Allocation operator
      \return A pointer to a new instance of T
      \post Memory has been allocated for the new layout. It should be deleted
      by the receiver
    */
    layout_t * operator() () const {
      return (new T());
    }
    
    /*!
      \brief Copy allocation operator
      \param l : layout to copy
      \return A pointer to a copy of layout l of type T
      \post Memory has been allocated for the new layout. It should be deleted
      by the receiver
    */
    layout_t * operator() (layout_t const * l) const {
      T const * t = CAST(T const *, l);
      assert(t != nullptr);
      return (new T(*t));
    }
  };

} // end of namespace syntax


#endif // __TCHECKER_LAYOUT_HH__
