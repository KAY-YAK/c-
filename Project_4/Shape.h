#ifndef SHAPE_H
#define SHAPE_H
#include<string>
#include<vector>
#include<iostream>
#include<typeinfo>
using namespace std;



class Shape {
private:
	static int num;
	int id_num;
	string generic_name;
	string descriptive_name;
public:

	vector< vector<char> > str_rep;

	//getters
	virtual int  get_id() const;
	virtual string  get_generic_name() const;
	virtual string  get_descriptive_name() const;
	int num_incr();

	//setters
  virtual void set_generic_name(string name);
	virtual void  set_desciptive_name(string name);
	virtual void  set_id(int id);

	virtual void draw_on_screen(char penChar, char fillChar) const = 0;
	virtual void draw_on_screen(char penChar) const = 0;
	virtual void draw_on_screen() const = 0;

	//pure_virtuals
	virtual void generate_string_representation() = 0;
	virtual void scale(int factor) = 0;
	virtual float area() const = 0;
	virtual float perimeter() const = 0;
	virtual vector< vector<char> > draw(char penChar, char fillChar) const = 0;
	virtual vector< vector<char> > draw(char penChar) const = 0;
	virtual vector< vector<char> > draw() const = 0;
	virtual float calculate_box_height() const = 0;
	virtual float calculate_box_width() const = 0;
	virtual float scrn_area() const = 0;
	virtual float scrn_perimeter() const = 0;
	virtual string toString() const = 0;


};

inline ostream& operator<<(ostream& os, const Shape& obj) {
  os << "Shape Information" << endl;
  os << "-----------------" << endl;
  os << "Static type: " << typeid(&obj).name() << endl;
  os << "Dynamic type: " << typeid(obj).name() << endl;
  os << "Generic Name: " << obj.get_generic_name() << endl;
  os << "Description: " << obj.get_descriptive_name() << endl;
  os << "id: " << obj.get_id() << endl;
  os << "B. box width: " << obj.calculate_box_width() << endl;
  os << "B. box height: " << obj.calculate_box_height() << endl;
  os << "Scr area: " << obj.scrn_area() << endl;
  os << "Geo area: " << obj.area() << endl;
  os << "Scr Perimeter: " << obj.scrn_perimeter() << endl;
  os << "Geo Perimeter: " << obj.perimeter() << endl;
  return os;
}

inline ostream& operator<<(ostream& os,  const vector< vector<char> >& grid) {
  for (const vector<char>& vec : grid) {
    for (const char& ch : vec) {
      os << ch;
    }
    os <<"\n";
  }
  return os;
}

#endif
