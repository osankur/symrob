#include <iostream>
        #include "syntax/system.hh"
        #include "syntax/sync_product.hh"
        namespace monoprocess {
        class layout_t : public syntax::layout_t {
        public:
        
	bool Ip0_0;
	bool Ip0_1;
	bool Ip0_2;
	bool Ip1_0;
	bool Ip1_1;
	bool Ip1_2;
	bool Ip2_0;
	bool Ip2_1;
	bool Ip2_2;
	bool IerrorCount_0_0_1;
	bool Icontrollable_arm1_0_0_2;
	bool Icontrollable_arm1_1;
	bool Icontrollable_arm2_0_0_2;
	bool Icontrollable_arm2_1;
	bool Icontrollable_arm1op_0_0_2;
	bool Icontrollable_arm1op_1;
	bool Icontrollable_arm2op_0_0_2;
	bool Icontrollable_arm2op_1;
	bool LIsNotFirstRound;
	bool Lprev_p0_0;
	bool Lprev_p0_1;
	bool Lprev_p0_2;
	bool Lprev_p1_0;
	bool Lprev_p1_1;
	bool Lprev_p1_2;
	bool Lprev_p2_0;
	bool Lprev_p2_1;
	bool Lprev_p2_2;
	bool Lprev_errorCount_0_0_1;
	bool Lprev_arm1_0_0_2;
	bool Lprev_arm1_1;
	bool Lprev_arm2_0_0_2;
	bool Lprev_arm2_1;
	bool Lprev_arm1op_0_0_2;
	bool Lprev_arm1op_1;
	bool Lprev_arm2op_0_0_2;
	bool Lprev_arm2op_1;
	bool LAssumptionsAlreadyViolated;
	layout_t(){
		Ip0_0 = 0;
		Ip0_1 = 0;
		Ip0_2 = 0;
		Ip1_0 = 0;
		Ip1_1 = 0;
		Ip1_2 = 0;
		Ip2_0 = 0;
		Ip2_1 = 0;
		Ip2_2 = 0;
		IerrorCount_0_0_1 = 0;
		Icontrollable_arm1_0_0_2 = 0;
		Icontrollable_arm1_1 = 0;
		Icontrollable_arm2_0_0_2 = 0;
		Icontrollable_arm2_1 = 0;
		Icontrollable_arm1op_0_0_2 = 0;
		Icontrollable_arm1op_1 = 0;
		Icontrollable_arm2op_0_0_2 = 0;
		Icontrollable_arm2op_1 = 0;
		LIsNotFirstRound = 0;
		Lprev_p0_0 = 0;
		Lprev_p0_1 = 0;
		Lprev_p0_2 = 0;
		Lprev_p1_0 = 0;
		Lprev_p1_1 = 0;
		Lprev_p1_2 = 0;
		Lprev_p2_0 = 0;
		Lprev_p2_1 = 0;
		Lprev_p2_2 = 0;
		Lprev_errorCount_0_0_1 = 0;
		Lprev_arm1_0_0_2 = 0;
		Lprev_arm1_1 = 0;
		Lprev_arm2_0_0_2 = 0;
		Lprev_arm2_1 = 0;
		Lprev_arm1op_0_0_2 = 0;
		Lprev_arm1op_1 = 0;
		Lprev_arm2op_0_0_2 = 0;
		Lprev_arm2op_1 = 0;
		LAssumptionsAlreadyViolated = 0;
	}
virtual ~layout_t(){}
layout_t (const layout_t &l) = default;

        inline bool operator == (const syntax::layout_t & l) const {
            monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);
        
		if(Ip0_0 != _l.Ip0_0) return false;
		if(Ip0_1 != _l.Ip0_1) return false;
		if(Ip0_2 != _l.Ip0_2) return false;
		if(Ip1_0 != _l.Ip1_0) return false;
		if(Ip1_1 != _l.Ip1_1) return false;
		if(Ip1_2 != _l.Ip1_2) return false;
		if(Ip2_0 != _l.Ip2_0) return false;
		if(Ip2_1 != _l.Ip2_1) return false;
		if(Ip2_2 != _l.Ip2_2) return false;
		if(IerrorCount_0_0_1 != _l.IerrorCount_0_0_1) return false;
		if(Icontrollable_arm1_0_0_2 != _l.Icontrollable_arm1_0_0_2) return false;
		if(Icontrollable_arm1_1 != _l.Icontrollable_arm1_1) return false;
		if(Icontrollable_arm2_0_0_2 != _l.Icontrollable_arm2_0_0_2) return false;
		if(Icontrollable_arm2_1 != _l.Icontrollable_arm2_1) return false;
		if(Icontrollable_arm1op_0_0_2 != _l.Icontrollable_arm1op_0_0_2) return false;
		if(Icontrollable_arm1op_1 != _l.Icontrollable_arm1op_1) return false;
		if(Icontrollable_arm2op_0_0_2 != _l.Icontrollable_arm2op_0_0_2) return false;
		if(Icontrollable_arm2op_1 != _l.Icontrollable_arm2op_1) return false;
		if(LIsNotFirstRound != _l.LIsNotFirstRound) return false;
		if(Lprev_p0_0 != _l.Lprev_p0_0) return false;
		if(Lprev_p0_1 != _l.Lprev_p0_1) return false;
		if(Lprev_p0_2 != _l.Lprev_p0_2) return false;
		if(Lprev_p1_0 != _l.Lprev_p1_0) return false;
		if(Lprev_p1_1 != _l.Lprev_p1_1) return false;
		if(Lprev_p1_2 != _l.Lprev_p1_2) return false;
		if(Lprev_p2_0 != _l.Lprev_p2_0) return false;
		if(Lprev_p2_1 != _l.Lprev_p2_1) return false;
		if(Lprev_p2_2 != _l.Lprev_p2_2) return false;
		if(Lprev_errorCount_0_0_1 != _l.Lprev_errorCount_0_0_1) return false;
		if(Lprev_arm1_0_0_2 != _l.Lprev_arm1_0_0_2) return false;
		if(Lprev_arm1_1 != _l.Lprev_arm1_1) return false;
		if(Lprev_arm2_0_0_2 != _l.Lprev_arm2_0_0_2) return false;
		if(Lprev_arm2_1 != _l.Lprev_arm2_1) return false;
		if(Lprev_arm1op_0_0_2 != _l.Lprev_arm1op_0_0_2) return false;
		if(Lprev_arm1op_1 != _l.Lprev_arm1op_1) return false;
		if(Lprev_arm2op_0_0_2 != _l.Lprev_arm2op_0_0_2) return false;
		if(Lprev_arm2op_1 != _l.Lprev_arm2op_1) return false;
		if(LAssumptionsAlreadyViolated != _l.LAssumptionsAlreadyViolated) return false;
return true;
}

        inline size_t hash() const {
        size_t seed = global_t::instance().hash_seed();
        
		boost::hash_combine(seed, Ip0_0);
		boost::hash_combine(seed, Ip0_1);
		boost::hash_combine(seed, Ip0_2);
		boost::hash_combine(seed, Ip1_0);
		boost::hash_combine(seed, Ip1_1);
		boost::hash_combine(seed, Ip1_2);
		boost::hash_combine(seed, Ip2_0);
		boost::hash_combine(seed, Ip2_1);
		boost::hash_combine(seed, Ip2_2);
		boost::hash_combine(seed, IerrorCount_0_0_1);
		boost::hash_combine(seed, Icontrollable_arm1_0_0_2);
		boost::hash_combine(seed, Icontrollable_arm1_1);
		boost::hash_combine(seed, Icontrollable_arm2_0_0_2);
		boost::hash_combine(seed, Icontrollable_arm2_1);
		boost::hash_combine(seed, Icontrollable_arm1op_0_0_2);
		boost::hash_combine(seed, Icontrollable_arm1op_1);
		boost::hash_combine(seed, Icontrollable_arm2op_0_0_2);
		boost::hash_combine(seed, Icontrollable_arm2op_1);
		boost::hash_combine(seed, LIsNotFirstRound);
		boost::hash_combine(seed, Lprev_p0_0);
		boost::hash_combine(seed, Lprev_p0_1);
		boost::hash_combine(seed, Lprev_p0_2);
		boost::hash_combine(seed, Lprev_p1_0);
		boost::hash_combine(seed, Lprev_p1_1);
		boost::hash_combine(seed, Lprev_p1_2);
		boost::hash_combine(seed, Lprev_p2_0);
		boost::hash_combine(seed, Lprev_p2_1);
		boost::hash_combine(seed, Lprev_p2_2);
		boost::hash_combine(seed, Lprev_errorCount_0_0_1);
		boost::hash_combine(seed, Lprev_arm1_0_0_2);
		boost::hash_combine(seed, Lprev_arm1_1);
		boost::hash_combine(seed, Lprev_arm2_0_0_2);
		boost::hash_combine(seed, Lprev_arm2_1);
		boost::hash_combine(seed, Lprev_arm1op_0_0_2);
		boost::hash_combine(seed, Lprev_arm1op_1);
		boost::hash_combine(seed, Lprev_arm2op_0_0_2);
		boost::hash_combine(seed, Lprev_arm2op_1);
		boost::hash_combine(seed, LAssumptionsAlreadyViolated);
return seed;
}

        void output(std::ostream & os) const {
        
		os << "Ip0_0 = " << Ip0_0 << ",";
		os << "Ip0_1 = " << Ip0_1 << ",";
		os << "Ip0_2 = " << Ip0_2 << ",";
		os << "Ip1_0 = " << Ip1_0 << ",";
		os << "Ip1_1 = " << Ip1_1 << ",";
		os << "Ip1_2 = " << Ip1_2 << ",";
		os << "Ip2_0 = " << Ip2_0 << ",";
		os << "Ip2_1 = " << Ip2_1 << ",";
		os << "Ip2_2 = " << Ip2_2 << ",";
		os << "IerrorCount_0_0_1 = " << IerrorCount_0_0_1 << ",";
		os << "Icontrollable_arm1_0_0_2 = " << Icontrollable_arm1_0_0_2 << ",";
		os << "Icontrollable_arm1_1 = " << Icontrollable_arm1_1 << ",";
		os << "Icontrollable_arm2_0_0_2 = " << Icontrollable_arm2_0_0_2 << ",";
		os << "Icontrollable_arm2_1 = " << Icontrollable_arm2_1 << ",";
		os << "Icontrollable_arm1op_0_0_2 = " << Icontrollable_arm1op_0_0_2 << ",";
		os << "Icontrollable_arm1op_1 = " << Icontrollable_arm1op_1 << ",";
		os << "Icontrollable_arm2op_0_0_2 = " << Icontrollable_arm2op_0_0_2 << ",";
		os << "Icontrollable_arm2op_1 = " << Icontrollable_arm2op_1 << ",";
		os << "LIsNotFirstRound = " << LIsNotFirstRound << ",";
		os << "Lprev_p0_0 = " << Lprev_p0_0 << ",";
		os << "Lprev_p0_1 = " << Lprev_p0_1 << ",";
		os << "Lprev_p0_2 = " << Lprev_p0_2 << ",";
		os << "Lprev_p1_0 = " << Lprev_p1_0 << ",";
		os << "Lprev_p1_1 = " << Lprev_p1_1 << ",";
		os << "Lprev_p1_2 = " << Lprev_p1_2 << ",";
		os << "Lprev_p2_0 = " << Lprev_p2_0 << ",";
		os << "Lprev_p2_1 = " << Lprev_p2_1 << ",";
		os << "Lprev_p2_2 = " << Lprev_p2_2 << ",";
		os << "Lprev_errorCount_0_0_1 = " << Lprev_errorCount_0_0_1 << ",";
		os << "Lprev_arm1_0_0_2 = " << Lprev_arm1_0_0_2 << ",";
		os << "Lprev_arm1_1 = " << Lprev_arm1_1 << ",";
		os << "Lprev_arm2_0_0_2 = " << Lprev_arm2_0_0_2 << ",";
		os << "Lprev_arm2_1 = " << Lprev_arm2_1 << ",";
		os << "Lprev_arm1op_0_0_2 = " << Lprev_arm1op_0_0_2 << ",";
		os << "Lprev_arm1op_1 = " << Lprev_arm1op_1 << ",";
		os << "Lprev_arm2op_0_0_2 = " << Lprev_arm2op_0_0_2 << ",";
		os << "Lprev_arm2op_1 = " << Lprev_arm2op_1 << ",";
		os << "LAssumptionsAlreadyViolated = " << LAssumptionsAlreadyViolated << ",";
	}
};
}
void build_model(syntax::system_t & s){
        	s.name("Mono");
        	s.layout_alloc< syntax::layout_T_alloc_t<monoprocess::layout_t> >();
        
s.add_clock("x_38");
s.add_clock("x_40");
s.add_clock("x_42");
s.add_clock("x_44");
s.add_clock("x_46");
s.add_clock("x_48");
s.add_clock("x_50");
s.add_clock("x_52");
s.add_clock("x_54");
s.add_clock("T");
s.add_label("err");
s.add_label("nothing");
s.add_process("Circuit");
s.add_location("Circuit", "init", "", "", syntax::loc_t::INIT | syntax::loc_t::URGENT);
s.add_location("Circuit", "dead", "", "err");
s.add_location("Circuit", "JustSetIp0_0", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "init", "JustSetIp0_0", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Ip0_0=0;;\
                    }
                    
);
s.add_edge("Circuit", "init", "JustSetIp0_0", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Ip0_0=1;;\
                    }
                    
);
s.add_location("Circuit", "JustSetIp0_1", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "JustSetIp0_0", "JustSetIp0_1", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Ip0_1=0;;\
                    }
                    
);
s.add_edge("Circuit", "JustSetIp0_0", "JustSetIp0_1", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Ip0_1=1;;\
                    }
                    
);
s.add_location("Circuit", "JustSetIp0_2", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "JustSetIp0_1", "JustSetIp0_2", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Ip0_2=0;;\
                    }
                    
);
s.add_edge("Circuit", "JustSetIp0_1", "JustSetIp0_2", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Ip0_2=1;;\
                    }
                    
);
s.add_location("Circuit", "JustSetIp1_0", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "JustSetIp0_2", "JustSetIp1_0", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Ip1_0=0;;\
                    }
                    
);
s.add_edge("Circuit", "JustSetIp0_2", "JustSetIp1_0", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Ip1_0=1;;\
                    }
                    
);
s.add_location("Circuit", "JustSetIp1_1", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "JustSetIp1_0", "JustSetIp1_1", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Ip1_1=0;;\
                    }
                    
);
s.add_edge("Circuit", "JustSetIp1_0", "JustSetIp1_1", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Ip1_1=1;;\
                    }
                    
);
s.add_location("Circuit", "JustSetIp1_2", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "JustSetIp1_1", "JustSetIp1_2", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Ip1_2=0;;\
                    }
                    
);
s.add_edge("Circuit", "JustSetIp1_1", "JustSetIp1_2", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Ip1_2=1;;\
                    }
                    
);
s.add_location("Circuit", "JustSetIp2_0", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "JustSetIp1_2", "JustSetIp2_0", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Ip2_0=0;;\
                    }
                    
);
s.add_edge("Circuit", "JustSetIp1_2", "JustSetIp2_0", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Ip2_0=1;;\
                    }
                    
);
s.add_location("Circuit", "JustSetIp2_1", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "JustSetIp2_0", "JustSetIp2_1", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Ip2_1=0;;\
                    }
                    
);
s.add_edge("Circuit", "JustSetIp2_0", "JustSetIp2_1", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Ip2_1=1;;\
                    }
                    
);
s.add_location("Circuit", "JustSetIp2_2", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "JustSetIp2_1", "JustSetIp2_2", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Ip2_2=0;;\
                    }
                    
);
s.add_edge("Circuit", "JustSetIp2_1", "JustSetIp2_2", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Ip2_2=1;;\
                    }
                    
);
s.add_location("Circuit", "JustSetIerrorCount_0_0_1", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "JustSetIp2_2", "JustSetIerrorCount_0_0_1", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.IerrorCount_0_0_1=0;;\
                    }
                    
);
s.add_edge("Circuit", "JustSetIp2_2", "JustSetIerrorCount_0_0_1", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.IerrorCount_0_0_1=1;;\
                    }
                    
);
s.add_location("Circuit", "JustSetIcontrollable_arm1_0_0_2", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "JustSetIerrorCount_0_0_1", "JustSetIcontrollable_arm1_0_0_2", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Icontrollable_arm1_0_0_2=0;;\
                    }
                    
);
s.add_edge("Circuit", "JustSetIerrorCount_0_0_1", "JustSetIcontrollable_arm1_0_0_2", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Icontrollable_arm1_0_0_2=1;;\
                    }
                    
);
s.add_location("Circuit", "JustSetIcontrollable_arm1_1", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "JustSetIcontrollable_arm1_0_0_2", "JustSetIcontrollable_arm1_1", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Icontrollable_arm1_1=0;;\
                    }
                    
);
s.add_edge("Circuit", "JustSetIcontrollable_arm1_0_0_2", "JustSetIcontrollable_arm1_1", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Icontrollable_arm1_1=1;;\
                    }
                    
);
s.add_location("Circuit", "JustSetIcontrollable_arm2_0_0_2", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "JustSetIcontrollable_arm1_1", "JustSetIcontrollable_arm2_0_0_2", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Icontrollable_arm2_0_0_2=0;;\
                    }
                    
);
s.add_edge("Circuit", "JustSetIcontrollable_arm1_1", "JustSetIcontrollable_arm2_0_0_2", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Icontrollable_arm2_0_0_2=1;;\
                    }
                    
);
s.add_location("Circuit", "JustSetIcontrollable_arm2_1", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "JustSetIcontrollable_arm2_0_0_2", "JustSetIcontrollable_arm2_1", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Icontrollable_arm2_1=0;;\
                    }
                    
);
s.add_edge("Circuit", "JustSetIcontrollable_arm2_0_0_2", "JustSetIcontrollable_arm2_1", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Icontrollable_arm2_1=1;;\
                    }
                    
);
s.add_location("Circuit", "JustSetIcontrollable_arm1op_0_0_2", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "JustSetIcontrollable_arm2_1", "JustSetIcontrollable_arm1op_0_0_2", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Icontrollable_arm1op_0_0_2=0;;\
                    }
                    
);
s.add_edge("Circuit", "JustSetIcontrollable_arm2_1", "JustSetIcontrollable_arm1op_0_0_2", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Icontrollable_arm1op_0_0_2=1;;\
                    }
                    
);
s.add_location("Circuit", "JustSetIcontrollable_arm1op_1", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "JustSetIcontrollable_arm1op_0_0_2", "JustSetIcontrollable_arm1op_1", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Icontrollable_arm1op_1=0;;\
                    }
                    
);
s.add_edge("Circuit", "JustSetIcontrollable_arm1op_0_0_2", "JustSetIcontrollable_arm1op_1", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Icontrollable_arm1op_1=1;;\
                    }
                    
);
s.add_location("Circuit", "JustSetIcontrollable_arm2op_0_0_2", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "JustSetIcontrollable_arm1op_1", "JustSetIcontrollable_arm2op_0_0_2", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Icontrollable_arm2op_0_0_2=0;;\
                    }
                    
);
s.add_edge("Circuit", "JustSetIcontrollable_arm1op_1", "JustSetIcontrollable_arm2op_0_0_2", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Icontrollable_arm2op_0_0_2=1;;\
                    }
                    
);
s.add_location("Circuit", "JustSetIcontrollable_arm2op_1", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "JustSetIcontrollable_arm2op_0_0_2", "JustSetIcontrollable_arm2op_1", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Icontrollable_arm2op_1=0;;\
                    }
                    
);
s.add_edge("Circuit", "JustSetIcontrollable_arm2op_0_0_2", "JustSetIcontrollable_arm2op_1", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Icontrollable_arm2op_1=1;;\
                    }
                    
);
s.add_location("Circuit", "UpdatedLIsNotFirstRound", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "JustSetIcontrollable_arm2op_1", "UpdatedLIsNotFirstRound", "", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.LIsNotFirstRound==1;;\
        }
        );
