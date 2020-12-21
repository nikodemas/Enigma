#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "errors.h"
#include "enigma.h"
#include "rotor.h"
#include "reflector.h"
#include "plugboard.h"


using namespace std;


int Enigma::check_position_file(char* filename) {
  ifstream instream_rot_position;
  string number;
  int int_number, count = 0;
  instream_rot_position.open(filename);
  if (instream_rot_position.fail()) {
    cerr << "Error encountered while opening rotor positions configuration"
	 << " file: " << filename;
    return ERROR_OPENING_CONFIGURATION_FILE;
  }
  instream_rot_position >> number;
  while (!instream_rot_position.fail()) {
    for (unsigned int i = 0; i < number.length(); i++)
      if (isdigit(number[i]) == false) {
	cerr << "Non-numeric character in rotor positions file "
	     << filename << endl;
	return NON_NUMERIC_CHARACTER;
      }
    int_number = stoi(number);
    if (int_number < 0 || int_number > 25) {
      cerr << "Invalid integer character (greater than 25 or less than 0) in"
	   << " rotor positions file " << filename << endl;
      return INVALID_INDEX;
    }
    count++;
    instream_rot_position >> number;
  }
  if (count < num_of_rotors) {//checking if all the rotors have position defined
    cerr << "No starting position for rotor " << count
	 << " in rotor position file: " << filename << endl;
    return NO_ROTOR_STARTING_POSITION;
  }
  instream_rot_position.close();
  return NO_ERROR;
}


void Enigma::link_rotors() {
  for (int i = 0; i < num_of_rotors - 1; i++) {
    rotors[i+1]->set_rotor_to_left(rotors[i]);
    rotors[i]->set_rotor_to_right(rotors[i+1]);
  }
}


int Enigma::init_enigma(int argc, char** argv) {
  ifstream instream_rot_position;
  int rotor_pos, return_code = NO_ERROR;
  if (argc < MIN_ARG_COUNT) {
    cerr << "usage: enigma plugboard-file reflector-file (<rotor-file>)* "
	 << "rotor-positions" << endl;
    return INSUFFICIENT_NUMBER_OF_PARAMETERS;
  }
  num_of_rotors = argc - 4;
  plugboard = new Plugboard;
  return_code = plugboard->init_plugboard_configuration(argv[1]);
  if (return_code > 0) {//checking if plugboard was initialized
    return return_code;
  }
  reflector = new Reflector;
  return_code = reflector->init_reflector_configuration(argv[2]);
  if (return_code > 0) {//checking if reflector was initialized
    return return_code;
  }
  return_code = check_position_file(argv[argc-1]);
  if (return_code > 0) {//checking the position file
    return return_code;
  }
  instream_rot_position.open(argv[argc-1]);
  instream_rot_position >> rotor_pos;
  for (int i = 0; i < num_of_rotors; i++) {
    Rotor* rotor_tmp = new Rotor;
    return_code = rotor_tmp->init_rotor_configuration(argv[3+i]);
    if (return_code > 0) {//checking if each rotor is initialized
      return return_code;
    }
    rotor_tmp->set_position(rotor_pos);
    rotors.push_back(rotor_tmp);
    instream_rot_position >> rotor_pos;
  }
  instream_rot_position.close();
  if (num_of_rotors > 1) {//linking the rotors if there are enough to link
    link_rotors();
  }
  return return_code;
}


int Enigma::encrypt() {
  char character;
  cin >> ws >> character;
  while (!cin.fail()) {
    if (character < 'A' || character > 'Z') {
      cerr << character << " is not a valid input character (input characters"
	   << " must be upper case letters A-Z)!" << endl;
      return INVALID_INPUT_CHARACTER;
    }
    int int_character = (int)(character - 'A');
    if (num_of_rotors > 0) {//check if there are any rotors for encryption
      rotors[num_of_rotors-1]->rotate();
      int_character = plugboard->encrypt(int_character);
      int_character = rotors[num_of_rotors-1]->encrypt_left(int_character);
      int_character = reflector->encrypt(int_character);
      int_character = rotors[0]->encrypt_right(int_character);
      int_character = plugboard->encrypt(int_character);
    } else {
      int_character = plugboard->encrypt(int_character);
      int_character = reflector->encrypt(int_character);
      int_character = plugboard->encrypt(int_character);
    }
    character = (char) (int_character + (int) 'A');
    cout << character;
    cin >> ws >> character;
  }
  return NO_ERROR;
}


Enigma::~Enigma() {
  if (!rotors.empty()) {//checking if there were any rotors initialized
    for (int i = 0; i < num_of_rotors; i++) {
      delete rotors[i];
    }
  }
  if (plugboard != nullptr) {
    delete plugboard;
  }
  if (reflector != nullptr) {
    delete reflector;
  }
}
