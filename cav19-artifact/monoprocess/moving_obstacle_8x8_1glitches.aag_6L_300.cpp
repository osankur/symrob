#include <iostream>
        #include "syntax/system.hh"
        #include "syntax/sync_product.hh"
        namespace monoprocess {
        class layout_t : public syntax::layout_t {
        public:
        
	bool Iobsx_0_0_6;
	bool Iobsx_1;
	bool Iobsx_2;
	bool Iobsy_0_0_6;
	bool Iobsy_1;
	bool Iobsy_2;
	bool Irobx_0_0_7;
	bool Irobx_1;
	bool Irobx_2;
	bool Iroby_0_0_7;
	bool Iroby_1;
	bool Iroby_2;
	bool Iglitches_0_0_1;
	bool Icontrollable_movx_0_0_2;
	bool Icontrollable_movx_1;
	bool Icontrollable_movy_0_0_2;
	bool Icontrollable_movy_1;
	bool Icontrollable_obsmove;
	bool LIsNotFirstRound;
	bool Lprev_obsx_0_0_6;
	bool Lprev_obsx_1;
	bool Lprev_obsx_2;
	bool Lprev_obsy_0_0_6;
	bool Lprev_obsy_1;
	bool Lprev_obsy_2;
	bool Lprev_robx_0_0_7;
	bool Lprev_robx_1;
	bool Lprev_robx_2;
	bool Lprev_roby_0_0_7;
	bool Lprev_roby_1;
	bool Lprev_roby_2;
	bool Lprev_glitches_0_0_1;
	bool Lprev_movx_0_0_2;
	bool Lprev_movx_1;
	bool Lprev_movy_0_0_2;
	bool Lprev_movy_1;
	bool Lprev_obsmove;
	bool LAssumptionsAlreadyViolated;
	layout_t(){
		Iobsx_0_0_6 = 0;
		Iobsx_1 = 0;
		Iobsx_2 = 0;
		Iobsy_0_0_6 = 0;
		Iobsy_1 = 0;
		Iobsy_2 = 0;
		Irobx_0_0_7 = 0;
		Irobx_1 = 0;
		Irobx_2 = 0;
		Iroby_0_0_7 = 0;
		Iroby_1 = 0;
		Iroby_2 = 0;
		Iglitches_0_0_1 = 0;
		Icontrollable_movx_0_0_2 = 0;
		Icontrollable_movx_1 = 0;
		Icontrollable_movy_0_0_2 = 0;
		Icontrollable_movy_1 = 0;
		Icontrollable_obsmove = 0;
		LIsNotFirstRound = 0;
		Lprev_obsx_0_0_6 = 0;
		Lprev_obsx_1 = 0;
		Lprev_obsx_2 = 0;
		Lprev_obsy_0_0_6 = 0;
		Lprev_obsy_1 = 0;
		Lprev_obsy_2 = 0;
		Lprev_robx_0_0_7 = 0;
		Lprev_robx_1 = 0;
		Lprev_robx_2 = 0;
		Lprev_roby_0_0_7 = 0;
		Lprev_roby_1 = 0;
		Lprev_roby_2 = 0;
		Lprev_glitches_0_0_1 = 0;
		Lprev_movx_0_0_2 = 0;
		Lprev_movx_1 = 0;
		Lprev_movy_0_0_2 = 0;
		Lprev_movy_1 = 0;
		Lprev_obsmove = 0;
		LAssumptionsAlreadyViolated = 0;
	}
virtual ~layout_t(){}
layout_t (const layout_t &l) = default;

        inline bool operator == (const syntax::layout_t & l) const {
            monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);
        
		if(Iobsx_0_0_6 != _l.Iobsx_0_0_6) return false;
		if(Iobsx_1 != _l.Iobsx_1) return false;
		if(Iobsx_2 != _l.Iobsx_2) return false;
		if(Iobsy_0_0_6 != _l.Iobsy_0_0_6) return false;
		if(Iobsy_1 != _l.Iobsy_1) return false;
		if(Iobsy_2 != _l.Iobsy_2) return false;
		if(Irobx_0_0_7 != _l.Irobx_0_0_7) return false;
		if(Irobx_1 != _l.Irobx_1) return false;
		if(Irobx_2 != _l.Irobx_2) return false;
		if(Iroby_0_0_7 != _l.Iroby_0_0_7) return false;
		if(Iroby_1 != _l.Iroby_1) return false;
		if(Iroby_2 != _l.Iroby_2) return false;
		if(Iglitches_0_0_1 != _l.Iglitches_0_0_1) return false;
		if(Icontrollable_movx_0_0_2 != _l.Icontrollable_movx_0_0_2) return false;
		if(Icontrollable_movx_1 != _l.Icontrollable_movx_1) return false;
		if(Icontrollable_movy_0_0_2 != _l.Icontrollable_movy_0_0_2) return false;
		if(Icontrollable_movy_1 != _l.Icontrollable_movy_1) return false;
		if(Icontrollable_obsmove != _l.Icontrollable_obsmove) return false;
		if(LIsNotFirstRound != _l.LIsNotFirstRound) return false;
		if(Lprev_obsx_0_0_6 != _l.Lprev_obsx_0_0_6) return false;
		if(Lprev_obsx_1 != _l.Lprev_obsx_1) return false;
		if(Lprev_obsx_2 != _l.Lprev_obsx_2) return false;
		if(Lprev_obsy_0_0_6 != _l.Lprev_obsy_0_0_6) return false;
		if(Lprev_obsy_1 != _l.Lprev_obsy_1) return false;
		if(Lprev_obsy_2 != _l.Lprev_obsy_2) return false;
		if(Lprev_robx_0_0_7 != _l.Lprev_robx_0_0_7) return false;
		if(Lprev_robx_1 != _l.Lprev_robx_1) return false;
		if(Lprev_robx_2 != _l.Lprev_robx_2) return false;
		if(Lprev_roby_0_0_7 != _l.Lprev_roby_0_0_7) return false;
		if(Lprev_roby_1 != _l.Lprev_roby_1) return false;
		if(Lprev_roby_2 != _l.Lprev_roby_2) return false;
		if(Lprev_glitches_0_0_1 != _l.Lprev_glitches_0_0_1) return false;
		if(Lprev_movx_0_0_2 != _l.Lprev_movx_0_0_2) return false;
		if(Lprev_movx_1 != _l.Lprev_movx_1) return false;
		if(Lprev_movy_0_0_2 != _l.Lprev_movy_0_0_2) return false;
		if(Lprev_movy_1 != _l.Lprev_movy_1) return false;
		if(Lprev_obsmove != _l.Lprev_obsmove) return false;
		if(LAssumptionsAlreadyViolated != _l.LAssumptionsAlreadyViolated) return false;
return true;
}

        inline size_t hash() const {
        size_t seed = global_t::instance().hash_seed();
        
		boost::hash_combine(seed, Iobsx_0_0_6);
		boost::hash_combine(seed, Iobsx_1);
		boost::hash_combine(seed, Iobsx_2);
		boost::hash_combine(seed, Iobsy_0_0_6);
		boost::hash_combine(seed, Iobsy_1);
		boost::hash_combine(seed, Iobsy_2);
		boost::hash_combine(seed, Irobx_0_0_7);
		boost::hash_combine(seed, Irobx_1);
		boost::hash_combine(seed, Irobx_2);
		boost::hash_combine(seed, Iroby_0_0_7);
		boost::hash_combine(seed, Iroby_1);
		boost::hash_combine(seed, Iroby_2);
		boost::hash_combine(seed, Iglitches_0_0_1);
		boost::hash_combine(seed, Icontrollable_movx_0_0_2);
		boost::hash_combine(seed, Icontrollable_movx_1);
		boost::hash_combine(seed, Icontrollable_movy_0_0_2);
		boost::hash_combine(seed, Icontrollable_movy_1);
		boost::hash_combine(seed, Icontrollable_obsmove);
		boost::hash_combine(seed, LIsNotFirstRound);
		boost::hash_combine(seed, Lprev_obsx_0_0_6);
		boost::hash_combine(seed, Lprev_obsx_1);
		boost::hash_combine(seed, Lprev_obsx_2);
		boost::hash_combine(seed, Lprev_obsy_0_0_6);
		boost::hash_combine(seed, Lprev_obsy_1);
		boost::hash_combine(seed, Lprev_obsy_2);
		boost::hash_combine(seed, Lprev_robx_0_0_7);
		boost::hash_combine(seed, Lprev_robx_1);
		boost::hash_combine(seed, Lprev_robx_2);
		boost::hash_combine(seed, Lprev_roby_0_0_7);
		boost::hash_combine(seed, Lprev_roby_1);
		boost::hash_combine(seed, Lprev_roby_2);
		boost::hash_combine(seed, Lprev_glitches_0_0_1);
		boost::hash_combine(seed, Lprev_movx_0_0_2);
		boost::hash_combine(seed, Lprev_movx_1);
		boost::hash_combine(seed, Lprev_movy_0_0_2);
		boost::hash_combine(seed, Lprev_movy_1);
		boost::hash_combine(seed, Lprev_obsmove);
		boost::hash_combine(seed, LAssumptionsAlreadyViolated);
return seed;
}

        void output(std::ostream & os) const {
        
		os << "Iobsx_0_0_6 = " << Iobsx_0_0_6 << ",";
		os << "Iobsx_1 = " << Iobsx_1 << ",";
		os << "Iobsx_2 = " << Iobsx_2 << ",";
		os << "Iobsy_0_0_6 = " << Iobsy_0_0_6 << ",";
		os << "Iobsy_1 = " << Iobsy_1 << ",";
		os << "Iobsy_2 = " << Iobsy_2 << ",";
		os << "Irobx_0_0_7 = " << Irobx_0_0_7 << ",";
		os << "Irobx_1 = " << Irobx_1 << ",";
		os << "Irobx_2 = " << Irobx_2 << ",";
		os << "Iroby_0_0_7 = " << Iroby_0_0_7 << ",";
		os << "Iroby_1 = " << Iroby_1 << ",";
		os << "Iroby_2 = " << Iroby_2 << ",";
		os << "Iglitches_0_0_1 = " << Iglitches_0_0_1 << ",";
		os << "Icontrollable_movx_0_0_2 = " << Icontrollable_movx_0_0_2 << ",";
		os << "Icontrollable_movx_1 = " << Icontrollable_movx_1 << ",";
		os << "Icontrollable_movy_0_0_2 = " << Icontrollable_movy_0_0_2 << ",";
		os << "Icontrollable_movy_1 = " << Icontrollable_movy_1 << ",";
		os << "Icontrollable_obsmove = " << Icontrollable_obsmove << ",";
		os << "LIsNotFirstRound = " << LIsNotFirstRound << ",";
		os << "Lprev_obsx_0_0_6 = " << Lprev_obsx_0_0_6 << ",";
		os << "Lprev_obsx_1 = " << Lprev_obsx_1 << ",";
		os << "Lprev_obsx_2 = " << Lprev_obsx_2 << ",";
		os << "Lprev_obsy_0_0_6 = " << Lprev_obsy_0_0_6 << ",";
		os << "Lprev_obsy_1 = " << Lprev_obsy_1 << ",";
		os << "Lprev_obsy_2 = " << Lprev_obsy_2 << ",";
		os << "Lprev_robx_0_0_7 = " << Lprev_robx_0_0_7 << ",";
		os << "Lprev_robx_1 = " << Lprev_robx_1 << ",";
		os << "Lprev_robx_2 = " << Lprev_robx_2 << ",";
		os << "Lprev_roby_0_0_7 = " << Lprev_roby_0_0_7 << ",";
		os << "Lprev_roby_1 = " << Lprev_roby_1 << ",";
		os << "Lprev_roby_2 = " << Lprev_roby_2 << ",";
		os << "Lprev_glitches_0_0_1 = " << Lprev_glitches_0_0_1 << ",";
		os << "Lprev_movx_0_0_2 = " << Lprev_movx_0_0_2 << ",";
		os << "Lprev_movx_1 = " << Lprev_movx_1 << ",";
		os << "Lprev_movy_0_0_2 = " << Lprev_movy_0_0_2 << ",";
		os << "Lprev_movy_1 = " << Lprev_movy_1 << ",";
		os << "Lprev_obsmove = " << Lprev_obsmove << ",";
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
s.add_clock("T");
s.add_label("err");
s.add_label("nothing");
s.add_process("Circuit");
s.add_location("Circuit", "init", "", "", syntax::loc_t::INIT | syntax::loc_t::URGENT);
s.add_location("Circuit", "dead", "", "err");
s.add_location("Circuit", "JustSetIobsx_0_0_6", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "init", "JustSetIobsx_0_0_6", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Iobsx_0_0_6=0;;\
                    }
                    
);
s.add_edge("Circuit", "init", "JustSetIobsx_0_0_6", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Iobsx_0_0_6=1;;\
                    }
                    
);
s.add_location("Circuit", "JustSetIobsx_1", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "JustSetIobsx_0_0_6", "JustSetIobsx_1", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Iobsx_1=0;;\
                    }
                    
);
s.add_edge("Circuit", "JustSetIobsx_0_0_6", "JustSetIobsx_1", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Iobsx_1=1;;\
                    }
                    
);
s.add_location("Circuit", "JustSetIobsx_2", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "JustSetIobsx_1", "JustSetIobsx_2", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Iobsx_2=0;;\
                    }
                    
);
s.add_edge("Circuit", "JustSetIobsx_1", "JustSetIobsx_2", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Iobsx_2=1;;\
                    }
                    
);
s.add_location("Circuit", "JustSetIobsy_0_0_6", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "JustSetIobsx_2", "JustSetIobsy_0_0_6", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Iobsy_0_0_6=0;;\
                    }
                    
);
s.add_edge("Circuit", "JustSetIobsx_2", "JustSetIobsy_0_0_6", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Iobsy_0_0_6=1;;\
                    }
                    
);
s.add_location("Circuit", "JustSetIobsy_1", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "JustSetIobsy_0_0_6", "JustSetIobsy_1", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Iobsy_1=0;;\
                    }
                    
);
s.add_edge("Circuit", "JustSetIobsy_0_0_6", "JustSetIobsy_1", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Iobsy_1=1;;\
                    }
                    
);
s.add_location("Circuit", "JustSetIobsy_2", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "JustSetIobsy_1", "JustSetIobsy_2", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Iobsy_2=0;;\
                    }
                    
);
s.add_edge("Circuit", "JustSetIobsy_1", "JustSetIobsy_2", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Iobsy_2=1;;\
                    }
                    
);
s.add_location("Circuit", "JustSetIrobx_0_0_7", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "JustSetIobsy_2", "JustSetIrobx_0_0_7", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Irobx_0_0_7=0;;\
                    }
                    
);
s.add_edge("Circuit", "JustSetIobsy_2", "JustSetIrobx_0_0_7", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Irobx_0_0_7=1;;\
                    }
                    
);
s.add_location("Circuit", "JustSetIrobx_1", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "JustSetIrobx_0_0_7", "JustSetIrobx_1", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Irobx_1=0;;\
                    }
                    
);
s.add_edge("Circuit", "JustSetIrobx_0_0_7", "JustSetIrobx_1", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Irobx_1=1;;\
                    }
                    
);
s.add_location("Circuit", "JustSetIrobx_2", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "JustSetIrobx_1", "JustSetIrobx_2", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Irobx_2=0;;\
                    }
                    
);
s.add_edge("Circuit", "JustSetIrobx_1", "JustSetIrobx_2", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Irobx_2=1;;\
                    }
                    
);
s.add_location("Circuit", "JustSetIroby_0_0_7", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "JustSetIrobx_2", "JustSetIroby_0_0_7", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Iroby_0_0_7=0;;\
                    }
                    
);
s.add_edge("Circuit", "JustSetIrobx_2", "JustSetIroby_0_0_7", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Iroby_0_0_7=1;;\
                    }
                    
);
s.add_location("Circuit", "JustSetIroby_1", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "JustSetIroby_0_0_7", "JustSetIroby_1", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Iroby_1=0;;\
                    }
                    
);
s.add_edge("Circuit", "JustSetIroby_0_0_7", "JustSetIroby_1", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Iroby_1=1;;\
                    }
                    
);
s.add_location("Circuit", "JustSetIroby_2", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "JustSetIroby_1", "JustSetIroby_2", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Iroby_2=0;;\
                    }
                    
);
s.add_edge("Circuit", "JustSetIroby_1", "JustSetIroby_2", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Iroby_2=1;;\
                    }
                    
);
s.add_location("Circuit", "JustSetIglitches_0_0_1", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "JustSetIroby_2", "JustSetIglitches_0_0_1", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Iglitches_0_0_1=0;;\
                    }
                    
);
s.add_edge("Circuit", "JustSetIroby_2", "JustSetIglitches_0_0_1", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Iglitches_0_0_1=1;;\
                    }
                    
);
s.add_location("Circuit", "JustSetIcontrollable_movx_0_0_2", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "JustSetIglitches_0_0_1", "JustSetIcontrollable_movx_0_0_2", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Icontrollable_movx_0_0_2=0;;\
                    }
                    
);
s.add_edge("Circuit", "JustSetIglitches_0_0_1", "JustSetIcontrollable_movx_0_0_2", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Icontrollable_movx_0_0_2=1;;\
                    }
                    
);
s.add_location("Circuit", "JustSetIcontrollable_movx_1", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "JustSetIcontrollable_movx_0_0_2", "JustSetIcontrollable_movx_1", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Icontrollable_movx_1=0;;\
                    }
                    
);
s.add_edge("Circuit", "JustSetIcontrollable_movx_0_0_2", "JustSetIcontrollable_movx_1", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Icontrollable_movx_1=1;;\
                    }
                    
);
s.add_location("Circuit", "JustSetIcontrollable_movy_0_0_2", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "JustSetIcontrollable_movx_1", "JustSetIcontrollable_movy_0_0_2", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Icontrollable_movy_0_0_2=0;;\
                    }
                    
);
s.add_edge("Circuit", "JustSetIcontrollable_movx_1", "JustSetIcontrollable_movy_0_0_2", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Icontrollable_movy_0_0_2=1;;\
                    }
                    
);
s.add_location("Circuit", "JustSetIcontrollable_movy_1", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "JustSetIcontrollable_movy_0_0_2", "JustSetIcontrollable_movy_1", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Icontrollable_movy_1=0;;\
                    }
                    
);
s.add_edge("Circuit", "JustSetIcontrollable_movy_0_0_2", "JustSetIcontrollable_movy_1", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Icontrollable_movy_1=1;;\
                    }
                    
);
s.add_location("Circuit", "JustSetIcontrollable_obsmove", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "JustSetIcontrollable_movy_1", "JustSetIcontrollable_obsmove", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Icontrollable_obsmove=0;;\
                    }
                    
);
s.add_edge("Circuit", "JustSetIcontrollable_movy_1", "JustSetIcontrollable_obsmove", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Icontrollable_obsmove=1;;\
                    }
                    
);
s.add_location("Circuit", "UpdatedLIsNotFirstRound", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "JustSetIcontrollable_obsmove", "UpdatedLIsNotFirstRound", "", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.LIsNotFirstRound==1;;\
        }
        );
