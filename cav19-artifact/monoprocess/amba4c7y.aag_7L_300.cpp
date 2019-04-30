#include <iostream>
        #include "syntax/system.hh"
        #include "syntax/sync_product.hh"
        namespace monoprocess {
        class layout_t : public syntax::layout_t {
        public:
        
	bool Ii_hbusreq0;
	bool Ii_hbusreq1;
	bool Ii_hbusreq2;
	bool Ii_hbusreq3;
	bool Ii_hburst1;
	bool Ii_hburst0;
	bool Ii_hlock0;
	bool Ii_hlock1;
	bool Ii_hlock2;
	bool Ii_hlock3;
	bool Ii_hready;
	bool Icontrollable_hmastlock;
	bool Icontrollable_nstart;
	bool Icontrollable_hmaster1;
	bool Icontrollable_locked;
	bool Icontrollable_hmaster0;
	bool Icontrollable_hgrant1;
	bool Icontrollable_busreq;
	bool Icontrollable_hgrant2;
	bool Icontrollable_hgrant3;
	bool Icontrollable_ndecide;
	bool Icontrollable_nhgrant0;
	bool Ln47;
	bool Lreg_controllable_hgrant2_out;
	bool Lreg_controllable_hmaster1_out;
	bool Lreg_controllable_hgrant3_out;
	bool Lnext_env_fair_out;
	bool Lreg_stateG3_0_out;
	bool Lreg_controllable_locked_out;
	bool Lreg_stateG3_1_out;
	bool Lreg_controllable_ndecide_out;
	bool Lreg_stateG3_2_out;
	bool Lreg_i_hbusreq0_out;
	bool Lreg_controllable_busreq_out;
	bool Lreg_controllable_nstart_out;
	bool Lreg_i_hbusreq1_out;
	bool Lreg_i_hlock3_out;
	bool Lreg_stateG2_out;
	bool Lreg_stateG10_1_out;
	bool Lreg_controllable_nhgrant0_out;
	bool Lreg_i_hlock2_out;
	bool Lreg_stateG10_2_out;
	bool Lreg_stateA1_out;
	bool Lreg_controllable_hmastlock_out;
	bool Lreg_i_hbusreq2_out;
	bool Lnext_sys_fair0_out;
	bool Lnext_sys_fair1_out;
	bool Lnext_sys_fair2_out;
	bool Lnext_sys_fair3_out;
	bool Lreg_i_hlock1_out;
	bool Lreg_stateG10_3_out;
	bool Lfair_cnt0_out;
	bool Lfair_cnt1_out;
	bool Lfair_cnt2_out;
	bool Lreg_i_hbusreq3_out;
	bool Lenv_safe_err_happened_out;
	bool Lreg_i_hlock0_out;
	bool Lreg_i_hready_out;
	bool Lreg_controllable_hgrant1_out;
	bool Lreg_controllable_hmaster0_out;
	layout_t(){
		Ii_hbusreq0 = 0;
		Ii_hbusreq1 = 0;
		Ii_hbusreq2 = 0;
		Ii_hbusreq3 = 0;
		Ii_hburst1 = 0;
		Ii_hburst0 = 0;
		Ii_hlock0 = 0;
		Ii_hlock1 = 0;
		Ii_hlock2 = 0;
		Ii_hlock3 = 0;
		Ii_hready = 0;
		Icontrollable_hmastlock = 0;
		Icontrollable_nstart = 0;
		Icontrollable_hmaster1 = 0;
		Icontrollable_locked = 0;
		Icontrollable_hmaster0 = 0;
		Icontrollable_hgrant1 = 0;
		Icontrollable_busreq = 0;
		Icontrollable_hgrant2 = 0;
		Icontrollable_hgrant3 = 0;
		Icontrollable_ndecide = 0;
		Icontrollable_nhgrant0 = 0;
		Ln47 = 0;
		Lreg_controllable_hgrant2_out = 0;
		Lreg_controllable_hmaster1_out = 0;
		Lreg_controllable_hgrant3_out = 0;
		Lnext_env_fair_out = 0;
		Lreg_stateG3_0_out = 0;
		Lreg_controllable_locked_out = 0;
		Lreg_stateG3_1_out = 0;
		Lreg_controllable_ndecide_out = 0;
		Lreg_stateG3_2_out = 0;
		Lreg_i_hbusreq0_out = 0;
		Lreg_controllable_busreq_out = 0;
		Lreg_controllable_nstart_out = 0;
		Lreg_i_hbusreq1_out = 0;
		Lreg_i_hlock3_out = 0;
		Lreg_stateG2_out = 0;
		Lreg_stateG10_1_out = 0;
		Lreg_controllable_nhgrant0_out = 0;
		Lreg_i_hlock2_out = 0;
		Lreg_stateG10_2_out = 0;
		Lreg_stateA1_out = 0;
		Lreg_controllable_hmastlock_out = 0;
		Lreg_i_hbusreq2_out = 0;
		Lnext_sys_fair0_out = 0;
		Lnext_sys_fair1_out = 0;
		Lnext_sys_fair2_out = 0;
		Lnext_sys_fair3_out = 0;
		Lreg_i_hlock1_out = 0;
		Lreg_stateG10_3_out = 0;
		Lfair_cnt0_out = 0;
		Lfair_cnt1_out = 0;
		Lfair_cnt2_out = 0;
		Lreg_i_hbusreq3_out = 0;
		Lenv_safe_err_happened_out = 0;
		Lreg_i_hlock0_out = 0;
		Lreg_i_hready_out = 0;
		Lreg_controllable_hgrant1_out = 0;
		Lreg_controllable_hmaster0_out = 0;
	}
virtual ~layout_t(){}
layout_t (const layout_t &l) = default;

        inline bool operator == (const syntax::layout_t & l) const {
            monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);
        
		if(Ii_hbusreq0 != _l.Ii_hbusreq0) return false;
		if(Ii_hbusreq1 != _l.Ii_hbusreq1) return false;
		if(Ii_hbusreq2 != _l.Ii_hbusreq2) return false;
		if(Ii_hbusreq3 != _l.Ii_hbusreq3) return false;
		if(Ii_hburst1 != _l.Ii_hburst1) return false;
		if(Ii_hburst0 != _l.Ii_hburst0) return false;
		if(Ii_hlock0 != _l.Ii_hlock0) return false;
		if(Ii_hlock1 != _l.Ii_hlock1) return false;
		if(Ii_hlock2 != _l.Ii_hlock2) return false;
		if(Ii_hlock3 != _l.Ii_hlock3) return false;
		if(Ii_hready != _l.Ii_hready) return false;
		if(Icontrollable_hmastlock != _l.Icontrollable_hmastlock) return false;
		if(Icontrollable_nstart != _l.Icontrollable_nstart) return false;
		if(Icontrollable_hmaster1 != _l.Icontrollable_hmaster1) return false;
		if(Icontrollable_locked != _l.Icontrollable_locked) return false;
		if(Icontrollable_hmaster0 != _l.Icontrollable_hmaster0) return false;
		if(Icontrollable_hgrant1 != _l.Icontrollable_hgrant1) return false;
		if(Icontrollable_busreq != _l.Icontrollable_busreq) return false;
		if(Icontrollable_hgrant2 != _l.Icontrollable_hgrant2) return false;
		if(Icontrollable_hgrant3 != _l.Icontrollable_hgrant3) return false;
		if(Icontrollable_ndecide != _l.Icontrollable_ndecide) return false;
		if(Icontrollable_nhgrant0 != _l.Icontrollable_nhgrant0) return false;
		if(Ln47 != _l.Ln47) return false;
		if(Lreg_controllable_hgrant2_out != _l.Lreg_controllable_hgrant2_out) return false;
		if(Lreg_controllable_hmaster1_out != _l.Lreg_controllable_hmaster1_out) return false;
		if(Lreg_controllable_hgrant3_out != _l.Lreg_controllable_hgrant3_out) return false;
		if(Lnext_env_fair_out != _l.Lnext_env_fair_out) return false;
		if(Lreg_stateG3_0_out != _l.Lreg_stateG3_0_out) return false;
		if(Lreg_controllable_locked_out != _l.Lreg_controllable_locked_out) return false;
		if(Lreg_stateG3_1_out != _l.Lreg_stateG3_1_out) return false;
		if(Lreg_controllable_ndecide_out != _l.Lreg_controllable_ndecide_out) return false;
		if(Lreg_stateG3_2_out != _l.Lreg_stateG3_2_out) return false;
		if(Lreg_i_hbusreq0_out != _l.Lreg_i_hbusreq0_out) return false;
		if(Lreg_controllable_busreq_out != _l.Lreg_controllable_busreq_out) return false;
		if(Lreg_controllable_nstart_out != _l.Lreg_controllable_nstart_out) return false;
		if(Lreg_i_hbusreq1_out != _l.Lreg_i_hbusreq1_out) return false;
		if(Lreg_i_hlock3_out != _l.Lreg_i_hlock3_out) return false;
		if(Lreg_stateG2_out != _l.Lreg_stateG2_out) return false;
		if(Lreg_stateG10_1_out != _l.Lreg_stateG10_1_out) return false;
		if(Lreg_controllable_nhgrant0_out != _l.Lreg_controllable_nhgrant0_out) return false;
		if(Lreg_i_hlock2_out != _l.Lreg_i_hlock2_out) return false;
		if(Lreg_stateG10_2_out != _l.Lreg_stateG10_2_out) return false;
		if(Lreg_stateA1_out != _l.Lreg_stateA1_out) return false;
		if(Lreg_controllable_hmastlock_out != _l.Lreg_controllable_hmastlock_out) return false;
		if(Lreg_i_hbusreq2_out != _l.Lreg_i_hbusreq2_out) return false;
		if(Lnext_sys_fair0_out != _l.Lnext_sys_fair0_out) return false;
		if(Lnext_sys_fair1_out != _l.Lnext_sys_fair1_out) return false;
		if(Lnext_sys_fair2_out != _l.Lnext_sys_fair2_out) return false;
		if(Lnext_sys_fair3_out != _l.Lnext_sys_fair3_out) return false;
		if(Lreg_i_hlock1_out != _l.Lreg_i_hlock1_out) return false;
		if(Lreg_stateG10_3_out != _l.Lreg_stateG10_3_out) return false;
		if(Lfair_cnt0_out != _l.Lfair_cnt0_out) return false;
		if(Lfair_cnt1_out != _l.Lfair_cnt1_out) return false;
		if(Lfair_cnt2_out != _l.Lfair_cnt2_out) return false;
		if(Lreg_i_hbusreq3_out != _l.Lreg_i_hbusreq3_out) return false;
		if(Lenv_safe_err_happened_out != _l.Lenv_safe_err_happened_out) return false;
		if(Lreg_i_hlock0_out != _l.Lreg_i_hlock0_out) return false;
		if(Lreg_i_hready_out != _l.Lreg_i_hready_out) return false;
		if(Lreg_controllable_hgrant1_out != _l.Lreg_controllable_hgrant1_out) return false;
		if(Lreg_controllable_hmaster0_out != _l.Lreg_controllable_hmaster0_out) return false;
return true;
}

        inline size_t hash() const {
        size_t seed = global_t::instance().hash_seed();
        
		boost::hash_combine(seed, Ii_hbusreq0);
		boost::hash_combine(seed, Ii_hbusreq1);
		boost::hash_combine(seed, Ii_hbusreq2);
		boost::hash_combine(seed, Ii_hbusreq3);
		boost::hash_combine(seed, Ii_hburst1);
		boost::hash_combine(seed, Ii_hburst0);
		boost::hash_combine(seed, Ii_hlock0);
		boost::hash_combine(seed, Ii_hlock1);
		boost::hash_combine(seed, Ii_hlock2);
		boost::hash_combine(seed, Ii_hlock3);
		boost::hash_combine(seed, Ii_hready);
		boost::hash_combine(seed, Icontrollable_hmastlock);
		boost::hash_combine(seed, Icontrollable_nstart);
		boost::hash_combine(seed, Icontrollable_hmaster1);
		boost::hash_combine(seed, Icontrollable_locked);
		boost::hash_combine(seed, Icontrollable_hmaster0);
		boost::hash_combine(seed, Icontrollable_hgrant1);
		boost::hash_combine(seed, Icontrollable_busreq);
		boost::hash_combine(seed, Icontrollable_hgrant2);
		boost::hash_combine(seed, Icontrollable_hgrant3);
		boost::hash_combine(seed, Icontrollable_ndecide);
		boost::hash_combine(seed, Icontrollable_nhgrant0);
		boost::hash_combine(seed, Ln47);
		boost::hash_combine(seed, Lreg_controllable_hgrant2_out);
		boost::hash_combine(seed, Lreg_controllable_hmaster1_out);
		boost::hash_combine(seed, Lreg_controllable_hgrant3_out);
		boost::hash_combine(seed, Lnext_env_fair_out);
		boost::hash_combine(seed, Lreg_stateG3_0_out);
		boost::hash_combine(seed, Lreg_controllable_locked_out);
		boost::hash_combine(seed, Lreg_stateG3_1_out);
		boost::hash_combine(seed, Lreg_controllable_ndecide_out);
		boost::hash_combine(seed, Lreg_stateG3_2_out);
		boost::hash_combine(seed, Lreg_i_hbusreq0_out);
		boost::hash_combine(seed, Lreg_controllable_busreq_out);
		boost::hash_combine(seed, Lreg_controllable_nstart_out);
		boost::hash_combine(seed, Lreg_i_hbusreq1_out);
		boost::hash_combine(seed, Lreg_i_hlock3_out);
		boost::hash_combine(seed, Lreg_stateG2_out);
		boost::hash_combine(seed, Lreg_stateG10_1_out);
		boost::hash_combine(seed, Lreg_controllable_nhgrant0_out);
		boost::hash_combine(seed, Lreg_i_hlock2_out);
		boost::hash_combine(seed, Lreg_stateG10_2_out);
		boost::hash_combine(seed, Lreg_stateA1_out);
		boost::hash_combine(seed, Lreg_controllable_hmastlock_out);
		boost::hash_combine(seed, Lreg_i_hbusreq2_out);
		boost::hash_combine(seed, Lnext_sys_fair0_out);
		boost::hash_combine(seed, Lnext_sys_fair1_out);
		boost::hash_combine(seed, Lnext_sys_fair2_out);
		boost::hash_combine(seed, Lnext_sys_fair3_out);
		boost::hash_combine(seed, Lreg_i_hlock1_out);
		boost::hash_combine(seed, Lreg_stateG10_3_out);
		boost::hash_combine(seed, Lfair_cnt0_out);
		boost::hash_combine(seed, Lfair_cnt1_out);
		boost::hash_combine(seed, Lfair_cnt2_out);
		boost::hash_combine(seed, Lreg_i_hbusreq3_out);
		boost::hash_combine(seed, Lenv_safe_err_happened_out);
		boost::hash_combine(seed, Lreg_i_hlock0_out);
		boost::hash_combine(seed, Lreg_i_hready_out);
		boost::hash_combine(seed, Lreg_controllable_hgrant1_out);
		boost::hash_combine(seed, Lreg_controllable_hmaster0_out);
return seed;
}

        void output(std::ostream & os) const {
        
		os << "Ii_hbusreq0 = " << Ii_hbusreq0 << ",";
		os << "Ii_hbusreq1 = " << Ii_hbusreq1 << ",";
		os << "Ii_hbusreq2 = " << Ii_hbusreq2 << ",";
		os << "Ii_hbusreq3 = " << Ii_hbusreq3 << ",";
		os << "Ii_hburst1 = " << Ii_hburst1 << ",";
		os << "Ii_hburst0 = " << Ii_hburst0 << ",";
		os << "Ii_hlock0 = " << Ii_hlock0 << ",";
		os << "Ii_hlock1 = " << Ii_hlock1 << ",";
		os << "Ii_hlock2 = " << Ii_hlock2 << ",";
		os << "Ii_hlock3 = " << Ii_hlock3 << ",";
		os << "Ii_hready = " << Ii_hready << ",";
		os << "Icontrollable_hmastlock = " << Icontrollable_hmastlock << ",";
		os << "Icontrollable_nstart = " << Icontrollable_nstart << ",";
		os << "Icontrollable_hmaster1 = " << Icontrollable_hmaster1 << ",";
		os << "Icontrollable_locked = " << Icontrollable_locked << ",";
		os << "Icontrollable_hmaster0 = " << Icontrollable_hmaster0 << ",";
		os << "Icontrollable_hgrant1 = " << Icontrollable_hgrant1 << ",";
		os << "Icontrollable_busreq = " << Icontrollable_busreq << ",";
		os << "Icontrollable_hgrant2 = " << Icontrollable_hgrant2 << ",";
		os << "Icontrollable_hgrant3 = " << Icontrollable_hgrant3 << ",";
		os << "Icontrollable_ndecide = " << Icontrollable_ndecide << ",";
		os << "Icontrollable_nhgrant0 = " << Icontrollable_nhgrant0 << ",";
		os << "Ln47 = " << Ln47 << ",";
		os << "Lreg_controllable_hgrant2_out = " << Lreg_controllable_hgrant2_out << ",";
		os << "Lreg_controllable_hmaster1_out = " << Lreg_controllable_hmaster1_out << ",";
		os << "Lreg_controllable_hgrant3_out = " << Lreg_controllable_hgrant3_out << ",";
		os << "Lnext_env_fair_out = " << Lnext_env_fair_out << ",";
		os << "Lreg_stateG3_0_out = " << Lreg_stateG3_0_out << ",";
		os << "Lreg_controllable_locked_out = " << Lreg_controllable_locked_out << ",";
		os << "Lreg_stateG3_1_out = " << Lreg_stateG3_1_out << ",";
		os << "Lreg_controllable_ndecide_out = " << Lreg_controllable_ndecide_out << ",";
		os << "Lreg_stateG3_2_out = " << Lreg_stateG3_2_out << ",";
		os << "Lreg_i_hbusreq0_out = " << Lreg_i_hbusreq0_out << ",";
		os << "Lreg_controllable_busreq_out = " << Lreg_controllable_busreq_out << ",";
		os << "Lreg_controllable_nstart_out = " << Lreg_controllable_nstart_out << ",";
		os << "Lreg_i_hbusreq1_out = " << Lreg_i_hbusreq1_out << ",";
		os << "Lreg_i_hlock3_out = " << Lreg_i_hlock3_out << ",";
		os << "Lreg_stateG2_out = " << Lreg_stateG2_out << ",";
		os << "Lreg_stateG10_1_out = " << Lreg_stateG10_1_out << ",";
		os << "Lreg_controllable_nhgrant0_out = " << Lreg_controllable_nhgrant0_out << ",";
		os << "Lreg_i_hlock2_out = " << Lreg_i_hlock2_out << ",";
		os << "Lreg_stateG10_2_out = " << Lreg_stateG10_2_out << ",";
		os << "Lreg_stateA1_out = " << Lreg_stateA1_out << ",";
		os << "Lreg_controllable_hmastlock_out = " << Lreg_controllable_hmastlock_out << ",";
		os << "Lreg_i_hbusreq2_out = " << Lreg_i_hbusreq2_out << ",";
		os << "Lnext_sys_fair0_out = " << Lnext_sys_fair0_out << ",";
		os << "Lnext_sys_fair1_out = " << Lnext_sys_fair1_out << ",";
		os << "Lnext_sys_fair2_out = " << Lnext_sys_fair2_out << ",";
		os << "Lnext_sys_fair3_out = " << Lnext_sys_fair3_out << ",";
		os << "Lreg_i_hlock1_out = " << Lreg_i_hlock1_out << ",";
		os << "Lreg_stateG10_3_out = " << Lreg_stateG10_3_out << ",";
		os << "Lfair_cnt0_out = " << Lfair_cnt0_out << ",";
		os << "Lfair_cnt1_out = " << Lfair_cnt1_out << ",";
		os << "Lfair_cnt2_out = " << Lfair_cnt2_out << ",";
		os << "Lreg_i_hbusreq3_out = " << Lreg_i_hbusreq3_out << ",";
		os << "Lenv_safe_err_happened_out = " << Lenv_safe_err_happened_out << ",";
		os << "Lreg_i_hlock0_out = " << Lreg_i_hlock0_out << ",";
		os << "Lreg_i_hready_out = " << Lreg_i_hready_out << ",";
		os << "Lreg_controllable_hgrant1_out = " << Lreg_controllable_hgrant1_out << ",";
		os << "Lreg_controllable_hmaster0_out = " << Lreg_controllable_hmaster0_out << ",";
	}
};
}
void build_model(syntax::system_t & s){
        	s.name("Mono");
        	s.layout_alloc< syntax::layout_T_alloc_t<monoprocess::layout_t> >();
        
s.add_clock("x_46");
s.add_clock("x_48");
s.add_clock("x_50");
s.add_clock("x_52");
s.add_clock("x_54");
s.add_clock("x_56");
s.add_clock("x_58");
s.add_clock("T");
s.add_label("err");
s.add_label("nothing");
s.add_process("Circuit");
s.add_location("Circuit", "init", "", "", syntax::loc_t::INIT | syntax::loc_t::URGENT);
s.add_location("Circuit", "dead", "", "err");
s.add_location("Circuit", "JustSetIi_hbusreq0", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "init", "JustSetIi_hbusreq0", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Ii_hbusreq0=0;;\
                    }
                    
);
s.add_edge("Circuit", "init", "JustSetIi_hbusreq0", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Ii_hbusreq0=1;;\
                    }
                    
);
s.add_location("Circuit", "JustSetIi_hbusreq1", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "JustSetIi_hbusreq0", "JustSetIi_hbusreq1", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Ii_hbusreq1=0;;\
                    }
                    
);
s.add_edge("Circuit", "JustSetIi_hbusreq0", "JustSetIi_hbusreq1", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Ii_hbusreq1=1;;\
                    }
                    
);
s.add_location("Circuit", "JustSetIi_hbusreq2", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "JustSetIi_hbusreq1", "JustSetIi_hbusreq2", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Ii_hbusreq2=0;;\
                    }
                    
);
s.add_edge("Circuit", "JustSetIi_hbusreq1", "JustSetIi_hbusreq2", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Ii_hbusreq2=1;;\
                    }
                    
);
s.add_location("Circuit", "JustSetIi_hbusreq3", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "JustSetIi_hbusreq2", "JustSetIi_hbusreq3", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Ii_hbusreq3=0;;\
                    }
                    
);
s.add_edge("Circuit", "JustSetIi_hbusreq2", "JustSetIi_hbusreq3", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Ii_hbusreq3=1;;\
                    }
                    
);
s.add_location("Circuit", "JustSetIi_hburst1", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "JustSetIi_hbusreq3", "JustSetIi_hburst1", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Ii_hburst1=0;;\
                    }
                    
);
s.add_edge("Circuit", "JustSetIi_hbusreq3", "JustSetIi_hburst1", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Ii_hburst1=1;;\
                    }
                    
);
s.add_location("Circuit", "JustSetIi_hburst0", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "JustSetIi_hburst1", "JustSetIi_hburst0", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Ii_hburst0=0;;\
                    }
                    
);
s.add_edge("Circuit", "JustSetIi_hburst1", "JustSetIi_hburst0", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Ii_hburst0=1;;\
                    }
                    
);
s.add_location("Circuit", "JustSetIi_hlock0", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "JustSetIi_hburst0", "JustSetIi_hlock0", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Ii_hlock0=0;;\
                    }
                    
);
s.add_edge("Circuit", "JustSetIi_hburst0", "JustSetIi_hlock0", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Ii_hlock0=1;;\
                    }
                    
);
s.add_location("Circuit", "JustSetIi_hlock1", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "JustSetIi_hlock0", "JustSetIi_hlock1", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Ii_hlock1=0;;\
                    }
                    
);
s.add_edge("Circuit", "JustSetIi_hlock0", "JustSetIi_hlock1", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Ii_hlock1=1;;\
                    }
                    
);
s.add_location("Circuit", "JustSetIi_hlock2", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "JustSetIi_hlock1", "JustSetIi_hlock2", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Ii_hlock2=0;;\
                    }
                    
);
s.add_edge("Circuit", "JustSetIi_hlock1", "JustSetIi_hlock2", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Ii_hlock2=1;;\
                    }
                    
);
s.add_location("Circuit", "JustSetIi_hlock3", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "JustSetIi_hlock2", "JustSetIi_hlock3", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Ii_hlock3=0;;\
                    }
                    
);
s.add_edge("Circuit", "JustSetIi_hlock2", "JustSetIi_hlock3", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Ii_hlock3=1;;\
                    }
                    
);
s.add_location("Circuit", "JustSetIi_hready", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "JustSetIi_hlock3", "JustSetIi_hready", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Ii_hready=0;;\
                    }
                    
);
s.add_edge("Circuit", "JustSetIi_hlock3", "JustSetIi_hready", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Ii_hready=1;;\
                    }
                    
);
s.add_location("Circuit", "JustSetIcontrollable_hmastlock", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "JustSetIi_hready", "JustSetIcontrollable_hmastlock", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Icontrollable_hmastlock=0;;\
                    }
                    
);
s.add_edge("Circuit", "JustSetIi_hready", "JustSetIcontrollable_hmastlock", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Icontrollable_hmastlock=1;;\
                    }
                    
);
s.add_location("Circuit", "JustSetIcontrollable_nstart", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "JustSetIcontrollable_hmastlock", "JustSetIcontrollable_nstart", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Icontrollable_nstart=0;;\
                    }
                    
);
s.add_edge("Circuit", "JustSetIcontrollable_hmastlock", "JustSetIcontrollable_nstart", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Icontrollable_nstart=1;;\
                    }
                    
);
s.add_location("Circuit", "JustSetIcontrollable_hmaster1", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "JustSetIcontrollable_nstart", "JustSetIcontrollable_hmaster1", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Icontrollable_hmaster1=0;;\
                    }
                    
);
s.add_edge("Circuit", "JustSetIcontrollable_nstart", "JustSetIcontrollable_hmaster1", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Icontrollable_hmaster1=1;;\
                    }
                    
);
s.add_location("Circuit", "JustSetIcontrollable_locked", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "JustSetIcontrollable_hmaster1", "JustSetIcontrollable_locked", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Icontrollable_locked=0;;\
                    }
                    
);
s.add_edge("Circuit", "JustSetIcontrollable_hmaster1", "JustSetIcontrollable_locked", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Icontrollable_locked=1;;\
                    }
                    
);
s.add_location("Circuit", "JustSetIcontrollable_hmaster0", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "JustSetIcontrollable_locked", "JustSetIcontrollable_hmaster0", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Icontrollable_hmaster0=0;;\
                    }
                    
);
s.add_edge("Circuit", "JustSetIcontrollable_locked", "JustSetIcontrollable_hmaster0", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Icontrollable_hmaster0=1;;\
                    }
                    
);
s.add_location("Circuit", "JustSetIcontrollable_hgrant1", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "JustSetIcontrollable_hmaster0", "JustSetIcontrollable_hgrant1", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Icontrollable_hgrant1=0;;\
                    }
                    
);
s.add_edge("Circuit", "JustSetIcontrollable_hmaster0", "JustSetIcontrollable_hgrant1", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Icontrollable_hgrant1=1;;\
                    }
                    
);
s.add_location("Circuit", "JustSetIcontrollable_busreq", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "JustSetIcontrollable_hgrant1", "JustSetIcontrollable_busreq", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Icontrollable_busreq=0;;\
                    }
                    
);
s.add_edge("Circuit", "JustSetIcontrollable_hgrant1", "JustSetIcontrollable_busreq", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Icontrollable_busreq=1;;\
                    }
                    
);
s.add_location("Circuit", "JustSetIcontrollable_hgrant2", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "JustSetIcontrollable_busreq", "JustSetIcontrollable_hgrant2", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Icontrollable_hgrant2=0;;\
                    }
                    
);
s.add_edge("Circuit", "JustSetIcontrollable_busreq", "JustSetIcontrollable_hgrant2", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Icontrollable_hgrant2=1;;\
                    }
                    
);
s.add_location("Circuit", "JustSetIcontrollable_hgrant3", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "JustSetIcontrollable_hgrant2", "JustSetIcontrollable_hgrant3", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Icontrollable_hgrant3=0;;\
                    }
                    
);
s.add_edge("Circuit", "JustSetIcontrollable_hgrant2", "JustSetIcontrollable_hgrant3", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Icontrollable_hgrant3=1;;\
                    }
                    
);
s.add_location("Circuit", "JustSetIcontrollable_ndecide", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "JustSetIcontrollable_hgrant3", "JustSetIcontrollable_ndecide", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Icontrollable_ndecide=0;;\
                    }
                    
);
s.add_edge("Circuit", "JustSetIcontrollable_hgrant3", "JustSetIcontrollable_ndecide", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Icontrollable_ndecide=1;;\
                    }
                    
);
s.add_location("Circuit", "JustSetIcontrollable_nhgrant0", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "JustSetIcontrollable_ndecide", "JustSetIcontrollable_nhgrant0", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Icontrollable_nhgrant0=0;;\
                    }
                    
);
s.add_edge("Circuit", "JustSetIcontrollable_ndecide", "JustSetIcontrollable_nhgrant0", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Icontrollable_nhgrant0=1;;\
                    }
                    
);
s.add_location("Circuit", "UpdatedLn47", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "JustSetIcontrollable_nhgrant0", "UpdatedLn47", "", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Ln47==1;;\
        }
        );
