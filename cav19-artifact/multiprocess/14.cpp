#include <iostream>
#include "syntax/system.hh"
#include "syntax/sync_product.hh"
namespace multi{
  class layout_t : public syntax::layout_t {
  public:
        
bool IP0stay;
bool IP0controllable_reset;
bool LP0n7;
bool LP0counter0_out;
bool LP0counter1_out;
bool LP0counter2_out;
bool LP0counter3_out;
bool LP0counter4_out;
bool IP1stay;
bool IP1controllable_reset;
bool LP1n7;
bool LP1counter0_out;
bool LP1counter1_out;
bool LP1counter2_out;
bool IP2stay;
bool IP2controllable_reset;
bool LP2n7;
bool LP2counter0_out;
bool LP2counter1_out;
bool LP2counter2_out;

        char running0;
        char running1;
        char dead ;
        char round ;
        bool w0 ;
        bool w1 ;
        bool w2 ;
    layout_t(){
        
IP0stay =0;
IP0controllable_reset =0;
LP0n7 =0;
LP0counter0_out =0;
LP0counter1_out =0;
LP0counter2_out =0;
LP0counter3_out =0;
LP0counter4_out =0;
IP1stay =0;
IP1controllable_reset =0;
LP1n7 =0;
LP1counter0_out =0;
LP1counter1_out =0;
LP1counter2_out =0;
IP2stay =0;
IP2controllable_reset =0;
LP2n7 =0;
LP2counter0_out =0;
LP2counter1_out =0;
LP2counter2_out =0;

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
        
if (_l.IP0stay != IP0stay) return false;
if (_l.IP0controllable_reset != IP0controllable_reset) return false;
if (_l.LP0n7 != LP0n7) return false;
if (_l.LP0counter0_out != LP0counter0_out) return false;
if (_l.LP0counter1_out != LP0counter1_out) return false;
if (_l.LP0counter2_out != LP0counter2_out) return false;
if (_l.LP0counter3_out != LP0counter3_out) return false;
if (_l.LP0counter4_out != LP0counter4_out) return false;

            if (_l.running0 != running0) return false;
            if (_l.running1 != running1) return false;
            if (_l.round != round) return false;
            if (_l.w0 != w0) return false;
            if (_l.w1 != w1) return false;
            if (_l.w2 != w2) return false;
            if (_l.dead != dead) return false;
            
if (_l.IP1stay != IP1stay) return false;
if (_l.IP1controllable_reset != IP1controllable_reset) return false;
if (_l.LP1n7 != LP1n7) return false;
if (_l.LP1counter0_out != LP1counter0_out) return false;
if (_l.LP1counter1_out != LP1counter1_out) return false;
if (_l.LP1counter2_out != LP1counter2_out) return false;

            if (_l.running0 != running0) return false;
            if (_l.running1 != running1) return false;
            if (_l.round != round) return false;
            if (_l.w0 != w0) return false;
            if (_l.w1 != w1) return false;
            if (_l.w2 != w2) return false;
            if (_l.dead != dead) return false;
            
if (_l.IP2stay != IP2stay) return false;
if (_l.IP2controllable_reset != IP2controllable_reset) return false;
if (_l.LP2n7 != LP2n7) return false;
if (_l.LP2counter0_out != LP2counter0_out) return false;
if (_l.LP2counter1_out != LP2counter1_out) return false;
if (_l.LP2counter2_out != LP2counter2_out) return false;

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
        
	boost::hash_combine(seed,IP0stay);
	boost::hash_combine(seed,IP0controllable_reset);
	boost::hash_combine(seed,LP0n7);
	boost::hash_combine(seed,LP0counter0_out);
	boost::hash_combine(seed,LP0counter1_out);
	boost::hash_combine(seed,LP0counter2_out);
	boost::hash_combine(seed,LP0counter3_out);
	boost::hash_combine(seed,LP0counter4_out);

            	boost::hash_combine(seed, running0);
            	boost::hash_combine(seed, running1);
            	boost::hash_combine(seed, round);
            	boost::hash_combine(seed, w0);
            	boost::hash_combine(seed, w1);
            	boost::hash_combine(seed, w2);
            	boost::hash_combine(seed, dead);
            
	boost::hash_combine(seed,IP1stay);
	boost::hash_combine(seed,IP1controllable_reset);
	boost::hash_combine(seed,LP1n7);
	boost::hash_combine(seed,LP1counter0_out);
	boost::hash_combine(seed,LP1counter1_out);
	boost::hash_combine(seed,LP1counter2_out);

            	boost::hash_combine(seed, running0);
            	boost::hash_combine(seed, running1);
            	boost::hash_combine(seed, round);
            	boost::hash_combine(seed, w0);
            	boost::hash_combine(seed, w1);
            	boost::hash_combine(seed, w2);
            	boost::hash_combine(seed, dead);
            
	boost::hash_combine(seed,IP2stay);
	boost::hash_combine(seed,IP2controllable_reset);
	boost::hash_combine(seed,LP2n7);
	boost::hash_combine(seed,LP2counter0_out);
	boost::hash_combine(seed,LP2counter1_out);
	boost::hash_combine(seed,LP2counter2_out);

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
    return _l.LP0counter0_out == 0;\
    }
    ,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.w0 = 0;\
    }
    );
