#ifndef ROTOR_H
#define ROTOR_H

#include <vector>

class Rotor {
  /* array representing rotor mapping configuration going forward */
  int configuration[26];
  
  /* array representing rotor mapping configuration going back */
  int reverse_configuration[26];

  
  std::vector<int> notches;

  /* pointers pointing to the 'neighbour' rotors */ 
  Rotor *rotor_to_right = nullptr;

  Rotor *rotor_to_left = nullptr;


  int num_of_notches = 0;
  
  /* position of a rotor - 0 for 'A', 1 for 'B' and etc. */
  int position = 0;
  
  /* helper function to check whether current position is at notch */
  bool is_notch();

  /* helper function to check whether input was already previously mapped */
  bool is_used(int count, int int_number);

public:
  /* setters to set the 'neighbour' rotors */
  void set_rotor_to_right(Rotor* right_rotor);

  void set_rotor_to_left(Rotor* left_rotor);

  
  /* setter to set initial position of a rotor */
  void set_position(int position);

  /* function that returns rotor mapping of the letter represented by the
     integer going forward */ 
  int encrypt_left(int int_char);
  
  /* function that returns rotor mapping of the letter represented by the
     integer going back */ 
  int encrypt_right(int int_char);

  /* function that initializes rotor configuration from the given file and
     returns error code (or no error if initialization was successful) */
  int init_rotor_configuration(char* filename);

  /* function that rotates the rotor and starts rotating the next one if the
     notch is hit */
  void rotate();

  /* constructor to initialize rotor configuration where each letter is mapped
     to itself */
  Rotor ();

};

#endif
