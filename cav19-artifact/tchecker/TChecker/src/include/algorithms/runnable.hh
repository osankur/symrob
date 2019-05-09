#ifndef __TCHECKER_ALGORITHMS_RUNNABLE_HH__
#define __TCHECKER_ALGORITHMS_RUNNABLE_HH__

/*!
  \file runnable.hh
  \brief Runnable algorithms
 */

namespace algorithms {
  
  /*!
    \class runnable_t
    \brief A class of runnable algorithms (i.e. that provide method run())
   */
  class runnable_t {
  public:
    /*!
      \brief Destructor
     */
    virtual ~runnable_t() = default;

    /*!
      \brief Runs the algorithm
      \return Semantics of return value depend on the algorithm
    */
    virtual bool run() = 0;
  };

} // end of namespace algorithms

#endif // __TCHECKER_ALGORITHMS_RUNNABLE_HH__
