


#include "ingress_sch.h"
//激励包长应从顶层获取，先配置固定256B，稍后再改
ingress_sch::ingress_sch(string name, global_config_c *glb_cfg):sc_module(name)
{

    m_cycle_cnt =0;
    m_cfg = glb_cfg;
    input_fifo.resize(g_m_inter_num);
    input_que.resize(g_m_inter_num);
    for(int i=0; i < g_m_inter_num; i++)
    {
        input_fifo[i] = new sc_fifo_in<TRANS>();
    }
    //sch 
    rr_sch = new RR_SCH(g_m_inter_num);

    SC_METHOD(main_process);
    sensitive << clk.pos();

}
void ingress_sch::main_process()
{
   m_cycle_cnt++;   
   recv_packet_process();
   sch_process();
}

//read(T &)和read()是阻塞型读方法，如果读的时候FIFO为空，则它们等到FIFO有数据写入时才返回数据，它们的读操作永远是成功的。
//nb_read(T&)是非阻塞型读操作，它总是立刻返回。
//如果FIFO非空，则读FIFO成功，否则读失败。bool，返回的是成功 or 失败

//num_available()返回当前还有多少数据单元可以读出。FIFO当前深度
//data_written_event()用于返回数据写事件。

void ingress_sch::recv_packet_process()
{
    for(int i =0; i < g_m_inter_num; i++)
    {
        // num_available  -- FIFo curr num
        while(input_fifo[i]->num_available() >0)  
        {
            TRANS input_trans;
            bool flag = input_fifo[i]->nb_readd(input_trans);

 //assert --- 断言要少用，一般用于不会出现错的地方，如上面因为input_fifo[i]->num_available() >0 ，所以不会出现flag = 0 的情况           
            assert(flag);


// push_back相对应的vector,ist 
// push_back 方法介绍
// vector::void push_back (const value_type& val);
// vector::void push_back (value_type&& val);
// 该函数将一个新的元素加到vector的最后面，位置为当前最后一个元素的下一个元素，新的元素的值是val的拷贝（或者是移动拷贝）
// deque 是个链表，前后都可以操作 push_back是在最后添加

            input_que[i].push_back(input_trans);                 //vector<deque<TRANS> >   input_que


        }
    }
}


 //   push对应的stack,queue
 //   push 函数介绍
 //   stack::push();//在栈顶增加元素
 //   queue::push();//将x 接到队列的末端。





void ingress_sch::sch_process()
{
    //sch process
    for(int i =0; i < g_m_inter_num; i++)
    {
        if(input_que[i].size() >0)
        {
            rr_sch->set_que_valid(i ,true);    // que非空的时候才参与sch
        }
        else
        {
            rr_sch->set_que_valid(i ,false);
        }
    }
    
    //调度
    int rst_que =-1;
    bool rst_flag = rr_sch->get_sch_result(rst_que);
    if(rst_flag ==true)
    {
        TRANS front_trans = input_que[rst_que].front();
        input_que[rst_que].pop_front();
    }
    
}
