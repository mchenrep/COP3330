studentlist: menu.o studentlist.o
	g++ -o studentlist menu.o studentlist.o

menu.o: menu.cpp studentlist.h
	g++ -c menu.cpp

studentlist.o: studentlist.cpp studentlist.h
	g++ -c studentlist.cpp

clean:
	rm *.o studentlist  
