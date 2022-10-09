#include <fstream>
#include <map>
#include<vector>
#include <string>
#include <regex>
#include <locale>

class Resw : public Directive{
    public:
        int lc;
        void performPass1(Pass1Core *assem , struct statement *codeLine){


            assem.locationCounter += lc;
        }


        // return true if operands are valid
        bool validateOperands(vector<pair<string , bool>> operands){

            //Assert that there's only one Operand
            if(operands.size() > 1){
                return false;
            }

            string str = operands[0].first;

            //one or more DECIMAL digits
            regex rxDec("[:d:]{1,7}", regex_constants::icase);

            bool match = regex_match(str.c_str(),rxDec);

            if(match){
                //convert string to integer and multiply by 3 (Word)
                lc = std::stoi (str);
                lc *= 3;
            }
            return match;
        }

    };
