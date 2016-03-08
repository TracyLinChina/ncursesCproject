#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include <unistd.h>
#include "win_ui.h"
#define ENTER 10
#define ESC 13
#define KEY_SPACE 27

static WINDOW *win=NULL;               /* Ê°ÜÊû∂Á™óÂè£ */
static WINDOW *title_win=NULL;         /* Ê†áÈ¢òÁ™óÂè£ */
static WINDOW *main_win=NULL;          /* ‰∏ªÁ™óÂè£   */
static WINDOW *message_win=NULL;       /* Ê∂àÊÅØÁ™óÂè£ */
static WINDOW *register_win=NULL;
static WINDOW *login_win=NULL;
static WINDOW *boot_win=NULL;
static WINDOW *boot_title=NULL;
static WINDOW *boot_choice[3]={NULL,NULL,NULL};
static WINDOW *operate_main_win = NULL;
static WINDOW *operate_win[3] = {NULL,NULL,NULL}; 
static WINDOW *Add_win = NULL;
static WINDOW *prompting_frame[2] ={NULL,NULL};
static WINDOW *show_win = NULL;
static WINDOW *show_title = NULL;
static WINDOW *prompting_win = NULL;
static WINDOW *show_find_win = NULL;
static WINDOW *show_all_win[10];

extern bug_msg_t head;
extern user_msg_t head_user;

void init_win(void)
{
    initscr();
    cbreak();
    noecho(); 
}

void exit_win()
{
   endwin();
}


void create_msg_zone(void)
{
    message_win=newwin(4, 78, 19, 1); 
    keypad(message_win, true);
    wrefresh(win);
}


void create_frame(void)
{
    win=newwin(24, 80, 0, 0);       

    box(win,0,0);  
    mvwprintw(win, 0, 25, "Mini BUG Management Systems");
    mvwhline(win, 18, 1, 0, 78);
    mvwprintw(win, 18, 36, "Message");
    
    wrefresh(win);
}


void create_title_window(char *s)
{
    title_win=newwin(3, 20, 1, 28);  
    wclear(title_win);
    mvwhline(title_win, 0, 1, 0, 18);
    mvwhline(title_win, 2, 1, 0, 18);
    mvwprintw(title_win,1,5,s);
    wrefresh(title_win);
}


void show_message(char *s)
{
    wclear(message_win);
    mvwprintw(message_win,0,0,s);
    wrefresh(message_win);
}


void Color_set(void)
{
    if(has_colors == FALSE) {
        endwin();
        return;
    }
    start_color();
}
void goback_n(WINDOW *win_tmp, int n)
{
    int row = 0,col = 0;
    while(n--) {
        getyx(win_tmp, row, col);
        mvwprintw(win_tmp, row, col-1," ");
        wmove(win_tmp, row, col-1);
    }
    wrefresh(win_tmp);
}


void login_register(void)
{
    int y = 0,x = 0,i = 0;
    char l[] = "LOGIN IN";
    char *r = "REGISTER";
    char *e = "EXIT";
    boot_choice[0] = newwin(1,10,14,(80 - strlen(l))/2);
    boot_choice[1] = newwin(1,8,16,(80 - strlen(r))/2);
    boot_choice[2]= newwin(1,5,18,(80 - strlen(e))/2);
    Color_set();
    init_pair(3,COLOR_RED,COLOR_BLACK);
    init_pair(5,COLOR_RED,COLOR_WHITE);
    wmove(boot_choice[0],0,1);
    for(i = 0;i < strlen(l);i++) {
        getyx(boot_choice[0],y,x);
        mvwaddch(boot_choice[0],y,x,l[i]|COLOR_PAIR(5));
        wrefresh(boot_choice[0]);
    }
    wmove(boot_choice[1],0,1);
    for(i = 0;i < strlen(r);i++) {
        getyx(boot_choice[1],y,x);
        mvwaddch(boot_choice[1],y,x,r[i]|COLOR_PAIR(3));
        wrefresh(boot_choice[1]);
    }
    wmove(boot_choice[2],0,1);
    for(i = 0;i < strlen(e);i++) {
        getyx(boot_choice[2],y,x);
        mvwaddch(boot_choice[2],y,x,e[i]|COLOR_PAIR(3));
        wrefresh(boot_choice[2]);
    }
    
    return;
}


