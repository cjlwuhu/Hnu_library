#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <bits/stdc++.h>
//管理员，和读者系统的登录 

void setColor(int color);
int sign_up_conductor();  //登录管理员账号 
int register_conductor(); //注册 
int sign_up_reader();  //读者登录 
int register_reader();  //注册 
int conductor(); //管理员系统的菜单 
int reader(); //读者菜单 
void showLoginStatus(int id);  //主页显示状态 
std::string getProtectedInput();

#endif
