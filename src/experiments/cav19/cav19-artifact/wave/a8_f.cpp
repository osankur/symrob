#include <iostream>
#include "syntax/system.hh"
#include "syntax/sync_product.hh"
namespace wave{
  class layout_t : public syntax::layout_t {
  public:
        
	char out0;
	char b0_0;
	char b0_1;
	char out1;
	char out2;
	char out3;
	char b3_0;
	char b3_1;
	char out4;
	char b4_0;
	char b4_1;
	char out5;
	char b5_0;
	char b5_1;
	char out6;
	char b6_0;
	char b6_1;
	char b6_2;
	char b6_3;
	char b6_4;
	char out7;
	char out8;
	char out9;
layout_t() {
	out0 = 2;
	b0_0 = 2;
	b0_1 = 2;
	out1 = 2;
	out2 = 2;
	out3 = 2;
	b3_0 = 2;
	b3_1 = 2;
	out4 = 2;
	b4_0 = 2;
	b4_1 = 2;
	out5 = 2;
	b5_0 = 2;
	b5_1 = 2;
	out6 = 2;
	b6_0 = 2;
	b6_1 = 2;
	b6_2 = 2;
	b6_3 = 2;
	b6_4 = 2;
	out7 = 2;
	out8 = 2;
	out9 = 2;

    }

    virtual ~layout_t() {
    }

    layout_t(const layout_t & l)  = default;

    inline bool operator == (const syntax::layout_t & l) const {
      wave::layout_t const & _l = CAST(wave::layout_t const &, l);
        
	if (out0 != _l.out0) return false;
	if(b0_0 != _l.b0_0) return false;
	if(b0_1 != _l.b0_1) return false;
	if (out1 != _l.out1) return false;
	if (out2 != _l.out2) return false;
	if (out3 != _l.out3) return false;
	if(b3_0 != _l.b3_0) return false;
	if(b3_1 != _l.b3_1) return false;
	if (out4 != _l.out4) return false;
	if(b4_0 != _l.b4_0) return false;
	if(b4_1 != _l.b4_1) return false;
	if (out5 != _l.out5) return false;
	if(b5_0 != _l.b5_0) return false;
	if(b5_1 != _l.b5_1) return false;
	if (out6 != _l.out6) return false;
	if(b6_0 != _l.b6_0) return false;
	if(b6_1 != _l.b6_1) return false;
	if(b6_2 != _l.b6_2) return false;
	if(b6_3 != _l.b6_3) return false;
	if(b6_4 != _l.b6_4) return false;
	if (out7 != _l.out7) return false;
	if (out8 != _l.out8) return false;
	if (out9 != _l.out9) return false;

        return true;
    }

    inline size_t hash() const {
      size_t seed = global_t::instance().hash_seed();
        
	boost::hash_combine(seed, out0);
	boost::hash_combine(seed, b0_0);
	boost::hash_combine(seed, b0_1);
	boost::hash_combine(seed, out1);
	boost::hash_combine(seed, out2);
	boost::hash_combine(seed, out3);
	boost::hash_combine(seed, b3_0);
	boost::hash_combine(seed, b3_1);
	boost::hash_combine(seed, out4);
	boost::hash_combine(seed, b4_0);
	boost::hash_combine(seed, b4_1);
	boost::hash_combine(seed, out5);
	boost::hash_combine(seed, b5_0);
	boost::hash_combine(seed, b5_1);
	boost::hash_combine(seed, out6);
	boost::hash_combine(seed, b6_0);
	boost::hash_combine(seed, b6_1);
	boost::hash_combine(seed, b6_2);
	boost::hash_combine(seed, b6_3);
	boost::hash_combine(seed, b6_4);
	boost::hash_combine(seed, out7);
	boost::hash_combine(seed, out8);
	boost::hash_combine(seed, out9);

      return seed;
    }

