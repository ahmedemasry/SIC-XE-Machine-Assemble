#ifndef FILEWRITER_H
#define FILEWRITER_H
#include "Statement.h"
#include<vector>
#include <string>

class FileWriter
{
    public:
        FileWriter();
        void writePass1Listing(std::vector<struct statement> lines , std::string path);
    private:
        std::string int_to_hex( int i );
};

#endif // FILEWRITER_H
