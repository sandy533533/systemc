#ifndef __COMM_FUNC_H__
#define __COMM_FUNC_H__
#include<vector>
#include "systemc.h"
#include "comm_def.h"

using namespace std;

class WRR_SCH
{


};
class RR_SCH
{
    public:
        int que_num;
        int sch_pos;
        vector<int> que_status;
    public:
        RR_SCH(int tmp_que_num);
        void set_que_valid(int que_id, bool valid_flag);
        bool  get_sch_result(int &rst_que);

};


                                                     
class SP_SCH
{
    public:
        int que_num;
        int sch_pos;
        vector<int> que_status;
    public:
        SP_SCH(int tmp_que_num);
        void set_que_valid(int que_id, bool valid_flag);
        void set_que_hpri (int que_id);
        bool  get_sch_result(int &rst_que);

};



class comm_shape_func
{
    //令牌填充10CC填充13个Byte，这算速率13*8*100M=1.04G,如果当前桶内令牌数>=包长,则允许报文发出，同时扣除相应令牌数，
    //如果令牌小于包长,则不允许发出，令牌周期性的填充，最大填充桶深为CBS
    public:
       int cbs_value;
       int token_value;
       int fill_period;
    
    public:
       comm_shape_func(int shape_value, int tmp_cbs_value, int add_value, int fill_period);
       void add_token(int add_value);     //单位Byte
       void sub_token(int sub_value);     //单位Byte
       bool shape_status(int packet_len); //单位Byte


};

template <class T>
class comm_delay_fifo: public sc_module
{
    public: 
        comm_delay_fifo(string name, sc_time t1);
        SC_HAS_PROCESS(comm_delay_fifo);
        void notify(T &);
        bool get_ready_info(T &);
        void main_process();

    private:
        sc_in_clk clk;
        int m_cycle_cnt;


};

template <class T>
comm_delay_fifo<T>::comm_delay_fifo(string name, sc_time t1):sc_module(name)
{
    m_cycle_cnt =0;
    SC_METHOD(main_process);
    sensitive << clk.pos();
}

template <class T>
void comm_delay_fifo<T>::notify(T &)
{
    
}

template <class T>
bool comm_delay_fifo<T>::get_ready_info(T &)
{
    return true;
}

template <class T>
void comm_delay_fifo<T>::main_process()
{
    m_cycle_cnt ++;
}

class comm_stat_bw
{
    public:
        int m_que_num;
        vector <int> m_que_pktlen_stat;
        vector <int> m_que_pktnum_stat;
        int m_total_pktlen_stat;
        int m_total_pktnum_stat;
        int m_stat_period;
        global_config_c *m_glb_cfg;
        string   m_file_name;
        FILE     *m_fp; 
    public:
        comm_stat_bw(global_config_c *glb_cfg, string file_name, int que_num);
        void record_bw_info(int que_id, int valid_len, int is_eop);
        void print_bw_info(int m_cycle);
};



#endif