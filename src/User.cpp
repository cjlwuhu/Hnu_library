#include "../include/User.h"
#include "../include/Account.h"
#include <bits/stdc++.h>
#include <windows.h>
using namespace std;

User::User() : username(""), password(""), userType(2) {} 

User::User(const string& username, const string& password, int userType)
    : username(username), password(password), userType(userType) {}

string User::getUsername() const { return username; }
string User::getPassword() const { return password; }
int User::getUserType() const { return userType; }

void User::setUsername(const string& username) { this->username = username; }
void User::setPassword(const string& password) { this->password = password; }
void User::setUserType(int userType) { this->userType = userType; }

vector<User> User::loadUsers() {
    vector<User> users;
    ifstream fin("Data\\reader.txt");
    
    if (!fin.is_open()) {
        return users;
    }
    
    string username, password;
    while (fin >> username >> password) {
        users.push_back(User(username, password, 2)); 
    }
    fin.close();
    
    return users;
}

void User::saveUsers(const vector<User>& users) {
    ofstream fout("Data\\reader.txt");
    for (const auto& user : users) {
        fout << user.username << " " << user.password << endl;
    }
    fout.close();
}

void User::addUser() {
    string username, password;
    cout<<"请输入新用户名: ";
    cin>>username;
    cout<<"请输入密码: ";
    cin>>password;
    
    vector<User> users = loadUsers();
    
    for (const auto& user : users) {
        if (user.username == username) {
            setColor(12);
            cout<<"用户名已存在！"<<endl;
            setColor(7);
            return;
        }
    }
    
    users.push_back(User(username, password, 2));
    saveUsers(users);
    
    setColor(10);
    cout<<"用户添加成功！"<<endl;
    setColor(7);
}

void User::deleteUser() {
    string username;
    cout<<"请输入要删除的用户名: ";
    cin>>username;
    
    vector<User> users = loadUsers();
    vector<User> newUsers;
    bool found = false;
    
    for (const auto& user : users) {
        if (user.username != username) {
            newUsers.push_back(user);
        } else {
            found = true;
        }
    }
    
    if (!found) {
        setColor(12);
        cout<<"用户不存在！"<<endl;
        setColor(7);
        return;
    }
    
    saveUsers(newUsers);
    
    setColor(10);
    cout<<"用户删除成功！"<<endl;
    setColor(7);
}

void User::changePassword() {
    string username, oldPassword, newPassword;
    cout<<"请输入用户名: ";
    cin>>username;
    cout<<"请输入原密码: ";
    cin>>oldPassword;
    cout<<"请输入新密码: ";
    cin>>newPassword;
    
    vector<User> users = loadUsers();
    bool found = false;
    
    for (auto& user : users) {
        if (user.username == username) {
            if (user.password == oldPassword) {
                user.password = newPassword;
                found = true;
                setColor(10);
                cout<<"密码修改成功！"<<endl;
                setColor(7);
                break;
            } else {
                setColor(12);
                cout<<"原密码错误！"<<endl;
                setColor(7);
                return;
            }
        }
    }
    
    if (!found) {
        setColor(12);
        cout<<"用户不存在！"<<endl;
        setColor(7);
        return;
    }
    
    saveUsers(users);
}

void User::listUsers() {
    vector<User> users = loadUsers();
    
    if (users.empty()) {
        cout<<"暂无用户。"<<endl;
        return;
    }
    
    cout<<"\n=== 用户列表 ==="<<endl;
    cout<<"总数: " <<users.size()<<" 个用户\n"<<endl;
    
    for (size_t i = 0; i < users.size(); i++) {
        cout<<"用户 "<< i + 1<< ":" <<endl;
        cout<< "  用户名: "<<users[i].username<<endl;
        cout<< "  密码: "<<users[i].password<<endl;
        cout<< "  类型: "<<(users[i].userType == 1 ? "管理员" : "读者")<<endl;
        cout<< endl;
    }
}

void User::resetPassword() {
    string username, newPassword;
    cout<<"请输入要重置密码的用户名: ";
    cin>>username;
    cout<<"请输入新密码: ";
    cin>>newPassword;
    
    vector<User> users = loadUsers();
    bool found = false;
    
    for (auto& user : users) {
        if (user.username == username) {
            user.password = newPassword;
            found = true;
            setColor(10);
            cout<<"密码重置成功！"<<endl;
            setColor(7);
            break;
        }
    }
    
    if (!found) {
        setColor(12);
        cout<<"用户不存在！"<<endl;
        setColor(7);
        return;
    }
    
    saveUsers(users);
}

void User::manageUsers() {
    int choice;
    do {
        system("cls");
        cout<<"=== 用户管理 ==="<<endl;
        cout<<"\n请选择操作:\n"<<endl;
        cout<<"1. 添加用户"<<endl;
        cout<<"2. 删除用户"<<endl;
        cout<<"3. 修改密码"<<endl;
        cout<<"4. 查看用户列表"<<endl;
        cout<<"5. 重置用户密码"<<endl;
        cout<<"0. 返回上级菜单\n"<<endl;
        cout<<"请选择: ";
        cin>>choice;
        
        switch(choice) {
            case 1:
                system("cls");
                addUser();
                cout<<"\n按任意键继续..."<<endl;
                cin.ignore();
                cin.get();
                break;
                
            case 2:
                system("cls");
                deleteUser();
                cout<<"\n按任意键继续..."<<endl;
                cin.ignore();
                cin.get();
                break;
                
            case 3:
                system("cls");
                changePassword();
                cout<<"\n按任意键继续..."<<endl;
                cin.ignore();
                cin.get();
                break;
                
            case 4:
                system("cls");
                listUsers();
                cout<<"\n按任意键继续..."<<endl;
                cin.ignore();
                cin.get();
                break;
                
            case 5:
                system("cls");
                resetPassword();
                cout<<"\n按任意键继续..."<<endl;
                cin.ignore();
                cin.get();
                break;
                
            case 0:
                return;
            default:
                cout<<"无效选择，请重新输入！"<<endl;
                cin.ignore();
                cin.get();
        }
    } while(choice!=0);
}
