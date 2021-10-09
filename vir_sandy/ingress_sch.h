#ifndef __INGRESS_SCH__
#define __INGRESS_SCH__

#include "comm_def.h"
#include "comm_func.h"


struct ingress_sch : sc_module {


    sc_in<TRANS>               *input_fifo;
    sc_in_clk                   clk; 


    int                         m_cycle_cnt;   
    deque<TRANS>                *input_que;
   

    void                        main_process();
    void                        recv_packet_process();
//    void                        sch_process();

  comm_stat_bw                   *m_bw_stat;
  global_config_c                *m_cfg;

 //   RR_SCH                      *rr_sch; 


    SC_CTOR(ingress_sch) 
     {

//    rr_sch = new RR_SCH(0);
      input_fifo = new  sc_in<TRANS>() ;
      input_que  = new  deque<TRANS>() ;

      m_cycle_cnt =0;
      m_cfg = new global_config_c();
      m_cfg->stat_period = 10 ;

      string debug_file = string("ingress_sach_debug.log");
      m_bw_stat =new comm_stat_bw(m_cfg, debug_file,g_m_inter_num);

 //     rr_sch = new RR_SCH(g_m_inter_num);


       SC_METHOD(main_process);
       sensitive << clk.pos();


   }  
   
};
#endif 