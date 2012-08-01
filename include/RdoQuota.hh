/** \file RdoQuota.hh 
    \brief Header for quota class
*/
#ifndef RDOQUOTA
#define RDOQUOTA

#include "RdoAbsObject.hh"

/** \class RdoQuota 
    \brief random.org quota checker.
*/
class RdoQuota : public RdoAbsObject { 
public:
  RdoQuota();
  RdoQuota(const RdoQuota& other);
  inline virtual ~RdoQuota() {}

  // IP address
  void setIP(const char* ip);
  const char* ip() const { return _ip.c_str(); }

  // available bits
  unsigned long remainingBits() const { return _remainingBits; }
  bool withinQuota() const { return (_remainingBits>0); }

protected:
  std::string _ip;
  unsigned long _remainingBits;

  virtual void buildUrl();
  virtual void parseMemory(struct RdoAbsObject::CurlMem cMem);
};

#endif // RDOQUOTA


  // comand line for returning external ip
  // curl ifconfig.me
