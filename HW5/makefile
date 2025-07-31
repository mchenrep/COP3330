mystring: main.o mystring.o
	g++ -o mystring main.o mystring.o

main.o: main.cpp mystring.h
	g++ -c main.cpp

mystring.o: mystring.cpp mystring.h
	g++ -c mystring.cpp

clean:
	rm *.o mystring
