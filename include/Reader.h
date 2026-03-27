#ifndef READER_H
#define READER_H

//选项3进入读者模式 

#include <string>
using namespace std;

class Reader {
public:
    static void readerMenu(const string& username);  //读者菜单 
    
    static void borrowBookMenu(const string& username);  //图书借阅并推荐系统 
    static void reservebook(const string& username);      //预约图书 
    static void returnBookMenu(const string& username);   //归还图书 
    static void searchBookMenu();  //搜索图书 
    static void viewRankingMenu();   //查看图书排行菜单 
    static void viewMyBooks(const string& username);  //读者借阅经历 
};

#endif 
