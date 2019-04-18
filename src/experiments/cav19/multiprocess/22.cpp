#include <iostream>
#include "syntax/system.hh"
#include "syntax/sync_product.hh"
namespace multi{
  class layout_t : public syntax::layout_t {
  public:
        
bool IP0i_hbusreq0;
bool IP0i_hbusreq1;
bool IP0i_hbusreq2;
bool IP0i_hburst1;
bool IP0i_hburst0;
bool IP0i_hlock0;
bool IP0i_hlock1;
bool IP0i_hlock2;
bool IP0i_hready;
bool IP0controllable_hmastlock;
bool IP0controllable_nstart;
bool IP0controllable_hmaster1;
bool IP0controllable_locked;
bool IP0controllable_hmaster0;
bool IP0controllable_hgrant1;
bool IP0controllable_busreq;
bool IP0controllable_hgrant2;
bool IP0controllable_ndecide;
bool IP0controllable_nhgrant0;
bool LP0n41;
bool LP0reg_controllable_hgrant2_out;
bool LP0reg_controllable_hmaster1_out;
bool LP0sys_fair0done_out;
bool LP0reg_stateG3_0_out;
bool LP0env_fair1done_out;
bool LP0reg_controllable_locked_out;
bool LP0sys_fair3done_out;
bool LP0reg_stateG3_1_out;
bool LP0reg_controllable_ndecide_out;
bool LP0reg_stateG3_2_out;
bool LP0reg_i_hbusreq0_out;
bool LP0reg_controllable_busreq_out;
bool LP0reg_controllable_nstart_out;
bool LP0reg_i_hbusreq1_out;
bool LP0sys_fair1done_out;
bool LP0reg_stateG2_out;
bool LP0reg_stateG10_1_out;
bool LP0env_fair0done_out;
bool LP0reg_controllable_nhgrant0_out;
bool LP0reg_i_hlock2_out;
bool LP0reg_stateG10_2_out;
bool LP0reg_stateA1_out;
bool LP0reg_controllable_hmastlock_out;
bool LP0sys_fair4done_out;
bool LP0reg_i_hbusreq2_out;
bool LP0reg_i_hlock1_out;
bool LP0fair_cnt0_out;
bool LP0fair_cnt1_out;
bool LP0fair_cnt2_out;
bool LP0env_safe_err_happened_out;
bool LP0reg_i_hlock0_out;
bool LP0reg_i_hready_out;
bool LP0reg_controllable_hgrant1_out;
bool LP0sys_fair2done_out;
bool LP0reg_controllable_hmaster0_out;
bool IP1a_0_;
bool IP1a_1_;
bool IP1b_0_;
bool IP1b_1_;
bool IP1controllable_c_0_;
bool IP1controllable_c_1_;
bool LP1state_n15;
bool LP1err_out;
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
        
IP0i_hbusreq0 =0;
IP0i_hbusreq1 =0;
IP0i_hbusreq2 =0;
IP0i_hburst1 =0;
IP0i_hburst0 =0;
IP0i_hlock0 =0;
IP0i_hlock1 =0;
IP0i_hlock2 =0;
IP0i_hready =0;
IP0controllable_hmastlock =0;
IP0controllable_nstart =0;
IP0controllable_hmaster1 =0;
IP0controllable_locked =0;
IP0controllable_hmaster0 =0;
IP0controllable_hgrant1 =0;
IP0controllable_busreq =0;
IP0controllable_hgrant2 =0;
IP0controllable_ndecide =0;
IP0controllable_nhgrant0 =0;
LP0n41 =0;
LP0reg_controllable_hgrant2_out =0;
LP0reg_controllable_hmaster1_out =0;
LP0sys_fair0done_out =0;
LP0reg_stateG3_0_out =0;
LP0env_fair1done_out =0;
LP0reg_controllable_locked_out =0;
LP0sys_fair3done_out =0;
LP0reg_stateG3_1_out =0;
LP0reg_controllable_ndecide_out =0;
LP0reg_stateG3_2_out =0;
LP0reg_i_hbusreq0_out =0;
LP0reg_controllable_busreq_out =0;
LP0reg_controllable_nstart_out =0;
LP0reg_i_hbusreq1_out =0;
LP0sys_fair1done_out =0;
LP0reg_stateG2_out =0;
LP0reg_stateG10_1_out =0;
LP0env_fair0done_out =0;
LP0reg_controllable_nhgrant0_out =0;
LP0reg_i_hlock2_out =0;
LP0reg_stateG10_2_out =0;
LP0reg_stateA1_out =0;
LP0reg_controllable_hmastlock_out =0;
LP0sys_fair4done_out =0;
LP0reg_i_hbusreq2_out =0;
LP0reg_i_hlock1_out =0;
LP0fair_cnt0_out =0;
LP0fair_cnt1_out =0;
LP0fair_cnt2_out =0;
LP0env_safe_err_happened_out =0;
LP0reg_i_hlock0_out =0;
LP0reg_i_hready_out =0;
LP0reg_controllable_hgrant1_out =0;
LP0sys_fair2done_out =0;
LP0reg_controllable_hmaster0_out =0;
IP1a_0_ =0;
IP1a_1_ =0;
IP1b_0_ =0;
IP1b_1_ =0;
IP1controllable_c_0_ =0;
IP1controllable_c_1_ =0;
LP1state_n15 =0;
LP1err_out =0;
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
        
if (_l.IP0i_hbusreq0 != IP0i_hbusreq0) return false;
if (_l.IP0i_hbusreq1 != IP0i_hbusreq1) return false;
if (_l.IP0i_hbusreq2 != IP0i_hbusreq2) return false;
if (_l.IP0i_hburst1 != IP0i_hburst1) return false;
if (_l.IP0i_hburst0 != IP0i_hburst0) return false;
if (_l.IP0i_hlock0 != IP0i_hlock0) return false;
if (_l.IP0i_hlock1 != IP0i_hlock1) return false;
if (_l.IP0i_hlock2 != IP0i_hlock2) return false;
if (_l.IP0i_hready != IP0i_hready) return false;
if (_l.IP0controllable_hmastlock != IP0controllable_hmastlock) return false;
if (_l.IP0controllable_nstart != IP0controllable_nstart) return false;
if (_l.IP0controllable_hmaster1 != IP0controllable_hmaster1) return false;
if (_l.IP0controllable_locked != IP0controllable_locked) return false;
if (_l.IP0controllable_hmaster0 != IP0controllable_hmaster0) return false;
if (_l.IP0controllable_hgrant1 != IP0controllable_hgrant1) return false;
if (_l.IP0controllable_busreq != IP0controllable_busreq) return false;
if (_l.IP0controllable_hgrant2 != IP0controllable_hgrant2) return false;
if (_l.IP0controllable_ndecide != IP0controllable_ndecide) return false;
if (_l.IP0controllable_nhgrant0 != IP0controllable_nhgrant0) return false;
if (_l.LP0n41 != LP0n41) return false;
if (_l.LP0reg_controllable_hgrant2_out != LP0reg_controllable_hgrant2_out) return false;
if (_l.LP0reg_controllable_hmaster1_out != LP0reg_controllable_hmaster1_out) return false;
if (_l.LP0sys_fair0done_out != LP0sys_fair0done_out) return false;
if (_l.LP0reg_stateG3_0_out != LP0reg_stateG3_0_out) return false;
if (_l.LP0env_fair1done_out != LP0env_fair1done_out) return false;
if (_l.LP0reg_controllable_locked_out != LP0reg_controllable_locked_out) return false;
if (_l.LP0sys_fair3done_out != LP0sys_fair3done_out) return false;
if (_l.LP0reg_stateG3_1_out != LP0reg_stateG3_1_out) return false;
if (_l.LP0reg_controllable_ndecide_out != LP0reg_controllable_ndecide_out) return false;
if (_l.LP0reg_stateG3_2_out != LP0reg_stateG3_2_out) return false;
if (_l.LP0reg_i_hbusreq0_out != LP0reg_i_hbusreq0_out) return false;
if (_l.LP0reg_controllable_busreq_out != LP0reg_controllable_busreq_out) return false;
if (_l.LP0reg_controllable_nstart_out != LP0reg_controllable_nstart_out) return false;
if (_l.LP0reg_i_hbusreq1_out != LP0reg_i_hbusreq1_out) return false;
if (_l.LP0sys_fair1done_out != LP0sys_fair1done_out) return false;
if (_l.LP0reg_stateG2_out != LP0reg_stateG2_out) return false;
if (_l.LP0reg_stateG10_1_out != LP0reg_stateG10_1_out) return false;
if (_l.LP0env_fair0done_out != LP0env_fair0done_out) return false;
if (_l.LP0reg_controllable_nhgrant0_out != LP0reg_controllable_nhgrant0_out) return false;
if (_l.LP0reg_i_hlock2_out != LP0reg_i_hlock2_out) return false;
if (_l.LP0reg_stateG10_2_out != LP0reg_stateG10_2_out) return false;
if (_l.LP0reg_stateA1_out != LP0reg_stateA1_out) return false;
if (_l.LP0reg_controllable_hmastlock_out != LP0reg_controllable_hmastlock_out) return false;
if (_l.LP0sys_fair4done_out != LP0sys_fair4done_out) return false;
if (_l.LP0reg_i_hbusreq2_out != LP0reg_i_hbusreq2_out) return false;
if (_l.LP0reg_i_hlock1_out != LP0reg_i_hlock1_out) return false;
if (_l.LP0fair_cnt0_out != LP0fair_cnt0_out) return false;
if (_l.LP0fair_cnt1_out != LP0fair_cnt1_out) return false;
if (_l.LP0fair_cnt2_out != LP0fair_cnt2_out) return false;
if (_l.LP0env_safe_err_happened_out != LP0env_safe_err_happened_out) return false;
if (_l.LP0reg_i_hlock0_out != LP0reg_i_hlock0_out) return false;
if (_l.LP0reg_i_hready_out != LP0reg_i_hready_out) return false;
if (_l.LP0reg_controllable_hgrant1_out != LP0reg_controllable_hgrant1_out) return false;
if (_l.LP0sys_fair2done_out != LP0sys_fair2done_out) return false;
if (_l.LP0reg_controllable_hmaster0_out != LP0reg_controllable_hmaster0_out) return false;

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
        
