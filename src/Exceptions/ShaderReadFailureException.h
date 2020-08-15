#ifndef __SHADER_READ_FAILURE__
#define __SHADER_READ_FAILURE__

#include <exception>

class ShaderReadFailureException: public std::exception{
    private: 
    std::string place;
    bool eof;
    bool fail;
    bool bad;

    public: 
    ShaderReadFailureException(std::string place,bool eof, bool fail,bool bad){
        this->place = place;
        this->eof = eof;
        this->fail = fail;
        this->bad = bad;
    }
    
    virtual const char* what() const throw()
    {
        //return "Shader Read Failure";
        std::string output = this->place;
        if(this->eof){
            output += "| End of File reached";
        }
        if(this->fail){
            output += "| Fail bit is set";
        }
        if(this->bad){
            output += "| bad bit is set";
        }
        
        return output.c_str();
    }
};

#endif