s.add_edge("Circuit", "JustSetIcontrollable_arm2op_1", "UpdatedLIsNotFirstRound", "x_38 <= 1000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.LIsNotFirstRound == 1 && _l.LIsNotFirstRound != 1;\
        }
        );
s.add_edge("Circuit", "JustSetIcontrollable_arm2op_1", "UpdatedLIsNotFirstRound", "x_38 <= 1500", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.LIsNotFirstRound == 0 && _l.LIsNotFirstRound != 1;\
        }
        );
s.add_location("Circuit", "UpdatedLIsNotFirstRound_becomes0","x_38<=1000", "");
s.add_location("Circuit", "UpdatedLIsNotFirstRound_becomes1","x_38<=1500", "");
s.add_edge("Circuit", "JustSetIcontrollable_arm2op_1", "UpdatedLIsNotFirstRound_becomes0", "x_38 < 1000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.LIsNotFirstRound == 1 && _l.LIsNotFirstRound != 1;\
        }
        );
s.add_edge("Circuit", "UpdatedLIsNotFirstRound_becomes0", "UpdatedLIsNotFirstRound", "x_38 >= 1000", "x_38", "", syntax::layout_true,  [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.LIsNotFirstRound = 1;;\
                    }
                    );
s.add_edge("Circuit", "JustSetIcontrollable_arm2op_1", "UpdatedLIsNotFirstRound_becomes1", "x_38 < 1500", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.LIsNotFirstRound == 0 && _l.LIsNotFirstRound != 1;\
        }
        );
