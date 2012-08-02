# C++ Library and Client for [random.org](https://www.random.org)
This package includes **LGPLv3** licensed **GNU/Linux** [libCURL](http://curl.haxx.se/)-based
tools for downloading data from **[random.org](https://www.random.org)**.

## Features
* **Versatile**: You can access the typical [random.org](https://www.random.org) 
  API (quota, integers, sequences and strings) along with some derived extras 
  (fractions, bytes and binary) via the commandline executable `bin/random-dot-org` 
  or within your own program via libRdO API.
* **Standard**: Uses [libCURL](http://curl.haxx.se/) library to connect to 
  [random.org](https://www.random.org) and download data. 
* **Secure**: HTTPS is used by default (disabled with `--not-secure` run-time option). 
  Also, attempts are made to clear (over-write) in-memory sensitive data on exit.
* **Anonymizable**: Proxy and user-agent can be set at run-time: 
    * I.e., `--proxy 127.0.0.1:9050 --proxy-type SOCKS4a` will use the default 
	[Vidalia-Tor](https://www.torproject.org/projects/vidalia) proxy:port-number configuration.
	See [TorFAQ](https://trac.torproject.org/projects/tor/wiki/doc/TorFAQ#SOCKSAndDNS) for 
	more information. (Note that the [Tor-Browser-Bundle](https://www.torproject.org/projects/torbrowser.html) 
	uses a randomized port-number.)
	* I.e., `--agent me@me.org` will identify the user-agent as `me@me.org` to 
	[random.org](https://www.random.org).
* **API**: You can use this library (headers/classes) in your own software. 
 There are examples included for using the API of this software: 
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

Optionally, you can soft-link the binary to a globally accessable bin. 
(The default is `/usr/bin` and you can edit the Makefile to modify the install diretory):

	$ make install

# Contribute
Please consider helping with this project. Some things to do include:
* **Vet and debug code, especially any security issues!!**
* Add `./configure` script for *nix portability.
* Port to Windows and/or Mac OS.
* Add support for internet connection username/password interface.
* Add support for proxy connection username/password interface.
* A GUI would be awesome.

# License
**[LGPLv3](https://www.gnu.org/copyleft/lgpl)**

libRdO for downloading data from random.org
Copyright (C) 2012 Doug Hague

libRdO is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

libRdO is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with libRdO.  If not, see <http://www.gnu.org/licenses/>.
