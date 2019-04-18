#include <iostream>
        #include "syntax/system.hh"
        #include "syntax/sync_product.hh"
        namespace monoprocess {
        class layout_t : public syntax::layout_t {
        public:
        
	bool Ish_0_;
	bool Ish_1_;
	bool Ish_2_;
	bool Ish_3_;
	bool Icontrollable_do_shift;
	bool Lbenchn13;
	bool Lbenchr_0__out;
	bool Lbenchr_1__out;
	bool Lbenchr_2__out;
	bool Lbenchr_3__out;
	bool Lbenchr_4__out;
	bool Lbenchr_5__out;
	bool Lbenchr_6__out;
	bool Lbenchr_7__out;
	bool Lbenchr_8__out;
	bool Lbenchr_9__out;
	bool Lbenchr_10__out;
	bool Lbenchr_11__out;
	bool Lbenchr_12__out;
	bool Lbenchr_13__out;
	bool Lbenchr_14__out;
	bool Lbenchr_15__out;
	layout_t(){
		Ish_0_ = 0;
		Ish_1_ = 0;
		Ish_2_ = 0;
		Ish_3_ = 0;
		Icontrollable_do_shift = 0;
		Lbenchn13 = 0;
		Lbenchr_0__out = 0;
		Lbenchr_1__out = 0;
		Lbenchr_2__out = 0;
		Lbenchr_3__out = 0;
		Lbenchr_4__out = 0;
		Lbenchr_5__out = 0;
		Lbenchr_6__out = 0;
		Lbenchr_7__out = 0;
		Lbenchr_8__out = 0;
		Lbenchr_9__out = 0;
		Lbenchr_10__out = 0;
		Lbenchr_11__out = 0;
		Lbenchr_12__out = 0;
		Lbenchr_13__out = 0;
		Lbenchr_14__out = 0;
		Lbenchr_15__out = 0;
	}
virtual ~layout_t(){}
layout_t (const layout_t &l) = default;

        inline bool operator == (const syntax::layout_t & l) const {
            monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);
        
		if(Ish_0_ != _l.Ish_0_) return false;
		if(Ish_1_ != _l.Ish_1_) return false;
		if(Ish_2_ != _l.Ish_2_) return false;
		if(Ish_3_ != _l.Ish_3_) return false;
		if(Icontrollable_do_shift != _l.Icontrollable_do_shift) return false;
		if(Lbenchn13 != _l.Lbenchn13) return false;
		if(Lbenchr_0__out != _l.Lbenchr_0__out) return false;
		if(Lbenchr_1__out != _l.Lbenchr_1__out) return false;
		if(Lbenchr_2__out != _l.Lbenchr_2__out) return false;
		if(Lbenchr_3__out != _l.Lbenchr_3__out) return false;
		if(Lbenchr_4__out != _l.Lbenchr_4__out) return false;
		if(Lbenchr_5__out != _l.Lbenchr_5__out) return false;
		if(Lbenchr_6__out != _l.Lbenchr_6__out) return false;
		if(Lbenchr_7__out != _l.Lbenchr_7__out) return false;
		if(Lbenchr_8__out != _l.Lbenchr_8__out) return false;
		if(Lbenchr_9__out != _l.Lbenchr_9__out) return false;
		if(Lbenchr_10__out != _l.Lbenchr_10__out) return false;
		if(Lbenchr_11__out != _l.Lbenchr_11__out) return false;
		if(Lbenchr_12__out != _l.Lbenchr_12__out) return false;
		if(Lbenchr_13__out != _l.Lbenchr_13__out) return false;
		if(Lbenchr_14__out != _l.Lbenchr_14__out) return false;
		if(Lbenchr_15__out != _l.Lbenchr_15__out) return false;
return true;
}

        inline size_t hash() const {
        size_t seed = global_t::instance().hash_seed();
        
		boost::hash_combine(seed, Ish_0_);
		boost::hash_combine(seed, Ish_1_);
		boost::hash_combine(seed, Ish_2_);
		boost::hash_combine(seed, Ish_3_);
		boost::hash_combine(seed, Icontrollable_do_shift);
		boost::hash_combine(seed, Lbenchn13);
		boost::hash_combine(seed, Lbenchr_0__out);
		boost::hash_combine(seed, Lbenchr_1__out);
		boost::hash_combine(seed, Lbenchr_2__out);
		boost::hash_combine(seed, Lbenchr_3__out);
		boost::hash_combine(seed, Lbenchr_4__out);
		boost::hash_combine(seed, Lbenchr_5__out);
		boost::hash_combine(seed, Lbenchr_6__out);
		boost::hash_combine(seed, Lbenchr_7__out);
		boost::hash_combine(seed, Lbenchr_8__out);
		boost::hash_combine(seed, Lbenchr_9__out);
		boost::hash_combine(seed, Lbenchr_10__out);
		boost::hash_combine(seed, Lbenchr_11__out);
		boost::hash_combine(seed, Lbenchr_12__out);
		boost::hash_combine(seed, Lbenchr_13__out);
		boost::hash_combine(seed, Lbenchr_14__out);
		boost::hash_combine(seed, Lbenchr_15__out);
return seed;
}

        void output(std::ostream & os) const {
        
		os << "Ish_0_ = " << Ish_0_ << ",";
		os << "Ish_1_ = " << Ish_1_ << ",";
		os << "Ish_2_ = " << Ish_2_ << ",";
		os << "Ish_3_ = " << Ish_3_ << ",";
		os << "Icontrollable_do_shift = " << Icontrollable_do_shift << ",";
		os << "Lbenchn13 = " << Lbenchn13 << ",";
		os << "Lbenchr_0__out = " << Lbenchr_0__out << ",";
		os << "Lbenchr_1__out = " << Lbenchr_1__out << ",";
		os << "Lbenchr_2__out = " << Lbenchr_2__out << ",";
		os << "Lbenchr_3__out = " << Lbenchr_3__out << ",";
		os << "Lbenchr_4__out = " << Lbenchr_4__out << ",";
		os << "Lbenchr_5__out = " << Lbenchr_5__out << ",";
		os << "Lbenchr_6__out = " << Lbenchr_6__out << ",";
		os << "Lbenchr_7__out = " << Lbenchr_7__out << ",";
		os << "Lbenchr_8__out = " << Lbenchr_8__out << ",";
		os << "Lbenchr_9__out = " << Lbenchr_9__out << ",";
		os << "Lbenchr_10__out = " << Lbenchr_10__out << ",";
		os << "Lbenchr_11__out = " << Lbenchr_11__out << ",";
		os << "Lbenchr_12__out = " << Lbenchr_12__out << ",";
		os << "Lbenchr_13__out = " << Lbenchr_13__out << ",";
		os << "Lbenchr_14__out = " << Lbenchr_14__out << ",";
		os << "Lbenchr_15__out = " << Lbenchr_15__out << ",";
	}
};
}
void build_model(syntax::system_t & s){
        	s.name("Mono");
        	s.layout_alloc< syntax::layout_T_alloc_t<monoprocess::layout_t> >();
        
s.add_clock("x_12");
s.add_clock("x_14");
s.add_clock("x_16");
s.add_clock("x_18");
s.add_clock("T");
s.add_label("err");
s.add_label("nothing");
s.add_process("Circuit");
s.add_location("Circuit", "init", "", "", syntax::loc_t::INIT | syntax::loc_t::URGENT);
s.add_location("Circuit", "dead", "", "err");
s.add_location("Circuit", "JustSetIsh_0_", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "init", "JustSetIsh_0_", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Ish_0_=0;;\
                    }
                    
);
s.add_edge("Circuit", "init", "JustSetIsh_0_", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Ish_0_=1;;\
                    }
                    
);
s.add_location("Circuit", "JustSetIsh_1_", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "JustSetIsh_0_", "JustSetIsh_1_", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Ish_1_=0;;\
                    }
                    
);
s.add_edge("Circuit", "JustSetIsh_0_", "JustSetIsh_1_", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Ish_1_=1;;\
                    }
                    
);
s.add_location("Circuit", "JustSetIsh_2_", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "JustSetIsh_1_", "JustSetIsh_2_", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Ish_2_=0;;\
                    }
                    
);
s.add_edge("Circuit", "JustSetIsh_1_", "JustSetIsh_2_", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Ish_2_=1;;\
                    }
                    
);
s.add_location("Circuit", "JustSetIsh_3_", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "JustSetIsh_2_", "JustSetIsh_3_", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Ish_3_=0;;\
                    }
                    
);
s.add_edge("Circuit", "JustSetIsh_2_", "JustSetIsh_3_", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Ish_3_=1;;\
                    }
                    
);
s.add_location("Circuit", "JustSetIcontrollable_do_shift", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "JustSetIsh_3_", "JustSetIcontrollable_do_shift", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Icontrollable_do_shift=0;;\
                    }
                    
);
s.add_edge("Circuit", "JustSetIsh_3_", "JustSetIcontrollable_do_shift", "", "", "", syntax::layout_true,
 [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Icontrollable_do_shift=1;;\
                    }
                    
);
s.add_location("Circuit", "UpdatedLbenchn13", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "JustSetIcontrollable_do_shift", "UpdatedLbenchn13", "", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lbenchn13==1;;\
        }
        );
