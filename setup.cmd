@echo off
setlocal EnableDelayedExpansion
mode con: cols=110 lines=20
color 0f
title TECHLIB Setup Utility

:: ************************************
::	MinGW Location 
:: 
set MINGW_DIR=C:\MinGW
::
::
:: ************************************


set PWD=%~dp0

set COLOR_DIR=%PWD%\util

set IS_ADMIN=0
net session >nul 2>&1
if %errorLevel% == 0 Set IS_ADMIN=1

if %IS_ADMIN%==0 (
	echo.
	call :color /0b " TECHLIB Setup Utility"
	echo.
	echo.
	call :color /0c " You have to be administrator to install TECHLIB."
	echo.
	call :color /0f " Press any key to exit..."
	pause >nul
	exit
)
cd %PWD%


set MINGW_EXISTS=0

set MINGW_GCC_EXISTS=0
set MINGW_GPP_EXISTS=0




:: MINGW DIRECTORY EXISTANCE CHECK
if exist %MINGW_DIR% (
	set MINGW_EXISTS=1
)
if %MINGW_EXISTS%==0 (
	echo.
	call :color /0b " TECHLIB Setup Utility"
	echo.
	echo.
	call :color /0c " MinGW does not exists!"
	echo.
	call :color /0e " Please install MinGW or specify the Installation Directory currently"
	echo.
	echo  Press any key to exit...
	pause >nul
	exit
)


:: COMPILER EXISTANCE CHECK

if exist %MINGW_DIR%\bin\gcc.exe (
	set MINGW_GCC_EXISTS=1 
)
if exist %MINGW_DIR%\bin\g^+^+.exe (
	set MINGW_GPP_EXISTS=1 
)

if %MINGW_GCC_EXISTS%==0 (
	echo.
	call :color /0b " TECHLIB Setup Utility"
	echo.
	echo.
	call :color /0c " Cannot find gcc.exe"
	echo.
	echo.
	call :color /0E " Exiting..."
	echo.
	timeout /t 2 >nul
	exit
)

if %MINGW_GPP_EXISTS%==0 (
	echo.
	call :color /0b " TECHLIB Setup Utility"
	echo.
	echo.
	call :color /0c " Cannot find g++.exe"
	echo.
	echo.
	call :color /0e " Exiting..."
	echo.
	timeout /t 2 >nul
	exit
)





set TECHLIB_EXISTS=0
set CC=gcc
set CXX=g++

set CFLAGS=-fPIC -shared
set CXXFLAGS=-fPIC -shared

set INCLUDE_DIR=%MINGW_DIR%\include
set LIB_DIR=%MINGW_DIR%\lib

set VERSION=1.1.0
set VERSIONXX=1.1.0

set SRC=list.c log.c math.c color_cmd.c
set SRCXX=list.cpp log.cpp math.cpp color_cmd.cpp exception.cpp








:: TECHLIB EXISTANCE CHECK
if exist %MINGW_DIR%\include\techlib (
	set TECHLIB_EXISTS=1
)







:: PATH CHECK


set PATH_MODIFICATION_REQUIRED=0

echo !path! | findstr /L "!MINGW_DIR!\bin"
cls
set MINGW_PATH_BIN_EXISTS=%errorlevel%

if %MINGW_PATH_BIN_EXISTS%==1 (

	set PATH_MODIFICATION_REQUIRED=1
)


echo !path! | findstr /L "!MINGW_DIR!\lib"
cls
set MINGW_PATH_LIB_EXISTS=%errorlevel%

if %MINGW_PATH_LIB_EXISTS%==1 (

	set PATH_MODIFICATION_REQUIRED=1
)




if %PATH_MODIFICATION_REQUIRED%==1 (
	echo.
	call :color /0b " TECHLIB Setup Utility"
	echo.
	echo.
	call :color /0c " Following values are needed as a directory inside PATH varibale."
	echo.
	echo.
	if %MINGW_PATH_BIN_EXISTS%==1 (
		call :color /0e " !MINGW_DIR!\bin"
		echo.	
	)
	if %MINGW_PATH_LIB_EXISTS%==1 (

		call :color /0e " !MINGW_DIR!\lib"
		echo.		
	)
	
	:check_path_inclusion
	echo.
	echo  Do you want to add the location here? [y/n]
	echo.
	call :input
	set /p choice=
	if !choice!==y (
	
		set "PATH_ADD_STRING="
	
		if %MINGW_PATH_BIN_EXISTS%==1 (
			set "PATH_ADD_STRING=!PATH_ADD_STRING!;!MINGW_DIR!\bin"
		)
		
		if %MINGW_PATH_LIB_EXISTS%==1 (
			set "PATH_ADD_STRING=!PATH_ADD_STRING!;!MINGW_DIR!\lib"
		)		
	


		setx PATH "!PATH!!PATH_ADD_STRING!"
		timeout /t 2 >nul
		goto :skip_path_inclusion
	
	
	)

	if !choice!==n (
		call :color /0e " Exiting..."
		timeout /t 2 >nul
		exit
	)
	echo.
	goto :check_path_inclusion

)


