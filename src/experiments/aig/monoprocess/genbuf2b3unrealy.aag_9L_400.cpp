#include <iostream>
        #include "syntax/system.hh"
        #include "syntax/sync_product.hh"
        namespace monoprocess {
        class layout_t : public syntax::layout_t {
        public:
        
	bool Ii_RtoB_ACK1;
	bool Ii_RtoB_ACK0;
	bool Ii_FULL;
	bool Ii_nEMPTY;
	bool Ii_StoB_REQ0;
	bool Ii_StoB_REQ1;
	bool Icontrollable_BtoR_REQ0;
	bool Icontrollable_BtoR_REQ1;
	bool Icontrollable_BtoS_ACK0;
	bool Icontrollable_BtoS_ACK1;
	bool Icontrollable_SLC0;
	bool Icontrollable_ENQ;
	bool Icontrollable_DEQ;
	bool Ln29;
	bool Lreg_stateG7_0_out;
	bool Lreg_controllable_BtoR_REQ1_out;
	bool Lreg_i_RtoB_ACK1_out;
	bool Lsys_fair0done_out;
	bool Lreg_controllable_BtoS_ACK0_out;
	bool Lenv_fair1done_out;
	bool Lreg_i_nEMPTY_out;
	bool Lreg_nstateG7_1_out;
	bool Lreg_controllable_BtoS_ACK1_out;
	bool Lreg_controllable_SLC0_out;
	bool Lsys_fair1done_out;
	bool Lenv_fair0done_out;
	bool Lreg_controllable_ENQ_out;
	bool Lreg_i_FULL_out;
	bool Lreg_stateG12_out;
	bool Lfair_cnt0_out;
	bool Lfair_cnt1_out;
	bool Lreg_controllable_DEQ_out;
	bool Lenv_safe_err_happened_out;
	bool Lreg_i_StoB_REQ1_out;
	bool Lreg_i_RtoB_ACK0_out;
	bool Lsys_fair2done_out;
	bool Lreg_controllable_BtoR_REQ0_out;
	bool Lreg_i_StoB_REQ0_out;
	layout_t(){
		Ii_RtoB_ACK1 = 0;
		Ii_RtoB_ACK0 = 0;
		Ii_FULL = 0;
		Ii_nEMPTY = 0;
		Ii_StoB_REQ0 = 0;
		Ii_StoB_REQ1 = 0;
		Icontrollable_BtoR_REQ0 = 0;
		Icontrollable_BtoR_REQ1 = 0;
		Icontrollable_BtoS_ACK0 = 0;
		Icontrollable_BtoS_ACK1 = 0;
		Icontrollable_SLC0 = 0;
		Icontrollable_ENQ = 0;
		Icontrollable_DEQ = 0;
		Ln29 = 0;
		Lreg_stateG7_0_out = 0;
		Lreg_controllable_BtoR_REQ1_out = 0;
		Lreg_i_RtoB_ACK1_out = 0;
		Lsys_fair0done_out = 0;
		Lreg_controllable_BtoS_ACK0_out = 0;
		Lenv_fair1done_out = 0;
		Lreg_i_nEMPTY_out = 0;
		Lreg_nstateG7_1_out = 0;
		Lreg_controllable_BtoS_ACK1_out = 0;
		Lreg_controllable_SLC0_out = 0;
		Lsys_fair1done_out = 0;
		Lenv_fair0done_out = 0;
		Lreg_controllable_ENQ_out = 0;
		Lreg_i_FULL_out = 0;
		Lreg_stateG12_out = 0;
		Lfair_cnt0_out = 0;
		Lfair_cnt1_out = 0;
		Lreg_controllable_DEQ_out = 0;
		Lenv_safe_err_happened_out = 0;
		Lreg_i_StoB_REQ1_out = 0;
		Lreg_i_RtoB_ACK0_out = 0;
		Lsys_fair2done_out = 0;
		Lreg_controllable_BtoR_REQ0_out = 0;
		Lreg_i_StoB_REQ0_out = 0;
	}
virtual ~layout_t(){}
layout_t (const layout_t &l) = default;

        inline bool operator == (const syntax::layout_t & l) const {
            monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);
        
		if(Ii_RtoB_ACK1 != _l.Ii_RtoB_ACK1) return false;
		if(Ii_RtoB_ACK0 != _l.Ii_RtoB_ACK0) return false;
		if(Ii_FULL != _l.Ii_FULL) return false;
		if(Ii_nEMPTY != _l.Ii_nEMPTY) return false;
		if(Ii_StoB_REQ0 != _l.Ii_StoB_REQ0) return false;
		if(Ii_StoB_REQ1 != _l.Ii_StoB_REQ1) return false;
		if(Icontrollable_BtoR_REQ0 != _l.Icontrollable_BtoR_REQ0) return false;
		if(Icontrollable_BtoR_REQ1 != _l.Icontrollable_BtoR_REQ1) return false;
		if(Icontrollable_BtoS_ACK0 != _l.Icontrollable_BtoS_ACK0) return false;
		if(Icontrollable_BtoS_ACK1 != _l.Icontrollable_BtoS_ACK1) return false;
		if(Icontrollable_SLC0 != _l.Icontrollable_SLC0) return false;
		if(Icontrollable_ENQ != _l.Icontrollable_ENQ) return false;
		if(Icontrollable_DEQ != _l.Icontrollable_DEQ) return false;
		if(Ln29 != _l.Ln29) return false;
		if(Lreg_stateG7_0_out != _l.Lreg_stateG7_0_out) return false;
		if(Lreg_controllable_BtoR_REQ1_out != _l.Lreg_controllable_BtoR_REQ1_out) return false;
		if(Lreg_i_RtoB_ACK1_out != _l.Lreg_i_RtoB_ACK1_out) return false;
		if(Lsys_fair0done_out != _l.Lsys_fair0done_out) return false;
		if(Lreg_controllable_BtoS_ACK0_out != _l.Lreg_controllable_BtoS_ACK0_out) return false;
		if(Lenv_fair1done_out != _l.Lenv_fair1done_out) return false;
		if(Lreg_i_nEMPTY_out != _l.Lreg_i_nEMPTY_out) return false;
		if(Lreg_nstateG7_1_out != _l.Lreg_nstateG7_1_out) return false;
		if(Lreg_controllable_BtoS_ACK1_out != _l.Lreg_controllable_BtoS_ACK1_out) return false;
		if(Lreg_controllable_SLC0_out != _l.Lreg_controllable_SLC0_out) return false;
		if(Lsys_fair1done_out != _l.Lsys_fair1done_out) return false;
		if(Lenv_fair0done_out != _l.Lenv_fair0done_out) return false;
		if(Lreg_controllable_ENQ_out != _l.Lreg_controllable_ENQ_out) return false;
		if(Lreg_i_FULL_out != _l.Lreg_i_FULL_out) return false;
		if(Lreg_stateG12_out != _l.Lreg_stateG12_out) return false;
		if(Lfair_cnt0_out != _l.Lfair_cnt0_out) return false;
		if(Lfair_cnt1_out != _l.Lfair_cnt1_out) return false;
		if(Lreg_controllable_DEQ_out != _l.Lreg_controllable_DEQ_out) return false;
		if(Lenv_safe_err_happened_out != _l.Lenv_safe_err_happened_out) return false;
		if(Lreg_i_StoB_REQ1_out != _l.Lreg_i_StoB_REQ1_out) return false;
		if(Lreg_i_RtoB_ACK0_out != _l.Lreg_i_RtoB_ACK0_out) return false;
		if(Lsys_fair2done_out != _l.Lsys_fair2done_out) return false;
		if(Lreg_controllable_BtoR_REQ0_out != _l.Lreg_controllable_BtoR_REQ0_out) return false;
		if(Lreg_i_StoB_REQ0_out != _l.Lreg_i_StoB_REQ0_out) return false;
return true;
}

        inline size_t hash() const {
        size_t seed = global_t::instance().hash_seed();
        
		boost::hash_combine(seed, Ii_RtoB_ACK1);
		boost::hash_combine(seed, Ii_RtoB_ACK0);
		boost::hash_combine(seed, Ii_FULL);
		boost::hash_combine(seed, Ii_nEMPTY);
		boost::hash_combine(seed, Ii_StoB_REQ0);
		boost::hash_combine(seed, Ii_StoB_REQ1);
		boost::hash_combine(seed, Icontrollable_BtoR_REQ0);
		boost::hash_combine(seed, Icontrollable_BtoR_REQ1);
		boost::hash_combine(seed, Icontrollable_BtoS_ACK0);
		boost::hash_combine(seed, Icontrollable_BtoS_ACK1);
		boost::hash_combine(seed, Icontrollable_SLC0);
		boost::hash_combine(seed, Icontrollable_ENQ);
		boost::hash_combine(seed, Icontrollable_DEQ);
		boost::hash_combine(seed, Ln29);
		boost::hash_combine(seed, Lreg_stateG7_0_out);
		boost::hash_combine(seed, Lreg_controllable_BtoR_REQ1_out);
		boost::hash_combine(seed, Lreg_i_RtoB_ACK1_out);
		boost::hash_combine(seed, Lsys_fair0done_out);
		boost::hash_combine(seed, Lreg_controllable_BtoS_ACK0_out);
		boost::hash_combine(seed, Lenv_fair1done_out);
		boost::hash_combine(seed, Lreg_i_nEMPTY_out);
		boost::hash_combine(seed, Lreg_nstateG7_1_out);
		boost::hash_combine(seed, Lreg_controllable_BtoS_ACK1_out);
		boost::hash_combine(seed, Lreg_controllable_SLC0_out);
		boost::hash_combine(seed, Lsys_fair1done_out);
		boost::hash_combine(seed, Lenv_fair0done_out);
		boost::hash_combine(seed, Lreg_controllable_ENQ_out);
		boost::hash_combine(seed, Lreg_i_FULL_out);
		boost::hash_combine(seed, Lreg_stateG12_out);
		boost::hash_combine(seed, Lfair_cnt0_out);
		boost::hash_combine(seed, Lfair_cnt1_out);
		boost::hash_combine(seed, Lreg_controllable_DEQ_out);
		boost::hash_combine(seed, Lenv_safe_err_happened_out);
		boost::hash_combine(seed, Lreg_i_StoB_REQ1_out);
		boost::hash_combine(seed, Lreg_i_RtoB_ACK0_out);
		boost::hash_combine(seed, Lsys_fair2done_out);
		boost::hash_combine(seed, Lreg_controllable_BtoR_REQ0_out);
		boost::hash_combine(seed, Lreg_i_StoB_REQ0_out);
return seed;
}

        void output(std::ostream & os) const {
        
		os << "Ii_RtoB_ACK1 = " << Ii_RtoB_ACK1 << ",";
		os << "Ii_RtoB_ACK0 = " << Ii_RtoB_ACK0 << ",";
		os << "Ii_FULL = " << Ii_FULL << ",";
		os << "Ii_nEMPTY = " << Ii_nEMPTY << ",";
		os << "Ii_StoB_REQ0 = " << Ii_StoB_REQ0 << ",";
		os << "Ii_StoB_REQ1 = " << Ii_StoB_REQ1 << ",";
		os << "Icontrollable_BtoR_REQ0 = " << Icontrollable_BtoR_REQ0 << ",";
		os << "Icontrollable_BtoR_REQ1 = " << Icontrollable_BtoR_REQ1 << ",";
		os << "Icontrollable_BtoS_ACK0 = " << Icontrollable_BtoS_ACK0 << ",";
		os << "Icontrollable_BtoS_ACK1 = " << Icontrollable_BtoS_ACK1 << ",";
		os << "Icontrollable_SLC0 = " << Icontrollable_SLC0 << ",";
		os << "Icontrollable_ENQ = " << Icontrollable_ENQ << ",";
		os << "Icontrollable_DEQ = " << Icontrollable_DEQ << ",";
		os << "Ln29 = " << Ln29 << ",";
		os << "Lreg_stateG7_0_out = " << Lreg_stateG7_0_out << ",";
		os << "Lreg_controllable_BtoR_REQ1_out = " << Lreg_controllable_BtoR_REQ1_out << ",";
		os << "Lreg_i_RtoB_ACK1_out = " << Lreg_i_RtoB_ACK1_out << ",";
		os << "Lsys_fair0done_out = " << Lsys_fair0done_out << ",";
		os << "Lreg_controllable_BtoS_ACK0_out = " << Lreg_controllable_BtoS_ACK0_out << ",";
		os << "Lenv_fair1done_out = " << Lenv_fair1done_out << ",";
		os << "Lreg_i_nEMPTY_out = " << Lreg_i_nEMPTY_out << ",";
		os << "Lreg_nstateG7_1_out = " << Lreg_nstateG7_1_out << ",";
		os << "Lreg_controllable_BtoS_ACK1_out = " << Lreg_controllable_BtoS_ACK1_out << ",";
		os << "Lreg_controllable_SLC0_out = " << Lreg_controllable_SLC0_out << ",";
		os << "Lsys_fair1done_out = " << Lsys_fair1done_out << ",";
		os << "Lenv_fair0done_out = " << Lenv_fair0done_out << ",";
		os << "Lreg_controllable_ENQ_out = " << Lreg_controllable_ENQ_out << ",";
		os << "Lreg_i_FULL_out = " << Lreg_i_FULL_out << ",";
		os << "Lreg_stateG12_out = " << Lreg_stateG12_out << ",";
		os << "Lfair_cnt0_out = " << Lfair_cnt0_out << ",";
		os << "Lfair_cnt1_out = " << Lfair_cnt1_out << ",";
		os << "Lreg_controllable_DEQ_out = " << Lreg_controllable_DEQ_out << ",";
		os << "Lenv_safe_err_happened_out = " << Lenv_safe_err_happened_out << ",";
		os << "Lreg_i_StoB_REQ1_out = " << Lreg_i_StoB_REQ1_out << ",";
		os << "Lreg_i_RtoB_ACK0_out = " << Lreg_i_RtoB_ACK0_out << ",";
		os << "Lsys_fair2done_out = " << Lsys_fair2done_out << ",";
		os << "Lreg_controllable_BtoR_REQ0_out = " << Lreg_controllable_BtoR_REQ0_out << ",";
		os << "Lreg_i_StoB_REQ0_out = " << Lreg_i_StoB_REQ0_out << ",";
	}
};
}
void build_model(syntax::system_t & s){
        	s.name("Mono");
        	s.layout_alloc< syntax::layout_T_alloc_t<monoprocess::layout_t> >();
        
s.add_clock("x_28");
s.add_clock("x_30");
s.add_clock("x_32");
s.add_clock("x_34");
s.add_clock("x_36");
s.add_clock("x_38");
s.add_clock("x_40");
s.add_clock("x_42");
s.add_clock("x_44");
s.add_clock("T");
s.add_label("err");
s.add_label("nothing");
s.add_process("Circuit");
s.add_location("Circuit", "init", "", "", syntax::loc_t::INIT | syntax::loc_t::URGENT);
s.add_location("Circuit", "dead", "", "err");
s.add_location("Circuit", "JustSetIi_RtoB_ACK1", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "init", "JustSetIi_RtoB_ACK1", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Ii_RtoB_ACK1=0;;\
                    }
                    
);
s.add_edge("Circuit", "init", "JustSetIi_RtoB_ACK1", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Ii_RtoB_ACK1=1;;\
                    }
                    
);
s.add_location("Circuit", "JustSetIi_RtoB_ACK0", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "JustSetIi_RtoB_ACK1", "JustSetIi_RtoB_ACK0", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Ii_RtoB_ACK0=0;;\
                    }
                    
);
s.add_edge("Circuit", "JustSetIi_RtoB_ACK1", "JustSetIi_RtoB_ACK0", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Ii_RtoB_ACK0=1;;\
                    }
                    
);
s.add_location("Circuit", "JustSetIi_FULL", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "JustSetIi_RtoB_ACK0", "JustSetIi_FULL", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Ii_FULL=0;;\
                    }
                    
);
s.add_edge("Circuit", "JustSetIi_RtoB_ACK0", "JustSetIi_FULL", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Ii_FULL=1;;\
                    }
                    
);
s.add_location("Circuit", "JustSetIi_nEMPTY", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "JustSetIi_FULL", "JustSetIi_nEMPTY", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Ii_nEMPTY=0;;\
                    }
                    
);
s.add_edge("Circuit", "JustSetIi_FULL", "JustSetIi_nEMPTY", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Ii_nEMPTY=1;;\
                    }
                    
);
s.add_location("Circuit", "JustSetIi_StoB_REQ0", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "JustSetIi_nEMPTY", "JustSetIi_StoB_REQ0", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Ii_StoB_REQ0=0;;\
                    }
                    
);
s.add_edge("Circuit", "JustSetIi_nEMPTY", "JustSetIi_StoB_REQ0", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Ii_StoB_REQ0=1;;\
                    }
                    
);
s.add_location("Circuit", "JustSetIi_StoB_REQ1", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "JustSetIi_StoB_REQ0", "JustSetIi_StoB_REQ1", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Ii_StoB_REQ1=0;;\
                    }
                    
);
s.add_edge("Circuit", "JustSetIi_StoB_REQ0", "JustSetIi_StoB_REQ1", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Ii_StoB_REQ1=1;;\
                    }
                    
);
s.add_location("Circuit", "JustSetIcontrollable_BtoR_REQ0", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "JustSetIi_StoB_REQ1", "JustSetIcontrollable_BtoR_REQ0", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Icontrollable_BtoR_REQ0=0;;\
                    }
                    
);
s.add_edge("Circuit", "JustSetIi_StoB_REQ1", "JustSetIcontrollable_BtoR_REQ0", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Icontrollable_BtoR_REQ0=1;;\
                    }
                    
);
s.add_location("Circuit", "JustSetIcontrollable_BtoR_REQ1", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "JustSetIcontrollable_BtoR_REQ0", "JustSetIcontrollable_BtoR_REQ1", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Icontrollable_BtoR_REQ1=0;;\
                    }
                    
);
s.add_edge("Circuit", "JustSetIcontrollable_BtoR_REQ0", "JustSetIcontrollable_BtoR_REQ1", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Icontrollable_BtoR_REQ1=1;;\
                    }
                    
);
s.add_location("Circuit", "JustSetIcontrollable_BtoS_ACK0", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "JustSetIcontrollable_BtoR_REQ1", "JustSetIcontrollable_BtoS_ACK0", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Icontrollable_BtoS_ACK0=0;;\
                    }
                    
);
s.add_edge("Circuit", "JustSetIcontrollable_BtoR_REQ1", "JustSetIcontrollable_BtoS_ACK0", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Icontrollable_BtoS_ACK0=1;;\
                    }
                    
);
s.add_location("Circuit", "JustSetIcontrollable_BtoS_ACK1", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "JustSetIcontrollable_BtoS_ACK0", "JustSetIcontrollable_BtoS_ACK1", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Icontrollable_BtoS_ACK1=0;;\
                    }
                    
);
s.add_edge("Circuit", "JustSetIcontrollable_BtoS_ACK0", "JustSetIcontrollable_BtoS_ACK1", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Icontrollable_BtoS_ACK1=1;;\
                    }
                    
);
s.add_location("Circuit", "JustSetIcontrollable_SLC0", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "JustSetIcontrollable_BtoS_ACK1", "JustSetIcontrollable_SLC0", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Icontrollable_SLC0=0;;\
                    }
                    
);
s.add_edge("Circuit", "JustSetIcontrollable_BtoS_ACK1", "JustSetIcontrollable_SLC0", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Icontrollable_SLC0=1;;\
                    }
                    
);
s.add_location("Circuit", "JustSetIcontrollable_ENQ", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "JustSetIcontrollable_SLC0", "JustSetIcontrollable_ENQ", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Icontrollable_ENQ=0;;\
                    }
                    
);
s.add_edge("Circuit", "JustSetIcontrollable_SLC0", "JustSetIcontrollable_ENQ", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Icontrollable_ENQ=1;;\
                    }
                    
);
s.add_location("Circuit", "JustSetIcontrollable_DEQ", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "JustSetIcontrollable_ENQ", "JustSetIcontrollable_DEQ", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Icontrollable_DEQ=0;;\
                    }
                    
);
s.add_edge("Circuit", "JustSetIcontrollable_ENQ", "JustSetIcontrollable_DEQ", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Icontrollable_DEQ=1;;\
                    }
                    
);
s.add_location("Circuit", "UpdatedLn29", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "JustSetIcontrollable_DEQ", "UpdatedLn29", "", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Ln29==1;;\
        }
        );
