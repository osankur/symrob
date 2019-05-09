#ifndef __TCHECKER_CAST_HH__
#define __TCHECKER_CAST_HH__

/*!
  \file cast.hh
  \brief Type casting
 */

/*!
  \macro SAFE_CAST
  \brief If macro SAFE_CAST is defined, then casts are typed checked using
  dynamic_cast<>. Otherwise, static_cast<> is used which is faster but has
  no type checking
*/

/*!
  \macro CAST
  \brief Casts value v into type T. The cast is typechecked if the macro
  SAFE_CAST is defined
 */
#ifdef SAFE_CAST
#define CAST(T,v) (dynamic_cast<T>(v))
#else
#define CAST(T,v) (static_cast<T>(v))
#endif // SAFE_CAST

#endif // __TCHECKER_CAST_HH__