s.add_edge("Circuit", "UpdatedLIsNotFirstRound_becomes1", "UpdatedLIsNotFirstRound", "x_38 >= 1500", "x_38", "", syntax::layout_true,  [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.LIsNotFirstRound = 1;;\
                    }
                    );
s.add_location("Circuit", "UpdatedLprev_p0_0", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "UpdatedLIsNotFirstRound", "UpdatedLprev_p0_0", "", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lprev_p0_0==(_l.Ip0_0);;\
        }
        );
s.add_edge("Circuit", "UpdatedLIsNotFirstRound", "UpdatedLprev_p0_0", "x_40 <= 500", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lprev_p0_0 == 1 && _l.Lprev_p0_0 != (_l.Ip0_0);\
        }
        );
s.add_edge("Circuit", "UpdatedLIsNotFirstRound", "UpdatedLprev_p0_0", "x_40 <= 2000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lprev_p0_0 == 0 && _l.Lprev_p0_0 != (_l.Ip0_0);\
        }
        );
s.add_location("Circuit", "UpdatedLprev_p0_0_becomes0","x_40<=500", "");
s.add_location("Circuit", "UpdatedLprev_p0_0_becomes1","x_40<=2000", "");
s.add_edge("Circuit", "UpdatedLIsNotFirstRound", "UpdatedLprev_p0_0_becomes0", "x_40 < 500", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lprev_p0_0 == 1 && _l.Lprev_p0_0 != (_l.Ip0_0);\
        }
        );
