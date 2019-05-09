#ifndef __UPPAAL_LAYOUT_HH__
# define __UPPAAL_LAYOUT_HH__

# include <stdexcept>
# include "syntax/layout.hh"
# include "uppaal/compiled_model.hh"

namespace uppaal {
  class layout_t : public syntax::layout_t {
  public:
    layout_t (compiled_model_t const *ucm);

    layout_t (layout_t const &l);

    virtual ~layout_t();

    virtual bool operator == (syntax::layout_t const & l) const;

    virtual std::size_t hash() const;

    virtual void output(std::ostream & os) const;

    virtual void initial();

    compiled_model_t const *get_model () const;

    int get_value (id_t i) const;

    void set_value (id_t i, int value) const;

  private:
    compiled_model_t const *umodel;
    int *values;
  };


  class layout_predicate_t : public syntax::layout_predicate_t {
  public:
    layout_predicate_t (address_t addr);
    virtual ~layout_predicate_t();
    virtual bool operator () (syntax::layout_t const & l) const;
  private:
    address_t addr;
  };
    

  class layout_update_t : public syntax::layout_update_t {
  public:
    layout_update_t (address_t addr);
    virtual ~layout_update_t ();
    virtual void operator () (syntax::layout_t & l) const;
  private:
    address_t addr;
  };
} // end of namespace uppaal

#endif /* ! __UPPAAL_LAYOUT_HH__ */
