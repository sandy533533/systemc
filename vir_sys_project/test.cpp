

#include "stdio.h"
#include <iostream>
#include "packet_gen.h"
#include "switch_top.h"

#include "systemc.h"
#include <memory>
#include "comm_def.h"
#include "comm_func.h"
using namespace std;


int sc_main(int argc, char *argv[])




{
  
//systemC中并不允许直接调用通道，不同模块之间进行通信必须通过端口。

//在同一模块里，各个进程之间需要通信，他们可以通过共享变量、握手信号、模块内通道等方式通信。
//如果他们之间的通信是通过模块内通道。

//sc_fifo<T>

//sc_fifo是SystemC库中已经实现好的FIFO通道，其中T为FIFO中存储的数据类型。
//write(&T)代表写FIFO的方法，read()是读FIFO的方法。
//Num_free()查询FIFO还有多少空单元，num_available()查询FIFO还有多少个数据可以读。对于fifo的size，默认深度为16.

   sc_clock    clk                    ("clk",100,SC_NS);  //100ns 对应10MHZ 

   vector      < sc_fifo<TRANS> * >   tmp_fifo;  

// new 分配动态内存
   tmp_fifo.resize(g_m_inter_num);

   for(int i=0; i < g_m_inter_num; i++)
   {
 //     tmp_fifo[i] =new sc_fifo<TRANS>();
     tmp_fifo[i] =new sc_fifo<TRANS>;

   }
    

   //init module
   // reg config  ?
   global_config_c *glb_cfg = new global_config_c();

   //例化一个packet_gen_module模块，名字pkt_gen_mod
   //module packet_gen_module  u_pkt_gen_mod
   // 入参：name ：packet_gen
   //glb_cfg ：全局参数传入模块，就像module map中的cfg寄存器信号。模块除了自己的输入输出，就是外面的配置寄存器了

   packet_gen_module pkt_gen_mod("packet_gen", glb_cfg);

   pkt_gen_mod.clk(clk);


   switch_top switch_top_mod("u_switch_top", glb_cfg);
   switch_top_mod.clk(clk);


  //例化一个ingress_sch模块，名字pkt_gen_ing_sch_mod
   //module ingress_sch  u_ing_sch_mod
   // 入参：name ：recu_v_sch

//   ingress_sch ing_sch_mod("recu_v_sch", glb_cfg);
 //  ing_sch_mod.clk(clk);

   //bind -- ptr,-->bind
   for(int i =0; i < g_m_inter_num; i++)
   {
      pkt_gen_mod.output[i]->bind(*tmp_fifo[i]);
 //     (*pkt_gen_mod.output[i])(*tmp_fifo[i]);

   
      switch_top_mod.input_top_fifo[i]->bind(*tmp_fifo[i]);
//       ing_sch_mod.input_fifo[i]->bind(*tmp_fifo[i]);

   }
   //char

   sc_start(100,SC_MS);

   return 0;
}