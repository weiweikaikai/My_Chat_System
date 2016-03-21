/*************************************************************************
    > File Name: data_pool.cpp
    > Author: WK
    > Mail:18402927708@163.com 
    > Created Time: Sat 16 Jan 2016 08:00:01 PM CST
 ************************************************************************/

#include"data_pool.h"

data_pool::data_pool(int size):pool_size(size),pool(size)
{
	start =end=0;
	sem_init(&product_sem,0,size);
	sem_init(&consumer_sem,0,0);
}
bool data_pool::get_msg(std::string &msg)
{
	sem_wait(&consumer_sem);
	msg = pool[end];
	sem_post(&product_sem);
	end = (++end)%pool_size;
	return true;
}

bool data_pool::put_msg(const std::string &msg)
{
	sem_wait(&product_sem);
	pool[start]=msg;
	sem_post(&consumer_sem);
	start =(++start)%pool_size;
	return true;
}
data_pool::~data_pool()
{
	sem_destroy(&product_sem);
	sem_destroy(&consumer_sem);
}
