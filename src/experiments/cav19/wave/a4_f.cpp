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
	char b1_10;
	char b1_11;
	char b1_12;
	char b1_13;
	char b1_14;
	char b1_15;
	char b1_16;
	char b1_17;
	char b1_18;
	char b1_19;
	char b1_20;
	char b1_21;
	char b1_22;
	char b1_23;
	char b1_24;
	char b1_25;
	char b1_26;
	char b1_27;
	char b1_28;
	char b1_29;
	char b1_30;
	char b1_31;
	char b1_32;
	char b1_33;
	char b1_34;
	char out2;
	char b2_0;
	char b2_1;
	char b2_2;
	char b2_3;
	char b2_4;
	char b2_5;
	char b2_6;
	char b2_7;
	char b2_8;
	char b2_9;
	char b2_10;
	char b2_11;
	char b2_12;
	char b2_13;
	char b2_14;
	char b2_15;
	char b2_16;
	char b2_17;
	char b2_18;
	char b2_19;
	char b2_20;
	char out3;
	char b3_0;
	char b3_1;
	char out4;
	char out5;
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
	char out20;
	char out21;
	char out22;
	char out23;
	char out24;
	char out25;
	char out26;
	char out27;
	char out28;
	char out29;
	char out30;
	char out31;
	char out32;
	char out33;
	char out34;
	char out35;
	char out36;
	char out37;
	char out38;
	char out39;
