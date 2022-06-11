#============
# Makefile for simplify_radicals.
#============

.POSIX:

#========================

# Compiler
CC       = cc

# Flags
INCLUDE  =
CFLAGS   = $(INCLUDE) -std=c99 -Wall -Wno-unused -O3 -static
LFLAGS   = -lm

# Folders
BINDIR   = bin
BUILDDIR = build
SRCDIR   = src

# Installation
TARGET   = radical-reducer
PREFIX  ?= /usr/local/bin

# Compilation
SRC      = $(wildcard $(SRCDIR)/*.c)
OBJ      = $(notdir $(SRC:.c=.o))

#========================

all: build install

build:
	if [ ! -d ./$(BINDIR) ]; then mkdir ./$(BINDIR); fi
	if [ ! -d ./$(BUILDDIR) ]; then mkdir ./$(BUILDDIR); fi

	$(CC) $(CFLAGS) $(LFLAGS) -c $(SRC)

	mv $(OBJ) ./$(BUILDDIR)

	$(CC) $(CFLAGS) -o ./$(BINDIR)/$(TARGET) \
	$(addprefix ./$(BUILDDIR)/,$(notdir $(OBJ))) $(LFLAGS)

install:
	cp ./$(BINDIR)/$(TARGET) $(PREFIX)/

uninstall:
	rm -vi $(PREFIX)/$(TARGET)

clean:
	rm -rv ./$(BINDIR)/*
	rm -vi ./$(BUILDDIR)/*

.PHONY: all build install uninstall clean
