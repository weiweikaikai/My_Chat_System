/*************************************************************************
    > File Name: client.h
    > Author: WK
    > Mail:18402927708@163.com 
    > Created Time: Fri 15 Jan 2016 02:45:23 PM CST
 ************************************************************************/
#pragma once
#include<string>
#include<iostream>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <string.h>
#include <string>
#include <map>
#include <arpa/inet.h>
#include <vector>
#include <strstream>



class udp_client
{
   public:
       udp_client(std::string remote_ip="127.0.0.1",unsigned short remote_port=8080);
       ~udp_client();
	   int init_client();
	   int reliable_recv_msg(std::string &msg);
	   int reliable_send_msg(std::string &msg);
   private:
	   int recv_msg(std::string &msg);
	   int send_msg(std::string &msg);
	   int sock;
	   std::string _remote_ip;
	   unsigned short _remote_port;
};