	boost::hash_combine(seed,IP0i_hbusreq0);
	boost::hash_combine(seed,IP0i_hbusreq1);
	boost::hash_combine(seed,IP0i_hbusreq2);
	boost::hash_combine(seed,IP0i_hburst1);
	boost::hash_combine(seed,IP0i_hburst0);
	boost::hash_combine(seed,IP0i_hlock0);
	boost::hash_combine(seed,IP0i_hlock1);
	boost::hash_combine(seed,IP0i_hlock2);
	boost::hash_combine(seed,IP0i_hready);
	boost::hash_combine(seed,IP0controllable_hmastlock);
	boost::hash_combine(seed,IP0controllable_nstart);
	boost::hash_combine(seed,IP0controllable_hmaster1);
	boost::hash_combine(seed,IP0controllable_locked);
	boost::hash_combine(seed,IP0controllable_hmaster0);
	boost::hash_combine(seed,IP0controllable_hgrant1);
	boost::hash_combine(seed,IP0controllable_busreq);
	boost::hash_combine(seed,IP0controllable_hgrant2);
	boost::hash_combine(seed,IP0controllable_ndecide);
	boost::hash_combine(seed,IP0controllable_nhgrant0);
	boost::hash_combine(seed,LP0n41);
	boost::hash_combine(seed,LP0reg_controllable_hgrant2_out);
	boost::hash_combine(seed,LP0reg_controllable_hmaster1_out);
	boost::hash_combine(seed,LP0sys_fair0done_out);
	boost::hash_combine(seed,LP0reg_stateG3_0_out);
	boost::hash_combine(seed,LP0env_fair1done_out);
	boost::hash_combine(seed,LP0reg_controllable_locked_out);
	boost::hash_combine(seed,LP0sys_fair3done_out);
	boost::hash_combine(seed,LP0reg_stateG3_1_out);
	boost::hash_combine(seed,LP0reg_controllable_ndecide_out);
	boost::hash_combine(seed,LP0reg_stateG3_2_out);
	boost::hash_combine(seed,LP0reg_i_hbusreq0_out);
	boost::hash_combine(seed,LP0reg_controllable_busreq_out);
	boost::hash_combine(seed,LP0reg_controllable_nstart_out);
	boost::hash_combine(seed,LP0reg_i_hbusreq1_out);
	boost::hash_combine(seed,LP0sys_fair1done_out);
	boost::hash_combine(seed,LP0reg_stateG2_out);
	boost::hash_combine(seed,LP0reg_stateG10_1_out);
	boost::hash_combine(seed,LP0env_fair0done_out);
	boost::hash_combine(seed,LP0reg_controllable_nhgrant0_out);
	boost::hash_combine(seed,LP0reg_i_hlock2_out);
	boost::hash_combine(seed,LP0reg_stateG10_2_out);
	boost::hash_combine(seed,LP0reg_stateA1_out);
	boost::hash_combine(seed,LP0reg_controllable_hmastlock_out);
	boost::hash_combine(seed,LP0sys_fair4done_out);
	boost::hash_combine(seed,LP0reg_i_hbusreq2_out);
	boost::hash_combine(seed,LP0reg_i_hlock1_out);
	boost::hash_combine(seed,LP0fair_cnt0_out);
	boost::hash_combine(seed,LP0fair_cnt1_out);
	boost::hash_combine(seed,LP0fair_cnt2_out);
	boost::hash_combine(seed,LP0env_safe_err_happened_out);
	boost::hash_combine(seed,LP0reg_i_hlock0_out);
	boost::hash_combine(seed,LP0reg_i_hready_out);
	boost::hash_combine(seed,LP0reg_controllable_hgrant1_out);
	boost::hash_combine(seed,LP0sys_fair2done_out);
	boost::hash_combine(seed,LP0reg_controllable_hmaster0_out);

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
    return _l.LP0reg_stateG3_0_out == 0;\
    }
    ,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.w0 = 0;\
    }
    );
s.add_edge("Process0", "w", "dead", "x0 >= 499", "", "", 
    [](syntax::layout_t const & l){\
    multi::layout_t const & _l = CAST(multi::layout_t const &, l);\
    return _l.LP0reg_stateG3_0_out == 0;\
    }
    ,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.dead=1;;\
    }
    );
s.add_edge("Process0", "on0", "up", "x0 >= 500 && x0 <= 1000", "x0", "", 
    [](syntax::layout_t const & l){\
    multi::layout_t const & _l = CAST(multi::layout_t const &, l);\
    return _l.LP0reg_stateG3_0_out == 0;\
    }
    );
s.add_edge("Process0", "w", "on1", "", "x0", "go0?", 
    [](syntax::layout_t const & l){\
    multi::layout_t const & _l = CAST(multi::layout_t const &, l);\
    return _l.LP0reg_stateG3_0_out == 1;\
    }
    ,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.w0 = 0;\
    }
    );
s.add_edge("Process0", "w", "dead", "x0 >= 799", "", "", 
    [](syntax::layout_t const & l){\
    multi::layout_t const & _l = CAST(multi::layout_t const &, l);\
    return _l.LP0reg_stateG3_0_out == 1;\
    }
    ,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.dead=1;;\
    }
    );
s.add_edge("Process0", "on1", "up", "x0 >= 400 && x0 <= 800", "x0", "", 
    [](syntax::layout_t const & l){\
    multi::layout_t const & _l = CAST(multi::layout_t const &, l);\
    return _l.LP0reg_stateG3_0_out == 1;\
    }
    );
s.add_location("Process0", "JustSetIP0i_hbusreq0", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process0", "up", "JustSetIP0i_hbusreq0", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP0i_hbusreq0 = 0;;\
    }
    );
