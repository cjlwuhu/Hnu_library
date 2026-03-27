#ifndef RESERVEDBOOK_H
#define RESERVEDBOOK_H

#include "Book.h"
#include <string>
#include <ctime>

using namespace std;

class ReservedBook : public Book {
private:
    string reservedUser;        // 预约用户
    time_t reserveDate;         // 预约日期
    time_t expiryDate;          // 预约过期日期
    int reservationStatus;      // 预约状态 0:等待中 1:已通知 2:已取消
    
public:
    ReservedBook();
    ReservedBook(const string& title, const string& isbn, const string& author,
                 const string& publisher, double price, const string& publishDate,
                 const string& user);
    
    static bool makeReservation(const string& username, const string& isbn);
    static bool cancelReservation(const string& username, const string& isbn);
    
    static vector<ReservedBook> loadReservationsFromFile();
};

#endif
