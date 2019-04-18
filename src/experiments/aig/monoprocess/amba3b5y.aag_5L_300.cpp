#include <iostream>
        #include "syntax/system.hh"
        #include "syntax/sync_product.hh"
        namespace monoprocess {
        class layout_t : public syntax::layout_t {
        public:
        
	bool Ii_hbusreq0;
	bool Ii_hbusreq1;
	bool Ii_hbusreq2;
	bool Ii_hburst1;
	bool Ii_hburst0;
	bool Ii_hlock0;
	bool Ii_hlock1;
	bool Ii_hlock2;
	bool Ii_hready;
	bool Icontrollable_hmastlock;
	bool Icontrollable_nstart;
	bool Icontrollable_hmaster1;
	bool Icontrollable_locked;
	bool Icontrollable_hmaster0;
	bool Icontrollable_hgrant1;
	bool Icontrollable_busreq;
	bool Icontrollable_hgrant2;
	bool Icontrollable_ndecide;
	bool Icontrollable_nhgrant0;
	bool Ln41;
	bool Lreg_controllable_hgrant2_out;
	bool Lreg_controllable_hmaster1_out;
	bool Lsys_fair0done_out;
	bool Lreg_stateG3_0_out;
	bool Lenv_fair1done_out;
	bool Lreg_controllable_locked_out;
	bool Lsys_fair3done_out;
	bool Lreg_stateG3_1_out;
	bool Lreg_controllable_ndecide_out;
	bool Lreg_stateG3_2_out;
	bool Lreg_i_hbusreq0_out;
	bool Lreg_controllable_busreq_out;
	bool Lreg_controllable_nstart_out;
	bool Lreg_i_hbusreq1_out;
	bool Lsys_fair1done_out;
	bool Lreg_stateG2_out;
	bool Lreg_stateG10_1_out;
	bool Lenv_fair0done_out;
	bool Lreg_controllable_nhgrant0_out;
	bool Lreg_i_hlock2_out;
	bool Lreg_stateG10_2_out;
	bool Lreg_stateA1_out;
	bool Lreg_controllable_hmastlock_out;
	bool Lsys_fair4done_out;
	bool Lreg_i_hbusreq2_out;
	bool Lreg_i_hlock1_out;
	bool Lfair_cnt0_out;
	bool Lfair_cnt1_out;
	bool Lfair_cnt2_out;
	bool Lenv_safe_err_happened_out;
	bool Lreg_i_hlock0_out;
	bool Lreg_i_hready_out;
	bool Lreg_controllable_hgrant1_out;
	bool Lsys_fair2done_out;
	bool Lreg_controllable_hmaster0_out;
	layout_t(){
		Ii_hbusreq0 = 0;
		Ii_hbusreq1 = 0;
		Ii_hbusreq2 = 0;
		Ii_hburst1 = 0;
		Ii_hburst0 = 0;
		Ii_hlock0 = 0;
		Ii_hlock1 = 0;
		Ii_hlock2 = 0;
		Ii_hready = 0;
		Icontrollable_hmastlock = 0;
		Icontrollable_nstart = 0;
		Icontrollable_hmaster1 = 0;
		Icontrollable_locked = 0;
		Icontrollable_hmaster0 = 0;
		Icontrollable_hgrant1 = 0;
		Icontrollable_busreq = 0;
		Icontrollable_hgrant2 = 0;
		Icontrollable_ndecide = 0;
		Icontrollable_nhgrant0 = 0;
		Ln41 = 0;
		Lreg_controllable_hgrant2_out = 0;
		Lreg_controllable_hmaster1_out = 0;
		Lsys_fair0done_out = 0;
		Lreg_stateG3_0_out = 0;
		Lenv_fair1done_out = 0;
		Lreg_controllable_locked_out = 0;
		Lsys_fair3done_out = 0;
		Lreg_stateG3_1_out = 0;
		Lreg_controllable_ndecide_out = 0;
		Lreg_stateG3_2_out = 0;
		Lreg_i_hbusreq0_out = 0;
		Lreg_controllable_busreq_out = 0;
		Lreg_controllable_nstart_out = 0;
		Lreg_i_hbusreq1_out = 0;
		Lsys_fair1done_out = 0;
		Lreg_stateG2_out = 0;
		Lreg_stateG10_1_out = 0;
		Lenv_fair0done_out = 0;
		Lreg_controllable_nhgrant0_out = 0;
		Lreg_i_hlock2_out = 0;
		Lreg_stateG10_2_out = 0;
		Lreg_stateA1_out = 0;
		Lreg_controllable_hmastlock_out = 0;
		Lsys_fair4done_out = 0;
		Lreg_i_hbusreq2_out = 0;
		Lreg_i_hlock1_out = 0;
		Lfair_cnt0_out = 0;
		Lfair_cnt1_out = 0;
		Lfair_cnt2_out = 0;
		Lenv_safe_err_happened_out = 0;
		Lreg_i_hlock0_out = 0;
		Lreg_i_hready_out = 0;
		Lreg_controllable_hgrant1_out = 0;
		Lsys_fair2done_out = 0;
		Lreg_controllable_hmaster0_out = 0;
	}
virtual ~layout_t(){}
layout_t (const layout_t &l) = default;

        inline bool operator == (const syntax::layout_t & l) const {
            monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);
        
		if(Ii_hbusreq0 != _l.Ii_hbusreq0) return false;
		if(Ii_hbusreq1 != _l.Ii_hbusreq1) return false;
		if(Ii_hbusreq2 != _l.Ii_hbusreq2) return false;
		if(Ii_hburst1 != _l.Ii_hburst1) return false;
		if(Ii_hburst0 != _l.Ii_hburst0) return false;
		if(Ii_hlock0 != _l.Ii_hlock0) return false;
		if(Ii_hlock1 != _l.Ii_hlock1) return false;
		if(Ii_hlock2 != _l.Ii_hlock2) return false;
		if(Ii_hready != _l.Ii_hready) return false;
		if(Icontrollable_hmastlock != _l.Icontrollable_hmastlock) return false;
		if(Icontrollable_nstart != _l.Icontrollable_nstart) return false;
		if(Icontrollable_hmaster1 != _l.Icontrollable_hmaster1) return false;
		if(Icontrollable_locked != _l.Icontrollable_locked) return false;
		if(Icontrollable_hmaster0 != _l.Icontrollable_hmaster0) return false;
		if(Icontrollable_hgrant1 != _l.Icontrollable_hgrant1) return false;
		if(Icontrollable_busreq != _l.Icontrollable_busreq) return false;
		if(Icontrollable_hgrant2 != _l.Icontrollable_hgrant2) return false;
		if(Icontrollable_ndecide != _l.Icontrollable_ndecide) return false;
		if(Icontrollable_nhgrant0 != _l.Icontrollable_nhgrant0) return false;
		if(Ln41 != _l.Ln41) return false;
		if(Lreg_controllable_hgrant2_out != _l.Lreg_controllable_hgrant2_out) return false;
		if(Lreg_controllable_hmaster1_out != _l.Lreg_controllable_hmaster1_out) return false;
		if(Lsys_fair0done_out != _l.Lsys_fair0done_out) return false;
		if(Lreg_stateG3_0_out != _l.Lreg_stateG3_0_out) return false;
		if(Lenv_fair1done_out != _l.Lenv_fair1done_out) return false;
		if(Lreg_controllable_locked_out != _l.Lreg_controllable_locked_out) return false;
		if(Lsys_fair3done_out != _l.Lsys_fair3done_out) return false;
		if(Lreg_stateG3_1_out != _l.Lreg_stateG3_1_out) return false;
		if(Lreg_controllable_ndecide_out != _l.Lreg_controllable_ndecide_out) return false;
		if(Lreg_stateG3_2_out != _l.Lreg_stateG3_2_out) return false;
		if(Lreg_i_hbusreq0_out != _l.Lreg_i_hbusreq0_out) return false;
		if(Lreg_controllable_busreq_out != _l.Lreg_controllable_busreq_out) return false;
		if(Lreg_controllable_nstart_out != _l.Lreg_controllable_nstart_out) return false;
		if(Lreg_i_hbusreq1_out != _l.Lreg_i_hbusreq1_out) return false;
		if(Lsys_fair1done_out != _l.Lsys_fair1done_out) return false;
		if(Lreg_stateG2_out != _l.Lreg_stateG2_out) return false;
		if(Lreg_stateG10_1_out != _l.Lreg_stateG10_1_out) return false;
		if(Lenv_fair0done_out != _l.Lenv_fair0done_out) return false;
		if(Lreg_controllable_nhgrant0_out != _l.Lreg_controllable_nhgrant0_out) return false;
		if(Lreg_i_hlock2_out != _l.Lreg_i_hlock2_out) return false;
		if(Lreg_stateG10_2_out != _l.Lreg_stateG10_2_out) return false;
		if(Lreg_stateA1_out != _l.Lreg_stateA1_out) return false;
		if(Lreg_controllable_hmastlock_out != _l.Lreg_controllable_hmastlock_out) return false;
		if(Lsys_fair4done_out != _l.Lsys_fair4done_out) return false;
		if(Lreg_i_hbusreq2_out != _l.Lreg_i_hbusreq2_out) return false;
		if(Lreg_i_hlock1_out != _l.Lreg_i_hlock1_out) return false;
		if(Lfair_cnt0_out != _l.Lfair_cnt0_out) return false;
		if(Lfair_cnt1_out != _l.Lfair_cnt1_out) return false;
		if(Lfair_cnt2_out != _l.Lfair_cnt2_out) return false;
		if(Lenv_safe_err_happened_out != _l.Lenv_safe_err_happened_out) return false;
		if(Lreg_i_hlock0_out != _l.Lreg_i_hlock0_out) return false;
		if(Lreg_i_hready_out != _l.Lreg_i_hready_out) return false;
		if(Lreg_controllable_hgrant1_out != _l.Lreg_controllable_hgrant1_out) return false;
		if(Lsys_fair2done_out != _l.Lsys_fair2done_out) return false;
		if(Lreg_controllable_hmaster0_out != _l.Lreg_controllable_hmaster0_out) return false;
return true;
}

        inline size_t hash() const {
        size_t seed = global_t::instance().hash_seed();
        
		boost::hash_combine(seed, Ii_hbusreq0);
		boost::hash_combine(seed, Ii_hbusreq1);
		boost::hash_combine(seed, Ii_hbusreq2);
		boost::hash_combine(seed, Ii_hburst1);
		boost::hash_combine(seed, Ii_hburst0);
		boost::hash_combine(seed, Ii_hlock0);
		boost::hash_combine(seed, Ii_hlock1);
		boost::hash_combine(seed, Ii_hlock2);
		boost::hash_combine(seed, Ii_hready);
		boost::hash_combine(seed, Icontrollable_hmastlock);
		boost::hash_combine(seed, Icontrollable_nstart);
		boost::hash_combine(seed, Icontrollable_hmaster1);
		boost::hash_combine(seed, Icontrollable_locked);
		boost::hash_combine(seed, Icontrollable_hmaster0);
		boost::hash_combine(seed, Icontrollable_hgrant1);
		boost::hash_combine(seed, Icontrollable_busreq);
		boost::hash_combine(seed, Icontrollable_hgrant2);
		boost::hash_combine(seed, Icontrollable_ndecide);
		boost::hash_combine(seed, Icontrollable_nhgrant0);
		boost::hash_combine(seed, Ln41);
		boost::hash_combine(seed, Lreg_controllable_hgrant2_out);
		boost::hash_combine(seed, Lreg_controllable_hmaster1_out);
		boost::hash_combine(seed, Lsys_fair0done_out);
		boost::hash_combine(seed, Lreg_stateG3_0_out);
		boost::hash_combine(seed, Lenv_fair1done_out);
		boost::hash_combine(seed, Lreg_controllable_locked_out);
		boost::hash_combine(seed, Lsys_fair3done_out);
		boost::hash_combine(seed, Lreg_stateG3_1_out);
		boost::hash_combine(seed, Lreg_controllable_ndecide_out);
		boost::hash_combine(seed, Lreg_stateG3_2_out);
		boost::hash_combine(seed, Lreg_i_hbusreq0_out);
		boost::hash_combine(seed, Lreg_controllable_busreq_out);
		boost::hash_combine(seed, Lreg_controllable_nstart_out);
		boost::hash_combine(seed, Lreg_i_hbusreq1_out);
		boost::hash_combine(seed, Lsys_fair1done_out);
		boost::hash_combine(seed, Lreg_stateG2_out);
		boost::hash_combine(seed, Lreg_stateG10_1_out);
		boost::hash_combine(seed, Lenv_fair0done_out);
		boost::hash_combine(seed, Lreg_controllable_nhgrant0_out);
		boost::hash_combine(seed, Lreg_i_hlock2_out);
		boost::hash_combine(seed, Lreg_stateG10_2_out);
		boost::hash_combine(seed, Lreg_stateA1_out);
		boost::hash_combine(seed, Lreg_controllable_hmastlock_out);
		boost::hash_combine(seed, Lsys_fair4done_out);
		boost::hash_combine(seed, Lreg_i_hbusreq2_out);
		boost::hash_combine(seed, Lreg_i_hlock1_out);
		boost::hash_combine(seed, Lfair_cnt0_out);
		boost::hash_combine(seed, Lfair_cnt1_out);
		boost::hash_combine(seed, Lfair_cnt2_out);
		boost::hash_combine(seed, Lenv_safe_err_happened_out);
		boost::hash_combine(seed, Lreg_i_hlock0_out);
		boost::hash_combine(seed, Lreg_i_hready_out);
		boost::hash_combine(seed, Lreg_controllable_hgrant1_out);
		boost::hash_combine(seed, Lsys_fair2done_out);
		boost::hash_combine(seed, Lreg_controllable_hmaster0_out);
return seed;
}

        void output(std::ostream & os) const {
        
		os << "Ii_hbusreq0 = " << Ii_hbusreq0 << ",";
		os << "Ii_hbusreq1 = " << Ii_hbusreq1 << ",";
		os << "Ii_hbusreq2 = " << Ii_hbusreq2 << ",";
		os << "Ii_hburst1 = " << Ii_hburst1 << ",";
		os << "Ii_hburst0 = " << Ii_hburst0 << ",";
		os << "Ii_hlock0 = " << Ii_hlock0 << ",";
		os << "Ii_hlock1 = " << Ii_hlock1 << ",";
		os << "Ii_hlock2 = " << Ii_hlock2 << ",";
		os << "Ii_hready = " << Ii_hready << ",";
		os << "Icontrollable_hmastlock = " << Icontrollable_hmastlock << ",";
		os << "Icontrollable_nstart = " << Icontrollable_nstart << ",";
		os << "Icontrollable_hmaster1 = " << Icontrollable_hmaster1 << ",";
		os << "Icontrollable_locked = " << Icontrollable_locked << ",";
		os << "Icontrollable_hmaster0 = " << Icontrollable_hmaster0 << ",";
		os << "Icontrollable_hgrant1 = " << Icontrollable_hgrant1 << ",";
		os << "Icontrollable_busreq = " << Icontrollable_busreq << ",";
		os << "Icontrollable_hgrant2 = " << Icontrollable_hgrant2 << ",";
		os << "Icontrollable_ndecide = " << Icontrollable_ndecide << ",";
		os << "Icontrollable_nhgrant0 = " << Icontrollable_nhgrant0 << ",";
		os << "Ln41 = " << Ln41 << ",";
		os << "Lreg_controllable_hgrant2_out = " << Lreg_controllable_hgrant2_out << ",";
		os << "Lreg_controllable_hmaster1_out = " << Lreg_controllable_hmaster1_out << ",";
		os << "Lsys_fair0done_out = " << Lsys_fair0done_out << ",";
		os << "Lreg_stateG3_0_out = " << Lreg_stateG3_0_out << ",";
		os << "Lenv_fair1done_out = " << Lenv_fair1done_out << ",";
		os << "Lreg_controllable_locked_out = " << Lreg_controllable_locked_out << ",";
		os << "Lsys_fair3done_out = " << Lsys_fair3done_out << ",";
		os << "Lreg_stateG3_1_out = " << Lreg_stateG3_1_out << ",";
		os << "Lreg_controllable_ndecide_out = " << Lreg_controllable_ndecide_out << ",";
		os << "Lreg_stateG3_2_out = " << Lreg_stateG3_2_out << ",";
		os << "Lreg_i_hbusreq0_out = " << Lreg_i_hbusreq0_out << ",";
		os << "Lreg_controllable_busreq_out = " << Lreg_controllable_busreq_out << ",";
		os << "Lreg_controllable_nstart_out = " << Lreg_controllable_nstart_out << ",";
		os << "Lreg_i_hbusreq1_out = " << Lreg_i_hbusreq1_out << ",";
		os << "Lsys_fair1done_out = " << Lsys_fair1done_out << ",";
		os << "Lreg_stateG2_out = " << Lreg_stateG2_out << ",";
		os << "Lreg_stateG10_1_out = " << Lreg_stateG10_1_out << ",";
		os << "Lenv_fair0done_out = " << Lenv_fair0done_out << ",";
		os << "Lreg_controllable_nhgrant0_out = " << Lreg_controllable_nhgrant0_out << ",";
		os << "Lreg_i_hlock2_out = " << Lreg_i_hlock2_out << ",";
		os << "Lreg_stateG10_2_out = " << Lreg_stateG10_2_out << ",";
		os << "Lreg_stateA1_out = " << Lreg_stateA1_out << ",";
		os << "Lreg_controllable_hmastlock_out = " << Lreg_controllable_hmastlock_out << ",";
		os << "Lsys_fair4done_out = " << Lsys_fair4done_out << ",";
		os << "Lreg_i_hbusreq2_out = " << Lreg_i_hbusreq2_out << ",";
		os << "Lreg_i_hlock1_out = " << Lreg_i_hlock1_out << ",";
		os << "Lfair_cnt0_out = " << Lfair_cnt0_out << ",";
		os << "Lfair_cnt1_out = " << Lfair_cnt1_out << ",";
		os << "Lfair_cnt2_out = " << Lfair_cnt2_out << ",";
		os << "Lenv_safe_err_happened_out = " << Lenv_safe_err_happened_out << ",";
		os << "Lreg_i_hlock0_out = " << Lreg_i_hlock0_out << ",";
		os << "Lreg_i_hready_out = " << Lreg_i_hready_out << ",";
		os << "Lreg_controllable_hgrant1_out = " << Lreg_controllable_hgrant1_out << ",";
		os << "Lsys_fair2done_out = " << Lsys_fair2done_out << ",";
		os << "Lreg_controllable_hmaster0_out = " << Lreg_controllable_hmaster0_out << ",";
	}
};
}
void build_model(syntax::system_t & s){
        	s.name("Mono");
        	s.layout_alloc< syntax::layout_T_alloc_t<monoprocess::layout_t> >();
        
s.add_clock("x_40");
s.add_clock("x_42");
s.add_clock("x_44");
s.add_clock("x_46");
s.add_clock("x_48");
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
s.add_location("Circuit", "JustSetIi_hburst1", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "JustSetIi_hbusreq2", "JustSetIi_hburst1", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Ii_hburst1=0;;\
                    }
                    
);
s.add_edge("Circuit", "JustSetIi_hbusreq2", "JustSetIi_hburst1", "", "", "", syntax::layout_true,
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
s.add_location("Circuit", "JustSetIi_hready", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "JustSetIi_hlock2", "JustSetIi_hready", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Ii_hready=0;;\
                    }
                    
);
s.add_edge("Circuit", "JustSetIi_hlock2", "JustSetIi_hready", "", "", "", syntax::layout_true,
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
s.add_location("Circuit", "JustSetIcontrollable_ndecide", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "JustSetIcontrollable_hgrant2", "JustSetIcontrollable_ndecide", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Icontrollable_ndecide=0;;\
                    }
                    
);
s.add_edge("Circuit", "JustSetIcontrollable_hgrant2", "JustSetIcontrollable_ndecide", "", "", "", syntax::layout_true,
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
s.add_location("Circuit", "UpdatedLn41", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "JustSetIcontrollable_nhgrant0", "UpdatedLn41", "", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Ln41==1;;\
        }
        );
