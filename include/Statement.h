#ifndef STATEMENT_H
#define STATEMENT_H
#include<string>


struct statement{
    //IMPORTANT you Should capitalize all characters read from source code and instrucation file

    //Note if you have comment line which starts "." put all line in label string and set all paremetars with null
    /*Eample
        LDA                            TEN   ,   x
        label = NULL
        Inst  = LDA
        operads =  TEN,X
        notValid = false
        error  = null
        warnFlag = false
        loctcunt = 0
    */
    std::string label;
    std::string inst;
    //you should put in operands all operands you have without any space and comma sperated
    // like 10,7,6,9
    //note it can be more than two then put all string you have in operands
    /*note only line comment is allowed which start "." so don't take care about comment in instruction
        line because it is not allowed*/
    std::string operands;
    // shoud make it true when you have error
    /*Example
        LDA    LDA   #3
        you should make sure that label not in map of instruction
        if it is you should make notVaild flag true
        and write error <Unallowed label>
    */
    bool notValid = false;
    std::string error;
    bool warnFlag = false;
    bool extendable = false;
    //location counter used in write not in read
    int loctCount;
};


#endif // STATEMENT_H
