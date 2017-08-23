#ifndef MEGAINT_H
#define MEGAINT_H
#include<iostream>
#include<string>
#include<deque>
using namespace std;


class Megaint{
private:
  deque<char> mega_int;
  //string sign;
  //string magnitude;

public:
  string sign;
  string magnitude;
  ~Megaint();
  // Constructors
  Megaint();
  Megaint(const int&);
  Megaint(const string&);
  Megaint(const Megaint&);
  // HINDI seedha magnitude pe iterate karke deque me ghusao
  void to_deque();

  //Implement +=/-=/*=//=/%= as member since they are BINARY operators and they MODIFY the CALLING operand
  Megaint& operator+=(const Megaint& rhs); // Megaint += Megaint
  Megaint& operator-=(const Megaint& rhs); // Megaint -= Megaint
  Megaint& operator*=(const Megaint& rhs); // Megaint *= Megaint
  Megaint& operator/=(const Megaint& rhs); // Megaint /= Megaint
  Megaint& operator%=(const Megaint& rhs); // Megaint %= Megaint

  //Implement +/-/*/%// as friend because both the operands are of equal importance and none of them are modified
  friend Megaint operator+(const Megaint& lhs, const Megaint& rhs);  // Megaint + Megaint
  friend Megaint operator-(const Megaint& lhs, const Megaint& rhs);  // Megaint - Megaint;
  friend Megaint operator*(const Megaint& lhs, const Megaint& rhs);  // Megaint * Megaint
  friend Megaint operator/(const Megaint& lhs, const Megaint& rhs);  // Megaint / Megaint
  friend Megaint operator%(const Megaint& lhs, const Megaint& rhs);  // Megaint % Megaint
  //
  // //Implement UNARY - and + as member
  Megaint operator+(); // unary +
  Megaint operator-(); // unary -
  //
  // //Implement BINARY assignment as member as it modifies its calling operand
  Megaint& operator=(const Megaint& rhs);
  //
  // //
  friend bool operator==(const Megaint& lhs, const Megaint& rhs); // Megaint == Megaint
  friend bool operator<(const Megaint& lhs, const Megaint& rhs); // Megaint < Megaint
  // // To overload the remaing 4, use the std::rel_ops namespace from <utility> rather than DIY.
  // // However, we implement them in this presentaion for your reference.
  friend bool operator>(const Megaint& lhs, const Megaint& rhs); // Megaint > Megaint
  friend bool operator!=(const Megaint& lhs, const Megaint& rhs); // Megaint != Megaint
  friend bool operator<=(const Megaint& lhs, const Megaint& rhs); // Megaint <= Megaint
  friend bool operator>=(const Megaint& lhs, const Megaint& rhs); // Megaint >= Megaint
  //
  //
  // //Prefix increment and decrement
  Megaint& operator++(); // unary prefix increment
  Megaint& operator--(); // unary prefix decrement
  //
  // //Postfix increment and decrement operators with dummy int as parameter
  Megaint operator++(int); // unary postfix increment
  Megaint operator--(int); // unary postfix decrement
  //
  // // subscript operator overload: read-only
  // const char& operator[](int i) const;
  bool greater_than(const Megaint& rhs) const;
  char& operator[](int pos);
  friend ostream& operator<<(ostream &out, const Megaint& source); // write to out from supplied source

};


#endif
