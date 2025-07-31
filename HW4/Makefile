playlist: menu.o playlist.o song.o
	g++ -o playlist menu.o playlist.o song.o
menu.o: menu.cpp playlist.h
	g++ -c menu.cpp
playlist.o: playlist.cpp playlist.h
	g++ -c playlist.cpp
song.o: song.cpp song.h
	g++ -c song.cpp
clean:
	rm *.o playlist
