#include <systemc.h>
#include "ingress_sch.h"


void ingress_sch::main_process()
{

  cout << "ingress_sch : start" << endl;


//   m_cycle_cnt++;   
   recv_packet_process();
//   sch_process();
//
// //stat
//   if((m_cycle_cnt !=0) && (m_cycle_cnt % (10*100) ==0))
//   {
//       m_bw_stat->print_bw_info(m_cycle_cnt);
//   }



  
}


  void ingress_sch::recv_packet_process()
{
        while(input_fifo->event())  
        {
            TRANS input_trans;
 
            input_que.push_back(input_trans);                 //vector<deque<TRANS> >   input_que

        }
    
}
/*
void ingress_sch::sch_process()
{
     

            if(input_que.size() >0)
            {
                rr_sch->set_que_valid(0 ,true);    // que非空的时候才参与sch
            }
            else
            {
                rr_sch->set_que_valid(0 ,false);
            }

    
    //调度
    int rst_que = 0;
    bool rst_flag = rr_sch->get_sch_result(rst_que);


    //找出一个非空的队列，输出
    //因为是RR调度
    if(rst_flag ==true)
    {
        TRANS front_trans = input_que.front();
        input_que.pop_front();
 //       output_sch_que[rst_que]->nb_write(front_trans);
        m_bw_stat->record_bw_info(0, front_trans->valid_len, true);
    }
    
}
*/
