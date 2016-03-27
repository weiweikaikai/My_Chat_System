/*************************************************************************
    > File Name: udp_data.h
    > Author: WK
    > Mail:18402927708@163.com 
    > Created Time: Tue 19 Jan 2016 03:49:15 PM CST
 ************************************************************************/

#pragma once
#include<iostream>
#include"json.h"

class udp_data
{
	public:
     udp_data();
     ~udp_data();

	 void set_nick_name(const std::string &_s)
	 {
		 nick_name = _s;
	 }
	 void set_school(const std::string &_s)
	 {
		 school=_s;
	 }
	 void set_msg(const std::string &_s)
	 {
		 msg = _s;
	 }
	 void set_cmd(const std::string &_s)
	 {
		 cmd = _s;
	 }

	 void get_nick_name(std::string &_s)
	 {
		 _s=nick_name;
	 }
	 void get_school( std::string &_s)
	 {
		_s=school;
	 }
	 void get_msg(std::string &_s)
	 {
        _s = msg;
	 }
	 void get_cmd( std::string &_s)
	 {
        _s = cmd;
	 }

	 bool val_to_str(std::string &out_msg);
	 bool str_to_val(std::string &in_msg);
	private:
	 my_json myjson;
     std::string nick_name;
	 std::string school;
	 std::string msg;
	 std::string cmd;

};