s.add_edge("Circuit", "JustSetIcontrollable_obsmove", "UpdatedLIsNotFirstRound", "x_38 <= 1000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.LIsNotFirstRound == 1 && _l.LIsNotFirstRound != 1;\
        }
        );
s.add_edge("Circuit", "JustSetIcontrollable_obsmove", "UpdatedLIsNotFirstRound", "x_38 <= 1500", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.LIsNotFirstRound == 0 && _l.LIsNotFirstRound != 1;\
        }
        );
s.add_location("Circuit", "UpdatedLIsNotFirstRound_becomes0","x_38<=1000", "");
s.add_location("Circuit", "UpdatedLIsNotFirstRound_becomes1","x_38<=1500", "");
s.add_edge("Circuit", "JustSetIcontrollable_obsmove", "UpdatedLIsNotFirstRound_becomes0", "x_38 < 1000", "", "", 
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
s.add_edge("Circuit", "JustSetIcontrollable_obsmove", "UpdatedLIsNotFirstRound_becomes1", "x_38 < 1500", "", "", 
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
s.add_location("Circuit", "UpdatedLprev_obsx_0_0_6", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "UpdatedLIsNotFirstRound", "UpdatedLprev_obsx_0_0_6", "", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lprev_obsx_0_0_6==(_l.Iobsx_0_0_6);;\
        }
        );
s.add_edge("Circuit", "UpdatedLIsNotFirstRound", "UpdatedLprev_obsx_0_0_6", "x_40 <= 500", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lprev_obsx_0_0_6 == 1 && _l.Lprev_obsx_0_0_6 != (_l.Iobsx_0_0_6);\
        }
        );
