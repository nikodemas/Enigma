#include <iostream>
#include <fstream>
#include <string>
#include "errors.h"
#include "plugboard.h"


using namespace std;

  
int Plugboard::init_plugboard_configuration(char* filename) {
  ifstream instream_plugboard;
  string number;
  int int_number, first_number, second_number, count = 0;
  instream_plugboard.open(filename);
  if (instream_plugboard.fail()) {
    cerr << "Error encountered while opening plugboard configuration file: "
	 << filename << endl;
    return ERROR_OPENING_CONFIGURATION_FILE;
  }
  instream_plugboard >> number;
  while (!instream_plugboard.fail()) {
    for (unsigned int i = 0; i < number.length(); i++) {
      if (isdigit(number[i]) == false) {
	cerr << "Non-numeric character in plugboard file " << filename << endl;
	return NON_NUMERIC_CHARACTER;
      }
    }
    int_number = stoi(number);
    if (int_number < 0 || int_number > 25) {
      cerr << "Invalid integer character (greater than 25 or less than 0) for "
	   << "mapping in plugboard file " << filename << endl;
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
	     << " in plugboard file " << filename << endl;
	return IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
      }
    }
    count++;
    instream_plugboard >> number;
  }
  if (count%2 == 1 || count > 26) {
    /* check that there are even number of mappings provided
       and that fewer than the alphabet size */
    cerr <<  "Incorrect number of parameters in plugboard file " << filename
	 << endl;
    return INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
  }
  instream_plugboard.close();
  return NO_ERROR;
}


int Plugboard::encrypt(int int_char) {
  return configuration[int_char];
}


Plugboard::Plugboard () {
  for (int i = 0; i < 26; i++) {
    configuration[i] = i;
  }
}