s.add_edge("Circuit", "JustSetIcontrollable_nhgrant0", "UpdatedLn41", "x_40 <= 1000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Ln41 == 1 && _l.Ln41 != 1;\
        }
        );
s.add_edge("Circuit", "JustSetIcontrollable_nhgrant0", "UpdatedLn41", "x_40 <= 1500", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Ln41 == 0 && _l.Ln41 != 1;\
        }
        );
s.add_location("Circuit", "UpdatedLn41_becomes0","x_40<=1000", "");
s.add_location("Circuit", "UpdatedLn41_becomes1","x_40<=1500", "");
s.add_edge("Circuit", "JustSetIcontrollable_nhgrant0", "UpdatedLn41_becomes0", "x_40 < 1000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Ln41 == 1 && _l.Ln41 != 1;\
        }
        );
s.add_edge("Circuit", "UpdatedLn41_becomes0", "UpdatedLn41", "x_40 >= 1000", "x_40", "", syntax::layout_true,  [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Ln41 = 1;;\
                    }
                    );
s.add_edge("Circuit", "JustSetIcontrollable_nhgrant0", "UpdatedLn41_becomes1", "x_40 < 1500", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Ln41 == 0 && _l.Ln41 != 1;\
        }
        );
s.add_edge("Circuit", "UpdatedLn41_becomes1", "UpdatedLn41", "x_40 >= 1500", "x_40", "", syntax::layout_true,  [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Ln41 = 1;;\
                    }
                    );
