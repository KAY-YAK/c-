/*c++ is a brainless compiler. If I incude the same header more than once it will do so and later this will cause errors.
This can happen specially when we have two seperate headers but both are include a common headre file. So, we need a way to handle multiple includes.
To guard from this we use PREPOCESSOR WRAPPER. The preprocessor wrapper tells the compiler to skip a header completely if it is already included
Example :

#ifndef ...  <- if not defined
#define ...
  //code
#endif
*/

#ifndef TEXT_H
#define TEXT_H
#include<iostream>

class Text{
	private:
		char* text;
	public:
		~Text();							// destructor
		Text();								// default constructor
		Text(const Text &);					// copy constructor /constructor overloading
		Text(const char*);					// conversion constructor / constructor overloading
		void set(const char*);				// setter
		void set(const Text &);				// overloading setter
		Text & operator= (const Text &);	// overloading = operator
		void append (const char*);			// appending to Text_store of an object
		void append (const Text &);			// overloading appending to add Text_store of object passed as parameter to the calling object
		int length() const;					// These are read only functions i.e. they can only read the private members and not modify them 
		bool isEmpty() const;				// If a function modifies private members it CANT BE CONST
		friend std::ostream& operator<<(std::ostream & , const Text &); //friend function for operator overloading
		
		
		
};


#endif
