SHELL = /bin/bash

CC = g++
CFLAGS = -fPIC -shared

SRC = color_terminal.cpp list.cpp log.cpp math.cpp sockets.cpp

lib: ${SRC}
	@echo "Creating 'libtechcpp.so'..."
	${CC} ${CFLAGS} ${SRC} -o libtechcpp.so

