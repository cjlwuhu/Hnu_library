#include "../include/Book.h"
#include <bits/stdc++.h>
#include <windows.h>
#include "../include/Account.h"

using namespace std;

Book::Book() : title(""), isbn(""), author(""), publisher(""), 
               price(0.0), borrowCount(0), publishDate(""), isBorrowed(false) {}

Book::Book(const string& title, const string& isbn, 
           const string& author, const string& publisher, 
           double price, const string& publishDate, int borrowCount, bool isBorrowed)
    : title(title), isbn(isbn), author(author), publisher(publisher), 
      price(price), borrowCount(borrowCount), publishDate(publishDate), isBorrowed(isBorrowed) {
    if (publishDate.empty()) {
        time_t now = time(0);
        tm* ltm = localtime(&now);
        this->publishDate = to_string(1900 + ltm->tm_year) + "-" + 
                           (ltm->tm_mon + 1 < 10 ? "0" : "") + to_string(ltm->tm_mon + 1);
    }
}

string Book::getTitle() const { return title; }
string Book::getISBN() const { return isbn; }
string Book::getAuthor() const { return author; }
string Book::getPublisher() const { return publisher; }
double Book::getPrice() const { return price; }
int Book::getBorrowCount() const { return borrowCount; }
string Book::getPublishDate() const { return publishDate; }
bool Book::getIsBorrowed() const { return isBorrowed; }

void Book::setTitle(const string& title) { this->title = title; }
void Book::setISBN(const string& isbn) { this->isbn = isbn; }
void Book::setAuthor(const string& author) { this->author = author; }
void Book::setPublisher(const string& publisher) { this->publisher = publisher; }
void Book::setPrice(double price) { this->price = price; }
void Book::setBorrowCount(int count) { this->borrowCount = count; }
void Book::setPublishDate(const string& date) { this->publishDate = date; }
void Book::setIsBorrowed(bool borrowed) { this->isBorrowed = borrowed; }

void Book::incrementBorrowCount() { 
    borrowCount++; 
}

void Book::display() const {
    cout << "书名: " << title << endl;
    cout << "ISBN: " << isbn << endl;
    cout << "作者: " << author << endl;
    cout << "出版社: " << publisher << endl;
    cout << "价格: " << fixed << setprecision(2) << price << "元" << endl;
    cout << "借阅次数: " << borrowCount << endl;
    cout << "出版日期: " << publishDate << endl;
    cout << "状态: " << (isBorrowed ? "已借出" : "可借阅") << endl;
}

void Book::displaySimple() const {
    cout << "《" << title << "》 - " << author;
    if (isBorrowed) {
        cout << " [已借出]";
    }
    cout << endl;
}

bool Book::compareByAuthorTitle(const Book& a, const Book& b) {
    if (a.author != b.author) {
        return a.author < b.author;
    }
    return a.title < b.title;
}

bool Book::compareByBorrowCount(const Book& a, const Book& b) {
    return a.borrowCount > b.borrowCount; 
}

bool Book::compareByPublishDate(const Book& a, const Book& b) {
    return a.publishDate > b.publishDate; 
}

vector<Book> Book::loadFromFile() {
    vector<Book> books;
    ifstream fin("Data\\book.txt");
    
    if (!fin.is_open()) {
        return books;
    }
    
    string line;
    while (getline(fin, line)) {
        if (line.empty()) continue;
        
        istringstream iss(line);
        string title, isbn, author, publisher, publishDate;
        double price;
        int borrowCount;
        bool isBorrowed;
        
        if (iss >> title >> isbn >> author >> publisher >> price >> borrowCount >> publishDate >> isBorrowed) {
            books.push_back(Book(title, isbn, author, publisher, price, publishDate, borrowCount, isBorrowed));
        }
    }
    fin.close();
    
    return books;
}

void Book::saveToFile(const vector<Book>& books) {
    ofstream fout("Data\\book.txt");
    for (const auto& book : books) {
        fout << book.title << " "
             << book.isbn << " "
             << book.author << " "
             << book.publisher << " "
             << fixed << setprecision(2) << book.price << " "
             << book.borrowCount << " "
             << book.publishDate << " "
             << book.isBorrowed << endl;
    }
    fout.close();
}

