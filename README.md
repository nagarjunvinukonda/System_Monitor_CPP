# CppND-System-Monitor

# Overview
This package is my work with Udacity ND course to build and understand Linux systems, its performance and memmory usage. This project is compatable with majority of Ubuntu distributions and has been tested on Ubuntu 16.04 and Ubuntu 18.0

![System Monitor](images/monitor.png)

##  Workspace
For this project I have used Udacity workspace. You are welcome to use any workspace. 


## ncurses
[ncurses](https://www.gnu.org/software/ncurses/) is a library that facilitates text-based graphical output in the terminal. This project relies on ncurses for display output.

If you are not using the Udacity Workspace, install ncurses within your own Linux environment: `sudo apt install libncurses5-dev libncursesw5-dev`

## Make
This project uses [Make](https://www.gnu.org/software/make/). The Makefile has four targets:
* `build` compiles the source code and generates an executable
* `format` applies [ClangFormat](https://clang.llvm.org/docs/ClangFormat.html) to style the source code
* `debug` compiles the source code and generates an executable, including debugging symbols
* `clean` deletes the `build/` directory, including all of the build artifacts

## Instructions

1. Clone the project repository: `git clone https://github.com/udacity/CppND-System-Monitor-Project-Updated.git`

2. Build the project: `make build`

3. Run the resulting executable: `./build/monitor`
![Starting System Monitor](images/starting_monitor.png)

4. Here our goal lies to implement the `System`, `Process`, and `Processor` classes, as well as functions within the `LinuxParser` namespace. This already done in this repo. You guys can test it for understanding!!