s.add_edge("Circuit", "JustSetIcontrollable_DEQ", "UpdatedLn29", "x_28 <= 1000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Ln29 == 1 && _l.Ln29 != 1;\
        }
        );
s.add_edge("Circuit", "JustSetIcontrollable_DEQ", "UpdatedLn29", "x_28 <= 1500", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Ln29 == 0 && _l.Ln29 != 1;\
        }
        );
s.add_location("Circuit", "UpdatedLn29_becomes0","x_28<=1000", "");
s.add_location("Circuit", "UpdatedLn29_becomes1","x_28<=1500", "");
s.add_edge("Circuit", "JustSetIcontrollable_DEQ", "UpdatedLn29_becomes0", "x_28 < 1000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Ln29 == 1 && _l.Ln29 != 1;\
        }
        );
s.add_edge("Circuit", "UpdatedLn29_becomes0", "UpdatedLn29", "x_28 >= 1000", "x_28", "", syntax::layout_true,  [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Ln29 = 1;;\
                    }
                    );
s.add_edge("Circuit", "JustSetIcontrollable_DEQ", "UpdatedLn29_becomes1", "x_28 < 1500", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Ln29 == 0 && _l.Ln29 != 1;\
        }
        );
s.add_edge("Circuit", "UpdatedLn29_becomes1", "UpdatedLn29", "x_28 >= 1500", "x_28", "", syntax::layout_true,  [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Ln29 = 1;;\
                    }
                    );