s.add_edge("Circuit", "JustSetIcontrollable_nhgrant0", "UpdatedLn47", "x_46 <= 1000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Ln47 == 1 && _l.Ln47 != 1;\
        }
        );
s.add_edge("Circuit", "JustSetIcontrollable_nhgrant0", "UpdatedLn47", "x_46 <= 1500", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Ln47 == 0 && _l.Ln47 != 1;\
        }
        );
s.add_location("Circuit", "UpdatedLn47_becomes0","x_46<=1000", "");
s.add_location("Circuit", "UpdatedLn47_becomes1","x_46<=1500", "");
s.add_edge("Circuit", "JustSetIcontrollable_nhgrant0", "UpdatedLn47_becomes0", "x_46 < 1000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Ln47 == 1 && _l.Ln47 != 1;\
        }
        );
s.add_edge("Circuit", "UpdatedLn47_becomes0", "UpdatedLn47", "x_46 >= 1000", "x_46", "", syntax::layout_true,  [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Ln47 = 1;;\
                    }
                    );
s.add_edge("Circuit", "JustSetIcontrollable_nhgrant0", "UpdatedLn47_becomes1", "x_46 < 1500", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Ln47 == 0 && _l.Ln47 != 1;\
        }
        );
s.add_edge("Circuit", "UpdatedLn47_becomes1", "UpdatedLn47", "x_46 >= 1500", "x_46", "", syntax::layout_true,  [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Ln47 = 1;;\
                    }
                    );
