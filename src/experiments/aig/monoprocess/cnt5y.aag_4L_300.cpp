#include <iostream>
        #include "syntax/system.hh"
        #include "syntax/sync_product.hh"
        namespace monoprocess {
        class layout_t : public syntax::layout_t {
        public:
        
	bool Istay;
	bool Icontrollable_reset;
	bool Ln7;
	bool Lcounter0_out;
	bool Lcounter1_out;
	bool Lcounter2_out;
	bool Lcounter3_out;
	bool Lcounter4_out;
	layout_t(){
		Istay = 0;
		Icontrollable_reset = 0;
		Ln7 = 0;
		Lcounter0_out = 0;
		Lcounter1_out = 0;
		Lcounter2_out = 0;
		Lcounter3_out = 0;
		Lcounter4_out = 0;
	}
virtual ~layout_t(){}
layout_t (const layout_t &l) = default;

        inline bool operator == (const syntax::layout_t & l) const {
            monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);
        
		if(Istay != _l.Istay) return false;
		if(Icontrollable_reset != _l.Icontrollable_reset) return false;
		if(Ln7 != _l.Ln7) return false;
		if(Lcounter0_out != _l.Lcounter0_out) return false;
		if(Lcounter1_out != _l.Lcounter1_out) return false;
		if(Lcounter2_out != _l.Lcounter2_out) return false;
		if(Lcounter3_out != _l.Lcounter3_out) return false;
		if(Lcounter4_out != _l.Lcounter4_out) return false;
return true;
}

        inline size_t hash() const {
        size_t seed = global_t::instance().hash_seed();
        
		boost::hash_combine(seed, Istay);
		boost::hash_combine(seed, Icontrollable_reset);
		boost::hash_combine(seed, Ln7);
		boost::hash_combine(seed, Lcounter0_out);
		boost::hash_combine(seed, Lcounter1_out);
		boost::hash_combine(seed, Lcounter2_out);
		boost::hash_combine(seed, Lcounter3_out);
		boost::hash_combine(seed, Lcounter4_out);
return seed;
}

        void output(std::ostream & os) const {
        
		os << "Istay = " << Istay << ",";
		os << "Icontrollable_reset = " << Icontrollable_reset << ",";
		os << "Ln7 = " << Ln7 << ",";
		os << "Lcounter0_out = " << Lcounter0_out << ",";
		os << "Lcounter1_out = " << Lcounter1_out << ",";
		os << "Lcounter2_out = " << Lcounter2_out << ",";
		os << "Lcounter3_out = " << Lcounter3_out << ",";
		os << "Lcounter4_out = " << Lcounter4_out << ",";
	}
};
}
void build_model(syntax::system_t & s){
        	s.name("Mono");
        	s.layout_alloc< syntax::layout_T_alloc_t<monoprocess::layout_t> >();
        
s.add_clock("x_6");
s.add_clock("x_8");
s.add_clock("x_10");
s.add_clock("x_12");
s.add_clock("T");
s.add_label("err");
s.add_label("nothing");
s.add_process("Circuit");
s.add_location("Circuit", "init", "", "", syntax::loc_t::INIT | syntax::loc_t::URGENT);
s.add_location("Circuit", "dead", "", "err");
s.add_location("Circuit", "JustSetIstay", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "init", "JustSetIstay", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Istay=0;;\
                    }
                    
);
s.add_edge("Circuit", "init", "JustSetIstay", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Istay=1;;\
                    }
                    
);
s.add_location("Circuit", "JustSetIcontrollable_reset", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "JustSetIstay", "JustSetIcontrollable_reset", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Icontrollable_reset=0;;\
                    }
                    
);
s.add_edge("Circuit", "JustSetIstay", "JustSetIcontrollable_reset", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Icontrollable_reset=1;;\
                    }
                    
);
s.add_location("Circuit", "UpdatedLn7", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "JustSetIcontrollable_reset", "UpdatedLn7", "", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Ln7==1;;\
        }
        );
s.add_edge("Circuit", "JustSetIcontrollable_reset", "UpdatedLn7", "x_6 <= 1000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Ln7 == 1 && _l.Ln7 != 1;\
        }
        );
s.add_edge("Circuit", "JustSetIcontrollable_reset", "UpdatedLn7", "x_6 <= 1500", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Ln7 == 0 && _l.Ln7 != 1;\
        }
        );
