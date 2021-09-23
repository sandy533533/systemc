#include "switch_top.h"

switch_top::switch_top(string name, global_config_c *glb_cfg):sc_module(name)
{
 /*   
    input_top_fifo.resize(g_m_inter_num);

    for(int i=0; i < g_m_inter_num; i++)
    {
        input_top_fifo[i] = new sc_fifo_in<TRANS>();
    }

*/
    m_cfg = glb_cfg;
    m_name = name ;

// 例化 ingress_sch_mod 模块

      ingress_sch_mod = new ingress_sch(m_name, m_cfg);
      ingress_sch_mod->clk(clk);

    SC_METHOD(switch_top_process);
    sensitive << clk.pos();

}



void switch_top::switch_top_process()
{
//ingress_sch_mod不是指针，所以不是.而是->
 for(int i =0; i < g_m_inter_num; i++)
 {
// 方法一：       
 //     input_top_fifo[i] = ingress_sch_mod->input_fifo[i];
// 方法二：
 //   (*input_top_fifo[i] )(*(ingress_sch_mod->input_fifo[i])) ;
    
 }


}
    

    