s.add_location("Circuit", "UpdatedLreg_controllable_hgrant2_out", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "UpdatedLn47", "UpdatedLreg_controllable_hgrant2_out", "", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lreg_controllable_hgrant2_out==(_l.Icontrollable_hgrant2);;\
        }
        );
s.add_edge("Circuit", "UpdatedLn47", "UpdatedLreg_controllable_hgrant2_out", "x_48 <= 500", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lreg_controllable_hgrant2_out == 1 && _l.Lreg_controllable_hgrant2_out != (_l.Icontrollable_hgrant2);\
        }
        );
s.add_edge("Circuit", "UpdatedLn47", "UpdatedLreg_controllable_hgrant2_out", "x_48 <= 2000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lreg_controllable_hgrant2_out == 0 && _l.Lreg_controllable_hgrant2_out != (_l.Icontrollable_hgrant2);\
        }
        );
s.add_location("Circuit", "UpdatedLreg_controllable_hgrant2_out_becomes0","x_48<=500", "");
s.add_location("Circuit", "UpdatedLreg_controllable_hgrant2_out_becomes1","x_48<=2000", "");
s.add_edge("Circuit", "UpdatedLn47", "UpdatedLreg_controllable_hgrant2_out_becomes0", "x_48 < 500", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lreg_controllable_hgrant2_out == 1 && _l.Lreg_controllable_hgrant2_out != (_l.Icontrollable_hgrant2);\
        }
        );
