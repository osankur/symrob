#ifndef __TCHECKER_CLOCKINFO_HH__
#define __TCHECKER_CLOCKINFO_HH__

/*!
  \file clockinfo.hh
  \brief Efficient storage of clock information from a transition (inspired
  from raw_t type in UPPAAL DBM library)
 */

/*!
  \brief Clock information from a transition: encodes a bound put on the clock
  by a guard (on 31 bits) and if the clock is reset or not (1 bit)
*/
typedef int32_t clockinfo_t;

/*!
  \brief Conversion from bound and reset to clock information
  \param bound : bound on the clock
  \param reset : whether the clock is reset or not
  \return The encoding of (bound, reset) as clock information
*/
static inline clockinfo_t bound2clockinfo(int32_t bound, bool reset) {
  return ( (bound << 1) | (reset ? 1 : 0) );
}

/*!
  \brief Conversion from clock information to bound
  \param v : clock information
  \return The bound stored in v
*/
static inline int32_t clockinfo2bound(clockinfo_t v) {
  return (v >> 1);
}

/*!
  \brief Conversion from clock information to reset
  \param v : clock information
  \return Whether the clock is reset or not according to v
*/
static inline bool clockinfo2reset(clockinfo_t v) {
  return ((v & 1) ? true : false);
}

#endif // __TCHECKER_CLOCKINFO_HH__
