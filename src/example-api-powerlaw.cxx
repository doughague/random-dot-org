/** \file example-api-powerlaw.cxx 
    \brief Source for example-api-powerlaw binary executable
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
#include <iostream>
#include <cmath>
#include "RdoRandom.hh"

//_____________________________________________________________________________
//! example-api-powerlaw binary executable main method
int main(int argc, char** argv)
{
  // --------------------------------------------
  // create/set the random.org object
  RdoRandom rdo;
  // number of fractions to download
  rdo.setNum(1000);
  // number of decimal places in each fraction
  rdo.setDecimals(4);
  // download to memory, not out put to a file
  rdo.setInMemory(true);

  // --------------------------------------------
  // get the random data
  bool failed = rdo.downloadData();
  if(failed){
    std::cerr << "example-api-powerlaw: Failed to download data" << std::endl;
    return -1;
  }

  // --------------------------------------------
  // in-memory random fractions
  std::vector<double> data = rdo.cache();
  unsigned int num = data.size();

  // --------------------------------------------
  // convert to power-law distributed data
  double min = 1.0;
  double index = 2.0;
  std::vector<double> pwlwData;
  for(unsigned int k=0; k<num; k++)
    pwlwData.push_back( min / pow(data[k],1./index));
  std::cout << "Generated " << num << " power-law distributed events with index = " << index << std::endl;

  // --------------------------------------------
  // estimate powerlaw index
  double lgsum = 0;
  for(unsigned int k=0; k<num; k++)
    lgsum += log(pwlwData[k]/min);
  double estindex = num/lgsum;
  std::cout << "Estimated index = " << estindex << " +/- " << (index)/sqrt(num) << std::endl;

  // --------------------------------------------
  // return
  return 0;
}