s.add_edge("Circuit", "UpdatedLreg_controllable_hgrant2_out_becomes0", "UpdatedLreg_controllable_hgrant2_out", "x_48 >= 500", "x_48", "", syntax::layout_true,  [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Lreg_controllable_hgrant2_out = (_l.Icontrollable_hgrant2);;\
                    }
                    );
s.add_edge("Circuit", "UpdatedLn47", "UpdatedLreg_controllable_hgrant2_out_becomes1", "x_48 < 2000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lreg_controllable_hgrant2_out == 0 && _l.Lreg_controllable_hgrant2_out != (_l.Icontrollable_hgrant2);\
        }
        );
s.add_edge("Circuit", "UpdatedLreg_controllable_hgrant2_out_becomes1", "UpdatedLreg_controllable_hgrant2_out", "x_48 >= 2000", "x_48", "", syntax::layout_true,  [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Lreg_controllable_hgrant2_out = (_l.Icontrollable_hgrant2);;\
                    }
                    );
s.add_location("Circuit", "UpdatedLreg_controllable_hmaster1_out", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "UpdatedLreg_controllable_hgrant2_out", "UpdatedLreg_controllable_hmaster1_out", "", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lreg_controllable_hmaster1_out==(_l.Icontrollable_hmaster1);;\
        }
        );
s.add_edge("Circuit", "UpdatedLreg_controllable_hgrant2_out", "UpdatedLreg_controllable_hmaster1_out", "x_50 <= 2000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lreg_controllable_hmaster1_out == 1 && _l.Lreg_controllable_hmaster1_out != (_l.Icontrollable_hmaster1);\
        }
        );
s.add_edge("Circuit", "UpdatedLreg_controllable_hgrant2_out", "UpdatedLreg_controllable_hmaster1_out", "x_50 <= 3000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lreg_controllable_hmaster1_out == 0 && _l.Lreg_controllable_hmaster1_out != (_l.Icontrollable_hmaster1);\
        }
        );
s.add_location("Circuit", "UpdatedLreg_controllable_hmaster1_out_becomes0","x_50<=2000", "");
s.add_location("Circuit", "UpdatedLreg_controllable_hmaster1_out_becomes1","x_50<=3000", "");
s.add_edge("Circuit", "UpdatedLreg_controllable_hgrant2_out", "UpdatedLreg_controllable_hmaster1_out_becomes0", "x_50 < 2000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lreg_controllable_hmaster1_out == 1 && _l.Lreg_controllable_hmaster1_out != (_l.Icontrollable_hmaster1);\
        }
        );