s.add_edge("Process0", "up", "JustSetIP0i_hbusreq0", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP0i_hbusreq0 = 1;;\
    }
    );
s.add_location("Process0", "JustSetIP0i_hbusreq1", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process0", "JustSetIP0i_hbusreq0", "JustSetIP0i_hbusreq1", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP0i_hbusreq1 = 0;;\
    }
    );
s.add_edge("Process0", "JustSetIP0i_hbusreq0", "JustSetIP0i_hbusreq1", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP0i_hbusreq1 = 1;;\
    }
    );
s.add_location("Process0", "JustSetIP0i_hbusreq2", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process0", "JustSetIP0i_hbusreq1", "JustSetIP0i_hbusreq2", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP0i_hbusreq2 = 0;;\
    }
    );
s.add_edge("Process0", "JustSetIP0i_hbusreq1", "JustSetIP0i_hbusreq2", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP0i_hbusreq2 = 1;;\
    }
    );
s.add_location("Process0", "JustSetIP0i_hburst1", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process0", "JustSetIP0i_hbusreq2", "JustSetIP0i_hburst1", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP0i_hburst1 = 0;;\
    }
    );
s.add_edge("Process0", "JustSetIP0i_hbusreq2", "JustSetIP0i_hburst1", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP0i_hburst1 = 1;;\
    }
    );
s.add_location("Process0", "JustSetIP0i_hburst0", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process0", "JustSetIP0i_hburst1", "JustSetIP0i_hburst0", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP0i_hburst0 = 0;;\
    }
    );
s.add_edge("Process0", "JustSetIP0i_hburst1", "JustSetIP0i_hburst0", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP0i_hburst0 = 1;;\
    }
    );
s.add_location("Process0", "JustSetIP0i_hlock0", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process0", "JustSetIP0i_hburst0", "JustSetIP0i_hlock0", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP0i_hlock0 = 0;;\
    }
    );
s.add_edge("Process0", "JustSetIP0i_hburst0", "JustSetIP0i_hlock0", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP0i_hlock0 = 1;;\
    }
    );
s.add_location("Process0", "JustSetIP0i_hlock1", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process0", "JustSetIP0i_hlock0", "JustSetIP0i_hlock1", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP0i_hlock1 = 0;;\
    }
    );
s.add_edge("Process0", "JustSetIP0i_hlock0", "JustSetIP0i_hlock1", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP0i_hlock1 = 1;;\
    }
    );
s.add_location("Process0", "JustSetIP0i_hlock2", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process0", "JustSetIP0i_hlock1", "JustSetIP0i_hlock2", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP0i_hlock2 = 0;;\
    }
    );
s.add_edge("Process0", "JustSetIP0i_hlock1", "JustSetIP0i_hlock2", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP0i_hlock2 = 1;;\
    }
    );
s.add_location("Process0", "JustSetIP0i_hready", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process0", "JustSetIP0i_hlock2", "JustSetIP0i_hready", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP0i_hready = 0;;\
    }
    );
s.add_edge("Process0", "JustSetIP0i_hlock2", "JustSetIP0i_hready", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP0i_hready = 1;;\
    }
    );
s.add_location("Process0", "JustSetIP0controllable_hmastlock", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process0", "JustSetIP0i_hready", "JustSetIP0controllable_hmastlock", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP0controllable_hmastlock = 0;;\
    }
    );
s.add_edge("Process0", "JustSetIP0i_hready", "JustSetIP0controllable_hmastlock", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP0controllable_hmastlock = 1;;\
    }
    );
s.add_location("Process0", "JustSetIP0controllable_nstart", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process0", "JustSetIP0controllable_hmastlock", "JustSetIP0controllable_nstart", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP0controllable_nstart = 0;;\
    }
    );
s.add_edge("Process0", "JustSetIP0controllable_hmastlock", "JustSetIP0controllable_nstart", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP0controllable_nstart = 1;;\
    }
    );
s.add_location("Process0", "JustSetIP0controllable_hmaster1", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process0", "JustSetIP0controllable_nstart", "JustSetIP0controllable_hmaster1", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP0controllable_hmaster1 = 0;;\
    }
    );
s.add_edge("Process0", "JustSetIP0controllable_nstart", "JustSetIP0controllable_hmaster1", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP0controllable_hmaster1 = 1;;\
    }
    );
s.add_location("Process0", "JustSetIP0controllable_locked", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process0", "JustSetIP0controllable_hmaster1", "JustSetIP0controllable_locked", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP0controllable_locked = 0;;\
    }
    );
s.add_edge("Process0", "JustSetIP0controllable_hmaster1", "JustSetIP0controllable_locked", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP0controllable_locked = 1;;\
    }
    );
s.add_location("Process0", "JustSetIP0controllable_hmaster0", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process0", "JustSetIP0controllable_locked", "JustSetIP0controllable_hmaster0", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP0controllable_hmaster0 = 0;;\
    }
    );
s.add_edge("Process0", "JustSetIP0controllable_locked", "JustSetIP0controllable_hmaster0", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP0controllable_hmaster0 = 1;;\
    }
    );
s.add_location("Process0", "JustSetIP0controllable_hgrant1", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process0", "JustSetIP0controllable_hmaster0", "JustSetIP0controllable_hgrant1", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP0controllable_hgrant1 = 0;;\
    }
    );
s.add_edge("Process0", "JustSetIP0controllable_hmaster0", "JustSetIP0controllable_hgrant1", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP0controllable_hgrant1 = 1;;\
    }
    );
s.add_location("Process0", "JustSetIP0controllable_busreq", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process0", "JustSetIP0controllable_hgrant1", "JustSetIP0controllable_busreq", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP0controllable_busreq = 0;;\
    }
    );
s.add_edge("Process0", "JustSetIP0controllable_hgrant1", "JustSetIP0controllable_busreq", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP0controllable_busreq = 1;;\
    }
    );
s.add_location("Process0", "JustSetIP0controllable_hgrant2", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process0", "JustSetIP0controllable_busreq", "JustSetIP0controllable_hgrant2", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP0controllable_hgrant2 = 0;;\
    }
    );
s.add_edge("Process0", "JustSetIP0controllable_busreq", "JustSetIP0controllable_hgrant2", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP0controllable_hgrant2 = 1;;\
    }
    );
s.add_location("Process0", "JustSetIP0controllable_ndecide", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process0", "JustSetIP0controllable_hgrant2", "JustSetIP0controllable_ndecide", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP0controllable_ndecide = 0;;\
    }
    );
s.add_edge("Process0", "JustSetIP0controllable_hgrant2", "JustSetIP0controllable_ndecide", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP0controllable_ndecide = 1;;\
    }
    );
s.add_location("Process0", "JustSetIP0controllable_nhgrant0", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process0", "JustSetIP0controllable_ndecide", "JustSetIP0controllable_nhgrant0", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP0controllable_nhgrant0 = 0;;\
    }
    );
s.add_edge("Process0", "JustSetIP0controllable_ndecide", "JustSetIP0controllable_nhgrant0", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.IP0controllable_nhgrant0 = 1;;\
    }
    );
s.add_location("Process0", "UpdatedLP0n41", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process0", "JustSetIP0controllable_nhgrant0", "UpdatedLP0n41", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.LP0n41 = 1;;\
    }
    );
s.add_location("Process0", "UpdatedLP0reg_controllable_hgrant2_out", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process0", "UpdatedLP0n41", "UpdatedLP0reg_controllable_hgrant2_out", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.LP0reg_controllable_hgrant2_out = (_l.IP0controllable_hgrant2);;\
    }
    );
s.add_location("Process0", "UpdatedLP0reg_controllable_hmaster1_out", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process0", "UpdatedLP0reg_controllable_hgrant2_out", "UpdatedLP0reg_controllable_hmaster1_out", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.LP0reg_controllable_hmaster1_out = (_l.IP0controllable_hmaster1);;\
    }
    );
