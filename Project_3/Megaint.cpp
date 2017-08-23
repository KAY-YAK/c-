#include"Megaint.h"
#include<iostream>
#include<string>
#include<regex>

using namespace std;


Megaint::~Megaint(){
}


//The constructor
Megaint::Megaint(){
  this->magnitude = "0";
  this->sign = "+";
  this->to_deque();
}


Megaint::Megaint(const int& integer){
  int temp = integer;
  if(integer<0){
    this->sign = "-";
    temp = temp * -1;
  }else{
    this->sign = "+";
  }

  string convert = to_string(temp);
  this->magnitude = convert;
  this->to_deque();

}

Megaint::Megaint(const string& integer){
  //Store the sign
  string copy = integer;
  if(copy[0] == '+' || copy[0] == '-'){
    this->sign = copy[0];
    copy.erase(0,1);
  }else{
    this->sign = "+";
  }

  //Handle 0
  if(copy == "0"){
    this->mega_int.push_back(copy[0]);
    this->magnitude = "0";
    return;
  }

  //removing leading zeroes
  string str = regex_replace(copy,regex("^0+"),"");

  //store this value in string
  this->magnitude = str;

  //Store the processed string in deque
  for(int x = 0; x < str.length(); x++ ){
    this->mega_int.push_back(copy[x]);
  }
}

Megaint::Megaint(const Megaint& rhs){

  this->magnitude = rhs.magnitude;
  this->sign = rhs.sign;
  this->to_deque();
}

void Megaint::to_deque(){
  for(int x = 0; x < this->magnitude.length(); x++ ){
    this->mega_int.push_back(this->magnitude[x]);
  }
}



//+ in terms of +=
Megaint operator+(const Megaint& lhs, const Megaint& rhs){
  Megaint lhs_copy(lhs);
  lhs_copy += rhs;
  return lhs_copy;
}

Megaint& Megaint::operator+=(const Megaint& rhs){
  //Copy Constructor
  Megaint rhs_cpy(rhs);
  //Actual addition
  if((this->sign == "-" && rhs.sign =="+") || (this->sign == "+" && rhs.sign =="-")){
    //change sign of rhs_copy
    if(rhs.sign == "-"){
      rhs_cpy.sign = "+";
    }

    if(rhs.sign == "+"){
      rhs_cpy.sign = "-";
    }
    //need to check this

    (*this) -= rhs_cpy;
  }else{
    int carry = 0;

    //loop through and find the sum
    string operand_1 ="0";
    string operand_2 ="0";
    string sum = "";
    int len_1 = this->magnitude.length();
    int len_2 = rhs.magnitude.length();
    while(true){
      //x+1 % 10 == 0
      if(len_1 != 0){
        if(len_1 - 10 < 0){
          operand_1 = this->magnitude.substr(0,len_1);
          len_1 = 0;
        }else{
          operand_1 = this->magnitude.substr(len_1 - 10,10);
          len_1 = len_1 - 10;
        }
      }

      if(len_2 != 0){
        if(len_2 - 10 < 0){
          operand_2 = rhs.magnitude.substr(0,len_2);
          len_2 = 0;
        }else{
          operand_2 = rhs.magnitude.substr(len_2 - 10,10);
          len_2 = len_2 - 10;
        }
      }

      //Add
      long long int a = stoll(operand_1);
      long long int b = stoll(operand_2);
      long long int c = a + b;
      if(carry == 1){
         c = c + 1;
      }


      string temp = to_string(c);

      if(temp.length() < 10){
        int z = temp.length();
        for(int c=1; c<=(10 - z); c++){
          temp =  "0" + temp;
        }
      }

      if(temp.length() > 10){
        carry = temp[0] - '0';
        temp.erase(0,1);
      }else{
        carry = 0;
      }
      sum = temp + sum;
      operand_1 ="0";
      operand_2 ="0";

      //Breaking condition
      if(len_1 == 0 && len_2 == 0 && carry == 0) break;
    }

    //now store in this
    sum = regex_replace(sum,regex("^0+"),"");
    this->magnitude = sum;
    this->to_deque(); //change the dequeue

    //Dont need to change sign because its either +a, +b or -a, -b
  }
  return *this;
}


