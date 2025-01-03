# compile the test tool

OBJ:=fast_sqrt.o test_fast_sqrt.o
CFLAGS:=-Wall
LDLIBS:=-lm

all: test_fast_sqrt

test_fast_sqrt: $(OBJ)

.PHONY: clean
clean:
	-rm $(OBJ) test_fast_sqrt