/*************************************************************************
    > File Name: service.c
    > Author: WK
    > Mail:18402927708@163.com 
    > Created Time: Fri 15 Jan 2016 02:38:23 PM CST
 ************************************************************************/

#include"service.h"
static void print_log(std::string _log)
{
	std::cerr<<_log<<std::endl;
}
udp_service::udp_service(std::string ip,unsigned short port):_ip(ip),_port(port)
{
  this->sock=-1;
}

udp_service::~udp_service()
{
   if(-1 != this->sock)
   {
	   close(this->sock);
   }
}

int udp_service::init_service()
{
  this->sock = socket(AF_INET,SOCK_DGRAM,0);
  if(sock < 0)
  {
	  print_log("create sock error");
	  exit(0);
  }
  print_log("create sock success\n");
  struct sockaddr_in local;
  local.sin_family = AF_INET;
  local.sin_port=htons(_port);
  local.sin_addr.s_addr=inet_addr(_ip.c_str());

  if(bind(sock,(struct sockaddr*)&local,sizeof(local)) < 0)
  {
	  print_log(strerror(errno));
	  exit(0);
  }
  print_log("bind sock success\n");
   return 0;
}

int udp_service::reliable_recv_msg(std::string &outmsg)
{
	//
	 int ret=recv_msg(outmsg);
     if(ret > 0)
	 {
		 _pool.put_msg(outmsg);
	 }
}

int udp_service::recv_msg(std::string &msg)
{
	char buf[BLOCK_SIZE];
	memset(buf,'\0',sizeof(buf));
	struct sockaddr_in outclient;
	socklen_t len= sizeof(outclient);
    bzero(&outclient,len);
	ssize_t size=0;
     size = recvfrom(this->sock,buf,sizeof(buf)-1,0,(struct sockaddr*)&outclient,&len);
         if(size <0)
		   {
              print_log("recvfrom data falied\n");
		   }
		 else if(size > 0)
		 {
                msg = buf;
				_pool.put_msg(msg);
		 }else
		 {

		 }
		 return size;
}

int udp_service::reliable_send_msg(const std::string &inmsg,struct sockaddr_in *client,socklen_t len)
{
	return send_msg(inmsg,client,len);
}
int udp_service::send_msg(const std::string &inmsg,struct sockaddr_in *client,socklen_t len)
{
     ssize_t size = sendto(this->sock,inmsg.c_str(),inmsg.size(),0,(struct sockaddr*)client,len);
	 if(size < 0)
	 {
		 print_log("sendto data falied\n");
	 }
	 else
	 {
     print_log("sendto data success\n");
	 }
	 return size;
}
int udp_service::broadcast_msg()
{
	std::string msg;
	_pool.get_msg(msg);
	std::map<std::string,struct sockaddr_in>::iterator iter= online_user.begin();
for(;iter != online_user.end();++iter)
{
	socklen_t len=sizeof(struct sockaddr_in);
	ssize_t ret=reliable_send_msg(msg,&iter->second,len);
}
return 0;
}
int udp_service::analy_client(const struct sockaddr_in &cli,const socklen_t &len,std::string &msg)
{
	std::string ip_key = inet_ntoa(cli.sin_addr);
	std::map<std::string,struct sockaddr_in>::iterator iter = online_user.find(ip_key);
	if(iter == online_user.end())
	{
online_user.insert(std::pair<std::string,struct sockaddr_in>(ip_key,cli));
	}
	return 0;
}

