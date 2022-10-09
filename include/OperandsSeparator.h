#ifndef OPERANDSSEPARATOR_H
#define OPERANDSSEPARATOR_H
#include <string>
#include <regex>
#include <vector>
#include "Statement.h"


class OperandsSeparator
{
    public:
        std::vector<std::pair <std::string , bool>> sperateOprands(struct statement s);

    protected:

    private:
};

#endif // OPERANDSSEPARATOR_H