s.add_edge("Circuit", "UpdatedLreg_controllable_hmaster1_out_becomes0", "UpdatedLreg_controllable_hmaster1_out", "x_50 >= 2000", "x_50", "", syntax::layout_true,  [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Lreg_controllable_hmaster1_out = (_l.Icontrollable_hmaster1);;\
                    }
                    );
s.add_edge("Circuit", "UpdatedLreg_controllable_hgrant2_out", "UpdatedLreg_controllable_hmaster1_out_becomes1", "x_50 < 3000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lreg_controllable_hmaster1_out == 0 && _l.Lreg_controllable_hmaster1_out != (_l.Icontrollable_hmaster1);\
        }
        );
s.add_edge("Circuit", "UpdatedLreg_controllable_hmaster1_out_becomes1", "UpdatedLreg_controllable_hmaster1_out", "x_50 >= 3000", "x_50", "", syntax::layout_true,  [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Lreg_controllable_hmaster1_out = (_l.Icontrollable_hmaster1);;\
                    }
                    );
s.add_location("Circuit", "UpdatedLreg_controllable_hgrant3_out", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "UpdatedLreg_controllable_hmaster1_out", "UpdatedLreg_controllable_hgrant3_out", "", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lreg_controllable_hgrant3_out==(_l.Icontrollable_hgrant3);;\
        }
        );
s.add_edge("Circuit", "UpdatedLreg_controllable_hmaster1_out", "UpdatedLreg_controllable_hgrant3_out", "x_52 <= 3000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lreg_controllable_hgrant3_out == 1 && _l.Lreg_controllable_hgrant3_out != (_l.Icontrollable_hgrant3);\
        }
        );
s.add_edge("Circuit", "UpdatedLreg_controllable_hmaster1_out", "UpdatedLreg_controllable_hgrant3_out", "x_52 <= 0", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lreg_controllable_hgrant3_out == 0 && _l.Lreg_controllable_hgrant3_out != (_l.Icontrollable_hgrant3);\
        }
        );
s.add_location("Circuit", "UpdatedLreg_controllable_hgrant3_out_becomes0","x_52<=3000", "");
s.add_location("Circuit", "UpdatedLreg_controllable_hgrant3_out_becomes1","x_52<=0", "");
s.add_edge("Circuit", "UpdatedLreg_controllable_hmaster1_out", "UpdatedLreg_controllable_hgrant3_out_becomes0", "x_52 < 3000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lreg_controllable_hgrant3_out == 1 && _l.Lreg_controllable_hgrant3_out != (_l.Icontrollable_hgrant3);\
        }
        );
s.add_edge("Circuit", "UpdatedLreg_controllable_hgrant3_out_becomes0", "UpdatedLreg_controllable_hgrant3_out", "x_52 >= 3000", "x_52", "", syntax::layout_true,  [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Lreg_controllable_hgrant3_out = (_l.Icontrollable_hgrant3);;\
                    }
                    );
s.add_edge("Circuit", "UpdatedLreg_controllable_hgrant3_out_becomes1", "UpdatedLreg_controllable_hgrant3_out", "x_52 >= 0", "x_52", "", syntax::layout_true,  [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Lreg_controllable_hgrant3_out = (_l.Icontrollable_hgrant3);;\
                    }
                    );
s.add_location("Circuit", "UpdatedLnext_env_fair_out", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "UpdatedLreg_controllable_hgrant3_out", "UpdatedLnext_env_fair_out", "", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lnext_env_fair_out==(!(((_l.Lreg_stateA1_out) && (_l.Ln47)) && !((_l.Lnext_env_fair_out) && (_l.Ln47))) && ((((!((((!((_l.Lnext_sys_fair1_out) && (_l.Ln47)) && !((_l.Lnext_sys_fair0_out) && (_l.Ln47))) && !((_l.Lnext_sys_fair2_out) && (_l.Ln47))) && !((_l.Lnext_sys_fair3_out) && (_l.Ln47))) && !((_l.Lreg_stateG2_out) && (_l.Ln47))) && !(!(!((_l.Icontrollable_hmaster0) && !(_l.Icontrollable_hmaster1)) && (_l.Ii_hbusreq1)) && (((((_l.Lnext_sys_fair1_out) && (_l.Ln47)) && ((_l.Lnext_sys_fair0_out) && (_l.Ln47))) && !((_l.Lnext_sys_fair2_out) && (_l.Ln47))) && !((_l.Lnext_sys_fair3_out) && (_l.Ln47))))) && (!((((!((_l.Lnext_sys_fair1_out) && (_l.Ln47)) && ((_l.Lnext_sys_fair0_out) && (_l.Ln47))) && !((_l.Lnext_sys_fair2_out) && (_l.Ln47))) && !((_l.Lnext_sys_fair3_out) && (_l.Ln47))) && (!((_l.Lreg_stateG3_2_out) && (_l.Ln47)) && (!((_l.Lreg_stateG3_1_out) && (_l.Ln47)) && !((_l.Lreg_stateG3_0_out) && (_l.Ln47))))) && !(!(!(!(_l.Icontrollable_hmaster0) && !(_l.Icontrollable_hmaster1)) && (_l.Ii_hbusreq0)) && (((((_l.Lnext_sys_fair1_out) && (_l.Ln47)) && !((_l.Lnext_sys_fair0_out) && (_l.Ln47))) && !((_l.Lnext_sys_fair2_out) && (_l.Ln47))) && !((_l.Lnext_sys_fair3_out) && (_l.Ln47)))))) && (!(!(!(!(_l.Icontrollable_hmaster0) && (_l.Icontrollable_hmaster1)) && (_l.Ii_hbusreq2)) && (((!((_l.Lnext_sys_fair1_out) && (_l.Ln47)) && !((_l.Lnext_sys_fair0_out) && (_l.Ln47))) && ((_l.Lnext_sys_fair2_out) && (_l.Ln47))) && !((_l.Lnext_sys_fair3_out) && (_l.Ln47)))) && !(!(!((_l.Icontrollable_hmaster0) && (_l.Icontrollable_hmaster1)) && (_l.Ii_hbusreq3)) && (((!((_l.Lnext_sys_fair1_out) && (_l.Ln47)) && ((_l.Lnext_sys_fair0_out) && (_l.Ln47))) && ((_l.Lnext_sys_fair2_out) && (_l.Ln47))) && !((_l.Lnext_sys_fair3_out) && (_l.Ln47)))))) && !(((_l.Lnext_env_fair_out) && (_l.Ln47)) && (_l.Ii_hready))));;\
        }
        );
s.add_edge("Circuit", "UpdatedLreg_controllable_hgrant3_out", "UpdatedLnext_env_fair_out", "x_54 <= 2500", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lnext_env_fair_out == 1 && _l.Lnext_env_fair_out != (!(((_l.Lreg_stateA1_out) && (_l.Ln47)) && !((_l.Lnext_env_fair_out) && (_l.Ln47))) && ((((!((((!((_l.Lnext_sys_fair1_out) && (_l.Ln47)) && !((_l.Lnext_sys_fair0_out) && (_l.Ln47))) && !((_l.Lnext_sys_fair2_out) && (_l.Ln47))) && !((_l.Lnext_sys_fair3_out) && (_l.Ln47))) && !((_l.Lreg_stateG2_out) && (_l.Ln47))) && !(!(!((_l.Icontrollable_hmaster0) && !(_l.Icontrollable_hmaster1)) && (_l.Ii_hbusreq1)) && (((((_l.Lnext_sys_fair1_out) && (_l.Ln47)) && ((_l.Lnext_sys_fair0_out) && (_l.Ln47))) && !((_l.Lnext_sys_fair2_out) && (_l.Ln47))) && !((_l.Lnext_sys_fair3_out) && (_l.Ln47))))) && (!((((!((_l.Lnext_sys_fair1_out) && (_l.Ln47)) && ((_l.Lnext_sys_fair0_out) && (_l.Ln47))) && !((_l.Lnext_sys_fair2_out) && (_l.Ln47))) && !((_l.Lnext_sys_fair3_out) && (_l.Ln47))) && (!((_l.Lreg_stateG3_2_out) && (_l.Ln47)) && (!((_l.Lreg_stateG3_1_out) && (_l.Ln47)) && !((_l.Lreg_stateG3_0_out) && (_l.Ln47))))) && !(!(!(!(_l.Icontrollable_hmaster0) && !(_l.Icontrollable_hmaster1)) && (_l.Ii_hbusreq0)) && (((((_l.Lnext_sys_fair1_out) && (_l.Ln47)) && !((_l.Lnext_sys_fair0_out) && (_l.Ln47))) && !((_l.Lnext_sys_fair2_out) && (_l.Ln47))) && !((_l.Lnext_sys_fair3_out) && (_l.Ln47)))))) && (!(!(!(!(_l.Icontrollable_hmaster0) && (_l.Icontrollable_hmaster1)) && (_l.Ii_hbusreq2)) && (((!((_l.Lnext_sys_fair1_out) && (_l.Ln47)) && !((_l.Lnext_sys_fair0_out) && (_l.Ln47))) && ((_l.Lnext_sys_fair2_out) && (_l.Ln47))) && !((_l.Lnext_sys_fair3_out) && (_l.Ln47)))) && !(!(!((_l.Icontrollable_hmaster0) && (_l.Icontrollable_hmaster1)) && (_l.Ii_hbusreq3)) && (((!((_l.Lnext_sys_fair1_out) && (_l.Ln47)) && ((_l.Lnext_sys_fair0_out) && (_l.Ln47))) && ((_l.Lnext_sys_fair2_out) && (_l.Ln47))) && !((_l.Lnext_sys_fair3_out) && (_l.Ln47)))))) && !(((_l.Lnext_env_fair_out) && (_l.Ln47)) && (_l.Ii_hready))));\
        }
        );
