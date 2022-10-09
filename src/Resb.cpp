
class Resb : public Directive{

    public:
        int lc;
        void performPass1(Pass1Core *assem , struct statement *codeLine){
            //string label = codeLine.label;
            //string label = (*codeLine).label;
            //std::map <std::string ,int> *symtab = assem.symbolTable;


            //adding the label as key and the address of LCCTR as the value
            //(*symtab)[label] = assem.locationCounter;

            assem.locationCounter += lc;
        }


        // return true if operands are valid
        bool validateOperands(vector<pair<string , bool>> operands){
            //vector<pair<string , bool>>::iterator itr = operands.begin();
            //string str = *itr.first;

            //Assert that there's only one Operand
            if(operands.size() > 1){
                return false;
            }

            string str = operands[0].first;

            //one or more DECIMAL digits
            regex rxDec("[:d:]{1,7}", regex_constants::icase);

            bool match = regex_match(str.c_str(),rxDec);

            if(match){
                //convert string to integer
                lc = std::stoi (str);
            }
            return match;
        }

};
