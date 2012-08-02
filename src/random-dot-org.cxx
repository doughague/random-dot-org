/** \file random-dot-org.cxx 
    \brief Source for random-dot-org binary executable
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
#include <iomanip>
#include <ostream>
#include <fstream>
#include <vector>
#include "RdoQuota.hh"
#include "RdoIntegers.hh"
#include "RdoSequence.hh"
#include "RdoStrings.hh"
#include "RdoRandom.hh"
#include "RdoBytes.hh"
#include "RdoOptions.hh"

// methods
int DownloadBinary(RdoOptions& opt);
void PrintUsage(std::ostream& os);

//_____________________________________________________________________________
//! random-dot-org binary executable main method
int main(int argc, char** argv)
{
  // --------------------------------------------
  // parse options 
  RdoOptions opt(argc, argv);
  // print help message
  if(opt.help){ PrintUsage(std::cout); return 0; }      

  // --------------------------------------------
  // check quota first? 
  if(opt.quota){
    RdoQuota rdoQuota;
    rdoQuota.setHttps(opt.useHTTPS);
    rdoQuota.setAgent(opt.agent.c_str());
    rdoQuota.setProxy(opt.proxy.c_str());
    rdoQuota.setProxyType(opt.proxyType.c_str());
    rdoQuota.setTimeOut(opt.timeout);
    rdoQuota.setInMemory(true);
    rdoQuota.setIP(opt.ip.c_str());
    bool failed = rdoQuota.downloadData();
    if(failed){
      std::cerr << "random-dot-org: Failed to download quota" << std::endl;
      return -1;
    } 
    if(!rdoQuota.withinQuota()){
      std::cerr << "random-dot-org: Quota exceeded" << std::endl;
      return -1;
    }
  }

  // --------------------------------------------
  // create/set the object
  RdoAbsObject* rdo = 0;
  if(opt.type=="quota"){
    rdo = new RdoQuota();
    ((RdoQuota*)rdo)->setIP(opt.ip.c_str());
  } 

  else if(opt.type=="integers"){
    rdo = new RdoIntegers();
    ((RdoIntegers*)rdo)->setNum(opt.num);
    ((RdoIntegers*)rdo)->setBase(opt.base.c_str());
    ((RdoIntegers*)rdo)->setRange(opt.min, opt.max);
    ((RdoIntegers*)rdo)->setColumns(opt.columns);
  } 

  else if(opt.type=="sequence"){
    rdo = new RdoSequence();
    ((RdoSequence*)rdo)->setRange(opt.min, opt.max);
    ((RdoSequence*)rdo)->setColumns(opt.columns);    
  }

  else if(opt.type=="strings"){
    rdo = new RdoStrings();
    ((RdoStrings*)rdo)->setNum(opt.num);
    ((RdoStrings*)rdo)->setLength(opt.length);
    ((RdoStrings*)rdo)->setDigits(opt.digits);
    ((RdoStrings*)rdo)->setUpper(opt.upper);
    ((RdoStrings*)rdo)->setLower(opt.lower);
    ((RdoStrings*)rdo)->setUnique(opt.unique);
  } 

  else if(opt.type=="fractions"){
    rdo = new RdoRandom();
    ((RdoRandom*)rdo)->setNum(opt.num);
    ((RdoRandom*)rdo)->setDecimals(opt.length);
    ((RdoRandom*)rdo)->setColumns(opt.columns);
  }

  else if(opt.type=="bytes"){
    rdo = new RdoBytes();
    ((RdoBytes*)rdo)->setNum(opt.num);
    ((RdoBytes*)rdo)->setBase(opt.base.c_str());    
    ((RdoBytes*)rdo)->setColumns(opt.columns);
  }

  else if(opt.type=="binary"){
    return DownloadBinary(opt);
  }

  else{
    std::cerr << "random-dot-org: Unknown data type = " << opt.type.c_str() << std::endl;
    PrintUsage(std::cerr);
    if(rdo) delete rdo;
    return -1;
  }

  // --------------------------------------------
  // set the general settings
  rdo->setHttps(opt.useHTTPS);
  rdo->setAgent(opt.agent.c_str());
  rdo->setProxy(opt.proxy.c_str());
  rdo->setProxyType(opt.proxyType.c_str());
  rdo->setTimeOut(opt.timeout);
  rdo->setOutFileName(opt.outFile.c_str());
  rdo->setAppend(opt.append);  

  // --------------------------------------------
  // get the random data
  bool failed = rdo->downloadData();
  if(failed){
    std::cerr << "random-dot-org: Failed to download " << opt.type.c_str() << " data" << std::endl;
    if(rdo) delete rdo;
    return -1;
  }

  // --------------------------------------------
  // clean & return
  if(rdo) delete rdo;
  return 0;
}

//_____________________________________________________________________________
//! download and output binary data
int DownloadBinary(RdoOptions& opt)
{
  // --------------------------------------------
  // create/set the object
  RdoBytes rdo;
  // set the general settings
  rdo.setHttps(opt.useHTTPS);
  rdo.setAgent(opt.agent.c_str());
  rdo.setProxy(opt.proxy.c_str());
  rdo.setProxyType(opt.proxyType.c_str());
  rdo.setTimeOut(opt.timeout);
  rdo.setInMemory(true);

  // specific settings
  // Note: num interpreted as bits!!
  unsigned int nBytes = (unsigned int)(opt.num/8.);
  if(opt.num % 8) nBytes += 1;
  rdo.setNum(nBytes);
  rdo.setBase("2");
  rdo.setColumns(1);

  // --------------------------------------------
  // get the random data
  bool failed = rdo.downloadData();
  if(failed){
    std::cerr << "random-dot-org: Failed to download " << opt.type.c_str() << " data" << std::endl;
    return -1;
  }
  std::vector<unsigned int> data = rdo.cache();

  // --------------------------------------------
  // stream
  std::ofstream ofs;
  bool toFile = (opt.outFile!="");
  if(toFile){
    if(opt.append) ofs.open(opt.outFile.c_str(), std::ios_base::out | std::ios_base::binary | std::ios_base::app);
    else           ofs.open(opt.outFile.c_str(), std::ios_base::out | std::ios_base::binary);
    if(!ofs.is_open()){
      std::cerr << "random-dot-org: Failed to open file " << opt.outFile.c_str() << std::endl;
      return -1;      
    }
  }

  // --------------------------------------------
  // write binary data
  for(unsigned int k=0; k<data.size(); k++){
    char c = static_cast<char>(data[k]);
    if(toFile) ofs << c;
    else std::cout << c;
  }

  // close file
  if(toFile) ofs.close();
  // return
  return 0;
}

//_____________________________________________________________________________
//! print random-dot-org usage to stream
void PrintUsage(std::ostream& os)
{
  os << "Usage: random-dot-org [type] [options]" << std::endl;
  os << "       Download random data from www.random.org." << std::endl;

  os << std::endl;
  os << "Types:" << std::endl;
  os << "  quota       check your quota" << std::endl;
  os << "  integers    download integers" << std::endl;
  os << "  sequence    download sequence of integers" << std::endl;
  os << "  strings     download strings" << std::endl;
  os << "  fractions   download decimal fractions" << std::endl;
  os << "  bytes       download random bytes" << std::endl;
  os << "  binary      download random bytes to binary format" << std::endl;

  // general options
  os << std::endl;
  os << "General Options:" << std::endl;
  os << "  [long], [short]    [example]       [description]" << std::endl;
  os << "  --help, -h,-?                      show this help message and exit" << std::endl;
  os << "  --agent, -g        me@me.org       set the user agent" << std::endl;
  os << "  --not-secure, -X                   use HTTP, not HTTPS" << std::endl;
  os << "  --proxy, -x        127.0.0.1:9050  connect through [proxy-url]:[port-number]" << std::endl;
  os << "  --proxy-type, -y   SOCKS4a         type of proxy; HTTP, SOCKS4, SOCKS4a, SOCKS5" << std::endl;
  os << "  --time-out, -t     120             time in seconds to wait for server" << std::endl;
  os << "  --out-file, -o     data.txt        write to file instead of std::cout" << std::endl;
  os << "  --append, -a                       append to out-file instead of overwriting" << std::endl;
  os << "  --format, -f       plain           format of file to write; plain or html" << std::endl;
  os << "  --quota, -Q                        check your quota before downloading random data" << std::endl;

  // integers options
  os << std::endl;
  os << "quota Options:" << std::endl;
  os << "  --ip, -w           134.226.36.80   check quota for specific IP address" << std::endl;

  // integers options
  os << std::endl;
  os << "integers Options:" << std::endl;
  os << "  --number, -n       100             number of integers to download; [1,1e4]" << std::endl;
  os << "  --min, -l          1               minimum possible integer; [-1e9,1e9]" << std::endl;
  os << "  --max, -u          10000           maximum possible integer; [-1e9,1e9]" << std::endl;
  os << "  --base, -b         10              base for the number system; 2, 8, 10 or 16" << std::endl;
  os << "  --columns, -c      1               number of columns in ouput; [1,1e9]" << std::endl;
  os << "Example: random-dot-org integers" << std::endl;
  os << "         Will write 10 integers within [1,10000] to std::cout." << std::endl;

  // sequence options
  os << std::endl;
  os << "sequence Options:" << std::endl;
  os << "  --min, -l          1               minimum possible integer; [-1e9,1e9]" << std::endl;
  os << "  --max, -u          10000           maximum possible integer; [-1e9,1e9]" << std::endl;
  os << "  --columns, -c      1               number of columns in ouput; [1,1e9]" << std::endl;
  os << "Example: random-dot-org sequence" << std::endl;
  os << "         Will write 10000 integers within [1,10000] to std::cout." << std::endl;

  // strings options
  os << std::endl;
  os << "strings Options:" << std::endl;
  os << "  --number, -n       100             number of strings to download; [1,1e4]" << std::endl;
  os << "  --length, -s       8               length of strings to download; [1,20]" << std::endl;
  os << "  --not-lower, -k                    exclude lowercase alphabetic characters (default is false)" << std::endl;
  os << "  --digits, -d                       use digits" << std::endl;
  os << "  --upper, -j                        use uppercase alphabetic characters" << std::endl;
  os << "  --unique, -q                       require unique strings" << std::endl;
  os << "Example: random-dot-org strings" << std::endl;
  os << "         Will write ten lowercase eight-character strings to std::cout." << std::endl;
  os << std::endl;

  // fractions options
  os << std::endl;
  os << "fractions Options:" << std::endl;
  os << "  --number, -n       100             number of fractions to download; [1,1e4]" << std::endl;
  os << "  --length, -s       8               length, e.g. number of decimal places; [1,20]" << std::endl;
  os << "  --columns, -c      1               number of columns in output; [1,1e9]" << std::endl;
  os << "Example: random-dot-org fractions" << std::endl;
  os << "         Will write ten eight-decimal fractions to std::cout." << std::endl;

  // bytes options
  os << std::endl;
  os << "bytes Options:" << std::endl;
  os << "  --number, -n       100             number of bytes to download; [1,1e4]" << std::endl;
  os << "  --base, -b         10              base for the number system; 2, 8, 10 or 16" << std::endl;
  os << "  --columns, -c      1               number of columns in output; [1,1e9]" << std::endl;
  os << "Example: random-dot-org bytes" << std::endl;
  os << "         Will write ten bytes to std::cout." << std::endl;

  // binary options
  os << std::endl;
  os << "binary Options:" << std::endl;
  os << "  --number, -n       100            number of bits (NOT bytes!!)" << std::endl;
  os << "                                    rounded up to nearest byte to download; [1,8e4]" << std::endl;
  os << "Example: random-dot-org binary" << std::endl;
  os << "         Will write 16 bits in binary format to std::cout." << std::endl;
}