// Operator - interms of -=
Megaint operator-(const Megaint& lhs, const Megaint& rhs){
  Megaint lhs_copy(lhs);
  lhs_copy -= rhs;
  return lhs_copy;
}


Megaint& Megaint::operator-=(const Megaint& rhs){
  //Copy constructor
  Megaint rhs_cpy(rhs);
  //Actual addition
  if((this->sign == "-" && rhs.sign =="+") || (this->sign == "+" && rhs.sign =="-")){
    //call operator+
    //change sign of rhs
    if(rhs.sign == "-"){
      rhs_cpy.sign = "+";
    }

    if(rhs.sign == "+"){
      rhs_cpy.sign = "-";
    }
    //need to check this
    (*this) += rhs_cpy;
  }else{
    int carry = 0;
    string operand_1 ="0";
    string operand_2 ="0";
    string diff = "";
    string tmp_1 = "";
    string tmp_2 = "";
    int len_1 = 0;
    int len_2 = 0;

    if(this->magnitude == rhs.magnitude){
      this->magnitude ="0";
      this->sign = "+";
      return *this;
    }

    if(this->greater_than(rhs)){
      len_1 = this->magnitude.length();
      len_2 = rhs.magnitude.length();
      tmp_1 = this->magnitude;
      tmp_2 = rhs.magnitude;
      //this->sign = "+";
    }else{
      len_1 = rhs.magnitude.length();
      len_2 = this->magnitude.length();
      tmp_1 = rhs.magnitude;
      tmp_2 = this->magnitude;
      if(this->sign == "-"){
        this->sign = "+";
      }else{
        this->sign = "-";
      }

      //this->sign = "-";
    }


    while(true){
      if(len_1 != 0){
        if(len_1 - 10 < 0){
          operand_1 = tmp_1.substr(0,len_1);
          len_1 = 0;
        }else{
          operand_1 = tmp_1.substr(len_1 - 10,10);
          len_1 = len_1 - 10;
        }
      }

      if(len_2 != 0){
        if(len_2 - 10 < 0){
          operand_2 = tmp_2.substr(0,len_2);
          len_2 = 0;
        }else{
          operand_2 = tmp_2.substr(len_2 - 10,10);
          len_2 = len_2 - 10;
        }
      }


      long long int a = stoll(operand_1);
      long long int b = stoll(operand_2);
      if(carry == 1){
        b = b + 1;
      }
      long long int c = 0;

      if(a<b){
        operand_1 = "1" + operand_1 ;
        a = stoll(operand_1);
        carry = 1;
      }else{
        carry = 0;
      }

      c = a - b;

      string temp = to_string(c);


      if(temp.length() < 10){
        int short_by = 10 - temp.length();
        for(int shift = 1; shift <= short_by; shift++){
          temp = "0" + temp;
        }
      }

      diff = temp + diff;
      operand_1 ="0";
      operand_2 ="0";

      //Breaking condition
      if(len_1 == 0 && len_2 == 0 && carry == 0) break;

    }


    this->magnitude = regex_replace(diff, regex("^0+"),"");
    this->to_deque(); //change the dequeue




  }
  return *this;
}