s.add_edge("Circuit", "UpdatedLprev_p0_0_becomes0", "UpdatedLprev_p0_0", "x_40 >= 500", "x_40", "", syntax::layout_true,  [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Lprev_p0_0 = (_l.Ip0_0);;\
                    }
                    );
s.add_edge("Circuit", "UpdatedLIsNotFirstRound", "UpdatedLprev_p0_0_becomes1", "x_40 < 2000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lprev_p0_0 == 0 && _l.Lprev_p0_0 != (_l.Ip0_0);\
        }
        );
s.add_edge("Circuit", "UpdatedLprev_p0_0_becomes1", "UpdatedLprev_p0_0", "x_40 >= 2000", "x_40", "", syntax::layout_true,  [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Lprev_p0_0 = (_l.Ip0_0);;\
                    }
                    );
s.add_location("Circuit", "UpdatedLprev_p0_1", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "UpdatedLprev_p0_0", "UpdatedLprev_p0_1", "", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lprev_p0_1==(_l.Ip0_1);;\
        }
        );
s.add_edge("Circuit", "UpdatedLprev_p0_0", "UpdatedLprev_p0_1", "x_42 <= 2000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lprev_p0_1 == 1 && _l.Lprev_p0_1 != (_l.Ip0_1);\
        }
        );
