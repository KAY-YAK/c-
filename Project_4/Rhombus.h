#ifndef RHOMBUS_H
#define RHOMBUS_H
#include"Shape.h"
#include<typeinfo>
#include <cmath>




class Rhombus: public Shape{
public:
  int diagonal;
  Rhombus(int diagonal);
  Rhombus(int diagonal, string desc_name);
  ~Rhombus();

  void generate_string_representation(){
    this->str_rep.resize(this->diagonal);
    int point = (this->diagonal / 2) ;
    int count = 0;
    for (int x = 0; x <= this->diagonal - 1; x++) {
      this->str_rep[x].resize(this->diagonal);
      for (int y = 0; y <= this->diagonal - 1; y++) {
        if(y >= point - count && y<= point + count){
          this->str_rep[x][y] ='*';
        }else{
          this->str_rep[x][y] =' ';
        }
      }
      if(x < point){
        count++;
      }else{
        count--;
      }
    }
  }

  void scale(int factor) {
    if (this->diagonal + (2 * factor) >= 1) {
      this->diagonal = this->diagonal  + (2 * factor);
      this->generate_string_representation();
    }
  }

  float area() const{
    return float(float(this->diagonal * this->diagonal) / 2);
  }

  float perimeter() const{
    return float(2 * pow(2,.5) * this->diagonal);
  }

  vector< vector<char> > draw(char penChar, char fillChar) const{
    const int diagonal = this->diagonal;

    vector< vector<char> > temp(this->diagonal, vector<char>(this->diagonal));
    int point = (this->diagonal / 2) ;
    int count = 0;
    for (int x = 0; x <= this->diagonal - 1; x++) {
      for (int y = 0; y <= this->diagonal - 1; y++) {
        if(y >= point - count && y<= point + count){
          temp[x].push_back(penChar);
        }else{
          temp[x].push_back(fillChar);
        }
      }
      if(x < point){
        count++;
      }else{
        count--;
      }
    }

    return temp;
  }

  vector< vector<char> > draw(char penChar) const{
    const int diagonal = this->diagonal;

    vector< vector<char> > temp(this->diagonal, vector<char>(this->diagonal));
    int point = (this->diagonal / 2) ;
    int count = 0;
    for (int x = 0; x <= this->diagonal - 1; x++) {
      for (int y = 0; y <= this->diagonal - 1; y++) {
        if(y >= point - count && y<= point + count){
          temp[x].push_back(penChar);
        }else{
          temp[x].push_back(' ');
        }
      }
      if(x < point){
        count++;
      }else{
        count--;
      }
    }

    return temp;
  }

  vector< vector<char> > draw() const{
    return this->str_rep;
  }

  float calculate_box_height() const{
    return this->diagonal;
  }

  float calculate_box_width() const{
    return this->diagonal;
  }

  float scrn_area() const{
    float temp = this->diagonal /2;
    return ((temp * 2) * (temp + 1))+1;
  }

  float scrn_perimeter() const{
    return (2 * float(this->diagonal - 1));
  }


  string toString() const{
    string abcd;
    abcd = string("Shape Information") + "\n";
    abcd = abcd + "-----------------" + "\n";
    abcd = abcd + "Static type: " + typeid(this).name() + "\n";
    abcd = abcd + "Dynamic type: " + typeid(this).name() + "\n";
    abcd = abcd + "Generic Name: " + this->get_generic_name() + "\n";
    abcd = abcd + "Description: " + this->get_descriptive_name() + "\n";
    abcd = abcd + "id: " + to_string(this->get_id()) + "\n";
    abcd = abcd + "B. box width: " + to_string(this->calculate_box_width()) + "\n";
    abcd = abcd + "B. box height: " + to_string(this->calculate_box_height()) + "\n";
    abcd = abcd + "Scr area: " + to_string(this->scrn_area()) + "\n";
    abcd = abcd + "Geo area: " + to_string(this->area()) + "\n";
    abcd = abcd + "Scr Perimeter: " + to_string(this->scrn_perimeter()) + "\n";
    abcd = abcd + "Geo Perimeter: " + to_string(this->perimeter()) + "\n";
    return abcd;
  }

  void draw_on_screen(char penChar, char fillChar) const{
    cout << draw(penChar,fillChar) << endl;
  }

  void draw_on_screen(char penChar) const{
    cout << draw(penChar) << endl;
  }

  void draw_on_screen() const{
    cout << draw() << endl;
  }


};


#endif