s.add_edge("Circuit", "UpdatedLreg_controllable_hgrant3_out", "UpdatedLnext_env_fair_out", "x_54 <= 0", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lnext_env_fair_out == 0 && _l.Lnext_env_fair_out != (!(((_l.Lreg_stateA1_out) && (_l.Ln47)) && !((_l.Lnext_env_fair_out) && (_l.Ln47))) && ((((!((((!((_l.Lnext_sys_fair1_out) && (_l.Ln47)) && !((_l.Lnext_sys_fair0_out) && (_l.Ln47))) && !((_l.Lnext_sys_fair2_out) && (_l.Ln47))) && !((_l.Lnext_sys_fair3_out) && (_l.Ln47))) && !((_l.Lreg_stateG2_out) && (_l.Ln47))) && !(!(!((_l.Icontrollable_hmaster0) && !(_l.Icontrollable_hmaster1)) && (_l.Ii_hbusreq1)) && (((((_l.Lnext_sys_fair1_out) && (_l.Ln47)) && ((_l.Lnext_sys_fair0_out) && (_l.Ln47))) && !((_l.Lnext_sys_fair2_out) && (_l.Ln47))) && !((_l.Lnext_sys_fair3_out) && (_l.Ln47))))) && (!((((!((_l.Lnext_sys_fair1_out) && (_l.Ln47)) && ((_l.Lnext_sys_fair0_out) && (_l.Ln47))) && !((_l.Lnext_sys_fair2_out) && (_l.Ln47))) && !((_l.Lnext_sys_fair3_out) && (_l.Ln47))) && (!((_l.Lreg_stateG3_2_out) && (_l.Ln47)) && (!((_l.Lreg_stateG3_1_out) && (_l.Ln47)) && !((_l.Lreg_stateG3_0_out) && (_l.Ln47))))) && !(!(!(!(_l.Icontrollable_hmaster0) && !(_l.Icontrollable_hmaster1)) && (_l.Ii_hbusreq0)) && (((((_l.Lnext_sys_fair1_out) && (_l.Ln47)) && !((_l.Lnext_sys_fair0_out) && (_l.Ln47))) && !((_l.Lnext_sys_fair2_out) && (_l.Ln47))) && !((_l.Lnext_sys_fair3_out) && (_l.Ln47)))))) && (!(!(!(!(_l.Icontrollable_hmaster0) && (_l.Icontrollable_hmaster1)) && (_l.Ii_hbusreq2)) && (((!((_l.Lnext_sys_fair1_out) && (_l.Ln47)) && !((_l.Lnext_sys_fair0_out) && (_l.Ln47))) && ((_l.Lnext_sys_fair2_out) && (_l.Ln47))) && !((_l.Lnext_sys_fair3_out) && (_l.Ln47)))) && !(!(!((_l.Icontrollable_hmaster0) && (_l.Icontrollable_hmaster1)) && (_l.Ii_hbusreq3)) && (((!((_l.Lnext_sys_fair1_out) && (_l.Ln47)) && ((_l.Lnext_sys_fair0_out) && (_l.Ln47))) && ((_l.Lnext_sys_fair2_out) && (_l.Ln47))) && !((_l.Lnext_sys_fair3_out) && (_l.Ln47)))))) && !(((_l.Lnext_env_fair_out) && (_l.Ln47)) && (_l.Ii_hready))));\
        }
        );
s.add_location("Circuit", "UpdatedLnext_env_fair_out_becomes0","x_54<=2500", "");
s.add_location("Circuit", "UpdatedLnext_env_fair_out_becomes1","x_54<=0", "");
s.add_edge("Circuit", "UpdatedLreg_controllable_hgrant3_out", "UpdatedLnext_env_fair_out_becomes0", "x_54 < 2500", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lnext_env_fair_out == 1 && _l.Lnext_env_fair_out != (!(((_l.Lreg_stateA1_out) && (_l.Ln47)) && !((_l.Lnext_env_fair_out) && (_l.Ln47))) && ((((!((((!((_l.Lnext_sys_fair1_out) && (_l.Ln47)) && !((_l.Lnext_sys_fair0_out) && (_l.Ln47))) && !((_l.Lnext_sys_fair2_out) && (_l.Ln47))) && !((_l.Lnext_sys_fair3_out) && (_l.Ln47))) && !((_l.Lreg_stateG2_out) && (_l.Ln47))) && !(!(!((_l.Icontrollable_hmaster0) && !(_l.Icontrollable_hmaster1)) && (_l.Ii_hbusreq1)) && (((((_l.Lnext_sys_fair1_out) && (_l.Ln47)) && ((_l.Lnext_sys_fair0_out) && (_l.Ln47))) && !((_l.Lnext_sys_fair2_out) && (_l.Ln47))) && !((_l.Lnext_sys_fair3_out) && (_l.Ln47))))) && (!((((!((_l.Lnext_sys_fair1_out) && (_l.Ln47)) && ((_l.Lnext_sys_fair0_out) && (_l.Ln47))) && !((_l.Lnext_sys_fair2_out) && (_l.Ln47))) && !((_l.Lnext_sys_fair3_out) && (_l.Ln47))) && (!((_l.Lreg_stateG3_2_out) && (_l.Ln47)) && (!((_l.Lreg_stateG3_1_out) && (_l.Ln47)) && !((_l.Lreg_stateG3_0_out) && (_l.Ln47))))) && !(!(!(!(_l.Icontrollable_hmaster0) && !(_l.Icontrollable_hmaster1)) && (_l.Ii_hbusreq0)) && (((((_l.Lnext_sys_fair1_out) && (_l.Ln47)) && !((_l.Lnext_sys_fair0_out) && (_l.Ln47))) && !((_l.Lnext_sys_fair2_out) && (_l.Ln47))) && !((_l.Lnext_sys_fair3_out) && (_l.Ln47)))))) && (!(!(!(!(_l.Icontrollable_hmaster0) && (_l.Icontrollable_hmaster1)) && (_l.Ii_hbusreq2)) && (((!((_l.Lnext_sys_fair1_out) && (_l.Ln47)) && !((_l.Lnext_sys_fair0_out) && (_l.Ln47))) && ((_l.Lnext_sys_fair2_out) && (_l.Ln47))) && !((_l.Lnext_sys_fair3_out) && (_l.Ln47)))) && !(!(!((_l.Icontrollable_hmaster0) && (_l.Icontrollable_hmaster1)) && (_l.Ii_hbusreq3)) && (((!((_l.Lnext_sys_fair1_out) && (_l.Ln47)) && ((_l.Lnext_sys_fair0_out) && (_l.Ln47))) && ((_l.Lnext_sys_fair2_out) && (_l.Ln47))) && !((_l.Lnext_sys_fair3_out) && (_l.Ln47)))))) && !(((_l.Lnext_env_fair_out) && (_l.Ln47)) && (_l.Ii_hready))));\
        }
        );
