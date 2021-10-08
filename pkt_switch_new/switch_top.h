
#ifndef SWITCH_TOP_H_INCLUDED
#define SWITCH_TOP_H_INCLUDED

#include "switch.h"

struct switch_top : sc_module {

    sc_in<bool>  switch_cntrl;
    sc_in<pkt>  in0;
    sc_in<pkt>  in1;
    sc_in<pkt>  in2;
    sc_in<pkt>  in3;

    sc_out<pkt>  out0;
    sc_out<pkt>  out1;
    sc_out<pkt>  out2;
    sc_out<pkt>  out3;   

    mcast_pkt_switch  *switch1 ;

    SC_CTOR(switch_top) 
     {
     switch1 = new mcast_pkt_switch("SWITCH");
     switch1->switch_cntrl(switch_cntrl);
     switch1->in0(in0);
     switch1->in1(in1);
     switch1->in2(in2);
     switch1->in3(in3);
     switch1->out0(out0);
     switch1->out1(out1);
     switch1->out2(out2);
     switch1->out3(out3);

   }  
   
};
#endif // SWITCH_TOP_H_INCLUDED