Megaint& Megaint::operator*=(const Megaint& rhs){
  //this is Multiplicand
  //rhs is multiplier
  int carry = 0;

  //IF ANY 0 RETURN 0
  if(this->magnitude == "0" || rhs.magnitude == "0"){
    this->magnitude = "0";
    this->to_deque();
    this->sign = "+";
    return *this;
  }

  //loop through and find the sum
  string operand_1 ="0";
  string operand_2 ="0";
  Megaint sum(operand_1);

  int count = 0;

  for(int x = rhs.magnitude.length() - 1; x >= 0  ; x--){
    string partial_prod = "";
    operand_2 = rhs.magnitude[x];
    int len_1 = this->magnitude.length();



    while(true){
      if(len_1 != 0){
        if(len_1 - 10 < 0){
          operand_1 = this->magnitude.substr(0,len_1);
          len_1 = 0;
        }else{
          operand_1 = this->magnitude.substr(len_1 - 10,10);
          len_1 = len_1 - 10;
        }
      }

      long long int a = stoll(operand_1);

      int b = operand_2[0] -'0' ;
      long long int c = 0;

      //Partial product
      c = a * b;

      //if carry is gt 0 then add to result
      if(carry != 0){
        c = c + carry;
      }

      string temp = to_string(c);
      //If len < 10
      if(temp.length()<10){
        int z = temp.length();
        for(int c = 1; c <= (10 - z); c++){
          temp = "0" + temp;
        }
      }


      if(temp.length() > 10){
        carry = temp[0] - '0';
        temp.erase(0,1);
      }else{
        carry = 0;
      }
      partial_prod = temp + partial_prod;
      if(len_1 == 0 ) break;
    }

    //New line
    if(carry > 0){
      partial_prod = to_string(carry) + partial_prod;
      carry = 0;
    }

    for(int d = 0; d<count; d++){
      partial_prod.append("0");
    }


    Megaint part_prod(partial_prod);
    sum += part_prod;
    count = count + 1;
  }


  this->magnitude = regex_replace(sum.magnitude, regex("^0+"), "");
  this->to_deque();

  //Handle sign of product
  if((this->sign == "-" && rhs.sign == "+") || (this->sign == "+" && rhs.sign == "-") ){
    this->sign = "-";
  }else{
    this->sign = "+";
  }

  return *this;
}

Megaint operator*(const Megaint& lhs, const Megaint& rhs){
  Megaint lhs_copy(lhs);
  lhs_copy *= rhs;
  return lhs_copy;
}


Megaint& Megaint::operator/=(const Megaint& rhs){

  if (rhs.magnitude == "0"){
    throw "Division by zero Error!";
  }

  Megaint this_copy(*this);
  Megaint rhs_copy_1(rhs);
  Megaint rhs_copy_2(rhs);
  this_copy.sign = "+";
  rhs_copy_1.sign = "+";
  rhs_copy_2.sign = "+";
  //this_copy-=rhs_copy;

  //Handle when divisor greater than dividend
  if(!this_copy.greater_than(rhs_copy_1) && this->magnitude!=rhs.magnitude){
    return *this;
  }


  //divide
  string operand_1 ="0";
  string operand_2 = rhs.magnitude;
  int len_1 = this->magnitude.length();;
  int len_2 = rhs.magnitude.length();
  string quotient ="";

  int mult = 0;
  operand_1 = this->magnitude.substr(0,len_2);
  Megaint temp_1(operand_1);
  int pos = len_2 - 1;
  bool loob = false;

  while(true){
    int count = 0;
    while((temp_1 - rhs_copy_1).sign == "-" ){
      pos = pos + 1;
      quotient = quotient + "0";
      if(pos >= len_1 ){
        loob = true;
        break;
      }


      if(this->magnitude[pos] == '0' && temp_1.magnitude == "0"){
        continue;
      }

      temp_1.magnitude = temp_1.magnitude + this->magnitude[pos];
      temp_1.to_deque();
    }


    if(temp_1.magnitude != "0"){
      temp_1.magnitude = regex_replace(temp_1.magnitude , regex("^0+"),"");
    }

    if(loob == true){
      break;
    }
    if(pos == len_1){
      break;
    }



    for(mult = 1; mult<=10; mult++){
      rhs_copy_2.magnitude = rhs.magnitude;
      Megaint temp_2(to_string(mult));
      rhs_copy_2*=temp_2;
      if( (temp_1 - rhs_copy_2).sign =="-"){
        rhs_copy_2-=rhs_copy_1;
        temp_1-=rhs_copy_2;;
        mult = mult - 1;
        break;
      }
    }

    quotient = quotient + to_string(mult);
    pos = pos + 1;
    if(pos > (len_1 - 1)) break;
    temp_1.magnitude = regex_replace(temp_1.magnitude , regex("^0+"),"");
    if(temp_1.magnitude == ""){
      temp_1.magnitude = this->magnitude[pos];
    }else{
      temp_1.magnitude = temp_1.magnitude + this->magnitude[pos];
    }

    temp_1.to_deque();


  }

  quotient = regex_replace(quotient,regex("^0+"),"");
  this->magnitude = quotient;
  this->to_deque();
  //Decide sign
  if((this->sign == "-" && rhs.sign == "+") || (this->sign == "+" && rhs.sign == "-")){
    this->sign = "-";
  }else{
    this->sign = "+";
  }

  return *this;
}



