RIMRAF     = $(RM) -f
STD        = -std=C11

# > If there are C compiler options that must be used for proper compilation of
# > certain files, do not include them in CFLAGS. Users expect to be able to
# > specify CFLAGS freely themselves. Instead, arrange to pass the necessary
# > options to the C compiler independently of CFLAGS, by writing them
# > explicitly in the compilation commands or by defining an implicit rule [...]
CFLAGS     = $(STD) -02 -pedantic -Wall -Wextra
ALL_CFLAGS = -Iinclude $(CFLAGS)

PKGNAME = libtimely

# Common prefix for installation directories.
# > Please make these install-format targets invoke the commands for the format
# > target, for example, by making format a dependency.
# <https://www.gnu.org/prep/standards/standards.html#Directory-Variables>
prefix      = /usr/local
datarootdir = $(prefix)/share
includedir  = $(prefix)/include
datadir     = $(datarootdir)
docdir      = $(datarootdir)/doc/$(PKGNAME)
htmldir     = $(docdir)
infodir     = $(datarootdir)/info
mandir      = $(datarootdir)/man
man3dir     = $(mandir)/man3
man3ext     = .3

# <https://www.gnu.org/software/make/manual/html_node/File-Name-Functions.html>
# <https://www.gnu.org/prep/standards/standards.html#Makefile-Conventions>
# <https://www.gnu.org/prep/standards/standards.html#Releases>

# ---------------------

# testdir = tests
# GROFF = groff -mdoc -T ascii -E
GROFF = groff -mdoc -T utf8 -E

# ---------------------

# The first target listed acts as the default so it is named thusly for semantics.
# default:
all:
	@ #echo $(test -w /usr/local)
	@ #echo $(testno)
	@ #echo $(HOME)
	@echo $(prefix)
	@echo $(mandir)
	@ #if test ! -w $(prefix); then mkdir $(TESTSBINDIR); fi
	@ #$(CC) $(CFLAGS) test.c && ./a.out

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

man:
	$(foreach man3, $(wildcard doc/man/man3/*$(man3ext)), $(GROFF) $(man3) > debug-man/$(notdir $(man3));)

# man-pages:
#	@ #$MANPAGES
#	@echo `man --path`

rebuild: clean default

.PHONEY: default test clean man-pages
