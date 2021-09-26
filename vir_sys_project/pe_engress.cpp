#include "pe_engress.h"
//激励包长应从顶层获取，先配置固定256B，稍后再改

pe_engress::pe_engress(sc_module_name name, global_config_c *glb_cfg):sc_module(name)
{

    m_cycle_cnt =0;
    m_cfg = glb_cfg;
    input_sch_que.resize(g_m_inter_num);
    output_que.resize(g_m_inter_num);
 //   output_engress_fifo.resize(g_m_inter_num);


    for(int i=0; i < g_m_inter_num; i++)
    {
        input_sch_que[i] = new sc_fifo_in<TRANS>();

    }

 //   for(int i=0; i < g_m_inter_num; i++)
 //   {
 //       output_engress_fifo[i] =new sc_fifo_out<TRANS>;
//    }
 

    if (m_cfg->m_sch_sel== 0)
    {    
        out_sp_sch = new SP_SCH(g_m_inter_num);
    }
    else if (m_cfg->m_sch_sel== 1) 
    {
        out_rr_sch = new RR_SCH(g_m_inter_num);
    }
    else
    {

    }

//stat
    string debug_file = string(name) + string("_debug.log");
    m_bw_stat =new comm_stat_bw(m_cfg, debug_file,g_m_inter_num);



    SC_METHOD(main_process);
    sensitive << clk.pos();

}   

void pe_engress::main_process()
{
   m_cycle_cnt++;   
   recv_inpacket_process();
   send_outpacket_process();
   send_sch_process();

 //stat
   if((m_cycle_cnt !=0) && (m_cycle_cnt % (m_cfg->stat_period *100) ==0))
   {
       m_bw_stat->print_bw_info(m_cycle_cnt);
   }

}

//assert --- 断言要少用，一般用于不会出现错的地方，如上面因为input_fifo[i]->num_available() >0 ，所以不会出现flag = 0 的情况          
// push_back相对应的vector,ist 
// push_back 方法介绍
// vector::void push_back (const value_type& val);
// vector::void push_back (value_type&& val);
// 该函数将一个新的元素加到vector的最后面，位置为当前最后一个元素的下一个元素，新的元素的值是val的拷贝（或者是移动拷贝）
// deque 是个链表，前后都可以操作 push_back是在最后添加

void pe_engress::recv_inpacket_process()
{
  for(int i =0; i < g_m_inter_num; i++)
    {
        // num_available  -- FIFo curr num
        while(input_sch_que[i]->num_available() >0)  
        {
            TRANS input_trans;
            bool flag = input_sch_que[i]->nb_read(input_trans);     

            assert(flag);

            output_que[i].push_back(input_trans);                 //vector<deque<TRANS> >   input_que
        }
    }
}

void pe_engress::send_sch_process()
{
  //sch process
    if (m_cfg->m_sch_sel= 0)
    {
        for(int i =0; i < g_m_inter_num; i++)
        {
            if(output_que[i].empty()== false)
            {
                out_sp_sch->set_que_valid(i ,true);    // que非空的时候才参与sch
            }
            else
            {
                out_sp_sch->set_que_valid(i ,false);
            }
        }

    }
    else if (m_cfg->m_sch_sel= 1)
    {
        for(int i =0; i < g_m_inter_num; i++)
        {
            if(output_que[i].size() >0)
            {
                out_rr_sch->set_que_valid(i ,true);    // que非空的时候才参与sch
            }
            else
            {
                out_rr_sch->set_que_valid(i ,false);
            }
        }
    }
    else
    {

    }

     rst_que =-1;
//    bool rst_flag = rr_sch->get_sch_result(rst_que);

    if (m_cfg->m_sch_sel== 0)
    {
        rst_flag = out_sp_sch->get_sch_result(rst_que);
    }
    else if (m_cfg->m_sch_sel== 1)
    {
        rst_flag = out_rr_sch->get_sch_result(rst_que);
    }


}

void pe_engress::send_outpacket_process()
{
  //找出一个非空的队列，输出
    //因为是RR调度
    if(rst_flag ==true)
    {
        TRANS front_trans = output_que[rst_que].front();
        output_que[rst_que].pop_front();

//        output_engress_fifo[rst_que]->nb_write(front_trans);

        m_bw_stat->record_bw_info(rst_que, front_trans->valid_len, true);
    }
}
