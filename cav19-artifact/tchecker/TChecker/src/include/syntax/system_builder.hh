#ifndef __TCHECKER_SYSTEM_BUILDER_HH__
#define __TCHECKER_SYSTEM_BUILDER_HH__

#include "base/labelset.hh"
#include "syntax/system_fwd.hh"

/*!
  \file system_builder.hh
  \brief Tools for building syntax::system_t instances
*/

namespace syntax {

  /*!
    \class system_builder_t
    \brief Abstract class of a system builder
  */
  class system_builder_t {
  public:
    /*!
      \brief Builds a syntax::system_t
      \param system : the system to build
    */
    virtual void operator() (syntax::system_t & system) = 0;

    /*!
      \brief Destructor
     */
    virtual ~system_builder_t() = default;
  };



  /*!
    \class extern_system_builder_t
    \brief System builder that encapsulates a building function
    \tparam build_system : the encapsulated function
  */
  template < void build_system(syntax::system_t & system) >
  class extern_system_builder_t : public system_builder_t {
  public:
    /*!
      \brief Constructor
    */
    extern_system_builder_t() = default;
    
    /*!
      \brief Constructor
      \param system : the system to build
      \post system has been built calling function build_system
    */
    extern_system_builder_t(syntax::system_t & system) {
      this->operator()(system);
    }

    /*!
      \brief Builds a syntax::system_t
      \param system : the system to build
      \post Function build_model has been applied on system
    */
    void operator() (syntax::system_t & system) {
      build_system(system);
    }

    /*!
      \brief Destructor
    */
    ~extern_system_builder_t() = default;
  };
  
} // end of namespace syntax

#endif // __TCHECKER_SYSTEM_BUILDER_HH__
