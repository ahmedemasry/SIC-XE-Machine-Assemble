#include "FileWriter.h"
#include "Statement.h"
#include<vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

FileWriter::FileWriter()
{
    //ctor
}


void FileWriter::writePass1Listing(vector<struct statement> lines , string path)
{
    ofstream f(path.c_str());
    int maxLabel = 0;
    for (vector<struct statement>::iterator it = lines.begin(); it != lines.end(); ++it)
    {
        if ((*it).label.size() > maxLabel && (*it).label[0] != '.')
            maxLabel = (*it).label.size();
    }
    string space = "    ";
    int labelStart = 6 + space.size(); //6 is length of LOCCTR
    int operatorStart = labelStart + space.size() + maxLabel;
    int operandStart = operatorStart + space.size() + 5; //5 is length of instruction
    for (vector<statement>::iterator it = lines.begin(); it != lines.end(); ++it)
    {
        string line  = "";
        line += int_to_hex( (*it).loctCount );
        line += space;
        line += (*it).label;
        if ((*it).label[0] == '.')
        {
                f << line << endl;
                continue;
        }
        for (int i = line.size() ; i != operatorStart - 1 ; i++)
            line += " ";
        if ((*it).extendable)
            line += "+";
        else
            line += " ";
        line += (*it).inst;
        for (int i = line.size() ; i != operandStart ; i++)
            line += " ";
        line += (*it).operands;
        f << line << endl;
        if ((*it).warnFlag || (*it).notValid)
            f << (*it).error << endl;
    }
    f.close();
}

string FileWriter::int_to_hex( int i )
{
      stringstream stream;
      stream << uppercase  << setfill ('0') << setw(6)
             << hex << i;
      return stream.str();
}