s.add_edge("Circuit", "UpdatedLprev_p0_0", "UpdatedLprev_p0_1", "x_42 <= 3000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lprev_p0_1 == 0 && _l.Lprev_p0_1 != (_l.Ip0_1);\
        }
        );
s.add_location("Circuit", "UpdatedLprev_p0_1_becomes0","x_42<=2000", "");
s.add_location("Circuit", "UpdatedLprev_p0_1_becomes1","x_42<=3000", "");
s.add_edge("Circuit", "UpdatedLprev_p0_0", "UpdatedLprev_p0_1_becomes0", "x_42 < 2000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lprev_p0_1 == 1 && _l.Lprev_p0_1 != (_l.Ip0_1);\
        }
        );
s.add_edge("Circuit", "UpdatedLprev_p0_1_becomes0", "UpdatedLprev_p0_1", "x_42 >= 2000", "x_42", "", syntax::layout_true,  [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Lprev_p0_1 = (_l.Ip0_1);;\
                    }
                    );
s.add_edge("Circuit", "UpdatedLprev_p0_0", "UpdatedLprev_p0_1_becomes1", "x_42 < 3000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lprev_p0_1 == 0 && _l.Lprev_p0_1 != (_l.Ip0_1);\
        }
        );
s.add_edge("Circuit", "UpdatedLprev_p0_1_becomes1", "UpdatedLprev_p0_1", "x_42 >= 3000", "x_42", "", syntax::layout_true,  [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Lprev_p0_1 = (_l.Ip0_1);;\
                    }
                    );
