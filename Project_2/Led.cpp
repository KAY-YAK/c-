#include"Led.h"
#include"Command.h"
#include<iostream>
#include<regex>
#include<fstream>
using namespace std;


Led::~Led(){
}

Led::Led(){
}

Led::Led(const string& f_name){
  this->filename = f_name;
}

void Led::run(){
  string read;
  //If filename is empty

  //Code to open file and read in to buffer.
  fstream fs;
  fs.open(this->filename, fstream::in);

  if(!fs){
    cout << "Unable to open file " << "\""<<this->filename<<"\"" <<endl;
    fs.close();
    if(this->filename.empty()){
      this->filename ="?";
    }

    cout << "\""<<this->filename<<"\" [New File]" <<endl;
  }else{
    //Read from file and put into buffer
    while(getline(fs, read)){
      buffer.push_back(read);
    }
    //Report no of lines read into led buffer
    cout << "\""<<this->filename<<"\"" << buffer.size() << " lines read\n";
  }
  fs.close();

  this->curr_line = buffer.size();
  this->last_line = buffer.size();

  cout << "Entering Command Mode" <<endl;

  string command_line;
  Command cmd;
  do{
    cout << ":"; //Printing prompt
    getline(cin,command_line);

    //Get rid of whiteWALKERS
    command_line = regex_replace(command_line,regex("\\s"),"");
    if(command_line =="."){
      string message = command_line + ": Command not found";
      cout << message << endl;
      continue;
    }

    //If buffer.size() == 0 then restrict user to use only i or q command
    //cout << "here" << endl;
    if(buffer.size() == 0 && !regex_match(command_line,regex("([0-9]*|[\\.$]?)[,]{0,1}([0-9]*|[\\.$]?)[iq]"))){
      cout << "\"i\"for Insert and \"q\" for Quit are only allowed for an empty file\n";
      continue;
    }

    cmd.parse(command_line, this->curr_line, this->last_line);

    //Handle erreronious commands
    if(cmd.flag == false){
      cout << cmd.message << endl;
      continue;
    }

    //Resctrict 0 for commands that require line address
    if(cmd.zero == false){
      cout <<"0 is not allowed as line address for this command\n";
      continue;
    }

    //Restricts line_addr_1 to be greater than line_addr_2
    if(cmd.line2_lt_line1 == false){
      cout << "Line address 1 cannot be greater than Line address 2\n";
      continue;
    }
    //cout << "then here" << endl;

    //cout << "LED_1 CMD_line 1: "<< cmd.line_addr_1 << "|||| CMD_line 2: " << cmd.line_addr_2 <<endl;
    this->execute(cmd);
    //cout << "LED_2 CMD_line 1: "<< cmd.line_addr_1 << "|||| CMD_line 2: " << cmd.line_addr_2 <<endl;
  }while(cmd.symbol != "q");

  //The write boolean variable helps not to write in file again just after command_w has been called
  if (this->write == false){
    fs.close();
    cout << "Quitting Led......Bye" <<endl;
    return;
  }

  cout << "Save changes to \"" << this->filename <<"\" (y/n)? :";
  getline(cin,command_line);
  while(!regex_match(command_line, regex("y|n"))){
    cout << "invalid answer: " << command_line << endl;
    cout << "Enter y for Yes and n for No" << endl;
    cout << "Save changes to \"" << this->filename <<"\" (y/n)? :";
    getline(cin,command_line);
  }
  if(command_line == "y"){
    //write to filename from buffer
    command_w();
    // fs.open(this->filename, fstream::in | fstream::out | fstream::app);
    // for(list<string>::iterator it = buffer.begin(); it!= buffer.end(); ++it){
    //   fs << *it << "\n";
    // }
    cout << "\"" << this->filename << "\" " << buffer.size() << " lines written" << endl;
    fs.close();
    cout << "Quitting Led......Bye" <<endl;
  }else{
    fs.close();
    cout << "Quitting Led......Bye" <<endl;
  }


}

//This will execute Command by retrieving symbol from command object and call respective command_*()
void Led::execute(const Command& cmd){
  // cout << "LED cmd_line>>>>>>> " << cmd.line_addr_1 << endl;
  // cout << "LED cmd_line>>>>>>> " << cmd.line_addr_2 << endl;
  if(cmd.symbol == "a"){
    this->command_a(cmd.line_addr_2);
    return;
  }

  if(cmd.symbol == "i"){
    this->command_i(cmd.line_addr_2);
    return;
  }

  if(cmd.symbol == "r"){
    this->command_r(cmd.line_addr_1, cmd.line_addr_2);
    return;
  }

  if(cmd.symbol == "p"){
    this->command_p(cmd.line_addr_1, cmd.line_addr_2);
    return;
  }

  if(cmd.symbol == "n"){
    this->command_n(cmd.line_addr_1, cmd.line_addr_2);
    return;
  }

  if(cmd.symbol == "c"){
    this->command_c(cmd.line_addr_1, cmd.line_addr_2);
    return;
  }

  if(cmd.symbol == "u"){
    this->command_u(cmd.line_addr_1, cmd.line_addr_2);
    return;
  }

  if(cmd.symbol == "d"){
    this->command_d(cmd.line_addr_1, cmd.line_addr_2);
    return;
  }

  if(cmd.symbol == "w"){
    this->command_w();
    return;
  }

  if(cmd.symbol == "="){
    this->command_equal_symbol();
    return;
  }

  if(cmd.symbol == "q"){
    this->command_q();
    return;
  }

}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//NOTE: All must modify boolean variable write and set it to true except command_w