int boot_screen(void)
{ 
    int y = 0,x = 0,i = 0,j = 0,flag = 0;
    char ch;
    char p_1[] = "FBI WARING";
    char *p[] = {"Federal law provides civil and criminal penalties  for", "the unauthorized reproduction,distribution,or exhibition of","copyrighted motion prictures (Title 17,United States Code,","Sections 501 and 508). Thefederal bureau of Investigation","investigate allegations of criminal copyright infringement.","(Title 17, United States Code, Section 506)"};
    boot_win = newwin(24,80,0,0);
    boot_title = newwin(3,13,3,(80 - strlen(p_1))/2);
    wrefresh(boot_win);
    keypad(boot_win,TRUE);
    Color_set();  
    wrefresh(boot_win);
    init_pair(1,COLOR_WHITE,COLOR_RED);
    init_pair(2,COLOR_WHITE,COLOR_BLACK);
    init_pair(4,COLOR_RED,COLOR_WHITE);
    init_pair(6,COLOR_RED,COLOR_BLACK);
    wmove(boot_title,1,1);
    for(i = 0;i < strlen(p_1);i++) {
        getyx(boot_title,y,x);
        mvwaddch(boot_title,y,x,p_1[i]|COLOR_PAIR(1)|A_BOLD);
        wrefresh(boot_title);
    }
    wrefresh(boot_win);
    wmove(boot_win,5,80 - strlen(p[0]));
    for(i = 0;i < 6;i++) {
        getyx(boot_win,y,x);
        x = (80 - strlen(p[i]))/2;
        y = y + 1;
        wmove(boot_win,y,x);
        for(j = 0;j < strlen(p[i]);j++) {
            mvwprintw(boot_win,y,x + j,"%c",p[i][j]|COLOR_PAIR(2));
            wrefresh(boot_win);
        }
    }
    wrefresh(boot_win);
    login_register();
    wmove(boot_win,0,0);
    wrefresh(boot_choice[0]);

while(1){
    ch = wgetch(boot_win);
    switch(ch) {
        case ENTER:
             if(flag == 0) {
                 return 0;
             }
             if(flag == 1) {
                 return 1;
             }
             return -1;
        case (char)KEY_DOWN:
        case (char)KEY_RIGHT:
             if(flag >= 2 || flag < 0) {
                 flag = -1;
             }
             flag++;
             if(flag == 0) {
       		 wbkgd(boot_choice[flag],COLOR_PAIR(4));
                 wrefresh(boot_choice[flag]);
                 wbkgd(boot_choice[2],COLOR_PAIR(6));
                 wrefresh(boot_choice[2]);
             }else{
                 wbkgd(boot_choice[flag],COLOR_PAIR(4));
                 wrefresh(boot_choice[flag]);
                 wbkgd(boot_choice[flag - 1],COLOR_PAIR(6));
                 wrefresh(boot_choice[flag - 1]);
                 wrefresh(boot_choice[flag]);
             }
             break;
       case (char)KEY_UP:
       case (char)KEY_LEFT:
             flag--;
             if(flag > 2 || flag < 0) {
                 flag = 2;
                 wrefresh(boot_win);
                 wbkgd(boot_choice[flag],COLOR_PAIR(4));
                 wrefresh(boot_choice[flag]);
                 wbkgd(boot_choice[0],COLOR_PAIR(6));
                 wrefresh(boot_choice[0]);
             }else{
                 wrefresh(boot_win);
                 wbkgd(boot_choice[flag],COLOR_PAIR(4));
                 wrefresh(boot_choice[flag]);
                 wbkgd(boot_choice[flag + 1],COLOR_PAIR(6));
                 wrefresh(boot_choice[flag + 1]);
                 wrefresh(boot_choice[flag]);
             }
             break;
       default:
             return -1;
    } 
} 
    exit_win();
    return -1;
}

int Get_input(WINDOW *tmp,char s[],int MAX_LEN,int flag)
{
    int i = 0,n = 0;
    int col = 0,row = 0;
    char ch[MAX_LEN];
    memset(s,'\0',sizeof(char) * MAX_LEN);
    keypad(tmp, TRUE);
    while(1) {
loop:   
        getyx(tmp,col,row);
        ch[n] = mvwgetch(tmp,col,row);
        switch(ch[n]) {
            case KEY_SPACE:
                 if(i < 1){
                     show_message("Wrong Input\nTry again");
                     goto loop;
                 }else {
                    s[i] = ch[n];
                    mvwaddch(tmp,col,row,ch[n]);
                    i++;
                    n++;
                    break;
                 }
            case ESC:
                 memset(s,'\0',sizeof(char));
                 return -1;
            case ENTER:
                 if(i < 1) {
                      show_message("Wrong Input");
                      goback_n(tmp,n);
                      sleep(3);
                      return -1;
                 }else {
                      s[i] = '\0';
                      return 0;
                 }
            case (char)KEY_BACKSPACE:
                 if(strlen(s) >= 1) {
                     goback_n(tmp,1);
                     i = i - 1;
                     n = n - 1;
                     getyx(tmp,col,row);
                     //mvwprintw(tmp,11,11,"%d %d\n",i,n);
                     wmove(tmp,col,row);
                     if(n <= 0) {
                         memset(s,'\0',sizeof(char) * MAX_LEN);
                         goto loop;
                     }
                     goto loop;
                 } else {
                     memset(s,'\0',sizeof(char));
                     show_message("Please input");
                     goto loop;  
                 }
            default:
                 if(isprint(ch[n])) { 
                     getyx(tmp,col,row);
                     s[i] = ch[n];
                     if(flag == 0) {
                         mvwaddch(tmp,col,row,ch[n]);
                     }else {
                         mvwprintw(tmp,col,row,"*");
                     }
                     i++;
                     n++;
                     if(n > MAX_LEN) {
                         goback_n(tmp,n);
                         return -1;
                     }else {
                         continue;
                     }
                 } else {
                     goback_n(tmp,n);
                     return -1;
                 }
                     
        }   
    }
    return 0;
}