s.add_edge("Process0", "w", "dead", "x0 >= 1999", "", "", 
    [](syntax::layout_t const & l){\
    multi::layout_t const & _l = CAST(multi::layout_t const &, l);\
    return _l.LP0counter0_out == 0;\
    }
    ,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.dead=1;;\
    }
    );
s.add_edge("Process0", "on0", "up", "x0 >= 500 && x0 <= 1000", "x0", "", 
    [](syntax::layout_t const & l){\
    multi::layout_t const & _l = CAST(multi::layout_t const &, l);\
    return _l.LP0counter0_out == 0;\
    }
    );
s.add_edge("Process0", "w", "on1", "", "x0", "go0?", 
    [](syntax::layout_t const & l){\
    multi::layout_t const & _l = CAST(multi::layout_t const &, l);\
    return _l.LP0counter0_out == 1;\
    }
    ,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.w0 = 0;\
    }
    );
s.add_edge("Process0", "w", "dead", "x0 >= 2199", "", "", 
    [](syntax::layout_t const & l){\
    multi::layout_t const & _l = CAST(multi::layout_t const &, l);\
    return _l.LP0counter0_out == 1;\
    }
    ,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.dead=1;;\
    }
    );
s.add_edge("Process0", "on1", "up", "x0 >= 400 && x0 <= 800", "x0", "", 
    [](syntax::layout_t const & l){\
    multi::layout_t const & _l = CAST(multi::layout_t const &, l);\
    return _l.LP0counter0_out == 1;\
    }
    );
s.add_location("Process0", "JustSetIP0stay", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process0", "up", "JustSetIP0stay", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP0stay = 0;;\
    }
    );
s.add_edge("Process0", "up", "JustSetIP0stay", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP0stay = 1;;\
    }
    );
s.add_location("Process0", "JustSetIP0controllable_reset", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process0", "JustSetIP0stay", "JustSetIP0controllable_reset", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP0controllable_reset = 0;;\
    }
    );
s.add_edge("Process0", "JustSetIP0stay", "JustSetIP0controllable_reset", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP0controllable_reset = 1;;\
    }
    );
s.add_location("Process0", "UpdatedLP0n7", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process0", "JustSetIP0controllable_reset", "UpdatedLP0n7", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.LP0n7 = 1;;\
    }
    );
s.add_location("Process0", "UpdatedLP0counter0_out", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process0", "UpdatedLP0n7", "UpdatedLP0counter0_out", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.LP0counter0_out = (1-((1-((1-((_l.LP0counter0_out) * (_l.LP0n7))) * (1-(_l.IP0stay)))) * (1-(((_l.LP0counter0_out) * (_l.LP0n7)) * (_l.IP0stay)))));;\
    }
    );
s.add_location("Process0", "UpdatedLP0counter1_out", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process0", "UpdatedLP0counter0_out", "UpdatedLP0counter1_out", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.LP0counter1_out = (1-((1-((((_l.LP0counter0_out) * (_l.LP0n7)) * (1-(_l.IP0stay))) * (1-((_l.LP0counter1_out) * (_l.LP0n7))))) * (1-((1-(((_l.LP0counter0_out) * (_l.LP0n7)) * (1-(_l.IP0stay)))) * ((_l.LP0counter1_out) * (_l.LP0n7))))));;\
    }
    );
