# C++ Library and Client for random.org
This package includes tools for downloading data from [random.org](https://random.org).

# Dependencies
0) standard c/c++ libraries and GNU-getopt (getopt.h)
1) libCURL <http://curl.haxx.se/>
2) Doxygen for making API documentation

# Installation
0) edit Makefile
   (see comments there: clang++ or gcc and 32 or 64 bit archetecture)
1) > make
   (requires libCURL and curl-config)
2) > make doc
   (requires Doxygen)
3) random-dot-org/bin/random-dot-org --help
   (to view options of main executable)

# Copyright
libRdO for downloading data from random.org
Copyright (C) 2012 Doug Hague

libRdO is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

libRdO is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with libRdO.  If not, see <http://www.gnu.org/licenses/>.