s.add_location("Circuit", "UpdatedLreg_stateG7_0_out", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "UpdatedLn29", "UpdatedLreg_stateG7_0_out", "", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lreg_stateG7_0_out==(!(!(!((_l.Lreg_controllable_BtoR_REQ1_out) && (_l.Ln29)) && !((_l.Lreg_controllable_BtoR_REQ0_out) && (_l.Ln29))) && !((_l.Lreg_stateG7_0_out) && (_l.Ln29))) && (!((!((_l.Lreg_nstateG7_1_out) && (_l.Ln29)) && ((_l.Lreg_controllable_BtoR_REQ0_out) && (_l.Ln29))) && !((_l.Lreg_controllable_BtoR_REQ1_out) && (_l.Ln29))) && !((((_l.Lreg_nstateG7_1_out) && (_l.Ln29)) && !((_l.Lreg_controllable_BtoR_REQ0_out) && (_l.Ln29))) && ((_l.Lreg_controllable_BtoR_REQ1_out) && (_l.Ln29)))));;\
        }
        );
s.add_edge("Circuit", "UpdatedLn29", "UpdatedLreg_stateG7_0_out", "x_30 <= 500", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lreg_stateG7_0_out == 1 && _l.Lreg_stateG7_0_out != (!(!(!((_l.Lreg_controllable_BtoR_REQ1_out) && (_l.Ln29)) && !((_l.Lreg_controllable_BtoR_REQ0_out) && (_l.Ln29))) && !((_l.Lreg_stateG7_0_out) && (_l.Ln29))) && (!((!((_l.Lreg_nstateG7_1_out) && (_l.Ln29)) && ((_l.Lreg_controllable_BtoR_REQ0_out) && (_l.Ln29))) && !((_l.Lreg_controllable_BtoR_REQ1_out) && (_l.Ln29))) && !((((_l.Lreg_nstateG7_1_out) && (_l.Ln29)) && !((_l.Lreg_controllable_BtoR_REQ0_out) && (_l.Ln29))) && ((_l.Lreg_controllable_BtoR_REQ1_out) && (_l.Ln29)))));\
        }
        );
s.add_edge("Circuit", "UpdatedLn29", "UpdatedLreg_stateG7_0_out", "x_30 <= 2000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lreg_stateG7_0_out == 0 && _l.Lreg_stateG7_0_out != (!(!(!((_l.Lreg_controllable_BtoR_REQ1_out) && (_l.Ln29)) && !((_l.Lreg_controllable_BtoR_REQ0_out) && (_l.Ln29))) && !((_l.Lreg_stateG7_0_out) && (_l.Ln29))) && (!((!((_l.Lreg_nstateG7_1_out) && (_l.Ln29)) && ((_l.Lreg_controllable_BtoR_REQ0_out) && (_l.Ln29))) && !((_l.Lreg_controllable_BtoR_REQ1_out) && (_l.Ln29))) && !((((_l.Lreg_nstateG7_1_out) && (_l.Ln29)) && !((_l.Lreg_controllable_BtoR_REQ0_out) && (_l.Ln29))) && ((_l.Lreg_controllable_BtoR_REQ1_out) && (_l.Ln29)))));\
        }
        );
s.add_location("Circuit", "UpdatedLreg_stateG7_0_out_becomes0","x_30<=500", "");
s.add_location("Circuit", "UpdatedLreg_stateG7_0_out_becomes1","x_30<=2000", "");
s.add_edge("Circuit", "UpdatedLn29", "UpdatedLreg_stateG7_0_out_becomes0", "x_30 < 500", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lreg_stateG7_0_out == 1 && _l.Lreg_stateG7_0_out != (!(!(!((_l.Lreg_controllable_BtoR_REQ1_out) && (_l.Ln29)) && !((_l.Lreg_controllable_BtoR_REQ0_out) && (_l.Ln29))) && !((_l.Lreg_stateG7_0_out) && (_l.Ln29))) && (!((!((_l.Lreg_nstateG7_1_out) && (_l.Ln29)) && ((_l.Lreg_controllable_BtoR_REQ0_out) && (_l.Ln29))) && !((_l.Lreg_controllable_BtoR_REQ1_out) && (_l.Ln29))) && !((((_l.Lreg_nstateG7_1_out) && (_l.Ln29)) && !((_l.Lreg_controllable_BtoR_REQ0_out) && (_l.Ln29))) && ((_l.Lreg_controllable_BtoR_REQ1_out) && (_l.Ln29)))));\
        }
        );
s.add_edge("Circuit", "UpdatedLreg_stateG7_0_out_becomes0", "UpdatedLreg_stateG7_0_out", "x_30 >= 500", "x_30", "", syntax::layout_true,  [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Lreg_stateG7_0_out = (!(!(!((_l.Lreg_controllable_BtoR_REQ1_out) && (_l.Ln29)) && !((_l.Lreg_controllable_BtoR_REQ0_out) && (_l.Ln29))) && !((_l.Lreg_stateG7_0_out) && (_l.Ln29))) && (!((!((_l.Lreg_nstateG7_1_out) && (_l.Ln29)) && ((_l.Lreg_controllable_BtoR_REQ0_out) && (_l.Ln29))) && !((_l.Lreg_controllable_BtoR_REQ1_out) && (_l.Ln29))) && !((((_l.Lreg_nstateG7_1_out) && (_l.Ln29)) && !((_l.Lreg_controllable_BtoR_REQ0_out) && (_l.Ln29))) && ((_l.Lreg_controllable_BtoR_REQ1_out) && (_l.Ln29)))));;\
                    }
                    );
