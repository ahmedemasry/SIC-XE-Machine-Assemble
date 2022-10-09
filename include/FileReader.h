#ifndef FILEREADER_H
#define FILEREADER_H
#include <map>
#include<vector>
#include <string>



class FileReader
{
    public:
        FileReader();
        std::map <std::string , struct instruction> readOperations(std::string path);
        std::map <std::string ,int> readDirectives(std::string path);
        std::vector <struct statement> readSourceCode(std::string path,
                                                      std::map <std::string , struct instruction>,
                                                      std::map <std::string, int>);
    private:
};

#endif // FILEREADER_H
