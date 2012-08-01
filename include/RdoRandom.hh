/** \file RdoRandom.hh 
    \brief Header for random (fractions) class
*/
#ifndef RDORANDOM
#define RDORANDOM

#include <vector>
#include "RdoAbsObject.hh"

/** \class RdoRandom 
    \brief Get random numbers in [0,1] (decimal fractions) from random.org.

    This class also includes methods for transforming the numbers into 
    some common simple distributions. Named Rdo-"Random" since this is 
    generally the most versatile form of random numbers.
*/
class RdoRandom : public RdoAbsObject { 
public:
  RdoRandom();
  RdoRandom(const RdoRandom& other);
  inline virtual ~RdoRandom() {}

  // decimals
  void setDecimals(unsigned int decimals = 8);
  unsigned int decimals() const { return _decimals; }

  // columns
  void setColumns(unsigned int columns = 1);
  unsigned int columns() const { return _columns; }

  // get a random number from memory
  double rndm();

  // examine the cached numbers
  std::vector<double> cache() const { return _randData; }
  unsigned int currentCachePossition() const { return _pos; }

protected:
  unsigned int _decimals;  //<! decimals (number of digits)
  unsigned int _columns;   //<! number of columns in which the integers will be arranged
  std::vector<double> _randData;  //<! in-memory downloaded random numbers
  unsigned int _pos;              //<! current possition in random data array

  virtual void buildUrl();
  virtual void parseMemory(struct RdoAbsObject::CurlMem cMem);
};

#endif // RDORANDOM
