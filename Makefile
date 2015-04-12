# RIMRAF ?= rm -rf
RIMRAF  = $(RM) -f
STD     = -std=C11
CFLAGS ?= $(STD) -O2 -pedantic -Wall -Wextra -Iinclude

# testdir = tests

PKGNAME = libtimely

# Common prefix for installation directories.
# NOTE: This directory must exist when you start the install.
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

# They should all be set to $(docdir) by default.
# [...]
# ‘$(htmldir)/’ll, ‘$(pdfdir)/’ll, etc. where ll is a locale abbreviation
# such as ‘en’ or ‘pt_BR’.

# 7.2.5 Variables for Installation Directories
#
# Installation directories should always be named by variables, so it is easy
# to install in a nonstandard place. The standard names for these variables
# and the values they should have in GNU packages are described below. They
# are based on a standard file system layout; variants of it are used in
# GNU/Linux and other modern operating systems.
#
# Installers are expected to override these values when calling make (e.g.,
# make prefix=/usr install or configure (e.g., configure --prefix=/usr). GNU
# packages should not try to guess which value should be appropriate for these
# variables on the system they are being installed onto: use the default
# settings specified here so that all GNU packages behave identically,
# allowing the installer to achieve any desired layout.
#
# All installation directories, and their parent directories, should be created
# (if necessary) before they are installed into.
#
# These first two variables set the root for the installation. All the other
# installation directories should be subdirectories of one of these two, and
# nothing should be directly installed into these two directories.
#
# prefix:
#
#     A prefix used in constructing the default values of the variables listed
#     below. The default value of prefix should be /usr/local. When building
#     the complete GNU system, the prefix will be empty and /usr will be a
#     symbolic link to /. (If you are using Autoconf, write it as ‘@prefix@’.)
#
#     Running ‘make install’ with a different value of prefix from the one used
#     to build the program should not recompile the program.
#
# [...]
#
# includedir:
#
#     The directory for installing header files to be included by user programs
#     with the C ‘#include’ preprocessor directive. This should normally be
#     /usr/local/include, but write it as $(prefix)/include. (If you are using
#	  Autoconf, write it as ‘@includedir@’.)
#
#     Most compilers other than GCC do not look for header files in directory
#     /usr/local/include. So installing the header files this way is only
#     useful with GCC. Sometimes this is not a problem because some libraries
#     are only really intended to work with GCC. But some libraries are
#     intended to work with other compilers. They should install their header
#     files in two places, one specified by includedir and one specified by
#     oldincludedir.
#
# [...]
#
# docdir:
#
#     The directory for installing documentation files (other than Info) for
#     this package. By default, it should be /usr/local/share/doc/yourpkg, but
#     it should be written as $(datarootdir)/doc/yourpkg. (If you are using
#     Autoconf, write it as ‘@docdir@’.) The yourpkg subdirectory, which may
#     include a version number, prevents collisions among files with common
#     names, such as README.
#
# infodir:
#
#     The directory for installing the Info files for this package. By default,
#     it should be /usr/local/share/info, but it should be written as
#     $(datarootdir)/info. (If you are using Autoconf, write it as ‘@infodir@’.)
#     infodir is separate from docdir for compatibility with existing practice.
#
# htmldir:
# dvidir:
# pdfdir:
# psdir:
#
#     Directories for installing documentation files in the particular format.
#     They should all be set to $(docdir) by default. (If you are using
#     Autoconf, write them as ‘@htmldir@’, ‘@dvidir@’, etc.) Packages which
#     supply several translations of their documentation should install them in
#     ‘$(htmldir)/’ll, ‘$(pdfdir)/’ll, etc. where ll is a locale abbreviation
#     such as ‘en’ or ‘pt_BR’.
#
# libdir:
#
#     The directory for object files and libraries of object code. Do not
#     install executables here, they probably ought to go in $(libexecdir)
#     instead. The value of libdir should normally be /usr/local/lib, but write
#     it as $(exec_prefix)/lib. (If you are using Autoconf, write it as
#     ‘@libdir@’.)
#
# [...]
#
# localedir:
#
#     The directory for installing locale-specific message catalogs for this
#     package. By default, it should be /usr/local/share/locale, but it should
#     be written as $(datarootdir)/locale. (If you are using Autoconf, write it
#     as ‘@localedir@’.) This directory usually has a subdirectory per locale.
#
# Unix-style man pages are installed in one of the following:
#
#
#‘mandir’
#
#   The top-level directory for installing the man pages (if any) for this package. It will normally be /usr/local/share/man, but you should write it as $(datarootdir)/man. (If you are using Autoconf, write it as ‘@mandir@’.)
#‘man1dir’
#
#   The directory for installing section 1 man pages. Write it as $(mandir)/man1.
#‘man2dir’
#
#    The directory for installing section 2 man pages. Write it as $(mandir)/man2
#‘…’
#
#    Don’t make the primary documentation for any GNU software be a man page. Write a manual in Texinfo instead. Man pages are just for the sake of people running GNU software on Unix, which is a secondary application only.
#‘manext’
#
#    The file name extension for the installed man page. This should contain a period followed by the appropriate digit; it should normally be ‘.1’.
#‘man1ext’
#
#    The file name extension for installed section 1 man pages.
#‘man2ext’
#
#    The file name extension for installed section 2 man pages.
#‘…’
#
#    Use these names instead of ‘manext’ if the package needs to install man pages in more than one section of the manual.
#
#And finally, you should set the following variable:
#
#‘srcdir’
#
#    The directory for the sources being compiled. The value of this variable is normally inserted by the configure shell script. (If you are using Autoconf, use ‘srcdir = @srcdir@’.)
#
#For example:
#
##Common prefix for installation directories.
##NOTE: This directory must exist when you start the install.
#prefix = /usr/local
#datarootdir = $(prefix)/share
#datadir = $(datarootdir)
#exec_prefix = $(prefix)
## Where to put the executable for the command 'gcc'.
#bindir = $(exec_prefix)/bin
## Where to put the directories used by the compiler.
#libexecdir = $(exec_prefix)/libexec
## Where to put the Info files.
#infodir = $(datarootdir)/info
#
#If your program installs a large number of files into one of the standard user-specified directories, it might be useful to group them into a subdirectory particular to that program. If you do this, you should write the install rule to create these subdirectories.
#
#Do not expect the user to include the subdirectory name in the value of any of the variables listed above. The idea of having a uniform set of variable names for installation directories is to enable the user to specify the exact same values for several different GNU packages. In order for this to be useful, all the packages must be designed so that they will work sensibly when the user does so.
#
# <https://www.gnu.org/prep/standards/standards.html#Makefile-Conventions>
# <https://www.gnu.org/prep/standards/standards.html#Releases>

# ---------------------

# @link https://www.gnu.org/software/make/manual/html_node/File-Name-Functions.html
# @link http://www.gnu.org/prep/standards/standards.html#Makefile-Conventions

#$(test -w /usr/local)

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

man-pages:
	@ #$MANPAGES
	@echo `man --path`

rebuild: clean default

.PHONEY: default test clean man-pages