void login_in_win(char *s) 
{
    int i = 0;
    login_win=newwin(3, 10, 9, 22);
    wclear(login_win);
    for(i = 0;i < strlen(s);i++) {
         mvwaddch(login_win,1,i + 1,s[i] | A_BOLD | A_UNDERLINE); 
         wrefresh(login_win);   
    }
    wrefresh(login_win); 
}

void new_user_win(char *s)
{
    int i = 0;
    register_win=newwin(3, 11, 9, 34);
    wclear(register_win);
    for(i = 0;i < strlen(s);i++) {
         mvwaddch(register_win,1,i + 1,s[i] | A_UNDERLINE | A_BOLD); 
         wrefresh(register_win);   
    }
    wrefresh(register_win); 
}



int user_login(void)
{  
    char str_name[15];
    char str_pass[10];
    user_msg_t *p = (user_msg_t *)malloc(sizeof(user_msg_t));
    if(p == NULL) {
        return -1;
    }
    main_win=newwin(14, 78, 4, 1);    /* ÷˜ΩÁ√Ê¥∞ø⁄ */
    /* µ±ø™∆Ùkeypad··£¨ø…“‘ π”√º¸≈Ã…œµƒ“ª–©Ãÿ ‚◊÷‘™£¨»Á…œœ¬◊Û”“µ»∑ΩœÚº¸*/
    keypad(main_win, TRUE);
    keypad(login_win, TRUE);
    keypad(register_win, TRUE);
    Color_set();
    wrefresh(main_win);
    login_in_win("Login In");
    new_user_win("Register");
    mvwprintw(main_win,1,13,"UserName:");
    mvwprintw(main_win,1,40,"[The max length of username is 10]");
    mvwprintw(main_win,3,13,"Password:");
    mvwprintw(main_win,3,40,"[The  length of password is 6]");
input:    
    wmove(main_win,1,32);
    goback_n(main_win,10);
    wrefresh(main_win);
    show_message("Please input user name.");  
    if(Get_input(main_win,str_name,10,0) == 0) {
           for(p = head_user.next;p != &head_user;p = p->next) {
               if(strcmp(str_name,p->user_name) == 0){
                     show_message("User name check\nPlease input password");
           	     wmove(main_win,3,22);
                     wrefresh(main_win); 
                     if(Get_input(main_win,str_pass,6,1) == 0) {
                          if(strcmp(str_pass,p->user_password) == 0){
                	      show_message("Password check");
                	      return 0;
                          }else {
                               show_message("Password is wrong,try again.");
                               sleep(2);
                               goto input;
                          }
           	     }else {
                           show_message("Password is wrong,try again.");
                           sleep(2);
                           goto input;
                     }
                }else{
                    show_message("User name is wrong,try again.");
                    sleep(2);
                    goto input;
                 }
              }
           }else {
            show_message("Wrong Input\nTray again");
            wrefresh(main_win);
            goto input;
      }
    return 1;
}