void Book::addBook() {
    string title, isbn, author, publisher, publishDate;
    double price;
    
    cout<<"=== 添加新书 ==="<<endl;
    cout<< "请输入题名(无空格): ";
    cin>>title;
    cout<<"请输入ISBN/ISSN: ";
    cin>>isbn;
    cout<<"请输入作者: ";
    cin>>author;
    cout<<"请输入出版社: ";
    cin>>publisher;
    cout<<"请输入价格: ";
    cin>>price;
    cout<<"请输入出版日期(YYYY-MM，如2023-10): ";
    cin>>publishDate;
    
    vector<Book> books = loadFromFile();
    
    for (const auto& book : books) {
        if (book.getISBN() == isbn) {
            setColor(12);
            cout<<"错误：该ISBN已存在！"<<endl;
            setColor(7);
            return;
        }
    }
    
    Book newBook(title, isbn, author, publisher, price, publishDate);
    books.push_back(newBook);
    
    sort(books.begin(), books.end(), compareByAuthorTitle);
    
    saveToFile(books);
    
    setColor(10);
    cout<<"图书添加成功！"<<endl;
    setColor(7);
}

void Book::deleteBook() {
    string isbn;
    cout<<"请输入要删除的图书ISBN: ";
    cin>>isbn;
    
    vector<Book> books = loadFromFile();
    vector<Book> newBooks;
    bool found = false;
    
    for (const auto& book : books) {
        if (book.getISBN() != isbn) {
            newBooks.push_back(book);
        } else {
            found = true;
            if (book.getIsBorrowed()) {
                setColor(12);
                cout<<"错误：该图书已被借出，无法删除！"<<endl;
                setColor(7);
                return;
            }
        }
    }
    
    if (!found) {
        setColor(12);
        cout<<"未找到该ISBN的图书！"<<endl;
        setColor(7);
        return;
    }
    
    saveToFile(newBooks);
    
    setColor(10);
    cout<<"图书删除成功！"<<endl;
    setColor(7);
}

void Book::modifyBook() {
    string isbn;
    cout<<"请输入要修改的图书ISBN: ";
    cin>>isbn;
    
    vector<Book> books = loadFromFile();
    bool found = false;
    
    for (auto& book : books) {
        if (book.getISBN() == isbn) {
            found = true;
            cout<<"当前信息:"<<endl;
            book.display();
            
            cout<<"\n请输入新信息(直接回车跳过修改):"<<endl;
            
            string input;
            cout<<"新题名: ";
            cin.ignore();
            getline(cin, input);
            if (!input.empty()) book.setTitle(input);
            
            cout<<"新作者: ";
            getline(cin, input);
            if (!input.empty()) book.setAuthor(input);
            
            cout<<"新出版社: ";
            getline(cin, input);
            if (!input.empty()) book.setPublisher(input);
            
            cout<<"新价格: ";
            getline(cin, input);
            if (!input.empty()) book.setPrice(stod(input));
            
            cout<<"新出版日期(YYYY-MM): ";
            getline(cin, input);
            if (!input.empty()) book.setPublishDate(input);
            
            break;
        }
    }
    
    if (!found) {
        setColor(12);
        cout<<"未找到该ISBN的图书！"<<endl;
        setColor(7);
        return;
    }
    
    sort(books.begin(), books.end(), compareByAuthorTitle);
    saveToFile(books);
    
    setColor(10);
    cout<<"图书信息修改成功！"<<endl;
    setColor(7);
}