s.add_location("Circuit", "UpdatedLprev_p0_2", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "UpdatedLprev_p0_1", "UpdatedLprev_p0_2", "", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lprev_p0_2==(_l.Ip0_2);;\
        }
        );
s.add_edge("Circuit", "UpdatedLprev_p0_1", "UpdatedLprev_p0_2", "x_44 <= 3000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lprev_p0_2 == 1 && _l.Lprev_p0_2 != (_l.Ip0_2);\
        }
        );
s.add_edge("Circuit", "UpdatedLprev_p0_1", "UpdatedLprev_p0_2", "x_44 <= 0", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lprev_p0_2 == 0 && _l.Lprev_p0_2 != (_l.Ip0_2);\
        }
        );
s.add_location("Circuit", "UpdatedLprev_p0_2_becomes0","x_44<=3000", "");
s.add_location("Circuit", "UpdatedLprev_p0_2_becomes1","x_44<=0", "");
s.add_edge("Circuit", "UpdatedLprev_p0_1", "UpdatedLprev_p0_2_becomes0", "x_44 < 3000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lprev_p0_2 == 1 && _l.Lprev_p0_2 != (_l.Ip0_2);\
        }
        );
s.add_edge("Circuit", "UpdatedLprev_p0_2_becomes0", "UpdatedLprev_p0_2", "x_44 >= 3000", "x_44", "", syntax::layout_true,  [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Lprev_p0_2 = (_l.Ip0_2);;\
                    }
                    );
s.add_edge("Circuit", "UpdatedLprev_p0_2_becomes1", "UpdatedLprev_p0_2", "x_44 >= 0", "x_44", "", syntax::layout_true,  [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Lprev_p0_2 = (_l.Ip0_2);;\
                    }
                    );
s.add_location("Circuit", "UpdatedLprev_p1_0", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "UpdatedLprev_p0_2", "UpdatedLprev_p1_0", "", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lprev_p1_0==(_l.Ip1_0);;\
        }
        );
s.add_edge("Circuit", "UpdatedLprev_p0_2", "UpdatedLprev_p1_0", "x_46 <= 2500", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lprev_p1_0 == 1 && _l.Lprev_p1_0 != (_l.Ip1_0);\
        }
        );