void Led::command_a(int line_no_2){
  //Only, Line address 2 matters
  int temp=0;
  string read;
  list<string>::iterator it = buffer.begin();

  //Go to desired line
  if (line_no_2 > this->last_line){
    line_no_2 = this->last_line;
    while(true){

      getline(cin, read);
      if(read == ".") break;
      buffer.push_back(read);
      temp = temp + 1;
    }
    if(temp > 0){
      this->curr_line = buffer.size();
    }
  }else{
    for (; it!=buffer.end();++it){
      temp = temp + 1;
      if(temp == line_no_2 + 1){
        break;
      }
    }
    temp = 0;
    while(true){

      getline(cin, read);
      if(read == ".") break;
      buffer.insert(it,read);
      temp = temp + 1;
    }
    if(temp > 0){
      this->curr_line = temp + line_no_2;
    }
  }

  // temp = 0;
  //
  // //Now read and Insert
  // string read;
  // while(true){
  //   temp = temp + 1;
  //   getline(cin, read);
  //   if(read == ".") break;
  //   buffer.insert(it,read);
  // }

  //Set last_line
  this->last_line = buffer.size();

  //Set current_line


  //Modify write
  this->write = true;
}

void Led::command_i(int line_no_2){
  //Only, Line address 2 matters
  int temp=0;
  string read;
  list<string>::iterator it = buffer.begin();

  //If buffer empty
  if(buffer.empty()){
    //cout << "here\n";
    while(true){

      getline(cin, read);
      if(read == ".") break;
      buffer.push_back(read);
      temp = temp + 1;
    }
    if(temp>0){
      this->curr_line = temp;
      this->last_line = buffer.size();
      this->write = true;
      return;
    }else{
      return;
    }
  }

  //If line_no_2 == 1
  if (line_no_2 == 1){

    while(true){

      getline(cin, read);
      if(read == ".") break;
      buffer.insert(it, read);
      temp = temp + 1;
    }
    this->last_line = buffer.size();
    if(temp == 0){
    }else{
      this->curr_line = temp ;
    }

    this->write = true;
    return;
  }

  //Go to desired line
  if (line_no_2 > this->last_line){
    line_no_2 = this->last_line;
    it = buffer.end();
    while(true){

      getline(cin, read);
      if(read == ".") break;
      buffer.insert(it,read);
      temp = temp + 1;
    }
    // size()-1
    if(temp == 0){
    }else{
      this->curr_line = temp + line_no_2 - 1;
    }
  }else{
    for (; it!=buffer.end();++it){
      temp = temp + 1;
      if(temp == line_no_2){
        break;
      }
    }
    temp = 0;
    while(true){

      getline(cin, read);
      if(read == ".") break;
      buffer.insert(it,read);
      temp = temp + 1;
    }
    if(temp == 0){
    }else{
      temp = temp - 1;
      this->curr_line = temp + line_no_2;
    }

  }

  // temp = 0;
  //
  // //Now read and Insert
  // string read;
  // while(true){
  //   temp = temp + 1;
  //   getline(cin, read);
  //   if(read == ".") break;
  //   buffer.insert(it,read);
  // }

  //Set last_line
  this->last_line = buffer.size();

  //Set current_line


  //Modify write
  this->write = true;
}

