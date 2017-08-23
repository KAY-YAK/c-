#include "Rhombus.h"
#include <iostream>

Rhombus::Rhombus(int diagonal) {
	if(diagonal<=0){
		std::cout << "Cannot pass values less than or equal to 0 \n";
		this->~Rhombus();
	}
  if(diagonal%2==0){
    diagonal++;
  }
	this->diagonal = diagonal;
	this->set_id(this->num_incr());
  this->set_generic_name("Rhombus");
  this->set_desciptive_name("Generic Rhombus");
	this->generate_string_representation();
}

Rhombus::Rhombus(int diagonal, string desc_name) {
	if(diagonal<=0){
		std::cout << "Cannot pass values less than or equal to 0 \n";
		this->~Rhombus();
	}
  if(diagonal%2==0){
    diagonal++;
  }
	this->diagonal = diagonal;
	this->set_id(this->num_incr());
  this->set_generic_name("Rhombus");
  this->set_desciptive_name(desc_name);
	this->generate_string_representation();
}

Rhombus::~Rhombus() {

}

// int main()
// {
// 	Rhombus rect(1,"DUMBA DUMBA");
// 	Rhombus rect_1(0);
// 	Rhombus rect_2(-10);
// 	cout << rect << endl;
//   cout << rect.draw('2', 'w') << endl;
//   rect.scale(2);
//   cout << rect.draw('2', 'w') << endl;
//   cout << rect.toString() << endl;
//   Shape* shp = &rect;
//   cout << typeid(shp).name() << endl;
//   cout << typeid(*shp).name() << endl;
//   cout << *shp << endl;
//   Shape& s = rect;
//   cout << s << endl;
//   cout << rect.draw('2') << endl;
//   cout << rect.draw() << endl;
// }