s.add_edge("Circuit", "UpdatedLprev_p0_2", "UpdatedLprev_p1_0", "x_46 <= 0", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lprev_p1_0 == 0 && _l.Lprev_p1_0 != (_l.Ip1_0);\
        }
        );
s.add_location("Circuit", "UpdatedLprev_p1_0_becomes0","x_46<=2500", "");
s.add_location("Circuit", "UpdatedLprev_p1_0_becomes1","x_46<=0", "");
s.add_edge("Circuit", "UpdatedLprev_p0_2", "UpdatedLprev_p1_0_becomes0", "x_46 < 2500", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lprev_p1_0 == 1 && _l.Lprev_p1_0 != (_l.Ip1_0);\
        }
        );
s.add_edge("Circuit", "UpdatedLprev_p1_0_becomes0", "UpdatedLprev_p1_0", "x_46 >= 2500", "x_46", "", syntax::layout_true,  [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Lprev_p1_0 = (_l.Ip1_0);;\
                    }
                    );
s.add_edge("Circuit", "UpdatedLprev_p1_0_becomes1", "UpdatedLprev_p1_0", "x_46 >= 0", "x_46", "", syntax::layout_true,  [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Lprev_p1_0 = (_l.Ip1_0);;\
                    }
                    );
s.add_location("Circuit", "UpdatedLprev_p1_1", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "UpdatedLprev_p1_0", "UpdatedLprev_p1_1", "", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lprev_p1_1==(_l.Ip1_1);;\
        }
        );
s.add_edge("Circuit", "UpdatedLprev_p1_0", "UpdatedLprev_p1_1", "x_48 <= 4000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lprev_p1_1 == 1 && _l.Lprev_p1_1 != (_l.Ip1_1);\
        }
        );
s.add_edge("Circuit", "UpdatedLprev_p1_0", "UpdatedLprev_p1_1", "x_48 <= 2000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lprev_p1_1 == 0 && _l.Lprev_p1_1 != (_l.Ip1_1);\
        }
        );
s.add_location("Circuit", "UpdatedLprev_p1_1_becomes0","x_48<=4000", "");
s.add_location("Circuit", "UpdatedLprev_p1_1_becomes1","x_48<=2000", "");
s.add_edge("Circuit", "UpdatedLprev_p1_0", "UpdatedLprev_p1_1_becomes0", "x_48 < 4000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lprev_p1_1 == 1 && _l.Lprev_p1_1 != (_l.Ip1_1);\
        }
        );
s.add_edge("Circuit", "UpdatedLprev_p1_1_becomes0", "UpdatedLprev_p1_1", "x_48 >= 4000", "x_48", "", syntax::layout_true,  [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Lprev_p1_1 = (_l.Ip1_1);;\
                    }
                    );
s.add_edge("Circuit", "UpdatedLprev_p1_0", "UpdatedLprev_p1_1_becomes1", "x_48 < 2000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lprev_p1_1 == 0 && _l.Lprev_p1_1 != (_l.Ip1_1);\
        }
        );
s.add_edge("Circuit", "UpdatedLprev_p1_1_becomes1", "UpdatedLprev_p1_1", "x_48 >= 2000", "x_48", "", syntax::layout_true,  [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Lprev_p1_1 = (_l.Ip1_1);;\
                    }
                    );
s.add_location("Circuit", "UpdatedLprev_p1_2", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "UpdatedLprev_p1_1", "UpdatedLprev_p1_2", "", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lprev_p1_2==(_l.Ip1_2);;\
        }
        );
s.add_edge("Circuit", "UpdatedLprev_p1_1", "UpdatedLprev_p1_2", "x_50 <= 1000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lprev_p1_2 == 1 && _l.Lprev_p1_2 != (_l.Ip1_2);\
        }
        );
s.add_edge("Circuit", "UpdatedLprev_p1_1", "UpdatedLprev_p1_2", "x_50 <= 500", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lprev_p1_2 == 0 && _l.Lprev_p1_2 != (_l.Ip1_2);\
        }
        );
s.add_location("Circuit", "UpdatedLprev_p1_2_becomes0","x_50<=1000", "");
s.add_location("Circuit", "UpdatedLprev_p1_2_becomes1","x_50<=500", "");
s.add_edge("Circuit", "UpdatedLprev_p1_1", "UpdatedLprev_p1_2_becomes0", "x_50 < 1000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lprev_p1_2 == 1 && _l.Lprev_p1_2 != (_l.Ip1_2);\
        }
        );
s.add_edge("Circuit", "UpdatedLprev_p1_2_becomes0", "UpdatedLprev_p1_2", "x_50 >= 1000", "x_50", "", syntax::layout_true,  [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Lprev_p1_2 = (_l.Ip1_2);;\
                    }
                    );
