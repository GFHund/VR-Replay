#ifndef __NORMALIZEZEROVECTOREXCEPTION__
#define __NORMALIZEZEROVECTOREXCEPTION__

#include <exception>

class NormalizeZeroVectorException : public std::exception{
public:
  NormalizeZeroVectorException();
  const char* what() const noexcept;
};

#endif