void Led::command_r(int line_no_1, int line_no_2){
  //line addr 1 and line_no_2 can be greater than last. If so then......
  if(line_no_1 > this->last_line) line_no_1 = this->last_line;
  if(line_no_2 > this->last_line) line_no_2 = this->last_line;

  int temp = 0;
  int size = buffer.size();

  list<string>::iterator it = buffer.begin();



  if(line_no_1 == 1 && line_no_2 == 1 && buffer.size()==1){
    //cout << "only one line\n";
    buffer.clear();
    this->last_line = buffer.size();
    this->curr_line = buffer.size();
    this->write = true;
    return;
  }

  if(line_no_2 == this->last_line && line_no_2 == this->last_line){
    //cout << "last\n";
    buffer.pop_back();
    this->last_line = buffer.size();
    this->curr_line = buffer.size();
    this->write = true;
    return;
  }

  if(line_no_1 == line_no_2){
    //cout << "line_1 == line _2 but not last\n";
    for(; it!=buffer.end(); ++it){
      temp = temp +1;
      if (temp == line_no_1) break;
    }
    buffer.erase(it++);
    this->last_line = buffer.size();
    this->curr_line = temp;
    this->write = true;
    return;
  }

  //cout << "all 3 cond are false\n";
  //Go to line_no_1
  for(; it!=buffer.end(); ++it){
    temp = temp +1;
    if (temp == line_no_1) break;
  }

  int temp_1 = temp;
  temp = temp - 1;

  while(it != buffer.end()){
    it = buffer.erase(it);
    size = size -1;
    temp_1 = temp_1 + 1;
    if(temp_1 == line_no_2){
      it = buffer.erase(it);
      break;
    }
    //++it;
  }

  if(temp_1 == size || temp_1 > size){
    this->last_line = buffer.size();
    this->curr_line = temp;
    this->write = true;
  }else{
    this->last_line = buffer.size();
    this->curr_line = temp_1;
    this->write = true;
  }

}

void Led::command_p(int line_no_1, int line_no_2){
  //line addr 1 and line_no_2 can be greater than last. If so then......
  if(line_no_1 > this->last_line) line_no_1 = this->last_line;
  if(line_no_2 > this->last_line) line_no_2 = this->last_line;

  int temp =0;
  for(list<string>::iterator it = buffer.begin(); it!=buffer.end(); ++it){
    temp = temp + 1;
    if(temp >= line_no_1){
      cout << *it <<endl;
      if(temp == line_no_2) break;
    }
  }
  this->curr_line = temp;
  this->write = true;
}

void Led::command_n(int line_no_1, int line_no_2){
  //line addr 1 and line_no_2 can be greater than last. If so then......
  if(line_no_1 > this->last_line) line_no_1 = this->last_line;
  if(line_no_2 > this->last_line) line_no_2 = this->last_line;

  int temp =0;
  for(list<string>::iterator it = buffer.begin(); it!=buffer.end(); ++it){
    temp = temp + 1;
    if(temp >= line_no_1){
      cout << temp << "\t" << *it <<endl;
      if(temp == line_no_2) break;
    }
  }
  this->curr_line = temp;
  this->write = true;
}

void Led::command_c(int line_no_1, int line_no_2){
  //regex_replace(command_line,regex("\\s"),"");
  if(line_no_1 > this->last_line) line_no_1 = this->last_line;
  if(line_no_2 > this->last_line) line_no_2 = this->last_line;
  string replace, replaceby;

  //Ask user for string to be replaced
  cout << "change what? :" <<endl;
  getline(cin, replace);
  cout << "to what? :" <<endl;
  getline(cin, replaceby);


  int temp =0;
  for(list<string>::iterator it = buffer.begin(); it!=buffer.end(); ++it){
    temp = temp + 1;
    if(temp >= line_no_1){
      *it = regex_replace(*it, regex(replace), replaceby);
      if(temp == line_no_2) break;
    }
  }
  this->write = true;
}

void Led::command_u(int line_no_1, int line_no_2){
  // cout << "line 1" << line_no_1 << endl;
  // cout << "line 2" << line_no_2 << endl;

  if(this->curr_line - line_no_2 < 1){
    this->curr_line = 1;
  }else{
    this->curr_line = this->curr_line - line_no_2;
  }

  this->command_p(this->curr_line, this->curr_line);

  this->write = true;
}

void Led::command_d(int line_no_1, int line_no_2){
  if(this->curr_line + line_no_2 > this->last_line){
    this->curr_line = this->last_line;
  }else{
    this->curr_line = this->curr_line + line_no_2;
  }

  this->command_p(this->curr_line, this->curr_line);

  this->write = true;
}

void Led::command_w(){
  string f_name;
  if(this->filename == "?"){
    cout << "Enter filename: ";
    getline(cin, f_name);
    while(!regex_match(f_name,regex("^[a-zA-z0-9_][a-zA-z0-9_]*"))){
      cout << "Only _,letters and numbers are allowed in Filename and It cannot be blank" << endl;
      cout << "Enter filename: ";
      getline(cin, f_name);
    }
  }else{
    f_name = this->filename;
  }

  //Write to file
  fstream fs;
  fs.open(f_name,  fstream::out |  std::fstream::trunc);

  for(list<string>::iterator it = buffer.begin(); it!= buffer.end(); ++it){
    fs << *it << "\n";
  }
  cout << "\"" << f_name << "\" " << buffer.size() << " lines written" << endl;
  this->filename = f_name;
  this->write = false;
  fs.close();
}

void Led::command_equal_symbol(){
  cout << this->curr_line << endl;
  this->write = true;
}

void Led::command_q(){
  return;
}
