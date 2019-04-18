#include <iostream>
#include "syntax/system.hh"
#include "syntax/sync_product.hh"
namespace multi{
  class layout_t : public syntax::layout_t {
  public:
        
bool IP0sh0;
bool IP0sh1;
bool IP0sh2;
bool IP0controllable_do_shift;
bool LP0state_benchn11;
bool LP0state_benchr0_out;
bool LP0state_benchr1_out;
bool LP0state_benchr2_out;
bool LP0state_benchr3_out;
bool LP0state_benchr4_out;
bool LP0state_benchr5_out;
bool LP0state_benchr6_out;
bool LP0state_benchr7_out;
bool IP1sh0;
bool IP1sh1;
bool IP1sh2;
bool IP1controllable_do_shift;
bool LP1state_benchn11;
bool LP1state_benchr0_out;
bool LP1state_benchr1_out;
bool LP1state_benchr2_out;
bool LP1state_benchr3_out;
bool LP1state_benchr4_out;
bool LP1state_benchr5_out;
bool LP1state_benchr6_out;
bool LP1state_benchr7_out;
bool IP2a_0_;
bool IP2a_1_;
bool IP2b_0_;
bool IP2b_1_;
bool IP2controllable_c_0_;
bool IP2controllable_c_1_;
bool LP2state_n15;
bool LP2err_out;

        char running0;
        char running1;
        char dead ;
        char round ;
        bool w0 ;
        bool w1 ;
        bool w2 ;
    layout_t(){
        
IP0sh0 =0;
IP0sh1 =0;
IP0sh2 =0;
IP0controllable_do_shift =0;
LP0state_benchn11 =0;
LP0state_benchr0_out =0;
LP0state_benchr1_out =0;
LP0state_benchr2_out =0;
LP0state_benchr3_out =0;
LP0state_benchr4_out =0;
LP0state_benchr5_out =0;
LP0state_benchr6_out =0;
LP0state_benchr7_out =0;
IP1sh0 =0;
IP1sh1 =0;
IP1sh2 =0;
IP1controllable_do_shift =0;
LP1state_benchn11 =0;
LP1state_benchr0_out =0;
LP1state_benchr1_out =0;
LP1state_benchr2_out =0;
LP1state_benchr3_out =0;
LP1state_benchr4_out =0;
LP1state_benchr5_out =0;
LP1state_benchr6_out =0;
LP1state_benchr7_out =0;
IP2a_0_ =0;
IP2a_1_ =0;
IP2b_0_ =0;
IP2b_1_ =0;
IP2controllable_c_0_ =0;
IP2controllable_c_1_ =0;
LP2state_n15 =0;
LP2err_out =0;

        running0 = 0;
        running1 = 0;
        dead = 0;
        round = 0;
        w0 = 1;
        w1 = 1;
        w2 = 1;
    }
    virtual ~layout_t() {
    }