s.add_location("Circuit", "UpdatedLn7_becomes0","x_6<=1000", "");
s.add_location("Circuit", "UpdatedLn7_becomes1","x_6<=1500", "");
s.add_edge("Circuit", "JustSetIcontrollable_reset", "UpdatedLn7_becomes0", "x_6 < 1000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Ln7 == 1 && _l.Ln7 != 1;\
        }
        );
s.add_edge("Circuit", "UpdatedLn7_becomes0", "UpdatedLn7", "x_6 >= 1000", "x_6", "", syntax::layout_true,  [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Ln7 = 1;;\
                    }
                    );
s.add_edge("Circuit", "JustSetIcontrollable_reset", "UpdatedLn7_becomes1", "x_6 < 1500", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Ln7 == 0 && _l.Ln7 != 1;\
        }
        );
s.add_edge("Circuit", "UpdatedLn7_becomes1", "UpdatedLn7", "x_6 >= 1500", "x_6", "", syntax::layout_true,  [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Ln7 = 1;;\
                    }
                    );
s.add_location("Circuit", "UpdatedLcounter0_out", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "UpdatedLn7", "UpdatedLcounter0_out", "", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lcounter0_out==!(!(!((_l.Lcounter0_out) && (_l.Ln7)) && !(_l.Istay)) && !(((_l.Lcounter0_out) && (_l.Ln7)) && (_l.Istay)));;\
        }
        );
s.add_edge("Circuit", "UpdatedLn7", "UpdatedLcounter0_out", "x_8 <= 500", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lcounter0_out == 1 && _l.Lcounter0_out != !(!(!((_l.Lcounter0_out) && (_l.Ln7)) && !(_l.Istay)) && !(((_l.Lcounter0_out) && (_l.Ln7)) && (_l.Istay)));\
        }
        );
s.add_edge("Circuit", "UpdatedLn7", "UpdatedLcounter0_out", "x_8 <= 2000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lcounter0_out == 0 && _l.Lcounter0_out != !(!(!((_l.Lcounter0_out) && (_l.Ln7)) && !(_l.Istay)) && !(((_l.Lcounter0_out) && (_l.Ln7)) && (_l.Istay)));\
        }
        );
s.add_location("Circuit", "UpdatedLcounter0_out_becomes0","x_8<=500", "");
s.add_location("Circuit", "UpdatedLcounter0_out_becomes1","x_8<=2000", "");
s.add_edge("Circuit", "UpdatedLn7", "UpdatedLcounter0_out_becomes0", "x_8 < 500", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lcounter0_out == 1 && _l.Lcounter0_out != !(!(!((_l.Lcounter0_out) && (_l.Ln7)) && !(_l.Istay)) && !(((_l.Lcounter0_out) && (_l.Ln7)) && (_l.Istay)));\
        }
        );
s.add_edge("Circuit", "UpdatedLcounter0_out_becomes0", "UpdatedLcounter0_out", "x_8 >= 500", "x_8", "", syntax::layout_true,  [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Lcounter0_out = !(!(!((_l.Lcounter0_out) && (_l.Ln7)) && !(_l.Istay)) && !(((_l.Lcounter0_out) && (_l.Ln7)) && (_l.Istay)));;\
                    }
                    );
s.add_edge("Circuit", "UpdatedLn7", "UpdatedLcounter0_out_becomes1", "x_8 < 2000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lcounter0_out == 0 && _l.Lcounter0_out != !(!(!((_l.Lcounter0_out) && (_l.Ln7)) && !(_l.Istay)) && !(((_l.Lcounter0_out) && (_l.Ln7)) && (_l.Istay)));\
        }
        );
s.add_edge("Circuit", "UpdatedLcounter0_out_becomes1", "UpdatedLcounter0_out", "x_8 >= 2000", "x_8", "", syntax::layout_true,  [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Lcounter0_out = !(!(!((_l.Lcounter0_out) && (_l.Ln7)) && !(_l.Istay)) && !(((_l.Lcounter0_out) && (_l.Ln7)) && (_l.Istay)));;\
                    }
                    );
