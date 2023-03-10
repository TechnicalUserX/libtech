# LIBTECH Makefile | Written by TechnicalUserX
# Specialized makefile for libraries
#!/bin/bash

######################################
# Version
VERSION=0.0.1-beta
VERSION_MAJOR=0
VERSION_MINOR=0
VERSION_PATCH=1
VERSION_PRE_RELEASE=1 # 0=stable 1=beta
######################################
# Common variables
SHELL := /bin/bash
CC = gcc
CC_INCLUDE_DIR=.
INSTALL_INCLUDE_DIR = /usr/include
INSTALL_LIB_DIR = /usr/lib
LOOKUP_DIR=tech
TARGET_LIB_NAME=tech
CFLAGS = -Wall -Wextra -fPIC -std=c11
BUILD_DIR=build
SRC_EXT=c
HDR_EXT=h
VERSION_HEADER=${LOOKUP_DIR}/version/version.${HDR_EXT}
######################################
BUILD_OBJ_DIR = ${BUILD_DIR}/obj
BUILD_LIB_DIR = ${BUILD_DIR}/lib
TARGET_LIB = lib${TARGET_LIB_NAME}
#pkg-config file
TARGET_LIB_PC = ${TARGET_LIB}.pc
#shared object file
TARGET_LIB_SO = ${TARGET_LIB}.so
######################################


IS_INSTALLED = $(shell if [ -e ${INSTALL_INCLUDE_DIR}/${TARGET_LIB_NAME} ]; then echo 1; else echo 0; fi)
IS_SUPER_USER = $(shell id -u)

SRC = $(shell find $(LOOKUP_DIR) -type f -name "*.${SRC_EXT}")
HDR = $(shell find $(LOOKUP_DIR) -type f -name "*.${HDR_EXT}")
OBJ = $(patsubst $(LOOKUP_DIR)/%, $(BUILD_OBJ_DIR)/%, $(SRC:.${SRC_EXT}=.o))


HDR_DIR=$(dir ${HDR} | sort -u);
INSTALL_HDR_DIR=$(addprefix  ${INSTALL_INCLUDE_DIR}/,$(dir $(subst ${TARGET_LIB_NAME}/,${TARGET_LIB_NAME}-${VERSION}/, ${HDR})) )

MKDIR_P = mkdir -p



${TARGET_LIB}: ${BUILD_LIB_DIR}/$(TARGET_LIB_SO) ${TARGET_LIB_NAME}.${HDR_EXT} ${TARGET_LIB_PC}
	@echo Compiled ${TARGET_LIB}

${BUILD_LIB_DIR}/$(TARGET_LIB_SO): ${VERSION_HEADER} $(OBJ) 
	@$(MKDIR_P) ${BUILD_LIB_DIR}
	@$(CC) -I ${CC_INCLUDE_DIR} -shared $^ -o $@.${VERSION}
	@echo Created ${TARGET_LIB_SO}

$(BUILD_OBJ_DIR)/%.o: $(LOOKUP_DIR)/%.c 
	@$(MKDIR_P) $(shell dirname $@)
	$(CC) -I ${CC_INCLUDE_DIR} $(CFLAGS) -c $< -o $@ 


${LOOKUP_DIR}/%.${HDR_EXT}:
	@echo $(subst ${TARGET_LIB_NAME}/,${TARGET_LIB_NAME}-${VERSION}/, $@ )


${VERSION_HEADER}:
	@sed -e 's/@VERSION_CONFIGURATION@/"${VERSION}"/g' -e 's/@VERSION_CONFIGURATION_MAJOR@/${VERSION_MAJOR}/g' -e 's/@VERSION_CONFIGURATION_MINOR@/${VERSION_MINOR}/g' -e 's/@VERSION_CONFIGURATION_PATCH@/${VERSION_PATCH}/g' -e 's/@VERSION_CONFIGURATION_PRE_RELEASE@/${VERSION_PRE_RELEASE}/g' ${VERSION_HEADER}.in > ${VERSION_HEADER}



${TARGET_LIB_NAME}.${HDR_EXT}:
	@sed 's/@VERSION_CONFIGURATION@/${VERSION}/g' ${TARGET_LIB_NAME}.${HDR_EXT}.in>${TARGET_LIB_NAME}.${HDR_EXT}
	@echo Created generic ${TARGET_LIB_NAME}.${HDR_EXT} file