    layout_t(const layout_t & l)  = default;
    inline bool operator == (const syntax::layout_t & l) const {
      multi::layout_t const & _l = CAST(multi::layout_t const &, l);
        
if (_l.IP0sh0 != IP0sh0) return false;
if (_l.IP0sh1 != IP0sh1) return false;
if (_l.IP0sh2 != IP0sh2) return false;
if (_l.IP0controllable_do_shift != IP0controllable_do_shift) return false;
if (_l.LP0state_benchn11 != LP0state_benchn11) return false;
if (_l.LP0state_benchr0_out != LP0state_benchr0_out) return false;
if (_l.LP0state_benchr1_out != LP0state_benchr1_out) return false;
if (_l.LP0state_benchr2_out != LP0state_benchr2_out) return false;
if (_l.LP0state_benchr3_out != LP0state_benchr3_out) return false;
if (_l.LP0state_benchr4_out != LP0state_benchr4_out) return false;
if (_l.LP0state_benchr5_out != LP0state_benchr5_out) return false;
if (_l.LP0state_benchr6_out != LP0state_benchr6_out) return false;
if (_l.LP0state_benchr7_out != LP0state_benchr7_out) return false;

            if (_l.running0 != running0) return false;
            if (_l.running1 != running1) return false;
            if (_l.round != round) return false;
            if (_l.w0 != w0) return false;
            if (_l.w1 != w1) return false;
            if (_l.w2 != w2) return false;
            if (_l.dead != dead) return false;
            
if (_l.IP1sh0 != IP1sh0) return false;
if (_l.IP1sh1 != IP1sh1) return false;
if (_l.IP1sh2 != IP1sh2) return false;
if (_l.IP1controllable_do_shift != IP1controllable_do_shift) return false;
if (_l.LP1state_benchn11 != LP1state_benchn11) return false;
if (_l.LP1state_benchr0_out != LP1state_benchr0_out) return false;
if (_l.LP1state_benchr1_out != LP1state_benchr1_out) return false;
if (_l.LP1state_benchr2_out != LP1state_benchr2_out) return false;
if (_l.LP1state_benchr3_out != LP1state_benchr3_out) return false;
if (_l.LP1state_benchr4_out != LP1state_benchr4_out) return false;
if (_l.LP1state_benchr5_out != LP1state_benchr5_out) return false;
if (_l.LP1state_benchr6_out != LP1state_benchr6_out) return false;
if (_l.LP1state_benchr7_out != LP1state_benchr7_out) return false;

            if (_l.running0 != running0) return false;
            if (_l.running1 != running1) return false;
            if (_l.round != round) return false;
            if (_l.w0 != w0) return false;
            if (_l.w1 != w1) return false;
            if (_l.w2 != w2) return false;
            if (_l.dead != dead) return false;
            
if (_l.IP2a_0_ != IP2a_0_) return false;
if (_l.IP2a_1_ != IP2a_1_) return false;
if (_l.IP2b_0_ != IP2b_0_) return false;
if (_l.IP2b_1_ != IP2b_1_) return false;
if (_l.IP2controllable_c_0_ != IP2controllable_c_0_) return false;
if (_l.IP2controllable_c_1_ != IP2controllable_c_1_) return false;
if (_l.LP2state_n15 != LP2state_n15) return false;
if (_l.LP2err_out != LP2err_out) return false;

            if (_l.running0 != running0) return false;
            if (_l.running1 != running1) return false;
            if (_l.round != round) return false;
            if (_l.w0 != w0) return false;
            if (_l.w1 != w1) return false;
            if (_l.w2 != w2) return false;
            if (_l.dead != dead) return false;
            
return true;
}
        inline size_t hash() const {
        size_t seed = global_t::instance().hash_seed();
        
	boost::hash_combine(seed,IP0sh0);
	boost::hash_combine(seed,IP0sh1);
	boost::hash_combine(seed,IP0sh2);
	boost::hash_combine(seed,IP0controllable_do_shift);
	boost::hash_combine(seed,LP0state_benchn11);
	boost::hash_combine(seed,LP0state_benchr0_out);
	boost::hash_combine(seed,LP0state_benchr1_out);
	boost::hash_combine(seed,LP0state_benchr2_out);
	boost::hash_combine(seed,LP0state_benchr3_out);
	boost::hash_combine(seed,LP0state_benchr4_out);
	boost::hash_combine(seed,LP0state_benchr5_out);
	boost::hash_combine(seed,LP0state_benchr6_out);
	boost::hash_combine(seed,LP0state_benchr7_out);

            	boost::hash_combine(seed, running0);
            	boost::hash_combine(seed, running1);
            	boost::hash_combine(seed, round);
            	boost::hash_combine(seed, w0);
            	boost::hash_combine(seed, w1);
            	boost::hash_combine(seed, w2);
            	boost::hash_combine(seed, dead);
            
	boost::hash_combine(seed,IP1sh0);
	boost::hash_combine(seed,IP1sh1);
	boost::hash_combine(seed,IP1sh2);
	boost::hash_combine(seed,IP1controllable_do_shift);
	boost::hash_combine(seed,LP1state_benchn11);
	boost::hash_combine(seed,LP1state_benchr0_out);
	boost::hash_combine(seed,LP1state_benchr1_out);
	boost::hash_combine(seed,LP1state_benchr2_out);
	boost::hash_combine(seed,LP1state_benchr3_out);
	boost::hash_combine(seed,LP1state_benchr4_out);
	boost::hash_combine(seed,LP1state_benchr5_out);
	boost::hash_combine(seed,LP1state_benchr6_out);
	boost::hash_combine(seed,LP1state_benchr7_out);

            	boost::hash_combine(seed, running0);
            	boost::hash_combine(seed, running1);
            	boost::hash_combine(seed, round);
            	boost::hash_combine(seed, w0);
            	boost::hash_combine(seed, w1);
            	boost::hash_combine(seed, w2);
            	boost::hash_combine(seed, dead);
            
	boost::hash_combine(seed,IP2a_0_);
	boost::hash_combine(seed,IP2a_1_);
	boost::hash_combine(seed,IP2b_0_);
	boost::hash_combine(seed,IP2b_1_);
	boost::hash_combine(seed,IP2controllable_c_0_);
	boost::hash_combine(seed,IP2controllable_c_1_);
	boost::hash_combine(seed,LP2state_n15);
	boost::hash_combine(seed,LP2err_out);

            	boost::hash_combine(seed, running0);
            	boost::hash_combine(seed, running1);
            	boost::hash_combine(seed, round);
            	boost::hash_combine(seed, w0);
            	boost::hash_combine(seed, w1);
            	boost::hash_combine(seed, w2);
            	boost::hash_combine(seed, dead);
            
return seed;
}

void output(std::ostream & os) const {}
};
}
void build_model(syntax::system_t & s){
s.name("Multi");
s.layout_alloc< syntax::layout_T_alloc_t<multi::layout_t> >();
s.add_clock("x0");
s.add_clock("x1");
s.add_clock("x2");
s.add_label("err");
s.add_process("Process0");
s.add_location("Process0", "w", "", "", syntax::loc_t::INIT);
s.add_location("Process0", "dead", "", "err");
s.add_location("Process0", "rel", "", "", syntax::loc_t::COMMITTED);
s.add_location("Process0", "up", "", "", syntax::loc_t::COMMITTED);
s.add_location("Process0", "disc_up", "", "", syntax::loc_t::COMMITTED);
s.add_location("Process0", "on0", "x0 <= 1000","");
s.add_location("Process0", "on1", "x0 <= 800","");
s.add_edge("Process0", "w", "on0", "", "x0", "go0?", 
    [](syntax::layout_t const & l){\
    multi::layout_t const & _l = CAST(multi::layout_t const &, l);\
    return _l.LP0state_benchn11 == 0;\
    }
    ,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.w0 = 0;\
    }
    );
s.add_edge("Process0", "w", "dead", "x0 >= 1999", "", "", 
    [](syntax::layout_t const & l){\
    multi::layout_t const & _l = CAST(multi::layout_t const &, l);\
    return _l.LP0state_benchn11 == 0;\
    }
    ,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.dead=1;;\
    }
    );
s.add_edge("Process0", "on0", "up", "x0 >= 500 && x0 <= 1000", "x0", "", 
    [](syntax::layout_t const & l){\
    multi::layout_t const & _l = CAST(multi::layout_t const &, l);\
    return _l.LP0state_benchn11 == 0;\
    }
    );
s.add_edge("Process0", "w", "on1", "", "x0", "go0?", 
    [](syntax::layout_t const & l){\
    multi::layout_t const & _l = CAST(multi::layout_t const &, l);\
    return _l.LP0state_benchn11 == 1;\
    }
    ,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.w0 = 0;\
    }
    );
s.add_edge("Process0", "w", "dead", "x0 >= 2199", "", "", 
    [](syntax::layout_t const & l){\
    multi::layout_t const & _l = CAST(multi::layout_t const &, l);\
    return _l.LP0state_benchn11 == 1;\
    }
    ,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.dead=1;;\
    }
    );
s.add_edge("Process0", "on1", "up", "x0 >= 400 && x0 <= 800", "x0", "", 
    [](syntax::layout_t const & l){\
    multi::layout_t const & _l = CAST(multi::layout_t const &, l);\
    return _l.LP0state_benchn11 == 1;\
    }
    );