int core_func(void)
{
    int i = 0,y = 0,x = 0,flag = 0;
    char p = '*';
    char ch;
    operate_main_win = newwin(24,80,0,0);
    operate_win[0] = newwin(3,12,3,2);
    operate_win[1] = newwin(3,12,7,2);
    operate_win[2] = newwin(3,12,11,2);
    Color_set();
    init_pair(1,COLOR_MAGENTA,COLOR_BLACK);
    init_pair(2,COLOR_MAGENTA,COLOR_CYAN);
    init_pair(3,COLOR_MAGENTA,COLOR_WHITE);
    keypad(operate_main_win,TRUE);
    box(operate_main_win,0,0);
    mvwprintw(operate_main_win, 0, 25, "Mini BUG Management Systems");
    wrefresh(operate_main_win);
    mvwprintw(operate_win[0],1,1,"%s","|Add Bug|");
    mvwprintw(operate_win[1],1,1,"%s","|Show Bug|");
    mvwprintw(operate_win[2],1,3,"%s","|Exit|");
    mvwhline(operate_main_win,18,1,0,78);
    wrefresh(operate_main_win);
    for(i = 0;i < 3;i++) {
        wbkgd(operate_win[i],COLOR_PAIR(2));
        wrefresh(operate_win[i]);
    }
    wmove(operate_main_win,5,15);
    getyx(operate_main_win,y,x);
    for(i = 0;i < 11;i++) {
        mvwaddch(operate_main_win,y,x + i,p|COLOR_PAIR(1));
        wrefresh(operate_main_win);
    }
    sleep(1);
    wmove(operate_main_win,6,20);
    getyx(operate_main_win,y,x);
    for(i = 0;i < 7;i++) {
        mvwaddch(operate_main_win,y + i,x,p|COLOR_PAIR(1));
        wrefresh(operate_main_win);
    }
    wmove(operate_main_win,8,26);
    getyx(operate_main_win,y,x);
    for(i = 0;i < 8;i++) {
        mvwaddch(operate_main_win,y,x + i,p|COLOR_PAIR(1));
        wrefresh(operate_main_win);
    }
    wmove(operate_main_win,5,35);
    getyx(operate_main_win,y,x);
    for(i = 0;i < 8;i ++) {
        mvwaddch(operate_main_win,y + i,x,p|COLOR_PAIR(1));
        wrefresh(operate_main_win);
    }
    wmove(operate_main_win,5,35);
    getyx(operate_main_win,y,x);
    for(i = 0;i < 6;i ++) {
        mvwaddch(operate_main_win,y + i,x + i,p|COLOR_PAIR(1));
        wrefresh(operate_main_win);
    }
    sleep(1);
    getyx(operate_main_win,y,x);
    x = x - 1;
    for(i = 0;i < 6;i ++) {
        mvwaddch(operate_main_win,y - i,x + i,p|COLOR_PAIR(1));
        wrefresh(operate_main_win);
    }
    getyx(operate_main_win,y,x);
    x = x - 1;
    for(i = 0;i < 8;i ++) {
        mvwaddch(operate_main_win,y + i,x,p|COLOR_PAIR(1));
        wrefresh(operate_main_win);
    }
    getyx(operate_main_win,y,x);
    x = x + 1;
    for(i = 0;i < 8;i ++) {
        mvwaddch(operate_main_win,y - i,x + i,p|COLOR_PAIR(1));
        wrefresh(operate_main_win);
    }
    sleep(1);
    getyx(operate_main_win,y,x);
    x = x - 1;
    for(i = 0;i < 8;i ++) {
        mvwaddch(operate_main_win,y + i,x + i,p|COLOR_PAIR(1));
        wrefresh(operate_main_win);
    }
    getyx(operate_main_win,y,x);
    x = x - 6;
    y = y - 4;
    for(i = 0;i < 5;i ++) {
        mvwaddch(operate_main_win,y ,x - i,p|COLOR_PAIR(1));
        wrefresh(operate_main_win);
    }
    wmove(operate_main_win,5,71);
    getyx(operate_main_win,y,x);
    for(i = 0;i < 8;i++) {
        mvwaddch(operate_main_win,y,x - i,p|COLOR_PAIR(1));
        wrefresh(operate_main_win);
    }
     sleep(1);
    getyx(operate_main_win,y,x);
    x = x - 1;
    for(i = 0;i < 8;i++) {
        mvwaddch(operate_main_win,y + i,x,p|COLOR_PAIR(1));
        wrefresh(operate_main_win);
    }
    getyx(operate_main_win,y,x);
    x = x - 1;
    for(i = 0;i < 8;i++) {
        mvwaddch(operate_main_win,y,x + i,p|COLOR_PAIR(1));
        wrefresh(operate_main_win);
    }
    //wmove(operate_win[0],1,0);
    wbkgd(operate_win[0],COLOR_PAIR(3));
    wrefresh(operate_win[0]); 
    while(1){
         show_message("Please selection function");
         ch = wgetch(operate_main_win);
         switch(ch) {
         case ENTER:
             if(flag == 0) {
                 return 0;
             }
             if(flag == 1) {
                 return 1;
             }
             return -1;
         case (char)KEY_DOWN:
         case (char)KEY_RIGHT:
             if(flag >= 2 || flag < 0) {
                 flag = -1;
             }
             flag++;
             if(flag == 0) {
       		 wbkgd(operate_win[flag],COLOR_PAIR(3));
                 wrefresh(operate_win[flag]);
                 wbkgd(operate_win[2],COLOR_PAIR(2));
                 wrefresh(operate_win[2]);
             }else{
                 wbkgd(operate_win[flag],COLOR_PAIR(3));
                 wrefresh(operate_win[flag]);
                 wbkgd(operate_win[flag - 1],COLOR_PAIR(2));
                 wrefresh(operate_win[flag - 1]);
                 //wmove(boot_choice[flag],1,0);
                 wrefresh(operate_win[flag]);
             }
             break;
         case (char)KEY_UP:
         case (char)KEY_LEFT:
             flag--;
             if(flag > 2 || flag < 0) {
                 flag = 2;
                 wrefresh(operate_main_win);
                 wbkgd(operate_win[flag],COLOR_PAIR(3));
                 wrefresh(operate_win[flag]);
                 wbkgd(operate_win[0],COLOR_PAIR(2));
                 wrefresh(operate_win[0]);
             }else{
                 wrefresh(operate_main_win);
                 wbkgd(operate_win[flag],COLOR_PAIR(3));
                 wrefresh(operate_win[flag]);
                 wbkgd(operate_win[flag + 1],COLOR_PAIR(2));
                 wrefresh(operate_win[flag + 1]);
                 wrefresh(operate_win[flag]);
             }
             break;
         default:
             return -1;
         } 
     } 
     exit_win();
     return -1;
}