s.add_edge("Circuit", "UpdatedLnext_env_fair_out_becomes0", "UpdatedLnext_env_fair_out", "x_54 >= 2500", "x_54", "", syntax::layout_true,  [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Lnext_env_fair_out = (!(((_l.Lreg_stateA1_out) && (_l.Ln47)) && !((_l.Lnext_env_fair_out) && (_l.Ln47))) && ((((!((((!((_l.Lnext_sys_fair1_out) && (_l.Ln47)) && !((_l.Lnext_sys_fair0_out) && (_l.Ln47))) && !((_l.Lnext_sys_fair2_out) && (_l.Ln47))) && !((_l.Lnext_sys_fair3_out) && (_l.Ln47))) && !((_l.Lreg_stateG2_out) && (_l.Ln47))) && !(!(!((_l.Icontrollable_hmaster0) && !(_l.Icontrollable_hmaster1)) && (_l.Ii_hbusreq1)) && (((((_l.Lnext_sys_fair1_out) && (_l.Ln47)) && ((_l.Lnext_sys_fair0_out) && (_l.Ln47))) && !((_l.Lnext_sys_fair2_out) && (_l.Ln47))) && !((_l.Lnext_sys_fair3_out) && (_l.Ln47))))) && (!((((!((_l.Lnext_sys_fair1_out) && (_l.Ln47)) && ((_l.Lnext_sys_fair0_out) && (_l.Ln47))) && !((_l.Lnext_sys_fair2_out) && (_l.Ln47))) && !((_l.Lnext_sys_fair3_out) && (_l.Ln47))) && (!((_l.Lreg_stateG3_2_out) && (_l.Ln47)) && (!((_l.Lreg_stateG3_1_out) && (_l.Ln47)) && !((_l.Lreg_stateG3_0_out) && (_l.Ln47))))) && !(!(!(!(_l.Icontrollable_hmaster0) && !(_l.Icontrollable_hmaster1)) && (_l.Ii_hbusreq0)) && (((((_l.Lnext_sys_fair1_out) && (_l.Ln47)) && !((_l.Lnext_sys_fair0_out) && (_l.Ln47))) && !((_l.Lnext_sys_fair2_out) && (_l.Ln47))) && !((_l.Lnext_sys_fair3_out) && (_l.Ln47)))))) && (!(!(!(!(_l.Icontrollable_hmaster0) && (_l.Icontrollable_hmaster1)) && (_l.Ii_hbusreq2)) && (((!((_l.Lnext_sys_fair1_out) && (_l.Ln47)) && !((_l.Lnext_sys_fair0_out) && (_l.Ln47))) && ((_l.Lnext_sys_fair2_out) && (_l.Ln47))) && !((_l.Lnext_sys_fair3_out) && (_l.Ln47)))) && !(!(!((_l.Icontrollable_hmaster0) && (_l.Icontrollable_hmaster1)) && (_l.Ii_hbusreq3)) && (((!((_l.Lnext_sys_fair1_out) && (_l.Ln47)) && ((_l.Lnext_sys_fair0_out) && (_l.Ln47))) && ((_l.Lnext_sys_fair2_out) && (_l.Ln47))) && !((_l.Lnext_sys_fair3_out) && (_l.Ln47)))))) && !(((_l.Lnext_env_fair_out) && (_l.Ln47)) && (_l.Ii_hready))));;\
                    }
                    );
s.add_edge("Circuit", "UpdatedLnext_env_fair_out_becomes1", "UpdatedLnext_env_fair_out", "x_54 >= 0", "x_54", "", syntax::layout_true,  [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Lnext_env_fair_out = (!(((_l.Lreg_stateA1_out) && (_l.Ln47)) && !((_l.Lnext_env_fair_out) && (_l.Ln47))) && ((((!((((!((_l.Lnext_sys_fair1_out) && (_l.Ln47)) && !((_l.Lnext_sys_fair0_out) && (_l.Ln47))) && !((_l.Lnext_sys_fair2_out) && (_l.Ln47))) && !((_l.Lnext_sys_fair3_out) && (_l.Ln47))) && !((_l.Lreg_stateG2_out) && (_l.Ln47))) && !(!(!((_l.Icontrollable_hmaster0) && !(_l.Icontrollable_hmaster1)) && (_l.Ii_hbusreq1)) && (((((_l.Lnext_sys_fair1_out) && (_l.Ln47)) && ((_l.Lnext_sys_fair0_out) && (_l.Ln47))) && !((_l.Lnext_sys_fair2_out) && (_l.Ln47))) && !((_l.Lnext_sys_fair3_out) && (_l.Ln47))))) && (!((((!((_l.Lnext_sys_fair1_out) && (_l.Ln47)) && ((_l.Lnext_sys_fair0_out) && (_l.Ln47))) && !((_l.Lnext_sys_fair2_out) && (_l.Ln47))) && !((_l.Lnext_sys_fair3_out) && (_l.Ln47))) && (!((_l.Lreg_stateG3_2_out) && (_l.Ln47)) && (!((_l.Lreg_stateG3_1_out) && (_l.Ln47)) && !((_l.Lreg_stateG3_0_out) && (_l.Ln47))))) && !(!(!(!(_l.Icontrollable_hmaster0) && !(_l.Icontrollable_hmaster1)) && (_l.Ii_hbusreq0)) && (((((_l.Lnext_sys_fair1_out) && (_l.Ln47)) && !((_l.Lnext_sys_fair0_out) && (_l.Ln47))) && !((_l.Lnext_sys_fair2_out) && (_l.Ln47))) && !((_l.Lnext_sys_fair3_out) && (_l.Ln47)))))) && (!(!(!(!(_l.Icontrollable_hmaster0) && (_l.Icontrollable_hmaster1)) && (_l.Ii_hbusreq2)) && (((!((_l.Lnext_sys_fair1_out) && (_l.Ln47)) && !((_l.Lnext_sys_fair0_out) && (_l.Ln47))) && ((_l.Lnext_sys_fair2_out) && (_l.Ln47))) && !((_l.Lnext_sys_fair3_out) && (_l.Ln47)))) && !(!(!((_l.Icontrollable_hmaster0) && (_l.Icontrollable_hmaster1)) && (_l.Ii_hbusreq3)) && (((!((_l.Lnext_sys_fair1_out) && (_l.Ln47)) && ((_l.Lnext_sys_fair0_out) && (_l.Ln47))) && ((_l.Lnext_sys_fair2_out) && (_l.Ln47))) && !((_l.Lnext_sys_fair3_out) && (_l.Ln47)))))) && !(((_l.Lnext_env_fair_out) && (_l.Ln47)) && (_l.Ii_hready))));;\
                    }
                    );
s.add_location("Circuit", "UpdatedLreg_stateG3_0_out", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "UpdatedLnext_env_fair_out", "UpdatedLreg_stateG3_0_out", "", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lreg_stateG3_0_out==!(!((!((!((_l.Lreg_stateG3_2_out) && (_l.Ln47)) && (_l.Ii_hready)) && ((_l.Lreg_stateG3_0_out) && (_l.Ln47))) && !(!(!((_l.Lreg_stateG3_2_out) && (_l.Ln47)) && (_l.Ii_hready)) && !((_l.Lreg_stateG3_0_out) && (_l.Ln47)))) && !(!((_l.Lreg_stateG3_1_out) && (_l.Ln47)) && !((_l.Lreg_stateG3_0_out) && (_l.Ln47)))) && !(((((!(_l.Icontrollable_nstart) && (_l.Icontrollable_hmastlock)) && !(_l.Ii_hburst0)) && (!((_l.Lreg_stateG3_2_out) && (_l.Ln47)) && (!((_l.Lreg_stateG3_1_out) && (_l.Ln47)) && !((_l.Lreg_stateG3_0_out) && (_l.Ln47))))) && (_l.Ii_hburst1)) && !(_l.Ii_hready)));;\
        }
        );
s.add_edge("Circuit", "UpdatedLnext_env_fair_out", "UpdatedLreg_stateG3_0_out", "x_56 <= 4000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lreg_stateG3_0_out == 1 && _l.Lreg_stateG3_0_out != !(!((!((!((_l.Lreg_stateG3_2_out) && (_l.Ln47)) && (_l.Ii_hready)) && ((_l.Lreg_stateG3_0_out) && (_l.Ln47))) && !(!(!((_l.Lreg_stateG3_2_out) && (_l.Ln47)) && (_l.Ii_hready)) && !((_l.Lreg_stateG3_0_out) && (_l.Ln47)))) && !(!((_l.Lreg_stateG3_1_out) && (_l.Ln47)) && !((_l.Lreg_stateG3_0_out) && (_l.Ln47)))) && !(((((!(_l.Icontrollable_nstart) && (_l.Icontrollable_hmastlock)) && !(_l.Ii_hburst0)) && (!((_l.Lreg_stateG3_2_out) && (_l.Ln47)) && (!((_l.Lreg_stateG3_1_out) && (_l.Ln47)) && !((_l.Lreg_stateG3_0_out) && (_l.Ln47))))) && (_l.Ii_hburst1)) && !(_l.Ii_hready)));\
        }
        );