s.add_location("Process0", "JustSetIP0sh0", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process0", "up", "JustSetIP0sh0", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP0sh0 = 0;;\
    }
    );
s.add_edge("Process0", "up", "JustSetIP0sh0", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP0sh0 = 1;;\
    }
    );
s.add_location("Process0", "JustSetIP0sh1", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process0", "JustSetIP0sh0", "JustSetIP0sh1", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP0sh1 = 0;;\
    }
    );
s.add_edge("Process0", "JustSetIP0sh0", "JustSetIP0sh1", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP0sh1 = 1;;\
    }
    );
s.add_location("Process0", "JustSetIP0sh2", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process0", "JustSetIP0sh1", "JustSetIP0sh2", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP0sh2 = 0;;\
    }
    );
s.add_edge("Process0", "JustSetIP0sh1", "JustSetIP0sh2", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP0sh2 = 1;;\
    }
    );
s.add_location("Process0", "JustSetIP0controllable_do_shift", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process0", "JustSetIP0sh2", "JustSetIP0controllable_do_shift", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP0controllable_do_shift = 0;;\
    }
    );
s.add_edge("Process0", "JustSetIP0sh2", "JustSetIP0controllable_do_shift", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP0controllable_do_shift = 1;;\
    }
    );
s.add_location("Process0", "UpdatedLP0state_benchn11", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process0", "JustSetIP0controllable_do_shift", "UpdatedLP0state_benchn11", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.LP0state_benchn11 = 1;;\
    }
    );
s.add_location("Process0", "UpdatedLP0state_benchr0_out", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process0", "UpdatedLP0state_benchn11", "UpdatedLP0state_benchr0_out", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.LP0state_benchr0_out = (1-((1-((1-((1-(_l.LP0state_benchr0_out)) * (_l.LP0state_benchn11))) * (1-(_l.IP0controllable_do_shift)))) * (1-((1-((1-((1-((1-((1-((1-(_l.LP0state_benchr0_out)) * (_l.LP0state_benchn11))) * (1-(_l.IP0sh0)))) * (1-(((_l.LP0state_benchr7_out) * (_l.LP0state_benchn11)) * (_l.IP0sh0))))) * (1-(_l.IP0sh2)))) * (1-((1-((1-(((_l.LP0state_benchr4_out) * (_l.LP0state_benchn11)) * (1-(_l.IP0sh0)))) * (1-(((_l.LP0state_benchr3_out) * (_l.LP0state_benchn11)) * (_l.IP0sh0))))) * (_l.IP0sh2))))) * (_l.IP0controllable_do_shift)))));;\
    }
    );
s.add_location("Process0", "UpdatedLP0state_benchr1_out", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process0", "UpdatedLP0state_benchr0_out", "UpdatedLP0state_benchr1_out", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.LP0state_benchr1_out = (1-((1-(((_l.LP0state_benchr1_out) * (_l.LP0state_benchn11)) * (1-(_l.IP0controllable_do_shift)))) * (1-((1-((1-((1-((1-(((_l.LP0state_benchr1_out) * (_l.LP0state_benchn11)) * (1-(_l.IP0sh0)))) * (1-((1-((1-(_l.LP0state_benchr0_out)) * (_l.LP0state_benchn11))) * (_l.IP0sh0))))) * (1-(_l.IP0sh2)))) * (1-((1-((1-(((_l.LP0state_benchr5_out) * (_l.LP0state_benchn11)) * (1-(_l.IP0sh0)))) * (1-(((_l.LP0state_benchr4_out) * (_l.LP0state_benchn11)) * (_l.IP0sh0))))) * (_l.IP0sh2))))) * (_l.IP0controllable_do_shift)))));;\
    }
    );
s.add_location("Process0", "UpdatedLP0state_benchr2_out", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process0", "UpdatedLP0state_benchr1_out", "UpdatedLP0state_benchr2_out", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.LP0state_benchr2_out = (1-((1-(((_l.LP0state_benchr2_out) * (_l.LP0state_benchn11)) * (1-(_l.IP0controllable_do_shift)))) * (1-((1-((1-((1-((1-(((_l.LP0state_benchr2_out) * (_l.LP0state_benchn11)) * (1-(_l.IP0sh0)))) * (1-(((_l.LP0state_benchr1_out) * (_l.LP0state_benchn11)) * (_l.IP0sh0))))) * (1-(_l.IP0sh2)))) * (1-((1-((1-(((_l.LP0state_benchr6_out) * (_l.LP0state_benchn11)) * (1-(_l.IP0sh0)))) * (1-(((_l.LP0state_benchr5_out) * (_l.LP0state_benchn11)) * (_l.IP0sh0))))) * (_l.IP0sh2))))) * (_l.IP0controllable_do_shift)))));;\
    }
    );
s.add_location("Process0", "UpdatedLP0state_benchr3_out", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process0", "UpdatedLP0state_benchr2_out", "UpdatedLP0state_benchr3_out", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.LP0state_benchr3_out = (1-((1-(((_l.LP0state_benchr3_out) * (_l.LP0state_benchn11)) * (1-(_l.IP0controllable_do_shift)))) * (1-((1-((1-((1-((1-(((_l.LP0state_benchr3_out) * (_l.LP0state_benchn11)) * (1-(_l.IP0sh0)))) * (1-(((_l.LP0state_benchr2_out) * (_l.LP0state_benchn11)) * (_l.IP0sh0))))) * (1-(_l.IP0sh2)))) * (1-((1-((1-(((_l.LP0state_benchr7_out) * (_l.LP0state_benchn11)) * (1-(_l.IP0sh0)))) * (1-(((_l.LP0state_benchr6_out) * (_l.LP0state_benchn11)) * (_l.IP0sh0))))) * (_l.IP0sh2))))) * (_l.IP0controllable_do_shift)))));;\
    }
    );
