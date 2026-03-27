#include "../include/Reader.h"
#include "../include/Book.h"
#include <bits/stdc++.h>
#include <windows.h>
#include "../include/Account.h"

using namespace std;

void Reader::readerMenu(const string& username) {
    int choice;
    do {
        system("cls");
        setColor(11);
        cout<<"=== 读者模式 === 当前用户:  "<<username<<endl;
        setColor(7);
        cout<<"\n请选择操作:\n"<< endl;
        cout<<"1. 搜索图书"<<endl;
        cout<<"2. 借阅图书"<<endl;
        cout<<"3. 归还图书"<<endl;
        cout<<"4. 查看我的借阅"<<endl;
        cout<<"5. 查看排行榜"<<endl;
        cout<<"6. 预约图书"<<endl; 
        cout<<"0. 返回上级菜单\n"<<endl;
        cout<<"请选择: ";
        cin>>choice;
        
        switch(choice) {
            case 1:
                system("cls");
                searchBookMenu();
                break;
                
            case 2:
                system("cls");
                borrowBookMenu(username);
                break;
                
            case 3:
                system("cls");
                returnBookMenu(username);
                break;
                
            case 4:
                system("cls");
                viewMyBooks(username);
                cout<<"\n按任意键继续..."<<endl;
                cin.ignore();
                cin.get();
                break;
                
            case 5:
                system("cls");
                viewRankingMenu();
                break;
                
            case 6:
            	system("cls");
            	reservebook(username);
                
            case 0:
                return;
            default:
                cout<<"无效选择，请重新输入！"<<endl;
                cin.ignore();
                cin.get();
        }
    } while(choice != 0);
}

void Reader::borrowBookMenu(const string& username) {
    system("cls");
    cout<<"=== 借阅图书 ===\n"<<endl;
    
    vector<Book> books = Book::loadFromFile();
    vector<Book> availableBooks;
    
    for (const auto& book : books) {
        if (!book.getIsBorrowed()) {
            availableBooks.push_back(book);
        }
    }
    
    if (availableBooks.empty()) {
        setColor(12);
        cout<<"暂无可借阅的图书！"<<endl;
        setColor(7);
        cout<<"\n按任意键返回..."<<endl;
        cin.ignore();
        cin.get();
        return;
    }
    
    cout << "可借阅图书列表:\n" << endl;
    for (int i = 0; i < availableBooks.size(); i++) {
        const auto& book = availableBooks[i];
        cout<<i+1 << ". 《"<< book.getTitle()<<"》"<<endl;
        cout<<"   ISBN: "<< book.getISBN() <<" 作者: " <<book.getAuthor()<<endl;
        cout<<"   出版社: "<< book.getPublisher() << " 价格: " <<book.getPrice()<< "元"<<endl;
        cout<<"   借阅次数: "<< book.getBorrowCount()<<" 出版日期: " <<book.getPublishDate()<< endl;
        cout<< endl;
    }
    
    string isbn;
    cout<<"请输入要借阅的图书ISBN（输入0取消）: ";
    cin>>isbn;
    
    if (isbn == "0") {
        return;
    }
    
    bool bookExists = false;
    for (const auto& book : books) {
        if (book.getISBN() == isbn) {
            bookExists = true;
            break;
        }
    }
    
    if (!bookExists) {
        setColor(12);
        cout<<"图书不存在！"<<endl;
        setColor(7);
        cout<<"\n按任意键返回..."<<endl;
        cin.ignore();
        cin.get();
        return;
    }
    
    if (Book::borrowBook(username, isbn)) {
        setColor(10);
        cout <<"借阅成功！"<<endl;
        setColor(7);
        
        vector<Book> recommendations = Book::getRecommendations(username);
        if (!recommendations.empty()) {
            cout<<"\n=== 为您推荐 ===\n"<<endl;
            setColor(14);
            for (int i = 0; i < recommendations.size(); i++) {
                const auto& book = recommendations[i];
                cout<<i+1 << ". 《"<<book.getTitle()<<"》 - "<<book.getAuthor()<<endl;
                cout<<"   ISBN: "<<book.getISBN()<< " 出版社: "<<book.getPublisher()<<endl;
            }
            setColor(7);
        }
    } else {
        setColor(12);
        cout<<"借阅失败！可能原因：图书已被借出，或您已借阅此书。"<<endl;
        setColor(7);
    }
    
    cout<<"\n按任意键继续..."<<endl;
    cin.ignore();
    cin.get();
}

