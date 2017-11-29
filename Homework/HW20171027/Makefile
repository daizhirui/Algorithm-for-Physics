SRC = MyString.cpp
MYSTRING = $(SRC:.cpp = .o)
BINS = testMyString

CC = gcc
CXX = g++
CFLAGS = -Wall

all:$(BINS)

testMyString:$(MYSTRING)
	$(CXX) $(CFLAGS) -o $@ $(MYSTRING)
test:
	./testMyString
upload:
	scp -r ../HW20171027 st15307110218@10.40.9.67:Homework/
download:
	scp -r st15307110218@10.40.9.67:Homework/HW20171027 ../from_server
clean:
	rm -f *.o
cleanall: clean
	rm -f $(BINS)

#########################################
.SUFFIXES: .f90 .f .o .mod .F .c .cpp
.c.o:
	$(CC) $(CFLAGS) -c $<

.cpp.o:
	$(CXX) $(CFLAGS) -c $<