s.add_location("Process0", "UpdatedLP0sys_fair0done_out", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process0", "UpdatedLP0reg_controllable_hmaster1_out", "UpdatedLP0sys_fair0done_out", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.LP0sys_fair0done_out = ((1-((1-((1-((_l.LP0sys_fair4done_out) * (_l.LP0n41))) * ((1-((1-(_l.IP0controllable_hmaster0)) * (_l.IP0controllable_hmaster1))) * (_l.IP0i_hbusreq2)))) * ((1-((1-((_l.LP0sys_fair3done_out) * (_l.LP0n41))) * ((1-((_l.IP0controllable_hmaster0) * (1-(_l.IP0controllable_hmaster1)))) * (_l.IP0i_hbusreq1)))) * ((1-((1-((_l.LP0sys_fair2done_out) * (_l.LP0n41))) * ((1-((1-(_l.IP0controllable_hmaster0)) * (1-(_l.IP0controllable_hmaster1)))) * (_l.IP0i_hbusreq0)))) * ((1-((1-((_l.LP0sys_fair1done_out) * (_l.LP0n41))) * (1-((1-((_l.LP0reg_stateG3_2_out) * (_l.LP0n41))) * ((1-((_l.LP0reg_stateG3_1_out) * (_l.LP0n41))) * (1-((_l.LP0reg_stateG3_0_out) * (_l.LP0n41)))))))) * (1-((1-((_l.LP0sys_fair0done_out) * (_l.LP0n41))) * ((_l.LP0reg_stateG2_out) * (_l.LP0n41))))))))) * (1-((1-((_l.LP0sys_fair0done_out) * (_l.LP0n41))) * ((_l.LP0reg_stateG2_out) * (_l.LP0n41)))));;\
    }
    );
s.add_location("Process0", "UpdatedLP0reg_stateG3_0_out", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process0", "UpdatedLP0sys_fair0done_out", "UpdatedLP0reg_stateG3_0_out", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.LP0reg_stateG3_0_out = (1-((1-(((1-(((1-((_l.LP0reg_stateG3_2_out) * (_l.LP0n41))) * (_l.IP0i_hready)) * ((_l.LP0reg_stateG3_0_out) * (_l.LP0n41)))) * (1-((1-((1-((_l.LP0reg_stateG3_2_out) * (_l.LP0n41))) * (_l.IP0i_hready))) * (1-((_l.LP0reg_stateG3_0_out) * (_l.LP0n41)))))) * (1-((1-((_l.LP0reg_stateG3_1_out) * (_l.LP0n41))) * (1-((_l.LP0reg_stateG3_0_out) * (_l.LP0n41))))))) * (1-((((((1-(_l.IP0controllable_nstart)) * (_l.IP0controllable_hmastlock)) * (1-(_l.IP0i_hburst0))) * ((1-((_l.LP0reg_stateG3_2_out) * (_l.LP0n41))) * ((1-((_l.LP0reg_stateG3_1_out) * (_l.LP0n41))) * (1-((_l.LP0reg_stateG3_0_out) * (_l.LP0n41)))))) * (_l.IP0i_hburst1)) * (1-(_l.IP0i_hready))))));;\
    }
    );
s.add_location("Process0", "UpdatedLP0env_fair1done_out", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process0", "UpdatedLP0reg_stateG3_0_out", "UpdatedLP0env_fair1done_out", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.LP0env_fair1done_out = (((((1-((1-((_l.LP0sys_fair4done_out) * (_l.LP0n41))) * (1-((1-((1-(_l.IP0controllable_hmaster0)) * (_l.IP0controllable_hmaster1))) * (_l.IP0i_hbusreq2))))) * ((1-((1-((_l.LP0sys_fair3done_out) * (_l.LP0n41))) * (1-((1-((_l.IP0controllable_hmaster0) * (1-(_l.IP0controllable_hmaster1)))) * (_l.IP0i_hbusreq1))))) * ((1-((1-((_l.LP0sys_fair2done_out) * (_l.LP0n41))) * (1-((1-((1-(_l.IP0controllable_hmaster0)) * (1-(_l.IP0controllable_hmaster1)))) * (_l.IP0i_hbusreq0))))) * ((1-((1-((_l.LP0sys_fair1done_out) * (_l.LP0n41))) * ((1-((_l.LP0reg_stateG3_2_out) * (_l.LP0n41))) * ((1-((_l.LP0reg_stateG3_1_out) * (_l.LP0n41))) * (1-((_l.LP0reg_stateG3_0_out) * (_l.LP0n41))))))) * (1-((1-((_l.LP0sys_fair0done_out) * (_l.LP0n41))) * (1-((_l.LP0reg_stateG2_out) * (_l.LP0n41))))))))) * (1-((1-((1-((_l.LP0sys_fair4done_out) * (_l.LP0n41))) * ((1-((1-(_l.IP0controllable_hmaster0)) * (_l.IP0controllable_hmaster1))) * (_l.IP0i_hbusreq2)))) * ((1-((1-((_l.LP0sys_fair3done_out) * (_l.LP0n41))) * ((1-((_l.IP0controllable_hmaster0) * (1-(_l.IP0controllable_hmaster1)))) * (_l.IP0i_hbusreq1)))) * ((1-((1-((_l.LP0sys_fair2done_out) * (_l.LP0n41))) * ((1-((1-(_l.IP0controllable_hmaster0)) * (1-(_l.IP0controllable_hmaster1)))) * (_l.IP0i_hbusreq0)))) * ((1-((1-((_l.LP0sys_fair1done_out) * (_l.LP0n41))) * (1-((1-((_l.LP0reg_stateG3_2_out) * (_l.LP0n41))) * ((1-((_l.LP0reg_stateG3_1_out) * (_l.LP0n41))) * (1-((_l.LP0reg_stateG3_0_out) * (_l.LP0n41)))))))) * (1-((1-((_l.LP0sys_fair0done_out) * (_l.LP0n41))) * ((_l.LP0reg_stateG2_out) * (_l.LP0n41)))))))))) * (1-((1-((1-((_l.LP0env_fair0done_out) * (_l.LP0n41))) * ((_l.LP0reg_stateA1_out) * (_l.LP0n41)))) * (1-((1-((_l.LP0env_fair1done_out) * (_l.LP0n41))) * (1-(_l.IP0i_hready))))))) * (1-((1-((_l.LP0env_fair1done_out) * (_l.LP0n41))) * (1-(_l.IP0i_hready)))));;\
    }
    );
s.add_location("Process0", "UpdatedLP0reg_controllable_locked_out", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process0", "UpdatedLP0env_fair1done_out", "UpdatedLP0reg_controllable_locked_out", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.LP0reg_controllable_locked_out = (_l.IP0controllable_locked);;\
    }
    );
s.add_location("Process0", "UpdatedLP0sys_fair3done_out", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process0", "UpdatedLP0reg_controllable_locked_out", "UpdatedLP0sys_fair3done_out", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.LP0sys_fair3done_out = ((1-((1-((1-((_l.LP0sys_fair4done_out) * (_l.LP0n41))) * ((1-((1-(_l.IP0controllable_hmaster0)) * (_l.IP0controllable_hmaster1))) * (_l.IP0i_hbusreq2)))) * ((1-((1-((_l.LP0sys_fair3done_out) * (_l.LP0n41))) * ((1-((_l.IP0controllable_hmaster0) * (1-(_l.IP0controllable_hmaster1)))) * (_l.IP0i_hbusreq1)))) * ((1-((1-((_l.LP0sys_fair2done_out) * (_l.LP0n41))) * ((1-((1-(_l.IP0controllable_hmaster0)) * (1-(_l.IP0controllable_hmaster1)))) * (_l.IP0i_hbusreq0)))) * ((1-((1-((_l.LP0sys_fair1done_out) * (_l.LP0n41))) * (1-((1-((_l.LP0reg_stateG3_2_out) * (_l.LP0n41))) * ((1-((_l.LP0reg_stateG3_1_out) * (_l.LP0n41))) * (1-((_l.LP0reg_stateG3_0_out) * (_l.LP0n41)))))))) * (1-((1-((_l.LP0sys_fair0done_out) * (_l.LP0n41))) * ((_l.LP0reg_stateG2_out) * (_l.LP0n41))))))))) * (1-((1-((_l.LP0sys_fair3done_out) * (_l.LP0n41))) * ((1-((_l.IP0controllable_hmaster0) * (1-(_l.IP0controllable_hmaster1)))) * (_l.IP0i_hbusreq1)))));;\
    }
    );
