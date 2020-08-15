#ifndef __INIT_FONT_EXCEPTION__
#define __INIT_FONT_EXCEPTION__

#include <exception>

class InitFontException: public std::exception{
    const char* message;
    public:
    InitFontException(const char* message){
        this->message = message;
    }
    
    virtual const char* what() const throw(){
        return message;
    }
};

#endif