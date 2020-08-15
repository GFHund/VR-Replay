#ifndef __LOADING_FONT_EXCEPTION__
#define __LOADING_FONT_EXCEPTION__

#include <exception>

class LoadingFontException: public std::exception{
    const char* message;
    public:
    LoadingFontException(const char* message){
        this->message = message;
    }
    
    virtual const char* what() const throw(){
        return message;
    }
};

#endif