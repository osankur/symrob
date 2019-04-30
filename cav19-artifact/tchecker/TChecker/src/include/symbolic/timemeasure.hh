#ifndef TIMEMEASURE_HH
#define TIMEMEASURE_HH

#include <chrono>

namespace symbolic {

  class time_measurement {
  public:
    static std::chrono::nanoseconds abstract_time ;
  };

}
#endif // TIMEMEASURE_HH
