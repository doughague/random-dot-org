/** \file RdoBytes.hh 
    \brief Header for integers class
*/
#ifndef RDOBYTES
#define RDOBYTES

#include <vector>
#include "RdoAbsObject.hh"

/** \class RdoBytes 
    \brief Get integers from random.org.
*/
class RdoBytes : public RdoAbsObject { 
public:
  RdoBytes();
  RdoBytes(const RdoBytes& other);
  inline virtual ~RdoBytes() {}

  // base
  void setBase(const char* base = "10");
  const char* base() const { return _base.c_str(); }

  // columns
  void setColumns(unsigned int columns = 1);
  unsigned int columns() const { return _columns; }

  // get a random byte (as int) from memory
  unsigned int rndm();

  // examine the cached numbers
  std::vector<unsigned int> cache() const { return _randData; }
  unsigned int currentCachePossition() const { return _pos; }

protected:
  std::string _base;     //<! base that will be used to print the numbers
  unsigned int _columns; //<! number of columns in which the integers will be arranged
  std::vector<unsigned int> _randData;  //<! in-memory downloaded random numbers
  unsigned int _pos;                //<! current possition in random data array

  virtual void buildUrl();
  virtual void parseMemory(struct RdoAbsObject::CurlMem cMem);
};

#endif // RDOBYTES