void creat_show_title(void)
{
    show_title = newwin(3,64,1,15);
    Color_set();
    init_pair(1,COLOR_WHITE,COLOR_GREEN);
    mvwprintw(show_title,1,1,"%s","CODE |");
    mvwprintw(show_title,1,10,"%s","TYPE   |");
    mvwprintw(show_title,1,27,"%s","DECRIBE");
    mvwprintw(show_title,1,43,"%s","|       DATE");
    wbkgd(show_title,COLOR_PAIR(1));
    //box(show_title,0,0);
    wrefresh(show_title);
    return;
}



int Add_Bug(void)
{
    time_t rwtime;                  //∂®“Â”√”⁄ªÒ»°µ±«∞œµÕ≥ ±º‰
    struct tm *timeinfo;            //∂®“Â ±º‰Ω·ππÃÂ
    bug_msg_t *p = (bug_msg_t *)malloc(sizeof(bug_msg_t));
    if(p == NULL) {
        show_message("Apply error");
        sleep(2);
        return -1;
    }
    Add_win = newwin(14,64,4,15);
    create_title_window("Add New Bug");
    mvwprintw(Add_win,1,10,"%s","Code:");
    mvwprintw(Add_win,3,10,"%s","Type:");
    mvwprintw(Add_win,5,10,"%s","Describe:");
    wmove(Add_win,1,17);
    wrefresh(Add_win);
    if(head.next == &head) {
		head.prev = p;
		head.next = p;
		p->prev = &head;
		p->next = &head;
    } else {
		p->next = head.next;
		p->prev = &head;
		head.next->prev = p;
		head.next = p;
    }
    srand(time(NULL));
Add_again:
    show_message("Please input the number(0~9999)");
    if(Get_input(Add_win,p->code,4,0) == 0) {
	wmove(Add_win,3,16);
        show_message("Please input the type(Max lenth is 20)");
        if(Get_input(Add_win,p->type,20,0) == 0) {
	    wmove(Add_win,5,19);
            show_message("Please input the describe(Max lenth is 255)");
            if(Get_input(Add_win,p->describe,255,0) == 0) {
                 time(&rwtime);                      //ªÒ»°µ±«∞œµÕ≥ ±º‰
    		 timeinfo = localtime(&rwtime);
		 p->date_t.year = 1900+timeinfo->tm_year;
		 p->date_t.month = 1+timeinfo->tm_mon;
		 p->date_t.day = timeinfo->tm_mday;
		 p->date_t.hour = timeinfo->tm_hour;
		 p->date_t.min = timeinfo->tm_min;
		 p->date_t.sec = timeinfo->tm_sec;
                 show_message(" New bug successfully added!");
                 sleep(2);
                 return 0;
            }else {
                 goto Add_again;
            }
        }else {
                 goto Add_again;
        }
    }else {
              goto Add_again;
    }
    return -1;
}



