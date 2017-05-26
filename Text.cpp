#include "Text.h"
#include <iostream>
#include<cstring>
using namespace std;



// destructor
Text::~Text(){
	delete[] this->text;
}

// Default Constructor
Text:: Text(){
	this->text = NULL;  				//c++ cant print null pointer
}

// copy constructor /constructor overloading
Text::Text(const Text &t){


	//delete 1
	this->text = new char[strlen(t.text) + 1 ];		// obviously points to nothing so allocate dynamic memory allocation with same size as that of passed arg
	strcpy(this->text,t.text);				// copy the text
}

// conversion constructor / constructor overloading
Text::Text(const char* t){


	//delete 1
	this->text = new char[strlen(t) +1 ];		// obviously points to nothing so allocate dynamic memory and copy
	strcpy(this->text,t);
}

// setter
void Text::set(const char* t){
	if (this->text == NULL){				// if NULL then allocate dynamic memory and copy
		//delete 1
		// cout << t <<endl;
		// cout << "here Text_set()";
		this->text = new char[strlen(t) + 1];
		strcpy(this->text,t);
		//cout <<"&&&&&&" << this->text<<"&&&&&&";
	}else{							// if not NULL then deallocate, allocate dynamic memory and copy
		//cout << "THIS Text_set()" << this->text<<endl;

		delete[] this->text;

		//delete 1
		this->text = new char[strlen(t) + 1];
		strcpy(this->text,t);
	}
}

// overloading setter
void Text::set(const Text &t){
	if (this->text == NULL){				// if NULL then allocate dynamic memory and copy
		//delete 1
		// cout << t <<endl;
		// cout << "here Text_set()";
		this->text = new char[strlen(t.text) + 1];
		strcpy(this->text,t.text);
		//cout <<"&&&&&&" << this->text<<"&&&&&&";
	}else{
		delete[] this->text;					// deallocate, allocate, copy

		//delete 1
		this->text = new char[strlen(t.text) + 1 ];
		strcpy(this->text,t.text);
	}
}

// overloading = operator
Text & Text::operator=(const Text &t){			// Note the Precedence of this operator is from RIGHT to LEFT
	set(t);						// could make this faster by checking if both have the same string
	return *this; 						//A question....what if i return only this. thats not possible coz of const keyword.
								// Why cant we use &this as return. If an object calls it also passes itself as an argument(obviously by 									//reference). But then *this would be the calling object not its reference.
								// But when we return it is converted back to reference coz of Text & at return type.
}

// appending to Text_store of an object
void Text::append (const char* t){
	// Store this->text in temp and deallocate this->text
	//delete 1

	if(this->text == NULL){
		//cout <<"{{{}}}"<< "Empty text obj append"<<"{{{}}}";
		this->set(t);
		return;
	}

	char *temp = new char[strlen(this->text) + 1];
	// cout << "+++++++" << t << "+++++++" << strlen(t)<<"+++++++";
	// cout << "****" << this->text << "****";
	strcpy(temp,this->text);
	//temp [strlen(this->text)] ='\0'; // handle auto double copy IDK WHY!!!
	//cout << "@#$" << temp << "@#$";
	delete[] this->text;

	// Allocate memory for new string
	//delete 1
	int len = strlen(temp) + strlen(t) + 1;
	this->text = new char[len];

	// Copy temp in this->text. Then concatinate text to this->text
	strcpy(this->text,temp);
	strcat(this->text,t);
	this->text[len-1] = '\0';  //have to see without this line

	//cout << "^^^^^^^" << this->text << "^^^^^^^^";

	// deallocate temp
	delete [] temp;
}

// overloading appending to add Text_store of object passed as parameter to the calling object
void Text::append(const Text &t){
	// Store this->text in temp and deallocate this->text

	if(this->text == NULL){
		this->set(t);
		return;
	}

	char *temp = new char[strlen(this->text) + 1];
	strcpy(temp,this->text);
	delete[] this->text;

	// Allocate memory for new string

	//delete 1
	int len = strlen(temp) + strlen(t.text) + 1;
	this->text = new char[len];

	// Copy temp in this->text. Then concatinate text to this->text
	strcpy(this->text,temp);
	strcat(this->text,t.text);

	// deallocate temp
	delete [] temp;

}

// These are read only functions i.e. they can only read the private members and not modify them
int Text::length() const{
	return strlen(this->text);
}

// These are read only functions i.e. they can only read the private members and not modify them
bool Text::isEmpty() const{
	return (this->text==NULL ? true:false);
}

std::ostream& operator<<(std::ostream& os, const Text &t){ 		//friend function for operator overloading
	if(t.text==NULL){						//had to do this because c++ cant print null pointer
		os << "";
	}else{
		os << t.text;
		return os;
	}
}


// int main()
// {
// 	Text t1("Welcome to C++"); 						// conversion constructor 4
// 	Text t2; 										// defalt constructor
// 	Text t3(t1); 									// copy constructor
// 	cout << "t1: " << t1 << endl; 					// operator<< overload 7
// 	cout << "t2: " << t2 << endl;
// 	cout << "t3: " << t3 << endl;
// 	t2.set(" Programming"); 						// set t2's text to " Programming" 11
// 	cout << "t2: " << t2 << endl;
// 	t3.set(t1); 									// set t3's text to t1's text 14
// 	cout << "t3: " << t3 << endl;
// 	t1.append(" Programming"); 						// append the c-string " Programming" to t1's text 17
// 	cout << "t1: " << t1 << endl;
// 	t3.append(t2); 									// append t2's text to t3's text 20
// 	cout << "t3: " << t3 << endl;
// 	cout<< t3.isEmpty()<<endl;
// 	cout<<t2.length()<<endl;
//
// 	Text t4;
// 	t4 = t3 = t2;
// 	Text t5;
// 	t5.append("pppppp");
// 	//t5.set("pppppp");
// 	cout<<"@@@@@@@@@@@"<<t5;
//
// 	t2.append("?->");
//
// 	cout << t2;
//
//
// 	return 0;
// }
