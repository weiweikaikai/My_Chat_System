/*************************************************************************
    > File Name: data_pool.h
    > Author: WK
    > Mail:18402927708@163.com 
    > Created Time: Sat 16 Jan 2016 08:00:12 PM CST
 ************************************************************************/

#pragma once

#include<iostream>
#include<semaphore.h>
#include<string>
#include<vector>


#define POOL_SIZE 512
class data_pool
{
	public:
		data_pool(const int pool_size=POOL_SIZE);
		~data_pool();
		bool get_msg(std::string &msg);
		bool put_msg(const std::string &msg);
	private:
		const int pool_size;
		std::vector<std::string> pool;
		sem_t product_sem;
		sem_t consumer_sem;

		int start;
		int end;
};


