#include "RightTriangle.h"
#include <iostream>

RightTriangle::RightTriangle(int base) {
	if(base<=0){
		std::cout << "Cannot pass values less than or equal to 0 \n";
		this->~RightTriangle();
	}

	this->base = base;
  this->height = base;
	this->set_id(this->num_incr());
  this->set_generic_name("RightTriangle");
  this->set_desciptive_name("Generic RightTriangle");
	this->generate_string_representation();
}

RightTriangle::RightTriangle(int base, string desc_name) {
	if(base<=0){
		std::cout << "Cannot pass values less than or equal to 0 \n";
		this->~RightTriangle();
	}

	this->base = base;
  this->height = base;
	this->set_id(this->num_incr());
  this->set_generic_name("RightTriangle");
  this->set_desciptive_name(desc_name);
	this->generate_string_representation();
}

RightTriangle::~RightTriangle() {

}

// int main()
// {
// 	RightTriangle rect(1,"DUMBA DUMBA");
// 	RightTriangle rect_1(0);
// 	RightTriangle rect_2(-10);
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
