/** \file RdoSequence.hh 
    \brief Header for sequence class
*/
#ifndef RDOSEQUENCE
#define RDOSEQUENCE

#include "RdoIntegers.hh"

/** \class RdoSequence 
    \brief Get a sequence of integers from random.org.
*/
class RdoSequence : public RdoIntegers { 
public:
  RdoSequence();
  RdoSequence(const RdoSequence& other);
  inline virtual ~RdoSequence() {}

protected:
  virtual void buildUrl();
};

#endif // RDOSEQUENCE
