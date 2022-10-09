#include <fstream>
#include <map>
#include<vector>
#include <string>
#include <regex>
#include <locale>


class End : public Directive{

    public:
        int lc;
        void performPass1(Pass1Core *assem , struct statement *codeLine){

        }


        // return true if operands are valid
        bool validateOperands(vector<pair<string , bool>> operands){

            if(operands.size() > 1){
                return false;
            }
            string str = operands[0].first;

             //regex ALPHA
            regex rxChar("[:w:]+", regex_constants::icase);

            //Match Label
            bool match = regex_match(str.c_str(),rxChar);

            return match;
        }

};
