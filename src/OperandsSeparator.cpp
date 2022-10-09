#include "OperandsSeparator.h"
#include <string>
#include <regex>
#include <vector>
#include "Statement.h"
#include <boost/algorithm/string.hpp>

std::vector<std::pair <std::string , bool>> OperandsSeparator::sperateOprands(struct statement s)
{
    std::vector< std::pair < std::string , bool>> oprands;
    std::vector<std::string> operandsWithX;
    std::string str (s.operands);
    boost::erase_all(str, " ");
    boost::erase_all(str, "\t");
    boost::split(operandsWithX,str, boost::is_any_of(","));
    for(unsigned int i = 0 ; i < operandsWithX.size() ; i++)
    {
        pair <string , bool> p;
        string temp = operandsWithX.at(i);
        if(temp.compare("x") != 0 && temp.compare("X") != 0)
        {
            if( i == operandsWithX.size()  - 1)
            {
                p = make_pair(temp,false);
                oprands.push_back(p);
            }
            else if(operandsWithX.at(i+1).compare("x") != 0 && operandsWithX.at(i+1).compare("X") != 0)
            {
                p = make_pair(temp,false);
                oprands.push_back(p);
            }
            else
            {
                p = make_pair(temp,true);
                oprands.push_back(p);
            }
        }
    }
    return oprands;
}
