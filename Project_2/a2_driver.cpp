#include <string>
#include<iostream>
using namespace std;
#include "Led.h"

int main(int argc, char * argv[]){
  string filename; // an empty filename
  switch (argc) { // determine the filename 11
    case 1: // no file nameb
      break;
    case 2: filename = argv[1]; // initialize filename from argument
      break;
    default: cout << ("too many arguments - all discarded") << endl;
      break;
	}
  Led led(filename); // create an editor named led
  led.run(); // run our edito
  return 0; // done
}
