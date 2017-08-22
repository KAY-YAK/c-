#include "Text.h" // Still getting undefined reference....maybe have to link headers during compilation
#include "Menu.h"
#include <iostream>
#include <cstring>
#include<string>
#include<stdexcept>
#include<cstdlib>
using namespace std;


//Destructor
Menu::~Menu() {
	delete[] this->option_list;
}


// Default Constructor
Menu::Menu() {
	this->count = 0;
	this->max_list_size = 1;
	this->option_list = new Text[max_list_size]; // This is a stack!! Note there are push_back and pop_back functions. So it must be a stack
	this->top_prompt;
	this->bottom_prompt;
	this->top_text;
	this->bottom_text;
}


// Copy Constructor
// NEED TO CHECK FOR DEEP COPY	for all variables
// Also need to chek if = has been overloaded
Menu::Menu(const Menu &otherMenu) {
	this->count = otherMenu.count;
	this->max_list_size = otherMenu.max_list_size;

	// Allocate memory for stack of the created object
	this->option_list = new Text[otherMenu.count];

	// Copy the stack from otherMenu
	for (int a = 0; a <= count - 1; a++) {
		this->option_list[a] = otherMenu.option_list[a];
	}

	this->top_prompt = otherMenu.top_prompt;
	this->bottom_prompt = otherMenu.bottom_prompt;
	this->top_text = otherMenu.top_text;
	this->bottom_text = otherMenu.bottom_text;

}



// Double max_list_size [little modification as per assignment expectation]
void Menu::double_capacity() {
	//double the size

	//cout<<"prev size "<<this->max_list_size<<endl;
	this->max_list_size = this->max_list_size * 2;
	//cout<<"doubl size "<<this->max_list_size<<endl;

	//make temp array for copying
	Text *temp_copy = new	Text[this->max_list_size];

	//Copy this->option_list to temp_copy
	for (int i = 0; i <= (this->count - 1); i++) {
		temp_copy[i] = this->option_list[i];
	}

	//Deallocate this->option_list
	delete[]this->option_list;

	//Allocate memory to this->option_list with size this->max_list_size
	this->option_list = new Text[this->max_list_size];

	//TEST
	//cout << this->max_list_size<< endl;

	//Copy content to this->option_list from temp_copy
	for (int i = 0; i <= (this->count - 1); i++) {
		this->option_list[i] = temp_copy[i];
	}

	//Deallocate temp_copy
	delete[] temp_copy;


}


// Create text obj assign char * and PUSH it to the STACK option_list
void Menu::push_back(char *pOption) {
	// Check for overflow
	if (this->count == this->max_list_size) {
		this->double_capacity();
	}

	//If not overflow
	this->option_list[this->count].set(pOption);
	//cout << this->option_list[this->count]<<"<<<push_back\n";
	this->count = this->count + 1;
	return;

}


// PUSH text obj to the STACK option_list
void Menu::push_back(const Text &option) {
	// check OVERFLOW
	if (this->count == this->max_list_size) {
		this->double_capacity();
	}

	//If not overflow
	this->option_list[this->count] = option;
	this->count = this->count + 1;
	return;
}


// Insert at position by shifting
void Menu::insert(int index, const Text &option) {
	//Check if index given is negative
	if (index<0) {
		cout << "No negative indexing" << endl;
		return;
	}

	//Check if index given is valid
	if ((index - 1) > this->count) {
		cout << "Index out of bounds" << endl;
		return;
	}

	//Check if there is space in stack for insertion
	if (this->count == this->max_list_size) {
		this->double_capacity();
	}

	Text temp_1;
	Text temp_2 = option;

	for (int c = (index - 1); c <= (this->max_list_size - 1); c++) {		// -1 because max_list_size if 4 then index is 0, 1, 2, 3
		temp_1 = this->option_list[c];
		this->option_list[c] = temp_2;
		temp_2 = temp_1;
	}



	//increase count
	this->count = this->count + 1;

}


