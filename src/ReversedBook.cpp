#include "../include/ReversedBook.h"
#include <fstream>
#include <sstream>
#include <windows.h>
#include "../include/Account.h"

using namespace std;

ReservedBook::ReservedBook() : Book(), reservedUser(""), reservationStatus(0) {
    time(&reserveDate);
    expiryDate = reserveDate + (15 * 24 * 3600);  // 15天后过期
}

ReservedBook::ReservedBook(const string& title, const string& isbn,
                         const string& author, const string& publisher,
                         double price, const string& publishDate,
                         const string& user)
    : Book(title, isbn, author, publisher, price, publishDate, 0, true),
      reservedUser(user), reservationStatus(0) {
    time(&reserveDate);
    expiryDate = reserveDate + (15 * 24 * 3600);
}

bool ReservedBook::makeReservation(const string& username, const string& isbn) {
    vector<Book> books = Book::loadFromFile();
    bool bookExists = false;
    bool bookBorrowed = false;
    
    for (const auto& book : books) {
        if (book.getISBN() == isbn) {
            bookExists = true;
            bookBorrowed = book.getIsBorrowed();
            break;
        }
    }
    
    if (!bookExists) {
        return false;
    }
    
    if (!bookBorrowed) {
        return false;
    }
    
    vector<ReservedBook> reservations = loadReservationsFromFile();
    
    ReservedBook resBook;
    for (const auto& book : books) {
        if (book.getISBN() == isbn) {
            resBook = ReservedBook(book.getTitle(), book.getISBN(),
                                 book.getAuthor(), book.getPublisher(),
                                 book.getPrice(), book.getPublishDate(), username);
            break;
        }
    }
    
    reservations.push_back(resBook);
    
    return true;
}

bool ReservedBook::cancelReservation(const string& username, const string& isbn) {
    vector<ReservedBook> reservations = loadReservationsFromFile();
    vector<ReservedBook> newReservations;
    bool found = false;
    
    if (!found) {
        return false;
    }
    
    return true;
}



vector<ReservedBook> ReservedBook::loadReservationsFromFile() {
    vector<ReservedBook> reservations;
    ifstream fin("Data\\reservations.txt");
    
    if (!fin.is_open()) {
        return reservations;
    }
    
    string line;
    while (getline(fin, line)) {
        if (line.empty()) continue;
        
        istringstream iss(line);
        string title, isbn, author, publisher, publishDate, user;
        double price;
        int borrowCount, status;
        time_t resDate, expDate;
        bool isBorrowed;
        
        if (iss >> title >> isbn >> author >> publisher >> price >> borrowCount
                >> publishDate >> isBorrowed >> user >> status >> resDate >> expDate) {
            ReservedBook resBook(title, isbn, author, publisher, price,
                               publishDate, user);
            reservations.push_back(resBook);
        }
    }
    fin.close();
    
    return reservations;
}