s.add_edge("Circuit", "JustSetIcontrollable_do_shift", "UpdatedLbenchn13", "x_12 <= 1000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lbenchn13 == 1 && _l.Lbenchn13 != 1;\
        }
        );
s.add_edge("Circuit", "JustSetIcontrollable_do_shift", "UpdatedLbenchn13", "x_12 <= 1500", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lbenchn13 == 0 && _l.Lbenchn13 != 1;\
        }
        );
s.add_location("Circuit", "UpdatedLbenchn13_becomes0","x_12<=1000", "");
s.add_location("Circuit", "UpdatedLbenchn13_becomes1","x_12<=1500", "");
s.add_edge("Circuit", "JustSetIcontrollable_do_shift", "UpdatedLbenchn13_becomes0", "x_12 < 1000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lbenchn13 == 1 && _l.Lbenchn13 != 1;\
        }
        );
s.add_edge("Circuit", "UpdatedLbenchn13_becomes0", "UpdatedLbenchn13", "x_12 >= 1000", "x_12", "", syntax::layout_true,  [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Lbenchn13 = 1;;\
                    }
                    );
s.add_edge("Circuit", "JustSetIcontrollable_do_shift", "UpdatedLbenchn13_becomes1", "x_12 < 1500", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lbenchn13 == 0 && _l.Lbenchn13 != 1;\
        }
        );
