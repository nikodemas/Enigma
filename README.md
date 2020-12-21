# Enigma
*implementation of an Enigma coding machine*

Enigma is the common name for the coding machine used by German forces in the Second World War. Two machines set up in the same way allowed the sending of a message securely between their users.

Enigma machine is configured by giving in the configuration files as the command line arguments. 
The first configuration file specifies the wiring map for the plugboard, the second file specifies the wiring map for the reflector, the next files specifies the wiring maps for the rotors and the last file specifies the rotors’ initial starting positions.

Machine then encrypts (or decrypts) messages provided on the standard input stream, outputting the encrypted (or decrypted) message on the standard output stream.

In order to run the machine firstly compile the code by running `make` in this directory. Then run the executable `enigma` together with the configuration parameters, e.g.
```bash
./enigma plugboards/I.pb reflectors/I.rf rotors/I.rot rotors/II.rot rotors/III.rot rotors/I.pos
```
Program will then (in a loop) read input characters from the standard input stream. White-space characters (space, tab, carriage-return and newline) are discarded and upper case characters (A-Z) are encrypted by the machine with the resulting upper case character output to the standard output stream. All other characters will cause the program to output an informative message to the standard error stream and exit.

More information can be found in the *specification.pdf*.
