#makefile

CXX := g++ #compilier flag

CXXFLAGS := -std=c++11 -pthread -ggdb -O0 # -Wall #compilier options

obj := fileRAII.o ExceptionHandlers.o HashClass.o EncryptionClass.o main.o #$(wildcard *.o) 


TheGreatEncryptor: $(obj)
	$(CXX) $(CXXFLAGS) -o TheGreatEncryptor $(obj)

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

fileRAII.o: fileRAII.cpp fileRAII.h
	$(CXX) $(CXXFLAGS) -c fileRAII.cpp

ExceptionHandlers.o : ExceptionHandlers.cpp #for exception handler class
	$(CXX) $(CXXFLAGS) -c ExceptionHandlers.cpp

HashClass.o : HashClass.cpp
	$(CXX) $(CXXFLAGS) -c HashClass.cpp

EncryptionClass.o : EncryptionClass.cpp
	$(CXX) $(CXXFLAGS) -c EncryptionClass.cpp

#need to add for hash class

.PHONY: clean

clean:
	rm -f TheGreatEncryptor $(obj)
