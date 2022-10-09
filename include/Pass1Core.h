#ifndef PASS1CORE_H
#define PASS1CORE_H
#include <map>
#include <vector>
#include "Statement.h"
#include <Instruction.h>
#include "FileReader.h"

struct Statement;

class Pass1Core
{
    public:
    Pass1Core(std::map <std::string , struct instruction> *opTable , std::map <std::string ,int> *directivesTable ,
              std::map <std::string ,int> *registersTable , std::map <std::string ,int> *symbolTable);
    std::vector <struct statement> * executePass1(std::string path);
    std::map <std::string , struct instruction> *opTable;
    std::map <std::string ,int> *directivesTable;
    std::map <std::string ,int> *registersTable;
    std::map <std::string ,int> *symbolTable;
    std::vector <struct statement> sourceStatements;
    int locationCounter = 0;
    protected:

    private:
        FileReader reader;
        bool validate(struct statement *codeLine , std::vector <std::pair <std::string , bool>> operands);
        bool validateRoperand(std::pair<std::string , bool> oper);
        bool validateMoperand(std::pair<std::string , bool> oper);
        bool checkWarning(struct statement *codeLine);
};

#endif // PASS1CORE_H
