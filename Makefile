prog: main.o Preference.o
	g++ -std=c++11 -g -Wall main.o Preference.o -o prog

main.o: main.cpp Preference.h
	g++ -std=c++11 -g -Wall -c main.cpp

Preference: Preference.cpp Preference.h
	g++ -std=c++11 -g -Wall -c Preference.cpp

clean:
	rm *.o prog