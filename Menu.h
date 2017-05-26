#ifndef MENU_H
#define MENU_H
#include "Text.h"
#include <iostream>


class Menu{
	private:
		Text* option_list;							// This is a stack!! Note there are push_back and pop_back functions. So it must be a stack
		int count;
		int max_list_size;
		Text top_prompt;
		Text bottom_prompt;
		Text top_text;
		Text bottom_text;
	public:
		Menu();										// Default Constructor
		Menu(const Menu &);							// Copy Constructor
		~Menu();
		void double_capacity();						// Double max_list_size
		void push_back(char *);						// Create text obj assign char * and PUSH it to the STACK option_list
													// check OVERFLOW
		void push_back(const Text &);				// PUSH text obj to the STACK option_list
													// check OVERFLOW
		void insert(int, Text &);					// Insert at position by shifting
		Text remove(int);							// removes option from STACK option_list at index i
		const int size();							// Returns size of STACK option_list NOTE THIS IS NOT max_list_size
		const int capacity();						// Returns value of max_list_size
		void pop_back();							// POP from STACK max_list_size
													// Do check for UNDERFLOW
		Text get(int); 								// Return k th From stack option_list
		const Text toString();						// Read all in STACK option_list and concatinate them in char*, store in Text object and return it
		int read_option_number();					// Calls to string internally then reads and returns a vaiid option number


		//I think these are explained in a wrong way in the assignment
		void set_top_prompt(const Text &);
		void set_bottom_prompt(const Text &);
		void set_top_message(const Text &);
		void set_bottom_message(const Text &);

		void clear_top_prompt();
		void clear_bottom_prompt();
		void clear_top_message();
		void clear_bottom_message();
		const bool isEmpty();                       // Returns true if STACK is empty()

		//Operator Overloading
		Menu & operator= (const Menu &);			// overloading = operator
		friend std::ostream& operator<<(std::ostream & , Menu &); //friend function for operator overloading
};

#endif
