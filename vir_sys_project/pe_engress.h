#ifndef __PE_ENGRESS__
#define __PE_ENGRESS__

#include "comm_def.h"
#include "comm_func.h"

class pe_engress: public sc_module
{
  public: 
  // input

    vector<sc_fifo_in<TRANS> *>  input_sch_que;
    sc_in_clk                    clk; 

  //output

    vector<sc_fifo_out<TRANS> *> output_engress_fifo;
  //cpu

    global_config_c              *m_cfg;
  // stat  

    comm_stat_bw                 *m_bw_stat;
  
    SC_HAS_PROCESS(pe_engress);

  public:
    pe_engress(string name, global_config_c *glb_cfg);
    void                        main_process();

    void                        recv_inpacket_process();
  
    void                        send_outpacket_process();
    void                        send_sch_process();

  private:
    vector<deque<TRANS> >       output_que;
    int                         m_cycle_cnt;
    RR_SCH                      *out_rr_sch; 
    SP_SCH                      *out_sp_sch; 
    bool                        rst_flag ;
    int                         rst_que ;

};
 

#endif