s.add_location("Circuit", "UpdatedLreg_controllable_hgrant2_out", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "UpdatedLn41", "UpdatedLreg_controllable_hgrant2_out", "", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lreg_controllable_hgrant2_out==(_l.Icontrollable_hgrant2);;\
        }
        );
s.add_edge("Circuit", "UpdatedLn41", "UpdatedLreg_controllable_hgrant2_out", "x_42 <= 500", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lreg_controllable_hgrant2_out == 1 && _l.Lreg_controllable_hgrant2_out != (_l.Icontrollable_hgrant2);\
        }
        );
s.add_edge("Circuit", "UpdatedLn41", "UpdatedLreg_controllable_hgrant2_out", "x_42 <= 2000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lreg_controllable_hgrant2_out == 0 && _l.Lreg_controllable_hgrant2_out != (_l.Icontrollable_hgrant2);\
        }
        );
s.add_location("Circuit", "UpdatedLreg_controllable_hgrant2_out_becomes0","x_42<=500", "");
s.add_location("Circuit", "UpdatedLreg_controllable_hgrant2_out_becomes1","x_42<=2000", "");
s.add_edge("Circuit", "UpdatedLn41", "UpdatedLreg_controllable_hgrant2_out_becomes0", "x_42 < 500", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lreg_controllable_hgrant2_out == 1 && _l.Lreg_controllable_hgrant2_out != (_l.Icontrollable_hgrant2);\
        }
        );
