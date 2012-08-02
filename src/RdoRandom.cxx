/** \file RdoRandom.cxx 
    \brief Source for random (fractions) class
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
#include <cmath>        // math functions
#include "RdoRandom.hh"

//_____________________________________________________________________________
/** Default constructor. */
RdoRandom::RdoRandom()
  : RdoAbsObject(),
    _decimals(8), _columns(1),
    _randData(0), _pos(0)
{}

//_____________________________________________________________________________
/** Copy constructor. */
RdoRandom::RdoRandom(const RdoRandom& other)
  : RdoAbsObject(other),
    _decimals(other._decimals), _columns(other._columns),
    _randData(other._randData), _pos(other._pos)
{}

//_____________________________________________________________________________
/** Set smallest value allowed for each integer. */
void RdoRandom::setDecimals(unsigned int decimals)
{
  _decimals = decimals;
}

//_____________________________________________________________________________
/** Set smallest value allowed for each integer. */
void RdoRandom::setColumns(unsigned int columns)
{
  _columns = columns;
}

//_____________________________________________________________________________
/** Build the URL for checking the quota. */
void RdoRandom::buildUrl()
{
  sprintf(_url,"%s://%s/decimal-fractions/?format=%s&rnd=%s&num=%d&col=%d&dec=%d", 
	  scheme(), rdoUrl(), format(), randomization(), num(), columns(), decimals());
}

//_____________________________________________________________________________
/** Get a random fraction from memory. */
double RdoRandom::rndm()
{
  unsigned int dsize = _randData.size();
  if(dsize==0){
    std::cerr << "Warning: RdoRandom::rndm: No data in memory" << std::endl;
    return 0;
  } 

  double val = 0;
  if(_pos >= dsize){
    std::cerr << "Warning: RdoRandom::rndm: Exceeded random cache size, begining to repeat!" << std::endl;
    _pos = 0;
  }
  val = _randData[_pos];	
  _pos++;
  
  return val;
}

//_____________________________________________________________________________
/** Parse the integers into memory. */
void RdoRandom::parseMemory(struct RdoAbsObject::CurlMem cMem)
{
  // check for some memory
  if(cMem.size <= 0){
    std::cerr << "Error: RdoRandom::parseMemory: No data in memory" << std::endl;
    return;
  }

  // check for proper formating
  if(_columns != 1){
    std::cerr << "Error: RdoRandom::parseMemory: Set columns = 1 to retrieve data in memory" << std::endl;
    return;
  }

  // parse the memory
  char delim = '\n';
  char* token = strtok(cMem.memory,&delim) ;
  while(token){
    _randData.push_back(atof(token));
    token = strtok(0,&delim) ; 
  }  

  if(_randData.size()<num())
    std::cerr << "Warning: RdoRandom::parseMemory: Parsed fewer numbers than downloaded" << std::endl;    
}
