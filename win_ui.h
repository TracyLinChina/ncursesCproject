#ifndef __WIN_UI_H__
#define __WIN_UI_H__

struct date{
    int year;
    int month;
    int day;
    int hour;
    int min;
    int sec;
}date_t;

typedef struct bug_msg{
    char describe[255];
    char type[20];
    char code[5];
    struct date date_t;
    struct bug_msg *next;
    struct bug_msg *prev;
}bug_msg_t;

bug_msg_t head;

typedef struct user{
     char user_name[12];
     char user_password[7];
     struct user *next;
     struct user *prev;
}user_msg_t;

user_msg_t head_user;

//初始化
void init_win(void);
//退出
void exit_win();
//创建消息窗口
void create_msg_zone(void);
//创建主框架窗口
void create_frame(void);
//创建标题窗口
void create_title_window(char *s);
//创建提示消息窗口
void show_message(char *s);
//退格删除函数
void goback_n(WINDOW *win_tmp, int n);
//创建开机窗口画面
void login_register(void);
//创建开机选择画面
int boot_screen(void);
//输入函数
int Get_input(WINDOW *tmp,char s[],int MAX_LEN,int flag);
//登陆边框
void login_in_win(char *s) ;
//注册边框
void new_user_win(char *s);
//用户登陆判断函数
int user_login(void);
//登陆后主界面
int core_func(void);
//创建小弹窗
void creat_show_title(void);
//添加BUG
int Add_Bug(void);
//查找指定bug
int find_bug(void);
//选择bug显示方式
int Selection_Show_Bug(void);
//用户注册
int User_register(void);
void File_bugList(bug_msg_t *p);
void overload_bugList(void);
void File_userList(user_msg_t *p);
int overload_userList(void);
void Color_set(void);

#endif





