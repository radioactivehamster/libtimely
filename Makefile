STD     = c11
SRC     = $(wildcard src/*/*.c)
OBJS    = $(SRC:.c=.o)
CFLAGS ?= -std=$(STD)
CFLAGS += -pedantic -O2 -Iinclude
CFLAGS += -Wall -Wextra -Wno-overlength-strings -Wswitch-default

test: $(OBJS)
	$(CC) $(CFLAGS) -o $(@).out $(@).c $(OBJS) && echo "\n" && ./$(@).out
#	$(CC) $(CFLAGS) $^ -o "$@.out" $(OBJS) && echo "\n" && ./"$@.out"

%.o: %.c
	$(CC) $< -c -o $@ $(CFLAGS)

lab: _lab.c $(OBJS)
	$(CC) $(CFLAGS) $^ -o lab.out && echo "\n" && ./lab.out

clean:
	rm -f $(OBJS) test.out

retest: clean test

.PHONEY: clean