s.add_edge("Circuit", "UpdatedLIsNotFirstRound", "UpdatedLprev_obsx_0_0_6", "x_40 <= 2000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lprev_obsx_0_0_6 == 0 && _l.Lprev_obsx_0_0_6 != (_l.Iobsx_0_0_6);\
        }
        );
s.add_location("Circuit", "UpdatedLprev_obsx_0_0_6_becomes0","x_40<=500", "");
s.add_location("Circuit", "UpdatedLprev_obsx_0_0_6_becomes1","x_40<=2000", "");
s.add_edge("Circuit", "UpdatedLIsNotFirstRound", "UpdatedLprev_obsx_0_0_6_becomes0", "x_40 < 500", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lprev_obsx_0_0_6 == 1 && _l.Lprev_obsx_0_0_6 != (_l.Iobsx_0_0_6);\
        }
        );
s.add_edge("Circuit", "UpdatedLprev_obsx_0_0_6_becomes0", "UpdatedLprev_obsx_0_0_6", "x_40 >= 500", "x_40", "", syntax::layout_true,  [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Lprev_obsx_0_0_6 = (_l.Iobsx_0_0_6);;\
                    }
                    );
s.add_edge("Circuit", "UpdatedLIsNotFirstRound", "UpdatedLprev_obsx_0_0_6_becomes1", "x_40 < 2000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lprev_obsx_0_0_6 == 0 && _l.Lprev_obsx_0_0_6 != (_l.Iobsx_0_0_6);\
        }
        );
