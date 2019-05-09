#ifndef __TCHECKER_SYSTEM_FWD_HH__
#define __TCHECKER_SYSTEM_FWD_HH__

/*!
  \file system_fwd.hh
  \brief Forward declarations
*/

/*!
  \namespace syntax
  \brief Syntax of timed automata
*/
namespace syntax {
  
  /*!
    \var static const std::string snz_name1
    \var static const std::string snz_name2
    \brief Reserved names for Strongly Non-Zeno (SNZ) construction
    
    ONLY FOR INTERNAL USE. ACCESS FROM global_t.
  */
  extern const std::string snz_name1;
  extern const std::string snz_name2;


  /*!
    \typedef unsigned int proc_id_t
    \brief Identifier of processes
  */
  typedef unsigned int proc_id_t;


  /*!
    \brief Forward declarations
  */
  class system_t;       // see system.hh
  class synchronizer_t; // see sync_product.hh

} // end of namespace syntax


#endif // __TCHECKER_SYSTEM_FWD_HH__
