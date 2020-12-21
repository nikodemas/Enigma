#include <iostream>
#include <fstream>
#include <string>
#include "errors.h"
#include "reflector.h"


using namespace std;

  
int Reflector::init_reflector_configuration(char* filename) {
  ifstream instream_reflector;
  string number;
  int int_number, first_number, second_number, count = 0;
  instream_reflector.open(filename);
  if (instream_reflector.fail()) {
    cerr << "Error encountered while opening reflector configuration file: "
	 << filename << endl;
    return ERROR_OPENING_CONFIGURATION_FILE;
  }
  instream_reflector >> number;
  while (!instream_reflector.fail()) {
    for (unsigned int i = 0; i < number.length(); i++) {
      if (isdigit(number[i]) == false) {
	cerr << "Non-numeric character in reflector file "
	     << filename << endl;
	return NON_NUMERIC_CHARACTER;
      }
    }
    int_number = stoi(number);
    if (int_number < 0 || int_number > 25) {
      cerr << "Invalid integer character (greater than 25 or less than 0) for "
	   << "mapping in reflector file " << filename << endl;
      return INVALID_INDEX;
    }      
    if (count%2 == 0) {// 'remembering' config numbers in pairs for later checks
      first_number = int_number;
    } else {
      second_number = int_number;
    }
    if (count > 0 && count%2 == 1) {
      /* check that the pair isnt mapping to itself
	 and that it wasnt mapped before */
      if (first_number != second_number
	  && configuration[first_number] == first_number
	  && configuration[second_number] == second_number) {
	configuration[first_number] = second_number;
	configuration[second_number] = first_number;
      } else {
	cerr << "Invalid mapping of " << first_number << " to " << second_number
	     << " in reflector file " << filename << endl;
	return INVALID_REFLECTOR_MAPPING;
      }
    }
    count++;
    instream_reflector >> number;
  }
  if (count%2 == 1) {
    cerr << "Incorrect (odd) number of parameters in reflector file "
	 << filename << endl;
    return INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
  } else if (count < 26) {
    cerr << "Insufficient number of mappings in reflector file: "
	 << filename << endl;
    return INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
  }
  instream_reflector.close();
  return NO_ERROR;
}


int Reflector::encrypt(int int_char) {
  return configuration[int_char];
}


Reflector::Reflector() {
  for (int i = 0; i < 26; i++) {
    configuration[i] = i;
  }
}
    