s.add_edge("Circuit", "UpdatedLprev_obsx_0_0_6_becomes1", "UpdatedLprev_obsx_0_0_6", "x_40 >= 2000", "x_40", "", syntax::layout_true,  [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Lprev_obsx_0_0_6 = (_l.Iobsx_0_0_6);;\
                    }
                    );
s.add_location("Circuit", "UpdatedLprev_obsx_1", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "UpdatedLprev_obsx_0_0_6", "UpdatedLprev_obsx_1", "", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lprev_obsx_1==(_l.Iobsx_1);;\
        }
        );
s.add_edge("Circuit", "UpdatedLprev_obsx_0_0_6", "UpdatedLprev_obsx_1", "x_42 <= 2000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lprev_obsx_1 == 1 && _l.Lprev_obsx_1 != (_l.Iobsx_1);\
        }
        );
s.add_edge("Circuit", "UpdatedLprev_obsx_0_0_6", "UpdatedLprev_obsx_1", "x_42 <= 3000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lprev_obsx_1 == 0 && _l.Lprev_obsx_1 != (_l.Iobsx_1);\
        }
        );
s.add_location("Circuit", "UpdatedLprev_obsx_1_becomes0","x_42<=2000", "");
s.add_location("Circuit", "UpdatedLprev_obsx_1_becomes1","x_42<=3000", "");
s.add_edge("Circuit", "UpdatedLprev_obsx_0_0_6", "UpdatedLprev_obsx_1_becomes0", "x_42 < 2000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lprev_obsx_1 == 1 && _l.Lprev_obsx_1 != (_l.Iobsx_1);\
        }
        );
