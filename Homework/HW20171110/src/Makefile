BINS = stringCount
SRC = main.cpp StrMap.cpp terminal_IO.cpp
OBJ = $(SRC:.cpp=.o)

CC = gcc
CXX = g++
CFLAGS = -Wall
CXXFLAGS = -Wall -std=c++11

all:$(BINS)

stringCount:$(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ)
clean:
	rm -f *.o *.a
cleanall: clean
	rm -f $(BINS)

#########################################
.SUFFIXES: .f90 .f .o .mod .F .c .cpp
.c.o:
	$(CC) $(CFLAGS) -c $<

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $<