s.add_edge("Circuit", "UpdatedLprev_p1_1", "UpdatedLprev_p1_2_becomes1", "x_50 < 500", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lprev_p1_2 == 0 && _l.Lprev_p1_2 != (_l.Ip1_2);\
        }
        );
s.add_edge("Circuit", "UpdatedLprev_p1_2_becomes1", "UpdatedLprev_p1_2", "x_50 >= 500", "x_50", "", syntax::layout_true,  [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Lprev_p1_2 = (_l.Ip1_2);;\
                    }
                    );
s.add_location("Circuit", "UpdatedLprev_p2_0", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "UpdatedLprev_p1_2", "UpdatedLprev_p2_0", "", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lprev_p2_0==(_l.Ip2_0);;\
        }
        );
s.add_edge("Circuit", "UpdatedLprev_p1_2", "UpdatedLprev_p2_0", "x_52 <= 1000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lprev_p2_0 == 1 && _l.Lprev_p2_0 != (_l.Ip2_0);\
        }
        );
s.add_edge("Circuit", "UpdatedLprev_p1_2", "UpdatedLprev_p2_0", "x_52 <= 500", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lprev_p2_0 == 0 && _l.Lprev_p2_0 != (_l.Ip2_0);\
        }
        );
s.add_location("Circuit", "UpdatedLprev_p2_0_becomes0","x_52<=1000", "");
s.add_location("Circuit", "UpdatedLprev_p2_0_becomes1","x_52<=500", "");
s.add_edge("Circuit", "UpdatedLprev_p1_2", "UpdatedLprev_p2_0_becomes0", "x_52 < 1000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lprev_p2_0 == 1 && _l.Lprev_p2_0 != (_l.Ip2_0);\
        }
        );
s.add_edge("Circuit", "UpdatedLprev_p2_0_becomes0", "UpdatedLprev_p2_0", "x_52 >= 1000", "x_52", "", syntax::layout_true,  [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Lprev_p2_0 = (_l.Ip2_0);;\
                    }
                    );
s.add_edge("Circuit", "UpdatedLprev_p1_2", "UpdatedLprev_p2_0_becomes1", "x_52 < 500", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lprev_p2_0 == 0 && _l.Lprev_p2_0 != (_l.Ip2_0);\
        }
        );
s.add_edge("Circuit", "UpdatedLprev_p2_0_becomes1", "UpdatedLprev_p2_0", "x_52 >= 500", "x_52", "", syntax::layout_true,  [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Lprev_p2_0 = (_l.Ip2_0);;\
                    }
                    );
s.add_location("Circuit", "UpdatedLprev_p2_1", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "UpdatedLprev_p2_0", "UpdatedLprev_p2_1", "", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lprev_p2_1==(_l.Ip2_1);;\
        }
        );
s.add_edge("Circuit", "UpdatedLprev_p2_0", "UpdatedLprev_p2_1", "x_54 <= 2000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lprev_p2_1 == 1 && _l.Lprev_p2_1 != (_l.Ip2_1);\
        }
        );
s.add_edge("Circuit", "UpdatedLprev_p2_0", "UpdatedLprev_p2_1", "x_54 <= 1500", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lprev_p2_1 == 0 && _l.Lprev_p2_1 != (_l.Ip2_1);\
        }
        );
s.add_location("Circuit", "UpdatedLprev_p2_1_becomes0","x_54<=2000", "");
s.add_location("Circuit", "UpdatedLprev_p2_1_becomes1","x_54<=1500", "");
s.add_edge("Circuit", "UpdatedLprev_p2_0", "UpdatedLprev_p2_1_becomes0", "x_54 < 2000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lprev_p2_1 == 1 && _l.Lprev_p2_1 != (_l.Ip2_1);\
        }
        );
s.add_edge("Circuit", "UpdatedLprev_p2_1_becomes0", "UpdatedLprev_p2_1", "x_54 >= 2000", "x_54", "", syntax::layout_true,  [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Lprev_p2_1 = (_l.Ip2_1);;\
                    }
                    );
s.add_edge("Circuit", "UpdatedLprev_p2_0", "UpdatedLprev_p2_1_becomes1", "x_54 < 1500", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lprev_p2_1 == 0 && _l.Lprev_p2_1 != (_l.Ip2_1);\
        }
        );
s.add_edge("Circuit", "UpdatedLprev_p2_1_becomes1", "UpdatedLprev_p2_1", "x_54 >= 1500", "x_54", "", syntax::layout_true,  [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Lprev_p2_1 = (_l.Ip2_1);;\
                    }
                    );
s.add_edge("Circuit", "UpdatedLprev_p2_1", "dead", "T>5000", "", "", syntax::layout_true);
s.add_edge("Circuit", "UpdatedLprev_p2_1", "init", "T<=5000", "T", "", syntax::layout_true);
s.synchronizer<syntax::asynchronous_product_t>();
}
