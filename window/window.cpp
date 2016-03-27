/*************************************************************************
    > File Name: window.cpp
    > Author: WK
    > Mail:18402927708@163.com 
    > Created Time: Fri 15 Jan 2016 02:52:31 PM CST
 ************************************************************************/

#include"window.h"
#include"udp_data.h"

chat_window::chat_window()
{
  header = NULL;
  output = NULL;
  list = NULL;
  input = NULL;
}
chat_window::~chat_window()
{
   delwin(this->header);
   delwin(this->output);
   delwin(this->list);
   delwin(this->input);
   endwin();
   pthread_mutex_destroy(&lock);
}
void chat_window::init()
{
	pthread_mutex_init(&lock,NULL);
	initscr();
}

void  chat_window::draw_header()
{
	int hei = LINES/5;
	int wit = COLS;
	int y=0;
	int x=0;
	this->header = create_win(hei,wit,y,x);

}
void chat_window::draw_output()
{
      int hei = LINES*3/5;
	  int wit = COLS*3/4;
	  int y = LINES/5;
	  int x = 0;
	  this->list = create_win(hei,wit,y,x);
}
void chat_window::draw_list()
{
  int hei=LINES*3/5;
  int wit = COLS/4;

  int y = LINES/5;
  int x = COLS*3/4;
  this->list = create_win(hei,wit,y,x);

}
void chat_window::draw_input()
{
  int hei = LINES/5;
  int wit = COLS;
  int y = 4*LINES/5;
  int x=0;
  this->input = create_win(hei,wit,y,x);
}
void chat_window:: win_refresh(WINDOW* _win)
{
   box(_win,0,0);
   wrefresh(_win);
}
 void chat_window::put_str_to_win(WINDOW* _win,int _y,int _x,std::string &_str)
{
       mvwaddstr(_win,_y,_x,_str.c_str());
}
 void chat_window::get_str_to_win(WINDOW* _win,std::string &_msg)
{
   char buf[BUF_SIZE];
   memset(buf,'\0',sizeof(buf));
   wgetnstr(_win,buf,sizeof(buf));
   _msg = buf;
}
void chat_window::clear_win_line(WINDOW* _win,int begin,int num)
{
   while(num-- > 0)
   {
        wmove(_win,begin++,0);
		wclrtoeol(_win);
   }
}
WINDOW * chat_window::create_win(int hei,int wth,int y,int x)
{

 WINDOW*win = newwin(hei,wth,y,x);  
  return win;
}
