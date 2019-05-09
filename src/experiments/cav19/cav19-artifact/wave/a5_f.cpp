#include <iostream>
#include "syntax/system.hh"
#include "syntax/sync_product.hh"
namespace wave{
  class layout_t : public syntax::layout_t {
  public:
        
	char out0;
	char b0_0;
	char b0_1;
	char b0_2;
	char out1;
	char b1_0;
	char b1_1;
	char b1_2;
	char b1_3;
	char b1_4;
	char b1_5;
	char b1_6;
	char b1_7;
	char b1_8;
	char b1_9;
	char out2;
	char b2_0;
	char b2_1;
	char b2_2;
	char b2_3;
	char b2_4;
	char out3;
	char b3_0;
	char b3_1;
	char b3_2;
	char b3_3;
	char b3_4;
	char out4;
	char out5;
	char b5_0;
	char b5_1;
	char b5_2;
	char out6;
	char out7;
	char out8;
	char out9;
	char out10;
	char out11;
	char out12;
	char out13;
	char out14;
	char out15;
	char out16;
	char out17;
	char out18;
	char out19;
layout_t() {
	out0 = 2;
	b0_0 = 2;
	b0_1 = 2;
	b0_2 = 2;
	out1 = 2;
	b1_0 = 2;
	b1_1 = 2;
	b1_2 = 2;
	b1_3 = 2;
	b1_4 = 2;
	b1_5 = 2;
	b1_6 = 2;
	b1_7 = 2;
	b1_8 = 2;
	b1_9 = 2;
	out2 = 2;
	b2_0 = 2;
	b2_1 = 2;
	b2_2 = 2;
	b2_3 = 2;
	b2_4 = 2;
	out3 = 2;
	b3_0 = 2;
	b3_1 = 2;
	b3_2 = 2;
	b3_3 = 2;
	b3_4 = 2;
	out4 = 2;
	out5 = 2;
	b5_0 = 2;
	b5_1 = 2;
	b5_2 = 2;
	out6 = 2;
	out7 = 2;
	out8 = 2;
	out9 = 2;
	out10 = 2;
	out11 = 2;
	out12 = 2;
	out13 = 2;
	out14 = 2;
	out15 = 2;
	out16 = 2;
	out17 = 2;
	out18 = 2;
	out19 = 2;

    }

    virtual ~layout_t() {
    }

    layout_t(const layout_t & l)  = default;

    inline bool operator == (const syntax::layout_t & l) const {
      wave::layout_t const & _l = CAST(wave::layout_t const &, l);
        
	if (out0 != _l.out0) return false;
	if(b0_0 != _l.b0_0) return false;
	if(b0_1 != _l.b0_1) return false;
	if(b0_2 != _l.b0_2) return false;
	if (out1 != _l.out1) return false;
	if(b1_0 != _l.b1_0) return false;
	if(b1_1 != _l.b1_1) return false;
	if(b1_2 != _l.b1_2) return false;
	if(b1_3 != _l.b1_3) return false;
	if(b1_4 != _l.b1_4) return false;
	if(b1_5 != _l.b1_5) return false;
	if(b1_6 != _l.b1_6) return false;
	if(b1_7 != _l.b1_7) return false;
	if(b1_8 != _l.b1_8) return false;
	if(b1_9 != _l.b1_9) return false;
	if (out2 != _l.out2) return false;
	if(b2_0 != _l.b2_0) return false;
	if(b2_1 != _l.b2_1) return false;
	if(b2_2 != _l.b2_2) return false;
	if(b2_3 != _l.b2_3) return false;
	if(b2_4 != _l.b2_4) return false;
	if (out3 != _l.out3) return false;
	if(b3_0 != _l.b3_0) return false;
	if(b3_1 != _l.b3_1) return false;
	if(b3_2 != _l.b3_2) return false;
	if(b3_3 != _l.b3_3) return false;
	if(b3_4 != _l.b3_4) return false;
	if (out4 != _l.out4) return false;
	if (out5 != _l.out5) return false;
	if(b5_0 != _l.b5_0) return false;
	if(b5_1 != _l.b5_1) return false;
	if(b5_2 != _l.b5_2) return false;
	if (out6 != _l.out6) return false;
	if (out7 != _l.out7) return false;
	if (out8 != _l.out8) return false;
	if (out9 != _l.out9) return false;
	if (out10 != _l.out10) return false;
	if (out11 != _l.out11) return false;
	if (out12 != _l.out12) return false;
	if (out13 != _l.out13) return false;
	if (out14 != _l.out14) return false;
	if (out15 != _l.out15) return false;
	if (out16 != _l.out16) return false;
	if (out17 != _l.out17) return false;
	if (out18 != _l.out18) return false;
	if (out19 != _l.out19) return false;

        return true;
    }

