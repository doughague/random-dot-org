/** \file RdoStrings.hh 
    \brief Header for strings class
*/
#ifndef RDOSTRINGS
#define RDOSTRINGS

#include <vector>
#include "RdoAbsObject.hh"

/** \class RdoStrings 
    \brief Get strings from random.org.
*/
class RdoStrings : public RdoAbsObject { 
public:
  RdoStrings();
  RdoStrings(const RdoStrings& other);
  inline virtual ~RdoStrings() {}

  // length
  void setLength(unsigned int length = 8);
  unsigned int length() const { return _length; }

  // types of characters
  void setDigits(bool digits = true);
  bool digits() const { return _digits; }
  void setUpper(bool upper = true);
  bool upper() const { return _upper; }
  void setLower(bool lower = true);
  bool lower() const { return _lower; }
  void setUnique(bool unique = true);
  bool unique() const { return _unique; }

  // get a random string from memory
  std::string rndm();

  // examine the cached strings
  std::vector<std::string> cache() const { return _randData; }
  unsigned int currentCachePossition() const { return _pos; }

protected:
  unsigned int _length; //<! length of each string
  bool _digits;         //<! allow digit characters
  bool _upper;          //<! allow uppercase alphabetical characters
  bool _lower;          //<! allow lowercase alphabetical characters
  bool _unique;         //<! whether the strings picked should be unique
  std::vector<std::string> _randData;  //<! in-memory downloaded random numbers
  unsigned int _pos;                //<! current possition in random data array

  virtual void buildUrl();
  virtual void parseMemory(struct RdoAbsObject::CurlMem cMem);
  static std::string boolToCode(bool b);
};

#endif // RDOSTRINGS
