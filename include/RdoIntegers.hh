/** \file RdoIntegers.hh 
    \brief Header for integers class
*/
#ifndef RDOINTEGERS
#define RDOINTEGERS

#include <vector>
#include "RdoAbsObject.hh"

/** \class RdoIntegers 
    \brief Get integers from random.org.
*/
class RdoIntegers : public RdoAbsObject { 
public:
  RdoIntegers();
  RdoIntegers(const RdoIntegers& other);
  inline virtual ~RdoIntegers() {}

  // range
  void setMin(long int min = 1);
  long int min() const { return _min; }
  void setMax(long int max = 1e4);
  long int max() const { return _max; }
  void setRange(long int min = 1, long int max = 1e4);

  // base
  void setBase(const char* base = "10");
  const char* base() const { return _base.c_str(); }

  // columns
  void setColumns(unsigned int columns = 1);
  unsigned int columns() const { return _columns; }

  // get a random integer from memory
  long int rndm();

  // examine the cached numbers
  std::vector<long int> cache() const { return _randData; }
  unsigned int currentCachePossition() const { return _pos; }

protected:
  long int _min;         //<! smallest value allowed for each integer
  long int _max;         //<! largest value allowed for each integer
  std::string _base;     //<! base that will be used to print the numbers
  unsigned int _columns; //<! number of columns in which the integers will be arranged
  std::vector<long int> _randData;  //<! in-memory downloaded random numbers
  unsigned int _pos;                //<! current possition in random data array

  virtual void buildUrl();
  virtual void parseMemory(struct RdoAbsObject::CurlMem cMem);
};

#endif // RDOINTEGERS
