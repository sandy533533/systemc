#include "switch_top.h"

switch_top::switch_top(sc_module_name name, global_config_c *glb_cfg):sc_module(name)
{
 
    m_cfg = glb_cfg;
    m_name = string(name) ;

// 例化 ingress_sch_mod 模块

//    ingress_sch ingress_sch_mod("u_switch_top", glb_cfg);
//    ingress_sch_mod.clk(clk);

    ingress_sch_mod = new ingress_sch("u_switch_top", m_cfg);
    ingress_sch_mod->clk(clk);

//    pe_engress pe_engress_mod("u_switch_top", glb_cfg);
//    pe_engress_mod.clk(clk);

    pe_engress_mod  = new pe_engress("u_switch_top", m_cfg);
    pe_engress_mod->clk(clk);

   


    tmp_fifo.resize(g_m_inter_num);

    for(int i=0; i < g_m_inter_num; i++)
    {
        tmp_fifo[i] =new sc_fifo<TRANS>;
    }  

    SC_METHOD(switch_top_process);
    sensitive << clk.pos();

}



void switch_top::switch_top_process()
{
//ingress_sch_mod不是指针，所以不是.而是->
 for(int i =0; i < g_m_inter_num; i++)
 {
   // ingress_sch_mod->output_sch_que[i] =tmp_fifo[i];

   // pe_engress_mod->input_sch_que[i] =tmp_fifo[i];

//    switch_top_mod.->bind(*tmp_fifo[i]);
    
 }

}
    

    