s.add_edge("Circuit", "UpdatedLbenchn13_becomes1", "UpdatedLbenchn13", "x_12 >= 1500", "x_12", "", syntax::layout_true,  [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Lbenchn13 = 1;;\
                    }
                    );
s.add_location("Circuit", "UpdatedLbenchr_0__out", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "UpdatedLbenchn13", "UpdatedLbenchr_0__out", "", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lbenchr_0__out==!(!(!(!(_l.Lbenchr_0__out) && (_l.Lbenchn13)) && !(_l.Icontrollable_do_shift)) && !(!(!(!(!(!(!(!(!(!(!(_l.Lbenchr_0__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_15__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && !(_l.Ish_1_)) && !(!(!(((_l.Lbenchr_14__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_13__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && (_l.Ish_1_))) && !(_l.Ish_2_)) && !(!(!(!(!(((_l.Lbenchr_12__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_11__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && !(_l.Ish_1_)) && !(!(!(((_l.Lbenchr_10__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_9__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && (_l.Ish_1_))) && (_l.Ish_2_))) && !(_l.Ish_3_)) && !(!(!(!(!(!(!(((_l.Lbenchr_8__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_7__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && !(_l.Ish_1_)) && !(!(!(((_l.Lbenchr_6__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_5__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && (_l.Ish_1_))) && !(_l.Ish_2_)) && !(!(!(!(!(((_l.Lbenchr_4__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_3__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && !(_l.Ish_1_)) && !(!(!(((_l.Lbenchr_2__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_1__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && (_l.Ish_1_))) && (_l.Ish_2_))) && (_l.Ish_3_))) && (_l.Icontrollable_do_shift)));;\
        }
        );
s.add_edge("Circuit", "UpdatedLbenchn13", "UpdatedLbenchr_0__out", "x_14 <= 500", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lbenchr_0__out == 1 && _l.Lbenchr_0__out != !(!(!(!(_l.Lbenchr_0__out) && (_l.Lbenchn13)) && !(_l.Icontrollable_do_shift)) && !(!(!(!(!(!(!(!(!(!(!(_l.Lbenchr_0__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_15__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && !(_l.Ish_1_)) && !(!(!(((_l.Lbenchr_14__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_13__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && (_l.Ish_1_))) && !(_l.Ish_2_)) && !(!(!(!(!(((_l.Lbenchr_12__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_11__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && !(_l.Ish_1_)) && !(!(!(((_l.Lbenchr_10__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_9__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && (_l.Ish_1_))) && (_l.Ish_2_))) && !(_l.Ish_3_)) && !(!(!(!(!(!(!(((_l.Lbenchr_8__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_7__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && !(_l.Ish_1_)) && !(!(!(((_l.Lbenchr_6__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_5__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && (_l.Ish_1_))) && !(_l.Ish_2_)) && !(!(!(!(!(((_l.Lbenchr_4__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_3__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && !(_l.Ish_1_)) && !(!(!(((_l.Lbenchr_2__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_1__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && (_l.Ish_1_))) && (_l.Ish_2_))) && (_l.Ish_3_))) && (_l.Icontrollable_do_shift)));\
        }
        );
s.add_edge("Circuit", "UpdatedLbenchn13", "UpdatedLbenchr_0__out", "x_14 <= 2000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lbenchr_0__out == 0 && _l.Lbenchr_0__out != !(!(!(!(_l.Lbenchr_0__out) && (_l.Lbenchn13)) && !(_l.Icontrollable_do_shift)) && !(!(!(!(!(!(!(!(!(!(!(_l.Lbenchr_0__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_15__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && !(_l.Ish_1_)) && !(!(!(((_l.Lbenchr_14__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_13__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && (_l.Ish_1_))) && !(_l.Ish_2_)) && !(!(!(!(!(((_l.Lbenchr_12__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_11__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && !(_l.Ish_1_)) && !(!(!(((_l.Lbenchr_10__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_9__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && (_l.Ish_1_))) && (_l.Ish_2_))) && !(_l.Ish_3_)) && !(!(!(!(!(!(!(((_l.Lbenchr_8__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_7__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && !(_l.Ish_1_)) && !(!(!(((_l.Lbenchr_6__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_5__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && (_l.Ish_1_))) && !(_l.Ish_2_)) && !(!(!(!(!(((_l.Lbenchr_4__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_3__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && !(_l.Ish_1_)) && !(!(!(((_l.Lbenchr_2__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_1__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && (_l.Ish_1_))) && (_l.Ish_2_))) && (_l.Ish_3_))) && (_l.Icontrollable_do_shift)));\
        }
        );
s.add_location("Circuit", "UpdatedLbenchr_0__out_becomes0","x_14<=500", "");
s.add_location("Circuit", "UpdatedLbenchr_0__out_becomes1","x_14<=2000", "");
s.add_edge("Circuit", "UpdatedLbenchn13", "UpdatedLbenchr_0__out_becomes0", "x_14 < 500", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lbenchr_0__out == 1 && _l.Lbenchr_0__out != !(!(!(!(_l.Lbenchr_0__out) && (_l.Lbenchn13)) && !(_l.Icontrollable_do_shift)) && !(!(!(!(!(!(!(!(!(!(!(_l.Lbenchr_0__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_15__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && !(_l.Ish_1_)) && !(!(!(((_l.Lbenchr_14__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_13__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && (_l.Ish_1_))) && !(_l.Ish_2_)) && !(!(!(!(!(((_l.Lbenchr_12__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_11__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && !(_l.Ish_1_)) && !(!(!(((_l.Lbenchr_10__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_9__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && (_l.Ish_1_))) && (_l.Ish_2_))) && !(_l.Ish_3_)) && !(!(!(!(!(!(!(((_l.Lbenchr_8__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_7__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && !(_l.Ish_1_)) && !(!(!(((_l.Lbenchr_6__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_5__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && (_l.Ish_1_))) && !(_l.Ish_2_)) && !(!(!(!(!(((_l.Lbenchr_4__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_3__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && !(_l.Ish_1_)) && !(!(!(((_l.Lbenchr_2__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_1__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && (_l.Ish_1_))) && (_l.Ish_2_))) && (_l.Ish_3_))) && (_l.Icontrollable_do_shift)));\
        }
        );
s.add_edge("Circuit", "UpdatedLbenchr_0__out_becomes0", "UpdatedLbenchr_0__out", "x_14 >= 500", "x_14", "", syntax::layout_true,  [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Lbenchr_0__out = !(!(!(!(_l.Lbenchr_0__out) && (_l.Lbenchn13)) && !(_l.Icontrollable_do_shift)) && !(!(!(!(!(!(!(!(!(!(!(_l.Lbenchr_0__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_15__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && !(_l.Ish_1_)) && !(!(!(((_l.Lbenchr_14__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_13__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && (_l.Ish_1_))) && !(_l.Ish_2_)) && !(!(!(!(!(((_l.Lbenchr_12__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_11__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && !(_l.Ish_1_)) && !(!(!(((_l.Lbenchr_10__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_9__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && (_l.Ish_1_))) && (_l.Ish_2_))) && !(_l.Ish_3_)) && !(!(!(!(!(!(!(((_l.Lbenchr_8__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_7__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && !(_l.Ish_1_)) && !(!(!(((_l.Lbenchr_6__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_5__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && (_l.Ish_1_))) && !(_l.Ish_2_)) && !(!(!(!(!(((_l.Lbenchr_4__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_3__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && !(_l.Ish_1_)) && !(!(!(((_l.Lbenchr_2__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_1__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && (_l.Ish_1_))) && (_l.Ish_2_))) && (_l.Ish_3_))) && (_l.Icontrollable_do_shift)));;\
                    }
                    );
s.add_edge("Circuit", "UpdatedLbenchn13", "UpdatedLbenchr_0__out_becomes1", "x_14 < 2000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lbenchr_0__out == 0 && _l.Lbenchr_0__out != !(!(!(!(_l.Lbenchr_0__out) && (_l.Lbenchn13)) && !(_l.Icontrollable_do_shift)) && !(!(!(!(!(!(!(!(!(!(!(_l.Lbenchr_0__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_15__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && !(_l.Ish_1_)) && !(!(!(((_l.Lbenchr_14__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_13__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && (_l.Ish_1_))) && !(_l.Ish_2_)) && !(!(!(!(!(((_l.Lbenchr_12__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_11__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && !(_l.Ish_1_)) && !(!(!(((_l.Lbenchr_10__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_9__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && (_l.Ish_1_))) && (_l.Ish_2_))) && !(_l.Ish_3_)) && !(!(!(!(!(!(!(((_l.Lbenchr_8__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_7__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && !(_l.Ish_1_)) && !(!(!(((_l.Lbenchr_6__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_5__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && (_l.Ish_1_))) && !(_l.Ish_2_)) && !(!(!(!(!(((_l.Lbenchr_4__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_3__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && !(_l.Ish_1_)) && !(!(!(((_l.Lbenchr_2__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_1__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && (_l.Ish_1_))) && (_l.Ish_2_))) && (_l.Ish_3_))) && (_l.Icontrollable_do_shift)));\
        }
        );
s.add_edge("Circuit", "UpdatedLbenchr_0__out_becomes1", "UpdatedLbenchr_0__out", "x_14 >= 2000", "x_14", "", syntax::layout_true,  [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Lbenchr_0__out = !(!(!(!(_l.Lbenchr_0__out) && (_l.Lbenchn13)) && !(_l.Icontrollable_do_shift)) && !(!(!(!(!(!(!(!(!(!(!(_l.Lbenchr_0__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_15__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && !(_l.Ish_1_)) && !(!(!(((_l.Lbenchr_14__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_13__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && (_l.Ish_1_))) && !(_l.Ish_2_)) && !(!(!(!(!(((_l.Lbenchr_12__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_11__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && !(_l.Ish_1_)) && !(!(!(((_l.Lbenchr_10__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_9__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && (_l.Ish_1_))) && (_l.Ish_2_))) && !(_l.Ish_3_)) && !(!(!(!(!(!(!(((_l.Lbenchr_8__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_7__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && !(_l.Ish_1_)) && !(!(!(((_l.Lbenchr_6__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_5__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && (_l.Ish_1_))) && !(_l.Ish_2_)) && !(!(!(!(!(((_l.Lbenchr_4__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_3__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && !(_l.Ish_1_)) && !(!(!(((_l.Lbenchr_2__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_1__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && (_l.Ish_1_))) && (_l.Ish_2_))) && (_l.Ish_3_))) && (_l.Icontrollable_do_shift)));;\
                    }
                    );
s.add_location("Circuit", "UpdatedLbenchr_1__out", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "UpdatedLbenchr_0__out", "UpdatedLbenchr_1__out", "", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lbenchr_1__out==!(!(((_l.Lbenchr_1__out) && (_l.Lbenchn13)) && !(_l.Icontrollable_do_shift)) && !(!(!(!(!(!(!(!(!(((_l.Lbenchr_1__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(!(!(_l.Lbenchr_0__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && !(_l.Ish_1_)) && !(!(!(((_l.Lbenchr_15__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_14__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && (_l.Ish_1_))) && !(_l.Ish_2_)) && !(!(!(!(!(((_l.Lbenchr_13__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_12__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && !(_l.Ish_1_)) && !(!(!(((_l.Lbenchr_11__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_10__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && (_l.Ish_1_))) && (_l.Ish_2_))) && !(_l.Ish_3_)) && !(!(!(!(!(!(!(((_l.Lbenchr_9__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_8__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && !(_l.Ish_1_)) && !(!(!(((_l.Lbenchr_7__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_6__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && (_l.Ish_1_))) && !(_l.Ish_2_)) && !(!(!(!(!(((_l.Lbenchr_5__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_4__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && !(_l.Ish_1_)) && !(!(!(((_l.Lbenchr_3__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_2__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && (_l.Ish_1_))) && (_l.Ish_2_))) && (_l.Ish_3_))) && (_l.Icontrollable_do_shift)));;\
        }
        );
s.add_edge("Circuit", "UpdatedLbenchr_0__out", "UpdatedLbenchr_1__out", "x_16 <= 2000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lbenchr_1__out == 1 && _l.Lbenchr_1__out != !(!(((_l.Lbenchr_1__out) && (_l.Lbenchn13)) && !(_l.Icontrollable_do_shift)) && !(!(!(!(!(!(!(!(!(((_l.Lbenchr_1__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(!(!(_l.Lbenchr_0__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && !(_l.Ish_1_)) && !(!(!(((_l.Lbenchr_15__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_14__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && (_l.Ish_1_))) && !(_l.Ish_2_)) && !(!(!(!(!(((_l.Lbenchr_13__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_12__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && !(_l.Ish_1_)) && !(!(!(((_l.Lbenchr_11__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_10__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && (_l.Ish_1_))) && (_l.Ish_2_))) && !(_l.Ish_3_)) && !(!(!(!(!(!(!(((_l.Lbenchr_9__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_8__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && !(_l.Ish_1_)) && !(!(!(((_l.Lbenchr_7__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_6__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && (_l.Ish_1_))) && !(_l.Ish_2_)) && !(!(!(!(!(((_l.Lbenchr_5__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_4__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && !(_l.Ish_1_)) && !(!(!(((_l.Lbenchr_3__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_2__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && (_l.Ish_1_))) && (_l.Ish_2_))) && (_l.Ish_3_))) && (_l.Icontrollable_do_shift)));\
        }
        );
s.add_edge("Circuit", "UpdatedLbenchr_0__out", "UpdatedLbenchr_1__out", "x_16 <= 3000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lbenchr_1__out == 0 && _l.Lbenchr_1__out != !(!(((_l.Lbenchr_1__out) && (_l.Lbenchn13)) && !(_l.Icontrollable_do_shift)) && !(!(!(!(!(!(!(!(!(((_l.Lbenchr_1__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(!(!(_l.Lbenchr_0__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && !(_l.Ish_1_)) && !(!(!(((_l.Lbenchr_15__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_14__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && (_l.Ish_1_))) && !(_l.Ish_2_)) && !(!(!(!(!(((_l.Lbenchr_13__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_12__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && !(_l.Ish_1_)) && !(!(!(((_l.Lbenchr_11__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_10__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && (_l.Ish_1_))) && (_l.Ish_2_))) && !(_l.Ish_3_)) && !(!(!(!(!(!(!(((_l.Lbenchr_9__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_8__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && !(_l.Ish_1_)) && !(!(!(((_l.Lbenchr_7__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_6__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && (_l.Ish_1_))) && !(_l.Ish_2_)) && !(!(!(!(!(((_l.Lbenchr_5__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_4__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && !(_l.Ish_1_)) && !(!(!(((_l.Lbenchr_3__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_2__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && (_l.Ish_1_))) && (_l.Ish_2_))) && (_l.Ish_3_))) && (_l.Icontrollable_do_shift)));\
        }
        );
s.add_location("Circuit", "UpdatedLbenchr_1__out_becomes0","x_16<=2000", "");
s.add_location("Circuit", "UpdatedLbenchr_1__out_becomes1","x_16<=3000", "");
s.add_edge("Circuit", "UpdatedLbenchr_0__out", "UpdatedLbenchr_1__out_becomes0", "x_16 < 2000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lbenchr_1__out == 1 && _l.Lbenchr_1__out != !(!(((_l.Lbenchr_1__out) && (_l.Lbenchn13)) && !(_l.Icontrollable_do_shift)) && !(!(!(!(!(!(!(!(!(((_l.Lbenchr_1__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(!(!(_l.Lbenchr_0__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && !(_l.Ish_1_)) && !(!(!(((_l.Lbenchr_15__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_14__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && (_l.Ish_1_))) && !(_l.Ish_2_)) && !(!(!(!(!(((_l.Lbenchr_13__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_12__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && !(_l.Ish_1_)) && !(!(!(((_l.Lbenchr_11__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_10__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && (_l.Ish_1_))) && (_l.Ish_2_))) && !(_l.Ish_3_)) && !(!(!(!(!(!(!(((_l.Lbenchr_9__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_8__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && !(_l.Ish_1_)) && !(!(!(((_l.Lbenchr_7__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_6__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && (_l.Ish_1_))) && !(_l.Ish_2_)) && !(!(!(!(!(((_l.Lbenchr_5__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_4__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && !(_l.Ish_1_)) && !(!(!(((_l.Lbenchr_3__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_2__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && (_l.Ish_1_))) && (_l.Ish_2_))) && (_l.Ish_3_))) && (_l.Icontrollable_do_shift)));\
        }
        );
s.add_edge("Circuit", "UpdatedLbenchr_1__out_becomes0", "UpdatedLbenchr_1__out", "x_16 >= 2000", "x_16", "", syntax::layout_true,  [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Lbenchr_1__out = !(!(((_l.Lbenchr_1__out) && (_l.Lbenchn13)) && !(_l.Icontrollable_do_shift)) && !(!(!(!(!(!(!(!(!(((_l.Lbenchr_1__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(!(!(_l.Lbenchr_0__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && !(_l.Ish_1_)) && !(!(!(((_l.Lbenchr_15__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_14__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && (_l.Ish_1_))) && !(_l.Ish_2_)) && !(!(!(!(!(((_l.Lbenchr_13__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_12__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && !(_l.Ish_1_)) && !(!(!(((_l.Lbenchr_11__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_10__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && (_l.Ish_1_))) && (_l.Ish_2_))) && !(_l.Ish_3_)) && !(!(!(!(!(!(!(((_l.Lbenchr_9__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_8__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && !(_l.Ish_1_)) && !(!(!(((_l.Lbenchr_7__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_6__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && (_l.Ish_1_))) && !(_l.Ish_2_)) && !(!(!(!(!(((_l.Lbenchr_5__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_4__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && !(_l.Ish_1_)) && !(!(!(((_l.Lbenchr_3__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_2__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && (_l.Ish_1_))) && (_l.Ish_2_))) && (_l.Ish_3_))) && (_l.Icontrollable_do_shift)));;\
                    }
                    );
s.add_edge("Circuit", "UpdatedLbenchr_0__out", "UpdatedLbenchr_1__out_becomes1", "x_16 < 3000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lbenchr_1__out == 0 && _l.Lbenchr_1__out != !(!(((_l.Lbenchr_1__out) && (_l.Lbenchn13)) && !(_l.Icontrollable_do_shift)) && !(!(!(!(!(!(!(!(!(((_l.Lbenchr_1__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(!(!(_l.Lbenchr_0__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && !(_l.Ish_1_)) && !(!(!(((_l.Lbenchr_15__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_14__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && (_l.Ish_1_))) && !(_l.Ish_2_)) && !(!(!(!(!(((_l.Lbenchr_13__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_12__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && !(_l.Ish_1_)) && !(!(!(((_l.Lbenchr_11__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_10__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && (_l.Ish_1_))) && (_l.Ish_2_))) && !(_l.Ish_3_)) && !(!(!(!(!(!(!(((_l.Lbenchr_9__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_8__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && !(_l.Ish_1_)) && !(!(!(((_l.Lbenchr_7__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_6__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && (_l.Ish_1_))) && !(_l.Ish_2_)) && !(!(!(!(!(((_l.Lbenchr_5__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_4__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && !(_l.Ish_1_)) && !(!(!(((_l.Lbenchr_3__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_2__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && (_l.Ish_1_))) && (_l.Ish_2_))) && (_l.Ish_3_))) && (_l.Icontrollable_do_shift)));\
        }
        );
s.add_edge("Circuit", "UpdatedLbenchr_1__out_becomes1", "UpdatedLbenchr_1__out", "x_16 >= 3000", "x_16", "", syntax::layout_true,  [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Lbenchr_1__out = !(!(((_l.Lbenchr_1__out) && (_l.Lbenchn13)) && !(_l.Icontrollable_do_shift)) && !(!(!(!(!(!(!(!(!(((_l.Lbenchr_1__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(!(!(_l.Lbenchr_0__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && !(_l.Ish_1_)) && !(!(!(((_l.Lbenchr_15__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_14__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && (_l.Ish_1_))) && !(_l.Ish_2_)) && !(!(!(!(!(((_l.Lbenchr_13__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_12__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && !(_l.Ish_1_)) && !(!(!(((_l.Lbenchr_11__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_10__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && (_l.Ish_1_))) && (_l.Ish_2_))) && !(_l.Ish_3_)) && !(!(!(!(!(!(!(((_l.Lbenchr_9__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_8__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && !(_l.Ish_1_)) && !(!(!(((_l.Lbenchr_7__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_6__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && (_l.Ish_1_))) && !(_l.Ish_2_)) && !(!(!(!(!(((_l.Lbenchr_5__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_4__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && !(_l.Ish_1_)) && !(!(!(((_l.Lbenchr_3__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_2__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && (_l.Ish_1_))) && (_l.Ish_2_))) && (_l.Ish_3_))) && (_l.Icontrollable_do_shift)));;\
                    }
                    );
s.add_location("Circuit", "UpdatedLbenchr_2__out", "", "", syntax::loc_t::URGENT);
s.add_edge("Circuit", "UpdatedLbenchr_1__out", "UpdatedLbenchr_2__out", "", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lbenchr_2__out==!(!(((_l.Lbenchr_2__out) && (_l.Lbenchn13)) && !(_l.Icontrollable_do_shift)) && !(!(!(!(!(!(!(!(!(((_l.Lbenchr_2__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_1__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && !(_l.Ish_1_)) && !(!(!(!(!(_l.Lbenchr_0__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_15__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && (_l.Ish_1_))) && !(_l.Ish_2_)) && !(!(!(!(!(((_l.Lbenchr_14__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_13__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && !(_l.Ish_1_)) && !(!(!(((_l.Lbenchr_12__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_11__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && (_l.Ish_1_))) && (_l.Ish_2_))) && !(_l.Ish_3_)) && !(!(!(!(!(!(!(((_l.Lbenchr_10__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_9__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && !(_l.Ish_1_)) && !(!(!(((_l.Lbenchr_8__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_7__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && (_l.Ish_1_))) && !(_l.Ish_2_)) && !(!(!(!(!(((_l.Lbenchr_6__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_5__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && !(_l.Ish_1_)) && !(!(!(((_l.Lbenchr_4__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_3__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && (_l.Ish_1_))) && (_l.Ish_2_))) && (_l.Ish_3_))) && (_l.Icontrollable_do_shift)));;\
        }
        );
s.add_edge("Circuit", "UpdatedLbenchr_1__out", "UpdatedLbenchr_2__out", "x_18 <= 3000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lbenchr_2__out == 1 && _l.Lbenchr_2__out != !(!(((_l.Lbenchr_2__out) && (_l.Lbenchn13)) && !(_l.Icontrollable_do_shift)) && !(!(!(!(!(!(!(!(!(((_l.Lbenchr_2__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_1__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && !(_l.Ish_1_)) && !(!(!(!(!(_l.Lbenchr_0__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_15__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && (_l.Ish_1_))) && !(_l.Ish_2_)) && !(!(!(!(!(((_l.Lbenchr_14__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_13__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && !(_l.Ish_1_)) && !(!(!(((_l.Lbenchr_12__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_11__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && (_l.Ish_1_))) && (_l.Ish_2_))) && !(_l.Ish_3_)) && !(!(!(!(!(!(!(((_l.Lbenchr_10__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_9__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && !(_l.Ish_1_)) && !(!(!(((_l.Lbenchr_8__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_7__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && (_l.Ish_1_))) && !(_l.Ish_2_)) && !(!(!(!(!(((_l.Lbenchr_6__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_5__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && !(_l.Ish_1_)) && !(!(!(((_l.Lbenchr_4__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_3__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && (_l.Ish_1_))) && (_l.Ish_2_))) && (_l.Ish_3_))) && (_l.Icontrollable_do_shift)));\
        }
        );
s.add_edge("Circuit", "UpdatedLbenchr_1__out", "UpdatedLbenchr_2__out", "x_18 <= 0", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lbenchr_2__out == 0 && _l.Lbenchr_2__out != !(!(((_l.Lbenchr_2__out) && (_l.Lbenchn13)) && !(_l.Icontrollable_do_shift)) && !(!(!(!(!(!(!(!(!(((_l.Lbenchr_2__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_1__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && !(_l.Ish_1_)) && !(!(!(!(!(_l.Lbenchr_0__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_15__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && (_l.Ish_1_))) && !(_l.Ish_2_)) && !(!(!(!(!(((_l.Lbenchr_14__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_13__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && !(_l.Ish_1_)) && !(!(!(((_l.Lbenchr_12__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_11__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && (_l.Ish_1_))) && (_l.Ish_2_))) && !(_l.Ish_3_)) && !(!(!(!(!(!(!(((_l.Lbenchr_10__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_9__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && !(_l.Ish_1_)) && !(!(!(((_l.Lbenchr_8__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_7__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && (_l.Ish_1_))) && !(_l.Ish_2_)) && !(!(!(!(!(((_l.Lbenchr_6__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_5__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && !(_l.Ish_1_)) && !(!(!(((_l.Lbenchr_4__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_3__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && (_l.Ish_1_))) && (_l.Ish_2_))) && (_l.Ish_3_))) && (_l.Icontrollable_do_shift)));\
        }
        );
s.add_location("Circuit", "UpdatedLbenchr_2__out_becomes0","x_18<=3000", "");
s.add_location("Circuit", "UpdatedLbenchr_2__out_becomes1","x_18<=0", "");
s.add_edge("Circuit", "UpdatedLbenchr_1__out", "UpdatedLbenchr_2__out_becomes0", "x_18 < 3000", "", "", 
        [](syntax::layout_t const & l){\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\
        return _l.Lbenchr_2__out == 1 && _l.Lbenchr_2__out != !(!(((_l.Lbenchr_2__out) && (_l.Lbenchn13)) && !(_l.Icontrollable_do_shift)) && !(!(!(!(!(!(!(!(!(((_l.Lbenchr_2__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_1__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && !(_l.Ish_1_)) && !(!(!(!(!(_l.Lbenchr_0__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_15__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && (_l.Ish_1_))) && !(_l.Ish_2_)) && !(!(!(!(!(((_l.Lbenchr_14__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_13__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && !(_l.Ish_1_)) && !(!(!(((_l.Lbenchr_12__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_11__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && (_l.Ish_1_))) && (_l.Ish_2_))) && !(_l.Ish_3_)) && !(!(!(!(!(!(!(((_l.Lbenchr_10__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_9__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && !(_l.Ish_1_)) && !(!(!(((_l.Lbenchr_8__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_7__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && (_l.Ish_1_))) && !(_l.Ish_2_)) && !(!(!(!(!(((_l.Lbenchr_6__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_5__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && !(_l.Ish_1_)) && !(!(!(((_l.Lbenchr_4__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_3__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && (_l.Ish_1_))) && (_l.Ish_2_))) && (_l.Ish_3_))) && (_l.Icontrollable_do_shift)));\
        }
        );
s.add_edge("Circuit", "UpdatedLbenchr_2__out_becomes0", "UpdatedLbenchr_2__out", "x_18 >= 3000", "x_18", "", syntax::layout_true,  [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Lbenchr_2__out = !(!(((_l.Lbenchr_2__out) && (_l.Lbenchn13)) && !(_l.Icontrollable_do_shift)) && !(!(!(!(!(!(!(!(!(((_l.Lbenchr_2__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_1__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && !(_l.Ish_1_)) && !(!(!(!(!(_l.Lbenchr_0__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_15__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && (_l.Ish_1_))) && !(_l.Ish_2_)) && !(!(!(!(!(((_l.Lbenchr_14__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_13__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && !(_l.Ish_1_)) && !(!(!(((_l.Lbenchr_12__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_11__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && (_l.Ish_1_))) && (_l.Ish_2_))) && !(_l.Ish_3_)) && !(!(!(!(!(!(!(((_l.Lbenchr_10__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_9__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && !(_l.Ish_1_)) && !(!(!(((_l.Lbenchr_8__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_7__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && (_l.Ish_1_))) && !(_l.Ish_2_)) && !(!(!(!(!(((_l.Lbenchr_6__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_5__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && !(_l.Ish_1_)) && !(!(!(((_l.Lbenchr_4__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_3__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && (_l.Ish_1_))) && (_l.Ish_2_))) && (_l.Ish_3_))) && (_l.Icontrollable_do_shift)));;\
                    }
                    );
s.add_edge("Circuit", "UpdatedLbenchr_2__out_becomes1", "UpdatedLbenchr_2__out", "x_18 >= 0", "x_18", "", syntax::layout_true,  [](syntax::layout_t  & l){\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\
                       _l.Lbenchr_2__out = !(!(((_l.Lbenchr_2__out) && (_l.Lbenchn13)) && !(_l.Icontrollable_do_shift)) && !(!(!(!(!(!(!(!(!(((_l.Lbenchr_2__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_1__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && !(_l.Ish_1_)) && !(!(!(!(!(_l.Lbenchr_0__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_15__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && (_l.Ish_1_))) && !(_l.Ish_2_)) && !(!(!(!(!(((_l.Lbenchr_14__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_13__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && !(_l.Ish_1_)) && !(!(!(((_l.Lbenchr_12__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_11__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && (_l.Ish_1_))) && (_l.Ish_2_))) && !(_l.Ish_3_)) && !(!(!(!(!(!(!(((_l.Lbenchr_10__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_9__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && !(_l.Ish_1_)) && !(!(!(((_l.Lbenchr_8__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_7__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && (_l.Ish_1_))) && !(_l.Ish_2_)) && !(!(!(!(!(((_l.Lbenchr_6__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_5__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && !(_l.Ish_1_)) && !(!(!(((_l.Lbenchr_4__out) && (_l.Lbenchn13)) && !(_l.Ish_0_)) && !(((_l.Lbenchr_3__out) && (_l.Lbenchn13)) && (_l.Ish_0_))) && (_l.Ish_1_))) && (_l.Ish_2_))) && (_l.Ish_3_))) && (_l.Icontrollable_do_shift)));;\
                    }
                    );
s.add_edge("Circuit", "UpdatedLbenchr_2__out", "dead", "T>2000", "", "", syntax::layout_true);
s.add_edge("Circuit", "UpdatedLbenchr_2__out", "init", "T<=2000", "T", "", syntax::layout_true);
s.synchronizer<syntax::asynchronous_product_t>();
}