int find_bug(void)
{
    int i = 0;
    char *s = NULL;
    char ch;
    Color_set();
    init_pair(0,COLOR_RED,COLOR_GREEN);
    show_find_win = newwin(1,64,4,15);
    bug_msg_t *p = (bug_msg_t *)malloc(sizeof(bug_msg_t));
    if(p == NULL) {
        show_message("Apply Error");
        sleep(2);
        return -1;
    }
    for(i = 0;i < 2;i++) {
         wclear(prompting_frame[i]);
         wrefresh(prompting_frame[i]);
    }
    keypad(show_find_win,TRUE);
    mvwprintw(prompting_frame[0],0,1,"%s","Input the code:");
    wrefresh(prompting_frame[0]);
    wmove(prompting_frame[1],0,5);
    wrefresh(prompting_frame[1]);
    show_message("Please input the code(0~9999)");
    Get_input(prompting_frame[1],s,4,0);
    for(p = head.next;p != &head;p = p->next) {
        if(strcmp(s,p->code) == 0) {
            wclear(show_win);
            wrefresh(show_win);
            creat_show_title();
            wrefresh(show_find_win);
            mvwprintw(show_find_win,0,2,"%s",p->code);
            mvwprintw(show_find_win,0,8,"%s",p->type);
            mvwprintw(show_find_win,0,20,"%s",p->describe);
            mvwprintw(show_find_win,0,44,"%4d-",p->date_t.year);
            mvwprintw(show_find_win,0,49,"%02d-",p->date_t.month);   
            mvwprintw(show_find_win,0,52,"%02d ",p->date_t.day); 
            mvwprintw(show_find_win,0,55,"%02d:",p->date_t.hour); 
            mvwprintw(show_find_win,0,58,"%02d:",p->date_t.min); 
            mvwprintw(show_find_win,0,61,"%02d",p->date_t.sec); 
            wbkgd(show_find_win,COLOR_PAIR(0));
            wrefresh(show_find_win);
            show_message("1.Press ESC to exit.\n2.Press ENTER to delet.");
        del:          
            ch = wgetch(show_find_win);
            switch(ch) {
                case ENTER:
                    p->prev->next = p->next;
		    p->next->prev = p->prev;
	            free(p);
                    show_message("Deleted successfully");
                    sleep(2);
                    return 0;
                case ESC:
                    return 0;
                default:
                    goto del;
            }
            return 0;
        }else {
            continue;
        }
    }
    if(p == &head) {
        show_message("The bug does not exist.");
        sleep(2);
        return -1;
    }
    return -1;
}



