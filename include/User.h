#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
using namespace std;

//管理员管理账户信息 

class User {
private:
    string username;    // 用户名
    string password;    // 密码
    int userType;           // 用户类型：1-管理员，2-读者

public:
    User();
    User(const string& username, const string& password, int userType);
    
    //获取账户信息 
    string getUsername() const;
    string getPassword() const;
    int getUserType() const;
    
    //设置账户信息 
    void setUsername(const string& username);
    void setPassword(const string& password);
    void setUserType(int userType);
    
    static void addUser();
    static void deleteUser();
    static void changePassword();
    static void listUsers();
    static void resetPassword();
    static void manageUsers();
    
    //加载账户信息 
    static vector<User> loadUsers();
    static void saveUsers(const vector<User>& users);  //保存用户信息 
};

#endif 