s.add_edge("Circuit", "UpdatedLprev_obsx_1_becomes0", "UpdatedLprev_obsx_1", "x_42 >= 2000", "x_42", "", syntax::layout_true,  [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Lprev_obsx_1 = (_l.Iobsx_1);;\
                    }
                    );
s.add_edge("Circuit", "UpdatedLprev_obsx_0_0_6", "UpdatedLprev_obsx_1_becomes1", "x_42 < 3000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lprev_obsx_1 == 0 && _l.Lprev_obsx_1 != (_l.Iobsx_1);\
        }
        );
s.add_edge("Circuit", "UpdatedLprev_obsx_1_becomes1", "UpdatedLprev_obsx_1", "x_42 >= 3000", "x_42", "", syntax::layout_true,  [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Lprev_obsx_1 = (_l.Iobsx_1);;\
                    }
                    );
s.add_location("Circuit", "UpdatedLprev_obsx_2", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "UpdatedLprev_obsx_1", "UpdatedLprev_obsx_2", "", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lprev_obsx_2==(_l.Iobsx_2);;\
        }
        );
s.add_edge("Circuit", "UpdatedLprev_obsx_1", "UpdatedLprev_obsx_2", "x_44 <= 3000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lprev_obsx_2 == 1 && _l.Lprev_obsx_2 != (_l.Iobsx_2);\
        }
        );