void Book::searchBook() {
    cout<<"\n=== 图书信息查询 ==="<<endl;
    cout<<"\n1. 查看所有图书"<<endl;
    cout<<"2. 按作者查询"<<endl;
    cout<<"3. 按ISBN查询"<<endl;
    cout<<"4. 按书名查询"<<endl;
    cout<<"5. 查看可借阅图书"<<endl;
    cout<<"请选择查询方式: ";
    
    int choice;
    cin >> choice;
    
    vector<Book> books = loadFromFile();
    
    if (books.empty()) {
        cout << "\n图书馆暂无图书！"<< endl;
        return;
    }
    
    system("cls");
    
    if (choice == 1) {
        cout<<"=== 所有图书（按作者分组，按书名排序） ===\n"<<endl;
        
        string currentAuthor = "";
        int bookCount = 0;
        
        for (const auto& book : books) {
            if (book.getAuthor() != currentAuthor) {
                if (currentAuthor != "") cout << endl;
                currentAuthor = book.getAuthor();
                setColor(14);
                cout<<"作者: "<<currentAuthor<<endl;
                setColor(7);
                bookCount = 0;
            }
            
            bookCount++;
            cout<<"  "<<bookCount<<". ";
            book.displaySimple();
            cout<<"     ISBN: "<<book.getISBN()<<endl;
            cout<<"     出版社: "<<book.getPublisher()<<endl;
            cout<<"     价格: "<< fixed<< setprecision(2)<<book.getPrice()<<"元"<<endl;
            cout<<"     借阅次数: "<<book.getBorrowCount()<<endl;
            cout<<"     出版日期: "<<book.getPublishDate()<<endl;
        }
        
        cout<<"\n共 "<<books.size()<<" 本图书"<<endl;
        
    } else if (choice == 2) {
        string author;
        cout<<"请输入作者姓名: ";
        cin>>author;
        
        vector<Book> authorBooks;
        for (const auto& book : books) {
            if (book.getAuthor() == author) {
                authorBooks.push_back(book);
            }
        }
        
        if (authorBooks.empty()) {
            cout<<"未找到该作者的图书！"<<endl;
        } else {
            cout <<"\n作者 "<<author <<" 的图书 ("<<authorBooks.size()<<" 本):\n"<<endl;
            for (int i = 0; i < authorBooks.size(); i++) {
                const auto& book = authorBooks[i];
                cout<<i+1<<". ";
                book.displaySimple();
                cout<<"   ISBN: "<<book.getISBN()<< endl;
                cout<<"   出版社: "<<book.getPublisher()<<endl;
                cout<<"   价格: "<<book.getPrice()<< "元" <<endl;
                cout<<"   借阅次数: "<<book.getBorrowCount()<<endl;
                cout<<"   出版日期: "<<book.getPublishDate()<<endl;
                cout<<endl;
            }
        }
        
    } else if (choice == 3) {
        string isbn;
        cout<<"请输入ISBN: ";
        cin>>isbn;
        
        bool found = false;
        for (const auto& book : books) {
            if (book.getISBN() == isbn) {
                cout<<"\n找到图书:"<<endl;
                book.display();
                found = true;
                break;
            }
        }
        
        if (!found) {
            cout<<"未找到该ISBN的图书！"<<endl;
        }
        
    } else if (choice == 4) {
        string title;
        cout << "请输入书名(或部分关键字): ";
        cin >> title;
        
        vector<Book> titleBooks;
        for (const auto& book : books) {
            if (book.getTitle().find(title) != string::npos) {
                titleBooks.push_back(book);
            }
        }
        
        if (titleBooks.empty()) {
            cout << "未找到相关图书！" << endl;
        } else {
            cout << "\n找到 " << titleBooks.size() << " 本相关图书:\n" << endl;
            for (int i = 0; i < titleBooks.size(); i++) {
                const auto& book = titleBooks[i];
                cout << i+1 << ". ";
                book.displaySimple();
                cout << "   ISBN: " << book.getISBN() << endl;
                cout << "   作者: " << book.getAuthor() << endl;
                cout << "   出版社: " << book.getPublisher() << endl;
                cout << "   价格: " << book.getPrice() << "元" << endl;
                cout << endl;
            }
        }
    } else if (choice == 5) {
        cout << "=== 可借阅图书 ===\n" << endl;
        int availableCount = 0;
        
        for (const auto& book : books) {
            if (!book.getIsBorrowed()) {
                availableCount++;
                cout<< availableCount << ". ";
                book.displaySimple();
                cout<<"   ISBN: "<< book.getISBN() <<endl;
                cout<<"   作者: "<< book.getAuthor()<<endl;
                cout<<"   出版社: "<< book.getPublisher()<<endl;
                cout<<"   价格: "<< book.getPrice() << "元" <<endl;
                cout<<"   借阅次数: "<<book.getBorrowCount()<<endl;
                cout<<endl;
            }
        }
        
        if (availableCount == 0) {
            cout<<"暂无可借阅的图书！"<<endl;
        } else {
            cout<<"共 "<< availableCount<< " 本可借阅图书" <<endl;
        }
    } else {
        cout << "无效选择！" << endl;
    }
}

