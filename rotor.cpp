#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "errors.h"
#include "rotor.h"


using namespace std;


bool Rotor::is_notch() {
  for (int i = 0; i < num_of_notches; i++) {
    if (notches[i] == position) {
      return true;
    }
  }
  return false;
}


bool Rotor::is_used(int count, int int_number) {
  for (int i = 0; i < count; i++) {
    if (configuration[i] == int_number) {
      return false;
    }
  }
  return true;
}


void Rotor::set_rotor_to_right(Rotor* right_rotor) {
  this->rotor_to_right = right_rotor;
}


void Rotor::set_rotor_to_left(Rotor* left_rotor) {
  this->rotor_to_left = left_rotor;
}


void Rotor::set_position(int position) {
  this->position = position;
}

/* after rotating to the 26th letter rotor
   with the next step starts again from the first position
   so the new position of mapping  needs to be derived this way.
   both functions (left and right) after mapping the letter send it
   for the mapping to the next rotor. */
int Rotor::encrypt_left(int int_char) {
  int new_position =
    (configuration[(position + int_char)%26] - position + 26)%26;
  if (rotor_to_left == nullptr) {
    return new_position;
  } else {
    return rotor_to_left->encrypt_left(new_position);
  }
}


int Rotor::encrypt_right(int int_char) {
  int new_position =
    (reverse_configuration[(position + int_char)%26] - position + 26)%26;
  if (rotor_to_right == nullptr) {
    return new_position;
  } else {
    return rotor_to_right->encrypt_right(new_position);
  }
}


int Rotor::init_rotor_configuration(char* filename) {
  ifstream instream_rotor;
  string number;
  int int_number, count = 0;
  instream_rotor.open(filename);
  if (instream_rotor.fail()) {
    cerr << "Error encountered while opening rotor configuration file: "
	 << filename << endl;
    return ERROR_OPENING_CONFIGURATION_FILE;
  }
  instream_rotor >> number;
  while (!instream_rotor.fail()) {
    for (unsigned int i = 0; i < number.length(); i++) {
      if (isdigit(number[i]) == false) {
	cerr << "Non-numeric character for mapping in rotor file "
	     << filename << endl;
	return NON_NUMERIC_CHARACTER;
      }
    }
    int_number = stoi(number);
    if (int_number < 0 || int_number > 25) {
      cerr << "Invalid integer character (greater than 25 or less than 0) "
	   << "for mapping in rotor file " << filename << endl;
      return INVALID_INDEX;
    }
    if (count < 26) {
      if (is_used(count, int_number)) {//check if the input wasnt mapped before
	configuration[count] = int_number;
	reverse_configuration[int_number] = count;
      } else {
	cerr << "Invalid mapping of input " << count << " to output "
	     << int_number << " in rotor file " << filename << endl;
	return INVALID_ROTOR_MAPPING;
      }
      count++;
      instream_rotor >> number;
    } else {//after reading 26 mappings the rest of the numbers are the notches
      notches.push_back(int_number);
      num_of_notches++;
      instream_rotor >> number;
    }
  }
  if (count < 26) {
    cerr << "Not all inputs mapped in rotor file: " << filename << endl;
    return INVALID_ROTOR_MAPPING;
  }
  instream_rotor.close();
  return NO_ERROR;
}

/* during each rotation position moves by one. because rotor rotates in circles,
   so when the 26th position is reached, then the next one is first again.
   also if the rotor hits the notch, then the next rotor is rotated as well  */
void Rotor::rotate() {
  position = (position < 25)? (position + 1) : (position + 1)%26;
  if (is_notch() && rotor_to_left != nullptr) {
    rotor_to_left->rotate();
  }
}


Rotor::Rotor () {
  for (int i = 0; i < 26; i++) {
    configuration[i] = i;
    reverse_configuration[i] = i;
  }
}
