#include "Command.h"
#include<iostream>
#include<cstring>
#include<string>
#include<locale>
#include<regex>
using namespace std;


Command::~Command(){
}

Command::Command(){
  //this->symbol = 'q';
  this->message = "";
  this->zero = true;
  this->flag = true;
  this->line2_lt_line1 = true;
  //this->gt_last = true;
  this->symbol ="";
}

void Command::parse(string& command_line, int& current_line, int& last_line){
  this->symbol = "";
  this->message = "";
  this->zero = true;
  this->flag = true;
  this->line2_lt_line1 = true;
  //this->gt_last = true;
  if (regex_match(command_line, regex("([0-9]*|[\\.\\$]?)[,]{0,1}([0-9]*|[\\.\\$]?)[airpncudw=q]{0,1}"))){
    //if(regex_match(command_line,regex("([0-9]+|[\\.$])([0-9]+|[\\.$])[airpncudw=q]{0,1}")) || regex_match(command_line,regex(",{1}[airpncudw=q]{0,1}"))){
    if(regex_match(command_line,regex("([0-9]+|[\\.\\$])([0-9]+|[\\.\\$])[airpncudw=q]{0,1}")) && !regex_match(command_line,regex("[0-9]+[airpncudw=]{0,1}"))){
      string message = command_line + ": Command not found";
      this->flag = false;
      this->message = message;
      return;
    }else{
      //Now split and find command

      locale loc;

      //Handle when there is no command at the end
      if(isdigit(command_line.back(),loc) || command_line.back() == '.' || command_line.back() == ',' || command_line.back() == '$'){
        // if(command_line.back() == '.' || command_line.back() == ',' || command_line.back() == '$'){
        //   command_line.pop_back();
        // }
        this->zero = this->extract(command_line, current_line, last_line);
        this->symbol ="p";
        return;
      }

      //Handle  a command
      if(command_line.back() == 'a'){
        command_line.pop_back();
        this->zero = this->extract(command_line, current_line, last_line);
        this->symbol ="a";
        return;
      }

      //Handle i command
      if(command_line.back() == 'i'){
        command_line.pop_back();
        this->zero = this->extract(command_line, current_line, last_line);
        this->symbol ="i";
        return;
      }

      //Handle r command
      if(command_line.back() == 'r'){
        command_line.pop_back();
        this->zero = this->extract(command_line, current_line, last_line);
        this->symbol ="r";
        return;
      }

      //Handle p command
      if(command_line.back() == 'p'){
        command_line.pop_back();
        this->zero = this->extract(command_line, current_line, last_line);
        this->symbol ="p";
        return;
      }

      //Handle n command
      if(command_line.back() == 'n'){
        //cout << "n hai re"<<endl;
        command_line.pop_back();
        cout << command_line<<endl;
        this->zero = this->extract(command_line, current_line, last_line);
        this->symbol ="n";
        return;
      }

      //Handle c command
      if(command_line.back() == 'c'){
        command_line.pop_back();
        this->zero = this->extract(command_line, current_line, last_line);
        this->symbol ="c";
        return;
      }

      //Handle u command
      if(command_line.back() == 'u'){
        command_line.pop_back();
        if(command_line.empty() || regex_match(command_line,regex(",\\.|\\.|,|\\.,||\\.,\\."))){
          int x =1;
          this->zero = this->extract(command_line, x, x);
        }else{
          this->zero = this->extract(command_line, current_line, last_line);
        }
        //cout << "COMMAND line 1 : "<< this->line_addr_1 << "|||| line 2 : " << this->line_addr_2 <<endl;
        this->symbol ="u";
        return;
      }

      //Handle d command
      if(command_line.back() == 'd' || command_line.empty()){   //Also handles when newline is entered
        this->symbol ="d";
        if (command_line.empty()){
          return;
        }else{
          command_line.pop_back();
          if(command_line.empty() || regex_match(command_line,regex(",\\.|\\.|,|\\.,||\\.,\\."))){
            int x = 1;
            this->zero = this->extract(command_line, x, x);
          }else{
            this->zero = this->extract(command_line, current_line, last_line);
          }
          return;
        }
      }

      //Handle w command
      if(command_line.back() == 'w'){
        this->symbol ="w";
        return;
      }

      //Handle = command
      if(command_line.back() == '='){
        this->symbol ="=";
        return;
      }

      //Handle q command
      if(command_line.back() == 'q'){
        this->symbol ="q";
        return;
      }


    }
  }else{
    string message = command_line + ": Command not found";
    this->flag = false;
    this->message = message;
    return;
  }
}


