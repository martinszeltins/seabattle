````
Seabattle 2.0

Author: Martins Zeltins <martins@martinsz.lv>

Version history:
2.0: June 10, 2022
1.0: May 1, 2021
````

## Instructions

**Download and install the SDL library**

````
sudo apt-get install -y build-essential clang libsdl2-2.0-0 libsdl2-dev libsdl2-image-2.0-0 libsdl2-image-dev libsdl2-ttf-dev
````

**Compile and run**

````
$ make && ./seabattle && make clean -fX

P.S. make clean will remove all object files and the executable so git tree will be clean.
````
