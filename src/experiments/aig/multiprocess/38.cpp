#include <iostream>
#include "syntax/system.hh"
#include "syntax/sync_product.hh"
namespace multi{
  class layout_t : public syntax::layout_t {
  public:
        
bool IP0in0;
bool IP0in1;
bool IP0in2;
bool IP0in3;
bool IP0controllable_c0;
bool IP0controllable_c1;
bool IP0controllable_c2;
bool IP0controllable_c3;
bool IP0controllable_s;
bool LP0benchn21;
bool LP0benchbad_out;
bool LP0benchstate0_out;
bool LP0benchstate1_out;
bool LP0benchstate2_out;
bool LP0benchstate3_out;
bool IP1a_0_;
bool IP1a_1_;
bool IP1b_0_;
bool IP1b_1_;
bool IP1controllable_c_0_;
bool IP1controllable_c_1_;
bool LP1state_n15;
bool LP1err_out;
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
        
IP0in0 =0;
IP0in1 =0;
IP0in2 =0;
IP0in3 =0;
IP0controllable_c0 =0;
IP0controllable_c1 =0;
IP0controllable_c2 =0;
IP0controllable_c3 =0;
IP0controllable_s =0;
LP0benchn21 =0;
LP0benchbad_out =0;
LP0benchstate0_out =0;
LP0benchstate1_out =0;
LP0benchstate2_out =0;
LP0benchstate3_out =0;
IP1a_0_ =0;
IP1a_1_ =0;
IP1b_0_ =0;
IP1b_1_ =0;
IP1controllable_c_0_ =0;
IP1controllable_c_1_ =0;
LP1state_n15 =0;
LP1err_out =0;
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
        
if (_l.IP0in0 != IP0in0) return false;
if (_l.IP0in1 != IP0in1) return false;
if (_l.IP0in2 != IP0in2) return false;
if (_l.IP0in3 != IP0in3) return false;
if (_l.IP0controllable_c0 != IP0controllable_c0) return false;
if (_l.IP0controllable_c1 != IP0controllable_c1) return false;
if (_l.IP0controllable_c2 != IP0controllable_c2) return false;
if (_l.IP0controllable_c3 != IP0controllable_c3) return false;
if (_l.IP0controllable_s != IP0controllable_s) return false;
if (_l.LP0benchn21 != LP0benchn21) return false;
if (_l.LP0benchbad_out != LP0benchbad_out) return false;
if (_l.LP0benchstate0_out != LP0benchstate0_out) return false;
if (_l.LP0benchstate1_out != LP0benchstate1_out) return false;
if (_l.LP0benchstate2_out != LP0benchstate2_out) return false;
if (_l.LP0benchstate3_out != LP0benchstate3_out) return false;

            if (_l.running0 != running0) return false;
            if (_l.running1 != running1) return false;
            if (_l.round != round) return false;
            if (_l.w0 != w0) return false;
            if (_l.w1 != w1) return false;
            if (_l.w2 != w2) return false;
            if (_l.dead != dead) return false;
            
if (_l.IP1a_0_ != IP1a_0_) return false;
if (_l.IP1a_1_ != IP1a_1_) return false;
if (_l.IP1b_0_ != IP1b_0_) return false;
if (_l.IP1b_1_ != IP1b_1_) return false;
if (_l.IP1controllable_c_0_ != IP1controllable_c_0_) return false;
if (_l.IP1controllable_c_1_ != IP1controllable_c_1_) return false;
if (_l.LP1state_n15 != LP1state_n15) return false;
if (_l.LP1err_out != LP1err_out) return false;

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
        
	boost::hash_combine(seed,IP0in0);
	boost::hash_combine(seed,IP0in1);
	boost::hash_combine(seed,IP0in2);
	boost::hash_combine(seed,IP0in3);
	boost::hash_combine(seed,IP0controllable_c0);
	boost::hash_combine(seed,IP0controllable_c1);
	boost::hash_combine(seed,IP0controllable_c2);
	boost::hash_combine(seed,IP0controllable_c3);
	boost::hash_combine(seed,IP0controllable_s);
	boost::hash_combine(seed,LP0benchn21);
	boost::hash_combine(seed,LP0benchbad_out);
	boost::hash_combine(seed,LP0benchstate0_out);
	boost::hash_combine(seed,LP0benchstate1_out);
	boost::hash_combine(seed,LP0benchstate2_out);
	boost::hash_combine(seed,LP0benchstate3_out);

            	boost::hash_combine(seed, running0);
            	boost::hash_combine(seed, running1);
            	boost::hash_combine(seed, round);
            	boost::hash_combine(seed, w0);
            	boost::hash_combine(seed, w1);
            	boost::hash_combine(seed, w2);
            	boost::hash_combine(seed, dead);
            
	boost::hash_combine(seed,IP1a_0_);
	boost::hash_combine(seed,IP1a_1_);
	boost::hash_combine(seed,IP1b_0_);
	boost::hash_combine(seed,IP1b_1_);
	boost::hash_combine(seed,IP1controllable_c_0_);
	boost::hash_combine(seed,IP1controllable_c_1_);
	boost::hash_combine(seed,LP1state_n15);
	boost::hash_combine(seed,LP1err_out);

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
s.add_location("Process0", "on1", "x0 <= 2000","");
s.add_edge("Process0", "w", "on0", "", "x0", "go0?", 
    [](syntax::layout_t const & l){\
    multi::layout_t const & _l = CAST(multi::layout_t const &, l);\
    return _l.LP0benchstate0_out == 0;\
    }
    ,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.w0 = 0;\
    }
    );
s.add_edge("Process0", "w", "dead", "x0 >= 8999", "", "", 
    [](syntax::layout_t const & l){\
    multi::layout_t const & _l = CAST(multi::layout_t const &, l);\
    return _l.LP0benchstate0_out == 0;\
    }
    ,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.dead=1;;\
    }
    );
s.add_edge("Process0", "on0", "up", "x0 >= 1000 && x0 <= 1000", "x0", "", 
    [](syntax::layout_t const & l){\
    multi::layout_t const & _l = CAST(multi::layout_t const &, l);\
    return _l.LP0benchstate0_out == 0;\
    }
    );
s.add_edge("Process0", "w", "on1", "", "x0", "go0?", 
    [](syntax::layout_t const & l){\
    multi::layout_t const & _l = CAST(multi::layout_t const &, l);\
    return _l.LP0benchstate0_out == 1;\
    }
    ,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.w0 = 0;\
    }
    );
s.add_edge("Process0", "w", "dead", "x0 >= 17999", "", "", 
    [](syntax::layout_t const & l){\
    multi::layout_t const & _l = CAST(multi::layout_t const &, l);\
    return _l.LP0benchstate0_out == 1;\
    }
    ,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.dead=1;;\
    }
    );
s.add_edge("Process0", "on1", "up", "x0 >= 2000 && x0 <= 2000", "x0", "", 
    [](syntax::layout_t const & l){\
    multi::layout_t const & _l = CAST(multi::layout_t const &, l);\
    return _l.LP0benchstate0_out == 1;\
    }
    );
s.add_location("Process0", "JustSetIP0in0", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process0", "up", "JustSetIP0in0", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP0in0 = 0;;\
    }
    );
s.add_edge("Process0", "up", "JustSetIP0in0", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP0in0 = 1;;\
    }
    );
s.add_location("Process0", "JustSetIP0in1", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process0", "JustSetIP0in0", "JustSetIP0in1", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP0in1 = 0;;\
    }
    );
s.add_edge("Process0", "JustSetIP0in0", "JustSetIP0in1", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP0in1 = 1;;\
    }
    );
s.add_location("Process0", "JustSetIP0in2", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process0", "JustSetIP0in1", "JustSetIP0in2", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP0in2 = 0;;\
    }
    );
s.add_edge("Process0", "JustSetIP0in1", "JustSetIP0in2", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP0in2 = 1;;\
    }
    );
s.add_location("Process0", "JustSetIP0in3", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process0", "JustSetIP0in2", "JustSetIP0in3", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP0in3 = 0;;\
    }
    );
