/** \file RdoAbsObject.hh 
    \brief Header for abstract base
*/
#ifndef RDOABSOBJECT
#define RDOABSOBJECT

#include <string>       // std::string type
#include <curl/curl.h>  // cURL library

/** \class RdoAbsObject 
    \brief Abstract base class for random.org client.
    
    A minimal concrete implementation of this class should implement 
    the buildUrl() method to construct the actual url passed to random.org 
    and parseMemory(struct CurlMem cMem) method to transform the downloaded 
    memory to a statically typed in-memory structure suitable for retrieving the 
    data.

    \todo Add connection username/password interface.
    \todo Add proxy username/password interface.
*/
class RdoAbsObject { 
public:
  RdoAbsObject();
  RdoAbsObject(const RdoAbsObject& other);
  virtual ~RdoAbsObject();

  // get the libCURL object pointer
  CURL* cURL() const { return _cURL; }
  // agent (identify yourself to random.org)
  void setAgent(const char* agent);
  const char* agent() const { return _agent.c_str(); }
  // proxy
  void setProxy(const char* proxy);
  const char* proxy() const { return _proxy.c_str(); }
  void setProxyType(const char* proxyType = "HTTP");
  const char* proxyType() const { return _proxyType.c_str(); }
  // time-out
  void setTimeOut(unsigned int seconds = 120);

  // random.org url
  const char* rdoUrl() const { return _rdoUrl.c_str(); }
  // set/get secure HTTP connect
  void setScheme(const char* scheme);
  const char* scheme() const { return _scheme.c_str(); }
  void setHttps(bool useHttps = true);
  // download format
  void setFormat(const char* format = "plain");
  const char* format() const { return _format.c_str(); }
  // randomization
  void setRandomization(const char* rnd = "new");
  const char* randomization() const { return _rnd.c_str(); }
  // number (amount) of data
  void setNum(unsigned int num = 10);
  unsigned int num() const { return _num; }

  // url address
  void setUrl(const char* u = 0);
  const char* url() const { return _url; }

  // file options
  const char* outFileName() const { return _outFileName.c_str(); }
  void setOutFileName(const char* fileName);
  bool append() const { return _append; }
  void setAppend(bool append=true);
  void setInMemory(bool inMem=true);
  bool inMemory() const { return _inMemory; }

  // download data
  bool downloadToStdOut();
  bool downloadToFile();
  bool downloadToMemory();
  bool downloadData();

  //! memory struct for callback method for libCURL.
  struct CurlMem {
    char* memory;
    size_t size;
  };

protected:
  std::string _scheme;       //<! http or https
  std::string _rdoUrl;       //<! base url for website
  std::string _format;       //<! format of downloaded data; plain or html
  std::string _rnd;          //<! randomization to use to generate the data
  unsigned int _num;         //<! number of random units to download;
  char* _url;                //<! the complete url for downloading data

  virtual void buildUrl() = 0;
  virtual void parseMemory(struct CurlMem cMem) = 0;

private:
  CURL* _cURL;               //<! libCURL object
  std::string _agent;        //<! some servers don't like anon agents
  std::string _proxy;        //<! proxy used by cURL
  std::string _proxyType;    //<! type of proxy used by cURL
  bool _inMemory;            //<! keep data in memory (don't write to file or cout)
  std::string _outFileName;  //<! name of file to which data is to be written
  bool _append;              //<! append-to or overwrite the output file?

  static size_t writeMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp);
  bool checkCURLcode(CURLcode res);
  bool checkHTTPcode();
  bool checkBytesDnld();
};

#endif // RDOABSOBJECT
