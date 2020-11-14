#ifndef __DATABASE_NOT_OPEN_EXCEPTION__
#define __DATABASE_NOT_OPEN_EXCEPTION__

#include <exception>
class DatabaseNotOpenException:public std::exception{
    public:

    virtual const char* what() const throw()
    {
        return "Database is not open";
    }
};
#endif