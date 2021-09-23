#ifndef __INGRESS_SCH__
#define __INGRESS_SCH__

#include "comm_def.h"
#include "comm_func.h"

class ingress_sch: public sc_module
{
  public: 
    vector<sc_fifo_in<TRANS> *> input_fifo;
    sc_in_clk                   clk; 
    global_config_c             *m_cfg;
    comm_stat_bw                *m_bw_stat;

    SC_HAS_PROCESS(ingress_sch);

  public:
    ingress_sch(string name, global_config_c *glb_cfg);
    void main_process();
    void recv_packet_process();
    void sch_process();
  private:
    vector<deque<TRANS> >   input_que;
    int                     m_cycle_cnt;
    RR_SCH                  *rr_sch; 
    SP_SCH                  *sp_sch; 
   
};
 

#endif