/*************************************************************************
    > File Name: client.cpp
    > Author: WK
    > Mail:18402927708@163.com 
    > Created Time: Fri 15 Jan 2016 02:45:29 PM CST
 ************************************************************************/

#include"client.h"

#define BLOCK_SIZE 1024
udp_client::udp_client(std::string remote_ip,unsigned short remote_port):_remote_ip(remote_ip),_remote_port(remote_port)
{
	this->sock=-1;
}
udp_client::~udp_client()
{
      if(sock != -1)
	  {
		  close(this->sock);
	  }
}

int udp_client::init_client()
{
  sock = socket(AF_INET,SOCK_DGRAM,0);
  if(-1 == this->sock)
  {
	  std::cout<<"create sock failed\n";
	  return 1;
  }
  return 0;
}
int udp_client::reliable_recv_msg(std::string &msg)
{
	return recv_msg(msg);
}
int udp_client::recv_msg(std::string &msg)
{
	 char buf[BLOCK_SIZE];
	 memset(buf,'\0',sizeof(buf));
      struct sockaddr_in dst;
	  socklen_t len =sizeof(struct sockaddr_in);
	  bzero(&dst,len);
	  ssize_t ret = recvfrom(this->sock,buf,sizeof(buf),0,(struct sockaddr*)&dst,&len);
	  if( -1 == ret)
	  {
		  std::cout<<"get msg falied\n";
	  }
	  else
	  {
		  msg =buf;
	  }
	  return ret;

}
int udp_client::reliable_send_msg(std::string &msg)
{
    return send_msg(msg);
}
int udp_client::send_msg(std::string &msg)
{
   struct sockaddr_in dst;
   socklen_t len = sizeof(struct sockaddr_in);
   bzero(&dst,len);
   dst.sin_family= AF_INET;
   dst.sin_port=htons(this->_remote_port);
   dst.sin_addr.s_addr = inet_addr(this->_remote_ip.c_str());
   ssize_t size = sendto(this->sock,msg.c_str(),msg.size(),0,(struct sockaddr*)&dst,len);
   if(-1 == size)
   {
	   std::cout<<"sendto data error\n";
   }
   return size;
}
