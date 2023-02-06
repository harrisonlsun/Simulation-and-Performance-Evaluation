CC=g++
CFLAGS=-Wall
SOURCES = $(wildcard *.cpp)
EXECS = $(SOURCES:%.cpp=%)

all: $(EXECS)

Homework2.3:	Homework2.3.cpp c_lib/rng.c
	$(CC) $^ -o $@

Homework2.4:	Homework2.4.cpp c_lib/rng.c
	$(CC) $^ -o $@

clean:
	rm $(EXECS)
