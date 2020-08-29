#ifndef __RENDERING_FONT_EXCEPTION__
#define __RENDERING_FONT_EXCEPTION__

#include <exception>

class RenderingFontException: public std::exception{
    const char* message;
    public:
    RenderingFontException(const char* message){
        this->message = message;
    }
    
    virtual const char* what() const throw(){
        return message;
    }
};

#endif