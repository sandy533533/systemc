#ifndef __INGRESS_SCH__
#define __INGRESS_SCH__

#include "comm_def.h"
#include "comm_func.h"


SC_MODULE(ingress_sch)
{
  // channels
  sc_in <TRANS_STR>                   input_fifo;
  sc_in_clk                           clk; 

  deque<TRANS_STR>                    input_que;
  int                                 m_cycle_cnt;

  comm_stat_bw                        *m_bw_stat;
  RR_SCH                              *rr_sch; 

 global_config_c                      *m_cfg;
 

    void                             main_process();
    void                             recv_packet_process();
    void                             sch_process();


  // constructor
  SC_CTOR(ingress_sch)
  {
     m_cycle_cnt =0;
      rr_sch = new RR_SCH(g_m_inter_num);
      m_cfg = new global_config_c();

     m_cfg->stat_period = 10 ;

    string debug_file = string("ingress_sach_debug.log");

    m_bw_stat =new comm_stat_bw(m_cfg, debug_file,g_m_inter_num);

    SC_METHOD(main_process);   
 //   SC_THREAD(main_process);
    sensitive << input_fifo;

  }


}; // end class simple_bus_test

#endif
