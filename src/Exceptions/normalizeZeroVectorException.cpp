#include "normalizeZeroVectorException.h"

NormalizeZeroVectorException::NormalizeZeroVectorException(){}

const char* NormalizeZeroVectorException::what()const noexcept{
  return "You tryed to normalize a Zero Vector. This is equal with a division by zero";
}
