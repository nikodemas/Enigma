#ifndef ENIGMA_H
#define ENIGMA_H

#include <vector>
#include "reflector.h"
#include "rotor.h"
#include "plugboard.h"

const int MIN_ARG_COUNT = 4;

class Enigma {
  /* pointer to the plugboard of enigma */
  Plugboard* plugboard = nullptr;
  
  /* pointer to the reflector of enigma */
  Reflector* reflector = nullptr;

  /* vector with pointers to rotors of enigma */
  std::vector<Rotor*> rotors;

  int num_of_rotors = 0;

  /* helper function that links its rotors with each other */
  void link_rotors();

  /* function that checks if the file of initial enigma rotors' position
     is valid. returns error code in case file is not correct */
  int check_position_file(char* filename);
  
public:
  /* function that initializes enigma configuration from the command line
     arguments and returns error code (or no error if initialization was
     successful) */
  int init_enigma(int argc, char** argv);

  /* function that encrypts the message received from standard input and
     sends it to standard output. returns error code (or no error if
     initialization was successful) */
  int encrypt();

  /* destructor that deletes enigma's objects created on the heap */
  ~Enigma();
  
};

#endif