s.add_location("Process0", "UpdatedLP0state_benchr4_out", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process0", "UpdatedLP0state_benchr3_out", "UpdatedLP0state_benchr4_out", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.LP0state_benchr4_out = (1-((1-(((_l.LP0state_benchr4_out) * (_l.LP0state_benchn11)) * (1-(_l.IP0controllable_do_shift)))) * (1-((1-((1-((1-((1-(((_l.LP0state_benchr4_out) * (_l.LP0state_benchn11)) * (1-(_l.IP0sh0)))) * (1-(((_l.LP0state_benchr3_out) * (_l.LP0state_benchn11)) * (_l.IP0sh0))))) * (1-(_l.IP0sh2)))) * (1-((1-((1-((1-((1-(_l.LP0state_benchr0_out)) * (_l.LP0state_benchn11))) * (1-(_l.IP0sh0)))) * (1-(((_l.LP0state_benchr7_out) * (_l.LP0state_benchn11)) * (_l.IP0sh0))))) * (_l.IP0sh2))))) * (_l.IP0controllable_do_shift)))));;\
    }
    );
s.add_location("Process0", "UpdatedLP0state_benchr5_out", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process0", "UpdatedLP0state_benchr4_out", "UpdatedLP0state_benchr5_out", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.LP0state_benchr5_out = (1-((1-(((_l.LP0state_benchr5_out) * (_l.LP0state_benchn11)) * (1-(_l.IP0controllable_do_shift)))) * (1-((1-((1-((1-((1-(((_l.LP0state_benchr5_out) * (_l.LP0state_benchn11)) * (1-(_l.IP0sh0)))) * (1-(((_l.LP0state_benchr4_out) * (_l.LP0state_benchn11)) * (_l.IP0sh0))))) * (1-(_l.IP0sh2)))) * (1-((1-((1-(((_l.LP0state_benchr1_out) * (_l.LP0state_benchn11)) * (1-(_l.IP0sh0)))) * (1-((1-((1-(_l.LP0state_benchr0_out)) * (_l.LP0state_benchn11))) * (_l.IP0sh0))))) * (_l.IP0sh2))))) * (_l.IP0controllable_do_shift)))));;\
    }
    );
s.add_location("Process0", "UpdatedLP0state_benchr6_out", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process0", "UpdatedLP0state_benchr5_out", "UpdatedLP0state_benchr6_out", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.LP0state_benchr6_out = (1-((1-(((_l.LP0state_benchr6_out) * (_l.LP0state_benchn11)) * (1-(_l.IP0controllable_do_shift)))) * (1-((1-((1-((1-((1-(((_l.LP0state_benchr6_out) * (_l.LP0state_benchn11)) * (1-(_l.IP0sh0)))) * (1-(((_l.LP0state_benchr5_out) * (_l.LP0state_benchn11)) * (_l.IP0sh0))))) * (1-(_l.IP0sh2)))) * (1-((1-((1-(((_l.LP0state_benchr2_out) * (_l.LP0state_benchn11)) * (1-(_l.IP0sh0)))) * (1-(((_l.LP0state_benchr1_out) * (_l.LP0state_benchn11)) * (_l.IP0sh0))))) * (_l.IP0sh2))))) * (_l.IP0controllable_do_shift)))));;\
    }
    );
s.add_location("Process0", "UpdatedLP0state_benchr7_out", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process0", "UpdatedLP0state_benchr6_out", "UpdatedLP0state_benchr7_out", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.LP0state_benchr7_out = (1-((1-(((_l.LP0state_benchr7_out) * (_l.LP0state_benchn11)) * (1-(_l.IP0controllable_do_shift)))) * (1-((1-((1-((1-((1-(((_l.LP0state_benchr7_out) * (_l.LP0state_benchn11)) * (1-(_l.IP0sh0)))) * (1-(((_l.LP0state_benchr6_out) * (_l.LP0state_benchn11)) * (_l.IP0sh0))))) * (1-(_l.IP0sh2)))) * (1-((1-((1-(((_l.LP0state_benchr3_out) * (_l.LP0state_benchn11)) * (1-(_l.IP0sh0)))) * (1-(((_l.LP0state_benchr2_out) * (_l.LP0state_benchn11)) * (_l.IP0sh0))))) * (_l.IP0sh2))))) * (_l.IP0controllable_do_shift)))));;\
    }
    );
s.add_edge("Process0", "UpdatedLP0state_benchr7_out", "w", "", "", "release0!", 
    [](syntax::layout_t const & l){\
    multi::layout_t const & _l = CAST(multi::layout_t const &, l);\
    return _l.running0 == 0;\
    }
    ,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.w0 = 1;;\
    }
    );
s.add_edge("Process0", "UpdatedLP0state_benchr7_out", "w", "", "", "release1!", 
    [](syntax::layout_t const & l){\
    multi::layout_t const & _l = CAST(multi::layout_t const &, l);\
    return _l.running1 == 0;\
    }
    ,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.w0 = 1;;\
    }
    );
s.add_process("Process1");
s.add_location("Process1", "w", "", "", syntax::loc_t::INIT);
s.add_location("Process1", "dead", "", "err");
s.add_location("Process1", "rel", "", "", syntax::loc_t::COMMITTED);
s.add_location("Process1", "up", "", "", syntax::loc_t::COMMITTED);
s.add_location("Process1", "disc_up", "", "", syntax::loc_t::COMMITTED);
s.add_location("Process1", "on0", "x1 <= 1000","");
s.add_location("Process1", "on1", "x1 <= 800","");
s.add_edge("Process1", "w", "on0", "", "x1", "go1?", 
    [](syntax::layout_t const & l){\
    multi::layout_t const & _l = CAST(multi::layout_t const &, l);\
    return _l.LP1state_benchn11 == 0;\
    }
    ,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.w1 = 0;\
    }
    );
s.add_edge("Process1", "w", "dead", "x1 >= 1999", "", "", 
    [](syntax::layout_t const & l){\
    multi::layout_t const & _l = CAST(multi::layout_t const &, l);\
    return _l.LP1state_benchn11 == 0;\
    }
    ,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.dead=1;;\
    }
    );
