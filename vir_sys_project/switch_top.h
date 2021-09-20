#ifndef __SWITCH_TOP__
#define __SWITCH_TOP__

#include "comm_def.h"
#include "comm_func.h"
#include "ingress_sch.h"

class switch_top: public sc_module
{
  public: 
    vector<sc_fifo_in<TRANS> *>  input_fifo;
    sc_in_clk                    clk; 
    global_config_c              *m_cfg;
    string                       m_name;
    SC_HAS_PROCESS               (switch_top);


  public:
    switch_top(string name, global_config_c *glb_cfg);
    void switch_top_process();
    ingress_sch         *ingress_sch_mod;


};
 

#endif
