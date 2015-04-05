STD    := c11
SRC     = $(wildcard src/*/*.c)
OBJDIR ?= .objects/
OBJSRC  = $(SRC:.c=.o)
OBJS   := $(addprefix $(OBJDIR), $(notdir $(OBJSRC)))
CFLAGS ?= -std=$(STD) -pedantic -O2 -Iinclude
CFLAGS += -Wall -Wextra -Wno-overlength-strings -Wswitch-default
RIMRAF ?= rm -rf

# @link https://www.gnu.org/software/make/manual/html_node/File-Name-Functions.html

test: $(OBJSRC)
	@$(CC) $(CFLAGS) $(@).c $(OBJS) -o $(@).out && ./$(@).out

check-test:
	@$(CC) $(CFLAGS) -o check-iso8601-test "tests/check-iso8601.c" -lcheck $(OBJS)

minunit-test:
	@$(CC) $(CFLAGS) -o minunit-iso8601-test "tests/minunit-iso8601.c" $(OBJS)

%.o: %.c
	@if test ! -d $(OBJDIR); then echo "Making dir..."; mkdir $(OBJDIR); fi
	@ #$(CC) $(CFLAGS) -MM $< -c -o $(OBJDIR)$(notdir $@)
	@$(CC) $(CFLAGS) $< -c -o $(OBJDIR)$(notdir $@)

lab: _lab.c
	@$(CC) $(CFLAGS) $^ -o lab.out && echo "\n" && ./lab.out

clean:
	$(RIMRAF) $(OBJS) $(OBJDIR) $(OBJSRC) test.out $(wildcard *-test)

retest: clean test

.PHONEY: clean