s.add_location("Process0", "UpdatedLP0reg_stateG3_1_out", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process0", "UpdatedLP0sys_fair3done_out", "UpdatedLP0reg_stateG3_1_out", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.LP0reg_stateG3_1_out = (1-(((1-(((1-((_l.LP0reg_stateG3_1_out) * (_l.LP0n41))) * ((_l.LP0reg_stateG3_0_out) * (_l.LP0n41))) * ((1-((_l.LP0reg_stateG3_2_out) * (_l.LP0n41))) * (_l.IP0i_hready)))) * (1-((1-(((((_l.LP0reg_stateG3_1_out) * (_l.LP0n41)) * ((_l.LP0reg_stateG3_0_out) * (_l.LP0n41))) * (1-((_l.LP0reg_stateG3_2_out) * (_l.LP0n41)))) * (_l.IP0i_hready))) * ((_l.LP0reg_stateG3_1_out) * (_l.LP0n41))))) * (1-((((((1-(_l.IP0controllable_nstart)) * (_l.IP0controllable_hmastlock)) * (1-(_l.IP0i_hburst0))) * ((1-((_l.LP0reg_stateG3_2_out) * (_l.LP0n41))) * ((1-((_l.LP0reg_stateG3_1_out) * (_l.LP0n41))) * (1-((_l.LP0reg_stateG3_0_out) * (_l.LP0n41)))))) * (_l.IP0i_hburst1)) * (_l.IP0i_hready)))));;\
    }
    );
s.add_location("Process0", "UpdatedLP0reg_controllable_ndecide_out", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process0", "UpdatedLP0reg_stateG3_1_out", "UpdatedLP0reg_controllable_ndecide_out", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.LP0reg_controllable_ndecide_out = (_l.IP0controllable_ndecide);;\
    }
    );
s.add_location("Process0", "UpdatedLP0reg_stateG3_2_out", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process0", "UpdatedLP0reg_controllable_ndecide_out", "UpdatedLP0reg_stateG3_2_out", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.LP0reg_stateG3_2_out = (1-((1-((1-(((1-((_l.LP0reg_stateG3_1_out) * (_l.LP0n41))) * (1-((_l.LP0reg_stateG3_0_out) * (_l.LP0n41)))) * (_l.IP0i_hready))) * ((_l.LP0reg_stateG3_2_out) * (_l.LP0n41)))) * (1-(((((_l.LP0reg_stateG3_1_out) * (_l.LP0n41)) * ((_l.LP0reg_stateG3_0_out) * (_l.LP0n41))) * (1-((_l.LP0reg_stateG3_2_out) * (_l.LP0n41)))) * (_l.IP0i_hready)))));;\
    }
    );
s.add_location("Process0", "UpdatedLP0reg_i_hbusreq0_out", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process0", "UpdatedLP0reg_stateG3_2_out", "UpdatedLP0reg_i_hbusreq0_out", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.LP0reg_i_hbusreq0_out = (_l.IP0i_hbusreq0);;\
    }
    );
s.add_location("Process0", "UpdatedLP0reg_controllable_busreq_out", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process0", "UpdatedLP0reg_i_hbusreq0_out", "UpdatedLP0reg_controllable_busreq_out", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.LP0reg_controllable_busreq_out = (_l.IP0controllable_busreq);;\
    }
    );
s.add_location("Process0", "UpdatedLP0reg_controllable_nstart_out", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process0", "UpdatedLP0reg_controllable_busreq_out", "UpdatedLP0reg_controllable_nstart_out", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.LP0reg_controllable_nstart_out = (_l.IP0controllable_nstart);;\
    }
    );
s.add_location("Process0", "UpdatedLP0reg_i_hbusreq1_out", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process0", "UpdatedLP0reg_controllable_nstart_out", "UpdatedLP0reg_i_hbusreq1_out", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.LP0reg_i_hbusreq1_out = (_l.IP0i_hbusreq1);;\
    }
    );
s.add_location("Process0", "UpdatedLP0sys_fair1done_out", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process0", "UpdatedLP0reg_i_hbusreq1_out", "UpdatedLP0sys_fair1done_out", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.LP0sys_fair1done_out = ((1-((1-((1-((_l.LP0sys_fair4done_out) * (_l.LP0n41))) * ((1-((1-(_l.IP0controllable_hmaster0)) * (_l.IP0controllable_hmaster1))) * (_l.IP0i_hbusreq2)))) * ((1-((1-((_l.LP0sys_fair3done_out) * (_l.LP0n41))) * ((1-((_l.IP0controllable_hmaster0) * (1-(_l.IP0controllable_hmaster1)))) * (_l.IP0i_hbusreq1)))) * ((1-((1-((_l.LP0sys_fair2done_out) * (_l.LP0n41))) * ((1-((1-(_l.IP0controllable_hmaster0)) * (1-(_l.IP0controllable_hmaster1)))) * (_l.IP0i_hbusreq0)))) * ((1-((1-((_l.LP0sys_fair1done_out) * (_l.LP0n41))) * (1-((1-((_l.LP0reg_stateG3_2_out) * (_l.LP0n41))) * ((1-((_l.LP0reg_stateG3_1_out) * (_l.LP0n41))) * (1-((_l.LP0reg_stateG3_0_out) * (_l.LP0n41)))))))) * (1-((1-((_l.LP0sys_fair0done_out) * (_l.LP0n41))) * ((_l.LP0reg_stateG2_out) * (_l.LP0n41))))))))) * (1-((1-((_l.LP0sys_fair1done_out) * (_l.LP0n41))) * (1-((1-((_l.LP0reg_stateG3_2_out) * (_l.LP0n41))) * ((1-((_l.LP0reg_stateG3_1_out) * (_l.LP0n41))) * (1-((_l.LP0reg_stateG3_0_out) * (_l.LP0n41)))))))));;\
    }
    );
s.add_location("Process0", "UpdatedLP0reg_stateG2_out", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process0", "UpdatedLP0sys_fair1done_out", "UpdatedLP0reg_stateG2_out", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.LP0reg_stateG2_out = (1-((1-(((1-((_l.LP0reg_stateG2_out) * (_l.LP0n41))) * (1-(_l.IP0i_hburst1))) * (((1-(_l.IP0controllable_nstart)) * (_l.IP0controllable_hmastlock)) * (1-(_l.IP0i_hburst0))))) * (1-(((_l.LP0reg_stateG2_out) * (_l.LP0n41)) * (_l.IP0controllable_busreq)))));;\
    }
    );
s.add_location("Process0", "UpdatedLP0reg_stateG10_1_out", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process0", "UpdatedLP0reg_stateG2_out", "UpdatedLP0reg_stateG10_1_out", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.LP0reg_stateG10_1_out = ((1-((1-((_l.LP0reg_stateG10_1_out) * (_l.LP0n41))) * (_l.IP0controllable_hgrant1))) * (1-(_l.IP0i_hbusreq1)));;\
    }
    );
