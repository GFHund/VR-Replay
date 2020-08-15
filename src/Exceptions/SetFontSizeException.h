#ifndef __SET_FONT_SIZE_EXCEPTION__
#define __SET_FONT_SIZE_EXCEPTION__

#include <exception>

class SetFontSizeException: public std::exception{
    const char* message;
    public:
    SetFontSizeException(const char* message){
        this->message = message;
    }
    
    virtual const char* what() const throw(){
        return message;
    }
};

#endif