s.add_edge("Circuit", "UpdatedLreg_controllable_hgrant2_out_becomes0", "UpdatedLreg_controllable_hgrant2_out", "x_42 >= 500", "x_42", "", syntax::layout_true,  [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Lreg_controllable_hgrant2_out = (_l.Icontrollable_hgrant2);;\
                    }
                    );
s.add_edge("Circuit", "UpdatedLn41", "UpdatedLreg_controllable_hgrant2_out_becomes1", "x_42 < 2000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lreg_controllable_hgrant2_out == 0 && _l.Lreg_controllable_hgrant2_out != (_l.Icontrollable_hgrant2);\
        }
        );
s.add_edge("Circuit", "UpdatedLreg_controllable_hgrant2_out_becomes1", "UpdatedLreg_controllable_hgrant2_out", "x_42 >= 2000", "x_42", "", syntax::layout_true,  [](syntax::layout_t  & l){\
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
s.add_edge("Circuit", "UpdatedLreg_controllable_hgrant2_out", "UpdatedLreg_controllable_hmaster1_out", "x_44 <= 2000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lreg_controllable_hmaster1_out == 1 && _l.Lreg_controllable_hmaster1_out != (_l.Icontrollable_hmaster1);\
        }
        );
s.add_edge("Circuit", "UpdatedLreg_controllable_hgrant2_out", "UpdatedLreg_controllable_hmaster1_out", "x_44 <= 3000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lreg_controllable_hmaster1_out == 0 && _l.Lreg_controllable_hmaster1_out != (_l.Icontrollable_hmaster1);\
        }
        );
s.add_location("Circuit", "UpdatedLreg_controllable_hmaster1_out_becomes0","x_44<=2000", "");
s.add_location("Circuit", "UpdatedLreg_controllable_hmaster1_out_becomes1","x_44<=3000", "");
s.add_edge("Circuit", "UpdatedLreg_controllable_hgrant2_out", "UpdatedLreg_controllable_hmaster1_out_becomes0", "x_44 < 2000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lreg_controllable_hmaster1_out == 1 && _l.Lreg_controllable_hmaster1_out != (_l.Icontrollable_hmaster1);\
        }
        );
s.add_edge("Circuit", "UpdatedLreg_controllable_hmaster1_out_becomes0", "UpdatedLreg_controllable_hmaster1_out", "x_44 >= 2000", "x_44", "", syntax::layout_true,  [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Lreg_controllable_hmaster1_out = (_l.Icontrollable_hmaster1);;\
                    }
                    );
s.add_edge("Circuit", "UpdatedLreg_controllable_hgrant2_out", "UpdatedLreg_controllable_hmaster1_out_becomes1", "x_44 < 3000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lreg_controllable_hmaster1_out == 0 && _l.Lreg_controllable_hmaster1_out != (_l.Icontrollable_hmaster1);\
        }
        );
s.add_edge("Circuit", "UpdatedLreg_controllable_hmaster1_out_becomes1", "UpdatedLreg_controllable_hmaster1_out", "x_44 >= 3000", "x_44", "", syntax::layout_true,  [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Lreg_controllable_hmaster1_out = (_l.Icontrollable_hmaster1);;\
                    }
                    );
s.add_location("Circuit", "UpdatedLsys_fair0done_out", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "UpdatedLreg_controllable_hmaster1_out", "UpdatedLsys_fair0done_out", "", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lsys_fair0done_out==(!(!(!((_l.Lsys_fair4done_out) && (_l.Ln41)) && (!(!(_l.Icontrollable_hmaster0) && (_l.Icontrollable_hmaster1)) && (_l.Ii_hbusreq2))) && (!(!((_l.Lsys_fair3done_out) && (_l.Ln41)) && (!((_l.Icontrollable_hmaster0) && !(_l.Icontrollable_hmaster1)) && (_l.Ii_hbusreq1))) && (!(!((_l.Lsys_fair2done_out) && (_l.Ln41)) && (!(!(_l.Icontrollable_hmaster0) && !(_l.Icontrollable_hmaster1)) && (_l.Ii_hbusreq0))) && (!(!((_l.Lsys_fair1done_out) && (_l.Ln41)) && !(!((_l.Lreg_stateG3_2_out) && (_l.Ln41)) && (!((_l.Lreg_stateG3_1_out) && (_l.Ln41)) && !((_l.Lreg_stateG3_0_out) && (_l.Ln41))))) && !(!((_l.Lsys_fair0done_out) && (_l.Ln41)) && ((_l.Lreg_stateG2_out) && (_l.Ln41))))))) && !(!((_l.Lsys_fair0done_out) && (_l.Ln41)) && ((_l.Lreg_stateG2_out) && (_l.Ln41))));;\
        }
        );
s.add_edge("Circuit", "UpdatedLreg_controllable_hmaster1_out", "UpdatedLsys_fair0done_out", "x_46 <= 3000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lsys_fair0done_out == 1 && _l.Lsys_fair0done_out != (!(!(!((_l.Lsys_fair4done_out) && (_l.Ln41)) && (!(!(_l.Icontrollable_hmaster0) && (_l.Icontrollable_hmaster1)) && (_l.Ii_hbusreq2))) && (!(!((_l.Lsys_fair3done_out) && (_l.Ln41)) && (!((_l.Icontrollable_hmaster0) && !(_l.Icontrollable_hmaster1)) && (_l.Ii_hbusreq1))) && (!(!((_l.Lsys_fair2done_out) && (_l.Ln41)) && (!(!(_l.Icontrollable_hmaster0) && !(_l.Icontrollable_hmaster1)) && (_l.Ii_hbusreq0))) && (!(!((_l.Lsys_fair1done_out) && (_l.Ln41)) && !(!((_l.Lreg_stateG3_2_out) && (_l.Ln41)) && (!((_l.Lreg_stateG3_1_out) && (_l.Ln41)) && !((_l.Lreg_stateG3_0_out) && (_l.Ln41))))) && !(!((_l.Lsys_fair0done_out) && (_l.Ln41)) && ((_l.Lreg_stateG2_out) && (_l.Ln41))))))) && !(!((_l.Lsys_fair0done_out) && (_l.Ln41)) && ((_l.Lreg_stateG2_out) && (_l.Ln41))));\
        }
        );
s.add_edge("Circuit", "UpdatedLreg_controllable_hmaster1_out", "UpdatedLsys_fair0done_out", "x_46 <= 0", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lsys_fair0done_out == 0 && _l.Lsys_fair0done_out != (!(!(!((_l.Lsys_fair4done_out) && (_l.Ln41)) && (!(!(_l.Icontrollable_hmaster0) && (_l.Icontrollable_hmaster1)) && (_l.Ii_hbusreq2))) && (!(!((_l.Lsys_fair3done_out) && (_l.Ln41)) && (!((_l.Icontrollable_hmaster0) && !(_l.Icontrollable_hmaster1)) && (_l.Ii_hbusreq1))) && (!(!((_l.Lsys_fair2done_out) && (_l.Ln41)) && (!(!(_l.Icontrollable_hmaster0) && !(_l.Icontrollable_hmaster1)) && (_l.Ii_hbusreq0))) && (!(!((_l.Lsys_fair1done_out) && (_l.Ln41)) && !(!((_l.Lreg_stateG3_2_out) && (_l.Ln41)) && (!((_l.Lreg_stateG3_1_out) && (_l.Ln41)) && !((_l.Lreg_stateG3_0_out) && (_l.Ln41))))) && !(!((_l.Lsys_fair0done_out) && (_l.Ln41)) && ((_l.Lreg_stateG2_out) && (_l.Ln41))))))) && !(!((_l.Lsys_fair0done_out) && (_l.Ln41)) && ((_l.Lreg_stateG2_out) && (_l.Ln41))));\
        }
        );
