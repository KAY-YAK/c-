#include "Megaint.h"
#include "Megacalc.h"
#include <iostream>
#include <string>
#include <regex>
using namespace std;

Megacalc::~Megacalc(){
}


Megacalc::Megacalc(){
}


void Megacalc::factorial(Megaint& mega_int){
  Megaint zero(0);
  if(mega_int < zero){
    cout << "Factorial of negative number is not defined" << endl;
    return;
  }

  if(mega_int == zero){
    cout << "+0! = +1" << endl;
    return;
  }


  Megaint count(1);
  Megaint fact(1);
  for (; count <= mega_int; count++){
    fact = fact * count;
    cout << count << "! = " <<fact<<'\n';
  }
}


/*
If n is even, divide it by 2 to give n = n/2
If n is odd, multiply it by 3 and add 1 to give n = 3n + 1.
*/
void Megacalc::hailstone(Megaint mega_int){
  Megaint copy = mega_int;
  Megaint zero;
  Megaint even(2);
  Megaint three(3);
  Megaint one(1);
  Megaint count;

  if(mega_int <= zero){
    cout << "Hailstone sequence of negative number or 0 is not defined" << endl;
    return;
  }

  while(true){
    cout << mega_int << endl;
    count++;
    if(mega_int == one) break;

    if(mega_int % even == zero ){
      mega_int = mega_int / even;
    }else{
      mega_int = (mega_int * three) + 1;
    }
  }

  cout <<"\nlength of hailstone(" << copy << ") sequence: " << count << endl;
}

void Megacalc::run(){
  Megaint accumulator;

  cout << "Welcome to Mega-calculator" << endl;
  cout << "==========================" << endl;
  cout << "\n";



  string input;

  while(true){
    cout << "Accumulator: " << accumulator <<endl;
    cout << "Enter Input: ";
    getline(cin, input);
    //Remove white spaces
    input = regex_replace(input, regex(" "), "");

    //cout << input << "!!!" <<endl;

    //IF EMPTY
    if(input.empty()){
      cout << "INVALID INPUT" <<endl;
      cout << "\n";
      continue;
    }

    //IF NOT LEGIT COMMAND
    if(!regex_match(input, regex("^([\\+-/%\\*=][\\+-]{0,1}[0-9]+)|[cnfhq]"))){
      cout << "INVALID INPUT" <<endl;
      cout << "\n";
      continue;
    }

    //Command +
    if(input[0] == '+'){
      Megaint mega_int(input.substr(1,input.length() - 1));
      accumulator = accumulator + mega_int;
    }

    //Command -
    if(input[0] == '-'){
      Megaint mega_int(input.substr(1,input.length() - 1));
      accumulator = accumulator - mega_int;
    }

    //Command / NOTE: Try catch because division by 0
    if(input[0] == '/'){
      try{
        Megaint mega_int(input.substr(1,input.length() - 1));
        accumulator = accumulator / mega_int;
      }catch(char const* msg){
        cout << msg << endl;
        cout << endl;
        continue;
      }
    }

    //Command % NOTE: Try catch because division by 0
    if(input[0] == '%'){
      try{
        Megaint mega_int(input.substr(1,input.length() - 1));
        accumulator = accumulator % mega_int;
      }catch(char const* msg){
        cout << msg << endl;
        cout << endl;
        continue;
      }
    }

    //Command *
    if(input[0] == '*'){
      Megaint mega_int(input.substr(1,input.length() - 1));
      accumulator = accumulator * mega_int;
    }

    //Command =
    if(input[0] == '='){
      Megaint mega_int(input.substr(1,input.length() - 1));
      accumulator = mega_int;
    }

    //Command c
    if(input == "c"){
      Megaint zero;
      accumulator = zero;
    }

    // NEED TO CHECK
    //Command n
    if(input == "n"){
      accumulator  = -accumulator;
    }

    //Command f
    if(input == "f"){
      this->factorial(accumulator);
    }

    //Command h
    if(input == "h"){
      this->hailstone(accumulator);
    }

    //Command q
    if(input == "q"){
      cout << "QUITTING MEGACALC!!.....BYE" << endl;
      return;
    }

    cout << "\n";

  }



}