s.add_edge("Process1", "on0", "up", "x1 >= 500 && x1 <= 1000", "x1", "", 
    [](syntax::layout_t const & l){\
    multi::layout_t const & _l = CAST(multi::layout_t const &, l);\
    return _l.LP1state_benchn11 == 0;\
    }
    );
s.add_edge("Process1", "w", "on1", "", "x1", "go1?", 
    [](syntax::layout_t const & l){\
    multi::layout_t const & _l = CAST(multi::layout_t const &, l);\
    return _l.LP1state_benchn11 == 1;\
    }
    ,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.w1 = 0;\
    }
    );
s.add_edge("Process1", "w", "dead", "x1 >= 2199", "", "", 
    [](syntax::layout_t const & l){\
    multi::layout_t const & _l = CAST(multi::layout_t const &, l);\
    return _l.LP1state_benchn11 == 1;\
    }
    ,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.dead=1;;\
    }
    );
s.add_edge("Process1", "on1", "up", "x1 >= 400 && x1 <= 800", "x1", "", 
    [](syntax::layout_t const & l){\
    multi::layout_t const & _l = CAST(multi::layout_t const &, l);\
    return _l.LP1state_benchn11 == 1;\
    }
    );
s.add_location("Process1", "JustSetIP1sh0", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process1", "up", "JustSetIP1sh0", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP1sh0 = 0;;\
    }
    );
s.add_edge("Process1", "up", "JustSetIP1sh0", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP1sh0 = 1;;\
    }
    );
s.add_location("Process1", "JustSetIP1sh1", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process1", "JustSetIP1sh0", "JustSetIP1sh1", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP1sh1 = 0;;\
    }
    );
s.add_edge("Process1", "JustSetIP1sh0", "JustSetIP1sh1", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP1sh1 = 1;;\
    }
    );
s.add_location("Process1", "JustSetIP1sh2", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process1", "JustSetIP1sh1", "JustSetIP1sh2", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP1sh2 = 0;;\
    }
    );
s.add_edge("Process1", "JustSetIP1sh1", "JustSetIP1sh2", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP1sh2 = 1;;\
    }
    );
s.add_location("Process1", "JustSetIP1controllable_do_shift", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process1", "JustSetIP1sh2", "JustSetIP1controllable_do_shift", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP1controllable_do_shift = 0;;\
    }
    );
s.add_edge("Process1", "JustSetIP1sh2", "JustSetIP1controllable_do_shift", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP1controllable_do_shift = 1;;\
    }
    );
s.add_location("Process1", "UpdatedLP1state_benchn11", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process1", "JustSetIP1controllable_do_shift", "UpdatedLP1state_benchn11", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.LP1state_benchn11 = 1;;\
    }
    );
s.add_location("Process1", "UpdatedLP1state_benchr0_out", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process1", "UpdatedLP1state_benchn11", "UpdatedLP1state_benchr0_out", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.LP1state_benchr0_out = (1-((1-((1-((1-(_l.LP1state_benchr0_out)) * (_l.LP1state_benchn11))) * (1-(_l.IP1controllable_do_shift)))) * (1-((1-((1-((1-((1-((1-((1-(_l.LP1state_benchr0_out)) * (_l.LP1state_benchn11))) * (1-(_l.IP1sh0)))) * (1-(((_l.LP1state_benchr7_out) * (_l.LP1state_benchn11)) * (_l.IP1sh0))))) * (1-(_l.IP1sh2)))) * (1-((1-((1-(((_l.LP1state_benchr4_out) * (_l.LP1state_benchn11)) * (1-(_l.IP1sh0)))) * (1-(((_l.LP1state_benchr3_out) * (_l.LP1state_benchn11)) * (_l.IP1sh0))))) * (_l.IP1sh2))))) * (_l.IP1controllable_do_shift)))));;\
    }
    );
s.add_location("Process1", "UpdatedLP1state_benchr1_out", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process1", "UpdatedLP1state_benchr0_out", "UpdatedLP1state_benchr1_out", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.LP1state_benchr1_out = (1-((1-(((_l.LP1state_benchr1_out) * (_l.LP1state_benchn11)) * (1-(_l.IP1controllable_do_shift)))) * (1-((1-((1-((1-((1-(((_l.LP1state_benchr1_out) * (_l.LP1state_benchn11)) * (1-(_l.IP1sh0)))) * (1-((1-((1-(_l.LP1state_benchr0_out)) * (_l.LP1state_benchn11))) * (_l.IP1sh0))))) * (1-(_l.IP1sh2)))) * (1-((1-((1-(((_l.LP1state_benchr5_out) * (_l.LP1state_benchn11)) * (1-(_l.IP1sh0)))) * (1-(((_l.LP1state_benchr4_out) * (_l.LP1state_benchn11)) * (_l.IP1sh0))))) * (_l.IP1sh2))))) * (_l.IP1controllable_do_shift)))));;\
    }
    );
s.add_location("Process1", "UpdatedLP1state_benchr2_out", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process1", "UpdatedLP1state_benchr1_out", "UpdatedLP1state_benchr2_out", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.LP1state_benchr2_out = (1-((1-(((_l.LP1state_benchr2_out) * (_l.LP1state_benchn11)) * (1-(_l.IP1controllable_do_shift)))) * (1-((1-((1-((1-((1-(((_l.LP1state_benchr2_out) * (_l.LP1state_benchn11)) * (1-(_l.IP1sh0)))) * (1-(((_l.LP1state_benchr1_out) * (_l.LP1state_benchn11)) * (_l.IP1sh0))))) * (1-(_l.IP1sh2)))) * (1-((1-((1-(((_l.LP1state_benchr6_out) * (_l.LP1state_benchn11)) * (1-(_l.IP1sh0)))) * (1-(((_l.LP1state_benchr5_out) * (_l.LP1state_benchn11)) * (_l.IP1sh0))))) * (_l.IP1sh2))))) * (_l.IP1controllable_do_shift)))));;\
    }
    );
