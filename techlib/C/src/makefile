SHELL = /bin/bash

CC = gcc
CFLAGS = -fPIC -shared

SRC = color_terminal.c list.c log.c math.c

lib: ${SRC}
	@echo "Creating 'libtechc.so'..."
	${CC} ${CFLAGS} ${SRC} -o libtechc.so

