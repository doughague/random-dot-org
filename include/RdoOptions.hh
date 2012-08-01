/** \file RdoOptions.hh 
    \brief Header for options class
*/
#ifndef RDOOPTIONS
#define RDOOPTIONS

#include <string>

/** \class RdoOptions 
    \brief Holding and parsing program options.
*/
class RdoOptions { 
public:
  RdoOptions();
  RdoOptions(int argc, char** argv);
  RdoOptions(const RdoOptions& other);
  inline virtual ~RdoOptions() {}

  void parseCmdLine(int argc, char** argv);

public:
  bool         help;         //<! print program help
  int          pLevel;       //<! print level

  std::string  agent;        //<! some servers don't like anon agents
  bool         useHTTPS;     //<! use https?
  std::string  proxy;        //<! proxy used by cURL
  std::string  proxyType;    //<! type of proxy used by cURL
  unsigned int timeout;      //<! time in seconds to wait for random.org

  std::string  outFile;      //<! name of file to which data is to be written
  bool         append;       //<! append to or overwrite the output file?

  std::string  format;       //<! format of downloaded data; plain or html
  std::string  rnd;          //<! randomization to use to generate the data
  unsigned long columns;      //<! number of columns for file formating
  unsigned long num;          //<! number of random units to download

  std::string  type;         //<! type of data to download

  bool         quota;        //<! run quota checker (before dowloading other randoms)
  std::string  ip;           //<! IP address for quota-checker

  // bool         integers;     //<! download integers (only)
  long int     min;          //<! minimum value
  long int     max;          //<! maximum value
  std::string  base;         //<! base for number integer system

  // bool         sequence;     //<! download sequence (only)

  // bool         strings;      //<! download strings (only)
  unsigned int length;       //<! length of requested strings
  bool         digits;       //<! allow digit characters in strings
  bool         upper;        //<! allow uppercase characters in strings
  bool         lower;        //<! allow lowercase characters in strings
  bool         unique;       //<! whether the strings picked should be unique
};

#endif // RDOOPTIONS
