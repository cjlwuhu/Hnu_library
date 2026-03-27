#ifndef BOOKSTATISTICS_H
#define BOOKSTATISTICS_H

#include "Book.h"
#include <string>
#include <vector>

using namespace std;

class BookStatistics {
private:
    BookStatistics() {}  // æ≤Ã¨¿‡
    
public:
    
    static vector<string> getTopAuthors(int limit = 10);
    static vector<string> getTopPublishers(int limit = 10);
};

#endif