s.add_location("Process0", "UpdatedLP0env_fair0done_out", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process0", "UpdatedLP0reg_stateG10_1_out", "UpdatedLP0env_fair0done_out", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.LP0env_fair0done_out = (((((1-((1-((_l.LP0sys_fair4done_out) * (_l.LP0n41))) * (1-((1-((1-(_l.IP0controllable_hmaster0)) * (_l.IP0controllable_hmaster1))) * (_l.IP0i_hbusreq2))))) * ((1-((1-((_l.LP0sys_fair3done_out) * (_l.LP0n41))) * (1-((1-((_l.IP0controllable_hmaster0) * (1-(_l.IP0controllable_hmaster1)))) * (_l.IP0i_hbusreq1))))) * ((1-((1-((_l.LP0sys_fair2done_out) * (_l.LP0n41))) * (1-((1-((1-(_l.IP0controllable_hmaster0)) * (1-(_l.IP0controllable_hmaster1)))) * (_l.IP0i_hbusreq0))))) * ((1-((1-((_l.LP0sys_fair1done_out) * (_l.LP0n41))) * ((1-((_l.LP0reg_stateG3_2_out) * (_l.LP0n41))) * ((1-((_l.LP0reg_stateG3_1_out) * (_l.LP0n41))) * (1-((_l.LP0reg_stateG3_0_out) * (_l.LP0n41))))))) * (1-((1-((_l.LP0sys_fair0done_out) * (_l.LP0n41))) * (1-((_l.LP0reg_stateG2_out) * (_l.LP0n41))))))))) * (1-((1-((1-((_l.LP0sys_fair4done_out) * (_l.LP0n41))) * ((1-((1-(_l.IP0controllable_hmaster0)) * (_l.IP0controllable_hmaster1))) * (_l.IP0i_hbusreq2)))) * ((1-((1-((_l.LP0sys_fair3done_out) * (_l.LP0n41))) * ((1-((_l.IP0controllable_hmaster0) * (1-(_l.IP0controllable_hmaster1)))) * (_l.IP0i_hbusreq1)))) * ((1-((1-((_l.LP0sys_fair2done_out) * (_l.LP0n41))) * ((1-((1-(_l.IP0controllable_hmaster0)) * (1-(_l.IP0controllable_hmaster1)))) * (_l.IP0i_hbusreq0)))) * ((1-((1-((_l.LP0sys_fair1done_out) * (_l.LP0n41))) * (1-((1-((_l.LP0reg_stateG3_2_out) * (_l.LP0n41))) * ((1-((_l.LP0reg_stateG3_1_out) * (_l.LP0n41))) * (1-((_l.LP0reg_stateG3_0_out) * (_l.LP0n41)))))))) * (1-((1-((_l.LP0sys_fair0done_out) * (_l.LP0n41))) * ((_l.LP0reg_stateG2_out) * (_l.LP0n41)))))))))) * (1-((1-((1-((_l.LP0env_fair0done_out) * (_l.LP0n41))) * ((_l.LP0reg_stateA1_out) * (_l.LP0n41)))) * (1-((1-((_l.LP0env_fair1done_out) * (_l.LP0n41))) * (1-(_l.IP0i_hready))))))) * (1-((1-((_l.LP0env_fair0done_out) * (_l.LP0n41))) * ((_l.LP0reg_stateA1_out) * (_l.LP0n41)))));;\
    }
    );
s.add_location("Process0", "UpdatedLP0reg_controllable_nhgrant0_out", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process0", "UpdatedLP0env_fair0done_out", "UpdatedLP0reg_controllable_nhgrant0_out", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.LP0reg_controllable_nhgrant0_out = (_l.IP0controllable_nhgrant0);;\
    }
    );
s.add_location("Process0", "UpdatedLP0reg_i_hlock2_out", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process0", "UpdatedLP0reg_controllable_nhgrant0_out", "UpdatedLP0reg_i_hlock2_out", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.LP0reg_i_hlock2_out = (_l.IP0i_hlock2);;\
    }
    );
s.add_location("Process0", "UpdatedLP0reg_stateG10_2_out", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process0", "UpdatedLP0reg_i_hlock2_out", "UpdatedLP0reg_stateG10_2_out", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.LP0reg_stateG10_2_out = ((1-((1-((_l.LP0reg_stateG10_2_out) * (_l.LP0n41))) * (_l.IP0controllable_hgrant2))) * (1-(_l.IP0i_hbusreq2)));;\
    }
    );
s.add_location("Process0", "UpdatedLP0reg_stateA1_out", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process0", "UpdatedLP0reg_stateG10_2_out", "UpdatedLP0reg_stateA1_out", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.LP0reg_stateA1_out = (1-((1-(((_l.LP0reg_stateA1_out) * (_l.LP0n41)) * (_l.IP0controllable_busreq))) * (1-(((1-(_l.IP0i_hburst0)) * (1-(_l.IP0i_hburst1))) * ((1-((_l.LP0reg_stateA1_out) * (_l.LP0n41))) * (_l.IP0controllable_hmastlock))))));;\
    }
    );
s.add_location("Process0", "UpdatedLP0reg_controllable_hmastlock_out", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process0", "UpdatedLP0reg_stateA1_out", "UpdatedLP0reg_controllable_hmastlock_out", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.LP0reg_controllable_hmastlock_out = (_l.IP0controllable_hmastlock);;\
    }
    );
s.add_location("Process0", "UpdatedLP0sys_fair4done_out", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process0", "UpdatedLP0reg_controllable_hmastlock_out", "UpdatedLP0sys_fair4done_out", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.LP0sys_fair4done_out = ((1-((1-((1-((_l.LP0sys_fair4done_out) * (_l.LP0n41))) * ((1-((1-(_l.IP0controllable_hmaster0)) * (_l.IP0controllable_hmaster1))) * (_l.IP0i_hbusreq2)))) * ((1-((1-((_l.LP0sys_fair3done_out) * (_l.LP0n41))) * ((1-((_l.IP0controllable_hmaster0) * (1-(_l.IP0controllable_hmaster1)))) * (_l.IP0i_hbusreq1)))) * ((1-((1-((_l.LP0sys_fair2done_out) * (_l.LP0n41))) * ((1-((1-(_l.IP0controllable_hmaster0)) * (1-(_l.IP0controllable_hmaster1)))) * (_l.IP0i_hbusreq0)))) * ((1-((1-((_l.LP0sys_fair1done_out) * (_l.LP0n41))) * (1-((1-((_l.LP0reg_stateG3_2_out) * (_l.LP0n41))) * ((1-((_l.LP0reg_stateG3_1_out) * (_l.LP0n41))) * (1-((_l.LP0reg_stateG3_0_out) * (_l.LP0n41)))))))) * (1-((1-((_l.LP0sys_fair0done_out) * (_l.LP0n41))) * ((_l.LP0reg_stateG2_out) * (_l.LP0n41))))))))) * (1-((1-((_l.LP0sys_fair4done_out) * (_l.LP0n41))) * ((1-((1-(_l.IP0controllable_hmaster0)) * (_l.IP0controllable_hmaster1))) * (_l.IP0i_hbusreq2)))));;\
    }
    );
s.add_location("Process0", "UpdatedLP0reg_i_hbusreq2_out", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process0", "UpdatedLP0sys_fair4done_out", "UpdatedLP0reg_i_hbusreq2_out", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.LP0reg_i_hbusreq2_out = (_l.IP0i_hbusreq2);;\
    }
    );
s.add_location("Process0", "UpdatedLP0reg_i_hlock1_out", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process0", "UpdatedLP0reg_i_hbusreq2_out", "UpdatedLP0reg_i_hlock1_out", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.LP0reg_i_hlock1_out = (_l.IP0i_hlock1);;\
    }
    );