s.add_edge("Process0", "JustSetIP0in2", "JustSetIP0in3", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP0in3 = 1;;\
    }
    );
s.add_location("Process0", "JustSetIP0controllable_c0", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process0", "JustSetIP0in3", "JustSetIP0controllable_c0", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP0controllable_c0 = 0;;\
    }
    );
s.add_edge("Process0", "JustSetIP0in3", "JustSetIP0controllable_c0", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP0controllable_c0 = 1;;\
    }
    );
s.add_location("Process0", "JustSetIP0controllable_c1", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process0", "JustSetIP0controllable_c0", "JustSetIP0controllable_c1", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP0controllable_c1 = 0;;\
    }
    );
s.add_edge("Process0", "JustSetIP0controllable_c0", "JustSetIP0controllable_c1", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP0controllable_c1 = 1;;\
    }
    );
s.add_location("Process0", "JustSetIP0controllable_c2", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process0", "JustSetIP0controllable_c1", "JustSetIP0controllable_c2", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP0controllable_c2 = 0;;\
    }
    );
s.add_edge("Process0", "JustSetIP0controllable_c1", "JustSetIP0controllable_c2", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP0controllable_c2 = 1;;\
    }
    );
s.add_location("Process0", "JustSetIP0controllable_c3", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process0", "JustSetIP0controllable_c2", "JustSetIP0controllable_c3", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP0controllable_c3 = 0;;\
    }
    );
s.add_edge("Process0", "JustSetIP0controllable_c2", "JustSetIP0controllable_c3", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP0controllable_c3 = 1;;\
    }
    );
s.add_location("Process0", "JustSetIP0controllable_s", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process0", "JustSetIP0controllable_c3", "JustSetIP0controllable_s", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP0controllable_s = 0;;\
    }
    );
s.add_edge("Process0", "JustSetIP0controllable_c3", "JustSetIP0controllable_s", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP0controllable_s = 1;;\
    }
    );
s.add_location("Process0", "UpdatedLP0benchn21", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process0", "JustSetIP0controllable_s", "UpdatedLP0benchn21", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.LP0benchn21 = 1;;\
    }
    );
s.add_location("Process0", "UpdatedLP0benchbad_out", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process0", "UpdatedLP0benchn21", "UpdatedLP0benchbad_out", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.LP0benchbad_out = (1-((1-((_l.LP0benchbad_out) * (_l.LP0benchn21))) * (1-(_l.IP0controllable_s))));;\
    }
    );
