#ifndef __UPPAAL_SYSTEM_BUILDER_HH__
# define __UPPAAL_SYSTEM_BUILDER_HH__

# include <istream>
# include "syntax/system.hh"

namespace uppaal {
  class compiled_model_t;

  class system_builder_t : public syntax::system_builder_t {
  public:

    system_builder_t ();

    virtual ~system_builder_t();

    virtual void load_system (std::istream &input)
      throw (std::string);
    
    virtual void operator() (syntax::system_t & system);

  private:
    compiled_model_t *umodel;
  };
} // end of namespace uppaal

#endif // __UPPAAL_SYSTEM_BUILDER_HH__
