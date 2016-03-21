/*************************************************************************
    > File Name: chat_client.cpp
    > Author: WK
    > Mail:18402927708@163.com 
    > Created Time: Fri 15 Jan 2016 02:45:42 PM CST
 ************************************************************************/

#include"client.h"


int main()
{

udp_client client("127.0.0.1",8080);
client.init_client();

std::string msg = "hello service\n";
client.reliable_send_msg(msg);
client.reliable_send_msg(msg);
client.reliable_send_msg(msg);
client.reliable_send_msg(msg);

sleep(5);
std::string inmsg;

client.reliable_recv_msg(inmsg);
std::cout<<inmsg.c_str()<<"\n";
client.reliable_recv_msg(inmsg);
std::cout<<inmsg.c_str()<<"\n";
client.reliable_recv_msg(inmsg);
std::cout<<inmsg.c_str()<<"\n";

	return 0;
}
