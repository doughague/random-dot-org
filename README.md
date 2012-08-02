# C++ Library and Client for random.org
This package includes tools for downloading data from [random.org](https://random.org).

# Features
* You can access the typical random.org API (quota, integers, sequences and strings) along 
with some derived extras (fractions and bytes).
* SSL (HTTPS) is used by default but can be disabled. 
* One can also use a proxy and proxy-type; for example, 127.0.0.1:9050 and SOCKS4a to use the 
default [Vidalia-Tor](https://www.torproject.org/projects/vidalia) proxy:port configuration.
* There are two examples included for using the API; 
[example-api-fake-key](https://github.com/doughague/random-dot-org/blob/master/src/example-api-fake-key.cxx) and 
[example-api-powerlaw](https://github.com/doughague/random-dot-org/blob/master/src/example-api-powerlaw.cxx)

# Dependencies
* standard C/C++ libraries
* [GNU getopt](https://www.gnu.org/software/libc/manual/html_node/Getopt.html)
* [libCURL](http://curl.haxx.se/) with curl-config
* [Doxygen](http://www.stack.nl/~dimitri/doxygen/) for making API documentation

# Installation
First, edit the Makefile. 
See comments there: 
* use clang++ or gcc for compilation
* 32- or 64-bit archetecture supported

Compile:

    $ make

If you have Doxygen:

    $ make doc

View options of main executable:

    $ ./bin/random-dot-org --help

Optionally, you can soft-link the binary to a globally accessable bin 
(edit Makefile to modify install diretory):

	$ make install

# License
GPLv3

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