bool Book::borrowBook(const string& username, const string& isbn) {
    vector<Book> books = loadFromFile();
    bool found = false;
    
    for (auto& book : books) {
        if (book.getISBN() == isbn) {
            found = true;
            
            if (book.getIsBorrowed()) {
                return false; 
            }
            
            book.setIsBorrowed(true);
            book.incrementBorrowCount();
            
            saveToFile(books);
            
            ofstream fout("Data\\balance.txt", ios::app);
            if (fout.is_open()) {
                time_t now = time(0);
                char* dt = ctime(&now);
                string timeStr = dt;
                timeStr.erase(timeStr.find_last_not_of("\n") + 1);
                
                fout << username << " " << isbn << " " << timeStr << endl;
                fout.close();
            }
            
            return true;
        }
    }
    
    return false;
}

bool Book::returnBook(const string& username, const string& isbn) {
    vector<Book> books = loadFromFile();
    bool found = false;
    
    for (auto& book : books) {
        if (book.getISBN() == isbn) {
            found = true;
            
            if (!book.getIsBorrowed()) {
                return false; 
            }
            
            ifstream fin("Data\\balance.txt");
            string user, bookIsbn, date;
            vector<string> userBorrows;
            bool userHasBorrowed = false;
            
            while (fin >> user >> bookIsbn) {
                getline(fin, date); 
                if (user == username && bookIsbn == isbn) {
                    userHasBorrowed = true;
                    ofstream fout("Data\\return.txt", ios::app);
                    if (fout.is_open()) {
                        time_t now = time(0);
                        char* dt = ctime(&now);
                        string returnTimeStr = dt;
                        returnTimeStr.erase(returnTimeStr.find_last_not_of("\n") + 1);
                        
                        fout << username << " " << isbn << " " << date << " " << returnTimeStr << endl;
                        fout.close();
                    }
                } else {
                    userBorrows.push_back(user + " " + bookIsbn + date);
                }
            }
            fin.close();
            
            if (!userHasBorrowed) {
                return false; 
            }
            
            book.setIsBorrowed(false);
            
            saveToFile(books);
            
            ofstream fout("Data\\balance.txt");
            for (const string& record : userBorrows) {
                fout << record << endl;
            }
            fout.close();
            
            return true;
        }
    }
    
    return false; 
}

vector<string> Book::getUserBorrowedBooks(const string& username) {
    vector<string> borrowedBooks;
    ifstream fin("Data\\balance.txt");
    
    if (!fin.is_open()) {
        return borrowedBooks;
    }
    
    string user, isbn, date;
    while (fin >> user >> isbn) {
        getline(fin, date);
        if (user == username) {
            borrowedBooks.push_back(isbn);
        }
    }
    fin.close();
    
    return borrowedBooks;
}

bool Book::isBookAvailable(const string& isbn) {
    vector<Book> books = loadFromFile();
    
    for (const auto& book : books) {
        if (book.getISBN() == isbn) {
            return !book.getIsBorrowed();
        }
    }
    
    return false; 
}

void Book::showBorrowRanking() {
    vector<Book> books = loadFromFile();
    
    if (books.empty()) {
        cout << "暂无图书数据！" << endl;
        return;
    }
    
    sort(books.begin(), books.end(), compareByBorrowCount);
    
    cout << "=== 借阅排行榜（前10名） ===\n"<<endl;
    setColor(14);
    cout << "排名 借阅次数 书名 - 作者"<<endl;
    setColor(7);
    cout << "----------------------------------------" <<endl;
    
    int count = min(10, (int)books.size());
    for (int i = 0; i < count; i++) {
        const auto& book = books[i];
        cout<<setw(2)<< i+1<<". " 
            <<setw(8)<<book.getBorrowCount() << "  "
            <<"《" <<book.getTitle() << "》 - "<<book.getAuthor()<<endl;
    }
}

void Book::showNewBookRanking() {
    vector<Book> books = loadFromFile();
    
    if (books.empty()) {
        cout<<"暂无图书数据！"<<endl;
        return;
    }
    
    sort(books.begin(), books.end(), compareByPublishDate);
    
    cout<<"=== 最新图书排行榜（前10名） ===\n"<<endl;
    setColor(14);
    cout<<"排名 出版日期 书名 - 作者"<<endl;
    setColor(7);
    cout<<"----------------------------------------"<<endl;
    
    int count = min(10, (int)books.size());
    for (int i = 0; i < count; i++) {
        const auto& book = books[i];
        cout<<setw(2)<< i+1 << ". " 
            <<setw(8)<< book.getPublishDate()<<"  "
            <<"《"<<book.getTitle() << "》 - "<<book.getAuthor()<<endl;
    }
}