//No idea if NULL pointer can be returned
// removes option from STACK option_list at index i
Text Menu::remove(int index) {

	Text temp;
	//Check if stack is empty
	if (this->isEmpty()) {
		cout << "Nothing to remove" << endl;
		return temp;
	}
	//Check if index given is negative
	if (index<0) {
		cout << "No negative indexing" << endl;
		return temp;
	}

	//Check if index given is valid
	if ((index - 1) > this->count) {
		cout << "Index out of bounds" << endl;
		return temp;
	}

	temp = this->option_list[index - 1];

	Text *new_option_list = new Text[this->max_list_size];

	int new_index = 0;

	for (int c = 0; c < (this->max_list_size); c++) {		// -1 because max_list_size if 4 then index is 0, 1, 2, 3

		//If this->option_list[c] is EMPTY break;
		if (this->option_list[c].isEmpty()) {
			break;
		}

		// Skip this because we dont want to copy this to the new array
		if (c == (index - 1)) {
			continue;
		}

		// Copy from this->option_list to new_option_list
		new_option_list[new_index] = this->option_list[c];
		new_index = new_index + 1;
	}

	//deallocate this->option_list
	delete[] this->option_list;

	//allocate memory to this->option_list
	this->option_list = new Text[this->max_list_size];
	//Now copy from new_option_list to new this->max_list_size
	for (int c = 0; c <= (this->max_list_size - 1); c++) {	//This might cause problem just try copying the whole array

		if (new_option_list[c].isEmpty()) {
			break;
		}
		this->option_list[c] = new_option_list[c];
	}
	this->count = this->count - 1;
	return temp;
}


// Returns size of STACK option_list NOTE THIS IS NOT max_list_size
const int Menu::size() {
	return this->count;
}


// Returns value of max_list_size
const int Menu::capacity() {
	return this->max_list_size;
}


// POP from STACK max_list_size
void Menu::pop_back() {
	if (this->isEmpty()) {
		cout << "There is nothing to remove";
	}
	else {
		this->option_list[this->count - 1];
		this->option_list[this->count - 1].set(NULL);
		this->count = this->count - 1;
	}
}


// Return k th From stack option_list
Text Menu::get(int k) {
	//if empty send message
	if (this->isEmpty()) {
		cout << "Empty stack" << endl;
		Text t;
		return t;
	}
	else {
		return this->option_list[k - 1];
	}
}

// Read all in STACK option_list and concatinate them in char*, store in Text object and return it
const Text Menu::toString() {
	// Create a Text object to store the string representation of Menu object. This is the object that we will return;
	Text toStr;

	//append top_message
	if (!this->top_text.isEmpty()) {
		//cout << "top_text\n";
		toStr.append(this->top_text);
		toStr.append("\n");
	}

	//append top_prompt
	if (!this->top_prompt.isEmpty()) {
		//cout << "top_prompt\n";
		toStr.append(this->top_prompt);
		toStr.append("\n");
	}


	//append all Text object in option_list array of Menu
	if (!this->isEmpty()) {
		//cout << "option_list\n";
		for (int c = 0; c <= (this->count - 1); c++) {

			char *conc = new char[4];

			conc[0] = '(';
			conc[1] = '0' + (c + 1);
			conc[2] = ')';
			conc[3] = '\0'; //must put this else it will fill with garbage
			//append conc and option_list[c] to toString Text object
			toStr.append(conc);
			//cout << "[{()}]" << this->option_list[c] << "[{()}]";
			toStr.append(this->option_list[c]);
			//append next line escape sequence
			toStr.append("\n");
		}
	}

	//append literal ?->
	toStr.append("?->");

	//append bottom_prompt
	if (!this->bottom_prompt.isEmpty()) {
		//cout << "bottom_prompt\n";
		toStr.append(this->bottom_prompt);
		toStr.append("\n");
	}

	//append bottom_message
	if (!this->bottom_text.isEmpty()) {
		//cout << "bottom_text\n";
		toStr.append(this->bottom_text);
	}


	return toStr;
}


// Calls to string internally then reads and returns a vaiid option number
int Menu::read_option_number() {

	int option;
	char *user_choice = new char[256];
	bool condition = true;

	//if empty just return choice
	if (this->count == 0) {
		while (condition) {
			cin.getline(user_choice, 256);
			try {
				option = atoi(user_choice);
				condition = false;
			}
			catch (invalid_argument &e) {
				cout << "Invalid entry, must be a number" << endl;
			}
		}

		delete[]user_choice;
		return option;
	}

	cout << this->toString();


	while (condition) {
		cin.getline(user_choice, 256);
		try {
			option = atoi(user_choice);
			condition = false;
		}
		catch (invalid_argument &e) {
			cout << "Invalid entry, must be a number" << endl;
		}
		catch (out_of_range &e) {
			cout << "Wahahahahahahahah!!! art thou SERIOUS??" << endl;
		}

		if (option > this->count) {
			cout << "invalid choice" << option << ". It must be within range [1," << this->count << "]" << endl;
			condition = true;
		}
	}
	delete[]user_choice;
	return option;
}


//I think these are explained in a wrong way in the assignment
void Menu::set_top_prompt(const Text &t) {
	this->top_prompt = t;
}


void Menu::set_bottom_prompt(const Text &t) {
	this->bottom_prompt = t;
}


void Menu::set_top_message(const Text &m) {
	this->top_text = m;
}


void Menu::set_bottom_message(const Text &m) {
	this->bottom_text = m;
}

