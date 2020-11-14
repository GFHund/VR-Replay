#ifndef __FILE_NOT_FOUND_EXCEPTION__
#define __FILE_NOT_FOUND_EXCEPTION__
#include <exception>
#include <string>
class FileNotFoundException: public std::exception{
    private:
    std::string file;
    public:
    FileNotFoundException(std::string file){
        this->file = file;
    }
    virtual const char* what() const throw()
    {
        std::string ret = std::string("File Not found:");
        ret += this->file;
        return ret.c_str();
    }
};
#endif