#ifndef __INDEX_OUT_OF_BOUNDS_EXCEPTION__
#define __INDEX_OUT_OF_BOUNDS_EXCPETION__
#include <exception>
class IndexOutOfBoundsException: public std::exception{
    virtual const char* what() const throw()
    {
        return "Index out of Bounds Exception";
    }
};
#endif