#include "Rectangle.h"
#include <iostream>

Rectangle::Rectangle(int height, int width) {
	if(height<=0 || width<=0){
		std::cout << "Cannot pass values less than or equal to 0 \n";
		this->~Rectangle();
	}
	this->height = height;
	this->width = width;
	this->set_id(this->num_incr());
  this->set_generic_name("Rectangle");
  this->set_desciptive_name("Generic Rectangle");
	this->generate_string_representation();
}


Rectangle::Rectangle(int height, int width, string desc_name) {
	if(height<=0 || width<=0){
		std::cout << "Cannot pass values less than or equal to 0 \n";
		this->~Rectangle();
	}
	this->height = height;
	this->width = width;
	this->set_id(this->num_incr());
  this->set_generic_name("Rectangle");
  this->set_desciptive_name(desc_name);
	this->generate_string_representation();
}


Rectangle::~Rectangle() {

}

// int main()
// {
// 	Rectangle rect(10, 3);
// 	Rectangle rect_1(10, 0);
// 	Rectangle rect_2(-10, 3);
// 	rect.scale(-1);
// 	cout << rect << endl;
//   cout << rect.draw('2', 'w') << endl;
//   //rect.draw('2', 'w');
// }
