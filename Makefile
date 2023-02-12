CC=g++
CFLAGS=-Wall
SOURCES = $(wildcard *.cpp)
EXECS = $(SOURCES:%.cpp=%)

all: $(EXECS)

Homework3.1:	Homework3.1.cpp c_lib/rng.c
	$(CC) $^ -o $@

Homework3.2:	Homework3.2.cpp c_lib/rvgs.c c_lib/rngs.c
	$(CC) $^ -o $@
	
Homework3.3:	Homework3.3.cpp c_lib/rng.c
	$(CC) $^ -o $@
	
Homework3.4:	Homework3.4.cpp c_lib/rvgs.c c_lib/rngs.c
	$(CC) $^ -o $@

clean:
	rm $(EXECS)