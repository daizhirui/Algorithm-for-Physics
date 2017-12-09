P=status.o histogram.o out.cpp
CC=gcc
CXX=g++
CXXFLAGS=-std=c++11 -O3
LIBS=-lm


p:$(P)
	$(CXX) $(P) -o $@ $(LIBS) $(CXXFLAGS)



########
clean:
	rm -f *.o

cleanall:clean
	rm -f p



########

.SUFFIXES: .c .cpp .o
.c.o:
	$(CC) $(CFLAGS) -c $<
.cpp.o:
	$(CXX) $(CXXFLAGS) -c $<