s.add_location("Process1", "UpdatedLP1state_benchr3_out", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process1", "UpdatedLP1state_benchr2_out", "UpdatedLP1state_benchr3_out", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.LP1state_benchr3_out = (1-((1-(((_l.LP1state_benchr3_out) * (_l.LP1state_benchn11)) * (1-(_l.IP1controllable_do_shift)))) * (1-((1-((1-((1-((1-(((_l.LP1state_benchr3_out) * (_l.LP1state_benchn11)) * (1-(_l.IP1sh0)))) * (1-(((_l.LP1state_benchr2_out) * (_l.LP1state_benchn11)) * (_l.IP1sh0))))) * (1-(_l.IP1sh2)))) * (1-((1-((1-(((_l.LP1state_benchr7_out) * (_l.LP1state_benchn11)) * (1-(_l.IP1sh0)))) * (1-(((_l.LP1state_benchr6_out) * (_l.LP1state_benchn11)) * (_l.IP1sh0))))) * (_l.IP1sh2))))) * (_l.IP1controllable_do_shift)))));;\
    }
    );
s.add_location("Process1", "UpdatedLP1state_benchr4_out", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process1", "UpdatedLP1state_benchr3_out", "UpdatedLP1state_benchr4_out", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.LP1state_benchr4_out = (1-((1-(((_l.LP1state_benchr4_out) * (_l.LP1state_benchn11)) * (1-(_l.IP1controllable_do_shift)))) * (1-((1-((1-((1-((1-(((_l.LP1state_benchr4_out) * (_l.LP1state_benchn11)) * (1-(_l.IP1sh0)))) * (1-(((_l.LP1state_benchr3_out) * (_l.LP1state_benchn11)) * (_l.IP1sh0))))) * (1-(_l.IP1sh2)))) * (1-((1-((1-((1-((1-(_l.LP1state_benchr0_out)) * (_l.LP1state_benchn11))) * (1-(_l.IP1sh0)))) * (1-(((_l.LP1state_benchr7_out) * (_l.LP1state_benchn11)) * (_l.IP1sh0))))) * (_l.IP1sh2))))) * (_l.IP1controllable_do_shift)))));;\
    }
    );
s.add_location("Process1", "UpdatedLP1state_benchr5_out", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process1", "UpdatedLP1state_benchr4_out", "UpdatedLP1state_benchr5_out", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.LP1state_benchr5_out = (1-((1-(((_l.LP1state_benchr5_out) * (_l.LP1state_benchn11)) * (1-(_l.IP1controllable_do_shift)))) * (1-((1-((1-((1-((1-(((_l.LP1state_benchr5_out) * (_l.LP1state_benchn11)) * (1-(_l.IP1sh0)))) * (1-(((_l.LP1state_benchr4_out) * (_l.LP1state_benchn11)) * (_l.IP1sh0))))) * (1-(_l.IP1sh2)))) * (1-((1-((1-(((_l.LP1state_benchr1_out) * (_l.LP1state_benchn11)) * (1-(_l.IP1sh0)))) * (1-((1-((1-(_l.LP1state_benchr0_out)) * (_l.LP1state_benchn11))) * (_l.IP1sh0))))) * (_l.IP1sh2))))) * (_l.IP1controllable_do_shift)))));;\
    }
    );
s.add_location("Process1", "UpdatedLP1state_benchr6_out", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process1", "UpdatedLP1state_benchr5_out", "UpdatedLP1state_benchr6_out", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.LP1state_benchr6_out = (1-((1-(((_l.LP1state_benchr6_out) * (_l.LP1state_benchn11)) * (1-(_l.IP1controllable_do_shift)))) * (1-((1-((1-((1-((1-(((_l.LP1state_benchr6_out) * (_l.LP1state_benchn11)) * (1-(_l.IP1sh0)))) * (1-(((_l.LP1state_benchr5_out) * (_l.LP1state_benchn11)) * (_l.IP1sh0))))) * (1-(_l.IP1sh2)))) * (1-((1-((1-(((_l.LP1state_benchr2_out) * (_l.LP1state_benchn11)) * (1-(_l.IP1sh0)))) * (1-(((_l.LP1state_benchr1_out) * (_l.LP1state_benchn11)) * (_l.IP1sh0))))) * (_l.IP1sh2))))) * (_l.IP1controllable_do_shift)))));;\
    }
    );
s.add_location("Process1", "UpdatedLP1state_benchr7_out", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process1", "UpdatedLP1state_benchr6_out", "UpdatedLP1state_benchr7_out", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.LP1state_benchr7_out = (1-((1-(((_l.LP1state_benchr7_out) * (_l.LP1state_benchn11)) * (1-(_l.IP1controllable_do_shift)))) * (1-((1-((1-((1-((1-(((_l.LP1state_benchr7_out) * (_l.LP1state_benchn11)) * (1-(_l.IP1sh0)))) * (1-(((_l.LP1state_benchr6_out) * (_l.LP1state_benchn11)) * (_l.IP1sh0))))) * (1-(_l.IP1sh2)))) * (1-((1-((1-(((_l.LP1state_benchr3_out) * (_l.LP1state_benchn11)) * (1-(_l.IP1sh0)))) * (1-(((_l.LP1state_benchr2_out) * (_l.LP1state_benchn11)) * (_l.IP1sh0))))) * (_l.IP1sh2))))) * (_l.IP1controllable_do_shift)))));;\
    }
    );
s.add_edge("Process1", "UpdatedLP1state_benchr7_out", "w", "", "", "release0!", 
    [](syntax::layout_t const & l){\
    multi::layout_t const & _l = CAST(multi::layout_t const &, l);\
    return _l.running0 == 1;\
    }
    ,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.w1 = 1;;\
    }
    );
s.add_edge("Process1", "UpdatedLP1state_benchr7_out", "w", "", "", "release1!", 
    [](syntax::layout_t const & l){\
    multi::layout_t const & _l = CAST(multi::layout_t const &, l);\
    return _l.running1 == 1;\
    }
    ,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.w1 = 1;;\
    }
    );