void Menu::clear_top_prompt() {
	this->top_prompt.set("");
}

void Menu::clear_bottom_prompt() {
	this->bottom_prompt.set("");
}


void Menu::clear_top_message() {
	this->top_text.set("");
}


void Menu::clear_bottom_message() {
	this->bottom_text.set("");
}


const bool Menu::isEmpty() {                       // Returns true if STACK option_list is empty()
	if (this->count == 0) {
		return true;
	}
	else {
		return false;
	}
}


//Operator Overloading
Menu & Menu::operator= (const Menu &menu) {
	//deallocate option_list
	delete[] this->option_list;

	//allocate memory
	this->option_list = new Text[menu.max_list_size];

	//copy stack option_list
	for (int c = 0; c <= menu.count - 1; c++) {
		this->option_list[c] = menu.option_list[c];
	}

	//copy all other members
	this->count = menu.count;
	this->max_list_size = menu.max_list_size;
	this->top_prompt = menu.top_prompt;
	this->bottom_prompt = menu.bottom_prompt;
	this->bottom_text = menu.bottom_text;
	this->top_text = menu.top_text;

	return *this;
}

//need tostring for this.
std::ostream& operator<<(std::ostream &os, Menu &menu) {
	// cout<< "##########" << endl;
	// cout<<menu.toString() << endl;
	// cout<< "##########" << endl;
	os << menu.toString();
	return os;
}

// int main()
// {
//
//
// 	Menu menu; // an empty menu
// 	cout << menu << endl;
//
// 	int choice = menu.read_option_number();
// 	cout << "you entered: " << choice << endl;
//
// 	cout << "demo operator<< on empty menu" << endl;
// 	cout << "--------------------------------" << endl;
// 	cout << menu << endl;
// 	cout << "--------------------" << endl;
//
// 	cout << "demo push_back" << endl;
// 	cout << "---------------------------------" << endl;
// 	menu.push_back("Pepsi");
// 	cout << menu << endl;
//
// 	cout << "demo more push_backs" << endl;
// 	cout << "---------------------------------" << endl;
// 	menu.push_back("Apple juice");
// 	menu.push_back("Root beer");
// 	choice = menu.read_option_number();
// 	cout << "you entered: " << choice << endl;
// 	cout << "--------------------" << endl;
//
// 	cout << "demo top/bot prompts" << endl;
// 	cout << "---------------------------------" << endl;
// 	menu.set_top_prompt("Choose your thirst crusher: ");
// 	menu.set_bottom_prompt("Enter a drink number: ");
// 	cout << menu << endl;
// 	cout << "--------------------" << endl;
//
// 	cout << "demo pop_back and insert on a menu" << endl;
// 	cout << "-------------------------------------" << endl;
// 	menu.pop_back();    // remove the last option
// 	cout << menu << "bagagagagagag\n";
// 	Text t("Iced tea with lemon");
// 	menu.insert(1, t);  //  this will be option 2
// 	choice = menu.read_option_number();
// 	cout << "you entered: " << choice << endl;
// 	cout << "--------------------" << endl;
//
// 	cout << "demo pop_back and remove on a menu" << endl;
// 	cout << "-------------------------------------" << endl;
// 	menu.pop_back(); // // remove the last option
// 	menu.remove(1);  //  // remove the first option (index k indexes element k+1)
// 	cout << menu << endl;
// 	cout << "--------------------" << endl;
//
// 	cout << "demo top/bot messages" << endl;
// 	cout << "---------------------------------" << endl;
// 	menu.set_top_message("Quench your thirst with our fine drinks");
// 	menu.set_bottom_message("Time to obey your thirst!");
// 	cout << menu << endl;
// 	cout << "--------------------" << endl;
//
// 	cout << "demo removing the only element" << endl;
// 	cout << "---------------------------------" << endl;
// 	menu.pop_back();
// 	cout << menu << endl;
// 	cout << "--------------------" << endl;
//
// 	cout << "demo resetting top/bot items + more push_backs" << endl;
// 	cout << "---------------------------------" << endl;
// 	menu.set_top_message("Who Says You Can't Buy Happiness?");
// 	menu.clear_bottom_message();
// 	menu.set_top_prompt("Just Consider Our Seriously Delicious Ice Cream Flavors for Summer ");
// 	menu.set_bottom_prompt("Enter the number of your Happiness Flavor: ");
// 	menu.push_back("Bacon ice cream!");
// 	menu.push_back("Strawberry ice cream");
// 	menu.push_back("Vanilla ice cream");
// 	menu.push_back("Chocolate chip cookie dough ice cream");
// 	choice = menu.read_option_number();
// 	cout << "you entered: " << choice << endl;
// 	cout << "--------------------" << endl;
//
// 	return 0; // from <cstddef>
// }
