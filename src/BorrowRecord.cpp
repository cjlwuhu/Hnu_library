#include "../include/BorrowRecord.h"
#include <fstream>
#include <sstream>
#include <windows.h>
#include "../include/Account.h"

using namespace std;

BorrowRecord::BorrowRecord() : borrower(""), bookISBN(""), isReturned(false), fine(0.0) {
    time(&borrowDate);
    dueDate = borrowDate + (30 * 24 * 3600);  // 30天后到期
    returnDate = 0;
}

BorrowRecord::BorrowRecord(const string& user, const string& isbn)
    : borrower(user), bookISBN(isbn), isReturned(false), fine(0.0) {
    time(&borrowDate);
    dueDate = borrowDate + (30 * 24 * 3600);
    returnDate = 0;
}

vector<BorrowRecord> BorrowRecord::getUserRecords(const string& username) {
    vector<BorrowRecord> userRecords;
    vector<BorrowRecord> allRecords = loadRecordsFromFile();
    
    
    return userRecords;
}


void BorrowRecord::generateReport() {
    vector<BorrowRecord> records = loadRecordsFromFile();
    int totalBorrowed = 0;
    int totalReturned = 0;
    int totalOverdue = 0;
    double totalFines = 0.0;
    time_t now;
    time(&now);
    
    for (const auto& record : records) {
        totalBorrowed++; 
    }
    
    cout << "=== 借阅统计报告 ===" << endl;
    cout << "总借阅次数: " << totalBorrowed << endl;
    cout << "已归还数量: " << totalReturned << endl;
    cout << "逾期未还数量: " << totalOverdue << endl;
    cout << "总罚款金额: " << fixed << setprecision(2) << totalFines << "元" << endl;
}

vector<BorrowRecord> BorrowRecord::loadRecordsFromFile() {
    vector<BorrowRecord> records;
    ifstream fin("Data\\borrow_records.txt");
    
    if (!fin.is_open()) {
        return records;
    }
    
    string line;
    while (getline(fin, line)) {
        if (line.empty()) continue;
        
        istringstream iss(line);
        string user, isbn;
        time_t borrowD, dueD, returnD;
        bool returned;
        double fineAmt;
        
        if (iss >> user >> isbn >> borrowD >> dueD >> returnD >> returned >> fineAmt) {
            BorrowRecord record(user, isbn);
            record.returnDate = returnD;
            record.isReturned = returned;
            record.fine = fineAmt;
            records.push_back(record);
        }
    }
    fin.close();
    
    return records;
}
