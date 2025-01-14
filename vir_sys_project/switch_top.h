#ifndef __SWITCH_TOP__
#define __SWITCH_TOP__

#include "comm_def.h"
#include "comm_func.h"
#include "ingress_sch.h"
#include "pe_engress.h"

class switch_top: public sc_module
{
  public: 
 //   vector<sc_fifo_in<TRANS * > >  input_fifo;
    vector   <sc_fifo_in<TRANS> *>  input_top_fifo;
    SC_HAS_PROCESS                  (switch_top);
    sc_in_clk                       clk; 
    global_config_c                 *m_cfg;
    string                          m_name;

  public:
    switch_top(sc_module_name name, global_config_c *glb_cfg);
    
    void                           switch_top_process();
    ingress_sch                    *ingress_sch_mod;
    pe_engress                     *pe_engress_mod ;

  private:
    vector   < sc_fifo<TRANS> * >  tmp_fifo; 
    vector   < sc_fifo<TRANS> * >  tmp_fifo1; 



};
 

#endif
