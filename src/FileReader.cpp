#include "FileReader.h"
#include "statement.h"
#include "instruction.h"
#include <fstream>
#include <map>
#include<vector>
#include <string>
#include <regex>
#include <locale>
#include <cstdlib>

using namespace std;


FileReader::FileReader()
{
    //ctor
}
map <string , struct instruction> FileReader::readOperations(string path)
{
    ifstream f(path.c_str());
    map<string, instruction> appendix;
    string mnemonic;
    struct instruction inst;
    string hex;
    while(f >> mnemonic >> inst.format >> hex)
    {
        inst.opCode = strtoul(hex.c_str(), 0, 16);
        regex re("(.+)<.+,.+>");
        smatch m;
        if(regex_search(mnemonic, m, re))
        {
            mnemonic = m[1].str();
            inst.numOfOperatands = 2;
        }
        appendix[mnemonic] = inst;
    }
    f.close();
    return appendix;
}

map<string ,int> FileReader::readDirectives(string path)
{
    ifstream f(path.c_str());
    map<string,int> directives;
    string directive;
    int i;
    while(f >> directive >> i)
    {
        directives[directive] = i;
    }
    f.close();
    return directives;
}

vector <struct statement> FileReader::readSourceCode(string path,
                                                     map <string , instruction> operations,
                                                     map <string , int> directives)
{
    regex pattern[5] = {regex("^[[:s:]]*([^[:s:]]+)[[:s:]]+(\\+?[[:w:]]+)[[:s:]]+([^[:s:]]+)[[:s:]]*$"),
    regex("^[[:s:]]*(\\+?[[:w:]]+)[[:s:]]+([^[:s:]]+)[[:s:]]*$"),
    regex("^[[:s:]]*([^[:s:]]+)[[:s:]]+(\\+?[[:w:]]+)[[:s:]]+$"),
    regex("^[[:s:]]*(\\+?[[:w:]]+)[[:s:]]*$"),regex("^\\..*")};

    vector<statement> code;
    ifstream f(path.c_str());
    string line;
    string str;
    while (getline(f, line))
    {
        line += " ";
        locale loc;
        for (string::size_type i=0; i<line.length(); ++i)
                toupper(line[i],loc);
        smatch m;
        statement s;
        int x = 1;
        bool visit = false;
        if(regex_search(line, m, pattern[0]))
        {
            goto case1;
        }
        else if(regex_search(line, m, pattern[1]))
        {
            goto case2;
        }
        else if (regex_search(line, m, pattern[2]))
        {
            goto case2;
        }
        else if (regex_search(line, m, pattern[3]))
        {
            goto case2;
        }
        else if (regex_search(line, m, pattern[4]))
        {
            s.label = m[0].str();
            s.notValid = true;
            goto endcase;
        }
        else
        {
            s.label = line;
            s.notValid = true;
            s.error = "******unrecognized operation code******";
            goto endcase;
        }
        case1:
            s.label = m[x++].str();
            visit = true;
        case2:
            str = m[x].str();
            if (str[0] == '+')
            {
                s.extendable = true;
                str = str.substr(1,str.size());
            }
            if (operations.find(str) != operations.end())
            {

                s.inst = str;
                x++;
            }
            else if (directives.find(m[x].str()) != directives.end())
            {
                int i = directives[m[x].str()];
                s.inst = m[x++].str();
                if(i == -1 )
                {
                    s.error = "******pass 1 not supported this directive******";
                    s.warnFlag = true;
                }
            }
            else
            {
                if (!visit) goto case1;
            }
            s.operands = m[x++].str();
        endcase:
            code.push_back(s);
    }
    f.close();
    return code;
}
