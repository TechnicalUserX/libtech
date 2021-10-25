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
make install
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
