/** \file RdoStrings.cxx 
    \brief Source for strings class
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
#include <iostream>     // for cout, cerr, clog
#include <string.h>     // string handling functions (memset, strtok)
#include "RdoStrings.hh"

//_____________________________________________________________________________
/** Default constructor. */
RdoStrings::RdoStrings()
  : RdoAbsObject(),
    _length(8), _digits(true),
    _upper(true), _lower(true),
    _unique(false),
    _randData(0), _pos(0)
{}

//_____________________________________________________________________________
/** Copy constructor. */
RdoStrings::RdoStrings(const RdoStrings& other)
  : RdoAbsObject(other),
    _length(other._length), _digits(other._digits),
    _upper(other._upper), _lower(other._lower),
    _unique(other._unique),
    _randData(other._randData), _pos(0)
{}

//_____________________________________________________________________________
/** Set smallest value allowed for each integer. */
void RdoStrings::setLength(unsigned int length)
{
  _length = length;
}

//_____________________________________________________________________________
/** Allow digit characters. */
void RdoStrings::setDigits(bool digits)
{
  _digits = digits;
}

//_____________________________________________________________________________
/** Allow uppercase alphabetic characters. */
void RdoStrings::setUpper(bool upper)
{
  _upper = upper;
}

//_____________________________________________________________________________
/** Allow lowercase alphabetic characters. */
void RdoStrings::setLower(bool lower)
{
  _lower = lower;
}

//_____________________________________________________________________________
/** Set whether the strings picked should be unique. */
void RdoStrings::setUnique(bool unique)
{
  _unique = unique;
}

//_____________________________________________________________________________
/** Convert boolean to url code. 
    \return "on" if true, else "off"
*/
std::string RdoStrings::boolToCode(bool b)
{
  if(b) return std::string("on");
  else  return std::string("off");
}

//_____________________________________________________________________________
/** Build the URL for checking the quota. */
void RdoStrings::buildUrl()
{
  sprintf(_url,"%s://%s/strings/?format=%s&rnd=%s&num=%d&len=%d&digits=%s&upperalpha=%s&loweralpha=%s&unique=%s", 
	  scheme(), rdoUrl(), format(), randomization(), num(), length(), 
	  boolToCode(digits()).c_str(), boolToCode(upper()).c_str(), 
	  boolToCode(lower()).c_str(), boolToCode(unique()).c_str());
}

//_____________________________________________________________________________
/** Get a random integer from memory. */
std::string RdoStrings::rndm()
{
  unsigned int dsize = _randData.size();
  if(dsize==0){
    std::cerr << "Warning: RdoStrings::rndm: No data in memory" << std::endl;
    return 0;
  } 

  std::string val("0");
  if(_pos >= dsize){
    std::cerr << "Warning: RdoStrings::rndm: Exceeded random cache size, begining to repeat!" << std::endl;
    _pos = 0;
  }
  val = _randData[_pos];	
  _pos++;
  
  return val;
}

//_____________________________________________________________________________
/** Parse the integers into memory. */
void RdoStrings::parseMemory(struct RdoAbsObject::CurlMem cMem)
{
  // check for some memory
  if(cMem.size <= 0){
    std::cerr << "Error: RdoStrings::parseMemory: No data in memory" << std::endl;
    return;
  }

  // parse the memory
  char delim = '\n';
  char* token = strtok(cMem.memory,&delim) ;
  while(token){
    _randData.push_back(std::string(token));
    token = strtok(0,&delim) ; 
  }  

  if(_randData.size()<num())
    std::cerr << "Warning: RdoStrings::parseMemory: Parsed fewer numbers than downloaded" << std::endl;    
}
