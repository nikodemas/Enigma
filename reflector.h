#ifndef REFLECTOR_H
#define REFLECTOR_H

class Reflector {
  /* array representing reflector mapping configuration */
  int configuration[26];

public:
  /* function that initializes reflector configuration from the given file and
     returns error code (or no error if initialization was successful) */
  int init_reflector_configuration(char* filename);

  /* function that returns reflector mapping of the letter represented by the
     integer */ 
  int encrypt(int int_char);

  /* constructor to initialize reflector configuration where each letter is
     mapped to itself */
  Reflector();
    
};

#endif
