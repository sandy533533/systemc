
#ifndef SWITCH_TOP_H_INCLUDED
#define SWITCH_TOP_H_INCLUDED



#include "comm_def.h"
#include "comm_func.h"
#include "ingress_sch.h"
using namespace std;


struct switch_top : sc_module {

    sc_in_clk                  clk;
    sc_in     <TRANS_STR>      input;

    ingress_sch                 *ingress_sch_mode ;

    SC_CTOR(switch_top) 
     {
        
     ingress_sch_mode = new ingress_sch("ingress");
     ingress_sch_mode->clk(clk);
     ingress_sch_mode->input_fifo(input);

   }  
   
};
#endif // SWITCH_TOP_H_INCLUDED