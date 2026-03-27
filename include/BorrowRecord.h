#ifndef BORROWRECORD_H
#define BORROWRECORD_H

#include <string>
#include <ctime>
#include <vector>
using namespace std;

class BorrowRecord {
private:
    string borrower;        // 借阅者
    string bookISBN;        // 图书ISBN
    time_t borrowDate;      // 借阅日期
    time_t dueDate;         // 应还日期
    time_t returnDate;      // 实际归还日期
    bool isReturned;        // 是否已归还
    double fine;            // 逾期罚款
    
public:
    BorrowRecord();
    BorrowRecord(const string& user, const string& isbn);
    
    static vector<BorrowRecord> getUserRecords(const string& username);
    static void generateReport();                    // 生成借阅报告
    
    static vector<BorrowRecord> loadRecordsFromFile();
};

#endif
