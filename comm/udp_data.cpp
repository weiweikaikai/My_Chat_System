/*************************************************************************
    > File Name: udp_data.cpp
    > Author: WK
    > Mail:18402927708@163.com 
    > Created Time: Tue 19 Jan 2016 03:57:48 PM CST
 ************************************************************************/

#include"udp_data.h"

udp_data::udp_data()
{

}
udp_data:: ~udp_data()
{

}
bool udp_data:: val_to_str( std::string &out_msg)
{
   Json::Value _value;
   _value["nick_name"]=this->nick_name;
   _value["school"]=this->school;
   _value["msg"]=this->msg;
   _value["cmd"]=this->cmd;
   myjson.serialize(_value,out_msg);
   return true;

}
bool udp_data:: str_to_val( std::string &in_msg)
{
  Json::Value _value;
  myjson.deserialize(in_msg,_value);
nick_name = _value["nick_name"].asString();
this->school = _value["msg"].asString();
this->msg = _value["msg"].asString();
this->cmd = _value["cmd"].asString();

return true;
}

