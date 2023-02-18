CC=g++
CFLAGS=-Wall
SOURCES = $(wildcard *.cpp)
EXECS = $(SOURCES:%.cpp=%)

all: $(EXECS)

Homework4.1: Homework4.1.cpp 
	$(CC) $(CFLAGS) -o $@ $^

Homework4.2: Homework4.2.cpp checkarg.cpp c_lib/rvgs.c c_lib/rngs.c 
	$(CC) $(CFLAGS) -o $@ $^

Homework4.3: Homework4.3.cpp checkarg.cpp c_lib/rvgs.c c_lib/rngs.c 
	$(CC) $(CFLAGS) -o $@ $^
	
clean:
	rm $(EXECS)