layout_t() {
	out0 = 2;
	b0_0 = 2;
	b0_1 = 2;
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
	b1_10 = 2;
	b1_11 = 2;
	b1_12 = 2;
	b1_13 = 2;
	b1_14 = 2;
	b1_15 = 2;
	b1_16 = 2;
	b1_17 = 2;
	b1_18 = 2;
	b1_19 = 2;
	b1_20 = 2;
	b1_21 = 2;
	b1_22 = 2;
	b1_23 = 2;
	b1_24 = 2;
	b1_25 = 2;
	b1_26 = 2;
	b1_27 = 2;
	b1_28 = 2;
	b1_29 = 2;
	b1_30 = 2;
	b1_31 = 2;
	b1_32 = 2;
	b1_33 = 2;
	b1_34 = 2;
	out2 = 2;
	b2_0 = 2;
	b2_1 = 2;
	b2_2 = 2;
	b2_3 = 2;
	b2_4 = 2;
	b2_5 = 2;
	b2_6 = 2;
	b2_7 = 2;
	b2_8 = 2;
	b2_9 = 2;
	b2_10 = 2;
	b2_11 = 2;
	b2_12 = 2;
	b2_13 = 2;
	b2_14 = 2;
	b2_15 = 2;
	b2_16 = 2;
	b2_17 = 2;
	b2_18 = 2;
	b2_19 = 2;
	b2_20 = 2;
	out3 = 2;
	b3_0 = 2;
	b3_1 = 2;
	out4 = 2;
	out5 = 2;
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
	out20 = 2;
	out21 = 2;
	out22 = 2;
	out23 = 2;
	out24 = 2;
	out25 = 2;
	out26 = 2;
	out27 = 2;
	out28 = 2;
	out29 = 2;
	out30 = 2;
	out31 = 2;
	out32 = 2;
	out33 = 2;
	out34 = 2;
	out35 = 2;
	out36 = 2;
	out37 = 2;
	out38 = 2;
	out39 = 2;

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
	if(b1_10 != _l.b1_10) return false;
	if(b1_11 != _l.b1_11) return false;
	if(b1_12 != _l.b1_12) return false;
	if(b1_13 != _l.b1_13) return false;
	if(b1_14 != _l.b1_14) return false;
	if(b1_15 != _l.b1_15) return false;
	if(b1_16 != _l.b1_16) return false;
	if(b1_17 != _l.b1_17) return false;
	if(b1_18 != _l.b1_18) return false;
	if(b1_19 != _l.b1_19) return false;
	if(b1_20 != _l.b1_20) return false;
	if(b1_21 != _l.b1_21) return false;
	if(b1_22 != _l.b1_22) return false;
	if(b1_23 != _l.b1_23) return false;
	if(b1_24 != _l.b1_24) return false;
	if(b1_25 != _l.b1_25) return false;
	if(b1_26 != _l.b1_26) return false;
	if(b1_27 != _l.b1_27) return false;
	if(b1_28 != _l.b1_28) return false;
	if(b1_29 != _l.b1_29) return false;
	if(b1_30 != _l.b1_30) return false;
	if(b1_31 != _l.b1_31) return false;
	if(b1_32 != _l.b1_32) return false;
	if(b1_33 != _l.b1_33) return false;
	if(b1_34 != _l.b1_34) return false;
	if (out2 != _l.out2) return false;
	if(b2_0 != _l.b2_0) return false;
	if(b2_1 != _l.b2_1) return false;
	if(b2_2 != _l.b2_2) return false;
	if(b2_3 != _l.b2_3) return false;
	if(b2_4 != _l.b2_4) return false;
	if(b2_5 != _l.b2_5) return false;
	if(b2_6 != _l.b2_6) return false;
	if(b2_7 != _l.b2_7) return false;
	if(b2_8 != _l.b2_8) return false;
	if(b2_9 != _l.b2_9) return false;
	if(b2_10 != _l.b2_10) return false;
	if(b2_11 != _l.b2_11) return false;
	if(b2_12 != _l.b2_12) return false;
	if(b2_13 != _l.b2_13) return false;
	if(b2_14 != _l.b2_14) return false;
	if(b2_15 != _l.b2_15) return false;
	if(b2_16 != _l.b2_16) return false;
	if(b2_17 != _l.b2_17) return false;
	if(b2_18 != _l.b2_18) return false;
	if(b2_19 != _l.b2_19) return false;
	if(b2_20 != _l.b2_20) return false;
	if (out3 != _l.out3) return false;
	if(b3_0 != _l.b3_0) return false;
	if(b3_1 != _l.b3_1) return false;
	if (out4 != _l.out4) return false;
	if (out5 != _l.out5) return false;
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
	if (out20 != _l.out20) return false;
	if (out21 != _l.out21) return false;
	if (out22 != _l.out22) return false;
	if (out23 != _l.out23) return false;
	if (out24 != _l.out24) return false;
	if (out25 != _l.out25) return false;
	if (out26 != _l.out26) return false;
	if (out27 != _l.out27) return false;
	if (out28 != _l.out28) return false;
	if (out29 != _l.out29) return false;
	if (out30 != _l.out30) return false;
	if (out31 != _l.out31) return false;
	if (out32 != _l.out32) return false;
	if (out33 != _l.out33) return false;
	if (out34 != _l.out34) return false;
	if (out35 != _l.out35) return false;
	if (out36 != _l.out36) return false;
	if (out37 != _l.out37) return false;
	if (out38 != _l.out38) return false;
	if (out39 != _l.out39) return false;

        return true;
    }

    inline size_t hash() const {
      size_t seed = global_t::instance().hash_seed();
        
	boost::hash_combine(seed, out0);
	boost::hash_combine(seed, b0_0);
	boost::hash_combine(seed, b0_1);
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
	boost::hash_combine(seed, b1_10);
	boost::hash_combine(seed, b1_11);
	boost::hash_combine(seed, b1_12);
	boost::hash_combine(seed, b1_13);
	boost::hash_combine(seed, b1_14);
	boost::hash_combine(seed, b1_15);
	boost::hash_combine(seed, b1_16);
	boost::hash_combine(seed, b1_17);
	boost::hash_combine(seed, b1_18);
	boost::hash_combine(seed, b1_19);
	boost::hash_combine(seed, b1_20);
	boost::hash_combine(seed, b1_21);
	boost::hash_combine(seed, b1_22);
	boost::hash_combine(seed, b1_23);
	boost::hash_combine(seed, b1_24);
	boost::hash_combine(seed, b1_25);
	boost::hash_combine(seed, b1_26);
	boost::hash_combine(seed, b1_27);
	boost::hash_combine(seed, b1_28);
	boost::hash_combine(seed, b1_29);
	boost::hash_combine(seed, b1_30);
	boost::hash_combine(seed, b1_31);
	boost::hash_combine(seed, b1_32);
	boost::hash_combine(seed, b1_33);
	boost::hash_combine(seed, b1_34);
	boost::hash_combine(seed, out2);
	boost::hash_combine(seed, b2_0);
	boost::hash_combine(seed, b2_1);
	boost::hash_combine(seed, b2_2);
	boost::hash_combine(seed, b2_3);
	boost::hash_combine(seed, b2_4);
	boost::hash_combine(seed, b2_5);
	boost::hash_combine(seed, b2_6);
	boost::hash_combine(seed, b2_7);
	boost::hash_combine(seed, b2_8);
	boost::hash_combine(seed, b2_9);
	boost::hash_combine(seed, b2_10);
	boost::hash_combine(seed, b2_11);
	boost::hash_combine(seed, b2_12);
	boost::hash_combine(seed, b2_13);
	boost::hash_combine(seed, b2_14);
	boost::hash_combine(seed, b2_15);
	boost::hash_combine(seed, b2_16);
	boost::hash_combine(seed, b2_17);
	boost::hash_combine(seed, b2_18);
	boost::hash_combine(seed, b2_19);
	boost::hash_combine(seed, b2_20);
	boost::hash_combine(seed, out3);
	boost::hash_combine(seed, b3_0);
	boost::hash_combine(seed, b3_1);
	boost::hash_combine(seed, out4);
	boost::hash_combine(seed, out5);
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
	boost::hash_combine(seed, out20);
	boost::hash_combine(seed, out21);
	boost::hash_combine(seed, out22);
	boost::hash_combine(seed, out23);
	boost::hash_combine(seed, out24);
	boost::hash_combine(seed, out25);
	boost::hash_combine(seed, out26);
	boost::hash_combine(seed, out27);
	boost::hash_combine(seed, out28);
	boost::hash_combine(seed, out29);
	boost::hash_combine(seed, out30);
	boost::hash_combine(seed, out31);
	boost::hash_combine(seed, out32);
	boost::hash_combine(seed, out33);
	boost::hash_combine(seed, out34);
	boost::hash_combine(seed, out35);
	boost::hash_combine(seed, out36);
	boost::hash_combine(seed, out37);
	boost::hash_combine(seed, out38);
	boost::hash_combine(seed, out39);

      return seed;
    }

    void output(std::ostream & os) const {
        
	os << "out0=" << out0 << ",";
	os << "b0_0=" << b0_0 << ",";
	os << "b0_1=" << b0_1 << ",";
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
	os << "b1_1=" << b1_10 << ",";
	os << "b1_1=" << b1_11 << ",";
	os << "b1_1=" << b1_12 << ",";
	os << "b1_1=" << b1_13 << ",";
	os << "b1_1=" << b1_14 << ",";
	os << "b1_1=" << b1_15 << ",";
	os << "b1_1=" << b1_16 << ",";
	os << "b1_1=" << b1_17 << ",";
	os << "b1_1=" << b1_18 << ",";
	os << "b1_1=" << b1_19 << ",";
	os << "b1_1=" << b1_20 << ",";
	os << "b1_1=" << b1_21 << ",";
	os << "b1_1=" << b1_22 << ",";
	os << "b1_1=" << b1_23 << ",";
	os << "b1_1=" << b1_24 << ",";
	os << "b1_1=" << b1_25 << ",";
	os << "b1_1=" << b1_26 << ",";
	os << "b1_1=" << b1_27 << ",";
	os << "b1_1=" << b1_28 << ",";
	os << "b1_1=" << b1_29 << ",";
	os << "b1_1=" << b1_30 << ",";
	os << "b1_1=" << b1_31 << ",";
	os << "b1_1=" << b1_32 << ",";
	os << "b1_1=" << b1_33 << ",";
	os << "b1_1=" << b1_34 << ",";
	os << "out2=" << out2 << ",";
	os << "b2_1=" << b2_0 << ",";
	os << "b2_1=" << b2_1 << ",";
	os << "b2_1=" << b2_2 << ",";
	os << "b2_1=" << b2_3 << ",";
	os << "b2_1=" << b2_4 << ",";
	os << "b2_1=" << b2_5 << ",";
	os << "b2_1=" << b2_6 << ",";
	os << "b2_1=" << b2_7 << ",";
	os << "b2_1=" << b2_8 << ",";
	os << "b2_1=" << b2_9 << ",";
	os << "b2_1=" << b2_10 << ",";
	os << "b2_1=" << b2_11 << ",";
	os << "b2_1=" << b2_12 << ",";
	os << "b2_1=" << b2_13 << ",";
	os << "b2_1=" << b2_14 << ",";
	os << "b2_1=" << b2_15 << ",";
	os << "b2_1=" << b2_16 << ",";
	os << "b2_1=" << b2_17 << ",";
	os << "b2_1=" << b2_18 << ",";
	os << "b2_1=" << b2_19 << ",";
	os << "b2_1=" << b2_20 << ",";
	os << "out3=" << out3 << ",";
	os << "b3_0=" << b3_0 << ",";
	os << "b3_1=" << b3_1 << ",";
	os << "out4=" << out4 << ",";
	os << "out5=" << out5 << ",";
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
	os << "out20=" << out20 << ",";
	os << "out21=" << out21 << ",";
	os << "out22=" << out22 << ",";
	os << "out23=" << out23 << ",";
	os << "out24=" << out24 << ",";
	os << "out25=" << out25 << ",";
	os << "out26=" << out26 << ",";
	os << "out27=" << out27 << ",";
	os << "out28=" << out28 << ",";
	os << "out29=" << out29 << ",";
	os << "out30=" << out30 << ",";
	os << "out31=" << out31 << ",";
	os << "out32=" << out32 << ",";
	os << "out33=" << out33 << ",";
	os << "out34=" << out34 << ",";
	os << "out35=" << out35 << ",";
	os << "out36=" << out36 << ",";
	os << "out37=" << out37 << ",";
	os << "out38=" << out38 << ",";
	os << "out39=" << out39 << ",";

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
s.add_label("err");
s.add_label("unreachable");
s.add_process("Node0");
s.add_location("Node0", "down", "x0<=100", "", syntax::loc_t::INIT);
s.add_location("Node0", "up", "x0<=300", "");
s.add_edge("Node0", "down", "up", "x0>=100 && x0 <= 300 && t <= 1000", "", "",
                    [](syntax::layout_t const & l){
                       wave::layout_t const & _l = CAST(wave::layout_t const &, l);
                       return _l.out3 < 2 && _l.out4 < 2 && _l.out3 == 1 && _l.out4 == 1;
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


                    });
                    
s.add_edge("Node0", "down", "up", "x0>=100 && x0<=300", "", "", 
                    [](syntax::layout_t const & l){
                       wave::layout_t const & _l = CAST(wave::layout_t const &, l);
                       return _l.out3 < 2 && _l.out4 < 2 && (_l.out3 == 1 && _l.out4 == 1)==0;
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
                       return (_l.out3 != 2 &&  _l.out4 != 2) == 0;
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
                       return _l.out5 < 2 && _l.out6 < 2 && _l.out7 < 2 && _l.out8 < 2 && _l.out9 < 2 && _l.out10 < 2 && _l.out11 < 2 && _l.out12 < 2 && _l.out13 < 2 && _l.out14 < 2 && _l.out15 < 2 && _l.out16 < 2 && _l.out17 < 2 && _l.out18 < 2 && _l.out19 < 2 && _l.out20 < 2 && _l.out21 < 2 && _l.out22 < 2 && _l.out23 < 2 && _l.out24 < 2 && _l.out25 < 2 && _l.out26 < 2 && _l.out27 < 2 && _l.out28 < 2 && _l.out29 < 2 && _l.out30 < 2 && _l.out31 < 2 && _l.out32 < 2 && _l.out33 < 2 && _l.out34 < 2 && _l.out35 < 2 && _l.out36 < 2 && _l.out37 < 2 && _l.out38 < 2 && _l.out39 < 2 && (_l.out5+(_l.out6+(_l.out7+(_l.out8+(_l.out9+(_l.out10+(_l.out11+(_l.out12+(_l.out13+(_l.out14+(_l.out15+(_l.out16+(_l.out17+(_l.out18+(_l.out19+(_l.out20+(_l.out21+(_l.out22+(_l.out23+(_l.out24+(_l.out25+(_l.out26+(_l.out27+(_l.out28+(_l.out29+(_l.out30+(_l.out31+(_l.out32+(_l.out33+(_l.out34+(_l.out35+(_l.out36+(_l.out37+(_l.out38+(_l.out39))))))))))))))))))))))))))))))))))) >= 10;
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
                       return _l.out5 < 2 && _l.out6 < 2 && _l.out7 < 2 && _l.out8 < 2 && _l.out9 < 2 && _l.out10 < 2 && _l.out11 < 2 && _l.out12 < 2 && _l.out13 < 2 && _l.out14 < 2 && _l.out15 < 2 && _l.out16 < 2 && _l.out17 < 2 && _l.out18 < 2 && _l.out19 < 2 && _l.out20 < 2 && _l.out21 < 2 && _l.out22 < 2 && _l.out23 < 2 && _l.out24 < 2 && _l.out25 < 2 && _l.out26 < 2 && _l.out27 < 2 && _l.out28 < 2 && _l.out29 < 2 && _l.out30 < 2 && _l.out31 < 2 && _l.out32 < 2 && _l.out33 < 2 && _l.out34 < 2 && _l.out35 < 2 && _l.out36 < 2 && _l.out37 < 2 && _l.out38 < 2 && _l.out39 < 2 && (_l.out5+(_l.out6+(_l.out7+(_l.out8+(_l.out9+(_l.out10+(_l.out11+(_l.out12+(_l.out13+(_l.out14+(_l.out15+(_l.out16+(_l.out17+(_l.out18+(_l.out19+(_l.out20+(_l.out21+(_l.out22+(_l.out23+(_l.out24+(_l.out25+(_l.out26+(_l.out27+(_l.out28+(_l.out29+(_l.out30+(_l.out31+(_l.out32+(_l.out33+(_l.out34+(_l.out35+(_l.out36+(_l.out37+(_l.out38+(_l.out39))))))))))))))))))))))))))))))))))) < 10;
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
                       return (_l.out5 != 2 && (_l.out6 != 2 && (_l.out7 != 2 && (_l.out8 != 2 && (_l.out9 != 2 && (_l.out10 != 2 && (_l.out11 != 2 && (_l.out12 != 2 && (_l.out13 != 2 && (_l.out14 != 2 && (_l.out15 != 2 && (_l.out16 != 2 && (_l.out17 != 2 && (_l.out18 != 2 && (_l.out19 != 2 && (_l.out20 != 2 && (_l.out21 != 2 && (_l.out22 != 2 && (_l.out23 != 2 && (_l.out24 != 2 && (_l.out25 != 2 && (_l.out26 != 2 && (_l.out27 != 2 && (_l.out28 != 2 && (_l.out29 != 2 && (_l.out30 != 2 && (_l.out31 != 2 && (_l.out32 != 2 && (_l.out33 != 2 && (_l.out34 != 2 && (_l.out35 != 2 && (_l.out36 != 2 && (_l.out37 != 2 && (_l.out38 != 2 && (_l.out39 != 2))))))))))))))))))))))))))))))))))) == 0;
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
                       return _l.out5 < 2 && _l.out6 < 2 && _l.out7 < 2 && _l.out8 < 2 && _l.out9 < 2 && _l.out10 < 2 && _l.out11 < 2 && _l.out12 < 2 && _l.out13 < 2 && _l.out14 < 2 && _l.out15 < 2 && _l.out16 < 2 && _l.out17 < 2 && _l.out18 < 2 && _l.out19 < 2 && _l.out20 < 2 && _l.out21 < 2 && _l.out22 < 2 && _l.out23 < 2 && _l.out24 < 2 && _l.out1 < 2 && (_l.out5+(_l.out6+(_l.out7+(_l.out8+(_l.out9+(_l.out10+(_l.out11+(_l.out12+(_l.out13+(_l.out14+(_l.out15+(_l.out16+(_l.out17+(_l.out18+(_l.out19+(_l.out20+(_l.out21+(_l.out22+(_l.out23+(_l.out24+(_l.out1))))))))))))))))))))) >= 10;
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
                       return _l.out5 < 2 && _l.out6 < 2 && _l.out7 < 2 && _l.out8 < 2 && _l.out9 < 2 && _l.out10 < 2 && _l.out11 < 2 && _l.out12 < 2 && _l.out13 < 2 && _l.out14 < 2 && _l.out15 < 2 && _l.out16 < 2 && _l.out17 < 2 && _l.out18 < 2 && _l.out19 < 2 && _l.out20 < 2 && _l.out21 < 2 && _l.out22 < 2 && _l.out23 < 2 && _l.out24 < 2 && _l.out1 < 2 && (_l.out5+(_l.out6+(_l.out7+(_l.out8+(_l.out9+(_l.out10+(_l.out11+(_l.out12+(_l.out13+(_l.out14+(_l.out15+(_l.out16+(_l.out17+(_l.out18+(_l.out19+(_l.out20+(_l.out21+(_l.out22+(_l.out23+(_l.out24+(_l.out1))))))))))))))))))))) < 10;
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
                       return (_l.out5 != 2 && (_l.out6 != 2 && (_l.out7 != 2 && (_l.out8 != 2 && (_l.out9 != 2 && (_l.out10 != 2 && (_l.out11 != 2 && (_l.out12 != 2 && (_l.out13 != 2 && (_l.out14 != 2 && (_l.out15 != 2 && (_l.out16 != 2 && (_l.out17 != 2 && (_l.out18 != 2 && (_l.out19 != 2 && (_l.out20 != 2 && (_l.out21 != 2 && (_l.out22 != 2 && (_l.out23 != 2 && (_l.out24 != 2 && (_l.out1 != 2))))))))))))))))))))) == 0;
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
                       return _l.out1 < 2 && _l.out2 < 2 && (_l.out1 == 0 && _l.out2 == 0) == 0;
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
                       return _l.out1 < 2 && _l.out2 < 2 && _l.out1 == 0 && _l.out2 == 0;
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
                       return (_l.out1 != 2 &&  _l.out2 != 2) == 0;
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
                       return _l.out2 < 2 && (1-_l.out2)==1;
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
                       return _l.out2 < 2 && (1-_l.out2) ==0;
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
                       return _l.out2 == 2;
                    }
                    );
s.add_edge("Node4", "up", "down", "x4 <= 0", "x4", "",syntax::layout_true,
                    [](syntax::layout_t  & l){
                       wave::layout_t & _l = CAST(wave::layout_t &, l);
                       _l.out4 = 2;
                    }
                    );
s.add_process("input");
s.add_location("input","input_init","","",syntax::loc_t::INIT | syntax::loc_t::COMMITTED);
s.add_location("input","in5","","",syntax::loc_t::COMMITTED);
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
s.add_location("input","in20","","",syntax::loc_t::COMMITTED);
s.add_location("input","in21","","",syntax::loc_t::COMMITTED);
s.add_location("input","in22","","",syntax::loc_t::COMMITTED);
s.add_location("input","in23","","",syntax::loc_t::COMMITTED);
s.add_location("input","in24","","",syntax::loc_t::COMMITTED);
s.add_location("input","in25","","",syntax::loc_t::COMMITTED);
s.add_location("input","in26","","",syntax::loc_t::COMMITTED);
s.add_location("input","in27","","",syntax::loc_t::COMMITTED);
s.add_location("input","in28","","",syntax::loc_t::COMMITTED);
s.add_location("input","in29","","",syntax::loc_t::COMMITTED);
s.add_location("input","in30","","",syntax::loc_t::COMMITTED);
s.add_location("input","in31","","",syntax::loc_t::COMMITTED);
s.add_location("input","in32","","",syntax::loc_t::COMMITTED);
s.add_location("input","in33","","",syntax::loc_t::COMMITTED);
s.add_location("input","in34","","",syntax::loc_t::COMMITTED);
s.add_location("input","in35","","",syntax::loc_t::COMMITTED);
s.add_location("input","in36","","",syntax::loc_t::COMMITTED);
s.add_location("input","in37","","",syntax::loc_t::COMMITTED);
s.add_location("input","in38","","",syntax::loc_t::COMMITTED);
s.add_location("input","in39","","",syntax::loc_t::COMMITTED);
s.add_edge("input", "input_init", "in5","", "","",syntax::layout_true,
            [](syntax::layout_t  & l){
            wave::layout_t & _l = CAST(wave::layout_t &, l);
            _l.out5 = 0;
            }
            );
s.add_edge("input", "input_init", "in5","", "","",syntax::layout_true,
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
s.add_edge("input", "in19", "in20","", "","",syntax::layout_true,
            [](syntax::layout_t  & l){
            wave::layout_t & _l = CAST(wave::layout_t &, l);
            _l.out20 = 0;
            }
            );
s.add_edge("input", "in19", "in20","", "","",syntax::layout_true,
            [](syntax::layout_t  & l){
            wave::layout_t & _l = CAST(wave::layout_t &, l);
            _l.out20 = 1;
            }
            );
s.add_edge("input", "in20", "in21","", "","",syntax::layout_true,
            [](syntax::layout_t  & l){
            wave::layout_t & _l = CAST(wave::layout_t &, l);
            _l.out21 = 0;
            }
            );
s.add_edge("input", "in20", "in21","", "","",syntax::layout_true,
            [](syntax::layout_t  & l){
            wave::layout_t & _l = CAST(wave::layout_t &, l);
            _l.out21 = 1;
            }
            );
s.add_edge("input", "in21", "in22","", "","",syntax::layout_true,
            [](syntax::layout_t  & l){
            wave::layout_t & _l = CAST(wave::layout_t &, l);
            _l.out22 = 0;
            }
            );
s.add_edge("input", "in21", "in22","", "","",syntax::layout_true,
            [](syntax::layout_t  & l){
            wave::layout_t & _l = CAST(wave::layout_t &, l);
            _l.out22 = 1;
            }
            );
s.add_edge("input", "in22", "in23","", "","",syntax::layout_true,
            [](syntax::layout_t  & l){
            wave::layout_t & _l = CAST(wave::layout_t &, l);
            _l.out23 = 0;
            }
            );
s.add_edge("input", "in22", "in23","", "","",syntax::layout_true,
            [](syntax::layout_t  & l){
            wave::layout_t & _l = CAST(wave::layout_t &, l);
            _l.out23 = 1;
            }
            );
s.add_edge("input", "in23", "in24","", "","",syntax::layout_true,
            [](syntax::layout_t  & l){
            wave::layout_t & _l = CAST(wave::layout_t &, l);
            _l.out24 = 0;
            }
            );
s.add_edge("input", "in23", "in24","", "","",syntax::layout_true,
            [](syntax::layout_t  & l){
            wave::layout_t & _l = CAST(wave::layout_t &, l);
            _l.out24 = 1;
            }
            );
s.add_edge("input", "in24", "in25","", "","",syntax::layout_true,
            [](syntax::layout_t  & l){
            wave::layout_t & _l = CAST(wave::layout_t &, l);
            _l.out25 = 0;
            }
            );
s.add_edge("input", "in24", "in25","", "","",syntax::layout_true,
            [](syntax::layout_t  & l){
            wave::layout_t & _l = CAST(wave::layout_t &, l);
            _l.out25 = 1;
            }
            );
s.add_edge("input", "in25", "in26","", "","",syntax::layout_true,
            [](syntax::layout_t  & l){
            wave::layout_t & _l = CAST(wave::layout_t &, l);
            _l.out26 = 0;
            }
            );
s.add_edge("input", "in25", "in26","", "","",syntax::layout_true,
            [](syntax::layout_t  & l){
            wave::layout_t & _l = CAST(wave::layout_t &, l);
            _l.out26 = 1;
            }
            );
s.add_edge("input", "in26", "in27","", "","",syntax::layout_true,
            [](syntax::layout_t  & l){
            wave::layout_t & _l = CAST(wave::layout_t &, l);
            _l.out27 = 0;
            }
            );
s.add_edge("input", "in26", "in27","", "","",syntax::layout_true,
            [](syntax::layout_t  & l){
            wave::layout_t & _l = CAST(wave::layout_t &, l);
            _l.out27 = 1;
            }
            );
s.add_edge("input", "in27", "in28","", "","",syntax::layout_true,
            [](syntax::layout_t  & l){
            wave::layout_t & _l = CAST(wave::layout_t &, l);
            _l.out28 = 0;
            }
            );
s.add_edge("input", "in27", "in28","", "","",syntax::layout_true,
            [](syntax::layout_t  & l){
            wave::layout_t & _l = CAST(wave::layout_t &, l);
            _l.out28 = 1;
            }
            );
s.add_edge("input", "in28", "in29","", "","",syntax::layout_true,
            [](syntax::layout_t  & l){
            wave::layout_t & _l = CAST(wave::layout_t &, l);
            _l.out29 = 0;
            }
            );
s.add_edge("input", "in28", "in29","", "","",syntax::layout_true,
            [](syntax::layout_t  & l){
            wave::layout_t & _l = CAST(wave::layout_t &, l);
            _l.out29 = 1;
            }
            );
s.add_edge("input", "in29", "in30","", "","",syntax::layout_true,
            [](syntax::layout_t  & l){
            wave::layout_t & _l = CAST(wave::layout_t &, l);
            _l.out30 = 0;
            }
            );
s.add_edge("input", "in29", "in30","", "","",syntax::layout_true,
            [](syntax::layout_t  & l){
            wave::layout_t & _l = CAST(wave::layout_t &, l);
            _l.out30 = 1;
            }
            );
s.add_edge("input", "in30", "in31","", "","",syntax::layout_true,
            [](syntax::layout_t  & l){
            wave::layout_t & _l = CAST(wave::layout_t &, l);
            _l.out31 = 0;
            }
            );
s.add_edge("input", "in30", "in31","", "","",syntax::layout_true,
            [](syntax::layout_t  & l){
            wave::layout_t & _l = CAST(wave::layout_t &, l);
            _l.out31 = 1;
            }
            );
s.add_edge("input", "in31", "in32","", "","",syntax::layout_true,
            [](syntax::layout_t  & l){
            wave::layout_t & _l = CAST(wave::layout_t &, l);
            _l.out32 = 0;
            }
            );
s.add_edge("input", "in31", "in32","", "","",syntax::layout_true,
            [](syntax::layout_t  & l){
            wave::layout_t & _l = CAST(wave::layout_t &, l);
            _l.out32 = 1;
            }
            );
s.add_edge("input", "in32", "in33","", "","",syntax::layout_true,
            [](syntax::layout_t  & l){
            wave::layout_t & _l = CAST(wave::layout_t &, l);
            _l.out33 = 0;
            }
            );
s.add_edge("input", "in32", "in33","", "","",syntax::layout_true,
            [](syntax::layout_t  & l){
            wave::layout_t & _l = CAST(wave::layout_t &, l);
            _l.out33 = 1;
            }
            );
s.add_edge("input", "in33", "in34","", "","",syntax::layout_true,
            [](syntax::layout_t  & l){
            wave::layout_t & _l = CAST(wave::layout_t &, l);
            _l.out34 = 0;
            }
            );
s.add_edge("input", "in33", "in34","", "","",syntax::layout_true,
            [](syntax::layout_t  & l){
            wave::layout_t & _l = CAST(wave::layout_t &, l);
            _l.out34 = 1;
            }
            );
s.add_edge("input", "in34", "in35","", "","",syntax::layout_true,
            [](syntax::layout_t  & l){
            wave::layout_t & _l = CAST(wave::layout_t &, l);
            _l.out35 = 0;
            }
            );
s.add_edge("input", "in34", "in35","", "","",syntax::layout_true,
            [](syntax::layout_t  & l){
            wave::layout_t & _l = CAST(wave::layout_t &, l);
            _l.out35 = 1;
            }
            );
s.add_edge("input", "in35", "in36","", "","",syntax::layout_true,
            [](syntax::layout_t  & l){
            wave::layout_t & _l = CAST(wave::layout_t &, l);
            _l.out36 = 0;
            }
            );
s.add_edge("input", "in35", "in36","", "","",syntax::layout_true,
            [](syntax::layout_t  & l){
            wave::layout_t & _l = CAST(wave::layout_t &, l);
            _l.out36 = 1;
            }
            );
s.add_edge("input", "in36", "in37","", "","",syntax::layout_true,
            [](syntax::layout_t  & l){
            wave::layout_t & _l = CAST(wave::layout_t &, l);
            _l.out37 = 0;
            }
            );
s.add_edge("input", "in36", "in37","", "","",syntax::layout_true,
            [](syntax::layout_t  & l){
            wave::layout_t & _l = CAST(wave::layout_t &, l);
            _l.out37 = 1;
            }
            );
s.add_edge("input", "in37", "in38","", "","",syntax::layout_true,
            [](syntax::layout_t  & l){
            wave::layout_t & _l = CAST(wave::layout_t &, l);
            _l.out38 = 0;
            }
            );
s.add_edge("input", "in37", "in38","", "","",syntax::layout_true,
            [](syntax::layout_t  & l){
            wave::layout_t & _l = CAST(wave::layout_t &, l);
            _l.out38 = 1;
            }
            );
s.add_edge("input", "in38", "in39","", "","",syntax::layout_true,
            [](syntax::layout_t  & l){
            wave::layout_t & _l = CAST(wave::layout_t &, l);
            _l.out39 = 0;
            }
            );
s.add_edge("input", "in38", "in39","", "","",syntax::layout_true,
            [](syntax::layout_t  & l){
            wave::layout_t & _l = CAST(wave::layout_t &, l);
            _l.out39 = 1;
            }
            );
s.add_location("input","input_end");
s.add_edge("input", "in39", "input_end");
	s.synchronizer<syntax::asynchronous_product_t>();
}