${TARGET_LIB_PC}:
	@sed -e 's/@VERSION_CONFIGURATION@/${VERSION}/g' ${TARGET_LIB_PC}.in > ${TARGET_LIB_PC}
clean:
	@echo Performing cleanup
	@rm -rf $(BUILD_DIR)
	@rm -f ${TARGET_LIB_NAME}.${HDR_EXT}
	@rm -f ${VERSION_HEADER}
	@rm -f ${TARGET_LIB_PC}


install: ${BUILD_LIB_DIR}/${TARGET_LIB_SO}

ifneq (${IS_SUPER_USER}, 0)
	@echo "You have to be root to install libraries!"
else

ifeq (${IS_INSTALLED},1)
	@echo "Libraries has been already installed";
	@echo "If you want to update, run: 'sudo make update'";
else
	@echo "Super user right has been satisfied!";
	@echo "Copying ${TARGET_LIB} library files to '${INSTALL_LIB_DIR}/${TARGET_LIB_NAME}'...";

# Create lib.so folder inside library folder
	$(shell if ! [ -d ${INSTALL_LIB_DIR}/${TARGET_LIB_NAME}-${VERSION} ]; then mkdir ${INSTALL_LIB_DIR}/${TARGET_LIB_NAME}-${VERSION}; fi)

	@cp ${BUILD_LIB_DIR}/${TARGET_LIB_SO}.${VERSION} ${INSTALL_LIB_DIR}/${TARGET_LIB_NAME}-${VERSION}
	@ln -s ${INSTALL_LIB_DIR}/${TARGET_LIB_NAME}-${VERSION}/${TARGET_LIB_SO}.${VERSION} ${INSTALL_LIB_DIR}/${TARGET_LIB_SO}

	@echo "Creating '${TARGET_LIB_NAME}-${VERSION}' directory inside '${INSTALL_INCLUDE_DIR}'..."

# Creating /usr/include/lib-version
	$(shell if ! [ -d ${INSTALL_INCLUDE_DIR}/${TARGET_LIB_NAME}-${VERSION} ]; then mkdir ${INSTALL_INCLUDE_DIR}/${TARGET_LIB_NAME}-${VERSION}; fi)
	@ln -s ${INSTALL_INCLUDE_DIR}/${TARGET_LIB_NAME}-${VERSION} ${INSTALL_INCLUDE_DIR}/${TARGET_LIB_NAME}
	
	@echo "Copying header files to ${INSTALL_INCLUDE_DIR}/${TARGET_LIB}/'..."
	@${MKDIR_P} ${INSTALL_HDR_DIR}
	@bash -c '$(foreach a,$(HDR),cp ${a} $(subst ${TARGET_LIB_NAME}/,${INSTALL_INCLUDE_DIR}/${TARGET_LIB_NAME}-${VERSION}/,$(dir ${a}) ); )'	@echo FINISH
	@cp ${TARGET_LIB_NAME}.${HDR_EXT} ${INSTALL_INCLUDE_DIR}/${TARGET_LIB_NAME}-${VERSION}
	@cp ${TARGET_LIB}.pc ${INSTALL_LIB_DIR}/pkgconfig

	@echo "Installation completed."

endif

endif


update: 
ifneq ($(IS_SUPER_USER), 0)
	@echo "You have to be root to update libraries!"
else
	@make --silent uninstall
	@make --silent install
endif


uninstall:
ifneq ($(IS_SUPER_USER), 0)
	@echo "You have to be root to uninstall libraries!"
else
	@echo "Uninstalling ${TARGET_LIB}..."

	@rm -rf ${INSTALL_INCLUDE_DIR}/${TARGET_LIB_NAME}-${VERSION}
	@rm -rf ${INSTALL_INCLUDE_DIR}/${TARGET_LIB_NAME}

	@rm -rf ${INSTALL_LIB_DIR}/${TARGET_LIB_SO}
	@rm -rf ${INSTALL_LIB_DIR}/${TARGET_LIB_NAME}-${VERSION}
	@rm -f  ${INSTALL_LIB_DIR}/pkgconfig/${TARGET_LIB}.pc


	@echo "Uninstall completed!"

endif