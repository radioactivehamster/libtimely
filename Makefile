STD         := c11
SRC          = $(wildcard src/*/*.c)
OBJDIR      ?= .objects/
OBJSRC       = $(SRC:.c=.o)
TESTSBINDIR ?= tests/bin/
OBJS        := $(addprefix $(OBJDIR), $(notdir $(OBJSRC)))
CFLAGS      ?= -std=$(STD) -O3 -pedantic -Wall -Wextra -Wswitch-default -Iinclude
RIMRAF      ?= rm -rf

# @link https://www.gnu.org/software/make/manual/html_node/File-Name-Functions.html
# @link http://www.gnu.org/prep/standards/standards.html#Makefile-Conventions

# The first target listed acts as the default so it is named thusly for semantics.
default:
	@ $(CC) $(CFLAGS) test.c && ./a.out

test:
	@if test ! -d $(TESTSBINDIR); then mkdir $(TESTSBINDIR); fi
	@$(CC) $(CFLAGS) -o "$(TESTSBINDIR)libtimely" "tests/libtimely.c" -lcheck $(OBJS)
	@./"$(TESTSBINDIR)libtimely"

%.o: %.c
	@if test ! -d $(OBJDIR); then mkdir $(OBJDIR); fi
	@ #$(CC) $(CFLAGS) -MM $< -c -o $(OBJDIR)$(notdir $@)
	@$(CC) $(CFLAGS) $< -c -o $(OBJDIR)$(notdir $@)

clean:
	@$(RIMRAF) $(OBJS) $(OBJDIR) $(OBJSRC) $(TESTSBINDIR) test.out $(wildcard *-test)

rebuild: clean default

.PHONEY: default test clean
