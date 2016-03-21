/*************************************************************************
    > File Name: chat_service.cpp
    > Author: WK
    > Mail:18402927708@163.com 
    > Created Time: Fri 15 Jan 2016 02:44:41 PM CST
 ************************************************************************/

#include"service.h"


int main()
{
  udp_service service("127.0.0.1",8080); 
  service.init_service();
  
  sleep(2);
  std::string inmsg;
  service.reliable_recv_msg(inmsg);
  std::cout<<inmsg.c_str()<<"\n";
  service.reliable_recv_msg(inmsg);
  std::cout<<inmsg.c_str()<<"\n";
  service.reliable_recv_msg(inmsg);
  std::cout<<inmsg.c_str()<<"\n";
 
  return 0;
}
