/** \file RdoQuota.cxx 
    \brief Source for quota class
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
#include <stdlib.h>
#include "RdoQuota.hh"

//_____________________________________________________________________________
/** Default constructor. */
RdoQuota::RdoQuota()
  : RdoAbsObject(),
    _ip(""), _remainingBits(-1)
{}

//_____________________________________________________________________________
/** Copy constructor. */
RdoQuota::RdoQuota(const RdoQuota& other)
  : RdoAbsObject(other),
    _ip(other._ip), _remainingBits(other._remainingBits)
{}

//_____________________________________________________________________________
/** Set the IP address of the quota to check. */
void RdoQuota::setIP(const char* ip)
{
  _ip = std::string(ip);
}

//_____________________________________________________________________________
/** Build the URL for checking the quota. */
void RdoQuota::buildUrl()
{
  if(_ip!="")
    sprintf(_url,"%s://%s/quota/?format=%s&ip=%s", 
	    scheme(), rdoUrl(), format(), ip());
  else
    sprintf(_url,"%s://%s/quota/?format=%s", 
	    scheme(), rdoUrl(), format());    
}

//_____________________________________________________________________________
/** Parse the quota into memory. */
void RdoQuota::parseMemory(struct RdoAbsObject::CurlMem cMem)
{
  if(cMem.size > 0)
    _remainingBits = atol(&cMem.memory[0]);
}