Megaint operator/(const Megaint& lhs, const Megaint& rhs){
  Megaint lhs_copy(lhs);
  lhs_copy /= rhs;
  return lhs_copy;
}



Megaint& Megaint::operator%=(const Megaint& rhs){
  //this is DIVIDEND and rhs is DIVISOR
  //Handle division by 0
  //remember to use try catch
  if (rhs.magnitude == "0"){
    throw "Division by zero Error!";
  }

  Megaint this_copy(*this);
  Megaint rhs_copy_1(rhs);
  Megaint rhs_copy_2(rhs);
  this_copy.sign = "+";
  rhs_copy_1.sign = "+";
  rhs_copy_2.sign = "+";
  //this_copy-=rhs_copy;

  //Handle when divisor greater than dividend
  if(!this_copy.greater_than(rhs_copy_1) && this->magnitude!=rhs.magnitude){
    return *this;
  }


  //divide
  string operand_1 ="0";
  string operand_2 = rhs.magnitude;
  int len_1 = this->magnitude.length();;
  int len_2 = rhs.magnitude.length();
  string quotient ="";

  int mult = 0;
  operand_1 = this->magnitude.substr(0,len_2);
  Megaint temp_1(operand_1);
  int pos = len_2 - 1;
  bool loob = false;

  while(true){
    int count = 0;
    while((temp_1 - rhs_copy_1).sign == "-" ){
      pos = pos + 1;
      quotient = quotient + "0";
      if(pos >= len_1 ){
        loob = true;
        break;
      }

      if(this->magnitude[pos] == '0' && temp_1.magnitude == "0"){
        continue;
      }

      temp_1.magnitude = temp_1.magnitude + this->magnitude[pos];
      temp_1.to_deque();
    }

    if(temp_1.magnitude != "0"){
      temp_1.magnitude = regex_replace(temp_1.magnitude , regex("^0+"),"");
    }

    if(loob == true){
      break;
    }
    if(pos == len_1){
      break;
    }



    for(mult = 1; mult<=10; mult++){
      rhs_copy_2.magnitude = rhs.magnitude;
      Megaint temp_2(to_string(mult));
      rhs_copy_2*=temp_2;
      if( (temp_1 - rhs_copy_2).sign =="-"){
        rhs_copy_2-=rhs_copy_1;
        temp_1-=rhs_copy_2;
        mult = mult - 1;
        break;
      }
    }

    quotient = quotient + to_string(mult);
    pos = pos + 1;

    if(pos > (len_1 - 1)) break;
    temp_1.magnitude = regex_replace(temp_1.magnitude , regex("^0+"),"");
    if(temp_1.magnitude == ""){
      temp_1.magnitude = this->magnitude[pos];
    }else{
      temp_1.magnitude = temp_1.magnitude + this->magnitude[pos];
    }

    temp_1.to_deque();


  }

  quotient = regex_replace(quotient,regex("^0+"),"");
  if(temp_1.magnitude == ""){
    this->magnitude = "0";
    this->sign = "+";
    return *this;
  }
  this->magnitude = temp_1.magnitude;
  this->to_deque();

  return *this;
}



