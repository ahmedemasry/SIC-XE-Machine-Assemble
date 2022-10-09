#ifndef DIRECTIVE_H
#define DIRECTIVE_H
#include "Pass1Core.h"


class Directive
{
    public:
    virtual void performPass1(Pass1Core *assem , struct statement *codeLine) = 0;
    // return true if operands are valid
    virtual bool validateOperands(std::vector<std::pair<std::string , bool>> operands) = 0;
};

#endif // DIRECTIVE_H