s.add_edge("Circuit", "UpdatedLn29", "UpdatedLreg_stateG7_0_out_becomes1", "x_30 < 2000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lreg_stateG7_0_out == 0 && _l.Lreg_stateG7_0_out != (!(!(!((_l.Lreg_controllable_BtoR_REQ1_out) && (_l.Ln29)) && !((_l.Lreg_controllable_BtoR_REQ0_out) && (_l.Ln29))) && !((_l.Lreg_stateG7_0_out) && (_l.Ln29))) && (!((!((_l.Lreg_nstateG7_1_out) && (_l.Ln29)) && ((_l.Lreg_controllable_BtoR_REQ0_out) && (_l.Ln29))) && !((_l.Lreg_controllable_BtoR_REQ1_out) && (_l.Ln29))) && !((((_l.Lreg_nstateG7_1_out) && (_l.Ln29)) && !((_l.Lreg_controllable_BtoR_REQ0_out) && (_l.Ln29))) && ((_l.Lreg_controllable_BtoR_REQ1_out) && (_l.Ln29)))));\
        }
        );
s.add_edge("Circuit", "UpdatedLreg_stateG7_0_out_becomes1", "UpdatedLreg_stateG7_0_out", "x_30 >= 2000", "x_30", "", syntax::layout_true,  [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Lreg_stateG7_0_out = (!(!(!((_l.Lreg_controllable_BtoR_REQ1_out) && (_l.Ln29)) && !((_l.Lreg_controllable_BtoR_REQ0_out) && (_l.Ln29))) && !((_l.Lreg_stateG7_0_out) && (_l.Ln29))) && (!((!((_l.Lreg_nstateG7_1_out) && (_l.Ln29)) && ((_l.Lreg_controllable_BtoR_REQ0_out) && (_l.Ln29))) && !((_l.Lreg_controllable_BtoR_REQ1_out) && (_l.Ln29))) && !((((_l.Lreg_nstateG7_1_out) && (_l.Ln29)) && !((_l.Lreg_controllable_BtoR_REQ0_out) && (_l.Ln29))) && ((_l.Lreg_controllable_BtoR_REQ1_out) && (_l.Ln29)))));;\
                    }
                    );
s.add_location("Circuit", "UpdatedLreg_controllable_BtoR_REQ1_out", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "UpdatedLreg_stateG7_0_out", "UpdatedLreg_controllable_BtoR_REQ1_out", "", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lreg_controllable_BtoR_REQ1_out==(_l.Icontrollable_BtoR_REQ1);;\
        }
        );
s.add_edge("Circuit", "UpdatedLreg_stateG7_0_out", "UpdatedLreg_controllable_BtoR_REQ1_out", "x_32 <= 2000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lreg_controllable_BtoR_REQ1_out == 1 && _l.Lreg_controllable_BtoR_REQ1_out != (_l.Icontrollable_BtoR_REQ1);\
        }
        );
s.add_edge("Circuit", "UpdatedLreg_stateG7_0_out", "UpdatedLreg_controllable_BtoR_REQ1_out", "x_32 <= 3000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lreg_controllable_BtoR_REQ1_out == 0 && _l.Lreg_controllable_BtoR_REQ1_out != (_l.Icontrollable_BtoR_REQ1);\
        }
        );
s.add_location("Circuit", "UpdatedLreg_controllable_BtoR_REQ1_out_becomes0","x_32<=2000", "");
s.add_location("Circuit", "UpdatedLreg_controllable_BtoR_REQ1_out_becomes1","x_32<=3000", "");
s.add_edge("Circuit", "UpdatedLreg_stateG7_0_out", "UpdatedLreg_controllable_BtoR_REQ1_out_becomes0", "x_32 < 2000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lreg_controllable_BtoR_REQ1_out == 1 && _l.Lreg_controllable_BtoR_REQ1_out != (_l.Icontrollable_BtoR_REQ1);\
        }
        );
s.add_edge("Circuit", "UpdatedLreg_controllable_BtoR_REQ1_out_becomes0", "UpdatedLreg_controllable_BtoR_REQ1_out", "x_32 >= 2000", "x_32", "", syntax::layout_true,  [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Lreg_controllable_BtoR_REQ1_out = (_l.Icontrollable_BtoR_REQ1);;\
                    }
                    );
s.add_edge("Circuit", "UpdatedLreg_stateG7_0_out", "UpdatedLreg_controllable_BtoR_REQ1_out_becomes1", "x_32 < 3000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lreg_controllable_BtoR_REQ1_out == 0 && _l.Lreg_controllable_BtoR_REQ1_out != (_l.Icontrollable_BtoR_REQ1);\
        }
        );
s.add_edge("Circuit", "UpdatedLreg_controllable_BtoR_REQ1_out_becomes1", "UpdatedLreg_controllable_BtoR_REQ1_out", "x_32 >= 3000", "x_32", "", syntax::layout_true,  [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Lreg_controllable_BtoR_REQ1_out = (_l.Icontrollable_BtoR_REQ1);;\
                    }
                    );
s.add_location("Circuit", "UpdatedLreg_i_RtoB_ACK1_out", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "UpdatedLreg_controllable_BtoR_REQ1_out", "UpdatedLreg_i_RtoB_ACK1_out", "", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lreg_i_RtoB_ACK1_out==(_l.Ii_RtoB_ACK1);;\
        }
        );
s.add_edge("Circuit", "UpdatedLreg_controllable_BtoR_REQ1_out", "UpdatedLreg_i_RtoB_ACK1_out", "x_34 <= 3000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lreg_i_RtoB_ACK1_out == 1 && _l.Lreg_i_RtoB_ACK1_out != (_l.Ii_RtoB_ACK1);\
        }
        );
s.add_edge("Circuit", "UpdatedLreg_controllable_BtoR_REQ1_out", "UpdatedLreg_i_RtoB_ACK1_out", "x_34 <= 0", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lreg_i_RtoB_ACK1_out == 0 && _l.Lreg_i_RtoB_ACK1_out != (_l.Ii_RtoB_ACK1);\
        }
        );
s.add_location("Circuit", "UpdatedLreg_i_RtoB_ACK1_out_becomes0","x_34<=3000", "");
s.add_location("Circuit", "UpdatedLreg_i_RtoB_ACK1_out_becomes1","x_34<=0", "");
s.add_edge("Circuit", "UpdatedLreg_controllable_BtoR_REQ1_out", "UpdatedLreg_i_RtoB_ACK1_out_becomes0", "x_34 < 3000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lreg_i_RtoB_ACK1_out == 1 && _l.Lreg_i_RtoB_ACK1_out != (_l.Ii_RtoB_ACK1);\
        }
        );
s.add_edge("Circuit", "UpdatedLreg_i_RtoB_ACK1_out_becomes0", "UpdatedLreg_i_RtoB_ACK1_out", "x_34 >= 3000", "x_34", "", syntax::layout_true,  [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Lreg_i_RtoB_ACK1_out = (_l.Ii_RtoB_ACK1);;\
                    }
                    );
s.add_edge("Circuit", "UpdatedLreg_i_RtoB_ACK1_out_becomes1", "UpdatedLreg_i_RtoB_ACK1_out", "x_34 >= 0", "x_34", "", syntax::layout_true,  [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Lreg_i_RtoB_ACK1_out = (_l.Ii_RtoB_ACK1);;\
                    }
                    );
s.add_location("Circuit", "UpdatedLsys_fair0done_out", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "UpdatedLreg_i_RtoB_ACK1_out", "UpdatedLsys_fair0done_out", "", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lsys_fair0done_out==(!(!(!((_l.Lsys_fair2done_out) && (_l.Ln29)) && ((_l.Lreg_stateG12_out) && (_l.Ln29))) && (!(!((_l.Lsys_fair1done_out) && (_l.Ln29)) && !(!((_l.Ii_StoB_REQ1) && !(_l.Icontrollable_BtoS_ACK1)) && !(!(_l.Ii_StoB_REQ1) && (_l.Icontrollable_BtoS_ACK1)))) && !(!(!((_l.Ii_StoB_REQ0) && !(_l.Icontrollable_BtoS_ACK0)) && !(!(_l.Ii_StoB_REQ0) && (_l.Icontrollable_BtoS_ACK0))) && !((_l.Lsys_fair0done_out) && (_l.Ln29))))) && !(!(!((_l.Ii_StoB_REQ0) && !(_l.Icontrollable_BtoS_ACK0)) && !(!(_l.Ii_StoB_REQ0) && (_l.Icontrollable_BtoS_ACK0))) && !((_l.Lsys_fair0done_out) && (_l.Ln29))));;\
        }
        );
s.add_edge("Circuit", "UpdatedLreg_i_RtoB_ACK1_out", "UpdatedLsys_fair0done_out", "x_36 <= 2500", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lsys_fair0done_out == 1 && _l.Lsys_fair0done_out != (!(!(!((_l.Lsys_fair2done_out) && (_l.Ln29)) && ((_l.Lreg_stateG12_out) && (_l.Ln29))) && (!(!((_l.Lsys_fair1done_out) && (_l.Ln29)) && !(!((_l.Ii_StoB_REQ1) && !(_l.Icontrollable_BtoS_ACK1)) && !(!(_l.Ii_StoB_REQ1) && (_l.Icontrollable_BtoS_ACK1)))) && !(!(!((_l.Ii_StoB_REQ0) && !(_l.Icontrollable_BtoS_ACK0)) && !(!(_l.Ii_StoB_REQ0) && (_l.Icontrollable_BtoS_ACK0))) && !((_l.Lsys_fair0done_out) && (_l.Ln29))))) && !(!(!((_l.Ii_StoB_REQ0) && !(_l.Icontrollable_BtoS_ACK0)) && !(!(_l.Ii_StoB_REQ0) && (_l.Icontrollable_BtoS_ACK0))) && !((_l.Lsys_fair0done_out) && (_l.Ln29))));\
        }
        );