void Reader::reservebook(const string& username){
	system("cls");
    cout<<"=== 预约图书 ===\n"<<endl;
    
    vector<Book> books = Book::loadFromFile();
    vector<Book> availableBooks;
    
    for (const auto& book : books) {
        if (!book.getIsBorrowed()) {
            availableBooks.push_back(book);
        }
    }
    
    if (availableBooks.empty()) {
        setColor(12);
        cout<<"暂无可预约的图书！"<<endl;
        setColor(7);
        cout<<"\n按任意键返回..."<<endl;
        cin.ignore();
        cin.get();
        return;
    }
    
    cout <<"可预约图书列表:\n"<<endl;
    for (int i = 0; i < availableBooks.size(); i++) {
        const auto& book = availableBooks[i];
        cout<<i+1 << ". 《"<< book.getTitle()<<"》"<<endl;
        cout<<"   ISBN: "<< book.getISBN()<<" 作者: "<<book.getAuthor()<<endl;
        cout<<"   出版社: "<< book.getPublisher()<<" 价格: " <<book.getPrice()<<"元"<<endl;
        cout<<"   借阅次数: "<< book.getBorrowCount()<<" 出版日期: " <<book.getPublishDate()<<endl;
        cout<<endl;
    }
    
    string isbn;
    cout<<"请输入要预约的图书ISBN（输入0取消）: ";
    cin>>isbn;
    
    if (isbn == "0") {
        return;
    }
    
    bool bookExists = false;
    for (const auto& book : books) {
        if (book.getISBN() == isbn) {
            bookExists = true;
            break;
        }
    }
    
    if (!bookExists) {
        setColor(12);
        cout<<"图书不存在！"<<endl;
        setColor(7);
        cout<<"\n按任意键返回..."<<endl;
        cin.ignore();
        cin.get();
        return;
    }
    
    if (Book::borrowBook(username, isbn)) {
        setColor(10);
        cout<<"预约成功！"<<endl;
        setColor(7);
        
        vector<Book> recommendations = Book::getRecommendations(username);
        if (!recommendations.empty()) {
            cout<<"\n=== 为您推荐 ===\n"<<endl;
            setColor(14);
            for (int i = 0; i < recommendations.size(); i++) {
                const auto& book = recommendations[i];
                cout<<i+1<<". 《"<< book.getTitle()<< "》 - "<<book.getAuthor()<<endl;
                cout<<"   ISBN: "<< book.getISBN()<<" 出版社: "<<book.getPublisher()<<endl;
            }
            setColor(7);
        }
    } else {
        setColor(12);
        cout << "预约失败！可能原因：图书已被借出，或您已借阅此书。" << endl;
        setColor(7);
    }
    
    cout << "\n按任意键继续..." << endl;
    cin.ignore();
    cin.get();
} 