s.add_location("Process0", "UpdatedLP0fair_cnt0_out", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process0", "UpdatedLP0reg_i_hlock1_out", "UpdatedLP0fair_cnt0_out", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.LP0fair_cnt0_out = (((1-((1-((1-((1-((_l.LP0env_fair0done_out) * (_l.LP0n41))) * ((_l.LP0reg_stateA1_out) * (_l.LP0n41)))) * (1-((1-((_l.LP0env_fair1done_out) * (_l.LP0n41))) * (1-(_l.IP0i_hready)))))) * (1-((_l.LP0fair_cnt0_out) * (_l.LP0n41))))) * (1-(((1-((1-((_l.LP0env_fair0done_out) * (_l.LP0n41))) * ((_l.LP0reg_stateA1_out) * (_l.LP0n41)))) * (1-((1-((_l.LP0env_fair1done_out) * (_l.LP0n41))) * (1-(_l.IP0i_hready))))) * ((_l.LP0fair_cnt0_out) * (_l.LP0n41))))) * (((1-((1-((_l.LP0sys_fair4done_out) * (_l.LP0n41))) * (1-((1-((1-(_l.IP0controllable_hmaster0)) * (_l.IP0controllable_hmaster1))) * (_l.IP0i_hbusreq2))))) * ((1-((1-((_l.LP0sys_fair3done_out) * (_l.LP0n41))) * (1-((1-((_l.IP0controllable_hmaster0) * (1-(_l.IP0controllable_hmaster1)))) * (_l.IP0i_hbusreq1))))) * ((1-((1-((_l.LP0sys_fair2done_out) * (_l.LP0n41))) * (1-((1-((1-(_l.IP0controllable_hmaster0)) * (1-(_l.IP0controllable_hmaster1)))) * (_l.IP0i_hbusreq0))))) * ((1-((1-((_l.LP0sys_fair1done_out) * (_l.LP0n41))) * ((1-((_l.LP0reg_stateG3_2_out) * (_l.LP0n41))) * ((1-((_l.LP0reg_stateG3_1_out) * (_l.LP0n41))) * (1-((_l.LP0reg_stateG3_0_out) * (_l.LP0n41))))))) * (1-((1-((_l.LP0sys_fair0done_out) * (_l.LP0n41))) * (1-((_l.LP0reg_stateG2_out) * (_l.LP0n41))))))))) * (1-((1-((1-((_l.LP0sys_fair4done_out) * (_l.LP0n41))) * ((1-((1-(_l.IP0controllable_hmaster0)) * (_l.IP0controllable_hmaster1))) * (_l.IP0i_hbusreq2)))) * ((1-((1-((_l.LP0sys_fair3done_out) * (_l.LP0n41))) * ((1-((_l.IP0controllable_hmaster0) * (1-(_l.IP0controllable_hmaster1)))) * (_l.IP0i_hbusreq1)))) * ((1-((1-((_l.LP0sys_fair2done_out) * (_l.LP0n41))) * ((1-((1-(_l.IP0controllable_hmaster0)) * (1-(_l.IP0controllable_hmaster1)))) * (_l.IP0i_hbusreq0)))) * ((1-((1-((_l.LP0sys_fair1done_out) * (_l.LP0n41))) * (1-((1-((_l.LP0reg_stateG3_2_out) * (_l.LP0n41))) * ((1-((_l.LP0reg_stateG3_1_out) * (_l.LP0n41))) * (1-((_l.LP0reg_stateG3_0_out) * (_l.LP0n41)))))))) * (1-((1-((_l.LP0sys_fair0done_out) * (_l.LP0n41))) * ((_l.LP0reg_stateG2_out) * (_l.LP0n41)))))))))));;\
    }
    );
s.add_location("Process0", "UpdatedLP0fair_cnt1_out", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process0", "UpdatedLP0fair_cnt0_out", "UpdatedLP0fair_cnt1_out", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.LP0fair_cnt1_out = ((1-((1-((((1-((1-((_l.LP0env_fair0done_out) * (_l.LP0n41))) * ((_l.LP0reg_stateA1_out) * (_l.LP0n41)))) * (1-((1-((_l.LP0env_fair1done_out) * (_l.LP0n41))) * (1-(_l.IP0i_hready))))) * ((_l.LP0fair_cnt0_out) * (_l.LP0n41))) * (1-((_l.LP0fair_cnt1_out) * (_l.LP0n41))))) * (1-((1-(((1-((1-((_l.LP0env_fair0done_out) * (_l.LP0n41))) * ((_l.LP0reg_stateA1_out) * (_l.LP0n41)))) * (1-((1-((_l.LP0env_fair1done_out) * (_l.LP0n41))) * (1-(_l.IP0i_hready))))) * ((_l.LP0fair_cnt0_out) * (_l.LP0n41)))) * ((_l.LP0fair_cnt1_out) * (_l.LP0n41)))))) * (((1-((1-((_l.LP0sys_fair4done_out) * (_l.LP0n41))) * (1-((1-((1-(_l.IP0controllable_hmaster0)) * (_l.IP0controllable_hmaster1))) * (_l.IP0i_hbusreq2))))) * ((1-((1-((_l.LP0sys_fair3done_out) * (_l.LP0n41))) * (1-((1-((_l.IP0controllable_hmaster0) * (1-(_l.IP0controllable_hmaster1)))) * (_l.IP0i_hbusreq1))))) * ((1-((1-((_l.LP0sys_fair2done_out) * (_l.LP0n41))) * (1-((1-((1-(_l.IP0controllable_hmaster0)) * (1-(_l.IP0controllable_hmaster1)))) * (_l.IP0i_hbusreq0))))) * ((1-((1-((_l.LP0sys_fair1done_out) * (_l.LP0n41))) * ((1-((_l.LP0reg_stateG3_2_out) * (_l.LP0n41))) * ((1-((_l.LP0reg_stateG3_1_out) * (_l.LP0n41))) * (1-((_l.LP0reg_stateG3_0_out) * (_l.LP0n41))))))) * (1-((1-((_l.LP0sys_fair0done_out) * (_l.LP0n41))) * (1-((_l.LP0reg_stateG2_out) * (_l.LP0n41))))))))) * (1-((1-((1-((_l.LP0sys_fair4done_out) * (_l.LP0n41))) * ((1-((1-(_l.IP0controllable_hmaster0)) * (_l.IP0controllable_hmaster1))) * (_l.IP0i_hbusreq2)))) * ((1-((1-((_l.LP0sys_fair3done_out) * (_l.LP0n41))) * ((1-((_l.IP0controllable_hmaster0) * (1-(_l.IP0controllable_hmaster1)))) * (_l.IP0i_hbusreq1)))) * ((1-((1-((_l.LP0sys_fair2done_out) * (_l.LP0n41))) * ((1-((1-(_l.IP0controllable_hmaster0)) * (1-(_l.IP0controllable_hmaster1)))) * (_l.IP0i_hbusreq0)))) * ((1-((1-((_l.LP0sys_fair1done_out) * (_l.LP0n41))) * (1-((1-((_l.LP0reg_stateG3_2_out) * (_l.LP0n41))) * ((1-((_l.LP0reg_stateG3_1_out) * (_l.LP0n41))) * (1-((_l.LP0reg_stateG3_0_out) * (_l.LP0n41)))))))) * (1-((1-((_l.LP0sys_fair0done_out) * (_l.LP0n41))) * ((_l.LP0reg_stateG2_out) * (_l.LP0n41)))))))))));;\
    }
    );
