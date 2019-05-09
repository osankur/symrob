#ifndef __UPPAAL_COMPILED_MODEL_HH__
# define __UPPAAL_COMPILED_MODEL_HH__

# include <vector>
# include <map>
# include <stack>

# include "base/ptr.hh"
# include "syntax/layout.hh"
# include "syntax/sync_product.hh"
# include "syntax/system.hh"

namespace uppaal {
  typedef unsigned int address_t;
  typedef unsigned int id_t;

  class layout_t;

  class compiled_model_t {
  public:
    struct process_t {
      id_t index;
      id_t initial_loc;
      std::string name;
    };
  
    struct location_t {
      id_t index;
      id_t pid;
      address_t invariant;
      std::string flag;
      std::string name;
    };
  
    typedef syntax::generic_label_t<address_t> sync_label_t;

    struct edge_t {
      id_t pid;
      id_t src;
      id_t tgt;
      address_t guard;
      address_t sync;
      address_t update;
    };
  
    struct slot_t {
      enum kind_t {
	CONST, CLOCK, VARIABLE, META, STATIC, OTHER
      };
      kind_t kind;
      id_t index;
      int min;
      int max;
      int init;
      std::string flags;
      std::string name;
    };

    struct expression_t {
      address_t addr;
      std::vector<id_t> reads;
      std::vector<id_t> writes;
      std::string text;
    };

    compiled_model_t ();
    virtual ~compiled_model_t ();

    slot_t const &get_ith_slot (id_t i) const;
    std::size_t get_number_of_slots () const;
    std::size_t get_number_of_clocks () const;
    std::size_t get_bytecode_size () const;
    std::size_t get_number_of_processes () const;
    
    bool has_pid (id_t id) const;
    bool has_loc (id_t id) const;
    bool has_expr (address_t addr) const;
    
    void add_edge (const edge_t &e);
    void add_location (const location_t &l);
    void add_slot (const slot_t &l);
    void add_clock (const slot_t &l);
    void add_bytecode (int bc);
    void add_process (process_t &p);

    location_t &get_location (id_t id);
    std::string make_default_label (const location_t &loc);
    process_t &get_process (id_t id);
    expression_t &get_expr (address_t addr);

    void build_system (syntax::system_t &system);
    int run_at (syntax::layout_t const *l, address_t addr) const;

    int run_at (syntax::layout_t *l, address_t addr) const
      throw (std::overflow_error);

    void check_slot_value (id_t id, int value) const 
      throw (std::overflow_error);

  private: 
    std::vector<int> bytecode;
    std::vector<process_t> processes;
    std::map<id_t, location_t> locations;
    std::map<address_t, expression_t> expressions;
    std::vector<edge_t> edges;
    std::vector<slot_t> slots;
    std::vector<int> clocks;

    void check_synchro (process_t &P, expression_t &expr, 
			syntax::sync_label_t const * &sync) const;

    std::string interp_cexpr (address_t addr)
      throw (std::invalid_argument);
    syntax::layout_predicate_t split_predicate (expression_t &expr,
						std::string &cexpr);
    syntax::layout_update_t split_updates (expression_t &expr,
					   std::string &creset);
    void look_for_clocks_and_vars (const std::vector<id_t> &,
				   std::map<std::string, std::string> &,
				   bool &, bool &);

    virtual void exec_instr (layout_t const *l, address_t &addr, 
			     std::stack<int> &S, address_t &bp) const;

    //    virtual void exec_instr (layout_t *l, address_t &addr, 
    // std::stack<int> &S, address_t &bp) const
    //      throw (std::overflow_error);
    template <typename layoutT> int _run_at (layoutT l, address_t addr) const;
  };
} // end of namespace uppaal

#endif /* ! __UPPAAL_COMPILED_MODEL_HH__ */
