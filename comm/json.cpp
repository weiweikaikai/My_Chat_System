/*************************************************************************
    > File Name: json.cpp
    > Author: WK
    > Mail:18402927708@163.com 
    > Created Time: Mon 18 Jan 2016 03:47:57 PM CST
 ************************************************************************/

#include"json.h"

my_json::my_json()
{

}
my_json::~my_json()
{

}
int my_json::serialize(Json::Value &in_val,std::string &str_out)
{
#ifdef _JSON_STYLE
	   Json::StyledWriter _write;
#else
	   Json::FastWriter  _write;
#endif

	   str_out = _write.write(in_val);
	   return 0;
}
int my_json::deserialize(std::string &in_str,Json::Value &out_val)
{
	Json::Reader _reader;
	if(_reader.parse(in_str,out_val,false))
	{
       return 0;
	}
	else
	{
		return 1;
	}
}



//int main()
//{
//	std::string str_out;
//	Json::Value _val;
//	_val["kai"]="wei";
//
//	my_json::serialize(_val,str_out);
//   std::cout<<str_out<<std::endl;
//
//	return 0;
//}





