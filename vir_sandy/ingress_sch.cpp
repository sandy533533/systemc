#include "ingress_sch.h"

using namespace std;

void ingress_sch::main_process()
 {
 
     m_cycle_cnt++;   
     recv_packet_process();
//   sch_process();
 //stat
   if((m_cycle_cnt !=0) && (m_cycle_cnt % (10*100) ==0))
   {
       m_bw_stat->print_bw_info(m_cycle_cnt);

   }
    
 }

   void ingress_sch::recv_packet_process()
{
            TRANS input_trans;
            input_trans = input_fifo->read();
            input_que->push_back(input_trans);                 //vector<deque<TRANS> >   input_que
//            cout << "input_fifo : start" << endl;

}