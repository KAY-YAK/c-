#ifndef LED_H
#define LED_H
#include<iostream>
#include<list>
#include<cstring>
#include<string>
#include "Command.h"
using namespace std;

class Led{
  private:
    string filename;
    list <string> buffer;             //The buffer

    int curr_line;
    int last_line;
    bool write;

    void execute(const Command&);           //This will execute Command by retrieving symbol from command object and call respective command_*()
    void command_a(int);
    void command_i(int);
    void command_r(int, int);
    void command_p(int, int);
    void command_n(int, int);
    void command_c(int, int);
    void command_u(int, int);
    void command_d(int, int);
    void command_w();
    void command_equal_symbol();
    void command_q();

  public:
    ~Led();
    Led();                            //Default Constructor
    Led(const string&);               //Overloading Constructor to pass file name from main
    void run();

};


#endif
