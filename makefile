SHELL := /bin/bash

CC = gcc
CXX = g++

INCLUDE_DIR = "/usr/include"
LIB_DIR = "/usr/lib"

CFLAGS = -fPIC -shared
CXXFLAGS = -fPIC -shared

VERSION = 1.0.0
VERSIONXX = 1.1.0

SRC = color_terminal.c list.c log.c math.c
SRCXX = color_terminal.cpp list.cpp log.cpp math.cpp sockets.cpp exception.cpp expandingbytes.cpp

IS_INSTALLED = ${shell if [ -e ${INCLUDE_DIR}/techlib ]; then echo 1; else echo 0; fi}

IS_SUPER_USER=${shell id -u}



build:
	make libtechc
	make libtechcpp

libtechc:
	@echo "Creating 'libtechc.so.${VERSION}'..."
	cd "techlib/Linux/C/src"; ${CC} ${CFLAGS} ${SRC} -o ../lib/libtechc.so.${VERSION}

libtechcpp: 
	@echo "Creating 'libtechcpp.so.${VERSIONXX}'..."
	cd "techlib/Linux/CPP/src"; ${CXX} ${CXXFLAGS} ${SRCXX} -o ../lib/libtechcpp.so.${VERSIONXX}


install: ./techlib/Linux/C/lib/libtechc.so.${VERSION} ./techlib/Linux/CPP/lib/libtechcpp.so.${VERSIONXX}

ifneq ($(IS_SUPER_USER), 0)
	@echo "You have to be root to install libraries!"
else

ifeq ($(IS_INSTALLED),1)
	@echo "Libraries has been already installed";
	@echo "If you want to update, run: 'sudo make update'";
else
	@echo "Super user rights has been satisfied!";
	@echo "Copying TECHLIB library files to '${LIB_DIR}/techlib'...";
	@mkdir ${LIB_DIR}/techlib
	@cp ./techlib/Linux/C/lib/libtechc.so.${VERSION} ${LIB_DIR}/techlib;
	@cp ./techlib/Linux/CPP/lib/libtechcpp.so.${VERSIONXX} ${LIB_DIR}/techlib;
	@ln -s ${LIB_DIR}/techlib/libtechc.so.${VERSION} ${LIB_DIR}/libtechc.so
	@ln -s ${LIB_DIR}/techlib/libtechcpp.so.${VERSIONXX} ${LIB_DIR}/libtechcpp.so
	@echo "Creating 'techlib' file inside '${INCLUDE_DIR}'..."
	@mkdir ${INCLUDE_DIR}/techlib
	@mkdir ${INCLUDE_DIR}/techlib/C
	@mkdir ${INCLUDE_DIR}/techlib/CPP
	@echo "Copying header files to ${INCLUDE_DIR}/techlib'..."
	@cp  ./techlib/Linux/C/include/* ${INCLUDE_DIR}/techlib/C
	@cp  ./techlib/Linux/CPP/include/* ${INCLUDE_DIR}/techlib/CPP
	@echo "Installation completed."
endif

endif

update:
ifneq ($(IS_SUPER_USER), 0)
	@echo "You have to be root to update libraries!"
else
	@echo "Removing current headers and libraries..."
	@rm -r ${INCLUDE_DIR}/techlib
	@rm ${LIB_DIR}/libtech*
	@rm -r ${LIB_DIR}/techlib
	@echo "Copying TECHLIB library files to '${LIB_DIR}/techlib'...";
	@mkdir ${LIB_DIR}/techlib
	@cp ./techlib/Linux/C/lib/libtechc.so.${VERSION} ${LIB_DIR}/techlib;
	@cp ./techlib/Linux/CPP/lib/libtechcpp.so.${VERSIONXX} ${LIB_DIR}/techlib;
	@ln -s ${LIB_DIR}/techlib/libtechc.so.${VERSION} ${LIB_DIR}/libtechc.so
	@ln -s ${LIB_DIR}/techlib/libtechcpp.so.${VERSIONXX} ${LIB_DIR}/libtechcpp.so
	@echo "Creating 'techlib' file inside '${INCLUDE_DIR}'..."
	@mkdir ${INCLUDE_DIR}/techlib
	@mkdir ${INCLUDE_DIR}/techlib/C
	@mkdir ${INCLUDE_DIR}/techlib/CPP
	@echo "Copying header files to ${INCLUDE_DIR}/techlib'..."
	@cp  ./techlib/Linux/C/include/* ${INCLUDE_DIR}/techlib/C
	@cp  ./techlib/Linux/CPP/include/* ${INCLUDE_DIR}/techlib/CPP
	@echo "Update completed."	
endif


uninstall:
ifneq ($(IS_SUPER_USER), 0)
	@echo "You have to be root to uninstall libraries!"
else
	@echo "Uninstalling TECHLIB..."
	@rm -r ${INCLUDE_DIR}/techlib
	@rm -r ${LIB_DIR}/techlib
	@rm ${LIB_DIR}/libtech*
	@echo "Uninstall completed!"
endif
