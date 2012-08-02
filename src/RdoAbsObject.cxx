/** \file RdoAbsObject.cxx 
    \brief Source for abstract base 
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
#include <stdlib.h> // general utilities
#include <iostream> // for cout, cerr, clog
#include <string.h> // for string utils like memcpy, &c.
#include "RdoAbsObject.hh"

//_____________________________________________________________________________
/** Default constructor. */
RdoAbsObject::RdoAbsObject()
  : _scheme("https"), _rdoUrl("www.random.org"), _format("plain"), _rnd("new"),
    _num(10), _url(0),
    _cURL(0), _agent("libcurl-agent"), _proxy(""), _proxyType(""),
    _inMemory(false), _outFileName(""), _append(false)
{
  // init the cURL session
  curl_global_init(CURL_GLOBAL_ALL);
  _cURL = curl_easy_init();

  // allocate url memory
  _url = new char[512];

  // some default settings
  setTimeOut();
}

//_____________________________________________________________________________
/** Copy constructor. */
RdoAbsObject::RdoAbsObject(const RdoAbsObject& other)
  : _scheme(other._scheme), _rdoUrl(other._rdoUrl), _format(other._format),
    _rnd(other._rnd), _num(other._num), _url(0),
    _cURL(other._cURL), _agent(other._agent),
    _proxy(other._proxy), _proxyType(other._proxyType),
    _inMemory(other._inMemory), _outFileName(other._outFileName),
    _append(other._append)
{
  sprintf(_url,"%s",other._url);
}

//_____________________________________________________________________________
/** Destructor. */
RdoAbsObject::~RdoAbsObject()
{
  // free url memory
  if(_url) delete [] _url;  
  // clean up CURL
  curl_easy_cleanup(_cURL);
  curl_global_cleanup();
}

//_____________________________________________________________________________
/** Set user agent. 
    Some servers don't like requests that are made without a user-agent.
*/
void RdoAbsObject::setAgent(const char* agent)
{
  _agent = std::string(agent);
  curl_easy_setopt(_cURL, CURLOPT_USERAGENT, _agent.c_str());  
}

//_____________________________________________________________________________
/** Set the proxy to use for conecting to random.org; [URL]:[PORT]. 
    For example 127.0.0.1:9050
*/
void RdoAbsObject::setProxy(const char* proxy)
{
  if(proxy && strlen(proxy)!=0){
    _proxy = std::string(proxy);
    curl_easy_setopt(_cURL, CURLOPT_PROXY, _proxy.c_str());    
  }
}
 
//_____________________________________________________________________________
/** Set the proxy type to use for conecting to random.org; HTTP, SOCKS4, SOCKS4a or SOCKS5. */
void RdoAbsObject::setProxyType(const char* proxyType)
{
  if(proxyType && strlen(proxyType)!=0){
    std::string spt(proxyType);
    if(spt=="HTTP"){
      _proxyType = spt;
      curl_easy_setopt(_cURL, CURLOPT_PROXYTYPE, CURLPROXY_HTTP);     
    } else if(spt=="SOCKS4") {
      _proxyType = spt;
      curl_easy_setopt(_cURL, CURLOPT_PROXYTYPE, CURLPROXY_SOCKS4); 
    } else if(spt=="SOCKS4a") {
      _proxyType = spt;
      curl_easy_setopt(_cURL, CURLOPT_PROXYTYPE, CURLPROXY_SOCKS4A); 
    } else if(spt=="SOCKS5") {
      _proxyType = spt;    
      curl_easy_setopt(_cURL, CURLOPT_PROXYTYPE, CURLPROXY_SOCKS5); 
    } else{
      std::cerr << "Error: RdoAbsObject::setProxyType: Unkown proxy type " << proxyType 
		<< ", using HTTP" << std::endl;
      _proxyType = "HTTP";
      curl_easy_setopt(_cURL, CURLOPT_PROXYTYPE, CURLPROXY_HTTP); 
    }
  }
}

