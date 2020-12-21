#include "enigma.h"


int main(int argc, char** argv) { 
  int return_code = 0;
  Enigma enigma;
  return_code = enigma.init_enigma(argc, argv);
  if (return_code > 0) {
    return return_code;
  }  
  return enigma.encrypt();
} 