    void output(std::ostream & os) const {
        
	os << "out0=" << out0 << ",";
	os << "b0_0=" << b0_0 << ",";
	os << "b0_1=" << b0_1 << ",";
	os << "out1=" << out1 << ",";
	os << "out2=" << out2 << ",";
	os << "out3=" << out3 << ",";
	os << "b3_0=" << b3_0 << ",";
	os << "b3_1=" << b3_1 << ",";
	os << "out4=" << out4 << ",";
	os << "b4_0=" << b4_0 << ",";
	os << "b4_1=" << b4_1 << ",";
	os << "out5=" << out5 << ",";
	os << "b5_0=" << b5_0 << ",";
	os << "b5_1=" << b5_1 << ",";
	os << "out6=" << out6 << ",";
	os << "b6_1=" << b6_0 << ",";
	os << "b6_1=" << b6_1 << ",";
	os << "b6_1=" << b6_2 << ",";
	os << "b6_1=" << b6_3 << ",";
	os << "b6_1=" << b6_4 << ",";
	os << "out7=" << out7 << ",";
	os << "out8=" << out8 << ",";
	os << "out9=" << out9 << ",";

    }
  };

}
        
void build_model(syntax::system_t & s){
s.name("Wave");
s.layout_alloc< syntax::layout_T_alloc_t<wave::layout_t> >();
s.add_clock("t");
s.add_clock("x0");
s.add_clock("x1");
s.add_clock("x2");
s.add_clock("x3");
s.add_clock("x4");
s.add_clock("x5");
s.add_clock("x6");
s.add_label("err");
s.add_label("unreachable");
s.add_process("Node0");
s.add_location("Node0", "down", "x0<=100", "", syntax::loc_t::INIT);
s.add_location("Node0", "up", "x0<=300", "");
s.add_edge("Node0", "down", "up", "x0>=100 && x0 <= 300 && t <= 1000", "", "",
                    [](syntax::layout_t const & l){
                       wave::layout_t const & _l = CAST(wave::layout_t const &, l);
                       return _l.out6 < 2 && _l.out5 < 2 && _l.out6 == 1 && _l.out5 == 1;
                    }
                    ,
                    [](syntax::layout_t  & l){
                       wave::layout_t & _l = CAST(wave::layout_t &, l);
                       _l.out0 = 1;
                    }
                    );
s.add_edge("Node0", "down", "down", "t>1000", "", "", syntax::layout_true, [](syntax::layout_t  & l){wave::layout_t & _l = CAST(wave::layout_t &, l);
_l.out0 = 2;

_l.out1 = 2;

_l.out2 = 2;

_l.out3 = 2;

_l.out4 = 2;

_l.out5 = 2;

_l.out6 = 2;


                    });
                    
s.add_edge("Node0", "down", "up", "x0>=100 && x0<=300", "", "", 
                    [](syntax::layout_t const & l){
                       wave::layout_t const & _l = CAST(wave::layout_t const &, l);
                       return _l.out6 < 2 && _l.out5 < 2 && (_l.out6 == 1 && _l.out5 == 1)==0;
                    }
                    , 
                    [](syntax::layout_t  & l){
                       wave::layout_t & _l = CAST(wave::layout_t &, l);
                       _l.out0 = 0;
                    }
                    );
s.add_edge("Node0", "down", "down", "x0 == 100", "x0", "", 
                    [](syntax::layout_t const & l){
                       wave::layout_t const & _l = CAST(wave::layout_t const &, l);
                       return (_l.out6 != 2 &&  _l.out5 != 2) == 0;
                    }
                    );
s.add_edge("Node0", "up", "down", "x0 <= 300", "x0", "",syntax::layout_true,
                    [](syntax::layout_t  & l){
                       wave::layout_t & _l = CAST(wave::layout_t &, l);
                       _l.out0 = 2;
                    }
                    );
s.add_location("Node0", "err", "", "err");
s.add_edge("Node0", "up", "err", "", "", "", 
                    [](syntax::layout_t const & l){
                       wave::layout_t const & _l = CAST(wave::layout_t const &, l);
                       return _l.out0;
                    }
                    );
s.add_process("Node1");
s.add_location("Node1", "down", "x1<=50", "", syntax::loc_t::INIT);
s.add_location("Node1", "up", "x1<=400", "");
s.add_edge("Node1", "down", "up", "x1>=50 && x1<=400", "", "", 
                    [](syntax::layout_t const & l){
                       wave::layout_t const & _l = CAST(wave::layout_t const &, l);
                       return _l.out7 < 2 && (1-_l.out7)==1;
                    }
                    , 
                    [](syntax::layout_t  & l){
                       wave::layout_t & _l = CAST(wave::layout_t &, l);
                       _l.out1 = 1;
                    }
                    );
s.add_edge("Node1", "down", "up", "x1>=50 && x1<=400", "", "", 
                    [](syntax::layout_t const & l){
                       wave::layout_t const & _l = CAST(wave::layout_t const &, l);
                       return _l.out7 < 2 && (1-_l.out7) ==0;
                    }
                    , 
                    [](syntax::layout_t  & l){
                       wave::layout_t & _l = CAST(wave::layout_t &, l);
                       _l.out1 = 0;
                    }
                    );
s.add_edge("Node1", "down", "down", "x1 == 50", "x1", "", 
                    [](syntax::layout_t const & l){
                       wave::layout_t const & _l = CAST(wave::layout_t const &, l);
                       return _l.out7 == 2;
                    }
                    );
s.add_edge("Node1", "up", "down", "x1 <= 400", "x1", "",syntax::layout_true,
                    [](syntax::layout_t  & l){
                       wave::layout_t & _l = CAST(wave::layout_t &, l);
                       _l.out1 = 2;
                    }
                    );
s.add_process("Node2");
s.add_location("Node2", "down", "x2<=200", "", syntax::loc_t::INIT);
s.add_location("Node2", "up", "x2<=600", "");
s.add_edge("Node2", "down", "up", "x2>=200 && x2<=600", "", "", 
                    [](syntax::layout_t const & l){
                       wave::layout_t const & _l = CAST(wave::layout_t const &, l);
                       return _l.out8 < 2 && (1-_l.out8)==1;
                    }
                    , 
                    [](syntax::layout_t  & l){
                       wave::layout_t & _l = CAST(wave::layout_t &, l);
                       _l.out2 = 1;
                    }
                    );
s.add_edge("Node2", "down", "up", "x2>=200 && x2<=600", "", "", 
                    [](syntax::layout_t const & l){
                       wave::layout_t const & _l = CAST(wave::layout_t const &, l);
                       return _l.out8 < 2 && (1-_l.out8) ==0;
                    }
                    , 
                    [](syntax::layout_t  & l){
                       wave::layout_t & _l = CAST(wave::layout_t &, l);
                       _l.out2 = 0;
                    }
                    );
s.add_edge("Node2", "down", "down", "x2 == 200", "x2", "", 
                    [](syntax::layout_t const & l){
                       wave::layout_t const & _l = CAST(wave::layout_t const &, l);
                       return _l.out8 == 2;
                    }
                    );
s.add_edge("Node2", "up", "down", "x2 <= 600", "x2", "",syntax::layout_true,
                    [](syntax::layout_t  & l){
                       wave::layout_t & _l = CAST(wave::layout_t &, l);
                       _l.out2 = 2;
                    }
                    );
s.add_process("Node3");
s.add_location("Node3", "down", "x3<=300", "", syntax::loc_t::INIT);
s.add_location("Node3", "up", "x3<=0", "");
s.add_edge("Node3", "down", "up", "x3>=300 && x3<=0", "", "", 
                    [](syntax::layout_t const & l){
                       wave::layout_t const & _l = CAST(wave::layout_t const &, l);
                       return _l.out7 < 2 && _l.out9 < 2 && _l.out7 == 1 && _l.out9 == 1;
                    }
                    , 
                    [](syntax::layout_t  & l){
                       wave::layout_t & _l = CAST(wave::layout_t &, l);
                       _l.out3 = 1;
                    }
                    );
s.add_edge("Node3", "down", "up", "x3>=300 && x3<=0", "", "", 
                    [](syntax::layout_t const & l){
                       wave::layout_t const & _l = CAST(wave::layout_t const &, l);
                       return _l.out7 < 2 && _l.out9 < 2 && (_l.out7 == 1 && _l.out9 == 1)==0;
                    }
                    , 
                    [](syntax::layout_t  & l){
                       wave::layout_t & _l = CAST(wave::layout_t &, l);
                       _l.out3 = 0;
                    }
                    );
s.add_edge("Node3", "down", "down", "x3 == 300", "x3", "", 
                    [](syntax::layout_t const & l){
                       wave::layout_t const & _l = CAST(wave::layout_t const &, l);
                       return (_l.out7 != 2 &&  _l.out9 != 2) == 0;
                    }
                    );
s.add_edge("Node3", "up", "down", "x3 <= 0", "x3", "",syntax::layout_true,
                    [](syntax::layout_t  & l){
                       wave::layout_t & _l = CAST(wave::layout_t &, l);
                       _l.out3 = 2;
                    }
                    );
s.add_process("Node4");
s.add_location("Node4", "down", "x4<=250", "", syntax::loc_t::INIT);
s.add_location("Node4", "up", "x4<=0", "");
s.add_edge("Node4", "down", "up", "x4>=250 && x4<=0", "", "", 
                    [](syntax::layout_t const & l){
                       wave::layout_t const & _l = CAST(wave::layout_t const &, l);
                       return _l.out3 < 2 && _l.out1 < 2 && (_l.out3 == 0 && _l.out1 == 0) == 0;
                    }
                    , 
                    [](syntax::layout_t  & l){
                       wave::layout_t & _l = CAST(wave::layout_t &, l);
                       _l.out4 = 1;
                    }
                    );
s.add_edge("Node4", "down", "up", "x4>=250 && x4<=0", "", "", 
                    [](syntax::layout_t const & l){
                       wave::layout_t const & _l = CAST(wave::layout_t const &, l);
                       return _l.out3 < 2 && _l.out1 < 2 && _l.out3 == 0 && _l.out1 == 0;
                    }
                    , 
                    [](syntax::layout_t  & l){
                       wave::layout_t & _l = CAST(wave::layout_t &, l);
                       _l.out4 = 0;
                    }
                    );
s.add_edge("Node4", "down", "down", "x4 == 250", "x4", "", 
                    [](syntax::layout_t const & l){
                       wave::layout_t const & _l = CAST(wave::layout_t const &, l);
                       return (_l.out3 != 2 &&  _l.out1 != 2) == 0;
                    }
                    );
s.add_edge("Node4", "up", "down", "x4 <= 0", "x4", "",syntax::layout_true,
                    [](syntax::layout_t  & l){
                       wave::layout_t & _l = CAST(wave::layout_t &, l);
                       _l.out4 = 2;
                    }
                    );
s.add_process("Node5");
s.add_location("Node5", "down", "x5<=400", "", syntax::loc_t::INIT);
s.add_location("Node5", "up", "x5<=400", "");
s.add_edge("Node5", "down", "up", "x5>=400 && x5<=400", "", "", 
                    [](syntax::layout_t const & l){
                       wave::layout_t const & _l = CAST(wave::layout_t const &, l);
                       return _l.out3 < 2 && _l.out2 < 2 && _l.out3 == 1 && _l.out2 == 1;
                    }
                    , 
                    [](syntax::layout_t  & l){
                       wave::layout_t & _l = CAST(wave::layout_t &, l);
                       _l.out5 = 1;
                    }
                    );
s.add_edge("Node5", "down", "up", "x5>=400 && x5<=400", "", "", 
                    [](syntax::layout_t const & l){
                       wave::layout_t const & _l = CAST(wave::layout_t const &, l);
                       return _l.out3 < 2 && _l.out2 < 2 && (_l.out3 == 1 && _l.out2 == 1)==0;
                    }
                    , 
                    [](syntax::layout_t  & l){
                       wave::layout_t & _l = CAST(wave::layout_t &, l);
                       _l.out5 = 0;
                    }
                    );
s.add_edge("Node5", "down", "down", "x5 == 400", "x5", "", 
                    [](syntax::layout_t const & l){
                       wave::layout_t const & _l = CAST(wave::layout_t const &, l);
                       return (_l.out3 != 2 &&  _l.out2 != 2) == 0;
                    }
                    );
s.add_edge("Node5", "up", "down", "x5 <= 400", "x5", "",syntax::layout_true,
                    [](syntax::layout_t  & l){
                       wave::layout_t & _l = CAST(wave::layout_t &, l);
                       _l.out5 = 2;
                    }
                    );
s.add_process("Node6");
s.add_location("Node6", "down", "x6<=100", "", syntax::loc_t::INIT);
s.add_location("Node6", "up", "x6<=100", "");
s.add_edge("Node6", "down", "up", "x6>=100 && x6<=100", "", "", 
                    [](syntax::layout_t const & l){
                       wave::layout_t const & _l = CAST(wave::layout_t const &, l);
                       return _l.out4 < 2 && _l.out5 < 2 && _l.out7 < 2 && _l.out8 < 2 && _l.out9 < 2 && (_l.out4+(_l.out5+(_l.out7+(_l.out8+(_l.out9))))) >= 5;
                    }
                    , 
                    [](syntax::layout_t  & l){
                       wave::layout_t & _l = CAST(wave::layout_t &, l);
                       _l.out6 = 1;
                    }
                    );
s.add_edge("Node6", "down", "up", "x6>=100 && x6<=100", "", "", 
                    [](syntax::layout_t const & l){
                       wave::layout_t const & _l = CAST(wave::layout_t const &, l);
                       return _l.out4 < 2 && _l.out5 < 2 && _l.out7 < 2 && _l.out8 < 2 && _l.out9 < 2 && (_l.out4+(_l.out5+(_l.out7+(_l.out8+(_l.out9))))) < 5;
                    }
                    , 
                    [](syntax::layout_t  & l){
                       wave::layout_t & _l = CAST(wave::layout_t &, l);
                       _l.out6 = 0;
                    }
                    );
s.add_edge("Node6", "down", "down", "x6 == 100", "x6", "", 
                    [](syntax::layout_t const & l){
                       wave::layout_t const & _l = CAST(wave::layout_t const &, l);
                       return (_l.out4 != 2 && (_l.out5 != 2 && (_l.out7 != 2 && (_l.out8 != 2 && (_l.out9 != 2))))) == 0;
                    }
                    );
s.add_edge("Node6", "up", "down", "x6 <= 100", "x6", "",syntax::layout_true,
                    [](syntax::layout_t  & l){
                       wave::layout_t & _l = CAST(wave::layout_t &, l);
                       _l.out6 = 2;
                    }
                    );
s.add_process("input");
s.add_location("input","input_init","","",syntax::loc_t::INIT | syntax::loc_t::COMMITTED);
s.add_location("input","in7","","",syntax::loc_t::COMMITTED);
s.add_location("input","in8","","",syntax::loc_t::COMMITTED);
s.add_location("input","in9","","",syntax::loc_t::COMMITTED);
s.add_edge("input", "input_init", "in7","", "","",syntax::layout_true,
            [](syntax::layout_t  & l){
            wave::layout_t & _l = CAST(wave::layout_t &, l);
            _l.out7 = 0;
            }
            );
s.add_edge("input", "input_init", "in7","", "","",syntax::layout_true,
            [](syntax::layout_t  & l){
            wave::layout_t & _l = CAST(wave::layout_t &, l);
            _l.out7 = 1;
            }
            );
s.add_edge("input", "in7", "in8","", "","",syntax::layout_true,
            [](syntax::layout_t  & l){
            wave::layout_t & _l = CAST(wave::layout_t &, l);
            _l.out8 = 0;
            }
            );
s.add_edge("input", "in7", "in8","", "","",syntax::layout_true,
            [](syntax::layout_t  & l){
            wave::layout_t & _l = CAST(wave::layout_t &, l);
            _l.out8 = 1;
            }
            );
s.add_edge("input", "in8", "in9","", "","",syntax::layout_true,
            [](syntax::layout_t  & l){
            wave::layout_t & _l = CAST(wave::layout_t &, l);
            _l.out9 = 0;
            }
            );
s.add_edge("input", "in8", "in9","", "","",syntax::layout_true,
            [](syntax::layout_t  & l){
            wave::layout_t & _l = CAST(wave::layout_t &, l);
            _l.out9 = 1;
            }
            );
s.add_location("input","input_end");
s.add_edge("input", "in9", "input_end");
	s.synchronizer<syntax::asynchronous_product_t>();
}