//_____________________________________________________________________________
/** Set wait time. random.org can be very slow. */
void RdoAbsObject::setTimeOut(unsigned int seconds)
{
  if(seconds>0)
    curl_easy_setopt(_cURL, CURLOPT_TIMEOUT, seconds);  
}

//_____________________________________________________________________________
/** Set scheme; http or https. */
void RdoAbsObject::setScheme(const char* scheme)
{
  _scheme = scheme;
}

//_____________________________________________________________________________
/** Set scheme; http or https. */
void RdoAbsObject::setHttps(bool useHttps)
{
  if(useHttps) setScheme("https");
  else setScheme("http");
}

//_____________________________________________________________________________
/** Set the format of the downloaded data. 
    Determines the return type of the document that the server produces as its response. 

    If 'html' is specified, the server produces a nicely formatted XHTML document (MIME type text/html), 
    which will display well in a browser but which is somewhat cumbersome to parse. 

    If 'plain' is specified, the server produces as minimalistic document of type plain text 
    (MIME type text/plain) document, which is easy to parse. 

    If you are writing an automated client, you probably want to specify plain here.
*/
void RdoAbsObject::setFormat(const char* format)
{
  _format = std::string(format);
}

//_____________________________________________________________________________
/** Set the randomization to use to generate the data. 

    If 'new' is specified, then a new randomization will created from the truly 
    random bitstream at RANDOM.ORG. This is probably what you want in most cases. 

    If 'id.identifier' is specified, the identifier is used to determine the randomization 
    in a deterministic fashion from a large pool of pregenerated random bits. 
    Because the numbers are produced in a deterministic fashion, specifying an id 
    basically uses RANDOM.ORG as a pseudo-random number generator. 

    The third ('date.iso-date') form is similar to the second; it allows the 
    randomization to be based on one of the daily pregenerated files. 
    This form must refer to one of the dates for which files exist, so it must 
    be the current day (according to UTC) or a day in the past. 
    The date must be in ISO 8601 format (i.e., YYYY-MM-DD) or one of the two 
    shorthand strings today or 'yesterday'.
*/
void RdoAbsObject::setRandomization(const char* rnd)
{
  _rnd = std::string(rnd);
}

//_____________________________________________________________________________
/** Set number of data points requested. */
void RdoAbsObject::setNum(unsigned int num)
{
  _num = num;
}

//_____________________________________________________________________________
/** Set the url to use when downloading. 
    If no parameter is given, the derived buildUrl method is called.
*/
void RdoAbsObject::setUrl(const char* u)
{
  if(u && strlen(u)!=0) 
    sprintf(_url,"%s",u);
  else 
    buildUrl();

  curl_easy_setopt(_cURL, CURLOPT_URL, _url);
}

//_____________________________________________________________________________
/** Download the random data from random.org. 
    \return true if operation failed
*/
bool RdoAbsObject::downloadToStdOut()
{
  // set the libCURL url to download
  setUrl();
  // get it!
  CURLcode res = curl_easy_perform(_cURL);
  // perform checks
  if(checkCURLcode(res)) return true;
  else return false;
}

//_____________________________________________________________________________
/** Set the output filename. */
void RdoAbsObject::setOutFileName(const char* fileName)
{
  _outFileName = std::string(fileName);
}

//_____________________________________________________________________________
/** Set the append-to-file flag. */
void RdoAbsObject::setAppend(bool append)
{
  _append = append;
}

//_____________________________________________________________________________
/** Download the random data from random.org. 
    \return true if operation failed
*/
bool RdoAbsObject::downloadToFile()
{
  // mode
  std::string mode("w");
  if(_append) mode = "a";

  // open file
  FILE *fp = fopen(_outFileName.c_str(), mode.c_str());
  if(fp == NULL) {
    std::cerr << "Error: Failed to open file " << _outFileName.c_str() << std::endl;
    return true;
  }

  // pass file pointer to the callback function
  curl_easy_setopt(_cURL, CURLOPT_WRITEDATA, fp);

  // set the libCURL url to download
  setUrl();

  // get it!
  CURLcode res = curl_easy_perform(_cURL);

  // close file
  fclose(fp);

  // perform checks
  if(checkCURLcode(res)) return true;
  else if(checkHTTPcode()) return true;
  //else if(checkBytesDnld()) return true;
  else return false;
}

