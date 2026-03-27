#ifndef BOOK_H
#define BOOK_H

//图书管理系统 

#include <string>
#include <vector>
#include <ctime>
using namespace std;

class Book {
private:
    string title;       // 题名
    string isbn;        // ISBN/ISSN
    string author;      // 作者
    string publisher;   // 出版社
    double price;           // 价格
    int borrowCount;        // 借阅次数
    string publishDate; // 出版日期 (格式: YYYY-MM)
    bool isBorrowed;        // 是否被借出

public:
    Book();
    Book(const string& title, const string& isbn, 
         const string& author, const string& publisher, 
         double price, const string& publishDate = "", int borrowCount = 0, bool isBorrowed = false);
    
    
    //得到基本信息 
    string getTitle() const; 
    string getISBN() const;
    string getAuthor() const;
    string getPublisher() const;
    double getPrice() const;
    int getBorrowCount() const;
    string getPublishDate() const;
    bool getIsBorrowed() const;
    
    //设置基本信息 
    void setTitle(const string& title);
    void setISBN(const string& isbn);
    void setAuthor(const std::string& author);
    void setPublisher(const string& publisher);
    void setPrice(double price);
    void setBorrowCount(int count);
    void setPublishDate(const string& date);
    void setIsBorrowed(bool borrowed);
    
    void incrementBorrowCount();//增加借书数目 
    
    //展示书信息 
    void display() const;
    void displaySimple() const;//是否借出 
    
    static void addBook();   //添加新图书 
    static void deleteBook();  //删除图书 
    static void modifyBook();   //修改图书 
    static void searchBook();   //查询图书 
    static void manageBooks();  //管理图书菜单 
    
    static bool borrowBook(const string& username, const string& isbn);
    static bool returnBook(const std::string& username, const string& isbn);
    static vector<string> getUserBorrowedBooks(const string& username);
    static bool isBookAvailable(const string& isbn);
    
    static void showBorrowRanking();   //根据借阅次数排序 
    static void showNewBookRanking();  //根据图书出版时间排序 
    
    static vector<Book> getRecommendations(const string& username); //推荐系统，先获取用户借去过的图书，然后读取所有用户借过的图书，分析和用户借过相似度最高的用户，然后推荐两本书 
    
    static vector<Book> loadFromFile();  //从txt中读取所有图书信息 
    static void saveToFile(const vector<Book>& books);  //保存图书信息 
    
    static bool compareByAuthorTitle(const Book& a, const Book& b);   //根据作者标题的cmp排序 
    static bool compareByBorrowCount(const Book& a, const Book& b);   //根据借阅次数的cmp 
    static bool compareByPublishDate(const Book& a, const Book& b);   //根据出版时间的cmp 
};

#endif 
#ifndef BOOK_H
#define BOOK_H

class BorrowRecord
{
	public:
	protected:
};

#endif
