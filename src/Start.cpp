#include <fstream>
#include <map>
#include<vector>
#include <string>
#include <regex>
#include <locale>


class Start : public Directive{

    public:
        int lc;
        void performPass1(Pass1Core *assem , struct statement *codeLine){

            assem.locationCounter = lc;
        }


        // return true if operands are valid
        bool validateOperands(vector<pair<string , bool>> operands){

            if(operands.size() > 1){
                return false;
            }
            string str = operands[0].first;

            //one or more HEXA digits
            regex rxHex("[:xdigit:]{1,6}", regex_constants::icase);

            bool match = regex_match(str.c_str(),rxHex);

            if(match){
                lc = std::stoi (str);
            }

            return match;
        }

};