s.add_location("Process0", "UpdatedLP0benchstate0_out", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process0", "UpdatedLP0benchbad_out", "UpdatedLP0benchstate0_out", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.LP0benchstate0_out = ((1-((((1-((1-(((1-((1-((1-(_l.IP0controllable_c1)) * (1-(_l.IP0controllable_c0)))) * (_l.IP0controllable_c3))) * (1-(_l.IP0in1))) * (1-(_l.IP0in2)))) * (1-((1-((1-(((1-(_l.IP0in2)) * (1-(_l.IP0controllable_c1))) * ((_l.IP0in1) * (_l.IP0controllable_c0)))) * (1-(((1-((1-((1-(_l.IP0in1)) * (1-(_l.IP0controllable_c0)))) * (1-((_l.IP0in1) * (_l.IP0controllable_c0))))) * (_l.IP0controllable_c1)) * (_l.IP0in2))))) * (_l.IP0controllable_c3))))) * (1-(_l.IP0in0))) * ((1-(((1-((1-(((1-(((1-(((_l.IP0in1) * (_l.IP0controllable_c1)) * ((_l.IP0in2) * (_l.IP0controllable_c0)))) * (1-((1-((_l.IP0in1) * (_l.IP0controllable_c1))) * (1-((_l.IP0in2) * (_l.IP0controllable_c0)))))) * (((_l.IP0in0) * (_l.IP0controllable_c1)) * ((_l.IP0in1) * (_l.IP0controllable_c0))))) * (1-((1-((1-(((_l.IP0in1) * (_l.IP0controllable_c1)) * ((_l.IP0in2) * (_l.IP0controllable_c0)))) * (1-((1-((_l.IP0in1) * (_l.IP0controllable_c1))) * (1-((_l.IP0in2) * (_l.IP0controllable_c0))))))) * (1-(((_l.IP0in0) * (_l.IP0controllable_c1)) * ((_l.IP0in1) * (_l.IP0controllable_c0))))))) * (1-(_l.IP0controllable_c3)))) * ((1-((1-(_l.IP0in0)) * (1-(_l.IP0controllable_c3)))) * (_l.IP0controllable_c2)))) * (1-((((1-(((1-(((_l.IP0in1) * (_l.IP0controllable_c1)) * ((_l.IP0in2) * (_l.IP0controllable_c0)))) * (1-((1-((_l.IP0in1) * (_l.IP0controllable_c1))) * (1-((_l.IP0in2) * (_l.IP0controllable_c0)))))) * (((_l.IP0in0) * (_l.IP0controllable_c1)) * ((_l.IP0in1) * (_l.IP0controllable_c0))))) * (1-((1-((1-(((_l.IP0in1) * (_l.IP0controllable_c1)) * ((_l.IP0in2) * (_l.IP0controllable_c0)))) * (1-((1-((_l.IP0in1) * (_l.IP0controllable_c1))) * (1-((_l.IP0in2) * (_l.IP0controllable_c0))))))) * (1-(((_l.IP0in0) * (_l.IP0controllable_c1)) * ((_l.IP0in1) * (_l.IP0controllable_c0))))))) * (1-(_l.IP0controllable_c3))) * (1-((1-((1-(_l.IP0in0)) * (1-(_l.IP0controllable_c3)))) * (_l.IP0controllable_c2)))))) * (_l.IP0in3))) * (1-((1-((1-((1-(((1-(((1-(((_l.IP0in1) * (_l.IP0controllable_c1)) * ((_l.IP0in2) * (_l.IP0controllable_c0)))) * (1-((1-((_l.IP0in1) * (_l.IP0controllable_c1))) * (1-((_l.IP0in2) * (_l.IP0controllable_c0)))))) * (((_l.IP0in0) * (_l.IP0controllable_c1)) * ((_l.IP0in1) * (_l.IP0controllable_c0))))) * (1-((1-((1-(((_l.IP0in1) * (_l.IP0controllable_c1)) * ((_l.IP0in2) * (_l.IP0controllable_c0)))) * (1-((1-((_l.IP0in1) * (_l.IP0controllable_c1))) * (1-((_l.IP0in2) * (_l.IP0controllable_c0))))))) * (1-(((_l.IP0in0) * (_l.IP0controllable_c1)) * ((_l.IP0in1) * (_l.IP0controllable_c0))))))) * (1-(_l.IP0controllable_c3)))) * ((1-((1-(_l.IP0in0)) * (1-(_l.IP0controllable_c3)))) * (_l.IP0controllable_c2)))) * (1-((((1-(((1-(((_l.IP0in1) * (_l.IP0controllable_c1)) * ((_l.IP0in2) * (_l.IP0controllable_c0)))) * (1-((1-((_l.IP0in1) * (_l.IP0controllable_c1))) * (1-((_l.IP0in2) * (_l.IP0controllable_c0)))))) * (((_l.IP0in0) * (_l.IP0controllable_c1)) * ((_l.IP0in1) * (_l.IP0controllable_c0))))) * (1-((1-((1-(((_l.IP0in1) * (_l.IP0controllable_c1)) * ((_l.IP0in2) * (_l.IP0controllable_c0)))) * (1-((1-((_l.IP0in1) * (_l.IP0controllable_c1))) * (1-((_l.IP0in2) * (_l.IP0controllable_c0))))))) * (1-(((_l.IP0in0) * (_l.IP0controllable_c1)) * ((_l.IP0in1) * (_l.IP0controllable_c0))))))) * (1-(_l.IP0controllable_c3))) * (1-((1-((1-(_l.IP0in0)) * (1-(_l.IP0controllable_c3)))) * (_l.IP0controllable_c2))))))) * (1-(_l.IP0in3)))))) * (1-((_l.LP0benchstate0_out) * (_l.LP0benchn21))))) * (1-((1-(((1-((1-(((1-((1-((1-(_l.IP0controllable_c1)) * (1-(_l.IP0controllable_c0)))) * (_l.IP0controllable_c3))) * (1-(_l.IP0in1))) * (1-(_l.IP0in2)))) * (1-((1-((1-(((1-(_l.IP0in2)) * (1-(_l.IP0controllable_c1))) * ((_l.IP0in1) * (_l.IP0controllable_c0)))) * (1-(((1-((1-((1-(_l.IP0in1)) * (1-(_l.IP0controllable_c0)))) * (1-((_l.IP0in1) * (_l.IP0controllable_c0))))) * (_l.IP0controllable_c1)) * (_l.IP0in2))))) * (_l.IP0controllable_c3))))) * (1-(_l.IP0in0))) * ((1-(((1-((1-(((1-(((1-(((_l.IP0in1) * (_l.IP0controllable_c1)) * ((_l.IP0in2) * (_l.IP0controllable_c0)))) * (1-((1-((_l.IP0in1) * (_l.IP0controllable_c1))) * (1-((_l.IP0in2) * (_l.IP0controllable_c0)))))) * (((_l.IP0in0) * (_l.IP0controllable_c1)) * ((_l.IP0in1) * (_l.IP0controllable_c0))))) * (1-((1-((1-(((_l.IP0in1) * (_l.IP0controllable_c1)) * ((_l.IP0in2) * (_l.IP0controllable_c0)))) * (1-((1-((_l.IP0in1) * (_l.IP0controllable_c1))) * (1-((_l.IP0in2) * (_l.IP0controllable_c0))))))) * (1-(((_l.IP0in0) * (_l.IP0controllable_c1)) * ((_l.IP0in1) * (_l.IP0controllable_c0))))))) * (1-(_l.IP0controllable_c3)))) * ((1-((1-(_l.IP0in0)) * (1-(_l.IP0controllable_c3)))) * (_l.IP0controllable_c2)))) * (1-((((1-(((1-(((_l.IP0in1) * (_l.IP0controllable_c1)) * ((_l.IP0in2) * (_l.IP0controllable_c0)))) * (1-((1-((_l.IP0in1) * (_l.IP0controllable_c1))) * (1-((_l.IP0in2) * (_l.IP0controllable_c0)))))) * (((_l.IP0in0) * (_l.IP0controllable_c1)) * ((_l.IP0in1) * (_l.IP0controllable_c0))))) * (1-((1-((1-(((_l.IP0in1) * (_l.IP0controllable_c1)) * ((_l.IP0in2) * (_l.IP0controllable_c0)))) * (1-((1-((_l.IP0in1) * (_l.IP0controllable_c1))) * (1-((_l.IP0in2) * (_l.IP0controllable_c0))))))) * (1-(((_l.IP0in0) * (_l.IP0controllable_c1)) * ((_l.IP0in1) * (_l.IP0controllable_c0))))))) * (1-(_l.IP0controllable_c3))) * (1-((1-((1-(_l.IP0in0)) * (1-(_l.IP0controllable_c3)))) * (_l.IP0controllable_c2)))))) * (_l.IP0in3))) * (1-((1-((1-((1-(((1-(((1-(((_l.IP0in1) * (_l.IP0controllable_c1)) * ((_l.IP0in2) * (_l.IP0controllable_c0)))) * (1-((1-((_l.IP0in1) * (_l.IP0controllable_c1))) * (1-((_l.IP0in2) * (_l.IP0controllable_c0)))))) * (((_l.IP0in0) * (_l.IP0controllable_c1)) * ((_l.IP0in1) * (_l.IP0controllable_c0))))) * (1-((1-((1-(((_l.IP0in1) * (_l.IP0controllable_c1)) * ((_l.IP0in2) * (_l.IP0controllable_c0)))) * (1-((1-((_l.IP0in1) * (_l.IP0controllable_c1))) * (1-((_l.IP0in2) * (_l.IP0controllable_c0))))))) * (1-(((_l.IP0in0) * (_l.IP0controllable_c1)) * ((_l.IP0in1) * (_l.IP0controllable_c0))))))) * (1-(_l.IP0controllable_c3)))) * ((1-((1-(_l.IP0in0)) * (1-(_l.IP0controllable_c3)))) * (_l.IP0controllable_c2)))) * (1-((((1-(((1-(((_l.IP0in1) * (_l.IP0controllable_c1)) * ((_l.IP0in2) * (_l.IP0controllable_c0)))) * (1-((1-((_l.IP0in1) * (_l.IP0controllable_c1))) * (1-((_l.IP0in2) * (_l.IP0controllable_c0)))))) * (((_l.IP0in0) * (_l.IP0controllable_c1)) * ((_l.IP0in1) * (_l.IP0controllable_c0))))) * (1-((1-((1-(((_l.IP0in1) * (_l.IP0controllable_c1)) * ((_l.IP0in2) * (_l.IP0controllable_c0)))) * (1-((1-((_l.IP0in1) * (_l.IP0controllable_c1))) * (1-((_l.IP0in2) * (_l.IP0controllable_c0))))))) * (1-(((_l.IP0in0) * (_l.IP0controllable_c1)) * ((_l.IP0in1) * (_l.IP0controllable_c0))))))) * (1-(_l.IP0controllable_c3))) * (1-((1-((1-(_l.IP0in0)) * (1-(_l.IP0controllable_c3)))) * (_l.IP0controllable_c2))))))) * (1-(_l.IP0in3))))))) * ((_l.LP0benchstate0_out) * (_l.LP0benchn21)))));;\
    }
    );
