#ifndef __SWTICH_TOP__
#define __SWTICH_TOP__

#include "comm_def.h"
#include "comm_func.h"
#include "ingress_sch.h"

using namespace std;

struct switch_top : sc_module {


    sc_in<TRANS>               *input_top_fifo;
    sc_in_clk                   clk; 

    void                        switch_top_process();
    ingress_sch                 *ingress_sch_mod;

    SC_CTOR(switch_top) 
     {
         
     ingress_sch_mod = new ingress_sch("ingress_sch");
     ingress_sch_mod->clk(clk);
     ingress_sch_mod->input_fifo->bind(*input_top_fifo);

   }  
   
};
#endif