# C++ Library and Client for random.org
This package includes tools for downloading data from [random.org](https://random.org).

# Dependencies
* standard C/C++ libraries
* [GNU getopt](https://www.gnu.org/software/libc/manual/html_node/Getopt.html)
* [libCURL](http://curl.haxx.se/) with curl-config
* [Doxygen](http://www.stack.nl/~dimitri/doxygen/) for making API documentation

# Installation
Edit the Makefile. See comments there: clang++ or gcc and 32- or 64-bit archetecture.

Then, 

    $ make

If you have Doxygen

    $ make doc

View options of main executable:

    $ random-dot-org/bin/random-dot-org --help

# License
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
