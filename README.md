# LIBTECH

## What is the purpose of this library?

Everyone will agree that learning something requires to practice it, and I thought that why not create a library for the things I learnt along the way? So the `libtech` was born.

## How to install it to your system?

This library is using `POSIX` standards and mainly `Linux` libraries for its functions and variables. `Debian` was the intended distribution for this library but it may work with other Linux distributions.

You need `gcc` and `GNU Make` to compile and use this library.

### Install Procedure:

#### Prerequisites

* gcc
* make
* git

#### Installing the prerequisites

```bash
$ sudo apt-get install gcc make git
```

> :information\_source: It does not matter how you retrieve the source code of this repository, but a simple method is to use `git` to clone it to your machine, you are free to download the zip folder from the repository page.

#### Installing the library

```bash
$ git clone https://github.com/technicaluserx/libtech
$ cd libtech
$ make
$ sudo make install
```

> :exclamation: Using `make` and `git` should not differ between distros.

## How to use this library in your code?

### Including headers

Library headers are placed so that you can include them in your code like this:

```c
#include <tech/tech.h>
```

This file, `tech/tech.h` is written so that it includes everything inside the libtech library. But if you want to include other headers individually, you can do like this:

```c
#include <tech/shared/tech_include.h>
```

libtech is structured into sub folders to make the sources understandable in context. So for example, you will be able to see IEEE80211 wireless headers inside `<tech/ieee80211/...>` folder.

### Linking to the shared object

libtech library is compiled with the name `libtech.so`. To link it to your program, you must do this:

```bash
$ gcc main.c -ltech
```

> :exclamation: `makefile` does the trick needed to compile the library and place the necessary files to the system. Do not modify it unless you know what you are doing. libtech can be used with C++ programs. The linking procedure does not differ much.

```bash
$ g++ main.cpp -ltech
```