int Selection_Show_Bug(void)
{
    int i = 0,y = 7,flag = 0,flag_1 = 0,x = 0;
    char ch,ch_1,match[10][4];
    bug_msg_t *p = (bug_msg_t *)malloc(sizeof(bug_msg_t));
    if(p == NULL) {
        show_message("Apply Error");
        sleep(1);
        return -1;
    }
    for(i = 0;i < 10;i++) {
        show_all_win[i] = newwin(1,64,4 + i,15);
    }
    for(i = 0;i < 2;i++) {
        y = y + i * 2;
        prompting_frame[i] = newwin(1,21,y,32);
    }
    show_win = newwin(14,64,4,15);
    keypad(show_win,TRUE);
    wrefresh(show_win);
    prompting_win = newwin(7,25,5,30);
    box(prompting_win,0,ACS_HLINE);
    wrefresh(prompting_win);
    Color_set();
    init_pair(1,COLOR_MAGENTA,COLOR_CYAN);
    init_pair(0,COLOR_RED,COLOR_WHITE);
    init_pair(2,COLOR_WHITE,COLOR_CYAN);
    init_pair(3,COLOR_CYAN,COLOR_WHITE);
    mvwprintw(prompting_frame[0],0,1,"%s","Show all of the bugs");
    mvwprintw(prompting_frame[1],0,1,"%s","Show what you want");
    wbkgd(prompting_frame[0],COLOR_PAIR(1));
    wrefresh(prompting_frame[0]);
    wbkgd(prompting_frame[1],COLOR_PAIR(0));
    wrefresh(prompting_frame[1]);
    wmove(prompting_frame[0],0,1);
    wrefresh(prompting_frame[0]);
    keypad(prompting_win,TRUE);
    wrefresh(prompting_win);
    while(1) {
loop:   
     ch = wgetch(prompting_win);
     switch(ch){
	 	case ENTER:
            if(flag == 0) {
                 wclear(prompting_win);
                 wrefresh(prompting_win);
                 for(i = 0;i < 2;i++) {
                      wclear(prompting_frame[i]);
                      wrefresh(prompting_frame[i]);
                 }
                 creat_show_title();
                 for(i=0,p=head.next;(p!=&head)&&(i<10);p=p->next,i++) {
                      if(p->code != NULL) {
                           strcpy(match[i],p->code);
                           mvwprintw(show_all_win[i],0,2,"%s",p->code);
            		       mvwprintw(show_all_win[i],0,8,"%s",p->type);
            		       mvwprintw(show_all_win[i],0,20,"%s",p->describe);
            			   mvwprintw(show_all_win[i],0,44,"%4d-",p->date_t.year);
            			   mvwprintw(show_all_win[i],0,49,"%02d-",p->date_t.month);   
            			   mvwprintw(show_all_win[i],0,52,"%02d ",p->date_t.day); 
            			   mvwprintw(show_all_win[i],0,55,"%02d:",p->date_t.hour); 
            			   mvwprintw(show_all_win[i],0,58,"%02d:",p->date_t.min); 
            			   mvwprintw(show_all_win[i],0,61,"%02d",p->date_t.sec); 
            			   wbkgd(show_all_win[i],COLOR_PAIR(2));
            			   wrefresh(show_all_win[i]);
                      }
                 }
                 wbkgd(show_all_win[0],COLOR_PAIR(3));
                 wrefresh(show_all_win[0]);
                 while(2){
               get:
                    show_message("1.Press KEY DOWN to choose.\n2.Press ESC to exit.\n3.Press ENTER to delet.");
                    ch_1 = wgetch(show_win);
                    switch(ch_1) {
                         case ESC:
                             return -1;
                         case ENTER:
                             for(p = head.next;p != &head;p = p ->next){
                                   if(strcmp(match[flag_1],p->code)==0) {
                                        p->prev->next = p->next;
		    							p->next->prev = p->prev;
	            						free(p);
                    					show_message("Deleted successfully");
                    					sleep(2);
                                        wclear(show_all_win[flag_1]);
                                        wrefresh(show_all_win[flag_1]);
                                        goto get;
                                   }
                             }
                             case (char)KEY_DOWN:
                             case (char)KEY_RIGHT:
                                  x = i - 1;
                                  if(flag_1 == x){
                                       flag_1 = 0;
                    				   wbkgd(show_all_win[flag_1],COLOR_PAIR(3));
    		                           wrefresh(show_all_win[flag_1]);
    		    					   wbkgd(show_all_win[x],COLOR_PAIR(2));
    		    					   wrefresh(show_all_win[x]);
                    				   break;
                                       
                                  }
                                  flag_1++;
                    			  wbkgd(show_all_win[flag_1],COLOR_PAIR(3));
    		    				  wrefresh(show_all_win[flag_1]);
    		    				  wbkgd(show_all_win[flag_1 - 1],COLOR_PAIR(2));
    		    				  wrefresh(show_all_win[flag_1 - 1]);
                    			  break;
                        
                             default:
                                  return -1;
                        }
                    }
                    return -1;
                }
                if(flag == 1) {
                    if(find_bug() == 0) {
                        return -1;
                    }
                }
                return -1;
            case (char)KEY_DOWN:
            case (char)KEY_RIGHT:
                if(flag == 1) {
                    flag = 0;
                    wbkgd(prompting_frame[flag],COLOR_PAIR(1));
    		    wrefresh(prompting_frame[flag]);
    		    wbkgd(prompting_frame[1],COLOR_PAIR(0));
    		    wrefresh(prompting_frame[1]);
                    break;
                }
                    flag++;
                    wbkgd(prompting_frame[flag],COLOR_PAIR(1));
    		    wrefresh(prompting_frame[flag]);
    		    wbkgd(prompting_frame[flag - 1],COLOR_PAIR(0));
    		    wrefresh(prompting_frame[flag - 1]);
                
                break; 
           case (char)KEY_LEFT:
           case (char)KEY_UP:
                if(flag == 0) {
                    flag = 1;
                    wbkgd(prompting_frame[flag],COLOR_PAIR(1));
    		    wrefresh(prompting_frame[flag]);
    		    wbkgd(prompting_frame[0],COLOR_PAIR(0));
    		    wrefresh(prompting_frame[0]);
                    break;
               }
                    flag--;
                    wbkgd(prompting_frame[flag],COLOR_PAIR(1));
    		    wrefresh(prompting_frame[flag]);
    		    wbkgd(prompting_frame[flag + 1],COLOR_PAIR(0));
    		    wrefresh(prompting_frame[flag + 1]);
               
               break;
            default:
                    goto loop;
                    return -1;
          }
     } 
     return -1;
}


int User_register(void) 
{
    char ch;
    user_msg_t *p = (user_msg_t *)malloc(sizeof(user_msg_t));
    if(p == NULL) {
        return -1;
    }
    if(head_user.next == &head_user) {
		head_user.prev = p;
		head_user.next = p;
		p->prev = &head_user;
		p->next = &head_user;
    } else {
		p->next = head_user.next;
		p->prev = &head_user;
		head_user.next->prev = p;
		head_user.next = p;
    }
    register_win = newwin(12,64,5,12);
    mvwprintw(register_win,3,3,"%s","User Name:");
    mvwprintw(register_win,5,4,"%s","Password:");
    wrefresh(register_win);
    keypad(register_win,TRUE);
    show_message("1.Press ENTER to input.\n2.Press ESC to exit.");
    ch = wgetch(register_win);
    switch(ch) {
         case ENTER:
register_Again:
    wmove(register_win,3,14);
    wrefresh(register_win);
    show_message("Please input user name\nMax lenth of user name is 10.");
    if(Get_input(register_win,p->user_name,10,0) == 0) {
        wmove(register_win,5,14);
        show_message("Please input password\nMax lenth of password is 6.");
        if(Get_input(register_win,p->user_password,6,1) == 0) {
             show_message("New user successfully added !");
             sleep(2);
             return 0;
        }else {
             goto register_Again;
        } 
    }else{
         goto register_Again;
    }
        case ESC:
            return -1;
        default:
            goto register_Again;
    }
    return -1;
}



