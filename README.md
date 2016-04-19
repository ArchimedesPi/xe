# xe
## X Engine
### A simple 3d (game?) engine written for learning purposes

## building/hacking
you'll need:
 * cmake
 * ninja
 * glfw 3.1.2

this is a standard cmake-style project, so do the cmakey thing:
```
$ mkdir build
$ cd build
$ cmake -GNinja ..
$ ninja
```

make should fart out an executable, `xe`. run this to start the engine.

## thanks and acknowledgements
thanks to:
 * the GLFW team for an awesome library
 * John Carmack for writing the Doom and Quake engines (great learning resource and inspiration)

## license
xe - a simple 3d game engine written for learning purposes
Copyright (C) 2016  Liam Marshall

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