bool Command::extract(string& command, int& curr_line, int& last_line){
  if(command.empty()){
    //cout << "Empty command" << endl;
    this->line_addr_1 = curr_line;
    this->line_addr_2 = curr_line;
    return true;
  }

  if(regex_match(command,regex(","))){
    //cout << "Only ," << endl;
    this->line_addr_1 = curr_line;
    this->line_addr_2 = curr_line;
    return true;
  }
  if(regex_match(command,regex("\\.,\\."))){
    //cout << "The .,." <<endl;
    this->line_addr_1 = curr_line;
    this->line_addr_2 = curr_line;
    return true;
  }

  if(regex_match(command,regex("\\.,"))){
    //cout << "The .," <<endl;
    this->line_addr_1 = curr_line;
    this->line_addr_2 = curr_line;
    return true;
  }

  if(regex_match(command,regex(",\\."))){
    //cout << "The ,." <<endl;
    this->line_addr_1 = curr_line;
    this->line_addr_2 = curr_line;
    return true;
  }

  if(regex_match(command,regex("\\.,\\$"))){
    //cout << "The .,$" <<endl;
    this->line_addr_1 = curr_line;
    this->line_addr_2 = last_line;
    if(this->line_addr_1 > this->line_addr_2){
      this->line2_lt_line1 = false;
    }
    return true;
  }

  if(regex_match(command,regex("\\$,\\."))){
    //cout << "The $,." <<endl;
    this->line_addr_1 = last_line;
    this->line_addr_2 = curr_line;
    if(this->line_addr_1 > this->line_addr_2){
      this->line2_lt_line1 = false;
    }
    return true;
  }

  if(regex_match(command,regex("\\$,\\$"))){
    //cout << "The $,$'" <<endl;
    this->line_addr_1 = last_line;
    this->line_addr_2 = last_line;
    return true;
  }

  if(regex_match(command,regex("\\$,"))){
    //cout << "The $," <<endl;
    this->line_addr_1 = last_line;
    this->line_addr_2 = curr_line;
    if(this->line_addr_1 > this->line_addr_2){
      this->line2_lt_line1 = false;
    }
    return true;
  }

  if(regex_match(command,regex(",\\$"))){
    //cout << "The ,$" <<endl;
    this->line_addr_1 = curr_line;
    this->line_addr_2 = last_line;
    if(this->line_addr_1 > this->line_addr_2){
      this->line2_lt_line1 = false;
    }
    return true;
  }

  if(regex_match(command,regex("[0-9]+,[0-9]+"))){
    //cout << "int,int" <<endl;
    string token = command.substr(0, command.find(","));
    this->line_addr_1 = stoi(token);
    string token_2 = command.substr(command.find(",") + 1, command.length());
    this->line_addr_2 = stoi(token_2);
    if(this->line_addr_1 == 0 || this->line_addr_2 == 0){
      return false;
    }
    if(this->line_addr_1 > this->line_addr_2){
      this->line2_lt_line1 = false;
    }
    return true;
  }

  if(regex_match(command,regex(",[0-9]+"))){
    //cout << "The ,int" <<endl;
    this->line_addr_1 = curr_line;
    string token = command.substr(1, command.length());
    this->line_addr_2 = stoi(token);
    if(this->line_addr_2 == 0){
      return false;
    }
    if(this->line_addr_1 > this->line_addr_2){
      this->line2_lt_line1 = false;
    }
    return true;
  }

  if(regex_match(command,regex("[0-9]+,"))){
    //cout << "The int," <<endl;
    string token = command.substr(0, command.find(","));
    this->line_addr_1 = stoi(token);
    this->line_addr_2 = curr_line;
    if(this->line_addr_1 == 0 ){
      return false;
    }
    if(this->line_addr_1 > this->line_addr_2){
      this->line2_lt_line1 = false;
    }
    return true;
  }

  if(regex_match(command,regex("[0-9]+,\\$"))){
    //cout << "The int,$" <<endl;
    string token = command.substr(0, command.find(","));
    this->line_addr_1 = stoi(token);
    this->line_addr_2 = last_line;
    if(this->line_addr_1 == 0 ){
      return false;
    }
    if(this->line_addr_1 > this->line_addr_2){
      this->line2_lt_line1 = false;
    }
    return true;
  }

  if(regex_match(command,regex("\\$,[0-9]+"))){
    //cout << "The $,int" <<endl;
    this->line_addr_1 = last_line;
    string token = command.substr(2, command.length());
    this->line_addr_2 = stoi(token);
    if(this->line_addr_2 == 0){
      return false;
    }
    if(this->line_addr_1 > this->line_addr_2){
      this->line2_lt_line1 = false;
    }
    return true;
  }

  if(regex_match(command,regex("\\.,[0-9]+"))){
    //cout << "The .,int" <<endl;
    this->line_addr_1 = curr_line;
    string token = command.substr(2, command.length());
    this->line_addr_2 = stoi(token);
    if(this->line_addr_2 == 0){
      return false;
    }
    if(this->line_addr_1 > this->line_addr_2){
      this->line2_lt_line1 = false;
    }
    return true;
  }

  if(regex_match(command,regex("[0-9]+,\\."))){
    //cout << "The int,." <<endl;
    string token = command.substr(0, command.find(","));
    this->line_addr_1 = stoi(token);
    this->line_addr_2 = curr_line;
    if(this->line_addr_1 == 0){
      return false;
    }
    if(this->line_addr_1 > this->line_addr_2){
      this->line2_lt_line1 = false;
    }
    return true;
  }

  if(regex_match(command,regex("\\."))){
    //cout << "The ." <<endl;
    this->line_addr_1 = curr_line;
    this->line_addr_2 = curr_line;
    return true;
  }

  if(regex_match(command,regex("\\$"))){
    //cout << "The $" <<endl;
    this->line_addr_1 = last_line;
    this->line_addr_2 = last_line;
    return true;
  }

  if(regex_match(command,regex("[0-9]+"))){
    //cout << "The int" <<endl;
    this->line_addr_1 = stoi(command);
    this->line_addr_2 = stoi(command);
    if(this->line_addr_1 == 0 || this->line_addr_2 == 0){
      return false;
    }
    return true;
  }
}

// int main(){
//   Command cmd;
//   string abc;
//   int curr_line = 10;
//   int last_line = 50;
//   while(true){
//     getline(cin,abc);
//     cmd.parse(abc, curr_line, last_line);
//     cout << "message: " << cmd.message<<'\n';
//     cout << "Symbol: " << cmd.symbol <<endl;
//     cout << "Line address 1:" << cmd.line_addr_1 <<endl;
//     cout << "Line address 2:" << cmd.line_addr_2 <<endl;
//   }
// }
