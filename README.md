# LIBTECH | Technical C Library
Created By TechnicalUserX
## Purpose
This library is created for the sake of assistance for personal projects.

> ℹ️ This library is only intended for Linux based operating systems


# Installation
## Installing To Debian Based Linux Distros

#### Requirements:
  1. GNU Compiler Collection (gcc) 
  2. GNU Make (make)

You can query whether your working Linux distribution satisfies the prerequisites by:
```bash
apt-cache policy gcc make
```
In order to install required packages if you don't have:
```bash
sudo apt-get install gcc make git
```


#### Execute these commands in order to install the library.
```bash
git clone https://github.com/TechnicalUserX/libtech.git
cd libtech
make
sudo make install
```
After successful installation, usage is as follows.
```c
#include <tech/tech.h>

int main(){
  
  tech_log(stdout,TECH_LOG_STYLE_CLOCK,"Hello");

  return 0;
}
```
In order to access to the `function definition`, compiler flag `-l` must be specified.
Language | Compiler flag appearance
-------- | ------------------------
C/C++    | -ltech


```bash
gcc main.c -ltech -o main.out
```

> ⚠️ If you encounter a problem like `undefined reference to sqrtl`, compile your code as follows:

```bash
gcc main.c -ltech -lm -o main.out
```
`-lm` specifies the math library. 

> ℹ️ This library is compatible with `C++`.



