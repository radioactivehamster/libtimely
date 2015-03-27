STD     = c11
SRC     = $(wildcard src/*/*.c)
OBJS    = $(SRC:.c=.o)
CFLAGS ?= -std=$(STD)
CFLAGS += -pedantic -O2 -Iinclude
CFLAGS += -Wall -Wextra -Wno-overlength-strings -Wswitch-default

test: test.c $(OBJS)
	$(CC) $(CFLAGS) $^ -o "$@.out" && echo "\n" && ./"$@.out"

lab: _lab.c $(OBJS)
	$(CC) $(CFLAGS) $^ -o lab.out && echo "\n" && ./lab.out

clean:
	rm -f $(OBJS) test

%.o: %.c
	$(CC) $< -c -o $@ $(CFLAGS)

retest: clean test


# .PHONEY: clean test
