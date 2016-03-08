#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <time.h>
#include "win_ui.h"


int main(int argc, char **args)
{
    init_win();
    int i = 0,flag = 0, x = 0;
    bug_msg_t *p = (bug_msg_t *)malloc(sizeof(bug_msg_t));
    if(p == NULL) {
        return -1;
    } 
    user_msg_t *p_1 = (user_msg_t *)malloc(sizeof(user_msg_t));
    if(p_1 == NULL) {
        return -1;
    } 
    head.next = &head;
    head.prev = &head;
    head_user.next = &head_user;
    head_user.prev = &head_user;
    overload_bugList();
joggle: 
	overload_userList();
    i = boot_screen();
    switch(i){
        case 0:
            create_frame();
            create_msg_zone();
            create_title_window("User Login");
			x = user_login();
            if(x == 1) {
                 show_message("No user\nPlease register");
                 sleep(2);
                 goto joggle;
            }            
            if(x == 0) {
            core:
                flag = core_func();
                switch(flag){
                    case 0:
                       p = &head;
                        if( Add_Bug() == 0) {
                            File_bugList(p);
                            goto core;
                        }else {
                             return 0;
                        }
                    case 1:
                        if(Selection_Show_Bug() == -1){
                           goto core;
                        }else {
                             p = &head;
                             File_bugList(p);
                        }
                        break;
                    default:
                         exit_win();
                         return 0;
                }
            }
            break;
        case 1:
            create_frame();
            create_msg_zone();
            create_title_window("User Register");
       	    if(User_register() == 0) {
                 p_1 = &head_user;
                 File_userList(p_1);
                 goto joggle;
                 break;
            }
            break;
        default:
            exit_win();
            return 0;
    }
     exit_win();
     return 0;
}
