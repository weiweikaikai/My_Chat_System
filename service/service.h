/*************************************************************************
    > File Name: service.h
    > Author: WK
    > Mail:18402927708@163.com 
    > Created Time: Fri 15 Jan 2016 02:38:36 PM CST
 ************************************************************************/
#pragma once
#include<iostream>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<signal.h>
#include<sys/syscall.h>
#include<pthread.h>
#include<sys/socket.h>
#include<string>
#include<map>
#include<arpa/inet.h>
#include<netinet/in.h>
#include"comm.h"
#include"data_pool.h"

class udp_service
{
	public:
		udp_service(std::string ip="127.0.0.1",unsigned short port=8080);
		int init_service();
		int reliable_recv_msg();
        int reliable_send_msg(const std::string &inmsg, struct sockaddr_in *client,socklen_t len);
		int broadcast_msg();
        bool analy_client(const struct sockaddr_in &cli);
		~udp_service();
	private:
		int send_msg(const std::string &inmsg, struct sockaddr_in *client,socklen_t len);
		int recv_msg(std::string &outmsg);

	int sock;
	std::string _ip;
	unsigned short _port;
    data_pool _pool;
    std::map<std::string,struct sockaddr_in> online_user;
};