s.add_location("Process0", "UpdatedLP0counter2_out", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process0", "UpdatedLP0counter1_out", "UpdatedLP0counter2_out", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.LP0counter2_out = (1-((1-(((((_l.LP0counter1_out) * (_l.LP0n7)) * ((_l.LP0counter0_out) * (_l.LP0n7))) * (1-(_l.IP0stay))) * (1-((_l.LP0counter2_out) * (_l.LP0n7))))) * (1-((1-((((_l.LP0counter1_out) * (_l.LP0n7)) * ((_l.LP0counter0_out) * (_l.LP0n7))) * (1-(_l.IP0stay)))) * ((_l.LP0counter2_out) * (_l.LP0n7))))));;\
    }
    );
s.add_location("Process0", "UpdatedLP0counter3_out", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process0", "UpdatedLP0counter2_out", "UpdatedLP0counter3_out", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.LP0counter3_out = (1-((1-((((((_l.LP0counter1_out) * (_l.LP0n7)) * ((_l.LP0counter0_out) * (_l.LP0n7))) * ((_l.LP0counter2_out) * (_l.LP0n7))) * (1-(_l.IP0stay))) * (1-((_l.LP0counter3_out) * (_l.LP0n7))))) * (1-((1-(((((_l.LP0counter1_out) * (_l.LP0n7)) * ((_l.LP0counter0_out) * (_l.LP0n7))) * ((_l.LP0counter2_out) * (_l.LP0n7))) * (1-(_l.IP0stay)))) * ((_l.LP0counter3_out) * (_l.LP0n7))))));;\
    }
    );
s.add_location("Process0", "UpdatedLP0counter4_out", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process0", "UpdatedLP0counter3_out", "UpdatedLP0counter4_out", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.LP0counter4_out = ((1-((1-((((((_l.LP0counter1_out) * (_l.LP0n7)) * ((_l.LP0counter0_out) * (_l.LP0n7))) * ((_l.LP0counter2_out) * (_l.LP0n7))) * ((_l.LP0counter3_out) * (_l.LP0n7))) * (1-(_l.IP0stay)))) * (1-((_l.LP0counter4_out) * (_l.LP0n7))))) * (1-(((((((_l.LP0counter1_out) * (_l.LP0n7)) * ((_l.LP0counter0_out) * (_l.LP0n7))) * ((_l.LP0counter2_out) * (_l.LP0n7))) * ((_l.LP0counter3_out) * (_l.LP0n7))) * (1-(_l.IP0stay))) * (1-((1-((_l.LP0counter4_out) * (_l.LP0n7))) * (1-(_l.IP0controllable_reset)))))));;\
    }
    );
s.add_edge("Process0", "UpdatedLP0counter4_out", "w", "", "", "release0!", 
    [](syntax::layout_t const & l){\
    multi::layout_t const & _l = CAST(multi::layout_t const &, l);\
    return _l.running0 == 0;\
    }
    ,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.w0 = 1;;\
    }
    );
s.add_edge("Process0", "UpdatedLP0counter4_out", "w", "", "", "release1!", 
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
    return _l.LP1counter0_out == 0;\
    }
    ,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.w1 = 0;\
    }
    );
s.add_edge("Process1", "w", "dead", "x1 >= 1999", "", "", 
    [](syntax::layout_t const & l){\
    multi::layout_t const & _l = CAST(multi::layout_t const &, l);\
    return _l.LP1counter0_out == 0;\
    }
    ,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.dead=1;;\
    }
    );
s.add_edge("Process1", "on0", "up", "x1 >= 500 && x1 <= 1000", "x1", "", 
    [](syntax::layout_t const & l){\
    multi::layout_t const & _l = CAST(multi::layout_t const &, l);\
    return _l.LP1counter0_out == 0;\
    }
    );