s.add_location("Circuit", "UpdatedLsys_fair0done_out_becomes0","x_46<=3000", "");
s.add_location("Circuit", "UpdatedLsys_fair0done_out_becomes1","x_46<=0", "");
s.add_edge("Circuit", "UpdatedLreg_controllable_hmaster1_out", "UpdatedLsys_fair0done_out_becomes0", "x_46 < 3000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lsys_fair0done_out == 1 && _l.Lsys_fair0done_out != (!(!(!((_l.Lsys_fair4done_out) && (_l.Ln41)) && (!(!(_l.Icontrollable_hmaster0) && (_l.Icontrollable_hmaster1)) && (_l.Ii_hbusreq2))) && (!(!((_l.Lsys_fair3done_out) && (_l.Ln41)) && (!((_l.Icontrollable_hmaster0) && !(_l.Icontrollable_hmaster1)) && (_l.Ii_hbusreq1))) && (!(!((_l.Lsys_fair2done_out) && (_l.Ln41)) && (!(!(_l.Icontrollable_hmaster0) && !(_l.Icontrollable_hmaster1)) && (_l.Ii_hbusreq0))) && (!(!((_l.Lsys_fair1done_out) && (_l.Ln41)) && !(!((_l.Lreg_stateG3_2_out) && (_l.Ln41)) && (!((_l.Lreg_stateG3_1_out) && (_l.Ln41)) && !((_l.Lreg_stateG3_0_out) && (_l.Ln41))))) && !(!((_l.Lsys_fair0done_out) && (_l.Ln41)) && ((_l.Lreg_stateG2_out) && (_l.Ln41))))))) && !(!((_l.Lsys_fair0done_out) && (_l.Ln41)) && ((_l.Lreg_stateG2_out) && (_l.Ln41))));\
        }
        );