s.add_edge("Circuit", "UpdatedLprev_obsx_1", "UpdatedLprev_obsx_2", "x_44 <= 0", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lprev_obsx_2 == 0 && _l.Lprev_obsx_2 != (_l.Iobsx_2);\
        }
        );
s.add_location("Circuit", "UpdatedLprev_obsx_2_becomes0","x_44<=3000", "");
s.add_location("Circuit", "UpdatedLprev_obsx_2_becomes1","x_44<=0", "");
s.add_edge("Circuit", "UpdatedLprev_obsx_1", "UpdatedLprev_obsx_2_becomes0", "x_44 < 3000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lprev_obsx_2 == 1 && _l.Lprev_obsx_2 != (_l.Iobsx_2);\
        }
        );
s.add_edge("Circuit", "UpdatedLprev_obsx_2_becomes0", "UpdatedLprev_obsx_2", "x_44 >= 3000", "x_44", "", syntax::layout_true,  [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Lprev_obsx_2 = (_l.Iobsx_2);;\
                    }
                    );
s.add_edge("Circuit", "UpdatedLprev_obsx_2_becomes1", "UpdatedLprev_obsx_2", "x_44 >= 0", "x_44", "", syntax::layout_true,  [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Lprev_obsx_2 = (_l.Iobsx_2);;\
                    }
                    );
