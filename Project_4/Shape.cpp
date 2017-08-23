#include"Shape.h"
#include<iostream>
using namespace std;


int Shape::num = 0;

int Shape::get_id() const{
	return this->id_num;
}

string Shape::get_generic_name() const{
	return this->generic_name;
}

string Shape::get_descriptive_name() const{
	return this->descriptive_name;
}

int Shape::num_incr() {
	Shape::num++;
	return Shape::num;
}

void Shape::set_generic_name(string name) {
	this->generic_name = name;
}

void Shape::set_desciptive_name(string name) {
	this->descriptive_name = name;
}

void Shape::set_id(int id) {
	this->id_num = id;
}
