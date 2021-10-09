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
const int g_m_inter_num =1;
const int g_m_ipg_len =20;

typedef struct trans_type
{
   int  sport_id;
   int  dport_id;
  
   int  que_id;
   int  packet_id;
   int  packet_len;
   int  valid_len;
   int  pri_id;
   bool is_sop;
   bool is_eop;
   
     inline bool operator == (const trans_type& rhs) const
   {
     return (rhs.sport_id == sport_id && rhs.dport_id == dport_id && rhs.que_id == que_id && rhs.packet_id == packet_id && rhs.packet_len == packet_len && rhs.valid_len == valid_len
     &&rhs.pri_id == pri_id && rhs.is_sop == is_sop && rhs.is_eop == is_eop);
   }

   trans_type()
   {
      sport_id =0;
      dport_id =0;     
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

inline
ostream&
operator << ( ostream& os, const trans_type& /* a */ )
{
    os << "streaming of struct TRANS_STR not implemented";
    return os;
}

inline
void
#if defined(SC_API_VERSION_STRING)
    sc_trace( sc_trace_file* tf, const trans_type& a, const std::string& name )
#else
    sc_trace( sc_trace_file* tf, const trans_type& a, const sc_string& name )
#endif
{
  sc_trace( tf, a.sport_id, name + ".sport_id" );
  sc_trace( tf, a.dport_id, name + ".dport_id" );
  sc_trace( tf, a.que_id, name + ".que_id" );
  sc_trace( tf, a.packet_id, name + ".packet_id" );
  sc_trace( tf, a.packet_len, name + ".packet_len" );
  sc_trace( tf, a.valid_len, name + ".valid_len" );
  sc_trace( tf, a.pri_id, name + ".pri_id" );
  sc_trace( tf, a.is_sop, name + ".is_sop" );
  sc_trace( tf, a.is_eop, name + ".is_eop" );


}


// 全局配置
class global_config_c
{
   public:
      int  m_freq;           //主频,单位MHZ
      int  m_inter_num;      //接口数
      int  m_sch_sel;        //调度器选择 0:SP 1:RR  2:WRR
      int  shape_value;      //限速值 单位Mbps
      int  stat_period;      //统计间隔，以us为单位


   global_config_c()
   {
      m_freq = g_m_freq;
      m_inter_num =g_m_inter_num; 
      m_sch_sel = 1;
      shape_value = 1000;
      stat_period = 10;        
//      sport_id_que[0][0] = 1;  
   }
}; 

class table_xid_to_qid
{
      public:
      map  <int, int>    Map_xid2qid;

      table_xid_to_qid()
      {
      }


};




#define  ASSERT(A)  (assert(A))



#endif