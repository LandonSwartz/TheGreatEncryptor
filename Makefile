CC = g++
CPPFLAGS =  # cpp compilier flags

obj = main.o fileRAII.o #read in object files

TheGreatEncryptor: $(obj) #makes app
	g++ -o -pthread TheGreatEncryptor $(obj)

main.o: main.cpp #making object for main.o
	g++ -c main.cpp

fileRAII.o: fileRAII.cpp fileRAII.h #making object for fileRAII class
	g++ -c fileRAII.cpp


.PHONY: clean
clean: #cleaning house 
	rm TheGreatEncryptor $(obj)
