#makefile

CXX := g++ #compilier flag

CXXFLAGS := -std=c++11 -pthread -ggdb -O0 -Wall #compilier options

obj := main.o fileRAII.o #$(wildcard *.o) 

TheGreatEncryptor: $(obj)
	$(CXX) $(CXXFLAGS) -o TheGreatEncryptor $(obj)

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

fileRAII.o: fileRAII.cpp fileRAII.h
	$(CXX) $(CXXFLAGS) -c fileRAII.cpp

#ExceptionHandlers.o : ExceptionHandlers.h #for exception handler class
#	$(CXX) $(CXXFLAGS) -c ExceptionHandlers.cpp

#need to add for hash class

.PHONY: clean

clean:
	rm -f TheGreatEncryptor $(obj)
