#include "Pass1Core.h"

Pass1Core::Pass1Core(std::map <std::string, struct instruction> *opTable, std::map <std::string,int> *directivesTable,
          std::map <std::string,int> *registersTable, std::map <std::string,int> *symbolTable)
{
    this->opTable = opTable;
    this->directivesTable = directivesTable;
    this->registersTable = registersTable;
    this->symbolTable = symbolTable;
}

std::vector <struct statement> * Pass1Core::executePass1(std::string path)
{
    sourceStatements = reader.readSourceCode(path, *opTable, *directivesTable);
    std::vector <struct statement>::iterator it = sourceStatements.begin();
    while(it != sourceStatements.end())
    {
        //core of each instruction
        if(!(*it).notValid && (*it).label != "" && (*it).inst == "" && (*it).operand == "" && (*it).label.at(0) == '.'){
            it++;
            continue;
        }
        // parse operands
        std::vector<std::pair<std::string, bool>> operands;
        if(!(*it).notValid){
            validate(it , operands);
        }
        if(!(*it).notValid){
            checkWarning(it);
        }
        if(!(*it).notValid && (*it).label != ""){
            (*symbolTable).insert((*it).label , locationCounter);
        }
        if((*opTable).count((*it).inst)){
            locationCounter += ((*opTable).find((*it).inst) -> second).format;
            if((*it).extendable){
                locationCounter += 1;
            }
        }
        if((*directivesTable).count((*it).inst)){
            // reflect the effect of the directive in pass 1

        }
        it++;
    }
}

bool determineError(struct statement *codeLine, std::string error)
{
    (*codeLine).notValid = true;
    (*codeLine).error = error;
    return false;
}

bool Pass1Core::validateRoperand(std::pair<std::string, bool> oper)
{
    if(!((*registersTable).count(oper.first)))
    {
        return false;
    }
    if(oper.second)
    {
        return false;
    }
    return true;
}

bool isHex(std::string str)
{
    std::string str2;
    char c = '0';
    for(int counter = 0; counter < 10; counter ++)
    {
        str2.append(1, c + counter);
    }
    c = 'a';
    for(int counter = 0; counter < 6; counter ++)
    {
        str2.append(1, c + counter);
    }
    c = 'A';
    for(int counter = 0; counter < 6; counter ++)
    {
        str2.append(1, c + counter);
    }
    return str.find_first_not_of(str2) == std::string::npos;
}

bool Pass1Core::validateMoperand(std::pair<std::string, bool> oper)
{
    if(oper.first.at(0) == '#' || oper.first.at(0) == '@')
    {
        if(oper.second)
        {
            return false;
        }
        oper.first.erase(0, 1);
    }
    if((*opTable).count(oper.first) != 0)
    {
        return false;
    }
    if((*directivesTable).count(oper.first) != 0)
    {
        return false;
    }
    if((*registersTable).count(oper.first) != 0)
    {
        return false;
    }
    if(isdigit(oper.first.at(0)))
    {
        if(oper.first.at(0) == '0')
        {
            return isHex(oper.first);
        }
        else
        {
            return oper.first.find_first_not_of("0123456789") == std::string::npos;
        }
    }
    if(isalpha(oper.first.at(0)))
    {
        return true;
    }
    return false;
}

bool Pass1Core::validate(struct statement *codeLine, std::vector<std::pair<std::string, bool>> operands)
{
    if((*codeLine).label != "")
    {
        if((*opTable).count((*codeLine).label) != 0)
        {
            return determineError(codeLine, "the label can't be an assembly instruction!");
        }
        if((*symbolTable).count((*codeLine).label) != 0)
        {
            return determineError(codeLine, "the label is repeated!");
        }
        if((*directivesTable).count((*codeLine).label) != 0)
        {
            return determineError(codeLine, "the label can't be an assembler directive!");
        }
        if((*registersTable).count((*codeLine).label) != 0)
        {
            return determineError(codeLine, "the label can't be an assembly register name!");
        }
        if(!isalpha((*codeLine).label.at(0)))
        {
            return determineError(codeLine, "the label can't begin with a non alphabetical character!");
        }
    }
    if((*codeLine).inst == "")
    {
        return determineError(codeLine, "no instruction in the line!");
    }
    if(!((*opTable).count((*codeLine).inst)) && !((*directivesTable).count((*codeLine).inst)))
    {
        return determineError(codeLine, "the instruction must be an assembly operation or an assembler directive!");
    }
    if(((*opTable).find((*codeLine).inst) -> second).numOfOperatands != operands.size())
    {
        return determineError(codeLine, "the number of operands is not the required for the instruction!");
    }
    std::vector<std::pair<std::string, bool>>::iterator it = operands.begin();
    for(int counter = 0; counter < ((*opTable).find((*codeLine).inst) -> second).numOfOperatands; counter ++)
    {
        bool vali;
        if((*opTable).count((*codeLine).inst) && ((*opTable).find((*codeLine).inst) -> second).format == 2)
        {
            vali = validateRoperand(*it);
        }
        if((*opTable).count((*codeLine).inst) && ((*opTable).find((*codeLine).inst) -> second).format == 3)
        {
            vali = validateMoperand(*it);
        }
        else
        {
            // directive checks
        }
        if(!vali)
        {
            return determineError(codeLine, "invalid operand format!");
        }
        it ++;
    }
    return true;
}

bool determineWarning(struct statement *codeLine, std::string warning)
{
    (*codeLine).warnFlag = true;
    (*codeLine).error = warning;
    return false;
}

bool Pass1Core::checkWarning(struct statement *codeLine)
{
    if((*directivesTable).count((*codeLine).inst))
    {
        if(((*directivesTable).find((*codeLine).inst) -> second) == -1)
        {
            return determineWarning(codeLine, "un handeled directive!");
        }
    }
    return true;
}