s.add_edge("Circuit", "UpdatedLsys_fair0done_out_becomes0", "UpdatedLsys_fair0done_out", "x_46 >= 3000", "x_46", "", syntax::layout_true,  [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Lsys_fair0done_out = (!(!(!((_l.Lsys_fair4done_out) && (_l.Ln41)) && (!(!(_l.Icontrollable_hmaster0) && (_l.Icontrollable_hmaster1)) && (_l.Ii_hbusreq2))) && (!(!((_l.Lsys_fair3done_out) && (_l.Ln41)) && (!((_l.Icontrollable_hmaster0) && !(_l.Icontrollable_hmaster1)) && (_l.Ii_hbusreq1))) && (!(!((_l.Lsys_fair2done_out) && (_l.Ln41)) && (!(!(_l.Icontrollable_hmaster0) && !(_l.Icontrollable_hmaster1)) && (_l.Ii_hbusreq0))) && (!(!((_l.Lsys_fair1done_out) && (_l.Ln41)) && !(!((_l.Lreg_stateG3_2_out) && (_l.Ln41)) && (!((_l.Lreg_stateG3_1_out) && (_l.Ln41)) && !((_l.Lreg_stateG3_0_out) && (_l.Ln41))))) && !(!((_l.Lsys_fair0done_out) && (_l.Ln41)) && ((_l.Lreg_stateG2_out) && (_l.Ln41))))))) && !(!((_l.Lsys_fair0done_out) && (_l.Ln41)) && ((_l.Lreg_stateG2_out) && (_l.Ln41))));;\
                    }
                    );
