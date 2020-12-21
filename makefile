enigma: main.o enigma.o reflector.o rotor.o plugboard.o
	g++ -g -Wall main.o enigma.o reflector.o rotor.o plugboard.o -o enigma

main.o: main.cpp enigma.h
	g++ -Wall -g -c main.cpp

enigma.o: enigma.cpp enigma.h reflector.h rotor.h plugboard.h errors.h
	g++ -Wall -g -c enigma.cpp

reflector.o: reflector.cpp reflector.h errors.h
	g++ -Wall -g -c reflector.cpp

rotor.o: rotor.cpp rotor.h errors.h
	g++ -Wall -g -c rotor.cpp

plugboard.o: plugboard.cpp plugboard.h errors.h
	g++ -Wall -g -c plugboard.cpp

clean:
	rm -f *.o enigma