s.add_location("Process0", "UpdatedLP0benchstate1_out", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process0", "UpdatedLP0benchstate0_out", "UpdatedLP0benchstate1_out", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.LP0benchstate1_out = ((1-((1-((1-(((1-((1-(((1-((1-((1-(_l.IP0controllable_c1)) * (1-(_l.IP0controllable_c0)))) * (_l.IP0controllable_c3))) * (1-(_l.IP0in1))) * (1-(_l.IP0in2)))) * (1-((1-((1-(((1-(_l.IP0in2)) * (1-(_l.IP0controllable_c1))) * ((_l.IP0in1) * (_l.IP0controllable_c0)))) * (1-(((1-((1-((1-(_l.IP0in1)) * (1-(_l.IP0controllable_c0)))) * (1-((_l.IP0in1) * (_l.IP0controllable_c0))))) * (_l.IP0controllable_c1)) * (_l.IP0in2))))) * (_l.IP0controllable_c3))))) * (1-(_l.IP0in0))) * ((1-(((1-((1-(((1-(((1-(((_l.IP0in1) * (_l.IP0controllable_c1)) * ((_l.IP0in2) * (_l.IP0controllable_c0)))) * (1-((1-((_l.IP0in1) * (_l.IP0controllable_c1))) * (1-((_l.IP0in2) * (_l.IP0controllable_c0)))))) * (((_l.IP0in0) * (_l.IP0controllable_c1)) * ((_l.IP0in1) * (_l.IP0controllable_c0))))) * (1-((1-((1-(((_l.IP0in1) * (_l.IP0controllable_c1)) * ((_l.IP0in2) * (_l.IP0controllable_c0)))) * (1-((1-((_l.IP0in1) * (_l.IP0controllable_c1))) * (1-((_l.IP0in2) * (_l.IP0controllable_c0))))))) * (1-(((_l.IP0in0) * (_l.IP0controllable_c1)) * ((_l.IP0in1) * (_l.IP0controllable_c0))))))) * (1-(_l.IP0controllable_c3)))) * ((1-((1-(_l.IP0in0)) * (1-(_l.IP0controllable_c3)))) * (_l.IP0controllable_c2)))) * (1-((((1-(((1-(((_l.IP0in1) * (_l.IP0controllable_c1)) * ((_l.IP0in2) * (_l.IP0controllable_c0)))) * (1-((1-((_l.IP0in1) * (_l.IP0controllable_c1))) * (1-((_l.IP0in2) * (_l.IP0controllable_c0)))))) * (((_l.IP0in0) * (_l.IP0controllable_c1)) * ((_l.IP0in1) * (_l.IP0controllable_c0))))) * (1-((1-((1-(((_l.IP0in1) * (_l.IP0controllable_c1)) * ((_l.IP0in2) * (_l.IP0controllable_c0)))) * (1-((1-((_l.IP0in1) * (_l.IP0controllable_c1))) * (1-((_l.IP0in2) * (_l.IP0controllable_c0))))))) * (1-(((_l.IP0in0) * (_l.IP0controllable_c1)) * ((_l.IP0in1) * (_l.IP0controllable_c0))))))) * (1-(_l.IP0controllable_c3))) * (1-((1-((1-(_l.IP0in0)) * (1-(_l.IP0controllable_c3)))) * (_l.IP0controllable_c2)))))) * (_l.IP0in3))) * (1-((1-((1-((1-(((1-(((1-(((_l.IP0in1) * (_l.IP0controllable_c1)) * ((_l.IP0in2) * (_l.IP0controllable_c0)))) * (1-((1-((_l.IP0in1) * (_l.IP0controllable_c1))) * (1-((_l.IP0in2) * (_l.IP0controllable_c0)))))) * (((_l.IP0in0) * (_l.IP0controllable_c1)) * ((_l.IP0in1) * (_l.IP0controllable_c0))))) * (1-((1-((1-(((_l.IP0in1) * (_l.IP0controllable_c1)) * ((_l.IP0in2) * (_l.IP0controllable_c0)))) * (1-((1-((_l.IP0in1) * (_l.IP0controllable_c1))) * (1-((_l.IP0in2) * (_l.IP0controllable_c0))))))) * (1-(((_l.IP0in0) * (_l.IP0controllable_c1)) * ((_l.IP0in1) * (_l.IP0controllable_c0))))))) * (1-(_l.IP0controllable_c3)))) * ((1-((1-(_l.IP0in0)) * (1-(_l.IP0controllable_c3)))) * (_l.IP0controllable_c2)))) * (1-((((1-(((1-(((_l.IP0in1) * (_l.IP0controllable_c1)) * ((_l.IP0in2) * (_l.IP0controllable_c0)))) * (1-((1-((_l.IP0in1) * (_l.IP0controllable_c1))) * (1-((_l.IP0in2) * (_l.IP0controllable_c0)))))) * (((_l.IP0in0) * (_l.IP0controllable_c1)) * ((_l.IP0in1) * (_l.IP0controllable_c0))))) * (1-((1-((1-(((_l.IP0in1) * (_l.IP0controllable_c1)) * ((_l.IP0in2) * (_l.IP0controllable_c0)))) * (1-((1-((_l.IP0in1) * (_l.IP0controllable_c1))) * (1-((_l.IP0in2) * (_l.IP0controllable_c0))))))) * (1-(((_l.IP0in0) * (_l.IP0controllable_c1)) * ((_l.IP0in1) * (_l.IP0controllable_c0))))))) * (1-(_l.IP0controllable_c3))) * (1-((1-((1-(_l.IP0in0)) * (1-(_l.IP0controllable_c3)))) * (_l.IP0controllable_c2))))))) * (1-(_l.IP0in3))))))) * ((_l.LP0benchstate0_out) * (_l.LP0benchn21)))) * (1-((_l.LP0benchstate1_out) * (_l.LP0benchn21))))) * (1-(((1-(((1-((1-(((1-((1-((1-(_l.IP0controllable_c1)) * (1-(_l.IP0controllable_c0)))) * (_l.IP0controllable_c3))) * (1-(_l.IP0in1))) * (1-(_l.IP0in2)))) * (1-((1-((1-(((1-(_l.IP0in2)) * (1-(_l.IP0controllable_c1))) * ((_l.IP0in1) * (_l.IP0controllable_c0)))) * (1-(((1-((1-((1-(_l.IP0in1)) * (1-(_l.IP0controllable_c0)))) * (1-((_l.IP0in1) * (_l.IP0controllable_c0))))) * (_l.IP0controllable_c1)) * (_l.IP0in2))))) * (_l.IP0controllable_c3))))) * (1-(_l.IP0in0))) * ((1-(((1-((1-(((1-(((1-(((_l.IP0in1) * (_l.IP0controllable_c1)) * ((_l.IP0in2) * (_l.IP0controllable_c0)))) * (1-((1-((_l.IP0in1) * (_l.IP0controllable_c1))) * (1-((_l.IP0in2) * (_l.IP0controllable_c0)))))) * (((_l.IP0in0) * (_l.IP0controllable_c1)) * ((_l.IP0in1) * (_l.IP0controllable_c0))))) * (1-((1-((1-(((_l.IP0in1) * (_l.IP0controllable_c1)) * ((_l.IP0in2) * (_l.IP0controllable_c0)))) * (1-((1-((_l.IP0in1) * (_l.IP0controllable_c1))) * (1-((_l.IP0in2) * (_l.IP0controllable_c0))))))) * (1-(((_l.IP0in0) * (_l.IP0controllable_c1)) * ((_l.IP0in1) * (_l.IP0controllable_c0))))))) * (1-(_l.IP0controllable_c3)))) * ((1-((1-(_l.IP0in0)) * (1-(_l.IP0controllable_c3)))) * (_l.IP0controllable_c2)))) * (1-((((1-(((1-(((_l.IP0in1) * (_l.IP0controllable_c1)) * ((_l.IP0in2) * (_l.IP0controllable_c0)))) * (1-((1-((_l.IP0in1) * (_l.IP0controllable_c1))) * (1-((_l.IP0in2) * (_l.IP0controllable_c0)))))) * (((_l.IP0in0) * (_l.IP0controllable_c1)) * ((_l.IP0in1) * (_l.IP0controllable_c0))))) * (1-((1-((1-(((_l.IP0in1) * (_l.IP0controllable_c1)) * ((_l.IP0in2) * (_l.IP0controllable_c0)))) * (1-((1-((_l.IP0in1) * (_l.IP0controllable_c1))) * (1-((_l.IP0in2) * (_l.IP0controllable_c0))))))) * (1-(((_l.IP0in0) * (_l.IP0controllable_c1)) * ((_l.IP0in1) * (_l.IP0controllable_c0))))))) * (1-(_l.IP0controllable_c3))) * (1-((1-((1-(_l.IP0in0)) * (1-(_l.IP0controllable_c3)))) * (_l.IP0controllable_c2)))))) * (_l.IP0in3))) * (1-((1-((1-((1-(((1-(((1-(((_l.IP0in1) * (_l.IP0controllable_c1)) * ((_l.IP0in2) * (_l.IP0controllable_c0)))) * (1-((1-((_l.IP0in1) * (_l.IP0controllable_c1))) * (1-((_l.IP0in2) * (_l.IP0controllable_c0)))))) * (((_l.IP0in0) * (_l.IP0controllable_c1)) * ((_l.IP0in1) * (_l.IP0controllable_c0))))) * (1-((1-((1-(((_l.IP0in1) * (_l.IP0controllable_c1)) * ((_l.IP0in2) * (_l.IP0controllable_c0)))) * (1-((1-((_l.IP0in1) * (_l.IP0controllable_c1))) * (1-((_l.IP0in2) * (_l.IP0controllable_c0))))))) * (1-(((_l.IP0in0) * (_l.IP0controllable_c1)) * ((_l.IP0in1) * (_l.IP0controllable_c0))))))) * (1-(_l.IP0controllable_c3)))) * ((1-((1-(_l.IP0in0)) * (1-(_l.IP0controllable_c3)))) * (_l.IP0controllable_c2)))) * (1-((((1-(((1-(((_l.IP0in1) * (_l.IP0controllable_c1)) * ((_l.IP0in2) * (_l.IP0controllable_c0)))) * (1-((1-((_l.IP0in1) * (_l.IP0controllable_c1))) * (1-((_l.IP0in2) * (_l.IP0controllable_c0)))))) * (((_l.IP0in0) * (_l.IP0controllable_c1)) * ((_l.IP0in1) * (_l.IP0controllable_c0))))) * (1-((1-((1-(((_l.IP0in1) * (_l.IP0controllable_c1)) * ((_l.IP0in2) * (_l.IP0controllable_c0)))) * (1-((1-((_l.IP0in1) * (_l.IP0controllable_c1))) * (1-((_l.IP0in2) * (_l.IP0controllable_c0))))))) * (1-(((_l.IP0in0) * (_l.IP0controllable_c1)) * ((_l.IP0in1) * (_l.IP0controllable_c0))))))) * (1-(_l.IP0controllable_c3))) * (1-((1-((1-(_l.IP0in0)) * (1-(_l.IP0controllable_c3)))) * (_l.IP0controllable_c2))))))) * (1-(_l.IP0in3))))))) * ((_l.LP0benchstate0_out) * (_l.LP0benchn21))) * ((_l.LP0benchstate1_out) * (_l.LP0benchn21)))));;\
    }
    );