void Reader::returnBookMenu(const string& username) {
    system("cls");
    cout<<"=== 归还图书 ===\n"<<endl;

    vector<string> borrowedISBNs = Book::getUserBorrowedBooks(username);
    
    if (borrowedISBNs.empty()) {
        cout<<"您当前没有借阅任何图书。"<<endl;
        cout<<"\n按任意键返回..."<<endl;
        cin.ignore();
        cin.get();
        return;
    }
    
    cout<<"您当前借阅的图书:\n"<<endl;
    vector<Book> allBooks = Book::loadFromFile();
    
    for (int i = 0; i < borrowedISBNs.size(); i++) {
        for (const auto& book : allBooks) {
            if (book.getISBN() == borrowedISBNs[i]) {
                cout<<i+1<<". 《"<< book.getTitle()<<"》"<<endl;
                cout<<"   ISBN: "<< book.getISBN()<<" 作者: "<<book.getAuthor()<<endl;
                cout<< endl;
                break;
            }
        }
    }
    
    string isbn;
    cout<<"请输入要归还的图书ISBN（输入0取消）: ";
    cin>>isbn;
    
    if (isbn == "0") {
        return;
    }

    bool hasBorrowed = false;
    for (const string& borrowedISBN : borrowedISBNs) {
        if (borrowedISBN == isbn) {
            hasBorrowed = true;
            break;
        }
    }
    
    if (!hasBorrowed) {
        setColor(12);
        cout << "您没有借阅此书！" << endl;
        setColor(7);
        cout << "\n按任意键返回..." << endl;
        cin.ignore();
        cin.get();
        return;
    }

    if (Book::returnBook(username, isbn)) {
        setColor(10);
        cout << "归还成功！" << endl;
        setColor(7);
    } else {
        setColor(12);
        cout << "归还失败！" << endl;
        setColor(7);
    }
    
    cout<<"\n按任意键继续..."<<endl;
    cin.ignore();
    cin.get();
}

void Reader::searchBookMenu() {
    Book::searchBook();
    cout<<"\n按任意键继续..."<<endl;
    cin.ignore();
    cin.get();
}

void Reader::viewRankingMenu() {
    int choice;
    do {
        system("cls");
        cout<<"=== 排行榜 ===\n"<<endl;
        cout<<"1. 借阅排行榜"<<endl;
        cout<<"2. 最新图书榜"<<endl;
        cout<<"0. 返回\n"<<endl;
        cout<<"请选择: ";
        cin >> choice;
        
        switch(choice) {
            case 1:
                system("cls");
                Book::showBorrowRanking();
                cout<<"\n按任意键继续..."<<endl;
                cin.ignore();
                cin.get();
                break;
                
            case 2:
                system("cls");
                Book::showNewBookRanking();
                cout<<"\n按任意键继续..."<<endl;
                cin.ignore();
                cin.get();
                break;
                
            case 0:
                return;
            default:
                cout<<"无效选择！"<<endl;
                cin.ignore();
                cin.get();
        }
    } while(choice != 0);
}

void Reader::viewMyBooks(const string& username) {
    cout<<"=== 我的借阅 ===\n"<<endl;
    
    vector<string> borrowedISBNs = Book::getUserBorrowedBooks(username);
    
    if (borrowedISBNs.empty()) {
        cout<<"您当前没有借阅任何图书。"<<endl;
        return;
    }
    
    cout <<"您当前借阅 "<<borrowedISBNs.size()<<" 本图书:\n"<<endl;
    
    vector<Book> allBooks = Book::loadFromFile();
    for (int i = 0; i < borrowedISBNs.size(); i++) {
        for (const auto& book : allBooks) {
            if (book.getISBN() == borrowedISBNs[i]) {
                cout<< i+1 << ". 《"<<book.getTitle()<<"》"<<endl;
                cout<<"   ISBN: "<<book.getISBN()<<endl;
                cout<<"   作者: "<<book.getAuthor()<<endl;
                cout<<"   出版社: "<<book.getPublisher()<<endl;
                cout<<"   价格: "<<book.getPrice()<<"元" <<endl;
                cout<<"   借阅次数: "<<book.getBorrowCount()<<endl;
                cout<<"   应归还日期: 借阅后30天内"<<endl;
                cout<< endl;
                break;
            }
        }
    }
    
    ifstream fin("Data\\return.txt");
    if (fin.is_open()) {
        string user, isbn, borrowDate, returnDate;
        vector<string> history;
        
        cout<<"=== 借阅历史 ===\n"<<endl;
        
        while (fin >> user >> isbn >> borrowDate >> returnDate) {
            if (user == username) {
                for (const auto& book : allBooks) {
                    if (book.getISBN() == isbn) {
                        cout<<"《"<< book.getTitle() << "》"<<endl;
                        cout<<"   借阅时间: " <<borrowDate<<endl;
                        cout<<"   归还时间: " <<returnDate<<endl;
                        cout<< endl;
                        break;
                    }
                }
            }
        }
        fin.close();
    }
}