s.add_location("Circuit", "UpdatedLprev_obsy_0_0_6", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "UpdatedLprev_obsx_2", "UpdatedLprev_obsy_0_0_6", "", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lprev_obsy_0_0_6==(_l.Iobsy_0_0_6);;\
        }
        );
s.add_edge("Circuit", "UpdatedLprev_obsx_2", "UpdatedLprev_obsy_0_0_6", "x_46 <= 2500", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lprev_obsy_0_0_6 == 1 && _l.Lprev_obsy_0_0_6 != (_l.Iobsy_0_0_6);\
        }
        );
s.add_edge("Circuit", "UpdatedLprev_obsx_2", "UpdatedLprev_obsy_0_0_6", "x_46 <= 0", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lprev_obsy_0_0_6 == 0 && _l.Lprev_obsy_0_0_6 != (_l.Iobsy_0_0_6);\
        }
        );
s.add_location("Circuit", "UpdatedLprev_obsy_0_0_6_becomes0","x_46<=2500", "");
s.add_location("Circuit", "UpdatedLprev_obsy_0_0_6_becomes1","x_46<=0", "");
s.add_edge("Circuit", "UpdatedLprev_obsx_2", "UpdatedLprev_obsy_0_0_6_becomes0", "x_46 < 2500", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lprev_obsy_0_0_6 == 1 && _l.Lprev_obsy_0_0_6 != (_l.Iobsy_0_0_6);\
        }
        );