    inline size_t hash() const {
      size_t seed = global_t::instance().hash_seed();
        
	boost::hash_combine(seed, out0);
	boost::hash_combine(seed, b0_0);
	boost::hash_combine(seed, b0_1);
	boost::hash_combine(seed, b0_2);
	boost::hash_combine(seed, out1);
	boost::hash_combine(seed, b1_0);
	boost::hash_combine(seed, b1_1);
	boost::hash_combine(seed, b1_2);
	boost::hash_combine(seed, b1_3);
	boost::hash_combine(seed, b1_4);
	boost::hash_combine(seed, b1_5);
	boost::hash_combine(seed, b1_6);
	boost::hash_combine(seed, b1_7);
	boost::hash_combine(seed, b1_8);
	boost::hash_combine(seed, b1_9);
	boost::hash_combine(seed, out2);
	boost::hash_combine(seed, b2_0);
	boost::hash_combine(seed, b2_1);
	boost::hash_combine(seed, b2_2);
	boost::hash_combine(seed, b2_3);
	boost::hash_combine(seed, b2_4);
	boost::hash_combine(seed, out3);
	boost::hash_combine(seed, b3_0);
	boost::hash_combine(seed, b3_1);
	boost::hash_combine(seed, b3_2);
	boost::hash_combine(seed, b3_3);
	boost::hash_combine(seed, b3_4);
	boost::hash_combine(seed, out4);
	boost::hash_combine(seed, out5);
	boost::hash_combine(seed, b5_0);
	boost::hash_combine(seed, b5_1);
	boost::hash_combine(seed, b5_2);
	boost::hash_combine(seed, out6);
	boost::hash_combine(seed, out7);
	boost::hash_combine(seed, out8);
	boost::hash_combine(seed, out9);
	boost::hash_combine(seed, out10);
	boost::hash_combine(seed, out11);
	boost::hash_combine(seed, out12);
	boost::hash_combine(seed, out13);
	boost::hash_combine(seed, out14);
	boost::hash_combine(seed, out15);
	boost::hash_combine(seed, out16);
	boost::hash_combine(seed, out17);
	boost::hash_combine(seed, out18);
	boost::hash_combine(seed, out19);

      return seed;
    }

