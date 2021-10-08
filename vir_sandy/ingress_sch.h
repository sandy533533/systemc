#ifndef __INGRESS_SCH__
#define __INGRESS_SCH__

#include "comm_def.h"
#include "comm_func.h"


struct ingress_sch : sc_module {


    sc_in<TRANS>               *input_fifo;
    sc_in_clk                   clk; 

    void                        main_process();
//    void                        recv_packet_process();
//    void                        sch_process();

 //   RR_SCH                      *rr_sch; 


    SC_CTOR(ingress_sch) 
     {

//    rr_sch = new RR_SCH(0);

       SC_METHOD(main_process);
       sensitive << clk.pos();


   }  
   
};
#endif 