s.add_edge("Circuit", "UpdatedLreg_i_RtoB_ACK1_out", "UpdatedLsys_fair0done_out", "x_36 <= 0", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lsys_fair0done_out == 0 && _l.Lsys_fair0done_out != (!(!(!((_l.Lsys_fair2done_out) && (_l.Ln29)) && ((_l.Lreg_stateG12_out) && (_l.Ln29))) && (!(!((_l.Lsys_fair1done_out) && (_l.Ln29)) && !(!((_l.Ii_StoB_REQ1) && !(_l.Icontrollable_BtoS_ACK1)) && !(!(_l.Ii_StoB_REQ1) && (_l.Icontrollable_BtoS_ACK1)))) && !(!(!((_l.Ii_StoB_REQ0) && !(_l.Icontrollable_BtoS_ACK0)) && !(!(_l.Ii_StoB_REQ0) && (_l.Icontrollable_BtoS_ACK0))) && !((_l.Lsys_fair0done_out) && (_l.Ln29))))) && !(!(!((_l.Ii_StoB_REQ0) && !(_l.Icontrollable_BtoS_ACK0)) && !(!(_l.Ii_StoB_REQ0) && (_l.Icontrollable_BtoS_ACK0))) && !((_l.Lsys_fair0done_out) && (_l.Ln29))));\
        }
        );
s.add_location("Circuit", "UpdatedLsys_fair0done_out_becomes0","x_36<=2500", "");
s.add_location("Circuit", "UpdatedLsys_fair0done_out_becomes1","x_36<=0", "");
s.add_edge("Circuit", "UpdatedLreg_i_RtoB_ACK1_out", "UpdatedLsys_fair0done_out_becomes0", "x_36 < 2500", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lsys_fair0done_out == 1 && _l.Lsys_fair0done_out != (!(!(!((_l.Lsys_fair2done_out) && (_l.Ln29)) && ((_l.Lreg_stateG12_out) && (_l.Ln29))) && (!(!((_l.Lsys_fair1done_out) && (_l.Ln29)) && !(!((_l.Ii_StoB_REQ1) && !(_l.Icontrollable_BtoS_ACK1)) && !(!(_l.Ii_StoB_REQ1) && (_l.Icontrollable_BtoS_ACK1)))) && !(!(!((_l.Ii_StoB_REQ0) && !(_l.Icontrollable_BtoS_ACK0)) && !(!(_l.Ii_StoB_REQ0) && (_l.Icontrollable_BtoS_ACK0))) && !((_l.Lsys_fair0done_out) && (_l.Ln29))))) && !(!(!((_l.Ii_StoB_REQ0) && !(_l.Icontrollable_BtoS_ACK0)) && !(!(_l.Ii_StoB_REQ0) && (_l.Icontrollable_BtoS_ACK0))) && !((_l.Lsys_fair0done_out) && (_l.Ln29))));\
        }
        );
s.add_edge("Circuit", "UpdatedLsys_fair0done_out_becomes0", "UpdatedLsys_fair0done_out", "x_36 >= 2500", "x_36", "", syntax::layout_true,  [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Lsys_fair0done_out = (!(!(!((_l.Lsys_fair2done_out) && (_l.Ln29)) && ((_l.Lreg_stateG12_out) && (_l.Ln29))) && (!(!((_l.Lsys_fair1done_out) && (_l.Ln29)) && !(!((_l.Ii_StoB_REQ1) && !(_l.Icontrollable_BtoS_ACK1)) && !(!(_l.Ii_StoB_REQ1) && (_l.Icontrollable_BtoS_ACK1)))) && !(!(!((_l.Ii_StoB_REQ0) && !(_l.Icontrollable_BtoS_ACK0)) && !(!(_l.Ii_StoB_REQ0) && (_l.Icontrollable_BtoS_ACK0))) && !((_l.Lsys_fair0done_out) && (_l.Ln29))))) && !(!(!((_l.Ii_StoB_REQ0) && !(_l.Icontrollable_BtoS_ACK0)) && !(!(_l.Ii_StoB_REQ0) && (_l.Icontrollable_BtoS_ACK0))) && !((_l.Lsys_fair0done_out) && (_l.Ln29))));;\
                    }
                    );
s.add_edge("Circuit", "UpdatedLsys_fair0done_out_becomes1", "UpdatedLsys_fair0done_out", "x_36 >= 0", "x_36", "", syntax::layout_true,  [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Lsys_fair0done_out = (!(!(!((_l.Lsys_fair2done_out) && (_l.Ln29)) && ((_l.Lreg_stateG12_out) && (_l.Ln29))) && (!(!((_l.Lsys_fair1done_out) && (_l.Ln29)) && !(!((_l.Ii_StoB_REQ1) && !(_l.Icontrollable_BtoS_ACK1)) && !(!(_l.Ii_StoB_REQ1) && (_l.Icontrollable_BtoS_ACK1)))) && !(!(!((_l.Ii_StoB_REQ0) && !(_l.Icontrollable_BtoS_ACK0)) && !(!(_l.Ii_StoB_REQ0) && (_l.Icontrollable_BtoS_ACK0))) && !((_l.Lsys_fair0done_out) && (_l.Ln29))))) && !(!(!((_l.Ii_StoB_REQ0) && !(_l.Icontrollable_BtoS_ACK0)) && !(!(_l.Ii_StoB_REQ0) && (_l.Icontrollable_BtoS_ACK0))) && !((_l.Lsys_fair0done_out) && (_l.Ln29))));;\
                    }
                    );
s.add_location("Circuit", "UpdatedLreg_controllable_BtoS_ACK0_out", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "UpdatedLsys_fair0done_out", "UpdatedLreg_controllable_BtoS_ACK0_out", "", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lreg_controllable_BtoS_ACK0_out==(_l.Icontrollable_BtoS_ACK0);;\
        }
        );
s.add_edge("Circuit", "UpdatedLsys_fair0done_out", "UpdatedLreg_controllable_BtoS_ACK0_out", "x_38 <= 4000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lreg_controllable_BtoS_ACK0_out == 1 && _l.Lreg_controllable_BtoS_ACK0_out != (_l.Icontrollable_BtoS_ACK0);\
        }
        );
s.add_edge("Circuit", "UpdatedLsys_fair0done_out", "UpdatedLreg_controllable_BtoS_ACK0_out", "x_38 <= 2000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lreg_controllable_BtoS_ACK0_out == 0 && _l.Lreg_controllable_BtoS_ACK0_out != (_l.Icontrollable_BtoS_ACK0);\
        }
        );
s.add_location("Circuit", "UpdatedLreg_controllable_BtoS_ACK0_out_becomes0","x_38<=4000", "");
s.add_location("Circuit", "UpdatedLreg_controllable_BtoS_ACK0_out_becomes1","x_38<=2000", "");
s.add_edge("Circuit", "UpdatedLsys_fair0done_out", "UpdatedLreg_controllable_BtoS_ACK0_out_becomes0", "x_38 < 4000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lreg_controllable_BtoS_ACK0_out == 1 && _l.Lreg_controllable_BtoS_ACK0_out != (_l.Icontrollable_BtoS_ACK0);\
        }
        );
s.add_edge("Circuit", "UpdatedLreg_controllable_BtoS_ACK0_out_becomes0", "UpdatedLreg_controllable_BtoS_ACK0_out", "x_38 >= 4000", "x_38", "", syntax::layout_true,  [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Lreg_controllable_BtoS_ACK0_out = (_l.Icontrollable_BtoS_ACK0);;\
                    }
                    );
s.add_edge("Circuit", "UpdatedLsys_fair0done_out", "UpdatedLreg_controllable_BtoS_ACK0_out_becomes1", "x_38 < 2000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lreg_controllable_BtoS_ACK0_out == 0 && _l.Lreg_controllable_BtoS_ACK0_out != (_l.Icontrollable_BtoS_ACK0);\
        }
        );
s.add_edge("Circuit", "UpdatedLreg_controllable_BtoS_ACK0_out_becomes1", "UpdatedLreg_controllable_BtoS_ACK0_out", "x_38 >= 2000", "x_38", "", syntax::layout_true,  [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Lreg_controllable_BtoS_ACK0_out = (_l.Icontrollable_BtoS_ACK0);;\
                    }
                    );
