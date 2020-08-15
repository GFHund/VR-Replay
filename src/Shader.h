#ifndef __SHADER__
#define __SHADER__
#include <string>

class Shader{
    private:
    std::string vertexProgram;
    std::string fragmentProgram;
    unsigned int glShaderId;
    public:
    Shader(std::string vertexProgram,std::string fragmentProgram);

    static Shader* getShaderPrograms(const char* vertextFile,const char* fragmentFile);

    const char* getVertexProgram();
    const char* getFragmentProgram();

    void setGlShaderId(unsigned int glShaderId);
    unsigned int getGlShaderId();
};

#endif