s.add_location("Circuit", "UpdatedLcounter1_out", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "UpdatedLcounter0_out", "UpdatedLcounter1_out", "", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lcounter1_out==!(!((((_l.Lcounter0_out) && (_l.Ln7)) && !(_l.Istay)) && !((_l.Lcounter1_out) && (_l.Ln7))) && !(!(((_l.Lcounter0_out) && (_l.Ln7)) && !(_l.Istay)) && ((_l.Lcounter1_out) && (_l.Ln7))));;\
        }
        );
s.add_edge("Circuit", "UpdatedLcounter0_out", "UpdatedLcounter1_out", "x_10 <= 2000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lcounter1_out == 1 && _l.Lcounter1_out != !(!((((_l.Lcounter0_out) && (_l.Ln7)) && !(_l.Istay)) && !((_l.Lcounter1_out) && (_l.Ln7))) && !(!(((_l.Lcounter0_out) && (_l.Ln7)) && !(_l.Istay)) && ((_l.Lcounter1_out) && (_l.Ln7))));\
        }
        );
s.add_edge("Circuit", "UpdatedLcounter0_out", "UpdatedLcounter1_out", "x_10 <= 3000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lcounter1_out == 0 && _l.Lcounter1_out != !(!((((_l.Lcounter0_out) && (_l.Ln7)) && !(_l.Istay)) && !((_l.Lcounter1_out) && (_l.Ln7))) && !(!(((_l.Lcounter0_out) && (_l.Ln7)) && !(_l.Istay)) && ((_l.Lcounter1_out) && (_l.Ln7))));\
        }
        );
s.add_location("Circuit", "UpdatedLcounter1_out_becomes0","x_10<=2000", "");
s.add_location("Circuit", "UpdatedLcounter1_out_becomes1","x_10<=3000", "");
s.add_edge("Circuit", "UpdatedLcounter0_out", "UpdatedLcounter1_out_becomes0", "x_10 < 2000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lcounter1_out == 1 && _l.Lcounter1_out != !(!((((_l.Lcounter0_out) && (_l.Ln7)) && !(_l.Istay)) && !((_l.Lcounter1_out) && (_l.Ln7))) && !(!(((_l.Lcounter0_out) && (_l.Ln7)) && !(_l.Istay)) && ((_l.Lcounter1_out) && (_l.Ln7))));\
        }
        );
s.add_edge("Circuit", "UpdatedLcounter1_out_becomes0", "UpdatedLcounter1_out", "x_10 >= 2000", "x_10", "", syntax::layout_true,  [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Lcounter1_out = !(!((((_l.Lcounter0_out) && (_l.Ln7)) && !(_l.Istay)) && !((_l.Lcounter1_out) && (_l.Ln7))) && !(!(((_l.Lcounter0_out) && (_l.Ln7)) && !(_l.Istay)) && ((_l.Lcounter1_out) && (_l.Ln7))));;\
                    }
                    );
s.add_edge("Circuit", "UpdatedLcounter0_out", "UpdatedLcounter1_out_becomes1", "x_10 < 3000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lcounter1_out == 0 && _l.Lcounter1_out != !(!((((_l.Lcounter0_out) && (_l.Ln7)) && !(_l.Istay)) && !((_l.Lcounter1_out) && (_l.Ln7))) && !(!(((_l.Lcounter0_out) && (_l.Ln7)) && !(_l.Istay)) && ((_l.Lcounter1_out) && (_l.Ln7))));\
        }
        );
s.add_edge("Circuit", "UpdatedLcounter1_out_becomes1", "UpdatedLcounter1_out", "x_10 >= 3000", "x_10", "", syntax::layout_true,  [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Lcounter1_out = !(!((((_l.Lcounter0_out) && (_l.Ln7)) && !(_l.Istay)) && !((_l.Lcounter1_out) && (_l.Ln7))) && !(!(((_l.Lcounter0_out) && (_l.Ln7)) && !(_l.Istay)) && ((_l.Lcounter1_out) && (_l.Ln7))));;\
                    }
                    );
s.add_location("Circuit", "UpdatedLcounter2_out", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "UpdatedLcounter1_out", "UpdatedLcounter2_out", "", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lcounter2_out==!(!(((((_l.Lcounter1_out) && (_l.Ln7)) && ((_l.Lcounter0_out) && (_l.Ln7))) && !(_l.Istay)) && !((_l.Lcounter2_out) && (_l.Ln7))) && !(!((((_l.Lcounter1_out) && (_l.Ln7)) && ((_l.Lcounter0_out) && (_l.Ln7))) && !(_l.Istay)) && ((_l.Lcounter2_out) && (_l.Ln7))));;\
        }
        );