s.add_location("Circuit", "UpdatedLenv_fair1done_out", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "UpdatedLreg_controllable_BtoS_ACK0_out", "UpdatedLenv_fair1done_out", "", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lenv_fair1done_out==((!(!(!((_l.Lenv_fair0done_out) && (_l.Ln29)) && !(!(!(_l.Ii_RtoB_ACK0) && (_l.Icontrollable_BtoR_REQ0)) && !((_l.Ii_RtoB_ACK0) && !(_l.Icontrollable_BtoR_REQ0)))) && !(!((_l.Lenv_fair1done_out) && (_l.Ln29)) && !(!((_l.Icontrollable_BtoR_REQ1) && !(_l.Ii_RtoB_ACK1)) && !(!(_l.Icontrollable_BtoR_REQ1) && (_l.Ii_RtoB_ACK1))))) && ((!(!((_l.Lsys_fair2done_out) && (_l.Ln29)) && !((_l.Lreg_stateG12_out) && (_l.Ln29))) && (!(!((_l.Lsys_fair1done_out) && (_l.Ln29)) && (!((_l.Ii_StoB_REQ1) && !(_l.Icontrollable_BtoS_ACK1)) && !(!(_l.Ii_StoB_REQ1) && (_l.Icontrollable_BtoS_ACK1)))) && !((!((_l.Ii_StoB_REQ0) && !(_l.Icontrollable_BtoS_ACK0)) && !(!(_l.Ii_StoB_REQ0) && (_l.Icontrollable_BtoS_ACK0))) && !((_l.Lsys_fair0done_out) && (_l.Ln29))))) && !(!(!((_l.Lsys_fair2done_out) && (_l.Ln29)) && ((_l.Lreg_stateG12_out) && (_l.Ln29))) && (!(!((_l.Lsys_fair1done_out) && (_l.Ln29)) && !(!((_l.Ii_StoB_REQ1) && !(_l.Icontrollable_BtoS_ACK1)) && !(!(_l.Ii_StoB_REQ1) && (_l.Icontrollable_BtoS_ACK1)))) && !(!(!((_l.Ii_StoB_REQ0) && !(_l.Icontrollable_BtoS_ACK0)) && !(!(_l.Ii_StoB_REQ0) && (_l.Icontrollable_BtoS_ACK0))) && !((_l.Lsys_fair0done_out) && (_l.Ln29))))))) && !(!((_l.Lenv_fair1done_out) && (_l.Ln29)) && !(!((_l.Icontrollable_BtoR_REQ1) && !(_l.Ii_RtoB_ACK1)) && !(!(_l.Icontrollable_BtoR_REQ1) && (_l.Ii_RtoB_ACK1)))));;\
        }
        );
s.add_edge("Circuit", "UpdatedLreg_controllable_BtoS_ACK0_out", "UpdatedLenv_fair1done_out", "x_40 <= 1000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lenv_fair1done_out == 1 && _l.Lenv_fair1done_out != ((!(!(!((_l.Lenv_fair0done_out) && (_l.Ln29)) && !(!(!(_l.Ii_RtoB_ACK0) && (_l.Icontrollable_BtoR_REQ0)) && !((_l.Ii_RtoB_ACK0) && !(_l.Icontrollable_BtoR_REQ0)))) && !(!((_l.Lenv_fair1done_out) && (_l.Ln29)) && !(!((_l.Icontrollable_BtoR_REQ1) && !(_l.Ii_RtoB_ACK1)) && !(!(_l.Icontrollable_BtoR_REQ1) && (_l.Ii_RtoB_ACK1))))) && ((!(!((_l.Lsys_fair2done_out) && (_l.Ln29)) && !((_l.Lreg_stateG12_out) && (_l.Ln29))) && (!(!((_l.Lsys_fair1done_out) && (_l.Ln29)) && (!((_l.Ii_StoB_REQ1) && !(_l.Icontrollable_BtoS_ACK1)) && !(!(_l.Ii_StoB_REQ1) && (_l.Icontrollable_BtoS_ACK1)))) && !((!((_l.Ii_StoB_REQ0) && !(_l.Icontrollable_BtoS_ACK0)) && !(!(_l.Ii_StoB_REQ0) && (_l.Icontrollable_BtoS_ACK0))) && !((_l.Lsys_fair0done_out) && (_l.Ln29))))) && !(!(!((_l.Lsys_fair2done_out) && (_l.Ln29)) && ((_l.Lreg_stateG12_out) && (_l.Ln29))) && (!(!((_l.Lsys_fair1done_out) && (_l.Ln29)) && !(!((_l.Ii_StoB_REQ1) && !(_l.Icontrollable_BtoS_ACK1)) && !(!(_l.Ii_StoB_REQ1) && (_l.Icontrollable_BtoS_ACK1)))) && !(!(!((_l.Ii_StoB_REQ0) && !(_l.Icontrollable_BtoS_ACK0)) && !(!(_l.Ii_StoB_REQ0) && (_l.Icontrollable_BtoS_ACK0))) && !((_l.Lsys_fair0done_out) && (_l.Ln29))))))) && !(!((_l.Lenv_fair1done_out) && (_l.Ln29)) && !(!((_l.Icontrollable_BtoR_REQ1) && !(_l.Ii_RtoB_ACK1)) && !(!(_l.Icontrollable_BtoR_REQ1) && (_l.Ii_RtoB_ACK1)))));\
        }
        );
s.add_edge("Circuit", "UpdatedLreg_controllable_BtoS_ACK0_out", "UpdatedLenv_fair1done_out", "x_40 <= 500", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lenv_fair1done_out == 0 && _l.Lenv_fair1done_out != ((!(!(!((_l.Lenv_fair0done_out) && (_l.Ln29)) && !(!(!(_l.Ii_RtoB_ACK0) && (_l.Icontrollable_BtoR_REQ0)) && !((_l.Ii_RtoB_ACK0) && !(_l.Icontrollable_BtoR_REQ0)))) && !(!((_l.Lenv_fair1done_out) && (_l.Ln29)) && !(!((_l.Icontrollable_BtoR_REQ1) && !(_l.Ii_RtoB_ACK1)) && !(!(_l.Icontrollable_BtoR_REQ1) && (_l.Ii_RtoB_ACK1))))) && ((!(!((_l.Lsys_fair2done_out) && (_l.Ln29)) && !((_l.Lreg_stateG12_out) && (_l.Ln29))) && (!(!((_l.Lsys_fair1done_out) && (_l.Ln29)) && (!((_l.Ii_StoB_REQ1) && !(_l.Icontrollable_BtoS_ACK1)) && !(!(_l.Ii_StoB_REQ1) && (_l.Icontrollable_BtoS_ACK1)))) && !((!((_l.Ii_StoB_REQ0) && !(_l.Icontrollable_BtoS_ACK0)) && !(!(_l.Ii_StoB_REQ0) && (_l.Icontrollable_BtoS_ACK0))) && !((_l.Lsys_fair0done_out) && (_l.Ln29))))) && !(!(!((_l.Lsys_fair2done_out) && (_l.Ln29)) && ((_l.Lreg_stateG12_out) && (_l.Ln29))) && (!(!((_l.Lsys_fair1done_out) && (_l.Ln29)) && !(!((_l.Ii_StoB_REQ1) && !(_l.Icontrollable_BtoS_ACK1)) && !(!(_l.Ii_StoB_REQ1) && (_l.Icontrollable_BtoS_ACK1)))) && !(!(!((_l.Ii_StoB_REQ0) && !(_l.Icontrollable_BtoS_ACK0)) && !(!(_l.Ii_StoB_REQ0) && (_l.Icontrollable_BtoS_ACK0))) && !((_l.Lsys_fair0done_out) && (_l.Ln29))))))) && !(!((_l.Lenv_fair1done_out) && (_l.Ln29)) && !(!((_l.Icontrollable_BtoR_REQ1) && !(_l.Ii_RtoB_ACK1)) && !(!(_l.Icontrollable_BtoR_REQ1) && (_l.Ii_RtoB_ACK1)))));\
        }
        );
s.add_location("Circuit", "UpdatedLenv_fair1done_out_becomes0","x_40<=1000", "");
s.add_location("Circuit", "UpdatedLenv_fair1done_out_becomes1","x_40<=500", "");
s.add_edge("Circuit", "UpdatedLreg_controllable_BtoS_ACK0_out", "UpdatedLenv_fair1done_out_becomes0", "x_40 < 1000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lenv_fair1done_out == 1 && _l.Lenv_fair1done_out != ((!(!(!((_l.Lenv_fair0done_out) && (_l.Ln29)) && !(!(!(_l.Ii_RtoB_ACK0) && (_l.Icontrollable_BtoR_REQ0)) && !((_l.Ii_RtoB_ACK0) && !(_l.Icontrollable_BtoR_REQ0)))) && !(!((_l.Lenv_fair1done_out) && (_l.Ln29)) && !(!((_l.Icontrollable_BtoR_REQ1) && !(_l.Ii_RtoB_ACK1)) && !(!(_l.Icontrollable_BtoR_REQ1) && (_l.Ii_RtoB_ACK1))))) && ((!(!((_l.Lsys_fair2done_out) && (_l.Ln29)) && !((_l.Lreg_stateG12_out) && (_l.Ln29))) && (!(!((_l.Lsys_fair1done_out) && (_l.Ln29)) && (!((_l.Ii_StoB_REQ1) && !(_l.Icontrollable_BtoS_ACK1)) && !(!(_l.Ii_StoB_REQ1) && (_l.Icontrollable_BtoS_ACK1)))) && !((!((_l.Ii_StoB_REQ0) && !(_l.Icontrollable_BtoS_ACK0)) && !(!(_l.Ii_StoB_REQ0) && (_l.Icontrollable_BtoS_ACK0))) && !((_l.Lsys_fair0done_out) && (_l.Ln29))))) && !(!(!((_l.Lsys_fair2done_out) && (_l.Ln29)) && ((_l.Lreg_stateG12_out) && (_l.Ln29))) && (!(!((_l.Lsys_fair1done_out) && (_l.Ln29)) && !(!((_l.Ii_StoB_REQ1) && !(_l.Icontrollable_BtoS_ACK1)) && !(!(_l.Ii_StoB_REQ1) && (_l.Icontrollable_BtoS_ACK1)))) && !(!(!((_l.Ii_StoB_REQ0) && !(_l.Icontrollable_BtoS_ACK0)) && !(!(_l.Ii_StoB_REQ0) && (_l.Icontrollable_BtoS_ACK0))) && !((_l.Lsys_fair0done_out) && (_l.Ln29))))))) && !(!((_l.Lenv_fair1done_out) && (_l.Ln29)) && !(!((_l.Icontrollable_BtoR_REQ1) && !(_l.Ii_RtoB_ACK1)) && !(!(_l.Icontrollable_BtoR_REQ1) && (_l.Ii_RtoB_ACK1)))));\
        }
        );
