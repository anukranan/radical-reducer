#=================
# Makefile for radical-reducer
#=================

#===========================

CCOMPILER   ?= gcc
CFLAGS       = -std=c99 -Wall -Wextra -static
LFLAGS       = -lm

BUILD        = build
BIN          = bin
TARGET       = radical-reducer
PREFIX      ?= /usr/local

SRC          = main.c reduce.c
OBJ          = $(SRC:.c=.o)

#============================

all: build install

build:
	cd src/                             \
	&& $(CCOMPILER) $(CFLAGS) -c $(SRC) \
	&& mv $(OBJ) ../$(BUILD)/           \
	&& cd ../$(BUILD)/                  \
	&& $(CCOMPILER) $(CFLAGS) -o ../bin/$(TARGET) $(OBJ) $(LFLAGS)

install:
	cp $(BIN)/$(TARGET) $(PREFIX)/bin/

uninstall:
	rm -vi $(PREFIX)/bin/$(TARGET)

clean:
	rm -rvI $(BUILD)/*
	rm -vi $(BIN)/*

.PHONY: all build install uninstall clean
