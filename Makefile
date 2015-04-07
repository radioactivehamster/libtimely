STD    := c11
SRC     = $(wildcard src/*/*.c)
OBJDIR ?= .objects/
OBJSRC  = $(SRC:.c=.o)
OBJS   := $(addprefix $(OBJDIR), $(notdir $(OBJSRC)))
CFLAGS ?= -std=$(STD) -O3 -pedantic -Wall -Wextra -Wswitch-default -Iinclude
RIMRAF ?= rm -rf

# @link https://www.gnu.org/software/make/manual/html_node/File-Name-Functions.html
# @link http://www.gnu.org/prep/standards/standards.html#Makefile-Conventions

# The first target listed acts as the default so it is named thusly for semantics.
default:
	@ $(CC) $(CFLAGS) test.c && ./a.out

check-test:
	@$(CC) $(CFLAGS) -o check-iso8601-test "tests/check-iso8601.c" -lcheck $(OBJS)

minunit-test:
	@$(CC) $(CFLAGS) -o minunit-iso8601-test "tests/minunit-iso8601.c" $(OBJS)

%.o: %.c
	@if test ! -d $(OBJDIR); then echo "Making dir..."; mkdir $(OBJDIR); fi
	@ #$(CC) $(CFLAGS) -MM $< -c -o $(OBJDIR)$(notdir $@)
	@$(CC) $(CFLAGS) $< -c -o $(OBJDIR)$(notdir $@)

clean:
	@$(RIMRAF) $(OBJS) $(OBJDIR) $(OBJSRC) test.out $(wildcard *-test)

rebuild: clean default

.PHONEY: default clean
