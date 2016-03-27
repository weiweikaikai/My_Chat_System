/*************************************************************************
    > File Name: json.h
    > Author: WK
    > Mail:18402927708@163.com 
    > Created Time: Mon 18 Jan 2016 03:47:26 PM CST
 ************************************************************************/


#include<string>
#include<iostream>
#include"json/json.h"

class my_json
{
public:
     my_json();
     ~my_json();
  int serialize(Json::Value &in_val,std::string &str_out);
  int deserialize(std::string &in_str,Json::Value &out_val);
};




