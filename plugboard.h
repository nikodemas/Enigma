#ifndef PLUGBOARD_H
#define PLUGBOARD_H

class Plugboard {
  /* array representing plugboard mapping configuration */
  int configuration[26];

public:
  /* function that initializes plugboard configuration from the given file and
     returns error code (or no error if initialization was successful) */
  int init_plugboard_configuration(char* filename);

  /* function that returns plugboard mapping of the letter represented by the
     integer */ 
  int encrypt(int int_char);
  
  /* constructor to initialize plugboard configuration where each letter is
     mapped to itself */
  Plugboard ();
  
};
 
#endif