s.add_edge("Circuit", "UpdatedLenv_fair1done_out_becomes0", "UpdatedLenv_fair1done_out", "x_40 >= 1000", "x_40", "", syntax::layout_true,  [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Lenv_fair1done_out = ((!(!(!((_l.Lenv_fair0done_out) && (_l.Ln29)) && !(!(!(_l.Ii_RtoB_ACK0) && (_l.Icontrollable_BtoR_REQ0)) && !((_l.Ii_RtoB_ACK0) && !(_l.Icontrollable_BtoR_REQ0)))) && !(!((_l.Lenv_fair1done_out) && (_l.Ln29)) && !(!((_l.Icontrollable_BtoR_REQ1) && !(_l.Ii_RtoB_ACK1)) && !(!(_l.Icontrollable_BtoR_REQ1) && (_l.Ii_RtoB_ACK1))))) && ((!(!((_l.Lsys_fair2done_out) && (_l.Ln29)) && !((_l.Lreg_stateG12_out) && (_l.Ln29))) && (!(!((_l.Lsys_fair1done_out) && (_l.Ln29)) && (!((_l.Ii_StoB_REQ1) && !(_l.Icontrollable_BtoS_ACK1)) && !(!(_l.Ii_StoB_REQ1) && (_l.Icontrollable_BtoS_ACK1)))) && !((!((_l.Ii_StoB_REQ0) && !(_l.Icontrollable_BtoS_ACK0)) && !(!(_l.Ii_StoB_REQ0) && (_l.Icontrollable_BtoS_ACK0))) && !((_l.Lsys_fair0done_out) && (_l.Ln29))))) && !(!(!((_l.Lsys_fair2done_out) && (_l.Ln29)) && ((_l.Lreg_stateG12_out) && (_l.Ln29))) && (!(!((_l.Lsys_fair1done_out) && (_l.Ln29)) && !(!((_l.Ii_StoB_REQ1) && !(_l.Icontrollable_BtoS_ACK1)) && !(!(_l.Ii_StoB_REQ1) && (_l.Icontrollable_BtoS_ACK1)))) && !(!(!((_l.Ii_StoB_REQ0) && !(_l.Icontrollable_BtoS_ACK0)) && !(!(_l.Ii_StoB_REQ0) && (_l.Icontrollable_BtoS_ACK0))) && !((_l.Lsys_fair0done_out) && (_l.Ln29))))))) && !(!((_l.Lenv_fair1done_out) && (_l.Ln29)) && !(!((_l.Icontrollable_BtoR_REQ1) && !(_l.Ii_RtoB_ACK1)) && !(!(_l.Icontrollable_BtoR_REQ1) && (_l.Ii_RtoB_ACK1)))));;\
                    }
                    );
s.add_edge("Circuit", "UpdatedLreg_controllable_BtoS_ACK0_out", "UpdatedLenv_fair1done_out_becomes1", "x_40 < 500", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lenv_fair1done_out == 0 && _l.Lenv_fair1done_out != ((!(!(!((_l.Lenv_fair0done_out) && (_l.Ln29)) && !(!(!(_l.Ii_RtoB_ACK0) && (_l.Icontrollable_BtoR_REQ0)) && !((_l.Ii_RtoB_ACK0) && !(_l.Icontrollable_BtoR_REQ0)))) && !(!((_l.Lenv_fair1done_out) && (_l.Ln29)) && !(!((_l.Icontrollable_BtoR_REQ1) && !(_l.Ii_RtoB_ACK1)) && !(!(_l.Icontrollable_BtoR_REQ1) && (_l.Ii_RtoB_ACK1))))) && ((!(!((_l.Lsys_fair2done_out) && (_l.Ln29)) && !((_l.Lreg_stateG12_out) && (_l.Ln29))) && (!(!((_l.Lsys_fair1done_out) && (_l.Ln29)) && (!((_l.Ii_StoB_REQ1) && !(_l.Icontrollable_BtoS_ACK1)) && !(!(_l.Ii_StoB_REQ1) && (_l.Icontrollable_BtoS_ACK1)))) && !((!((_l.Ii_StoB_REQ0) && !(_l.Icontrollable_BtoS_ACK0)) && !(!(_l.Ii_StoB_REQ0) && (_l.Icontrollable_BtoS_ACK0))) && !((_l.Lsys_fair0done_out) && (_l.Ln29))))) && !(!(!((_l.Lsys_fair2done_out) && (_l.Ln29)) && ((_l.Lreg_stateG12_out) && (_l.Ln29))) && (!(!((_l.Lsys_fair1done_out) && (_l.Ln29)) && !(!((_l.Ii_StoB_REQ1) && !(_l.Icontrollable_BtoS_ACK1)) && !(!(_l.Ii_StoB_REQ1) && (_l.Icontrollable_BtoS_ACK1)))) && !(!(!((_l.Ii_StoB_REQ0) && !(_l.Icontrollable_BtoS_ACK0)) && !(!(_l.Ii_StoB_REQ0) && (_l.Icontrollable_BtoS_ACK0))) && !((_l.Lsys_fair0done_out) && (_l.Ln29))))))) && !(!((_l.Lenv_fair1done_out) && (_l.Ln29)) && !(!((_l.Icontrollable_BtoR_REQ1) && !(_l.Ii_RtoB_ACK1)) && !(!(_l.Icontrollable_BtoR_REQ1) && (_l.Ii_RtoB_ACK1)))));\
        }
        );
s.add_edge("Circuit", "UpdatedLenv_fair1done_out_becomes1", "UpdatedLenv_fair1done_out", "x_40 >= 500", "x_40", "", syntax::layout_true,  [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Lenv_fair1done_out = ((!(!(!((_l.Lenv_fair0done_out) && (_l.Ln29)) && !(!(!(_l.Ii_RtoB_ACK0) && (_l.Icontrollable_BtoR_REQ0)) && !((_l.Ii_RtoB_ACK0) && !(_l.Icontrollable_BtoR_REQ0)))) && !(!((_l.Lenv_fair1done_out) && (_l.Ln29)) && !(!((_l.Icontrollable_BtoR_REQ1) && !(_l.Ii_RtoB_ACK1)) && !(!(_l.Icontrollable_BtoR_REQ1) && (_l.Ii_RtoB_ACK1))))) && ((!(!((_l.Lsys_fair2done_out) && (_l.Ln29)) && !((_l.Lreg_stateG12_out) && (_l.Ln29))) && (!(!((_l.Lsys_fair1done_out) && (_l.Ln29)) && (!((_l.Ii_StoB_REQ1) && !(_l.Icontrollable_BtoS_ACK1)) && !(!(_l.Ii_StoB_REQ1) && (_l.Icontrollable_BtoS_ACK1)))) && !((!((_l.Ii_StoB_REQ0) && !(_l.Icontrollable_BtoS_ACK0)) && !(!(_l.Ii_StoB_REQ0) && (_l.Icontrollable_BtoS_ACK0))) && !((_l.Lsys_fair0done_out) && (_l.Ln29))))) && !(!(!((_l.Lsys_fair2done_out) && (_l.Ln29)) && ((_l.Lreg_stateG12_out) && (_l.Ln29))) && (!(!((_l.Lsys_fair1done_out) && (_l.Ln29)) && !(!((_l.Ii_StoB_REQ1) && !(_l.Icontrollable_BtoS_ACK1)) && !(!(_l.Ii_StoB_REQ1) && (_l.Icontrollable_BtoS_ACK1)))) && !(!(!((_l.Ii_StoB_REQ0) && !(_l.Icontrollable_BtoS_ACK0)) && !(!(_l.Ii_StoB_REQ0) && (_l.Icontrollable_BtoS_ACK0))) && !((_l.Lsys_fair0done_out) && (_l.Ln29))))))) && !(!((_l.Lenv_fair1done_out) && (_l.Ln29)) && !(!((_l.Icontrollable_BtoR_REQ1) && !(_l.Ii_RtoB_ACK1)) && !(!(_l.Icontrollable_BtoR_REQ1) && (_l.Ii_RtoB_ACK1)))));;\
                    }
                    );
