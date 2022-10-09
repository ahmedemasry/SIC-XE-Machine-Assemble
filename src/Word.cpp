#include <fstream>
#include <map>
#include<vector>
#include <string>
#include <regex>
#include <locale>


class Word : public Directive{

    public:
        int lc;
        void performPass1(Pass1Core *assem , struct statement *codeLine){

            assem.locationCounter += lc;
        }


        // return true if operands are valid
        bool validateOperands(vector<pair<string , bool>> operands){

            bool match = true;
            lc = 0;
            for(int i = 0; i < operands.size(); i++){
                string str = operands[i].first;


                //one or more DECIMAL digits
                regex rxDec("[:d:]{1,7}", regex_constants::icase);

                //regex x'2 digits HEXA'
                regex rxHex("x'[:xdigit:]{2,6}'", regex_constants::icase);


                bool matchHex = regex_match(str.c_str(),rxHex);
                bool matchDec = regex_match(str.c_str(),rxDec);

                if(matchDec){
                    //Get the operand Value (String to int)
                    int operandVal = std::stoi(str);
                    //Check that it's between -2^23 & 2^23 (3 Bytes)
                    if(operandVal >= 8388608){
                        match = false;
                    }else if(operandVal < -8388608){
                        match = false;
                    }
                    lc += 3;
                }else if(matchHex){
                    lc += 3;
                }else{
                    //if there's no match then return false
                    match = false;
                }
            }
            return match;
        }

};
