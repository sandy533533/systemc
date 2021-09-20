#include "switch_top.h"

switch_top::switch_top(string name, global_config_c *glb_cfg):sc_module(name)
{
    input_fifo.resize(g_m_inter_num);

    for(int i=0; i < g_m_inter_num; i++)
    {
        input_fifo[i] = new sc_fifo_in<TRANS>();
    }

    m_cfg = glb_cfg;
    m_name = name ;

    ingress_sch ingress_sch_mod(string m_name, global_config_c *m_cfg);


    SC_METHOD(switch_top_process);
    sensitive << clk.pos();

}
void switch_top::switch_top_process()
{
    vector      < sc_fifo<TRANS> * >   tmp_fifo;  

     for(int i =0; i < g_m_inter_num; i++)
    {
       (tmp_fifo[i])-> bind (*input_fifo[i]);
    }


   for(int i =0; i < g_m_inter_num; i++)
   {
      ingress_sch.input_fifo[i]->bind(*tmp_fifo[i]);

   }

}
    

    