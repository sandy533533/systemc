

#include "stdio.h"
#include <iostream>
#include "packet_gen.h"
#include "switch_top.h"
//#include "ingress_sch.h"

#include "systemc.h"
#include <memory>
#include "comm_def.h"
#include "comm_func.h"

using namespace std;


int sc_main(int argc, char *argv[])


{


   sc_clock    clk                    ("clk",100,SC_NS);  //100ns 对应10MHZ 

   sc_signal<TRANS>     *tmp_signal;  

// new 分配动态内存

     tmp_signal = new sc_signal<TRANS>;
  

   //init module
   // reg config  ?
   global_config_c *glb_cfg = new global_config_c();

   
   packet_gen_module pkt_gen_mod("packet_gen", glb_cfg);
   pkt_gen_mod.clk(clk);
   pkt_gen_mod.output->bind(*tmp_signal);


   switch_top switch_top_mod("u_switch_top");
   switch_top_mod.clk(clk);
   switch_top_mod.input_top_fifo->bind(*tmp_signal);

/*
     ingress_sch  ingress_sch_mod ("ingress_sch");
     ingress_sch_mod.clk(clk);
     ingress_sch_mod.input_fifo->bind(*tmp_signal);
*/
     
  
   //char

   sc_start(100,SC_MS);

   return 0;
}