s.add_edge("Circuit", "UpdatedLprev_obsy_0_0_6_becomes0", "UpdatedLprev_obsy_0_0_6", "x_46 >= 2500", "x_46", "", syntax::layout_true,  [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Lprev_obsy_0_0_6 = (_l.Iobsy_0_0_6);;\
                    }
                    );
s.add_edge("Circuit", "UpdatedLprev_obsy_0_0_6_becomes1", "UpdatedLprev_obsy_0_0_6", "x_46 >= 0", "x_46", "", syntax::layout_true,  [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Lprev_obsy_0_0_6 = (_l.Iobsy_0_0_6);;\
                    }
                    );
s.add_location("Circuit", "UpdatedLprev_obsy_1", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "UpdatedLprev_obsy_0_0_6", "UpdatedLprev_obsy_1", "", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lprev_obsy_1==(_l.Iobsy_1);;\
        }
        );
s.add_edge("Circuit", "UpdatedLprev_obsy_0_0_6", "UpdatedLprev_obsy_1", "x_48 <= 4000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lprev_obsy_1 == 1 && _l.Lprev_obsy_1 != (_l.Iobsy_1);\
        }
        );
s.add_edge("Circuit", "UpdatedLprev_obsy_0_0_6", "UpdatedLprev_obsy_1", "x_48 <= 2000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lprev_obsy_1 == 0 && _l.Lprev_obsy_1 != (_l.Iobsy_1);\
        }
        );
s.add_location("Circuit", "UpdatedLprev_obsy_1_becomes0","x_48<=4000", "");
s.add_location("Circuit", "UpdatedLprev_obsy_1_becomes1","x_48<=2000", "");
s.add_edge("Circuit", "UpdatedLprev_obsy_0_0_6", "UpdatedLprev_obsy_1_becomes0", "x_48 < 4000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lprev_obsy_1 == 1 && _l.Lprev_obsy_1 != (_l.Iobsy_1);\
        }
        );
s.add_edge("Circuit", "UpdatedLprev_obsy_1_becomes0", "UpdatedLprev_obsy_1", "x_48 >= 4000", "x_48", "", syntax::layout_true,  [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Lprev_obsy_1 = (_l.Iobsy_1);;\
                    }
                    );
s.add_edge("Circuit", "UpdatedLprev_obsy_0_0_6", "UpdatedLprev_obsy_1_becomes1", "x_48 < 2000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lprev_obsy_1 == 0 && _l.Lprev_obsy_1 != (_l.Iobsy_1);\
        }
        );
s.add_edge("Circuit", "UpdatedLprev_obsy_1_becomes1", "UpdatedLprev_obsy_1", "x_48 >= 2000", "x_48", "", syntax::layout_true,  [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Lprev_obsy_1 = (_l.Iobsy_1);;\
                    }
                    );
s.add_edge("Circuit", "UpdatedLprev_obsy_1", "dead", "T>3000", "", "", syntax::layout_true);
s.add_edge("Circuit", "UpdatedLprev_obsy_1", "init", "T<=3000", "T", "", syntax::layout_true);
s.synchronizer<syntax::asynchronous_product_t>();
}
