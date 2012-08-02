/** \file RdoSequence.cxx 
    \brief Source for sequence class
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
#include "RdoSequence.hh"

//_____________________________________________________________________________
/** Default constructor. */
RdoSequence::RdoSequence()
  : RdoIntegers()
{}

//_____________________________________________________________________________
/** Copy constructor. */
RdoSequence::RdoSequence(const RdoSequence& other)
  : RdoIntegers(other)
{}

//_____________________________________________________________________________
/** Build the URL for checking the quota. */
void RdoSequence::buildUrl()
{
  sprintf(_url,"%s://%s/sequences/?format=%s&rnd=%s&col=%d&min=%ld&max=%ld", 
	  scheme(), rdoUrl(), format(), randomization(), columns(), min(), max());
}
