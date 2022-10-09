#include <fstream>
#include <map>
#include<vector>
#include <string>
#include <regex>
#include <locale>
#include "Directive.h"


class Byte : public Directive {

    public:
        int lc;
        void performPass1(Pass1Core *assem , struct statement *codeLine){

            assem.locationCounter += lc;
        }


        // return true if operands are valid
        bool validateOperands(std::vector<std::pair<std::string , bool>> operands){

            bool match = true;
            lc = 0;
            for(int i = 0; i < operands.size(); i++){
                string str = operands[i].first;


                //regex x'2 digits HEXA'
                regex rxHex("x'[:xdigit:]{2}'", regex_constants::icase);

                //regex c'ALPHA'
                regex rxChar("c'[:w:]+'", regex_constants::icase);

                bool matchHex = regex_match(str.c_str(),rxHex);
                bool matchChar = regex_match(str.c_str(),rxChar);

                if(matchChar){
                    //we subtract 3 to match the number of actual bytes exclusive c''
                    lc += str.length-3;
                }else if(matchHex){
                    //we subtract 3 to match the number of actual bytes exclusive x''
                    lc += (str.length-3)/2;
                }else{
                    match = false;
                }
            }
            return match;
        }

};
