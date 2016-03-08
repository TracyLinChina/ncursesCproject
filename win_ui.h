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

//��ʼ��
void init_win(void);
//�˳�
void exit_win();
//������Ϣ����
void create_msg_zone(void);
//��������ܴ���
void create_frame(void);
//�������ⴰ��
void create_title_window(char *s);
//������ʾ��Ϣ����
void show_message(char *s);
//�˸�ɾ������
void goback_n(WINDOW *win_tmp, int n);
//�����������ڻ���
void login_register(void);
//��������ѡ����
int boot_screen(void);
//���뺯��
int Get_input(WINDOW *tmp,char s[],int MAX_LEN,int flag);
//��½�߿�
void login_in_win(char *s) ;
//ע��߿�
void new_user_win(char *s);
//�û���½�жϺ���
int user_login(void);
//��½��������
int core_func(void);
//����С����
void creat_show_title(void);
//���BUG
int Add_Bug(void);
//����ָ��bug
int find_bug(void);
//ѡ��bug��ʾ��ʽ
int Selection_Show_Bug(void);
//�û�ע��
int User_register(void);
void File_bugList(bug_msg_t *p);
void overload_bugList(void);
void File_userList(user_msg_t *p);
int overload_userList(void);
void Color_set(void);

#endif