s.add_process("Process2");
s.add_location("Process2", "w", "", "", syntax::loc_t::INIT);
s.add_location("Process2", "dead", "", "err");
s.add_location("Process2", "rel", "", "", syntax::loc_t::COMMITTED);
s.add_location("Process2", "up", "", "", syntax::loc_t::COMMITTED);
s.add_location("Process2", "disc_up", "", "", syntax::loc_t::COMMITTED);
s.add_location("Process2", "on0", "x2 <= 1000","");
s.add_location("Process2", "on1", "x2 <= 800","");
s.add_edge("Process2", "w", "on0", "", "x2", "go2?", 
    [](syntax::layout_t const & l){\
    multi::layout_t const & _l = CAST(multi::layout_t const &, l);\
    return _l.LP2state_n15 == 0;\
    }
    ,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.w2 = 0;\
    }
    );
s.add_edge("Process2", "w", "dead", "x2 >= 1999", "", "", 
    [](syntax::layout_t const & l){\
    multi::layout_t const & _l = CAST(multi::layout_t const &, l);\
    return _l.LP2state_n15 == 0;\
    }
    ,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.dead=1;;\
    }
    );
s.add_edge("Process2", "on0", "up", "x2 >= 500 && x2 <= 1000", "x2", "", 
    [](syntax::layout_t const & l){\
    multi::layout_t const & _l = CAST(multi::layout_t const &, l);\
    return _l.LP2state_n15 == 0;\
    }
    );
s.add_edge("Process2", "w", "on1", "", "x2", "go2?", 
    [](syntax::layout_t const & l){\
    multi::layout_t const & _l = CAST(multi::layout_t const &, l);\
    return _l.LP2state_n15 == 1;\
    }
    ,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.w2 = 0;\
    }
    );
s.add_edge("Process2", "w", "dead", "x2 >= 2199", "", "", 
    [](syntax::layout_t const & l){\
    multi::layout_t const & _l = CAST(multi::layout_t const &, l);\
    return _l.LP2state_n15 == 1;\
    }
    ,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.dead=1;;\
    }
    );
s.add_edge("Process2", "on1", "up", "x2 >= 400 && x2 <= 800", "x2", "", 
    [](syntax::layout_t const & l){\
    multi::layout_t const & _l = CAST(multi::layout_t const &, l);\
    return _l.LP2state_n15 == 1;\
    }
    );
s.add_location("Process2", "JustSetIP2a_0_", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process2", "up", "JustSetIP2a_0_", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP2a_0_ = 0;;\
    }
    );
s.add_edge("Process2", "up", "JustSetIP2a_0_", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP2a_0_ = 1;;\
    }
    );
s.add_location("Process2", "JustSetIP2a_1_", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process2", "JustSetIP2a_0_", "JustSetIP2a_1_", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP2a_1_ = 0;;\
    }
    );
s.add_edge("Process2", "JustSetIP2a_0_", "JustSetIP2a_1_", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP2a_1_ = 1;;\
    }
    );
s.add_location("Process2", "JustSetIP2b_0_", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process2", "JustSetIP2a_1_", "JustSetIP2b_0_", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP2b_0_ = 0;;\
    }
    );
s.add_edge("Process2", "JustSetIP2a_1_", "JustSetIP2b_0_", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP2b_0_ = 1;;\
    }
    );
s.add_location("Process2", "JustSetIP2b_1_", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process2", "JustSetIP2b_0_", "JustSetIP2b_1_", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP2b_1_ = 0;;\
    }
    );
s.add_edge("Process2", "JustSetIP2b_0_", "JustSetIP2b_1_", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP2b_1_ = 1;;\
    }
    );
s.add_location("Process2", "JustSetIP2controllable_c_0_", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process2", "JustSetIP2b_1_", "JustSetIP2controllable_c_0_", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP2controllable_c_0_ = 0;;\
    }
    );
s.add_edge("Process2", "JustSetIP2b_1_", "JustSetIP2controllable_c_0_", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP2controllable_c_0_ = 1;;\
    }
    );
s.add_location("Process2", "JustSetIP2controllable_c_1_", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process2", "JustSetIP2controllable_c_0_", "JustSetIP2controllable_c_1_", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP2controllable_c_1_ = 0;;\
    }
    );
s.add_edge("Process2", "JustSetIP2controllable_c_0_", "JustSetIP2controllable_c_1_", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP2controllable_c_1_ = 1;;\
    }
    );
s.add_location("Process2", "UpdatedLP2state_n15", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process2", "JustSetIP2controllable_c_1_", "UpdatedLP2state_n15", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.LP2state_n15 = 1;;\
    }
    );
s.add_location("Process2", "UpdatedLP2err_out", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process2", "UpdatedLP2state_n15", "UpdatedLP2err_out", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.LP2err_out = (1-(((1-(((1-((1-((1-((1-(_l.IP2b_1_)) * (_l.IP2a_1_))) * (1-((_l.IP2b_1_) * (1-(_l.IP2a_1_)))))) * (1-((_l.IP2b_0_) * (_l.IP2a_0_))))) * (1-(((1-((1-(_l.IP2b_1_)) * (_l.IP2a_1_))) * (1-((_l.IP2b_1_) * (1-(_l.IP2a_1_))))) * ((_l.IP2b_0_) * (_l.IP2a_0_))))) * (_l.IP2controllable_c_1_))) * (1-((1-((1-((1-((1-((1-(_l.IP2b_1_)) * (_l.IP2a_1_))) * (1-((_l.IP2b_1_) * (1-(_l.IP2a_1_)))))) * (1-((_l.IP2b_0_) * (_l.IP2a_0_))))) * (1-(((1-((1-(_l.IP2b_1_)) * (_l.IP2a_1_))) * (1-((_l.IP2b_1_) * (1-(_l.IP2a_1_))))) * ((_l.IP2b_0_) * (_l.IP2a_0_)))))) * (1-(_l.IP2controllable_c_1_))))) * ((1-((1-((1-((1-(_l.IP2b_0_)) * (1-(_l.IP2a_0_)))) * (1-((_l.IP2b_0_) * (_l.IP2a_0_))))) * (_l.IP2controllable_c_0_))) * (1-(((1-((1-(_l.IP2b_0_)) * (1-(_l.IP2a_0_)))) * (1-((_l.IP2b_0_) * (_l.IP2a_0_)))) * (1-(_l.IP2controllable_c_0_)))))));;\
    }
    );
