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
	char out4;
	char out5;
	char out6;
	char out7;
	char out8;
	char out9;
	char b9_0;
	char b9_1;
	char b9_2;
	char b9_3;
	char out10;
	char b10_0;
	char b10_1;
	char b10_2;
	char b10_3;
	char b10_4;
	char b10_5;
	char out11;
	char b11_0;
	char b11_1;
	char b11_2;
	char b11_3;
	char b11_4;
	char out12;
	char b12_0;
	char b12_1;
	char b12_2;
	char b12_3;
	char b12_4;
	char out13;
	char b13_0;
	char b13_1;
	char out14;
	char b14_0;
	char b14_1;
	char out15;
layout_t() {
	out0 = 2;
	b0_0 = 2;
	b0_1 = 2;
	out1 = 2;
	out2 = 2;
	out3 = 2;
	out4 = 2;
	out5 = 2;
	out6 = 2;
	out7 = 2;
	out8 = 2;
	out9 = 2;
	b9_0 = 2;
	b9_1 = 2;
	b9_2 = 2;
	b9_3 = 2;
	out10 = 2;
	b10_0 = 2;
	b10_1 = 2;
	b10_2 = 2;
	b10_3 = 2;
	b10_4 = 2;
	b10_5 = 2;
	out11 = 2;
	b11_0 = 2;
	b11_1 = 2;
	b11_2 = 2;
	b11_3 = 2;
	b11_4 = 2;
	out12 = 2;
	b12_0 = 2;
	b12_1 = 2;
	b12_2 = 2;
	b12_3 = 2;
	b12_4 = 2;
	out13 = 2;
	b13_0 = 2;
	b13_1 = 2;
	out14 = 2;
	b14_0 = 2;
	b14_1 = 2;
	out15 = 2;

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
	if (out4 != _l.out4) return false;
	if (out5 != _l.out5) return false;
	if (out6 != _l.out6) return false;
	if (out7 != _l.out7) return false;
	if (out8 != _l.out8) return false;
	if (out9 != _l.out9) return false;
	if(b9_0 != _l.b9_0) return false;
	if(b9_1 != _l.b9_1) return false;
	if(b9_2 != _l.b9_2) return false;
	if(b9_3 != _l.b9_3) return false;
	if (out10 != _l.out10) return false;
	if(b10_0 != _l.b10_0) return false;
	if(b10_1 != _l.b10_1) return false;
	if(b10_2 != _l.b10_2) return false;
	if(b10_3 != _l.b10_3) return false;
	if(b10_4 != _l.b10_4) return false;
	if(b10_5 != _l.b10_5) return false;
	if (out11 != _l.out11) return false;
	if(b11_0 != _l.b11_0) return false;
	if(b11_1 != _l.b11_1) return false;
	if(b11_2 != _l.b11_2) return false;
	if(b11_3 != _l.b11_3) return false;
	if(b11_4 != _l.b11_4) return false;
	if (out12 != _l.out12) return false;
	if(b12_0 != _l.b12_0) return false;
	if(b12_1 != _l.b12_1) return false;
	if(b12_2 != _l.b12_2) return false;
	if(b12_3 != _l.b12_3) return false;
	if(b12_4 != _l.b12_4) return false;
	if (out13 != _l.out13) return false;
	if(b13_0 != _l.b13_0) return false;
	if(b13_1 != _l.b13_1) return false;
	if (out14 != _l.out14) return false;
	if(b14_0 != _l.b14_0) return false;
	if(b14_1 != _l.b14_1) return false;
	if (out15 != _l.out15) return false;

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
	boost::hash_combine(seed, out4);
	boost::hash_combine(seed, out5);
	boost::hash_combine(seed, out6);
	boost::hash_combine(seed, out7);
	boost::hash_combine(seed, out8);
	boost::hash_combine(seed, out9);
	boost::hash_combine(seed, b9_0);
	boost::hash_combine(seed, b9_1);
	boost::hash_combine(seed, b9_2);
	boost::hash_combine(seed, b9_3);
	boost::hash_combine(seed, out10);
	boost::hash_combine(seed, b10_0);
	boost::hash_combine(seed, b10_1);
	boost::hash_combine(seed, b10_2);
	boost::hash_combine(seed, b10_3);
	boost::hash_combine(seed, b10_4);
	boost::hash_combine(seed, b10_5);
	boost::hash_combine(seed, out11);
	boost::hash_combine(seed, b11_0);
	boost::hash_combine(seed, b11_1);
	boost::hash_combine(seed, b11_2);
	boost::hash_combine(seed, b11_3);
	boost::hash_combine(seed, b11_4);
	boost::hash_combine(seed, out12);
	boost::hash_combine(seed, b12_0);
	boost::hash_combine(seed, b12_1);
	boost::hash_combine(seed, b12_2);
	boost::hash_combine(seed, b12_3);
	boost::hash_combine(seed, b12_4);
	boost::hash_combine(seed, out13);
	boost::hash_combine(seed, b13_0);
	boost::hash_combine(seed, b13_1);
	boost::hash_combine(seed, out14);
	boost::hash_combine(seed, b14_0);
	boost::hash_combine(seed, b14_1);
	boost::hash_combine(seed, out15);

      return seed;
    }

    void output(std::ostream & os) const {
        
	os << "out0=" << out0 << ",";
	os << "b0_0=" << b0_0 << ",";
	os << "b0_1=" << b0_1 << ",";
	os << "out1=" << out1 << ",";
	os << "out2=" << out2 << ",";
	os << "out3=" << out3 << ",";
	os << "out4=" << out4 << ",";
	os << "out5=" << out5 << ",";
	os << "out6=" << out6 << ",";
	os << "out7=" << out7 << ",";
	os << "out8=" << out8 << ",";
	os << "out9=" << out9 << ",";
	os << "b9_1=" << b9_0 << ",";
	os << "b9_1=" << b9_1 << ",";
	os << "b9_1=" << b9_2 << ",";
	os << "b9_1=" << b9_3 << ",";
	os << "out10=" << out10 << ",";
	os << "b10_1=" << b10_0 << ",";
	os << "b10_1=" << b10_1 << ",";
	os << "b10_1=" << b10_2 << ",";
	os << "b10_1=" << b10_3 << ",";
	os << "b10_1=" << b10_4 << ",";
	os << "b10_1=" << b10_5 << ",";
	os << "out11=" << out11 << ",";
	os << "b11_1=" << b11_0 << ",";
	os << "b11_1=" << b11_1 << ",";
	os << "b11_1=" << b11_2 << ",";
	os << "b11_1=" << b11_3 << ",";
	os << "b11_1=" << b11_4 << ",";
	os << "out12=" << out12 << ",";
	os << "b12_1=" << b12_0 << ",";
	os << "b12_1=" << b12_1 << ",";
	os << "b12_1=" << b12_2 << ",";
	os << "b12_1=" << b12_3 << ",";
	os << "b12_1=" << b12_4 << ",";
	os << "out13=" << out13 << ",";
	os << "b13_0=" << b13_0 << ",";
	os << "b13_1=" << b13_1 << ",";
	os << "out14=" << out14 << ",";
	os << "b14_0=" << b14_0 << ",";
	os << "b14_1=" << b14_1 << ",";
	os << "out15=" << out15 << ",";

    }
  };

}
        