s.add_edge("Circuit", "UpdatedLnext_env_fair_out", "UpdatedLreg_stateG3_0_out", "x_56 <= 2000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lreg_stateG3_0_out == 0 && _l.Lreg_stateG3_0_out != !(!((!((!((_l.Lreg_stateG3_2_out) && (_l.Ln47)) && (_l.Ii_hready)) && ((_l.Lreg_stateG3_0_out) && (_l.Ln47))) && !(!(!((_l.Lreg_stateG3_2_out) && (_l.Ln47)) && (_l.Ii_hready)) && !((_l.Lreg_stateG3_0_out) && (_l.Ln47)))) && !(!((_l.Lreg_stateG3_1_out) && (_l.Ln47)) && !((_l.Lreg_stateG3_0_out) && (_l.Ln47)))) && !(((((!(_l.Icontrollable_nstart) && (_l.Icontrollable_hmastlock)) && !(_l.Ii_hburst0)) && (!((_l.Lreg_stateG3_2_out) && (_l.Ln47)) && (!((_l.Lreg_stateG3_1_out) && (_l.Ln47)) && !((_l.Lreg_stateG3_0_out) && (_l.Ln47))))) && (_l.Ii_hburst1)) && !(_l.Ii_hready)));\
        }
        );
s.add_location("Circuit", "UpdatedLreg_stateG3_0_out_becomes0","x_56<=4000", "");
s.add_location("Circuit", "UpdatedLreg_stateG3_0_out_becomes1","x_56<=2000", "");
s.add_edge("Circuit", "UpdatedLnext_env_fair_out", "UpdatedLreg_stateG3_0_out_becomes0", "x_56 < 4000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lreg_stateG3_0_out == 1 && _l.Lreg_stateG3_0_out != !(!((!((!((_l.Lreg_stateG3_2_out) && (_l.Ln47)) && (_l.Ii_hready)) && ((_l.Lreg_stateG3_0_out) && (_l.Ln47))) && !(!(!((_l.Lreg_stateG3_2_out) && (_l.Ln47)) && (_l.Ii_hready)) && !((_l.Lreg_stateG3_0_out) && (_l.Ln47)))) && !(!((_l.Lreg_stateG3_1_out) && (_l.Ln47)) && !((_l.Lreg_stateG3_0_out) && (_l.Ln47)))) && !(((((!(_l.Icontrollable_nstart) && (_l.Icontrollable_hmastlock)) && !(_l.Ii_hburst0)) && (!((_l.Lreg_stateG3_2_out) && (_l.Ln47)) && (!((_l.Lreg_stateG3_1_out) && (_l.Ln47)) && !((_l.Lreg_stateG3_0_out) && (_l.Ln47))))) && (_l.Ii_hburst1)) && !(_l.Ii_hready)));\
        }
        );
s.add_edge("Circuit", "UpdatedLreg_stateG3_0_out_becomes0", "UpdatedLreg_stateG3_0_out", "x_56 >= 4000", "x_56", "", syntax::layout_true,  [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Lreg_stateG3_0_out = !(!((!((!((_l.Lreg_stateG3_2_out) && (_l.Ln47)) && (_l.Ii_hready)) && ((_l.Lreg_stateG3_0_out) && (_l.Ln47))) && !(!(!((_l.Lreg_stateG3_2_out) && (_l.Ln47)) && (_l.Ii_hready)) && !((_l.Lreg_stateG3_0_out) && (_l.Ln47)))) && !(!((_l.Lreg_stateG3_1_out) && (_l.Ln47)) && !((_l.Lreg_stateG3_0_out) && (_l.Ln47)))) && !(((((!(_l.Icontrollable_nstart) && (_l.Icontrollable_hmastlock)) && !(_l.Ii_hburst0)) && (!((_l.Lreg_stateG3_2_out) && (_l.Ln47)) && (!((_l.Lreg_stateG3_1_out) && (_l.Ln47)) && !((_l.Lreg_stateG3_0_out) && (_l.Ln47))))) && (_l.Ii_hburst1)) && !(_l.Ii_hready)));;\
                    }
                    );
s.add_edge("Circuit", "UpdatedLnext_env_fair_out", "UpdatedLreg_stateG3_0_out_becomes1", "x_56 < 2000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lreg_stateG3_0_out == 0 && _l.Lreg_stateG3_0_out != !(!((!((!((_l.Lreg_stateG3_2_out) && (_l.Ln47)) && (_l.Ii_hready)) && ((_l.Lreg_stateG3_0_out) && (_l.Ln47))) && !(!(!((_l.Lreg_stateG3_2_out) && (_l.Ln47)) && (_l.Ii_hready)) && !((_l.Lreg_stateG3_0_out) && (_l.Ln47)))) && !(!((_l.Lreg_stateG3_1_out) && (_l.Ln47)) && !((_l.Lreg_stateG3_0_out) && (_l.Ln47)))) && !(((((!(_l.Icontrollable_nstart) && (_l.Icontrollable_hmastlock)) && !(_l.Ii_hburst0)) && (!((_l.Lreg_stateG3_2_out) && (_l.Ln47)) && (!((_l.Lreg_stateG3_1_out) && (_l.Ln47)) && !((_l.Lreg_stateG3_0_out) && (_l.Ln47))))) && (_l.Ii_hburst1)) && !(_l.Ii_hready)));\
        }
        );
s.add_edge("Circuit", "UpdatedLreg_stateG3_0_out_becomes1", "UpdatedLreg_stateG3_0_out", "x_56 >= 2000", "x_56", "", syntax::layout_true,  [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Lreg_stateG3_0_out = !(!((!((!((_l.Lreg_stateG3_2_out) && (_l.Ln47)) && (_l.Ii_hready)) && ((_l.Lreg_stateG3_0_out) && (_l.Ln47))) && !(!(!((_l.Lreg_stateG3_2_out) && (_l.Ln47)) && (_l.Ii_hready)) && !((_l.Lreg_stateG3_0_out) && (_l.Ln47)))) && !(!((_l.Lreg_stateG3_1_out) && (_l.Ln47)) && !((_l.Lreg_stateG3_0_out) && (_l.Ln47)))) && !(((((!(_l.Icontrollable_nstart) && (_l.Icontrollable_hmastlock)) && !(_l.Ii_hburst0)) && (!((_l.Lreg_stateG3_2_out) && (_l.Ln47)) && (!((_l.Lreg_stateG3_1_out) && (_l.Ln47)) && !((_l.Lreg_stateG3_0_out) && (_l.Ln47))))) && (_l.Ii_hburst1)) && !(_l.Ii_hready)));;\
                    }
                    );
s.add_location("Circuit", "UpdatedLreg_controllable_locked_out", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "UpdatedLreg_stateG3_0_out", "UpdatedLreg_controllable_locked_out", "", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lreg_controllable_locked_out==(_l.Icontrollable_locked);;\
        }
        );
s.add_edge("Circuit", "UpdatedLreg_stateG3_0_out", "UpdatedLreg_controllable_locked_out", "x_58 <= 1000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lreg_controllable_locked_out == 1 && _l.Lreg_controllable_locked_out != (_l.Icontrollable_locked);\
        }
        );
s.add_edge("Circuit", "UpdatedLreg_stateG3_0_out", "UpdatedLreg_controllable_locked_out", "x_58 <= 500", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lreg_controllable_locked_out == 0 && _l.Lreg_controllable_locked_out != (_l.Icontrollable_locked);\
        }
        );
s.add_location("Circuit", "UpdatedLreg_controllable_locked_out_becomes0","x_58<=1000", "");
s.add_location("Circuit", "UpdatedLreg_controllable_locked_out_becomes1","x_58<=500", "");
s.add_edge("Circuit", "UpdatedLreg_stateG3_0_out", "UpdatedLreg_controllable_locked_out_becomes0", "x_58 < 1000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lreg_controllable_locked_out == 1 && _l.Lreg_controllable_locked_out != (_l.Icontrollable_locked);\
        }
        );
s.add_edge("Circuit", "UpdatedLreg_controllable_locked_out_becomes0", "UpdatedLreg_controllable_locked_out", "x_58 >= 1000", "x_58", "", syntax::layout_true,  [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Lreg_controllable_locked_out = (_l.Icontrollable_locked);;\
                    }
                    );
s.add_edge("Circuit", "UpdatedLreg_stateG3_0_out", "UpdatedLreg_controllable_locked_out_becomes1", "x_58 < 500", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lreg_controllable_locked_out == 0 && _l.Lreg_controllable_locked_out != (_l.Icontrollable_locked);\
        }
        );
s.add_edge("Circuit", "UpdatedLreg_controllable_locked_out_becomes1", "UpdatedLreg_controllable_locked_out", "x_58 >= 500", "x_58", "", syntax::layout_true,  [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Lreg_controllable_locked_out = (_l.Icontrollable_locked);;\
                    }
                    );
s.add_edge("Circuit", "UpdatedLreg_controllable_locked_out", "dead", "T>3000", "", "", syntax::layout_true);
s.add_edge("Circuit", "UpdatedLreg_controllable_locked_out", "init", "T<=3000", "T", "", syntax::layout_true);
s.synchronizer<syntax::asynchronous_product_t>();
}
