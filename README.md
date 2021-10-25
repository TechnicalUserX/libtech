# TECHLIB | Technical C/C++ Library
Created By TechnicalUserX
## Purpose
This library is created for the sake of assistance for personal projects.
Library will be updated when there is a need.

# Installation
## Installing To Debian Based Linux Distros
### 1) Using Raw Source Files
You can give the source files to the compiler directly alongside including their correspoing header files.
```cpp
#include "techlib/CPP/list.hpp" // Pay attention to double quotes, this is the relative path to your main.cpp file
int main(){
  // Your code here
  return 0;
}
```
And...
```bash
g++ main.cpp list.cpp -o main.out
```
This applies to both C and C++.
### 2) Using Shared Object Files
This will make the library available from anywhere and you will be able to use `<lib.h>` notation.
#### Requirements:
  1. GNU Compiler Collection (gcc) (g++)
  2. GNU Make (make)

You can query wheter your working Linux distribution satisfies the prerequisites by:
```bash
apt-cache policy gcc g++ make
```
In order to install required packages if you don't have:
```bash
sudo apt-get install gcc g++ make
```


#### Execute these commands in order to install the library.
```bash
git clone https://github.com/TechnicalUserX/TECHLIB.git
cd TECHLIB
make
sudo make install
```
After successful installation, usage is as follows.
```c
#include <techlib/C/log.h>

int main(){
  
  techlib_log_ascii("Printing log message");

  return 0;
}
```
In order to access to the `function definition`, compiler flag `-l` must be specified.
Language | Compiler flag appearance
-------- | ------------------------
C++      | -ltechcpp
C        | -ltechc


```bash
g++ main.cpp -ltechcpp -o main.out

gcc main.c -ltechc -o main.out
```
IMPORTANT: If you encounter a problem like `undefined reference to sqrtl`, compile your code as follows:
It is highly probable that you will encounter this error while trying to compile `C` code.
```bash
gcc main.c -ltechc -lm -o main.out
```
`-lm` specifies the math library. 

## Installing To Windows

> ⚠️ This installation process deals with MinGW. It is your responsibility to handle other toolsets by yourself.

> ℹ️ MinGW `(Minimalist GNU For Windows)` is a toolset, which consists of many language compilers and tools, must be installed to proceed library installation.
If you have the MinGW already installed and `gcc`/`g++` is accessible from the Windows Command Prompt, you are free to skip this step.

### 1) Installing MinGW
Go to [sourceforge.net](https://sourceforge.net/projects/mingw/) and install the MinGW Get software. This tool is used for installing
Compilation tools with ease.
#### Click `Download` and download the `mingw-get-setup.exe` file
![](/images/mingw/mingw_1.png)

#### Click on `Install`
![](/images/mingw/mingw_2.png)

#### Leave everything as is. If you wish to change the `Installation Directory`, it is your responsibility to handle all path changes.
> ⚠️ All of the library files will be copied into `Installation Directory`, please be aware that when you change this location to something else
> you should modify `mingw_directory` variable inside `setup.bat` file. 
![](/images/mingw/mingw_3.png)

#### Click on `Continue`
![](/images/mingw/mingw_4.png)

#### Locate the option `mingw32-gcc-g++` and right click on it.
![](/images/mingw/mingw_5.png)

#### Click on `Mark for Installation`
![](/images/mingw/mingw_6.png)
![](/images/mingw/mingw_7.png)

#### Click on `Installation` tab at the top left corner an click on `Apply Changes`
![](/images/mingw/mingw_8.png)

#### Finally, click on `Appply` and when it finishes, you can close all windows.
![](/images/mingw/mingw_9.png)

### 2) Setting Up `PATH` Environment Variable
`Installation Directory` must be inserted into the `PATH` environment variable inside Windows system.
To modify `PATH`, you must open a command prompt and type this command.
```cmd
setx PATH {Installation Directory}\bin
```
Since the default `Installation Directory` is `C:\MinGW`, the command should correspond to the command below:
```cmd
setx PATH C:\MinGW\bin
```
> ⚠️ The reason you should specify `\bin` folder is the `gcc` and `g++` and many other tools are located inside this folder.
> They should be accessible anywhere in the Windows system.

> ℹ️ `setx` command does not modify the system `PATH` variable, it creates a local variable which also works like `PATH`, so any mistake using this command will not affect the system variable.
