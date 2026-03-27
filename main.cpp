#include <bits/stdc++.h>
#include <windows.h>  
#include "include/Account.h"
#include "include/Book.h"
#include "include/User.h"
#include "include/Reader.h"
#include "include/BorrowRecord.h"
#include "include/ReversedBook.h"
#include "include/BookStatistics.h"

using namespace std;

string currentUser = "";
int currentUserType = 0; // 0:未登录, 1:管理员, 2:读者

void conductorManager(){
    int choice;
    do{
        system("cls");
        showLoginStatus(currentUserType);
        cout<<"\n=== 管理员管理菜单 ==="<< endl;
        cout<< "\n请选择操作:\n"<<endl;
        cout<< "1. 管理用户信息"<< endl;
        cout<< "2. 管理图书信息"<< endl;
        cout<< "0. 返回上级菜单\n"<< endl;
        cout<< "请选择: ";
        cin>>choice;
        
        switch(choice){
            case 1:
                system("cls");
                User::manageUsers();
                break;
                
            case 2:
                system("cls");
                Book::manageBooks();
                break;
                
            case 0:
                system("cls");
                cout<<"返回上级菜单..."<<endl;
                return;
            default:
                cout<<"无效选择，请重新输入！"<<endl;
                cin.ignore();
                cin.get();
        }
    } while(choice != 0);
}

void readerMode(){
    Reader::readerMenu(currentUser);
}

void user_suggestion(){
	
	ShellExecuteA(
        NULL,           // 父窗口句柄
        "open",         // 操作
        "ReadMe.txt", // 文件路径
        NULL,           // 参数
        NULL,           // 默认目录
        SW_SHOWNORMAL   // 显示方式
    );
//	ifstream fin("ReadMe.txt");
//	string s;
//	while(getline(fin,s)){
//		cout << s << endl<<endl;
//	} 
//	fin.close();
//	setColor(10); 	
//	cout << "按任意键返回" <<endl;
	setColor(7); 

	cin.ignore();
	return;
}

int main() {
    int choice;
    
    system("mkdir Data 2>nul");
    
    do {
        system("cls");
        
        if (currentUserType != 0) {
            showLoginStatus(currentUserType);
            if (!currentUser.empty()) {
                cout<<"当前用户: "<<currentUser<<endl;
            }
        }
        
        cout<<"\n=== 图书管理系统 ==="<<endl;
        cout<<"\n请选择操作:\n"<<endl;
        cout<<"1. 管理员登录/注册"<<endl;
        cout<<"2. 读者登录/注册"<<endl;
        cout<<"3. 读者模式"<<endl;
        cout<<"4. 管理员模式"<<endl;
        cout<<"5. 操作指南"<<endl;
        cout<<"0. 退出系统\n"<<endl;
        
        cout<<"请选择: ";
        cin>>choice;
        cin.ignore();
        
        switch (choice) {
            case 1:
                system("cls");
                currentUserType=conductor();
                if (currentUserType==1){
                    currentUser="admin"; 
                }
                break;
            case 2:
                system("cls");
                currentUserType = reader();
                if (currentUserType == 2){
                    cout<<"请输入用户名: ";
                    getline(cin, currentUser);
                }
                break;
            case 3:
                system("cls");
                if (currentUserType!=2) {
                    setColor(12);
                    cout<<"请先以读者身份登录！"<< endl;
                    setColor(7);
                    cout<< "按任意键返回..."<< endl;
                    cin.get();
                } else {
                    readerMode();
                }
                break;
            case 4:
                system("cls");
                if (currentUserType != 1) {
                    setColor(12);
                    cout<<"请先以管理员身份登录！"<< endl;
                    setColor(7);
                    cout<<"按任意键返回..."<<endl;
                    cin.get();
                }else{
                    conductorManager();
                }
                break;
            case 5:
				system("cls");
				user_suggestion();
				break; 
            case 0:
                system("cls");
                setColor(14);
                cout<<"感谢使用图书管理系统，再见！"<<endl;
                setColor(7);
                break;
            default:
                system("cls");
                setColor(12);
                cout<<"无效选择，请重新输入！"<< endl;
                setColor(7);
                cout<<"按任意键继续..." <<endl;
                cin.get();
        }
    } while(choice!=0);
    
    return 0;
}
