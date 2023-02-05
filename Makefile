CC=g++
CFLAGS=-Wall
SOURCES = $(wildcard *.cpp)
EXECS = $(SOURCES:%.cpp=%)

all: $(EXECS)

clean:
	rm $(EXECS)