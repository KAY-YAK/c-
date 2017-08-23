#ifndef COMMAND_H
#define COMMAND_H
#include<iostream>
#include<string>
using namespace std;

class Command{
public:
    int line_addr_1;
    int line_addr_2;
    string message;
    bool flag;                                          // This handles erreronious commands
    bool zero;                                          // This restricts 0 as line address as required by commands
    bool line2_lt_line1;                                // This restricts line_addr_1 to be greater than line_addr_2
    //bool gt_last;                                       // This restricts line_addr_2 to be greater than last_line
    string symbol;                                      // This needs to be accessed by the object so public

    ~Command();
    Command();
    
    void parse(string&, int&, int&);                 //This sets the value of symbol, flag and message directly after parsing+
    bool extract(string&, int&, int&);

};


#endif
