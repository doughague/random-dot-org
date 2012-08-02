/** \file RdoOptions.cxx 
    \brief Source for options class
*/
/*  libRdO for downloading data from random.org
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
*/
#include <stdlib.h>    // general utilities
#include <getopt.h>    // GNU option parsing
#include "RdoOptions.hh"

//_____________________________________________________________________________
/** Default constructor. */
RdoOptions::RdoOptions()
  : help(false), pLevel(0),
    agent("libcurl-agent"), useHTTPS(true),
    proxy(""), proxyType(""),
    outFile(""), append(false),
    format("plain"), rnd("new"), columns(1), num(10),
    type(""), quota(false), ip(""),
    min(1), max(1e4), base("10"),
    length(8), digits(false), upper(false), lower(true), unique(false)
{}

//_____________________________________________________________________________
/** Constructor from commend-line inputs. */
RdoOptions::RdoOptions(int argc, char** argv)
  : help(false), pLevel(0),
    agent("libcurl-agent"), useHTTPS(true),
    proxy(""), proxyType(""),
    outFile(""), append(false),
    format("plain"), rnd("new"), columns(1), num(10),
    type(""), quota(false), ip(""),
    min(1), max(1e4), base("10"),
    length(8), digits(false), upper(false), lower(true), unique(false)
{
  parseCmdLine(argc, argv);
}

//_____________________________________________________________________________
/** Copy constructor. */
RdoOptions::RdoOptions(const RdoOptions& other)
  : help(other.help), pLevel(other.pLevel),
    agent(other.agent), useHTTPS(other.useHTTPS),
    proxy(other.proxy), proxyType(other.proxyType),
    outFile(other.outFile), append(other.append),
    format(other.format), rnd(other.rnd), columns(other.columns), num(other.num),
    type(other.type), quota(other.quota), ip(other.ip),
    min(other.min), max(other.max), base(other.base),
    length(other.length), digits(other.digits), upper(other.upper), 
    lower(other.lower), unique(other.unique)
{}

//_____________________________________________________________________________
/** Parse the command-line options.
    See gnu.org/software/libc/manual/html_node/Getopt.html for how to use GNU getopt.
*/
void RdoOptions::parseCmdLine(int argc, char** argv)
{
  // struct array for feeding to getopt
  static struct option long_options[] =
    {
      {"help",         no_argument,       0, 'h'},
      {"print-level",  required_argument, 0, 'p'},

      {"agent",        required_argument, 0, 'g'},
      {"not-secure",   no_argument,       0, 'X'},
      {"proxy",        required_argument, 0, 'x'},
      {"proxy-type",   required_argument, 0, 'y'},
      {"time-out",     required_argument, 0, 't'},

      {"out-file",     required_argument, 0, 'o'},
      {"append",       no_argument,       0, 'a'},
      {"format",       required_argument, 0, 'f'},
      {"rnd",          required_argument, 0, 'r'},
      {"columns",      required_argument, 0, 'c'},
      {"number",       required_argument, 0, 'n'},

      {"quota",        no_argument,       0, 'Q'},
      {"ip",           required_argument, 0, 'w'},

      // {"integers",     no_argument,       0, 'I'},
      {"min",          required_argument, 0, 'l'},
      {"max",          required_argument, 0, 'u'},
      {"base",         required_argument, 0, 'b'},

      // {"strings",      no_argument,       0, 'S'},
      {"length",       required_argument, 0, 's'},
      {"digits",       no_argument,       0, 'd'},
      {"upper",        no_argument,       0, 'j'},
      {"not-lower",    no_argument,       0, 'k'},
      {"unique",       no_argument,       0, 'q'},

      {0, 0, 0, 0}
    };

  // getopt_long stores the option index here.
  int option_index(0);
  int option_char(-1);

  // begin reading options
  while(1){
    // '' = no argument, ':' = required argument, '::' = optional argument
    option_char = getopt_long(argc, argv, "h?p:g:Xx:y:t:o:af:r:c:n:Qw:l:u:b:s:djkq", 
			      long_options, &option_index);
    
    if(option_char==-1) break;   // Detect the end of the options.
    switch(option_char){         // Detect the options.
    case 'h': help = true; break;
    case '?': help = true; break;
    case 'p': pLevel = atoi(optarg); break;

    case 'g': agent = std::string(optarg); break;
    case 'X': useHTTPS = false; break;
    case 'x': proxy = std::string(optarg); break;
    case 'y': proxyType = std::string(optarg); break;
    case 't': timeout = atoi(optarg); break;

    case 'o': outFile = std::string(optarg); break;
    case 'a': append = true; break;

    case 'f': format = std::string(optarg); break;
    case 'r': rnd = std::string(optarg); break;
    case 'c': columns = atol(optarg); break;
    case 'n': num = atol(optarg); break;

    case 'Q': quota = true; break;
    case 'w': ip = std::string(optarg); break;
      
    // case 'I': integers = true; break;
    case 'l': min = atol(optarg); break;
    case 'u': max = atol(optarg); break;
    case 'b': base = std::string(optarg); break;

    // case 'S': strings = true; break;
    case 's': length = atoi(optarg); break;
    case 'd': digits = true; break;
    case 'j': upper = true; break;
    case 'k': lower = false; break;
    case 'q': unique = true; break;

    default:  abort();
    } // end option switch
  } // end while (read opts)

  // first non-option is taken as type
  if(optind < argc){
    type = std::string(argv[optind++]);
  }
}
