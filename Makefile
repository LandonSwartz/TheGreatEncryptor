#makefile

CXX := g++ #compilier flag

CXXFLAGS := -std=c++11 -pthread -ggdb -O0 -Wall -pthread #compilier options

obj := main.o fileRAII.o

TheGreatEncryptor: $(obj)
	$(CXX) $(CXXFLAGS) TheGreatEncryptor $(obj)

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

fileRAII.o: fileRAII.cpp fileRAII.h
	$(CXX) $(CXXFLAGS) -c fileRAII.cpp 

.PHONY: clean

clean:
	rm -f TheGreatEncryptor $(obj)
