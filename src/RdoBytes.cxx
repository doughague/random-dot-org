/** \file RdoBytes.cxx 
    \brief Source for integers class
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
#include <stdlib.h>     // general utilities
#include <iostream>     // for cout, cerr, clog
#include <string.h>     // string handling functions (memset, strtok)
#include "RdoBytes.hh"

//_____________________________________________________________________________
/** Default constructor. */
RdoBytes::RdoBytes()
  : RdoAbsObject(),
    _base("10"), _columns(1),
    _randData(0), _pos(0)
{}

//_____________________________________________________________________________
/** Copy constructor. */
RdoBytes::RdoBytes(const RdoBytes& other)
  : RdoAbsObject(other),
    _base(other._base), _columns(other._columns),
    _randData(other._randData), _pos(other._pos)
{}

//_____________________________________________________________________________
/** Set base number system each integer. 
    \param base Choose 2, 8, 10 or 16 or the corresponding name: binary, octal, decimal, hexadecimal
*/
void RdoBytes::setBase(const char* base)
{
  std::string b(base);
  if(b=="2" || b=="binary")
    _base = "2";
  else if(b=="8" || b=="octal")
    _base = "8";
  else if(b=="10" || b=="decimal")
    _base = "10";
  else if(b=="16" || b=="hexadecimal")
    _base = "16";
  else{
    std::cerr << "Error: RdoBytes::setBase: Unkonwn base = " << base
	      << " requested, using base = 10" << std::endl;
    _base = "10";
  }
}

//_____________________________________________________________________________
/** Set smallest value allowed for each integer. */
void RdoBytes::setColumns(unsigned int columns)
{
  _columns = columns;
}

//_____________________________________________________________________________
/** Build the URL for checking the quota. */
void RdoBytes::buildUrl()
{
  sprintf(_url,"%s://%s/integers/?format=%s&rnd=%s&num=%d&col=%d&min=0&max=255&base=%s", 
	  scheme(), rdoUrl(), format(), randomization(), num(), columns(), base());
}

//_____________________________________________________________________________
/** Get a random byte (as int) from memory. */
unsigned int RdoBytes::rndm()
{
  unsigned int dsize = _randData.size();
  if(dsize==0){
    std::cerr << "Warning: RdoBytes::rndm: No data in memory" << std::endl;
    return 0;
  } 

  if(_pos >= dsize){
    std::cerr << "Warning: RdoBytes::rndm: Exceeded random cache size, begining to repeat!" << std::endl;
    _pos = 0;
  }
  unsigned int val = _randData[_pos];	
  _pos++;
  
  return val;
}

//_____________________________________________________________________________
/** Parse the integers into memory. */
void RdoBytes::parseMemory(struct RdoAbsObject::CurlMem cMem)
{
  // check for some memory
  if(cMem.size <= 0){
    std::cerr << "Error: RdoBytes::parseMemory: No data in memory" << std::endl;
    return;
  }

  // check for proper formating
  if(_columns != 1){
    std::cerr << "Error: RdoBytes::parseMemory: Set columns = 1 to retrieve data in memory" << std::endl;
    return;
  }

  // parse the memory
  char delim = '\n';
  char* token = strtok(cMem.memory,&delim) ;
  while(token){
    _randData.push_back(strtoul(token,NULL,atoi(base())));
    token = strtok(0,&delim) ; 
  }  

  if(_randData.size()<num())
    std::cerr << "Warning: RdoBytes::parseMemory: Parsed fewer numbers than downloaded" << std::endl;    
}
