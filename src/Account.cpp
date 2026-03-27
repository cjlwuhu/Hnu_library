#include <bits/stdc++.h>
#include <windows.h>  
#include "../include/Account.h"
#include<conio.h>
using namespace std;

string currentUsername = "";

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

string getProtectedInput(){
    string input;
    char ch;
    
    while(1){
        ch=_getch();
        
        if(ch=='\r'){
            cout<<endl;
            break;
        }
        else if(ch=='\b'){
            if(!input.empty()){
                input.pop_back();
                cout<<"\b \b";
            }
        }
        else if(ch>=32&&ch<=126){
            input.push_back(ch);
            cout<<"*";
        }
        else if(ch==3){
            cout<<endl;
            input.clear();
            break;
        }
    }
    
    return input;
}

int sign_up_conductor() {
    map<string, string> mapp;
    
    ifstream fin("Data\\conductor.txt");
    string a, b;
    while (fin >> a) {
        fin >> b;
        mapp[a] = b;
    }
    fin.close();
    
    cout << "请输入账号: ";
    cin >> a;
    cout << "请输入密码 " << endl;
    cout<<"是否开启输入保护？(1:开启,0:不开启):";
    int choice;
    cin>>choice;
    cin.ignore();
    if(choice==1){
        cout<<"输入保护已开启。请输入密码（将显示为*）:";
        b=getProtectedInput();
        
    }else{
        cout<<"输入保护未开启。请输入密码:";
        getline(cin,b);
    }
    
    if (mapp[a] == b) {
    	currentUsername = a;
    	return 1;
    }
    else return 0;
}

int register_conductor() {
    map<string, string> mapp;
    
    ifstream fin("Data\\conductor.txt");
    string a, b;
    while (fin >> a) {
        fin >> b;
        mapp[a] = b;
    }
    fin.close();
    
    cout << "请输入账号: ";
    cin >> a;
    cout << "请输入密码: ";
    cin >> b;
    
    if (mapp[a] != "\0") return 2;
    else {
        ofstream fout("Data\\conductor.txt", ios::app);
        fout << endl << a << " " << b;
        fout.close();
        return 1;
    }
}

int sign_up_reader() {
    map<string, string> mapp;
    
    ifstream fin("Data\\reader.txt");
    string a, b;
    while (fin >> a) {
        fin >> b;
        mapp[a] = b;
    }
    fin.close();
    
    cout << "请输入账号: ";
    cin >> a;
    cout << "请输入密码"<<endl;
    cout<<"是否开启输入保护？(1:开启,0:不开启):";
    int choice;
    cin>>choice;
    cin.ignore();
    if(choice==1){
        cout<<"输入保护已开启。请输入密码（将显示为*）:";
        b=getProtectedInput();
        
        if(!b.empty()){
            cout<<"输入内容已接收并处理。"<<endl;
        }
    }else{
        cout<<"输入保护未开启。请输入密码:";
        getline(cin,b);
    }
    
    if (mapp[a] == b) {
    	currentUsername =a;
    	return 1;
    }
    else return 0;
}

int register_reader() {
    map<string, string> mapp;
    
    ifstream fin("Data\\reader.txt");
    string a, b;
    while (fin >> a) {
        fin >> b;
        mapp[a] = b;
    }
    fin.close();
    
    cout << "请输入账号: ";
    cin >> a;
    cout << "请输入密码: ";
    cin >> b;
    
    if (mapp[a] != "\0") return 2;
    else {
        ofstream fout("Data\\reader.txt", ios::app);
        fout << endl << a << " " << b;
        fout.close();
        return 1;
    }
}

int conductor() {
    int o;
    int flag = 0;
    int k = 0;
    
    do {
        system("cls");
        cout << "管理员系统请选择:\n\n1.登录\n\n2.注册\n\n0.返回上级菜单\n\n";
        cin >> o;
        getchar();
        
        switch (o) {
            case 1:
                system("cls");
                k = sign_up_conductor();
                if (k == 1) {
                    flag = 1;
                    setColor(10);  
                    cout << "登录管理员成功,已进入管理员模式" << endl;
                    setColor(7);   
                    cout << "按任意键继续...";
                } else {
                    setColor(12); 
                    cout << "账号或密码错误！" << endl;
                    setColor(7);   
                    cout << "按任意键返回...";
                }
                getchar();
                getchar();
                break;
            case 2:
                system("cls");
                k = register_conductor();
                if (k == 1) {
                    flag = 1;
                    setColor(10);  
                    cout << "注册成功，已进入管理员模式" << endl;
                    setColor(7);  
                    cout << "按任意键继续...";
                } else if (k == 2) {
                    setColor(12); 
                    cout << "账号已存在，请重新选择！" << endl;
                    setColor(7);   
                    cout << "按任意键返回...";
                }
                getchar();
                getchar();
                break;
            case 0:
                system("cls");
                cout << "返回上级菜单..." << endl;
                return 0;  
        }
    } while (flag != 1 && o != 0);
    
    return 1;  
}

int reader() {
    int o;
    int flag = 0;
    int k = 0;
    
    do {
        system("cls");
        cout << "读者系统请选择:\n\n1.登录\n\n2.注册\n\n0.返回上级菜单\n\n";
        cin >> o;
        getchar();
        
        switch (o) {
            case 1:
                system("cls");
                k = sign_up_reader();
                if (k == 1) {
                    flag = 1;
                    setColor(11);  
                    cout << "登录读者成功,已进入读者模式" << endl;
                    setColor(7);   
                    cout << "按任意键继续...";
                } else {
                    setColor(12);  
                    cout << "账号或密码错误！" << endl;
                    setColor(7);  
                    cout << "按任意键返回...";
                }
                getchar();
                getchar();
                break;
            case 2:
                system("cls");
                k = register_reader();
                if (k == 1) {
                    flag = 1;
                    setColor(11);  
                    cout << "注册成功，已进入读者模式" << endl;
                    setColor(7);  
                    cout << "按任意键继续...";
                } else if (k == 2) {
                    setColor(12); 
                    cout << "账号已存在，请重新选择！" << endl;
                    setColor(7);  
                    cout << "按任意键返回...";
                }
                getchar();
                getchar();
                break;
            case 0:
                system("cls");
                cout << "返回上级菜单..." << endl;
                return 0; 
            default:
                system("cls");
                setColor(12);
                cout << "无效选择，请重新输入！" << endl;
                setColor(7);   
                cout << "按任意键继续..." << endl;
                getchar();
        }
    } while (flag != 1 && o != 0);
    
    return 2;  
}

void showLoginStatus(int id) {
    if (id == 1) {  
        setColor(10);  
        cout << "[管理员登录成功] ";
        setColor(7);   
    } else if (id == 2) { 
        setColor(11); 
        cout << "[读者登录成功] ";
        setColor(7);  
    }
}