s.add_edge("Circuit", "UpdatedLcounter1_out", "UpdatedLcounter2_out", "x_12 <= 3000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lcounter2_out == 1 && _l.Lcounter2_out != !(!(((((_l.Lcounter1_out) && (_l.Ln7)) && ((_l.Lcounter0_out) && (_l.Ln7))) && !(_l.Istay)) && !((_l.Lcounter2_out) && (_l.Ln7))) && !(!((((_l.Lcounter1_out) && (_l.Ln7)) && ((_l.Lcounter0_out) && (_l.Ln7))) && !(_l.Istay)) && ((_l.Lcounter2_out) && (_l.Ln7))));\
        }
        );
s.add_edge("Circuit", "UpdatedLcounter1_out", "UpdatedLcounter2_out", "x_12 <= 0", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lcounter2_out == 0 && _l.Lcounter2_out != !(!(((((_l.Lcounter1_out) && (_l.Ln7)) && ((_l.Lcounter0_out) && (_l.Ln7))) && !(_l.Istay)) && !((_l.Lcounter2_out) && (_l.Ln7))) && !(!((((_l.Lcounter1_out) && (_l.Ln7)) && ((_l.Lcounter0_out) && (_l.Ln7))) && !(_l.Istay)) && ((_l.Lcounter2_out) && (_l.Ln7))));\
        }
        );
s.add_location("Circuit", "UpdatedLcounter2_out_becomes0","x_12<=3000", "");
s.add_location("Circuit", "UpdatedLcounter2_out_becomes1","x_12<=0", "");
s.add_edge("Circuit", "UpdatedLcounter1_out", "UpdatedLcounter2_out_becomes0", "x_12 < 3000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lcounter2_out == 1 && _l.Lcounter2_out != !(!(((((_l.Lcounter1_out) && (_l.Ln7)) && ((_l.Lcounter0_out) && (_l.Ln7))) && !(_l.Istay)) && !((_l.Lcounter2_out) && (_l.Ln7))) && !(!((((_l.Lcounter1_out) && (_l.Ln7)) && ((_l.Lcounter0_out) && (_l.Ln7))) && !(_l.Istay)) && ((_l.Lcounter2_out) && (_l.Ln7))));\
        }
        );
s.add_edge("Circuit", "UpdatedLcounter2_out_becomes0", "UpdatedLcounter2_out", "x_12 >= 3000", "x_12", "", syntax::layout_true,  [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Lcounter2_out = !(!(((((_l.Lcounter1_out) && (_l.Ln7)) && ((_l.Lcounter0_out) && (_l.Ln7))) && !(_l.Istay)) && !((_l.Lcounter2_out) && (_l.Ln7))) && !(!((((_l.Lcounter1_out) && (_l.Ln7)) && ((_l.Lcounter0_out) && (_l.Ln7))) && !(_l.Istay)) && ((_l.Lcounter2_out) && (_l.Ln7))));;\
                    }
                    );
s.add_edge("Circuit", "UpdatedLcounter2_out_becomes1", "UpdatedLcounter2_out", "x_12 >= 0", "x_12", "", syntax::layout_true,  [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Lcounter2_out = !(!(((((_l.Lcounter1_out) && (_l.Ln7)) && ((_l.Lcounter0_out) && (_l.Ln7))) && !(_l.Istay)) && !((_l.Lcounter2_out) && (_l.Ln7))) && !(!((((_l.Lcounter1_out) && (_l.Ln7)) && ((_l.Lcounter0_out) && (_l.Ln7))) && !(_l.Istay)) && ((_l.Lcounter2_out) && (_l.Ln7))));;\
                    }
                    );
s.add_edge("Circuit", "UpdatedLcounter2_out", "dead", "T>3000", "", "", syntax::layout_true);
s.add_edge("Circuit", "UpdatedLcounter2_out", "init", "T<=3000", "T", "", syntax::layout_true);
s.synchronizer<syntax::asynchronous_product_t>();
}