s.add_edge("Process1", "w", "on1", "", "x1", "go1?", 
    [](syntax::layout_t const & l){\
    multi::layout_t const & _l = CAST(multi::layout_t const &, l);\
    return _l.LP1counter0_out == 1;\
    }
    ,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.w1 = 0;\
    }
    );
s.add_edge("Process1", "w", "dead", "x1 >= 2199", "", "", 
    [](syntax::layout_t const & l){\
    multi::layout_t const & _l = CAST(multi::layout_t const &, l);\
    return _l.LP1counter0_out == 1;\
    }
    ,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.dead=1;;\
    }
    );
s.add_edge("Process1", "on1", "up", "x1 >= 400 && x1 <= 800", "x1", "", 
    [](syntax::layout_t const & l){\
    multi::layout_t const & _l = CAST(multi::layout_t const &, l);\
    return _l.LP1counter0_out == 1;\
    }
    );
s.add_location("Process1", "JustSetIP1stay", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process1", "up", "JustSetIP1stay", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP1stay = 0;;\
    }
    );
s.add_edge("Process1", "up", "JustSetIP1stay", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP1stay = 1;;\
    }
    );
s.add_location("Process1", "JustSetIP1controllable_reset", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process1", "JustSetIP1stay", "JustSetIP1controllable_reset", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP1controllable_reset = 0;;\
    }
    );
s.add_edge("Process1", "JustSetIP1stay", "JustSetIP1controllable_reset", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP1controllable_reset = 1;;\
    }
    );
s.add_location("Process1", "UpdatedLP1n7", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process1", "JustSetIP1controllable_reset", "UpdatedLP1n7", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.LP1n7 = 1;;\
    }
    );
s.add_location("Process1", "UpdatedLP1counter0_out", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process1", "UpdatedLP1n7", "UpdatedLP1counter0_out", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.LP1counter0_out = (1-((1-((1-((_l.LP1counter0_out) * (_l.LP1n7))) * (1-(_l.IP1stay)))) * (1-(((_l.LP1counter0_out) * (_l.LP1n7)) * (_l.IP1stay)))));;\
    }
    );
s.add_location("Process1", "UpdatedLP1counter1_out", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process1", "UpdatedLP1counter0_out", "UpdatedLP1counter1_out", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.LP1counter1_out = (1-((1-((((_l.LP1counter0_out) * (_l.LP1n7)) * (1-(_l.IP1stay))) * (1-((_l.LP1counter1_out) * (_l.LP1n7))))) * (1-((1-(((_l.LP1counter0_out) * (_l.LP1n7)) * (1-(_l.IP1stay)))) * ((_l.LP1counter1_out) * (_l.LP1n7))))));;\
    }
    );
s.add_location("Process1", "UpdatedLP1counter2_out", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process1", "UpdatedLP1counter1_out", "UpdatedLP1counter2_out", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.LP1counter2_out = ((1-(((((_l.LP1counter1_out) * (_l.LP1n7)) * ((_l.LP1counter0_out) * (_l.LP1n7))) * ((_l.LP1counter2_out) * (_l.LP1n7))) * (1-(_l.IP1stay)))) * (1-((1-(((((_l.LP1counter1_out) * (_l.LP1n7)) * ((_l.LP1counter0_out) * (_l.LP1n7))) * (1-(_l.IP1controllable_reset))) * (1-(_l.IP1stay)))) * (1-((_l.LP1counter2_out) * (_l.LP1n7))))));;\
    }
    );
s.add_edge("Process1", "UpdatedLP1counter2_out", "w", "", "", "release0!", 
    [](syntax::layout_t const & l){\
    multi::layout_t const & _l = CAST(multi::layout_t const &, l);\
    return _l.running0 == 1;\
    }
    ,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.w1 = 1;;\
    }
    );
s.add_edge("Process1", "UpdatedLP1counter2_out", "w", "", "", "release1!", 
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
    return _l.LP2counter0_out == 0;\
    }
    ,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.w2 = 0;\
    }
    );
s.add_edge("Process2", "w", "dead", "x2 >= 1999", "", "", 
    [](syntax::layout_t const & l){\
    multi::layout_t const & _l = CAST(multi::layout_t const &, l);\
    return _l.LP2counter0_out == 0;\
    }
    ,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.dead=1;;\
    }
    );
