/** \file example-api-fake-key.cxx 
    \brief Source for example-api-fake-key binary executable
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
#include "RdoIntegers.hh"

//_____________________________________________________________________________
//! example-api-fake-key binary executable main method
int main(int argc, char** argv)
{
  // --------------------------------------------
  // create/set the random.org object
  RdoIntegers rdo;
  rdo.setNum(int(4096/8));
  rdo.setBase("10");
  rdo.setRange(33,126);
  rdo.setInMemory(true);

  // --------------------------------------------
  // get the random data
  bool failed = rdo.downloadData();
  if(failed){
    std::cerr << "example-api-fake-key: Failed to download data" << std::endl;
    return -1;
  }

  // --------------------------------------------
  // in-memory random integers
  std::vector<long int> data = rdo.cache();
  unsigned int num = data.size();

  // --------------------------------------------
  // convert to characters and print as a FAKE key-block
  std::cout << "-----BEGIN FAKE PUBLIC KEY BLOCK-----" << std::endl;
  std::cout << "Version: RdO v1 (GNU/Linux)" << std::endl;
  std::cout << std::endl;
  unsigned int columns = 64;
  for(unsigned int k=0; k<num; k++){
    std::cout << static_cast<char>(data[k]);
    if(!((k+1)%columns)) std::cout << std::endl;    
  }
  if(!((num+1)%columns)) std::cout << std::endl;      
  std::cout << "-----END FAKE PUBLIC KEY BLOCK-----" << std::endl;


  // --------------------------------------------
  // return
  return 0;
}