:skip_path_inclusion
if %PATH_MODIFICATION_REQUIRED%==1 (
	cls
	echo.
	call :color /0e " Restart required..."
	echo.
	echo  Restart system.cmd to proceed installation.
	echo.
	echo  Press any key to exit...
	pause >nul
	exit

)



















:menu
cls
echo.
call :color /0b " TECHLIB Setup Utility"
echo.
echo.
echo  Enter a command:
echo.
echo 	- build			^| Compiles libtechc and libtechcpp.
echo 	- install		^| Copies headers and lib files to !MINGW_DIR!.
echo 	- update		^| Deletes previous copies and copies again to !MINGW_DIR!.
echo 	- uninstall		^| Deletes everything about TECHLIB inside the machine.
echo.
call :input
set /p choice=

if %choice%==build (
	call :build
	goto :menu
)


if %choice%==uninstall (
	call :uninstall
	goto :menu
)



if %choice%==install (
	if !TECHLIB_EXISTS!==1 (
		call :color /0e " TECHLIB already exists!"
		echo.
		call :color /0f " Input: "
		call :color /0e "update" 
		call :color /0f " to update existing libraries."
		echo.
		echo.
		pause
		goto :menu
	)
	call :install
	goto :menu
)

if %choice%==update (
	call :color /0a " Updating current TECHLIB..."
	echo.
	call :install
	goto :menu
)

call :color /0c " Invalid command!"
pause
goto :menu




:build
	call :color /0e " Creating library files..."
	echo.
	echo.
	del /Q /F .\techlib\Windows\C\lib\*
	cd ".\techlib\Windows\C\src"
	call :color /0f " Now Compiling: "
	call :color /0a "libtechc"
	echo.
	!CC! !SRC! !CFLAGS! -o ../lib/libtechc.dll
	cd ..\..\..\..
	del /Q /F .\techlib\Windows\CPP\lib\*
	cd ".\techlib\Windows\CPP\src"
	call :color /0f " Now Compiling: "
	call :color /0a "libtechcpp"
	echo.
	!CXX! !SRCXX! !CXXFLAGS! -o ../lib/libtechcpp.dll
	cd ..\..\..\..
	call :color /0a " Done!"
	echo.
	echo.
	pause
goto :eof


:install
	call :color /0e " Copying library files to " 
	call :color /0a "!MINGW_DIR!\lib"
	call :color /0f "..."
	echo.
	copy ".\techlib\Windows\C\lib\libtechc.dll" "!MINGW_DIR!\lib"
	copy ".\techlib\Windows\CPP\lib\libtechcpp.dll" "!MINGW_DIR!\lib"

	mkdir "!MINGW_DIR!\include\techlib"
	mkdir "!MINGW_DIR!\include\techlib\C"
	mkdir "!MINGW_DIR!\include\techlib\CPP"
	call :color /0f " Copying header files to "
	call :color /0a "!MINGW_DIR!\include\techlib"
	call :color /0f "..."
	echo.
	copy ".\techlib\Windows\C\include\*" "!MINGW_DIR!\include\techlib\C"
	copy ".\techlib\Windows\CPP\include\*" "!MINGW_DIR!\include\techlib\CPP"
	set TECHLIB_EXISTS=1
	call :color /0a " Done!"
	echo.
	pause
goto :eof


:uninstall
	call :color /0c " Uninstalling..."
	echo.
	del /F /Q /S "!MINGW_DIR!\include\techlib"
	del /F /Q "!MINGW_DIR!\lib\libtech*"
	rmdir "!MINGW_DIR!\include\techlib\C"
	rmdir "!MINGW_DIR!\include\techlib\CPP"
	rmdir "!MINGW_DIR!\include\techlib"
	set TECHLIB_EXISTS=0
	call :color /0e " Done!"
	echo.
	pause 
goto :eof



:color
	call "!COLOR_DIR!\color.exe" %1 %2
goto :eof


:input
	call :color /0a " %username%"
	call :color /0f "@"
	call :color /08 "techlib"
	call :color /0f "[]> "
goto :eof