s.add_location("Process0", "UpdatedLP0benchstate2_out", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process0", "UpdatedLP0benchstate1_out", "UpdatedLP0benchstate2_out", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.LP0benchstate2_out = ((1-((1-(((1-(((1-((1-(((1-((1-((1-(_l.IP0controllable_c1)) * (1-(_l.IP0controllable_c0)))) * (_l.IP0controllable_c3))) * (1-(_l.IP0in1))) * (1-(_l.IP0in2)))) * (1-((1-((1-(((1-(_l.IP0in2)) * (1-(_l.IP0controllable_c1))) * ((_l.IP0in1) * (_l.IP0controllable_c0)))) * (1-(((1-((1-((1-(_l.IP0in1)) * (1-(_l.IP0controllable_c0)))) * (1-((_l.IP0in1) * (_l.IP0controllable_c0))))) * (_l.IP0controllable_c1)) * (_l.IP0in2))))) * (_l.IP0controllable_c3))))) * (1-(_l.IP0in0))) * ((1-(((1-((1-(((1-(((1-(((_l.IP0in1) * (_l.IP0controllable_c1)) * ((_l.IP0in2) * (_l.IP0controllable_c0)))) * (1-((1-((_l.IP0in1) * (_l.IP0controllable_c1))) * (1-((_l.IP0in2) * (_l.IP0controllable_c0)))))) * (((_l.IP0in0) * (_l.IP0controllable_c1)) * ((_l.IP0in1) * (_l.IP0controllable_c0))))) * (1-((1-((1-(((_l.IP0in1) * (_l.IP0controllable_c1)) * ((_l.IP0in2) * (_l.IP0controllable_c0)))) * (1-((1-((_l.IP0in1) * (_l.IP0controllable_c1))) * (1-((_l.IP0in2) * (_l.IP0controllable_c0))))))) * (1-(((_l.IP0in0) * (_l.IP0controllable_c1)) * ((_l.IP0in1) * (_l.IP0controllable_c0))))))) * (1-(_l.IP0controllable_c3)))) * ((1-((1-(_l.IP0in0)) * (1-(_l.IP0controllable_c3)))) * (_l.IP0controllable_c2)))) * (1-((((1-(((1-(((_l.IP0in1) * (_l.IP0controllable_c1)) * ((_l.IP0in2) * (_l.IP0controllable_c0)))) * (1-((1-((_l.IP0in1) * (_l.IP0controllable_c1))) * (1-((_l.IP0in2) * (_l.IP0controllable_c0)))))) * (((_l.IP0in0) * (_l.IP0controllable_c1)) * ((_l.IP0in1) * (_l.IP0controllable_c0))))) * (1-((1-((1-(((_l.IP0in1) * (_l.IP0controllable_c1)) * ((_l.IP0in2) * (_l.IP0controllable_c0)))) * (1-((1-((_l.IP0in1) * (_l.IP0controllable_c1))) * (1-((_l.IP0in2) * (_l.IP0controllable_c0))))))) * (1-(((_l.IP0in0) * (_l.IP0controllable_c1)) * ((_l.IP0in1) * (_l.IP0controllable_c0))))))) * (1-(_l.IP0controllable_c3))) * (1-((1-((1-(_l.IP0in0)) * (1-(_l.IP0controllable_c3)))) * (_l.IP0controllable_c2)))))) * (_l.IP0in3))) * (1-((1-((1-((1-(((1-(((1-(((_l.IP0in1) * (_l.IP0controllable_c1)) * ((_l.IP0in2) * (_l.IP0controllable_c0)))) * (1-((1-((_l.IP0in1) * (_l.IP0controllable_c1))) * (1-((_l.IP0in2) * (_l.IP0controllable_c0)))))) * (((_l.IP0in0) * (_l.IP0controllable_c1)) * ((_l.IP0in1) * (_l.IP0controllable_c0))))) * (1-((1-((1-(((_l.IP0in1) * (_l.IP0controllable_c1)) * ((_l.IP0in2) * (_l.IP0controllable_c0)))) * (1-((1-((_l.IP0in1) * (_l.IP0controllable_c1))) * (1-((_l.IP0in2) * (_l.IP0controllable_c0))))))) * (1-(((_l.IP0in0) * (_l.IP0controllable_c1)) * ((_l.IP0in1) * (_l.IP0controllable_c0))))))) * (1-(_l.IP0controllable_c3)))) * ((1-((1-(_l.IP0in0)) * (1-(_l.IP0controllable_c3)))) * (_l.IP0controllable_c2)))) * (1-((((1-(((1-(((_l.IP0in1) * (_l.IP0controllable_c1)) * ((_l.IP0in2) * (_l.IP0controllable_c0)))) * (1-((1-((_l.IP0in1) * (_l.IP0controllable_c1))) * (1-((_l.IP0in2) * (_l.IP0controllable_c0)))))) * (((_l.IP0in0) * (_l.IP0controllable_c1)) * ((_l.IP0in1) * (_l.IP0controllable_c0))))) * (1-((1-((1-(((_l.IP0in1) * (_l.IP0controllable_c1)) * ((_l.IP0in2) * (_l.IP0controllable_c0)))) * (1-((1-((_l.IP0in1) * (_l.IP0controllable_c1))) * (1-((_l.IP0in2) * (_l.IP0controllable_c0))))))) * (1-(((_l.IP0in0) * (_l.IP0controllable_c1)) * ((_l.IP0in1) * (_l.IP0controllable_c0))))))) * (1-(_l.IP0controllable_c3))) * (1-((1-((1-(_l.IP0in0)) * (1-(_l.IP0controllable_c3)))) * (_l.IP0controllable_c2))))))) * (1-(_l.IP0in3))))))) * ((_l.LP0benchstate0_out) * (_l.LP0benchn21))) * ((_l.LP0benchstate1_out) * (_l.LP0benchn21)))) * (1-((_l.LP0benchstate2_out) * (_l.LP0benchn21))))) * (1-((((1-(((1-((1-(((1-((1-((1-(_l.IP0controllable_c1)) * (1-(_l.IP0controllable_c0)))) * (_l.IP0controllable_c3))) * (1-(_l.IP0in1))) * (1-(_l.IP0in2)))) * (1-((1-((1-(((1-(_l.IP0in2)) * (1-(_l.IP0controllable_c1))) * ((_l.IP0in1) * (_l.IP0controllable_c0)))) * (1-(((1-((1-((1-(_l.IP0in1)) * (1-(_l.IP0controllable_c0)))) * (1-((_l.IP0in1) * (_l.IP0controllable_c0))))) * (_l.IP0controllable_c1)) * (_l.IP0in2))))) * (_l.IP0controllable_c3))))) * (1-(_l.IP0in0))) * ((1-(((1-((1-(((1-(((1-(((_l.IP0in1) * (_l.IP0controllable_c1)) * ((_l.IP0in2) * (_l.IP0controllable_c0)))) * (1-((1-((_l.IP0in1) * (_l.IP0controllable_c1))) * (1-((_l.IP0in2) * (_l.IP0controllable_c0)))))) * (((_l.IP0in0) * (_l.IP0controllable_c1)) * ((_l.IP0in1) * (_l.IP0controllable_c0))))) * (1-((1-((1-(((_l.IP0in1) * (_l.IP0controllable_c1)) * ((_l.IP0in2) * (_l.IP0controllable_c0)))) * (1-((1-((_l.IP0in1) * (_l.IP0controllable_c1))) * (1-((_l.IP0in2) * (_l.IP0controllable_c0))))))) * (1-(((_l.IP0in0) * (_l.IP0controllable_c1)) * ((_l.IP0in1) * (_l.IP0controllable_c0))))))) * (1-(_l.IP0controllable_c3)))) * ((1-((1-(_l.IP0in0)) * (1-(_l.IP0controllable_c3)))) * (_l.IP0controllable_c2)))) * (1-((((1-(((1-(((_l.IP0in1) * (_l.IP0controllable_c1)) * ((_l.IP0in2) * (_l.IP0controllable_c0)))) * (1-((1-((_l.IP0in1) * (_l.IP0controllable_c1))) * (1-((_l.IP0in2) * (_l.IP0controllable_c0)))))) * (((_l.IP0in0) * (_l.IP0controllable_c1)) * ((_l.IP0in1) * (_l.IP0controllable_c0))))) * (1-((1-((1-(((_l.IP0in1) * (_l.IP0controllable_c1)) * ((_l.IP0in2) * (_l.IP0controllable_c0)))) * (1-((1-((_l.IP0in1) * (_l.IP0controllable_c1))) * (1-((_l.IP0in2) * (_l.IP0controllable_c0))))))) * (1-(((_l.IP0in0) * (_l.IP0controllable_c1)) * ((_l.IP0in1) * (_l.IP0controllable_c0))))))) * (1-(_l.IP0controllable_c3))) * (1-((1-((1-(_l.IP0in0)) * (1-(_l.IP0controllable_c3)))) * (_l.IP0controllable_c2)))))) * (_l.IP0in3))) * (1-((1-((1-((1-(((1-(((1-(((_l.IP0in1) * (_l.IP0controllable_c1)) * ((_l.IP0in2) * (_l.IP0controllable_c0)))) * (1-((1-((_l.IP0in1) * (_l.IP0controllable_c1))) * (1-((_l.IP0in2) * (_l.IP0controllable_c0)))))) * (((_l.IP0in0) * (_l.IP0controllable_c1)) * ((_l.IP0in1) * (_l.IP0controllable_c0))))) * (1-((1-((1-(((_l.IP0in1) * (_l.IP0controllable_c1)) * ((_l.IP0in2) * (_l.IP0controllable_c0)))) * (1-((1-((_l.IP0in1) * (_l.IP0controllable_c1))) * (1-((_l.IP0in2) * (_l.IP0controllable_c0))))))) * (1-(((_l.IP0in0) * (_l.IP0controllable_c1)) * ((_l.IP0in1) * (_l.IP0controllable_c0))))))) * (1-(_l.IP0controllable_c3)))) * ((1-((1-(_l.IP0in0)) * (1-(_l.IP0controllable_c3)))) * (_l.IP0controllable_c2)))) * (1-((((1-(((1-(((_l.IP0in1) * (_l.IP0controllable_c1)) * ((_l.IP0in2) * (_l.IP0controllable_c0)))) * (1-((1-((_l.IP0in1) * (_l.IP0controllable_c1))) * (1-((_l.IP0in2) * (_l.IP0controllable_c0)))))) * (((_l.IP0in0) * (_l.IP0controllable_c1)) * ((_l.IP0in1) * (_l.IP0controllable_c0))))) * (1-((1-((1-(((_l.IP0in1) * (_l.IP0controllable_c1)) * ((_l.IP0in2) * (_l.IP0controllable_c0)))) * (1-((1-((_l.IP0in1) * (_l.IP0controllable_c1))) * (1-((_l.IP0in2) * (_l.IP0controllable_c0))))))) * (1-(((_l.IP0in0) * (_l.IP0controllable_c1)) * ((_l.IP0in1) * (_l.IP0controllable_c0))))))) * (1-(_l.IP0controllable_c3))) * (1-((1-((1-(_l.IP0in0)) * (1-(_l.IP0controllable_c3)))) * (_l.IP0controllable_c2))))))) * (1-(_l.IP0in3))))))) * ((_l.LP0benchstate0_out) * (_l.LP0benchn21))) * ((_l.LP0benchstate1_out) * (_l.LP0benchn21))) * ((_l.LP0benchstate2_out) * (_l.LP0benchn21)))));;\
    }
    );