s.add_location("Circuit", "UpdatedLreg_i_nEMPTY_out", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "UpdatedLenv_fair1done_out", "UpdatedLreg_i_nEMPTY_out", "", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lreg_i_nEMPTY_out==(_l.Ii_nEMPTY);;\
        }
        );
s.add_edge("Circuit", "UpdatedLenv_fair1done_out", "UpdatedLreg_i_nEMPTY_out", "x_42 <= 1000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lreg_i_nEMPTY_out == 1 && _l.Lreg_i_nEMPTY_out != (_l.Ii_nEMPTY);\
        }
        );
s.add_edge("Circuit", "UpdatedLenv_fair1done_out", "UpdatedLreg_i_nEMPTY_out", "x_42 <= 500", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lreg_i_nEMPTY_out == 0 && _l.Lreg_i_nEMPTY_out != (_l.Ii_nEMPTY);\
        }
        );
s.add_location("Circuit", "UpdatedLreg_i_nEMPTY_out_becomes0","x_42<=1000", "");
s.add_location("Circuit", "UpdatedLreg_i_nEMPTY_out_becomes1","x_42<=500", "");
s.add_edge("Circuit", "UpdatedLenv_fair1done_out", "UpdatedLreg_i_nEMPTY_out_becomes0", "x_42 < 1000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lreg_i_nEMPTY_out == 1 && _l.Lreg_i_nEMPTY_out != (_l.Ii_nEMPTY);\
        }
        );
s.add_edge("Circuit", "UpdatedLreg_i_nEMPTY_out_becomes0", "UpdatedLreg_i_nEMPTY_out", "x_42 >= 1000", "x_42", "", syntax::layout_true,  [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Lreg_i_nEMPTY_out = (_l.Ii_nEMPTY);;\
                    }
                    );
s.add_edge("Circuit", "UpdatedLenv_fair1done_out", "UpdatedLreg_i_nEMPTY_out_becomes1", "x_42 < 500", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lreg_i_nEMPTY_out == 0 && _l.Lreg_i_nEMPTY_out != (_l.Ii_nEMPTY);\
        }
        );
s.add_edge("Circuit", "UpdatedLreg_i_nEMPTY_out_becomes1", "UpdatedLreg_i_nEMPTY_out", "x_42 >= 500", "x_42", "", syntax::layout_true,  [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Lreg_i_nEMPTY_out = (_l.Ii_nEMPTY);;\
                    }
                    );
s.add_location("Circuit", "UpdatedLreg_nstateG7_1_out", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "UpdatedLreg_i_nEMPTY_out", "UpdatedLreg_nstateG7_1_out", "", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lreg_nstateG7_1_out==!(!(((_l.Lreg_nstateG7_1_out) && (_l.Ln29)) && ((_l.Lreg_controllable_BtoR_REQ0_out) && (_l.Ln29))) && !(!(!(!((_l.Lreg_nstateG7_1_out) && (_l.Ln29)) && ((_l.Lreg_controllable_BtoR_REQ0_out) && (_l.Ln29))) && !(((_l.Lreg_nstateG7_1_out) && (_l.Ln29)) && !((_l.Lreg_controllable_BtoR_REQ0_out) && (_l.Ln29)))) && !((_l.Lreg_controllable_BtoR_REQ1_out) && (_l.Ln29))));;\
        }
        );
s.add_edge("Circuit", "UpdatedLreg_i_nEMPTY_out", "UpdatedLreg_nstateG7_1_out", "x_44 <= 2000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lreg_nstateG7_1_out == 1 && _l.Lreg_nstateG7_1_out != !(!(((_l.Lreg_nstateG7_1_out) && (_l.Ln29)) && ((_l.Lreg_controllable_BtoR_REQ0_out) && (_l.Ln29))) && !(!(!(!((_l.Lreg_nstateG7_1_out) && (_l.Ln29)) && ((_l.Lreg_controllable_BtoR_REQ0_out) && (_l.Ln29))) && !(((_l.Lreg_nstateG7_1_out) && (_l.Ln29)) && !((_l.Lreg_controllable_BtoR_REQ0_out) && (_l.Ln29)))) && !((_l.Lreg_controllable_BtoR_REQ1_out) && (_l.Ln29))));\
        }
        );
s.add_edge("Circuit", "UpdatedLreg_i_nEMPTY_out", "UpdatedLreg_nstateG7_1_out", "x_44 <= 1500", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lreg_nstateG7_1_out == 0 && _l.Lreg_nstateG7_1_out != !(!(((_l.Lreg_nstateG7_1_out) && (_l.Ln29)) && ((_l.Lreg_controllable_BtoR_REQ0_out) && (_l.Ln29))) && !(!(!(!((_l.Lreg_nstateG7_1_out) && (_l.Ln29)) && ((_l.Lreg_controllable_BtoR_REQ0_out) && (_l.Ln29))) && !(((_l.Lreg_nstateG7_1_out) && (_l.Ln29)) && !((_l.Lreg_controllable_BtoR_REQ0_out) && (_l.Ln29)))) && !((_l.Lreg_controllable_BtoR_REQ1_out) && (_l.Ln29))));\
        }
        );
s.add_location("Circuit", "UpdatedLreg_nstateG7_1_out_becomes0","x_44<=2000", "");
s.add_location("Circuit", "UpdatedLreg_nstateG7_1_out_becomes1","x_44<=1500", "");
s.add_edge("Circuit", "UpdatedLreg_i_nEMPTY_out", "UpdatedLreg_nstateG7_1_out_becomes0", "x_44 < 2000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lreg_nstateG7_1_out == 1 && _l.Lreg_nstateG7_1_out != !(!(((_l.Lreg_nstateG7_1_out) && (_l.Ln29)) && ((_l.Lreg_controllable_BtoR_REQ0_out) && (_l.Ln29))) && !(!(!(!((_l.Lreg_nstateG7_1_out) && (_l.Ln29)) && ((_l.Lreg_controllable_BtoR_REQ0_out) && (_l.Ln29))) && !(((_l.Lreg_nstateG7_1_out) && (_l.Ln29)) && !((_l.Lreg_controllable_BtoR_REQ0_out) && (_l.Ln29)))) && !((_l.Lreg_controllable_BtoR_REQ1_out) && (_l.Ln29))));\
        }
        );
s.add_edge("Circuit", "UpdatedLreg_nstateG7_1_out_becomes0", "UpdatedLreg_nstateG7_1_out", "x_44 >= 2000", "x_44", "", syntax::layout_true,  [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Lreg_nstateG7_1_out = !(!(((_l.Lreg_nstateG7_1_out) && (_l.Ln29)) && ((_l.Lreg_controllable_BtoR_REQ0_out) && (_l.Ln29))) && !(!(!(!((_l.Lreg_nstateG7_1_out) && (_l.Ln29)) && ((_l.Lreg_controllable_BtoR_REQ0_out) && (_l.Ln29))) && !(((_l.Lreg_nstateG7_1_out) && (_l.Ln29)) && !((_l.Lreg_controllable_BtoR_REQ0_out) && (_l.Ln29)))) && !((_l.Lreg_controllable_BtoR_REQ1_out) && (_l.Ln29))));;\
                    }
                    );
s.add_edge("Circuit", "UpdatedLreg_i_nEMPTY_out", "UpdatedLreg_nstateG7_1_out_becomes1", "x_44 < 1500", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lreg_nstateG7_1_out == 0 && _l.Lreg_nstateG7_1_out != !(!(((_l.Lreg_nstateG7_1_out) && (_l.Ln29)) && ((_l.Lreg_controllable_BtoR_REQ0_out) && (_l.Ln29))) && !(!(!(!((_l.Lreg_nstateG7_1_out) && (_l.Ln29)) && ((_l.Lreg_controllable_BtoR_REQ0_out) && (_l.Ln29))) && !(((_l.Lreg_nstateG7_1_out) && (_l.Ln29)) && !((_l.Lreg_controllable_BtoR_REQ0_out) && (_l.Ln29)))) && !((_l.Lreg_controllable_BtoR_REQ1_out) && (_l.Ln29))));\
        }
        );
s.add_edge("Circuit", "UpdatedLreg_nstateG7_1_out_becomes1", "UpdatedLreg_nstateG7_1_out", "x_44 >= 1500", "x_44", "", syntax::layout_true,  [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Lreg_nstateG7_1_out = !(!(((_l.Lreg_nstateG7_1_out) && (_l.Ln29)) && ((_l.Lreg_controllable_BtoR_REQ0_out) && (_l.Ln29))) && !(!(!(!((_l.Lreg_nstateG7_1_out) && (_l.Ln29)) && ((_l.Lreg_controllable_BtoR_REQ0_out) && (_l.Ln29))) && !(((_l.Lreg_nstateG7_1_out) && (_l.Ln29)) && !((_l.Lreg_controllable_BtoR_REQ0_out) && (_l.Ln29)))) && !((_l.Lreg_controllable_BtoR_REQ1_out) && (_l.Ln29))));;\
                    }
                    );
s.add_edge("Circuit", "UpdatedLreg_nstateG7_1_out", "dead", "T>4000", "", "", syntax::layout_true);
s.add_edge("Circuit", "UpdatedLreg_nstateG7_1_out", "init", "T<=4000", "T", "", syntax::layout_true);
s.synchronizer<syntax::asynchronous_product_t>();
}
