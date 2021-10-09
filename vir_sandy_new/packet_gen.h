

#ifndef __PACKET_GEN__
#define __PACKET_GEN__

#include "comm_def.h"
#include "comm_func.h"
#include <map>
using namespace std;

class packet_gen_module: public sc_module
{
  public: 
//    vector<sc_out<TRANS> *> output;
    sc_out     <TRANS_STR>    output;

    sc_in_clk                  clk;
    int                        m_cycle_cnt;
    int                        m_packet_id;
    SC_HAS_PROCESS(packet_gen_module);
    global_config_c            *m_cfg;
    comm_stat_bw               *m_bw_stat;
    
  public:
  // 成员函数声明
    packet_gen_module(sc_module_name name, global_config_c *glb_cfg);
    void packet_gen_process();
    comm_shape_func            *packet_shape;
    

};
 

#endif