s.add_location("Process0", "UpdatedLP0benchstate3_out", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process0", "UpdatedLP0benchstate2_out", "UpdatedLP0benchstate3_out", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.LP0benchstate3_out = (1-((1-((1-((((1-(((1-((1-(((1-((1-((1-(_l.IP0controllable_c1)) * (1-(_l.IP0controllable_c0)))) * (_l.IP0controllable_c3))) * (1-(_l.IP0in1))) * (1-(_l.IP0in2)))) * (1-((1-((1-(((1-(_l.IP0in2)) * (1-(_l.IP0controllable_c1))) * ((_l.IP0in1) * (_l.IP0controllable_c0)))) * (1-(((1-((1-((1-(_l.IP0in1)) * (1-(_l.IP0controllable_c0)))) * (1-((_l.IP0in1) * (_l.IP0controllable_c0))))) * (_l.IP0controllable_c1)) * (_l.IP0in2))))) * (_l.IP0controllable_c3))))) * (1-(_l.IP0in0))) * ((1-(((1-((1-(((1-(((1-(((_l.IP0in1) * (_l.IP0controllable_c1)) * ((_l.IP0in2) * (_l.IP0controllable_c0)))) * (1-((1-((_l.IP0in1) * (_l.IP0controllable_c1))) * (1-((_l.IP0in2) * (_l.IP0controllable_c0)))))) * (((_l.IP0in0) * (_l.IP0controllable_c1)) * ((_l.IP0in1) * (_l.IP0controllable_c0))))) * (1-((1-((1-(((_l.IP0in1) * (_l.IP0controllable_c1)) * ((_l.IP0in2) * (_l.IP0controllable_c0)))) * (1-((1-((_l.IP0in1) * (_l.IP0controllable_c1))) * (1-((_l.IP0in2) * (_l.IP0controllable_c0))))))) * (1-(((_l.IP0in0) * (_l.IP0controllable_c1)) * ((_l.IP0in1) * (_l.IP0controllable_c0))))))) * (1-(_l.IP0controllable_c3)))) * ((1-((1-(_l.IP0in0)) * (1-(_l.IP0controllable_c3)))) * (_l.IP0controllable_c2)))) * (1-((((1-(((1-(((_l.IP0in1) * (_l.IP0controllable_c1)) * ((_l.IP0in2) * (_l.IP0controllable_c0)))) * (1-((1-((_l.IP0in1) * (_l.IP0controllable_c1))) * (1-((_l.IP0in2) * (_l.IP0controllable_c0)))))) * (((_l.IP0in0) * (_l.IP0controllable_c1)) * ((_l.IP0in1) * (_l.IP0controllable_c0))))) * (1-((1-((1-(((_l.IP0in1) * (_l.IP0controllable_c1)) * ((_l.IP0in2) * (_l.IP0controllable_c0)))) * (1-((1-((_l.IP0in1) * (_l.IP0controllable_c1))) * (1-((_l.IP0in2) * (_l.IP0controllable_c0))))))) * (1-(((_l.IP0in0) * (_l.IP0controllable_c1)) * ((_l.IP0in1) * (_l.IP0controllable_c0))))))) * (1-(_l.IP0controllable_c3))) * (1-((1-((1-(_l.IP0in0)) * (1-(_l.IP0controllable_c3)))) * (_l.IP0controllable_c2)))))) * (_l.IP0in3))) * (1-((1-((1-((1-(((1-(((1-(((_l.IP0in1) * (_l.IP0controllable_c1)) * ((_l.IP0in2) * (_l.IP0controllable_c0)))) * (1-((1-((_l.IP0in1) * (_l.IP0controllable_c1))) * (1-((_l.IP0in2) * (_l.IP0controllable_c0)))))) * (((_l.IP0in0) * (_l.IP0controllable_c1)) * ((_l.IP0in1) * (_l.IP0controllable_c0))))) * (1-((1-((1-(((_l.IP0in1) * (_l.IP0controllable_c1)) * ((_l.IP0in2) * (_l.IP0controllable_c0)))) * (1-((1-((_l.IP0in1) * (_l.IP0controllable_c1))) * (1-((_l.IP0in2) * (_l.IP0controllable_c0))))))) * (1-(((_l.IP0in0) * (_l.IP0controllable_c1)) * ((_l.IP0in1) * (_l.IP0controllable_c0))))))) * (1-(_l.IP0controllable_c3)))) * ((1-((1-(_l.IP0in0)) * (1-(_l.IP0controllable_c3)))) * (_l.IP0controllable_c2)))) * (1-((((1-(((1-(((_l.IP0in1) * (_l.IP0controllable_c1)) * ((_l.IP0in2) * (_l.IP0controllable_c0)))) * (1-((1-((_l.IP0in1) * (_l.IP0controllable_c1))) * (1-((_l.IP0in2) * (_l.IP0controllable_c0)))))) * (((_l.IP0in0) * (_l.IP0controllable_c1)) * ((_l.IP0in1) * (_l.IP0controllable_c0))))) * (1-((1-((1-(((_l.IP0in1) * (_l.IP0controllable_c1)) * ((_l.IP0in2) * (_l.IP0controllable_c0)))) * (1-((1-((_l.IP0in1) * (_l.IP0controllable_c1))) * (1-((_l.IP0in2) * (_l.IP0controllable_c0))))))) * (1-(((_l.IP0in0) * (_l.IP0controllable_c1)) * ((_l.IP0in1) * (_l.IP0controllable_c0))))))) * (1-(_l.IP0controllable_c3))) * (1-((1-((1-(_l.IP0in0)) * (1-(_l.IP0controllable_c3)))) * (_l.IP0controllable_c2))))))) * (1-(_l.IP0in3))))))) * ((_l.LP0benchstate0_out) * (_l.LP0benchn21))) * ((_l.LP0benchstate1_out) * (_l.LP0benchn21))) * ((_l.LP0benchstate2_out) * (_l.LP0benchn21)))) * ((_l.LP0benchstate3_out) * (_l.LP0benchn21)))) * (1-(((((1-(((1-((1-(((1-((1-((1-(_l.IP0controllable_c1)) * (1-(_l.IP0controllable_c0)))) * (_l.IP0controllable_c3))) * (1-(_l.IP0in1))) * (1-(_l.IP0in2)))) * (1-((1-((1-(((1-(_l.IP0in2)) * (1-(_l.IP0controllable_c1))) * ((_l.IP0in1) * (_l.IP0controllable_c0)))) * (1-(((1-((1-((1-(_l.IP0in1)) * (1-(_l.IP0controllable_c0)))) * (1-((_l.IP0in1) * (_l.IP0controllable_c0))))) * (_l.IP0controllable_c1)) * (_l.IP0in2))))) * (_l.IP0controllable_c3))))) * (1-(_l.IP0in0))) * ((1-(((1-((1-(((1-(((1-(((_l.IP0in1) * (_l.IP0controllable_c1)) * ((_l.IP0in2) * (_l.IP0controllable_c0)))) * (1-((1-((_l.IP0in1) * (_l.IP0controllable_c1))) * (1-((_l.IP0in2) * (_l.IP0controllable_c0)))))) * (((_l.IP0in0) * (_l.IP0controllable_c1)) * ((_l.IP0in1) * (_l.IP0controllable_c0))))) * (1-((1-((1-(((_l.IP0in1) * (_l.IP0controllable_c1)) * ((_l.IP0in2) * (_l.IP0controllable_c0)))) * (1-((1-((_l.IP0in1) * (_l.IP0controllable_c1))) * (1-((_l.IP0in2) * (_l.IP0controllable_c0))))))) * (1-(((_l.IP0in0) * (_l.IP0controllable_c1)) * ((_l.IP0in1) * (_l.IP0controllable_c0))))))) * (1-(_l.IP0controllable_c3)))) * ((1-((1-(_l.IP0in0)) * (1-(_l.IP0controllable_c3)))) * (_l.IP0controllable_c2)))) * (1-((((1-(((1-(((_l.IP0in1) * (_l.IP0controllable_c1)) * ((_l.IP0in2) * (_l.IP0controllable_c0)))) * (1-((1-((_l.IP0in1) * (_l.IP0controllable_c1))) * (1-((_l.IP0in2) * (_l.IP0controllable_c0)))))) * (((_l.IP0in0) * (_l.IP0controllable_c1)) * ((_l.IP0in1) * (_l.IP0controllable_c0))))) * (1-((1-((1-(((_l.IP0in1) * (_l.IP0controllable_c1)) * ((_l.IP0in2) * (_l.IP0controllable_c0)))) * (1-((1-((_l.IP0in1) * (_l.IP0controllable_c1))) * (1-((_l.IP0in2) * (_l.IP0controllable_c0))))))) * (1-(((_l.IP0in0) * (_l.IP0controllable_c1)) * ((_l.IP0in1) * (_l.IP0controllable_c0))))))) * (1-(_l.IP0controllable_c3))) * (1-((1-((1-(_l.IP0in0)) * (1-(_l.IP0controllable_c3)))) * (_l.IP0controllable_c2)))))) * (_l.IP0in3))) * (1-((1-((1-((1-(((1-(((1-(((_l.IP0in1) * (_l.IP0controllable_c1)) * ((_l.IP0in2) * (_l.IP0controllable_c0)))) * (1-((1-((_l.IP0in1) * (_l.IP0controllable_c1))) * (1-((_l.IP0in2) * (_l.IP0controllable_c0)))))) * (((_l.IP0in0) * (_l.IP0controllable_c1)) * ((_l.IP0in1) * (_l.IP0controllable_c0))))) * (1-((1-((1-(((_l.IP0in1) * (_l.IP0controllable_c1)) * ((_l.IP0in2) * (_l.IP0controllable_c0)))) * (1-((1-((_l.IP0in1) * (_l.IP0controllable_c1))) * (1-((_l.IP0in2) * (_l.IP0controllable_c0))))))) * (1-(((_l.IP0in0) * (_l.IP0controllable_c1)) * ((_l.IP0in1) * (_l.IP0controllable_c0))))))) * (1-(_l.IP0controllable_c3)))) * ((1-((1-(_l.IP0in0)) * (1-(_l.IP0controllable_c3)))) * (_l.IP0controllable_c2)))) * (1-((((1-(((1-(((_l.IP0in1) * (_l.IP0controllable_c1)) * ((_l.IP0in2) * (_l.IP0controllable_c0)))) * (1-((1-((_l.IP0in1) * (_l.IP0controllable_c1))) * (1-((_l.IP0in2) * (_l.IP0controllable_c0)))))) * (((_l.IP0in0) * (_l.IP0controllable_c1)) * ((_l.IP0in1) * (_l.IP0controllable_c0))))) * (1-((1-((1-(((_l.IP0in1) * (_l.IP0controllable_c1)) * ((_l.IP0in2) * (_l.IP0controllable_c0)))) * (1-((1-((_l.IP0in1) * (_l.IP0controllable_c1))) * (1-((_l.IP0in2) * (_l.IP0controllable_c0))))))) * (1-(((_l.IP0in0) * (_l.IP0controllable_c1)) * ((_l.IP0in1) * (_l.IP0controllable_c0))))))) * (1-(_l.IP0controllable_c3))) * (1-((1-((1-(_l.IP0in0)) * (1-(_l.IP0controllable_c3)))) * (_l.IP0controllable_c2))))))) * (1-(_l.IP0in3))))))) * ((_l.LP0benchstate0_out) * (_l.LP0benchn21))) * ((_l.LP0benchstate1_out) * (_l.LP0benchn21))) * ((_l.LP0benchstate2_out) * (_l.LP0benchn21))) * (1-((_l.LP0benchstate3_out) * (_l.LP0benchn21)))))));;\
    }
    );
