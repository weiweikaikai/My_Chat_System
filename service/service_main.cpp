/*************************************************************************
    > File Name: chat_service.cpp
    > Author: WK
    > Mail:18402927708@163.com 
    > Created Time: Fri 15 Jan 2016 02:44:41 PM CST
 ************************************************************************/

#include"service.h"



void*collect_data(void *arg)
{
	udp_service *s=(udp_service*)arg;
    while(1)
	{
		s->reliable_recv_msg();
	}
}
void*distribute_data(void *arg)
{
	udp_service *s=(udp_service*)arg;
    while(1)
	{
		s->broadcast_msg();
	}
}

void usage(std::string proc)
{
	std::cout<<"Usage: "<<proc<<" [IP] "<<" [PORT] \n";
}
int main(int argc,char*argv[])
{
	if(argc != 3)
	{
       usage(argv[0]);
	   exit(-1);
	}
     std::string ip = argv[1];
	unsigned short port = atoi(argv[2]);
     udp_service service(ip,port); 
     service.init_service();
   
      pthread_t id[2];
	  pthread_create(&id[1],NULL,collect_data,(void*)&service);
	  pthread_create(&id[2],NULL,distribute_data,(void*)&service);
	  pthread_join(id[1],NULL);
	  pthread_join(id[2],NULL);

  //sleep(2);
  //std::string inmsg;
  //service.reliable_recv_msg(inmsg);
  //std::cout<<inmsg.c_str()<<"\n";
  //service.reliable_recv_msg(inmsg);
  //std::cout<<inmsg.c_str()<<"\n";
  //service.reliable_recv_msg(inmsg);
  //std::cout<<inmsg.c_str()<<"\n";
    
  return 0;
}
