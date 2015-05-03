liyu:CarpNote.o carpNote_mysql.o encapsulation_mysql.o fileOP.o
	g++ -o liyu CarpNote.o carpNote_mysql.o encapsulation_mysql.o fileOP.o -lpthread -lmysqlclient
CarpNote.o:CarpNote.cpp CarpNote.h
	g++ -c -g CarpNote.cpp
carpNote_mysql.o:carpNote_mysql.cpp carpNote_mysql.h
	g++ -c -g carpNote_mysql.cpp
encapsulation_mysql.o:encapsulation_mysql.cpp encapsulation_mysql.h
	g++ -c -g encapsulation_mysql.cpp
fileOP.o:fileOP.cpp fileOP.h
	g++ -c -g fileOP.cpp
clean:
	rm  *.o *.h.gch