s.add_edge("Process0", "UpdatedLP0benchstate3_out", "w", "", "", "release0!", 
    [](syntax::layout_t const & l){\
    multi::layout_t const & _l = CAST(multi::layout_t const &, l);\
    return _l.running0 == 0;\
    }
    ,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.w0 = 1;;\
    }
    );
s.add_edge("Process0", "UpdatedLP0benchstate3_out", "w", "", "", "release1!", 
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
s.add_location("Process1", "on1", "x1 <= 2000","");
s.add_edge("Process1", "w", "on0", "", "x1", "go1?", 
    [](syntax::layout_t const & l){\
    multi::layout_t const & _l = CAST(multi::layout_t const &, l);\
    return _l.LP1state_n15 == 0;\
    }
    ,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.w1 = 0;\
    }
    );
s.add_edge("Process1", "w", "dead", "x1 >= 8999", "", "", 
    [](syntax::layout_t const & l){\
    multi::layout_t const & _l = CAST(multi::layout_t const &, l);\
    return _l.LP1state_n15 == 0;\
    }
    ,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.dead=1;;\
    }
    );
s.add_edge("Process1", "on0", "up", "x1 >= 1000 && x1 <= 1000", "x1", "", 
    [](syntax::layout_t const & l){\
    multi::layout_t const & _l = CAST(multi::layout_t const &, l);\
    return _l.LP1state_n15 == 0;\
    }
    );
