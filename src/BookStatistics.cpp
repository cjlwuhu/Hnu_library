#include "../include/BookStatistics.h"
#include <fstream>
#include <map>
#include <algorithm>
#include <windows.h>
#include "../include/Account.h"

using namespace std;

vector<string> BookStatistics::getTopAuthors(int limit) {
    vector<Book> books = Book::loadFromFile();
    map<string, int> authorBorrowCount;
    
    for (const auto& book : books) {
        authorBorrowCount[book.getAuthor()] += book.getBorrowCount();
    }
    
    vector<pair<string, int>> authorList;
    for (const auto& entry : authorBorrowCount) {
        authorList.push_back(entry);
    }
    
    sort(authorList.begin(), authorList.end(),
         [](const pair<string, int>& a, const pair<string, int>& b) {
             return a.second > b.second;
         });
    
    vector<string> topAuthors;
    for (int i = 0; i < min(limit, (int)authorList.size()); i++) {
        topAuthors.push_back(authorList[i].first);
    }
    
    return topAuthors;
}

vector<string> BookStatistics::getTopPublishers(int limit) {
    vector<Book> books = Book::loadFromFile();
    map<string, int> publisherBookCount;
    
    for (const auto& book : books) {
        publisherBookCount[book.getPublisher()]++;
    }
    
    vector<pair<string, int>> publisherList;
    for (const auto& entry : publisherBookCount) {
        publisherList.push_back(entry);
    }
    
    sort(publisherList.begin(), publisherList.end(),
         [](const pair<string, int>& a, const pair<string, int>& b) {
             return a.second > b.second;
         });
    
    vector<string> topPublishers;
    for (int i = 0; i < min(limit, (int)publisherList.size()); i++) {
        topPublishers.push_back(publisherList[i].first);
    }
    
    return topPublishers;
}

