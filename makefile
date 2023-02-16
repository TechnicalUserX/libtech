# LIBTECH Makefile | Written by TechnicalUserX

SHELL := /bin/bash

CC = gcc

INSTALL_INCLUDE_DIR = /usr/include
INSTALL_LIB_DIR = /usr/lib

SRC=$(shell ls ./src)
HDR=$(SRC:.c=.h)
OBJ=$(SRC:.c=.o)

OUT=libtech.so

OBJ_DEP=$(addprefix  ./obj/, ${OBJ})

BUILD_DIR=build
INCLUDE_DIR=include
SHARED_DIR=shared
CONFIG_DIR=config
SRC_DIR=src
OBJ_DIR=obj

CFLAGS = -shared -Wall -std=c11 -fPIC

VERSION = 0.0.1-beta

IS_INSTALLED = $(shell if [ -e ${INSTALL_INCLUDE_DIR}/tech ]; then echo 1; else echo 0; fi)

IS_SUPER_USER = $(shell id -u)



libtech: ${OBJ_DEP} 
	@echo "Compiling '${OUT}.${VERSION}'..."
	@$(shell if ! [ -d ${BUILD_DIR} ]; then mkdir ${BUILD_DIR}; fi)
	@${CC} ${OBJ_DEP} ${CFLAGS}  -o ${BUILD_DIR}/${OUT}.${VERSION}




config: tech.h



tech.h:
	@sed 's/@TECH_VERSION_CONFIGURATION@/${VERSION}/g' tech.h.in>tech.h




${OBJ_DIR}/%.o: ${SRC_DIR}/%.c ${INCLUDE_DIR}/%.h
	$(shell if ! [ -d ./${OBJ_DIR} ]; then mkdir ${OBJ_DIR}; fi )
	${CC} -fPIC -c $< -o $@




clean:
	@echo Cleaning object files and compiled library...
	$(shell if [ -d ${BUILD_DIR} ]; then rm -rf ${BUILD_DIR}/*; fi )
	$(shell if [ -d ${OBJ_DIR} ]; then rm -rf ${OBJ_DIR}/*; fi )
	@rm -f tech.h




full-clean: clean
	@echo Removing directories '${OBJ_DIR}' and '${BUILD_DIR}'...
	$(shell if [ -d ${BUILD_DIR} ]; then rmdir ${BUILD_DIR}; fi)
	$(shell if [ -d ${OBJ_DIR} ]; then rmdir ${OBJ_DIR}; fi)




install: ${BUILD_DIR}/${OUT}.${VERSION} config

ifneq (${IS_SUPER_USER}, 0)
	@echo "You have to be root to install libraries!"
else

ifeq (${IS_INSTALLED},1)
	@echo "Libraries has been already installed";
	@echo "If you want to update, run: 'sudo make update'";
else
	@echo "Super user right has been satisfied!";
	@echo "Copying LIBTECH library files to '${INSTALL_LIB_DIR}/tech'...";

	$(shell if ! [ -d ${INSTALL_LIB_DIR}/tech ]; then mkdir ${INSTALL_LIB_DIR}/tech; fi)

	@cp ${BUILD_DIR}/${OUT}.${VERSION} ${INSTALL_LIB_DIR}/tech;
	@ln -s ${INSTALL_LIB_DIR}/tech/${OUT}.${VERSION} ${INSTALL_LIB_DIR}/${OUT}

	@echo "Creating 'tech' directory inside '${INSTALL_INCLUDE_DIR}'..."

	$(shell if ! [ -d ${INSTALL_INCLUDE_DIR}/tech ]; then mkdir ${INSTALL_INCLUDE_DIR}/tech; fi)
	$(shell if ! [ -d ${INSTALL_INCLUDE_DIR}/tech/tech-${VERSION} ]; then mkdir ${INSTALL_INCLUDE_DIR}/tech/tech-${VERSION}; fi)
	$(shell if ! [ -d ${INSTALL_INCLUDE_DIR}/tech/shared ]; then mkdir ${INSTALL_INCLUDE_DIR}/tech/shared; fi)
	$(shell if ! [ -d ${INSTALL_INCLUDE_DIR}/tech/config ]; then mkdir ${INSTALL_INCLUDE_DIR}/tech/config; fi)


	@echo "Copying header files to ${INSTALL_INCLUDE_DIR}/tech/'..."
	@cp  ${INCLUDE_DIR}/* ${INSTALL_INCLUDE_DIR}/tech/tech-${VERSION}
	@cp ${SHARED_DIR}/* ${INSTALL_INCLUDE_DIR}/tech/${SHARED_DIR}
	@cp ${CONFIG_DIR}/* ${INSTALL_INCLUDE_DIR}/tech/${CONFIG_DIR}
	@cp tech.h ${INSTALL_INCLUDE_DIR}/tech
	@echo "Installation completed."

endif

endif




update: config libtech 
ifneq ($(IS_SUPER_USER), 0)
	@echo "You have to be root to update libraries!"
else
	@make --silent config
	@make --silent uninstall
	@make --silent install
endif




uninstall:
ifneq ($(IS_SUPER_USER), 0)
	@echo "You have to be root to uninstall libraries!"
else
	@echo "Uninstalling LIBTECH..."


	$(shell if [ -d ${INSTALL_INCLUDE_DIR}/tech ]; then \
	rm -rf ${INSTALL_INCLUDE_DIR}/tech/*; \
	rmdir ${INSTALL_INCLUDE_DIR}/tech; \
	fi \
	)

	$(shell if [ -d ${INSTALL_LIB_DIR}/tech ]; then \
	rm -rf ${INSTALL_LIB_DIR}/tech; \
	fi \
	)

	$(shell rm -f ${INSTALL_LIB_DIR}/${OUT})

	@echo "Uninstall completed!"

endif