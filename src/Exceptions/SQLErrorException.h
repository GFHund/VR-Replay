#ifndef __SQL_ERROR_EXCEPTION__
#define __SQL_ERROR_EXCEPTION__

#include <exception>
#include <string>

class SQLErrorException: public std::exception{
    private:
    std::string mErrorMsg;

    public:
    SQLErrorException(std::string errorMsg){
        mErrorMsg = errorMsg;
    }
    virtual const char* what() const throw()
    {
        std::string error = std::string("Error in the SQL Statement: ");
        error += mErrorMsg;
        return error.c_str();
    }
};

#endif