    void output(std::ostream & os) const {
        
	os << "out0=" << out0 << ",";
	os << "b0_1=" << b0_0 << ",";
	os << "b0_1=" << b0_1 << ",";
	os << "b0_1=" << b0_2 << ",";
	os << "out1=" << out1 << ",";
	os << "b1_1=" << b1_0 << ",";
	os << "b1_1=" << b1_1 << ",";
	os << "b1_1=" << b1_2 << ",";
	os << "b1_1=" << b1_3 << ",";
	os << "b1_1=" << b1_4 << ",";
	os << "b1_1=" << b1_5 << ",";
	os << "b1_1=" << b1_6 << ",";
	os << "b1_1=" << b1_7 << ",";
	os << "b1_1=" << b1_8 << ",";
	os << "b1_1=" << b1_9 << ",";
	os << "out2=" << out2 << ",";
	os << "b2_1=" << b2_0 << ",";
	os << "b2_1=" << b2_1 << ",";
	os << "b2_1=" << b2_2 << ",";
	os << "b2_1=" << b2_3 << ",";
	os << "b2_1=" << b2_4 << ",";
	os << "out3=" << out3 << ",";
	os << "b3_1=" << b3_0 << ",";
	os << "b3_1=" << b3_1 << ",";
	os << "b3_1=" << b3_2 << ",";
	os << "b3_1=" << b3_3 << ",";
	os << "b3_1=" << b3_4 << ",";
	os << "out4=" << out4 << ",";
	os << "out5=" << out5 << ",";
	os << "b5_1=" << b5_0 << ",";
	os << "b5_1=" << b5_1 << ",";
	os << "b5_1=" << b5_2 << ",";
	os << "out6=" << out6 << ",";
	os << "out7=" << out7 << ",";
	os << "out8=" << out8 << ",";
	os << "out9=" << out9 << ",";
	os << "out10=" << out10 << ",";
	os << "out11=" << out11 << ",";
	os << "out12=" << out12 << ",";
	os << "out13=" << out13 << ",";
	os << "out14=" << out14 << ",";
	os << "out15=" << out15 << ",";
	os << "out16=" << out16 << ",";
	os << "out17=" << out17 << ",";
	os << "out18=" << out18 << ",";
	os << "out19=" << out19 << ",";

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
s.add_label("err");
s.add_label("unreachable");
s.add_process("Node0");
s.add_location("Node0", "down", "x0<=100", "", syntax::loc_t::INIT);
s.add_location("Node0", "up", "x0<=300", "");
s.add_edge("Node0", "down", "up", "x0>=100 && x0 <= 300 && t <= 1000", "", "",
                    [](syntax::layout_t const & l){
                       wave::layout_t const & _l = CAST(wave::layout_t const &, l);
                       return _l.out5 < 2 && _l.out15 < 2 && _l.out3 < 2 && (_l.out5+(_l.out15+(_l.out3))) >= 3;
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


                    });
                    
s.add_edge("Node0", "down", "up", "x0>=100 && x0<=300", "", "", 
                    [](syntax::layout_t const & l){
                       wave::layout_t const & _l = CAST(wave::layout_t const &, l);
                       return _l.out5 < 2 && _l.out15 < 2 && _l.out3 < 2 && (_l.out5+(_l.out15+(_l.out3))) < 3;
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
                       return (_l.out5 != 2 && (_l.out15 != 2 && (_l.out3 != 2))) == 0;
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
                       return _l.out6 < 2 && _l.out7 < 2 && _l.out8 < 2 && _l.out9 < 2 && _l.out10 < 2 && _l.out11 < 2 && _l.out12 < 2 && _l.out13 < 2 && _l.out14 < 2 && _l.out15 < 2 && (_l.out6+(_l.out7+(_l.out8+(_l.out9+(_l.out10+(_l.out11+(_l.out12+(_l.out13+(_l.out14+(_l.out15)))))))))) >= 9;
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
                       return _l.out6 < 2 && _l.out7 < 2 && _l.out8 < 2 && _l.out9 < 2 && _l.out10 < 2 && _l.out11 < 2 && _l.out12 < 2 && _l.out13 < 2 && _l.out14 < 2 && _l.out15 < 2 && (_l.out6+(_l.out7+(_l.out8+(_l.out9+(_l.out10+(_l.out11+(_l.out12+(_l.out13+(_l.out14+(_l.out15)))))))))) < 9;
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
                       return (_l.out6 != 2 && (_l.out7 != 2 && (_l.out8 != 2 && (_l.out9 != 2 && (_l.out10 != 2 && (_l.out11 != 2 && (_l.out12 != 2 && (_l.out13 != 2 && (_l.out14 != 2 && (_l.out15 != 2)))))))))) == 0;
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
                       return _l.out15 < 2 && _l.out16 < 2 && _l.out17 < 2 && _l.out18 < 2 && _l.out19 < 2 && (_l.out15+(_l.out16+(_l.out17+(_l.out18+(_l.out19))))) >= 4;
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
                       return _l.out15 < 2 && _l.out16 < 2 && _l.out17 < 2 && _l.out18 < 2 && _l.out19 < 2 && (_l.out15+(_l.out16+(_l.out17+(_l.out18+(_l.out19))))) < 4;
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
                       return (_l.out15 != 2 && (_l.out16 != 2 && (_l.out17 != 2 && (_l.out18 != 2 && (_l.out19 != 2))))) == 0;
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
                       return _l.out15 < 2 && _l.out16 < 2 && _l.out17 < 2 && _l.out18 < 2 && _l.out19 < 2 && (_l.out15+(_l.out16+(_l.out17+(_l.out18+(_l.out19))))) >= 5;
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
                       return _l.out15 < 2 && _l.out16 < 2 && _l.out17 < 2 && _l.out18 < 2 && _l.out19 < 2 && (_l.out15+(_l.out16+(_l.out17+(_l.out18+(_l.out19))))) < 5;
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
                       return (_l.out15 != 2 && (_l.out16 != 2 && (_l.out17 != 2 && (_l.out18 != 2 && (_l.out19 != 2))))) == 0;
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
                       return _l.out3 < 2 && (1-_l.out3)==1;
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
                       return _l.out3 < 2 && (1-_l.out3) ==0;
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
                       return _l.out3 == 2;
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
                       return _l.out1 < 2 && _l.out2 < 2 && _l.out4 < 2 && (_l.out1+(_l.out2+(_l.out4))) >= 3;
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
                       return _l.out1 < 2 && _l.out2 < 2 && _l.out4 < 2 && (_l.out1+(_l.out2+(_l.out4))) < 3;
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
                       return (_l.out1 != 2 && (_l.out2 != 2 && (_l.out4 != 2))) == 0;
                    }
                    );
s.add_edge("Node5", "up", "down", "x5 <= 400", "x5", "",syntax::layout_true,
                    [](syntax::layout_t  & l){
                       wave::layout_t & _l = CAST(wave::layout_t &, l);
                       _l.out5 = 2;
                    }
                    );
s.add_process("input");
s.add_location("input","input_init","","",syntax::loc_t::INIT | syntax::loc_t::COMMITTED);
s.add_location("input","in6","","",syntax::loc_t::COMMITTED);
s.add_location("input","in7","","",syntax::loc_t::COMMITTED);
s.add_location("input","in8","","",syntax::loc_t::COMMITTED);
s.add_location("input","in9","","",syntax::loc_t::COMMITTED);
s.add_location("input","in10","","",syntax::loc_t::COMMITTED);
s.add_location("input","in11","","",syntax::loc_t::COMMITTED);
s.add_location("input","in12","","",syntax::loc_t::COMMITTED);
s.add_location("input","in13","","",syntax::loc_t::COMMITTED);
s.add_location("input","in14","","",syntax::loc_t::COMMITTED);
s.add_location("input","in15","","",syntax::loc_t::COMMITTED);
s.add_location("input","in16","","",syntax::loc_t::COMMITTED);
s.add_location("input","in17","","",syntax::loc_t::COMMITTED);
s.add_location("input","in18","","",syntax::loc_t::COMMITTED);
s.add_location("input","in19","","",syntax::loc_t::COMMITTED);
s.add_edge("input", "input_init", "in6","", "","",syntax::layout_true,
            [](syntax::layout_t  & l){
            wave::layout_t & _l = CAST(wave::layout_t &, l);
            _l.out6 = 0;
            }
            );
s.add_edge("input", "input_init", "in6","", "","",syntax::layout_true,
            [](syntax::layout_t  & l){
            wave::layout_t & _l = CAST(wave::layout_t &, l);
            _l.out6 = 1;
            }
            );
s.add_edge("input", "in6", "in7","", "","",syntax::layout_true,
            [](syntax::layout_t  & l){
            wave::layout_t & _l = CAST(wave::layout_t &, l);
            _l.out7 = 0;
            }
            );
s.add_edge("input", "in6", "in7","", "","",syntax::layout_true,
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
s.add_edge("input", "in9", "in10","", "","",syntax::layout_true,
            [](syntax::layout_t  & l){
            wave::layout_t & _l = CAST(wave::layout_t &, l);
            _l.out10 = 0;
            }
            );
s.add_edge("input", "in9", "in10","", "","",syntax::layout_true,
            [](syntax::layout_t  & l){
            wave::layout_t & _l = CAST(wave::layout_t &, l);
            _l.out10 = 1;
            }
            );
s.add_edge("input", "in10", "in11","", "","",syntax::layout_true,
            [](syntax::layout_t  & l){
            wave::layout_t & _l = CAST(wave::layout_t &, l);
            _l.out11 = 0;
            }
            );
s.add_edge("input", "in10", "in11","", "","",syntax::layout_true,
            [](syntax::layout_t  & l){
            wave::layout_t & _l = CAST(wave::layout_t &, l);
            _l.out11 = 1;
            }
            );
s.add_edge("input", "in11", "in12","", "","",syntax::layout_true,
            [](syntax::layout_t  & l){
            wave::layout_t & _l = CAST(wave::layout_t &, l);
            _l.out12 = 0;
            }
            );
s.add_edge("input", "in11", "in12","", "","",syntax::layout_true,
            [](syntax::layout_t  & l){
            wave::layout_t & _l = CAST(wave::layout_t &, l);
            _l.out12 = 1;
            }
            );
s.add_edge("input", "in12", "in13","", "","",syntax::layout_true,
            [](syntax::layout_t  & l){
            wave::layout_t & _l = CAST(wave::layout_t &, l);
            _l.out13 = 0;
            }
            );
s.add_edge("input", "in12", "in13","", "","",syntax::layout_true,
            [](syntax::layout_t  & l){
            wave::layout_t & _l = CAST(wave::layout_t &, l);
            _l.out13 = 1;
            }
            );
s.add_edge("input", "in13", "in14","", "","",syntax::layout_true,
            [](syntax::layout_t  & l){
            wave::layout_t & _l = CAST(wave::layout_t &, l);
            _l.out14 = 0;
            }
            );
s.add_edge("input", "in13", "in14","", "","",syntax::layout_true,
            [](syntax::layout_t  & l){
            wave::layout_t & _l = CAST(wave::layout_t &, l);
            _l.out14 = 1;
            }
            );
s.add_edge("input", "in14", "in15","", "","",syntax::layout_true,
            [](syntax::layout_t  & l){
            wave::layout_t & _l = CAST(wave::layout_t &, l);
            _l.out15 = 0;
            }
            );
s.add_edge("input", "in14", "in15","", "","",syntax::layout_true,
            [](syntax::layout_t  & l){
            wave::layout_t & _l = CAST(wave::layout_t &, l);
            _l.out15 = 1;
            }
            );
s.add_edge("input", "in15", "in16","", "","",syntax::layout_true,
            [](syntax::layout_t  & l){
            wave::layout_t & _l = CAST(wave::layout_t &, l);
            _l.out16 = 0;
            }
            );
s.add_edge("input", "in15", "in16","", "","",syntax::layout_true,
            [](syntax::layout_t  & l){
            wave::layout_t & _l = CAST(wave::layout_t &, l);
            _l.out16 = 1;
            }
            );
s.add_edge("input", "in16", "in17","", "","",syntax::layout_true,
            [](syntax::layout_t  & l){
            wave::layout_t & _l = CAST(wave::layout_t &, l);
            _l.out17 = 0;
            }
            );
s.add_edge("input", "in16", "in17","", "","",syntax::layout_true,
            [](syntax::layout_t  & l){
            wave::layout_t & _l = CAST(wave::layout_t &, l);
            _l.out17 = 1;
            }
            );
s.add_edge("input", "in17", "in18","", "","",syntax::layout_true,
            [](syntax::layout_t  & l){
            wave::layout_t & _l = CAST(wave::layout_t &, l);
            _l.out18 = 0;
            }
            );
s.add_edge("input", "in17", "in18","", "","",syntax::layout_true,
            [](syntax::layout_t  & l){
            wave::layout_t & _l = CAST(wave::layout_t &, l);
            _l.out18 = 1;
            }
            );
s.add_edge("input", "in18", "in19","", "","",syntax::layout_true,
            [](syntax::layout_t  & l){
            wave::layout_t & _l = CAST(wave::layout_t &, l);
            _l.out19 = 0;
            }
            );
s.add_edge("input", "in18", "in19","", "","",syntax::layout_true,
            [](syntax::layout_t  & l){
            wave::layout_t & _l = CAST(wave::layout_t &, l);
            _l.out19 = 1;
            }
            );
s.add_location("input","input_end");
s.add_edge("input", "in19", "input_end");
	s.synchronizer<syntax::asynchronous_product_t>();
}
