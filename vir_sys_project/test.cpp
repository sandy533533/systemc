

#include "stdio.h"
#include <iostream>
#include "packet_gen.h"
//#include "switch_top.h"
#include "ingress_sch.h"
#include "pe_engress.h"

#include "systemc.h"
#include <memory>
#include "comm_def.h"
#include "comm_func.h"
using namespace std;


int sc_main(int argc, char *argv[])


{

//systemC中并不允许直接调用通道channel，不同模块之间进行通信必须通过端口port。

//在同一模块里，各个进程之间需要通信，他们可以通过共享变量、握手信号、模块内通道等方式通信。
//如果他们之间的通信是通过模块内通道。

//sc_fifo<T>

//sc_fifo是SystemC库中已经实现好的FIFO通道，其中T为FIFO中存储的数据类型。
//write(&T)代表写FIFO的方法，read()是读FIFO的方法。
//Num_free()查询FIFO还有多少空单元，num_available()查询FIFO还有多少个数据可以读。对于fifo的size，默认深度为16.

   sc_clock    clk                    ("clk",100,SC_NS);  //100ns 对应10MHZ 

   vector      < sc_fifo<TRANS> * >   tmp_fifo0;  
   vector      < sc_fifo<TRANS> * >   tmp_fifo1;  

// new 分配动态内存
   tmp_fifo0.resize(g_m_inter_num);
   tmp_fifo1.resize(g_m_inter_num);

   for(int i=0; i < g_m_inter_num; i++)
   {
 //     tmp_fifo[i] =new sc_fifo<TRANS>();
     tmp_fifo0[i] =new sc_fifo<TRANS>;
     tmp_fifo1[i] =new sc_fifo<TRANS>;
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

   ingress_sch ing_sch_mod("ingress_sch", glb_cfg);
   ing_sch_mod.clk(clk);

   pe_engress pe_eng_mod("pe_engress", glb_cfg);
   pe_eng_mod.clk(clk);

 //  switch_top switch_top_mod("u_switch_top", glb_cfg);
 //  switch_top_mod.clk(clk);

   //bind -- ptr,-->bind
   for(int i =0; i < g_m_inter_num; i++)
   {
      pkt_gen_mod.output[i]->bind(*tmp_fifo0[i]);
      ing_sch_mod.input_fifo[i]->bind(*tmp_fifo0[i]);

      ing_sch_mod.output_sch_que[i]->bind(*tmp_fifo1[i]);
      pe_eng_mod.input_sch_que[i]->bind(*tmp_fifo1[i]);

   }
  // 模块嵌套的时候，是不是只有最底层是指针？嵌套的时候是结构体嵌套？

//符号.和->的作用和区别
//A.B则A为对象或者结构体；
//点号（.）：左边必须为实体。

//A->B则A为指针，->是成员提取，A->B是提取A中的成员B，A只能是指向类、结构、联合的指针；
//箭头（->）：左边必须为指针；

// 定义时有*，说明是指针，用->; 定义时无*，说明是结构体或class，用点号（.）  ？？？


 
   //char

   sc_start(100,SC_MS);

   return 0;
}