s.add_edge("Process2", "UpdatedLP2err_out", "w", "", "", "release0!", 
    [](syntax::layout_t const & l){\
    multi::layout_t const & _l = CAST(multi::layout_t const &, l);\
    return _l.running0 == 2;\
    }
    ,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.w2 = 1;;\
    }
    );
s.add_edge("Process2", "UpdatedLP2err_out", "w", "", "", "release1!", 
    [](syntax::layout_t const & l){\
    multi::layout_t const & _l = CAST(multi::layout_t const &, l);\
    return _l.running1 == 2;\
    }
    ,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.w2 = 1;;\
    }
    );
s.add_process("Machine0");
s.add_location("Machine0", "idle", "", "", syntax::loc_t::COMMITTED | syntax::loc_t::INIT);
s.add_location("Machine0", "busy", "","");
s.add_edge("Machine0", "busy", "idle", "", "", "release0?", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.running0 = 2;;\
    }
    );
s.add_edge("Machine0", "idle", "busy", "", "", "go0!", 
    [](syntax::layout_t const & l){\
    multi::layout_t const & _l = CAST(multi::layout_t const &, l);\
    return _l.round == 0 && _l.w0 == 1;\
    }
    ,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.round = 1; _l.running0 = 0; /*here?*/;\
    }
    );
s.add_edge("Machine0", "idle", "idle", "", "", "", 
    [](syntax::layout_t const & l){\
    multi::layout_t const & _l = CAST(multi::layout_t const &, l);\
    return _l.round == 0 && _l.w0 == 0;\
    }
    ,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.round = 1;;\
    }
    );
s.add_edge("Machine0", "idle", "busy", "", "", "go1!", 
    [](syntax::layout_t const & l){\
    multi::layout_t const & _l = CAST(multi::layout_t const &, l);\
    return _l.round == 1 && _l.w1 == 1;\
    }
    ,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.round = 2; _l.running0 = 1; /*here?*/;\
    }
    );
s.add_edge("Machine0", "idle", "idle", "", "", "", 
    [](syntax::layout_t const & l){\
    multi::layout_t const & _l = CAST(multi::layout_t const &, l);\
    return _l.round == 1 && _l.w1 == 0;\
    }
    ,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.round = 2;;\
    }
    );
s.add_edge("Machine0", "idle", "busy", "", "", "go2!", 
    [](syntax::layout_t const & l){\
    multi::layout_t const & _l = CAST(multi::layout_t const &, l);\
    return _l.round == 2 && _l.w2 == 1;\
    }
    ,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.round = 0; _l.running0 = 2; /*here?*/;\
    }
    );
s.add_edge("Machine0", "idle", "idle", "", "", "", 
    [](syntax::layout_t const & l){\
    multi::layout_t const & _l = CAST(multi::layout_t const &, l);\
    return _l.round == 2 && _l.w2 == 0;\
    }
    ,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.round = 0;;\
    }
    );
s.add_process("Machine1");
s.add_location("Machine1", "idle", "", "", syntax::loc_t::COMMITTED | syntax::loc_t::INIT);
s.add_location("Machine1", "busy", "","");
s.add_edge("Machine1", "busy", "idle", "", "", "release1?", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.running1 = 2;;\
    }
    );
s.add_edge("Machine1", "idle", "busy", "", "", "go0!", 
    [](syntax::layout_t const & l){\
    multi::layout_t const & _l = CAST(multi::layout_t const &, l);\
    return _l.round == 0 && _l.w0 == 1;\
    }
    ,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.round = 1; _l.running1 = 0; /*here?*/;\
    }
    );
s.add_edge("Machine1", "idle", "idle", "", "", "", 
    [](syntax::layout_t const & l){\
    multi::layout_t const & _l = CAST(multi::layout_t const &, l);\
    return _l.round == 0 && _l.w0 == 0;\
    }
    ,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.round = 1;;\
    }
    );
s.add_edge("Machine1", "idle", "busy", "", "", "go1!", 
    [](syntax::layout_t const & l){\
    multi::layout_t const & _l = CAST(multi::layout_t const &, l);\
    return _l.round == 1 && _l.w1 == 1;\
    }
    ,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.round = 2; _l.running1 = 1; /*here?*/;\
    }
    );
s.add_edge("Machine1", "idle", "idle", "", "", "", 
    [](syntax::layout_t const & l){\
    multi::layout_t const & _l = CAST(multi::layout_t const &, l);\
    return _l.round == 1 && _l.w1 == 0;\
    }
    ,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.round = 2;;\
    }
    );
s.add_edge("Machine1", "idle", "busy", "", "", "go2!", 
    [](syntax::layout_t const & l){\
    multi::layout_t const & _l = CAST(multi::layout_t const &, l);\
    return _l.round == 2 && _l.w2 == 1;\
    }
    ,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.round = 0; _l.running1 = 2; /*here?*/;\
    }
    );
s.add_edge("Machine1", "idle", "idle", "", "", "", 
    [](syntax::layout_t const & l){\
    multi::layout_t const & _l = CAST(multi::layout_t const &, l);\
    return _l.round == 2 && _l.w2 == 0;\
    }
    ,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.round = 0;;\
    }
    );
auto & sp = s.synchronizer<syntax::synchronized_product_t>(s);
sp.add_sync("Process0.release0!,Machine0.release0?");
sp.add_sync("Process0.go0?,Machine0.go0!");
sp.add_sync("Process0.release1!,Machine1.release1?");
sp.add_sync("Process0.go0?,Machine1.go0!");
sp.add_sync("Process1.release0!,Machine0.release0?");
sp.add_sync("Process1.go1?,Machine0.go1!");
sp.add_sync("Process1.release1!,Machine1.release1?");
sp.add_sync("Process1.go1?,Machine1.go1!");
sp.add_sync("Process2.release0!,Machine0.release0?");
sp.add_sync("Process2.go2?,Machine0.go2!");
sp.add_sync("Process2.release1!,Machine1.release1?");
sp.add_sync("Process2.go2?,Machine1.go2!");
}