//_____________________________________________________________________________
/** Set flag to keep data in memory; don't write to file or std::cout. */
void RdoAbsObject::setInMemory(bool inMem)
{
  _inMemory = inMem;
}

//_____________________________________________________________________________
/** Download the random data from random.org into internal memory. 
    \return true if operation failed
*/
bool RdoAbsObject::downloadToMemory()
{
  // initialize downloaded memory struct
  struct CurlMem cMem;
  cMem.memory = (char*)malloc(1); // will be grown as needed by the WriteMemoryCallback method
  cMem.size   = 0;                // no data at this point

  // send all data to writeMemoryCallback function
  curl_easy_setopt(_cURL, CURLOPT_WRITEFUNCTION, writeMemoryCallback);
  // we pass our 'CurlMem' struct to the callback function
  curl_easy_setopt(_cURL, CURLOPT_WRITEDATA, (void*)&cMem);

  // set the libCURL url to download
  setUrl();

  // get it!
  CURLcode res = curl_easy_perform(_cURL);
  // printf("%lu bytes retrieved\n", (long)cMem.size);

  // perform checks
  if(checkCURLcode(res)) return true;
  else if((long)cMem.size <= 0) return true;
  else{
    // write to internal memory
    parseMemory(cMem);
  }

  // free downloaded memory
  if(cMem.memory){
    delete [] cMem.memory;
    cMem.size = 0;
  } 

  // return failed
  return false;  
}

//_____________________________________________________________________________
/** Genericc download data. */
bool RdoAbsObject::downloadData()
{
  if(_inMemory) return downloadToMemory();
  else if(_outFileName!="") return downloadToFile();
  else return downloadToStdOut();
}

//_____________________________________________________________________________
/** static memory callback method for libCURL. */
size_t RdoAbsObject::writeMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
  // init/re-cast inputs
  size_t realsize = size * nmemb;
  struct CurlMem *mem = (struct CurlMem *)userp;

  // allocate memory
  mem->memory = (char*)realloc(mem->memory, mem->size + realsize + 1);
  if(mem->memory == NULL) {
    std::cerr << "Fatal: RdoAbsObject::WriteMemoryCallback: Not enough memory (realloc returned NULL)" << std::endl;
    exit(-1);
  }

  // copy recieved data to memory
  memcpy(&(mem->memory[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;

  // return the actual size of memory block
  return realsize;
}

//_____________________________________________________________________________
/** Check returned cURL code. 
    \return true if cURL operation failed
*/
bool RdoAbsObject::checkCURLcode(CURLcode res)
{
  if(res != CURLE_OK){
    std::cerr << "Error: cURL Failed: " << curl_easy_strerror(res) << std::endl;
    return true;
  }
  return false;
}

//_____________________________________________________________________________
/** Check returned HTTP response code. 
    \return true if HTTP get request failed
*/
bool RdoAbsObject::checkHTTPcode()
{
  unsigned int responseCode;
  curl_easy_getinfo(_cURL, CURLINFO_RESPONSE_CODE, &responseCode);
  if(responseCode != 200){
    std::cerr << "Error: random.org returned HTTP status = " << responseCode << std::endl;
    return true;
  }
  return false;
}

//_____________________________________________________________________________
/** Check number of bytes downloaded in last transfer. 
    \return true if zero bytes recived
*/
bool RdoAbsObject::checkBytesDnld()
{
  // Pass a pointer to a double to receive the total amount of bytes that were downloaded. 
  // The amount is only for the latest transfer and will be reset again for each new transfer. 
  double nBytes;
  curl_easy_getinfo(_cURL, CURLINFO_SIZE_DOWNLOAD, &nBytes);
  if(nBytes <= 0.){
    std::cerr << "Error: random.org returned zero bytes" << std::endl;
    return true;
  }
  return false;
}