void File_bugList(bug_msg_t *p)
{
        FILE *fp;
	fp = fopen("bugList.txt","w");
	if(fp == NULL) {
		fprintf(stderr, "Can not open inputfile.\n");
		return;
	}
	//File_List_Add();
		for(p = head.next;p != &head;p = p->next) {
		fprintf(fp,"Code:%s\n",p->code);
		fprintf(fp,"Type: %s\n",p->type);
		fprintf(fp,"Describe: %s\r",p->describe);
		fprintf(fp,"Date: %04d-",p->date_t.year);
		fprintf(fp,"%02d-",p->date_t.month);
                fprintf(fp,"%02d-",p->date_t.day);
                fprintf(fp,"%02d:",p->date_t.hour);
                fprintf(fp,"%02d:",p->date_t.min);
                fprintf(fp,"%02d\r",p->date_t.sec);
	}
	fclose(fp);
	return;
}


void overload_bugList(void)
{
	bug_msg_t *p;
        int i = 0;
        char str[20];
        FILE *fp;
	fp = fopen("bugList.txt","a+");
	if(fp == NULL) {
		return;
	}
        printf("healoo\n");
	while(fgets(str,sizeof(bug_msg_t),fp) == NULL) {
		printf("Nothing\n");
		return;
	}
	fseek(fp, 0, SEEK_SET);
        printf("aaaa\n");
       
	while(!feof(fp)) {
                i++;
                printf("%d\n",i);
		p = (bug_msg_t *)malloc(sizeof(bug_msg_t));
		if(p == NULL) {
			printf("Aply Error\n");
			return;
		}
		if(head.next == &head) {
			head.prev = p;
			head.next = p;
			p->prev = &head;
			p->next = &head;
		} else {
			p->next = head.next;
			p->prev = &head;
			head.next->prev = p;
			head.next = p;
		}
             	fscanf(fp,"Code:%s\n",p->code); 
		fscanf(fp,"Type: %s\n",p->type);
		fscanf(fp,"Describe: %s\r",p->describe);
        	fscanf(fp,"Date: %04d-",&p->date_t.year);
        	fscanf(fp,"%02d-",&p->date_t.month);
                fscanf(fp,"%02d-",&p->date_t.day);
                fscanf(fp,"%02d:",&p->date_t.hour);
                fscanf(fp,"%02d:",&p->date_t.min);
                fscanf(fp,"%02d\r",&p->date_t.sec);
      	}
    fclose(fp);
    return;
}


void File_userList(user_msg_t *p)
{
    FILE *fp;
	fp = fopen("userList.txt","w");
	if(fp == NULL) {
		fprintf(stderr, "Can not open inputfile.\n");
		return;
	}
		for(p = head_user.next;p != &head_user;p = p->next) {
		fprintf(fp,"User Name:%s\n",p->user_name);
		fprintf(fp,"Password: %s\n",p->user_password);
	}
	fclose(fp);
	return;
}



int overload_userList(void)
{
	user_msg_t *p;
        char str[20];
        FILE *fp;
	fp = fopen("userList.txt","a+");
	if(fp == NULL) {
		return -1;
	}
	while(fgets(str,sizeof(user_msg_t),fp) == NULL) {
		show_message("No user");
                sleep(2);
		return -1;
	}
	fseek(fp, 0, SEEK_SET);
	while(!feof(fp)) {
		p = (user_msg_t *)malloc(sizeof(user_msg_t));
		if(p == NULL) {
			printf("Aply Error\n");
			return -1;
		}
		if(head_user.next == &head_user) {
		head_user.prev = p;
		head_user.next = p;
		p->prev = &head_user;
		p->next = &head_user;
        } else {
		p->next = head_user.next;
		p->prev = &head_user;
		head_user.next->prev = p;
		head_user.next = p;
        }
        fscanf(fp,"User Name:%s\n",p->user_name); 
		fscanf(fp,"Password: %s\n",p->user_password);
      	}
    fclose(fp);
    return 0;;
}
















