CONST=status.o const_t.o
DIF=status.o dif_t.o
BINS=const dif
CC=gcc
CXX=g++
LIBS=-lm

all:$(BINS)

const:$(CONST)
	$(CXX) $(CONST) -o $@ $(LIBS) $(CXXFLAGS)

dif:$(DIF)
	$(CXX) $(DIF) -o $@ $(LIBS) $(CXXFLAGS)


########
clean:
	rm -f *.o

cleanall:clean
	rm -f $(BINS)



########

.SUFFIXES: .c .cpp .o
.c.o:
	$(CC) $(CFLAGS) -c $<
.cpp.o:
	$(CXX) $(CXXFLAGS) -c $<