s.add_edge("Process1", "w", "on1", "", "x1", "go1?", 
    [](syntax::layout_t const & l){\
    multi::layout_t const & _l = CAST(multi::layout_t const &, l);\
    return _l.LP1state_n15 == 1;\
    }
    ,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.w1 = 0;\
    }
    );
s.add_edge("Process1", "w", "dead", "x1 >= 17999", "", "", 
    [](syntax::layout_t const & l){\
    multi::layout_t const & _l = CAST(multi::layout_t const &, l);\
    return _l.LP1state_n15 == 1;\
    }
    ,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.dead=1;;\
    }
    );
s.add_edge("Process1", "on1", "up", "x1 >= 2000 && x1 <= 2000", "x1", "", 
    [](syntax::layout_t const & l){\
    multi::layout_t const & _l = CAST(multi::layout_t const &, l);\
    return _l.LP1state_n15 == 1;\
    }
    );
s.add_location("Process1", "JustSetIP1a_0_", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process1", "up", "JustSetIP1a_0_", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP1a_0_ = 0;;\
    }
    );
s.add_edge("Process1", "up", "JustSetIP1a_0_", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP1a_0_ = 1;;\
    }
    );
s.add_location("Process1", "JustSetIP1a_1_", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process1", "JustSetIP1a_0_", "JustSetIP1a_1_", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP1a_1_ = 0;;\
    }
    );
s.add_edge("Process1", "JustSetIP1a_0_", "JustSetIP1a_1_", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP1a_1_ = 1;;\
    }
    );
s.add_location("Process1", "JustSetIP1b_0_", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process1", "JustSetIP1a_1_", "JustSetIP1b_0_", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP1b_0_ = 0;;\
    }
    );
s.add_edge("Process1", "JustSetIP1a_1_", "JustSetIP1b_0_", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP1b_0_ = 1;;\
    }
    );
s.add_location("Process1", "JustSetIP1b_1_", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process1", "JustSetIP1b_0_", "JustSetIP1b_1_", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP1b_1_ = 0;;\
    }
    );
s.add_edge("Process1", "JustSetIP1b_0_", "JustSetIP1b_1_", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP1b_1_ = 1;;\
    }
    );
s.add_location("Process1", "JustSetIP1controllable_c_0_", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process1", "JustSetIP1b_1_", "JustSetIP1controllable_c_0_", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP1controllable_c_0_ = 0;;\
    }
    );
s.add_edge("Process1", "JustSetIP1b_1_", "JustSetIP1controllable_c_0_", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP1controllable_c_0_ = 1;;\
    }
    );
s.add_location("Process1", "JustSetIP1controllable_c_1_", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process1", "JustSetIP1controllable_c_0_", "JustSetIP1controllable_c_1_", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP1controllable_c_1_ = 0;;\
    }
    );
s.add_edge("Process1", "JustSetIP1controllable_c_0_", "JustSetIP1controllable_c_1_", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP1controllable_c_1_ = 1;;\
    }
    );
s.add_location("Process1", "UpdatedLP1state_n15", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process1", "JustSetIP1controllable_c_1_", "UpdatedLP1state_n15", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.LP1state_n15 = 1;;\
    }
    );
s.add_location("Process1", "UpdatedLP1err_out", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process1", "UpdatedLP1state_n15", "UpdatedLP1err_out", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.LP1err_out = (1-(((1-(((1-((1-((1-((1-(_l.IP1b_1_)) * (_l.IP1a_1_))) * (1-((_l.IP1b_1_) * (1-(_l.IP1a_1_)))))) * (1-((_l.IP1b_0_) * (_l.IP1a_0_))))) * (1-(((1-((1-(_l.IP1b_1_)) * (_l.IP1a_1_))) * (1-((_l.IP1b_1_) * (1-(_l.IP1a_1_))))) * ((_l.IP1b_0_) * (_l.IP1a_0_))))) * (_l.IP1controllable_c_1_))) * (1-((1-((1-((1-((1-((1-(_l.IP1b_1_)) * (_l.IP1a_1_))) * (1-((_l.IP1b_1_) * (1-(_l.IP1a_1_)))))) * (1-((_l.IP1b_0_) * (_l.IP1a_0_))))) * (1-(((1-((1-(_l.IP1b_1_)) * (_l.IP1a_1_))) * (1-((_l.IP1b_1_) * (1-(_l.IP1a_1_))))) * ((_l.IP1b_0_) * (_l.IP1a_0_)))))) * (1-(_l.IP1controllable_c_1_))))) * ((1-((1-((1-((1-(_l.IP1b_0_)) * (1-(_l.IP1a_0_)))) * (1-((_l.IP1b_0_) * (_l.IP1a_0_))))) * (_l.IP1controllable_c_0_))) * (1-(((1-((1-(_l.IP1b_0_)) * (1-(_l.IP1a_0_)))) * (1-((_l.IP1b_0_) * (_l.IP1a_0_)))) * (1-(_l.IP1controllable_c_0_)))))));;\
    }
    );
s.add_edge("Process1", "UpdatedLP1err_out", "w", "", "", "release0!", 
    [](syntax::layout_t const & l){\
    multi::layout_t const & _l = CAST(multi::layout_t const &, l);\
    return _l.running0 == 1;\
    }
    ,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.w1 = 1;;\
    }
    );
s.add_edge("Process1", "UpdatedLP1err_out", "w", "", "", "release1!", 
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
s.add_location("Process2", "on1", "x2 <= 2000","");
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
s.add_edge("Process2", "w", "dead", "x2 >= 8999", "", "", 
    [](syntax::layout_t const & l){\
    multi::layout_t const & _l = CAST(multi::layout_t const &, l);\
    return _l.LP2state_n15 == 0;\
    }
    ,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.dead=1;;\
    }
    );
s.add_edge("Process2", "on0", "up", "x2 >= 1000 && x2 <= 1000", "x2", "", 
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
s.add_edge("Process2", "w", "dead", "x2 >= 17999", "", "", 
    [](syntax::layout_t const & l){\
    multi::layout_t const & _l = CAST(multi::layout_t const &, l);\
    return _l.LP2state_n15 == 1;\
    }
    ,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.dead=1;;\
    }
    );
s.add_edge("Process2", "on1", "up", "x2 >= 2000 && x2 <= 2000", "x2", "", 
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
