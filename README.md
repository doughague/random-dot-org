# C++ Library and Client for [random.org](https://www.random.org)
This package includes **GPLv3** licensed **GNU/Linux** tools for downloading data from 
**[random.org](https://www.random.org)**.

## Features
* You can access the typical [random.org](https://www.random.org) API (quota, integers, sequences and strings) 
  along with some derived extras (fractions and bytes).
* Secure connection (HTTPS) is used by default but can be disabled at run-time with `--not-secure` option.
* One can specify a proxy and proxy-type at run-time. 
    * I.e., `--proxy 127.0.0.1:9050 --proxy-type SOCKS4a` will use the default 
	[Vidalia-Tor](https://www.torproject.org/projects/vidalia) proxy:port configuration.
* Uses `libCURL` to download data:
    * To `std::cout` (default)
	* Appended to specified output file, i.e. `-o data.txt --append`
	* In-memory c++ classes (API) for use in other programs.
* There are examples included for using the API of this software: 
    * [example-api-fake-key](https://github.com/doughague/random-dot-org/blob/master/src/example-api-fake-key.cxx) 
	will print ASCII characters that look somewhat like a GPG public key.
    * [example-api-powerlaw](https://github.com/doughague/random-dot-org/blob/master/src/example-api-powerlaw.cxx)
	shows how to download and generate power-law distributed random numbers and estimate the power-law index.

## Dependencies
* Standard C/C++ libraries with [GNU getopt](https://www.gnu.org/software/libc/manual/html_node/Getopt.html)
* [libCURL](http://curl.haxx.se/) with `curl-config`
* [Doxygen](http://www.stack.nl/~dimitri/doxygen/) for making API documentation

## Installation
Optionally, you can edit the Makefile to change the following:
* Use `clang++` or `gcc` for compilation (default is `clang++`).
* Is 32-bit or 64-bit archetecture (default is 64-bit, i.e. `-m64` compiler flag)
* Change the binary install (soft-link) directory (default is `/usr/bin/`)

Compile:

    $ make

If you have [Doxygen](http://www.stack.nl/~dimitri/doxygen/):

    $ make doc

View options of main executable:

    $ ./bin/random-dot-org --help

Optionally, you can soft-link the binary to a globally accessable bin 
(default is `/usr/bin`, edit the Makefile to modify install diretory):

	$ make install

# License
**GPLv3**

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