vector<Book> Book::getRecommendations(const string& username) {
    vector<Book> allBooks = loadFromFile();
    vector<string> userBooks = getUserBorrowedBooks(username);
    
    if (userBooks.empty()) {
        sort(allBooks.begin(), allBooks.end(), compareByBorrowCount);
        vector<Book> recommendations;
        int count = 0;
        for (const auto& book : allBooks) {
            if (!book.getIsBorrowed() && count < 2) {
                recommendations.push_back(book);
                count++;
            }
        }
        return recommendations;
    }
    
    map<string, vector<string>> allUserBorrows;
    ifstream fin("Data\\return.txt");
    string user, isbn, borrowDate, returnDate;
    
    while (fin >> user >> isbn >> borrowDate >> returnDate) {
        allUserBorrows[user].push_back(isbn);
    }
    fin.close();
    
    fin.open("Data\\balance.txt");
    while (fin >> user >> isbn) {
        getline(fin, borrowDate);
        allUserBorrows[user].push_back(isbn);
    }
    fin.close();
    
    string mostSimilarUser;
    int maxOverlap = -1;
    
    for (const auto& entry : allUserBorrows){
        const string& otherUser = entry.first;
        if (otherUser == username) continue; 
        
        const vector<string>& otherBooks = entry.second;
        
        int overlap = 0;
        for (const string& userBook : userBooks){
            if (find(otherBooks.begin(), otherBooks.end(), userBook) != otherBooks.end()){
                overlap++;
            }
        }
        
        if (overlap > maxOverlap && overlap > 0){
            maxOverlap = overlap;
            mostSimilarUser = otherUser;
        }
    }
    
    vector<Book> recommendations;
    
    if (!mostSimilarUser.empty()){
        const vector<string>& similarUserBooks = allUserBorrows[mostSimilarUser];
        
        for (const string& isbn : similarUserBooks){
            if (find(userBooks.begin(), userBooks.end(),isbn)!= userBooks.end()) {
                continue;
            }
            
            for (const Book& book : allBooks){
                if (book.getISBN()==isbn&& !book.getIsBorrowed()){
                    recommendations.push_back(book);
                    if (recommendations.size()>=2) break;
                }
            }
            
            if (recommendations.size()>=2) break;
        }
    }
    
    if (recommendations.size() < 2){
        sort(allBooks.begin(),allBooks.end(),compareByBorrowCount);
        for (const Book& book : allBooks){
            if (!book.getIsBorrowed()){
                bool alreadyInList=false;
                for (const Book& rec:recommendations) {
                    if (rec.getISBN()==book.getISBN()) {
                        alreadyInList=true;
                        break;
                    }
                }
                
                if (!alreadyInList){
                    recommendations.push_back(book);
                    if (recommendations.size() >= 2) break;
                }
            }
        }
    }
    
    return recommendations;
}

void Book::manageBooks(){
    int choice;
    do{
        system("cls");
        cout<<"=== 图书信息管理 ==="<<endl;
        cout<<"\n请选择操作:\n"<<endl;
        cout<<"1. 增加书籍信息"<<endl;
        cout<<"2. 删除书籍信息"<<endl;
        cout<<"3. 修改书籍信息"<<endl;
        cout<<"4. 查询书籍信息"<<endl;
        cout<<"5. 查看借阅排行榜"<<endl;
        cout<<"6. 查看最新图书榜"<<endl;
        cout<<"0. 返回上级菜单\n"<<endl;
        cout<<"请选择: ";
        cin>>choice;
        
        switch(choice) {
            case 1:
                system("cls");
                addBook();
                cout<<"\n按任意键继续..."<<endl;
                cin.ignore();
                cin.get();
                break;
                
            case 2:
                system("cls");
                deleteBook();
                cout<<"\n按任意键继续..."<<endl;
                cin.ignore();
                cin.get();
                break;
                
            case 3:
                system("cls");
                modifyBook();
                cout<<"\n按任意键继续..."<<endl;
                cin.ignore();
                cin.get();
                break;
                
            case 4:
                system("cls");
                searchBook();
                cout<<"\n按任意键继续..."<<endl;
                cin.ignore();
                cin.get();
                break;
                
            case 5:
                system("cls");
                showBorrowRanking();
                cout<<"\n按任意键继续..."<<endl;
                cin.ignore();
                cin.get();
                break;
                
            case 6:
                system("cls");
                showNewBookRanking();
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
    }while(choice != 0);
}