s.add_edge("Process2", "on0", "up", "x2 >= 500 && x2 <= 1000", "x2", "", 
    [](syntax::layout_t const & l){\
    multi::layout_t const & _l = CAST(multi::layout_t const &, l);\
    return _l.LP2counter0_out == 0;\
    }
    );
s.add_edge("Process2", "w", "on1", "", "x2", "go2?", 
    [](syntax::layout_t const & l){\
    multi::layout_t const & _l = CAST(multi::layout_t const &, l);\
    return _l.LP2counter0_out == 1;\
    }
    ,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.w2 = 0;\
    }
    );
s.add_edge("Process2", "w", "dead", "x2 >= 2199", "", "", 
    [](syntax::layout_t const & l){\
    multi::layout_t const & _l = CAST(multi::layout_t const &, l);\
    return _l.LP2counter0_out == 1;\
    }
    ,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.dead=1;;\
    }
    );
s.add_edge("Process2", "on1", "up", "x2 >= 400 && x2 <= 800", "x2", "", 
    [](syntax::layout_t const & l){\
    multi::layout_t const & _l = CAST(multi::layout_t const &, l);\
    return _l.LP2counter0_out == 1;\
    }
    );
s.add_location("Process2", "JustSetIP2stay", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process2", "up", "JustSetIP2stay", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP2stay = 0;;\
    }
    );
s.add_edge("Process2", "up", "JustSetIP2stay", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP2stay = 1;;\
    }
    );
s.add_location("Process2", "JustSetIP2controllable_reset", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process2", "JustSetIP2stay", "JustSetIP2controllable_reset", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP2controllable_reset = 0;;\
    }
    );
s.add_edge("Process2", "JustSetIP2stay", "JustSetIP2controllable_reset", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP2controllable_reset = 1;;\
    }
    );
s.add_location("Process2", "UpdatedLP2n7", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process2", "JustSetIP2controllable_reset", "UpdatedLP2n7", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.LP2n7 = 1;;\
    }
    );
s.add_location("Process2", "UpdatedLP2counter0_out", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process2", "UpdatedLP2n7", "UpdatedLP2counter0_out", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.LP2counter0_out = (1-((1-((1-((_l.LP2counter0_out) * (_l.LP2n7))) * (1-(_l.IP2stay)))) * (1-(((_l.LP2counter0_out) * (_l.LP2n7)) * (_l.IP2stay)))));;\
    }
    );
s.add_location("Process2", "UpdatedLP2counter1_out", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process2", "UpdatedLP2counter0_out", "UpdatedLP2counter1_out", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.LP2counter1_out = (1-((1-((((_l.LP2counter0_out) * (_l.LP2n7)) * (1-(_l.IP2stay))) * (1-((_l.LP2counter1_out) * (_l.LP2n7))))) * (1-((1-(((_l.LP2counter0_out) * (_l.LP2n7)) * (1-(_l.IP2stay)))) * ((_l.LP2counter1_out) * (_l.LP2n7))))));;\
    }
    );
s.add_location("Process2", "UpdatedLP2counter2_out", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process2", "UpdatedLP2counter1_out", "UpdatedLP2counter2_out", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.LP2counter2_out = ((1-(((((_l.LP2counter1_out) * (_l.LP2n7)) * ((_l.LP2counter0_out) * (_l.LP2n7))) * ((_l.LP2counter2_out) * (_l.LP2n7))) * (1-(_l.IP2stay)))) * (1-((1-(((((_l.LP2counter1_out) * (_l.LP2n7)) * ((_l.LP2counter0_out) * (_l.LP2n7))) * (1-(_l.IP2controllable_reset))) * (1-(_l.IP2stay)))) * (1-((_l.LP2counter2_out) * (_l.LP2n7))))));;\
    }
    );
s.add_edge("Process2", "UpdatedLP2counter2_out", "w", "", "", "release0!", 
    [](syntax::layout_t const & l){\
    multi::layout_t const & _l = CAST(multi::layout_t const &, l);\
    return _l.running0 == 2;\
    }
    ,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.w2 = 1;;\
    }
    );
s.add_edge("Process2", "UpdatedLP2counter2_out", "w", "", "", "release1!", 
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