s.add_location("Process0", "UpdatedLP0fair_cnt2_out", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process0", "UpdatedLP0fair_cnt1_out", "UpdatedLP0fair_cnt2_out", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.LP0fair_cnt2_out = (((1-(((((1-((1-((_l.LP0env_fair0done_out) * (_l.LP0n41))) * ((_l.LP0reg_stateA1_out) * (_l.LP0n41)))) * (1-((1-((_l.LP0env_fair1done_out) * (_l.LP0n41))) * (1-(_l.IP0i_hready))))) * ((_l.LP0fair_cnt0_out) * (_l.LP0n41))) * ((_l.LP0fair_cnt1_out) * (_l.LP0n41))) * ((_l.LP0fair_cnt2_out) * (_l.LP0n41)))) * (1-((1-((((1-((1-((_l.LP0env_fair0done_out) * (_l.LP0n41))) * ((_l.LP0reg_stateA1_out) * (_l.LP0n41)))) * (1-((1-((_l.LP0env_fair1done_out) * (_l.LP0n41))) * (1-(_l.IP0i_hready))))) * ((_l.LP0fair_cnt0_out) * (_l.LP0n41))) * ((_l.LP0fair_cnt1_out) * (_l.LP0n41)))) * (1-((_l.LP0fair_cnt2_out) * (_l.LP0n41)))))) * (((1-((1-((_l.LP0sys_fair4done_out) * (_l.LP0n41))) * (1-((1-((1-(_l.IP0controllable_hmaster0)) * (_l.IP0controllable_hmaster1))) * (_l.IP0i_hbusreq2))))) * ((1-((1-((_l.LP0sys_fair3done_out) * (_l.LP0n41))) * (1-((1-((_l.IP0controllable_hmaster0) * (1-(_l.IP0controllable_hmaster1)))) * (_l.IP0i_hbusreq1))))) * ((1-((1-((_l.LP0sys_fair2done_out) * (_l.LP0n41))) * (1-((1-((1-(_l.IP0controllable_hmaster0)) * (1-(_l.IP0controllable_hmaster1)))) * (_l.IP0i_hbusreq0))))) * ((1-((1-((_l.LP0sys_fair1done_out) * (_l.LP0n41))) * ((1-((_l.LP0reg_stateG3_2_out) * (_l.LP0n41))) * ((1-((_l.LP0reg_stateG3_1_out) * (_l.LP0n41))) * (1-((_l.LP0reg_stateG3_0_out) * (_l.LP0n41))))))) * (1-((1-((_l.LP0sys_fair0done_out) * (_l.LP0n41))) * (1-((_l.LP0reg_stateG2_out) * (_l.LP0n41))))))))) * (1-((1-((1-((_l.LP0sys_fair4done_out) * (_l.LP0n41))) * ((1-((1-(_l.IP0controllable_hmaster0)) * (_l.IP0controllable_hmaster1))) * (_l.IP0i_hbusreq2)))) * ((1-((1-((_l.LP0sys_fair3done_out) * (_l.LP0n41))) * ((1-((_l.IP0controllable_hmaster0) * (1-(_l.IP0controllable_hmaster1)))) * (_l.IP0i_hbusreq1)))) * ((1-((1-((_l.LP0sys_fair2done_out) * (_l.LP0n41))) * ((1-((1-(_l.IP0controllable_hmaster0)) * (1-(_l.IP0controllable_hmaster1)))) * (_l.IP0i_hbusreq0)))) * ((1-((1-((_l.LP0sys_fair1done_out) * (_l.LP0n41))) * (1-((1-((_l.LP0reg_stateG3_2_out) * (_l.LP0n41))) * ((1-((_l.LP0reg_stateG3_1_out) * (_l.LP0n41))) * (1-((_l.LP0reg_stateG3_0_out) * (_l.LP0n41)))))))) * (1-((1-((_l.LP0sys_fair0done_out) * (_l.LP0n41))) * ((_l.LP0reg_stateG2_out) * (_l.LP0n41)))))))))));;\
    }
    );
s.add_location("Process0", "UpdatedLP0env_safe_err_happened_out", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process0", "UpdatedLP0fair_cnt2_out", "UpdatedLP0env_safe_err_happened_out", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.LP0env_safe_err_happened_out = (1-((1-((_l.LP0env_safe_err_happened_out) * (_l.LP0n41))) * ((1-((_l.IP0i_hlock2) * (1-(_l.IP0i_hbusreq2)))) * ((1-((_l.IP0i_hlock1) * (1-(_l.IP0i_hbusreq1)))) * (1-((_l.IP0i_hlock0) * (1-(_l.IP0i_hbusreq0))))))));;\
    }
    );
s.add_location("Process0", "UpdatedLP0reg_i_hlock0_out", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process0", "UpdatedLP0env_safe_err_happened_out", "UpdatedLP0reg_i_hlock0_out", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.LP0reg_i_hlock0_out = (_l.IP0i_hlock0);;\
    }
    );
s.add_location("Process0", "UpdatedLP0reg_i_hready_out", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process0", "UpdatedLP0reg_i_hlock0_out", "UpdatedLP0reg_i_hready_out", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.LP0reg_i_hready_out = (_l.IP0i_hready);;\
    }
    );
s.add_location("Process0", "UpdatedLP0reg_controllable_hgrant1_out", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process0", "UpdatedLP0reg_i_hready_out", "UpdatedLP0reg_controllable_hgrant1_out", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.LP0reg_controllable_hgrant1_out = (_l.IP0controllable_hgrant1);;\
    }
    );
s.add_location("Process0", "UpdatedLP0sys_fair2done_out", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process0", "UpdatedLP0reg_controllable_hgrant1_out", "UpdatedLP0sys_fair2done_out", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.LP0sys_fair2done_out = ((1-((1-((1-((_l.LP0sys_fair4done_out) * (_l.LP0n41))) * ((1-((1-(_l.IP0controllable_hmaster0)) * (_l.IP0controllable_hmaster1))) * (_l.IP0i_hbusreq2)))) * ((1-((1-((_l.LP0sys_fair3done_out) * (_l.LP0n41))) * ((1-((_l.IP0controllable_hmaster0) * (1-(_l.IP0controllable_hmaster1)))) * (_l.IP0i_hbusreq1)))) * ((1-((1-((_l.LP0sys_fair2done_out) * (_l.LP0n41))) * ((1-((1-(_l.IP0controllable_hmaster0)) * (1-(_l.IP0controllable_hmaster1)))) * (_l.IP0i_hbusreq0)))) * ((1-((1-((_l.LP0sys_fair1done_out) * (_l.LP0n41))) * (1-((1-((_l.LP0reg_stateG3_2_out) * (_l.LP0n41))) * ((1-((_l.LP0reg_stateG3_1_out) * (_l.LP0n41))) * (1-((_l.LP0reg_stateG3_0_out) * (_l.LP0n41)))))))) * (1-((1-((_l.LP0sys_fair0done_out) * (_l.LP0n41))) * ((_l.LP0reg_stateG2_out) * (_l.LP0n41))))))))) * (1-((1-((_l.LP0sys_fair2done_out) * (_l.LP0n41))) * ((1-((1-(_l.IP0controllable_hmaster0)) * (1-(_l.IP0controllable_hmaster1)))) * (_l.IP0i_hbusreq0)))));;\
    }
    );
s.add_location("Process0", "UpdatedLP0reg_controllable_hmaster0_out", "", "", syntax::loc_t::COMMITTED);
s.add_edge("Process0", "UpdatedLP0sys_fair2done_out", "UpdatedLP0reg_controllable_hmaster0_out", "", "", "", syntax::layout_true,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.LP0reg_controllable_hmaster0_out = (_l.IP0controllable_hmaster0);;\
    }
    );
s.add_edge("Process0", "UpdatedLP0reg_controllable_hmaster0_out", "w", "", "", "release0!", 
    [](syntax::layout_t const & l){\
    multi::layout_t const & _l = CAST(multi::layout_t const &, l);\
    return _l.running0 == 0;\
    }
    ,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.w0 = 1;;\
    }
    );
s.add_edge("Process0", "UpdatedLP0reg_controllable_hmaster0_out", "w", "", "", "release1!", 
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
    return _l.LP1state_n15 == 0;\
    }
    ,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.w1 = 0;\
    }
    );
s.add_edge("Process1", "w", "dead", "x1 >= 499", "", "", 
    [](syntax::layout_t const & l){\
    multi::layout_t const & _l = CAST(multi::layout_t const &, l);\
    return _l.LP1state_n15 == 0;\
    }
    ,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.dead=1;;\
    }
    );
s.add_edge("Process1", "on0", "up", "x1 >= 500 && x1 <= 1000", "x1", "", 
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
s.add_edge("Process1", "w", "dead", "x1 >= 799", "", "", 
    [](syntax::layout_t const & l){\
    multi::layout_t const & _l = CAST(multi::layout_t const &, l);\
    return _l.LP1state_n15 == 1;\
    }
    ,  [](syntax::layout_t  & l){\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\
    _l.dead=1;;\
    }
    );
s.add_edge("Process1", "on1", "up", "x1 >= 400 && x1 <= 800", "x1", "", 
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
s.add_edge("Process2", "w", "dead", "x2 >= 499", "", "", 
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
s.add_edge("Process2", "w", "dead", "x2 >= 799", "", "", 
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
