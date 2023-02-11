CC=g++
CFLAGS=-Wall
SOURCES = $(wildcard *.cpp)
EXECS = $(SOURCES:%.cpp=%)

all: $(EXECS)

Homework3.1:	Homework3.1.cpp c_lib/rng.c
	$(CC) $^ -o $@

clean:
	rm $(EXECS)