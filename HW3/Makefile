mixed: main.o mixed.o
	g++ -o mixed main.o mixed.o

main.o: main.cpp mixed.h
	g++ -c main.cpp

mixed.o: mixed.cpp mixed.h
	g++ -c mixed.cpp

clean:
	rm *.o mixed