s.add_edge("Circuit", "UpdatedLsys_fair0done_out_becomes1", "UpdatedLsys_fair0done_out", "x_46 >= 0", "x_46", "", syntax::layout_true,  [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Lsys_fair0done_out = (!(!(!((_l.Lsys_fair4done_out) && (_l.Ln41)) && (!(!(_l.Icontrollable_hmaster0) && (_l.Icontrollable_hmaster1)) && (_l.Ii_hbusreq2))) && (!(!((_l.Lsys_fair3done_out) && (_l.Ln41)) && (!((_l.Icontrollable_hmaster0) && !(_l.Icontrollable_hmaster1)) && (_l.Ii_hbusreq1))) && (!(!((_l.Lsys_fair2done_out) && (_l.Ln41)) && (!(!(_l.Icontrollable_hmaster0) && !(_l.Icontrollable_hmaster1)) && (_l.Ii_hbusreq0))) && (!(!((_l.Lsys_fair1done_out) && (_l.Ln41)) && !(!((_l.Lreg_stateG3_2_out) && (_l.Ln41)) && (!((_l.Lreg_stateG3_1_out) && (_l.Ln41)) && !((_l.Lreg_stateG3_0_out) && (_l.Ln41))))) && !(!((_l.Lsys_fair0done_out) && (_l.Ln41)) && ((_l.Lreg_stateG2_out) && (_l.Ln41))))))) && !(!((_l.Lsys_fair0done_out) && (_l.Ln41)) && ((_l.Lreg_stateG2_out) && (_l.Ln41))));;\
                    }
                    );
s.add_location("Circuit", "UpdatedLreg_stateG3_0_out", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "UpdatedLsys_fair0done_out", "UpdatedLreg_stateG3_0_out", "", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lreg_stateG3_0_out==!(!((!((!((_l.Lreg_stateG3_2_out) && (_l.Ln41)) && (_l.Ii_hready)) && ((_l.Lreg_stateG3_0_out) && (_l.Ln41))) && !(!(!((_l.Lreg_stateG3_2_out) && (_l.Ln41)) && (_l.Ii_hready)) && !((_l.Lreg_stateG3_0_out) && (_l.Ln41)))) && !(!((_l.Lreg_stateG3_1_out) && (_l.Ln41)) && !((_l.Lreg_stateG3_0_out) && (_l.Ln41)))) && !(((((!(_l.Icontrollable_nstart) && (_l.Icontrollable_hmastlock)) && !(_l.Ii_hburst0)) && (!((_l.Lreg_stateG3_2_out) && (_l.Ln41)) && (!((_l.Lreg_stateG3_1_out) && (_l.Ln41)) && !((_l.Lreg_stateG3_0_out) && (_l.Ln41))))) && (_l.Ii_hburst1)) && !(_l.Ii_hready)));;\
        }
        );
s.add_edge("Circuit", "UpdatedLsys_fair0done_out", "UpdatedLreg_stateG3_0_out", "x_48 <= 2500", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lreg_stateG3_0_out == 1 && _l.Lreg_stateG3_0_out != !(!((!((!((_l.Lreg_stateG3_2_out) && (_l.Ln41)) && (_l.Ii_hready)) && ((_l.Lreg_stateG3_0_out) && (_l.Ln41))) && !(!(!((_l.Lreg_stateG3_2_out) && (_l.Ln41)) && (_l.Ii_hready)) && !((_l.Lreg_stateG3_0_out) && (_l.Ln41)))) && !(!((_l.Lreg_stateG3_1_out) && (_l.Ln41)) && !((_l.Lreg_stateG3_0_out) && (_l.Ln41)))) && !(((((!(_l.Icontrollable_nstart) && (_l.Icontrollable_hmastlock)) && !(_l.Ii_hburst0)) && (!((_l.Lreg_stateG3_2_out) && (_l.Ln41)) && (!((_l.Lreg_stateG3_1_out) && (_l.Ln41)) && !((_l.Lreg_stateG3_0_out) && (_l.Ln41))))) && (_l.Ii_hburst1)) && !(_l.Ii_hready)));\
        }
        );
