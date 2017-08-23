#include "IsoTriangle.h"
#include <iostream>

IsoTriangle::IsoTriangle(int base) {
	if(base<=0){
		std::cout << "Cannot pass values less than or equal to 0 \n";
		this->~IsoTriangle();
	}
  if(base%2==0){
    base++;
  }
	this->base = base;
  this->height = (base + 1)/2;
	this->set_id(this->num_incr());
  this->set_generic_name("IsoTriangle");
  this->set_desciptive_name("Generic IsoTriangle");
	this->generate_string_representation();
}

IsoTriangle::IsoTriangle(int base, string desc_name) {
	if(base<=0){
		std::cout << "Cannot pass values less than or equal to 0 \n";
		this->~IsoTriangle();
	}
  if(base%2==0){
    base++;
  }
	this->base = base;
  this->height = (base + 1)/2;
	this->set_id(this->num_incr());
  this->set_generic_name("IsoTriangle");
  this->set_desciptive_name(desc_name);
	this->generate_string_representation();
}

IsoTriangle::~IsoTriangle() {

}


//
// int main()
// {
// 	IsoTriangle rect(5,"DUMBA DUMBA");
// 	IsoTriangle rect_1(0);
// 	IsoTriangle rect_2(-10);
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