Megaint operator%(const Megaint& lhs, const Megaint& rhs){
  Megaint lhs_copy(lhs);
  lhs_copy %= rhs;
  return lhs_copy;
}



bool Megaint::greater_than(const Megaint& rhs)const{
  int this_len = this->magnitude.length();
  int rhs_len = rhs.magnitude.length();
  if(this_len>rhs_len) return true;
  if(this_len<rhs_len) return false;
  int count = 0;
  while(true){
    if(this->magnitude[count] == rhs.magnitude[count]){
      count = count + 1;
      if (count > this_len){
        return false;
      }
      continue;
    }else if(this->magnitude[count] -'0' > rhs.magnitude[count] - '0' ){
      return true;
    }else{
      return false;
    }

  }

}



Megaint Megaint::operator+(){
  if(this->sign == "-"){
    this->sign = "-";
  }else{
    this->sign = "+";
  }
  return *this;
}



Megaint Megaint::operator-(){
  if(this->sign == "-"){
    this->sign = "+";
  }else{
    this->sign = "-";
  }
  return *this;
}



Megaint& Megaint::operator=(const Megaint& rhs){
  this->magnitude = rhs.magnitude;
  this->sign = rhs.sign;
  this->to_deque();
  return *this;
}



bool operator==(const Megaint& lhs, const Megaint& rhs){
  if(lhs.magnitude == "0" && rhs.magnitude == "0"){
    return true;
  }

  if(lhs.magnitude == rhs.magnitude && lhs.sign == rhs.sign){
    return true;
  }

  return false;
}



bool operator<(const Megaint& lhs, const Megaint& rhs){
  if(lhs.magnitude == "0" && rhs.magnitude == "0"){
    return false;
  }

  //May run into problems with -ve 0
  if(lhs.sign == "-" && rhs.sign == "+"){
    return true;
  }

  //Reached here. So, it means sign is equal
  if(lhs.sign == "-" && lhs.greater_than(rhs)){
    return true;
  }

  if(lhs.sign == "+" && rhs.greater_than(lhs)){
    return true;
  }

  return false;
}



bool operator>(const Megaint& lhs, const Megaint& rhs){
    return rhs < lhs;
}


bool operator!=(const Megaint& lhs, const Megaint& rhs){
  return !(lhs == rhs);
}


bool operator<=(const Megaint& lhs, const Megaint& rhs){
  return !(rhs < lhs);
}


bool operator>=(const Megaint& lhs, const Megaint& rhs){
  return !(lhs<rhs);
}

//Decide  whether you want to add int or just add int 1 or mega int 1
Megaint& Megaint::operator++(){
  int add = 1;
  Megaint incr(add);
  *this = *this + incr;
  return *this;
}


Megaint& Megaint::operator--(){
  int sub = 1;
  Megaint decr(sub);
  *this = *this - decr;
  return *this;
}


Megaint Megaint::operator++(int){
  Megaint copy = *this;
  int add = 1;
  Megaint incr(add);

  *this = *this + incr;
  return copy;
}


Megaint Megaint::operator--(int){
  Megaint copy = *this;
  int sub = 1;
  Megaint decr(sub);
  *this = *this - decr;
  return copy;
}


char& Megaint::operator[](int pos){
  if(pos > this->magnitude.length() - 1 ){
    throw "Out of Index Error!!";
  }

  if(pos < 0){
    throw "Negative Indexing not supported!!";
  }

  return this->magnitude[pos];
}


//Have to decide whether to print sign for positive numbers
ostream& operator<<(ostream &out, const Megaint& source){
  string print = source.sign + source.magnitude;
  out << print;
  return out;
}