s.add_edge("Circuit", "UpdatedLsys_fair0done_out", "UpdatedLreg_stateG3_0_out", "x_48 <= 0", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lreg_stateG3_0_out == 0 && _l.Lreg_stateG3_0_out != !(!((!((!((_l.Lreg_stateG3_2_out) && (_l.Ln41)) && (_l.Ii_hready)) && ((_l.Lreg_stateG3_0_out) && (_l.Ln41))) && !(!(!((_l.Lreg_stateG3_2_out) && (_l.Ln41)) && (_l.Ii_hready)) && !((_l.Lreg_stateG3_0_out) && (_l.Ln41)))) && !(!((_l.Lreg_stateG3_1_out) && (_l.Ln41)) && !((_l.Lreg_stateG3_0_out) && (_l.Ln41)))) && !(((((!(_l.Icontrollable_nstart) && (_l.Icontrollable_hmastlock)) && !(_l.Ii_hburst0)) && (!((_l.Lreg_stateG3_2_out) && (_l.Ln41)) && (!((_l.Lreg_stateG3_1_out) && (_l.Ln41)) && !((_l.Lreg_stateG3_0_out) && (_l.Ln41))))) && (_l.Ii_hburst1)) && !(_l.Ii_hready)));\
        }
        );
s.add_location("Circuit", "UpdatedLreg_stateG3_0_out_becomes0","x_48<=2500", "");
s.add_location("Circuit", "UpdatedLreg_stateG3_0_out_becomes1","x_48<=0", "");
s.add_edge("Circuit", "UpdatedLsys_fair0done_out", "UpdatedLreg_stateG3_0_out_becomes0", "x_48 < 2500", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lreg_stateG3_0_out == 1 && _l.Lreg_stateG3_0_out != !(!((!((!((_l.Lreg_stateG3_2_out) && (_l.Ln41)) && (_l.Ii_hready)) && ((_l.Lreg_stateG3_0_out) && (_l.Ln41))) && !(!(!((_l.Lreg_stateG3_2_out) && (_l.Ln41)) && (_l.Ii_hready)) && !((_l.Lreg_stateG3_0_out) && (_l.Ln41)))) && !(!((_l.Lreg_stateG3_1_out) && (_l.Ln41)) && !((_l.Lreg_stateG3_0_out) && (_l.Ln41)))) && !(((((!(_l.Icontrollable_nstart) && (_l.Icontrollable_hmastlock)) && !(_l.Ii_hburst0)) && (!((_l.Lreg_stateG3_2_out) && (_l.Ln41)) && (!((_l.Lreg_stateG3_1_out) && (_l.Ln41)) && !((_l.Lreg_stateG3_0_out) && (_l.Ln41))))) && (_l.Ii_hburst1)) && !(_l.Ii_hready)));\
        }
        );
s.add_edge("Circuit", "UpdatedLreg_stateG3_0_out_becomes0", "UpdatedLreg_stateG3_0_out", "x_48 >= 2500", "x_48", "", syntax::layout_true,  [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Lreg_stateG3_0_out = !(!((!((!((_l.Lreg_stateG3_2_out) && (_l.Ln41)) && (_l.Ii_hready)) && ((_l.Lreg_stateG3_0_out) && (_l.Ln41))) && !(!(!((_l.Lreg_stateG3_2_out) && (_l.Ln41)) && (_l.Ii_hready)) && !((_l.Lreg_stateG3_0_out) && (_l.Ln41)))) && !(!((_l.Lreg_stateG3_1_out) && (_l.Ln41)) && !((_l.Lreg_stateG3_0_out) && (_l.Ln41)))) && !(((((!(_l.Icontrollable_nstart) && (_l.Icontrollable_hmastlock)) && !(_l.Ii_hburst0)) && (!((_l.Lreg_stateG3_2_out) && (_l.Ln41)) && (!((_l.Lreg_stateG3_1_out) && (_l.Ln41)) && !((_l.Lreg_stateG3_0_out) && (_l.Ln41))))) && (_l.Ii_hburst1)) && !(_l.Ii_hready)));;\
                    }
                    );
s.add_edge("Circuit", "UpdatedLreg_stateG3_0_out_becomes1", "UpdatedLreg_stateG3_0_out", "x_48 >= 0", "x_48", "", syntax::layout_true,  [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Lreg_stateG3_0_out = !(!((!((!((_l.Lreg_stateG3_2_out) && (_l.Ln41)) && (_l.Ii_hready)) && ((_l.Lreg_stateG3_0_out) && (_l.Ln41))) && !(!(!((_l.Lreg_stateG3_2_out) && (_l.Ln41)) && (_l.Ii_hready)) && !((_l.Lreg_stateG3_0_out) && (_l.Ln41)))) && !(!((_l.Lreg_stateG3_1_out) && (_l.Ln41)) && !((_l.Lreg_stateG3_0_out) && (_l.Ln41)))) && !(((((!(_l.Icontrollable_nstart) && (_l.Icontrollable_hmastlock)) && !(_l.Ii_hburst0)) && (!((_l.Lreg_stateG3_2_out) && (_l.Ln41)) && (!((_l.Lreg_stateG3_1_out) && (_l.Ln41)) && !((_l.Lreg_stateG3_0_out) && (_l.Ln41))))) && (_l.Ii_hburst1)) && !(_l.Ii_hready)));;\
                    }
                    );
s.add_edge("Circuit", "UpdatedLreg_stateG3_0_out", "dead", "T>3000", "", "", syntax::layout_true);
s.add_edge("Circuit", "UpdatedLreg_stateG3_0_out", "init", "T<=3000", "T", "", syntax::layout_true);
s.synchronizer<syntax::asynchronous_product_t>();
}
