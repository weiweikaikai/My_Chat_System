/*************************************************************************
    > File Name: chat_client.cpp
    > Author: WK
    > Mail:18402927708@163.com 
    > Created Time: Fri 15 Jan 2016 02:45:42 PM CST
 ************************************************************************/
#include<signal.h>
#include"client.h"
#include<pthread.h>
#include"udp_data.h"
#include"window.h"


chat_window win;
vector<std::string> arr;
udp_client * sig_client = NULL;

void *client_header(void *arg)
{
	
	win.draw_header();
	std::string line = "Welcome To Wechat of Linux!";
	int step = 6;
	
	while(1)
	{
        win.clear_win_line(win.get_header(),3,1);
		win.put_str_to_win(win.get_header(),2,step++,line);
		chat_window::win_refresh(win.get_header());
		win.clear_win_line(win.get_header(),3,1);
		step %= (COLS-6);
			if(step == 0)
			{
				step = 6;
			}
		usleep(100000);
		win.clear_win_line(win.get_header(),3,1);
		chat_window::win_refresh(win.get_header());
	}
}

void * client_output(void *arg)
{
	udp_client *client = (udp_client*)arg;
	udp_data data;
  std::string _msg;
	std::string nick_name;
	std::string school;
	std::string msg;
	std::string cmd;


	int total =1;
	while(1)
	{
		win.draw_output();
		chat_window::win_refresh(win.get_output());
		client->reliable_recv_msg(_msg);
		data.str_to_val(_msg);
		data.get_nick_name(nick_name);
		data.get_school(school);
		data.get_msg(msg);
		data.get_cmd(cmd);
		
		bool flag = true;

		if(cmd == "MESSAGE")
		{
			std::string show_msg = nick_name;
			show_msg += "-";
			show_msg+=school;
			vector<string>::iterator _iter = arr.begin();
			for(;_iter != arr.end();++_iter)
			{
				if(*_iter == show_msg)
				{
					flag = false;
				}
			}
			if(flag)
				arr.push_back(show_msg);
			show_msg += ":";
			show_msg += msg;

			win.put_str_to_win(win.get_output(),total++,2,show_msg);
			chat_window::win_refresh(win.get_output());
			total %= (LINES *3 /5 -1);
			if(total ==  0)
			{
				total = 1;
				win.clear_win_line(win.get_input(),1,(LINES*3/5 - 1));
				chat_window::win_refresh(win.get_output());
			}

		}
		usleep(100000);
	}
}

void *client_input(void *arg)
{
     udp_client * client =(udp_client*)arg;
	 std::string msg = "Please Enter:";
	 std::string  _client_msg;
	 std::string name = "l";
	 std::string school = "sgd";
	 std::string cmd = "MESSAGE";
	 
	 std::string send_str;
	 udp_data _data;

	 while(1)
	 {
		 win.draw_input();
		 chat_window::win_refresh(win.get_input());
         win.put_str_to_win(win.get_input(),1,2,msg);
         win.get_str_to_win(win.get_input(),_client_msg);

		 _data.set_nick_name(name);
		 _data.set_school(school);
		 _data.set_cmd(cmd);
		 _data.set_msg(_client_msg);
		 
		 _data.val_to_str(send_str);
		 client->reliable_send_msg(send_str);
		 
		 usleep(10000);
		 win.clear_win_line(win.get_input(),1,1);
	 }
}
void * client_list(void *arg)
{
     win.draw_list();
	 while(1)
	 {

		 int i=0;
		 int len = arr.size();
		 for(;i<len;++i)
		 {
			 win.put_str_to_win(win.get_list(),i+1,2,arr[i]);
		 }
		 chat_window::win_refresh(win.get_list());
		 usleep(10000);
	 }
}

void handler(int sig)
{

	udp_data _data;
	string name = "weikai";
	string school = "xgd";
	string cmd = "CMD_QUIT";
	string _client_msg = "NODE";

	switch(sig)
	{
		case SIGINT:
			{
				string send_str;
				_data.set_nick_name(name);
				_data.set_school(school);
				_data.set_cmd(cmd);
				_data.set_msg(_client_msg);
				_data.val_to_str(send_str);
				sig_client->reliable_send_msg(send_str);
				exit(1);
			}
			break;
		default:
			break;
	}
}
void usage(char*arg)
{
	std::cout<<"Usage: "<<arg<<"[ IP ]  [PORT]\n";
	exit(-1);
}

int main(int argc,char *argv[])
{
	//if(argc != 3)
	//{
//		usage(argv[0]);
//	}

	//std::string ip = argv[1];
	std::string ip = "127.0.0.1";
	//unsigned short port = atoi(argv[2]);
	unsigned short port = 8002;
udp_client client(ip,port);
client.init_client();

     win.init();
	 signal(SIGINT,handler);
	 pthread_t header ,output,input,list;
	
	 sleep(1);
	 pthread_create(&header,NULL,client_header,NULL);
	 pthread_create(&output,NULL,client_output,(void*)&client);
	 pthread_create(&input,NULL,client_input,(void*)&client);
	 pthread_create(&list,NULL,client_list,NULL);
	pthread_join(header,NULL);
	pthread_join(output,NULL);
	pthread_join(input,NULL);
	pthread_join(list,NULL);
	
	std::string _nick_name;
	std::string _school;
	std::string _cmd = "TALK_MASSAGE";

	udp_data _client_data;

	std::cout<<"please Enter nickname:> ";
	fflush(stdout);
	std::cin>>_nick_name;

	std::cout<<"please Enter school:> ";
	fflush(stdout);
	std::cin>>_school;

	std::string msg;
	std::string send_str;
	std::string recv_str;
	while(1)
	{
		_client_data.set_nick_name(_nick_name);
		_client_data.set_school(_school);
		_client_data.set_cmd(_cmd);

		std::cout<<"please Enter:> ";
		fflush(stdout);
		std::cin>>msg;
		_client_data.set_msg(msg);
		_client_data.val_to_str(send_str);
		cout<<"send:> "<<send_str<<endl;
		client.reliable_send_msg(send_str);		

		client.reliable_recv_msg(recv_str);
		_client_data.str_to_val(recv_str);

		std::string tmp;
		_client_data.get_nick_name(tmp);
		cout<<tmp<<",";
		_client_data.get_school(tmp);
		cout<<tmp<<",";
		_client_data.get_cmd(tmp);
		cout<<tmp<<",";
		_client_data.get_msg(tmp);
		cout<<tmp<<endl;
	}
	 
	return 0;
}
