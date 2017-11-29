LIBS = MyVector
BINS = testMyVector
MYVECTOR_SRC = MyVector.cpp
MYVECTOR_OBJ = $(MYVECTOR_SRC:.cpp=.o)
TESTMYVECTOR_SRC = testMyVector.cpp
TESTMYVECTOR_OBJ = $(TESTMYVECTOR_SRC:.cpp=.o)

CC = gcc
CXX = g++
AR = ar
CFLAGS = -Wall
CXXFLAGS = -Wall -std=c++11
LIBFLAG = -I ./ -L ./ -l$(LIBS)
ARFLAG = cr

all:$(BINS)

lib:$(LIBS)

testMyVector:$(LIBS) $(TESTMYVECTOR_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(TESTMYVECTOR_OBJ) $(LIBFLAG)
MyVector:$(MYVECTOR_OBJ)
	$(AR) $(ARFLAG) lib$(LIBS).a $(MYVECTOR_OBJ)
test:
	./testMyVector
upload:
	scp -r ../HW20171103 st15307110218@10.40.9.67:Homework/
download:
	scp -r st15307110218@10.40.9.67:Homework/HW20171103 ../from_server
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
