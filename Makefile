CC      = gcc
CFLAGS = -Wall -Wextra -std=c11 -I/opt/homebrew/include
TESTFLAGS = -lcriterion

SRC     = strgPtr.c cse_caesar.c
OBJ     = $(SRC:.c=.o)

TEST_SRC = tests/test_strg.c tests/test_caesar.c
TEST_OBJ = $(TEST_SRC:.c=.o)

.PHONY: all test clean

all: $(OBJ)

test: $(OBJ) $(TEST_OBJ)
	$(CC) $(CFLAGS) -o tests_runner $(OBJ) $(TEST_OBJ) -L/opt/homebrew/lib -lcriterion
	./tests_runner

clean:
	rm -f *.o tests/*.o tests_runner hw4