void build_model(syntax::system_t & s){
s.name("Wave");
s.layout_alloc< syntax::layout_T_alloc_t<wave::layout_t> >();
s.add_clock("t");
s.add_clock("x0");
s.add_clock("x9");
s.add_clock("x10");
s.add_clock("x11");
s.add_clock("x12");
s.add_clock("x13");
s.add_clock("x14");
s.add_clock("x15");
s.add_label("err");
s.add_label("unreachable");
s.add_process("Node0");
s.add_location("Node0", "down", "x0<=100", "", syntax::loc_t::INIT);
s.add_location("Node0", "up", "x0<=300", "");
s.add_edge("Node0", "down", "up", "x0>=100 && x0 <= 300 && t <= 1000", "", "",
                    [](syntax::layout_t const & l){
                       wave::layout_t const & _l = CAST(wave::layout_t const &, l);
                       return _l.out14 < 2 && _l.out15 < 2 && _l.out14 == 1 && _l.out15 == 1;
                    }
                    ,
                    [](syntax::layout_t  & l){
                       wave::layout_t & _l = CAST(wave::layout_t &, l);
                       _l.out0 = 1;
                    }
                    );
s.add_edge("Node0", "down", "down", "t>1000", "", "", syntax::layout_true, [](syntax::layout_t  & l){wave::layout_t & _l = CAST(wave::layout_t &, l);
_l.out0 = 2;

_l.out9 = 2;

_l.out10 = 2;

_l.out11 = 2;

_l.out12 = 2;

_l.out13 = 2;

_l.out14 = 2;

_l.out15 = 2;


                    });
                    
s.add_edge("Node0", "down", "up", "x0>=100 && x0<=300", "", "", 
                    [](syntax::layout_t const & l){
                       wave::layout_t const & _l = CAST(wave::layout_t const &, l);
                       return _l.out14 < 2 && _l.out15 < 2 && (_l.out14 == 1 && _l.out15 == 1)==0;
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
                       return (_l.out14 != 2 &&  _l.out15 != 2) == 0;
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
s.add_process("Node9");
s.add_location("Node9", "down", "x9<=50", "", syntax::loc_t::INIT);
s.add_location("Node9", "up", "x9<=400", "");
s.add_edge("Node9", "down", "up", "x9>=50 && x9<=400", "", "", 
                    [](syntax::layout_t const & l){
                       wave::layout_t const & _l = CAST(wave::layout_t const &, l);
                       return _l.out1 < 2 && _l.out2 < 2 && _l.out3 < 2 && _l.out4 < 2 && (_l.out1+(_l.out2+(_l.out3+(_l.out4)))) >= 4;
                    }
                    , 
                    [](syntax::layout_t  & l){
                       wave::layout_t & _l = CAST(wave::layout_t &, l);
                       _l.out9 = 1;
                    }
                    );
s.add_edge("Node9", "down", "up", "x9>=50 && x9<=400", "", "", 
                    [](syntax::layout_t const & l){
                       wave::layout_t const & _l = CAST(wave::layout_t const &, l);
                       return _l.out1 < 2 && _l.out2 < 2 && _l.out3 < 2 && _l.out4 < 2 && (_l.out1+(_l.out2+(_l.out3+(_l.out4)))) < 4;
                    }
                    , 
                    [](syntax::layout_t  & l){
                       wave::layout_t & _l = CAST(wave::layout_t &, l);
                       _l.out9 = 0;
                    }
                    );
s.add_edge("Node9", "down", "down", "x9 == 50", "x9", "", 
                    [](syntax::layout_t const & l){
                       wave::layout_t const & _l = CAST(wave::layout_t const &, l);
                       return (_l.out1 != 2 && (_l.out2 != 2 && (_l.out3 != 2 && (_l.out4 != 2)))) == 0;
                    }
                    );
s.add_edge("Node9", "up", "down", "x9 <= 400", "x9", "",syntax::layout_true,
                    [](syntax::layout_t  & l){
                       wave::layout_t & _l = CAST(wave::layout_t &, l);
                       _l.out9 = 2;
                    }
                    );
s.add_process("Node10");
s.add_location("Node10", "down", "x10<=200", "", syntax::loc_t::INIT);
s.add_location("Node10", "up", "x10<=600", "");
s.add_edge("Node10", "down", "up", "x10>=200 && x10<=600", "", "", 
                    [](syntax::layout_t const & l){
                       wave::layout_t const & _l = CAST(wave::layout_t const &, l);
                       return _l.out9 < 2 && _l.out1 < 2 && _l.out2 < 2 && _l.out3 < 2 && _l.out4 < 2 && _l.out5 < 2 && (_l.out9+(_l.out1+(_l.out2+(_l.out3+(_l.out4+(_l.out5)))))) >= 4;
                    }
                    , 
                    [](syntax::layout_t  & l){
                       wave::layout_t & _l = CAST(wave::layout_t &, l);
                       _l.out10 = 1;
                    }
                    );
s.add_edge("Node10", "down", "up", "x10>=200 && x10<=600", "", "", 
                    [](syntax::layout_t const & l){
                       wave::layout_t const & _l = CAST(wave::layout_t const &, l);
                       return _l.out9 < 2 && _l.out1 < 2 && _l.out2 < 2 && _l.out3 < 2 && _l.out4 < 2 && _l.out5 < 2 && (_l.out9+(_l.out1+(_l.out2+(_l.out3+(_l.out4+(_l.out5)))))) < 4;
                    }
                    , 
                    [](syntax::layout_t  & l){
                       wave::layout_t & _l = CAST(wave::layout_t &, l);
                       _l.out10 = 0;
                    }
                    );
s.add_edge("Node10", "down", "down", "x10 == 200", "x10", "", 
                    [](syntax::layout_t const & l){
                       wave::layout_t const & _l = CAST(wave::layout_t const &, l);
                       return (_l.out9 != 2 && (_l.out1 != 2 && (_l.out2 != 2 && (_l.out3 != 2 && (_l.out4 != 2 && (_l.out5 != 2)))))) == 0;
                    }
                    );
s.add_edge("Node10", "up", "down", "x10 <= 600", "x10", "",syntax::layout_true,
                    [](syntax::layout_t  & l){
                       wave::layout_t & _l = CAST(wave::layout_t &, l);
                       _l.out10 = 2;
                    }
                    );
s.add_process("Node11");
s.add_location("Node11", "down", "x11<=300", "", syntax::loc_t::INIT);
s.add_location("Node11", "up", "x11<=0", "");
s.add_edge("Node11", "down", "up", "x11>=300 && x11<=0", "", "", 
                    [](syntax::layout_t const & l){
                       wave::layout_t const & _l = CAST(wave::layout_t const &, l);
                       return _l.out9 < 2 && _l.out10 < 2 && _l.out5 < 2 && _l.out6 < 2 && _l.out7 < 2 && (_l.out9+(_l.out10+(_l.out5+(_l.out6+(_l.out7))))) >= 3;
                    }
                    , 
                    [](syntax::layout_t  & l){
                       wave::layout_t & _l = CAST(wave::layout_t &, l);
                       _l.out11 = 1;
                    }
                    );
s.add_edge("Node11", "down", "up", "x11>=300 && x11<=0", "", "", 
                    [](syntax::layout_t const & l){
                       wave::layout_t const & _l = CAST(wave::layout_t const &, l);
                       return _l.out9 < 2 && _l.out10 < 2 && _l.out5 < 2 && _l.out6 < 2 && _l.out7 < 2 && (_l.out9+(_l.out10+(_l.out5+(_l.out6+(_l.out7))))) < 3;
                    }
                    , 
                    [](syntax::layout_t  & l){
                       wave::layout_t & _l = CAST(wave::layout_t &, l);
                       _l.out11 = 0;
                    }
                    );
s.add_edge("Node11", "down", "down", "x11 == 300", "x11", "", 
                    [](syntax::layout_t const & l){
                       wave::layout_t const & _l = CAST(wave::layout_t const &, l);
                       return (_l.out9 != 2 && (_l.out10 != 2 && (_l.out5 != 2 && (_l.out6 != 2 && (_l.out7 != 2))))) == 0;
                    }
                    );
s.add_edge("Node11", "up", "down", "x11 <= 0", "x11", "",syntax::layout_true,
                    [](syntax::layout_t  & l){
                       wave::layout_t & _l = CAST(wave::layout_t &, l);
                       _l.out11 = 2;
                    }
                    );
s.add_process("Node12");
s.add_location("Node12", "down", "x12<=250", "", syntax::loc_t::INIT);
s.add_location("Node12", "up", "x12<=0", "");
s.add_edge("Node12", "down", "up", "x12>=250 && x12<=0", "", "", 
                    [](syntax::layout_t const & l){
                       wave::layout_t const & _l = CAST(wave::layout_t const &, l);
                       return _l.out9 < 2 && _l.out11 < 2 && _l.out4 < 2 && _l.out5 < 2 && _l.out6 < 2 && (_l.out9+(_l.out11+(_l.out4+(_l.out5+(_l.out6))))) >= 4;
                    }
                    , 
                    [](syntax::layout_t  & l){
                       wave::layout_t & _l = CAST(wave::layout_t &, l);
                       _l.out12 = 1;
                    }
                    );
s.add_edge("Node12", "down", "up", "x12>=250 && x12<=0", "", "", 
                    [](syntax::layout_t const & l){
                       wave::layout_t const & _l = CAST(wave::layout_t const &, l);
                       return _l.out9 < 2 && _l.out11 < 2 && _l.out4 < 2 && _l.out5 < 2 && _l.out6 < 2 && (_l.out9+(_l.out11+(_l.out4+(_l.out5+(_l.out6))))) < 4;
                    }
                    , 
                    [](syntax::layout_t  & l){
                       wave::layout_t & _l = CAST(wave::layout_t &, l);
                       _l.out12 = 0;
                    }
                    );
s.add_edge("Node12", "down", "down", "x12 == 250", "x12", "", 
                    [](syntax::layout_t const & l){
                       wave::layout_t const & _l = CAST(wave::layout_t const &, l);
                       return (_l.out9 != 2 && (_l.out11 != 2 && (_l.out4 != 2 && (_l.out5 != 2 && (_l.out6 != 2))))) == 0;
                    }
                    );
s.add_edge("Node12", "up", "down", "x12 <= 0", "x12", "",syntax::layout_true,
                    [](syntax::layout_t  & l){
                       wave::layout_t & _l = CAST(wave::layout_t &, l);
                       _l.out12 = 2;
                    }
                    );
s.add_process("Node13");
s.add_location("Node13", "down", "x13<=400", "", syntax::loc_t::INIT);
s.add_location("Node13", "up", "x13<=400", "");
s.add_edge("Node13", "down", "up", "x13>=400 && x13<=400", "", "", 
                    [](syntax::layout_t const & l){
                       wave::layout_t const & _l = CAST(wave::layout_t const &, l);
                       return _l.out11 < 2 && _l.out12 < 2 && (_l.out11 == 0 && _l.out12 == 0) == 0;
                    }
                    , 
                    [](syntax::layout_t  & l){
                       wave::layout_t & _l = CAST(wave::layout_t &, l);
                       _l.out13 = 1;
                    }
                    );
s.add_edge("Node13", "down", "up", "x13>=400 && x13<=400", "", "", 
                    [](syntax::layout_t const & l){
                       wave::layout_t const & _l = CAST(wave::layout_t const &, l);
                       return _l.out11 < 2 && _l.out12 < 2 && _l.out11 == 0 && _l.out12 == 0;
                    }
                    , 
                    [](syntax::layout_t  & l){
                       wave::layout_t & _l = CAST(wave::layout_t &, l);
                       _l.out13 = 0;
                    }
                    );
s.add_edge("Node13", "down", "down", "x13 == 400", "x13", "", 
                    [](syntax::layout_t const & l){
                       wave::layout_t const & _l = CAST(wave::layout_t const &, l);
                       return (_l.out11 != 2 &&  _l.out12 != 2) == 0;
                    }
                    );
s.add_edge("Node13", "up", "down", "x13 <= 400", "x13", "",syntax::layout_true,
                    [](syntax::layout_t  & l){
                       wave::layout_t & _l = CAST(wave::layout_t &, l);
                       _l.out13 = 2;
                    }
                    );
s.add_process("Node14");
s.add_location("Node14", "down", "x14<=100", "", syntax::loc_t::INIT);
s.add_location("Node14", "up", "x14<=100", "");
s.add_edge("Node14", "down", "up", "x14>=100 && x14<=100", "", "", 
                    [](syntax::layout_t const & l){
                       wave::layout_t const & _l = CAST(wave::layout_t const &, l);
                       return _l.out13 < 2 && _l.out10 < 2 && _l.out13 == 1 && _l.out10 == 1;
                    }
                    , 
                    [](syntax::layout_t  & l){
                       wave::layout_t & _l = CAST(wave::layout_t &, l);
                       _l.out14 = 1;
                    }
                    );
s.add_edge("Node14", "down", "up", "x14>=100 && x14<=100", "", "", 
                    [](syntax::layout_t const & l){
                       wave::layout_t const & _l = CAST(wave::layout_t const &, l);
                       return _l.out13 < 2 && _l.out10 < 2 && (_l.out13 == 1 && _l.out10 == 1)==0;
                    }
                    , 
                    [](syntax::layout_t  & l){
                       wave::layout_t & _l = CAST(wave::layout_t &, l);
                       _l.out14 = 0;
                    }
                    );
s.add_edge("Node14", "down", "down", "x14 == 100", "x14", "", 
                    [](syntax::layout_t const & l){
                       wave::layout_t const & _l = CAST(wave::layout_t const &, l);
                       return (_l.out13 != 2 &&  _l.out10 != 2) == 0;
                    }
                    );
s.add_edge("Node14", "up", "down", "x14 <= 100", "x14", "",syntax::layout_true,
                    [](syntax::layout_t  & l){
                       wave::layout_t & _l = CAST(wave::layout_t &, l);
                       _l.out14 = 2;
                    }
                    );
s.add_process("Node15");
s.add_location("Node15", "down", "x15<=100", "", syntax::loc_t::INIT);
s.add_location("Node15", "up", "x15<=100", "");
s.add_edge("Node15", "down", "up", "x15>=100 && x15<=100", "", "", 
                    [](syntax::layout_t const & l){
                       wave::layout_t const & _l = CAST(wave::layout_t const &, l);
                       return _l.out14 < 2 && (1-_l.out14)==1;
                    }
                    , 
                    [](syntax::layout_t  & l){
                       wave::layout_t & _l = CAST(wave::layout_t &, l);
                       _l.out15 = 1;
                    }
                    );
s.add_edge("Node15", "down", "up", "x15>=100 && x15<=100", "", "", 
                    [](syntax::layout_t const & l){
                       wave::layout_t const & _l = CAST(wave::layout_t const &, l);
                       return _l.out14 < 2 && (1-_l.out14) ==0;
                    }
                    , 
                    [](syntax::layout_t  & l){
                       wave::layout_t & _l = CAST(wave::layout_t &, l);
                       _l.out15 = 0;
                    }
                    );
s.add_edge("Node15", "down", "down", "x15 == 100", "x15", "", 
                    [](syntax::layout_t const & l){
                       wave::layout_t const & _l = CAST(wave::layout_t const &, l);
                       return _l.out14 == 2;
                    }
                    );
s.add_edge("Node15", "up", "down", "x15 <= 100", "x15", "",syntax::layout_true,
                    [](syntax::layout_t  & l){
                       wave::layout_t & _l = CAST(wave::layout_t &, l);
                       _l.out15 = 2;
                    }
                    );
s.add_process("input");
s.add_location("input","input_init","","",syntax::loc_t::INIT | syntax::loc_t::COMMITTED);
s.add_location("input","in1","","",syntax::loc_t::COMMITTED);
s.add_location("input","in2","","",syntax::loc_t::COMMITTED);
s.add_location("input","in3","","",syntax::loc_t::COMMITTED);
s.add_location("input","in4","","",syntax::loc_t::COMMITTED);
s.add_location("input","in5","","",syntax::loc_t::COMMITTED);
s.add_location("input","in6","","",syntax::loc_t::COMMITTED);
s.add_location("input","in7","","",syntax::loc_t::COMMITTED);
s.add_location("input","in8","","",syntax::loc_t::COMMITTED);
s.add_edge("input", "input_init", "in1","", "","",syntax::layout_true,
            [](syntax::layout_t  & l){
            wave::layout_t & _l = CAST(wave::layout_t &, l);
            _l.out1 = 0;
            }
            );
s.add_edge("input", "input_init", "in1","", "","",syntax::layout_true,
            [](syntax::layout_t  & l){
            wave::layout_t & _l = CAST(wave::layout_t &, l);
            _l.out1 = 1;
            }
            );
s.add_edge("input", "in1", "in2","", "","",syntax::layout_true,
            [](syntax::layout_t  & l){
            wave::layout_t & _l = CAST(wave::layout_t &, l);
            _l.out2 = 0;
            }
            );
s.add_edge("input", "in1", "in2","", "","",syntax::layout_true,
            [](syntax::layout_t  & l){
            wave::layout_t & _l = CAST(wave::layout_t &, l);
            _l.out2 = 1;
            }
            );
s.add_edge("input", "in2", "in3","", "","",syntax::layout_true,
            [](syntax::layout_t  & l){
            wave::layout_t & _l = CAST(wave::layout_t &, l);
            _l.out3 = 0;
            }
            );
s.add_edge("input", "in2", "in3","", "","",syntax::layout_true,
            [](syntax::layout_t  & l){
            wave::layout_t & _l = CAST(wave::layout_t &, l);
            _l.out3 = 1;
            }
            );
s.add_edge("input", "in3", "in4","", "","",syntax::layout_true,
            [](syntax::layout_t  & l){
            wave::layout_t & _l = CAST(wave::layout_t &, l);
            _l.out4 = 0;
            }
            );
s.add_edge("input", "in3", "in4","", "","",syntax::layout_true,
            [](syntax::layout_t  & l){
            wave::layout_t & _l = CAST(wave::layout_t &, l);
            _l.out4 = 1;
            }
            );
s.add_edge("input", "in4", "in5","", "","",syntax::layout_true,
            [](syntax::layout_t  & l){
            wave::layout_t & _l = CAST(wave::layout_t &, l);
            _l.out5 = 0;
            }
            );
s.add_edge("input", "in4", "in5","", "","",syntax::layout_true,
            [](syntax::layout_t  & l){
            wave::layout_t & _l = CAST(wave::layout_t &, l);
            _l.out5 = 1;
            }
            );
s.add_edge("input", "in5", "in6","", "","",syntax::layout_true,
            [](syntax::layout_t  & l){
            wave::layout_t & _l = CAST(wave::layout_t &, l);
            _l.out6 = 0;
            }
            );
s.add_edge("input", "in5", "in6","", "","",syntax::layout_true,
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
s.add_location("input","input_end");
s.add_edge("input", "in8", "input_end");
	s.synchronizer<syntax::asynchronous_product_t>();
}
