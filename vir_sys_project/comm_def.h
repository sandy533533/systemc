#ifndef __COMM_DEF_H__
#define __COMM_DEF_H__

#include "stdio.h"
#include <memory>
#include "systemc.h"
#include "tlm"
#include "tlm_utils/multi_passthrough_initiator_socket.h"
#include  "tlm_utils/multi_passthrough_target_socket.h"
#include "string.h"
#include<vector>
#include <assert.h>

using namespace std;
using namespace tlm_utils;
using namespace tlm;


const int g_m_freq  = 100; //100M HZ
const int g_m_inter_num =4;

typedef struct trans_type
{
   int  port_id;
   int  que_id;
   int  packet_id;
   int  packet_len;
   int  valid_len;
   int  pri_id;
   bool is_sop;
   bool is_eop;
   

   trans_type()
   {
      port_id =0;
      que_id  =0;
      packet_id =0;
      packet_len =0;
      valid_len  =0;
      pri_id     =0;
      is_sop     =false;
      is_eop     =false;
   }
} TRANS_STR; 

typedef  std::shared_ptr<TRANS_STR>  TRANS;


// 全局配置
class global_config_c
{
   public:
      int  m_freq;           //主频,单位MHZ
      int  m_inter_num;      //接口数
      int  m_sch_sel;        //调度器选择 0:SP 1:RR  2:WRR
      int  shape_value;      //限速值 单位Mbps
   public:
   global_config_c()
   {
      m_freq = g_m_freq;
      m_inter_num =g_m_inter_num; 
      m_sch_sel = 1;
      shape_value = 1000;
   }
}; 

#define  ASSERT(A)  (assert(A))



#endif