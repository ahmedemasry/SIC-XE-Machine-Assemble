#ifndef INSTRUCTION_H
#define INSTRUCTION_H


struct instruction{
    // # of operataors can be taken like in COMPR r1,r2 it is 2 operands
    // don't  take care about indexed operands like LDA label,x it is one openad not two
    //beacuse a lot of instruction can be indexed
    int numOfOperatands;
    /*
    >>remark format can take 0 , 1 , 2 , 3
    >>3 for 3/4 formats because all fromat 3
        instructions implies thats are also format 4
    >> o format for assembler directives */
    int format;
    //Note that opCode must store in decimal.
    //it can be done with dummy bulid in funcation in c++
    int opCode;
};


#endif // INSTRUCTION_H
