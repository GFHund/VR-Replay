#include "Shader.h"

#include <iostream>
#include <fstream>
#include "Exceptions/ShaderReadFailureException.h"

Shader::Shader(std::string vertexProgram1,std::string fragmentProgram1){
    this->fragmentProgram = fragmentProgram1;
    this->vertexProgram = vertexProgram1;
}

std::string getShaderProgram(const char* filename){
    std::ifstream ifs;
    ifs.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    std::string program;
    try{
        ifs.open(filename,std::ifstream::in | std::ifstream::binary);
    }
    catch(std::ifstream::failure e){
        throw ShaderReadFailureException("On Open",ifs.eof(),ifs.fail(),ifs.bad());
    }
    int length = 0;
    try{
        ifs.seekg(0,ifs.end);
        length = ifs.tellg();
        ifs.seekg(0,ifs.beg);
    }catch(std::ifstream::failure e){
        throw ShaderReadFailureException("determine File Length",ifs.eof(),ifs.fail(),ifs.bad());
    }
    if(length <= 0){
        throw ShaderReadFailureException("file length is less or equal to null",ifs.eof(),ifs.fail(),ifs.bad());
    }
    //length = length - 10;
    //std::cout << length << std::endl;
    char* buffer = new char[length+1];
    try{
        ifs.read(buffer,length);
        
    }catch(std::ifstream::failure e){
        //std::cout << length << std::endl;
        
        if(!(ifs.eof() && ifs.fail())){
            throw ShaderReadFailureException("read of File not successfull",ifs.eof(),ifs.fail(),ifs.bad());
        }
    }
    buffer[length] = '\0';
    //std::cout << buffer << std::endl;
    for(int i=0;i<length;i++){
        if(buffer[i] == '\0'){
            break;
        }
        if((buffer[i] >= 0x20 && buffer[i] <= 0x7D)|| buffer[i] == 0x0d || buffer[i] == 0x0a){
            program += buffer[i];
        }
        
    }
    //std::cout << program << std::endl;
    ifs.close();
    return program;
}

Shader* Shader::getShaderPrograms(const char* vertexFile,const char* fragmentFile){
    std::string localVertexProgram;
    try{
        localVertexProgram = getShaderProgram(vertexFile);
    } catch(ShaderReadFailureException e){
        std::cout << "Exception in Vertex Program" << std::endl;
        std::cout << e.what() << std::endl;
        throw e;
    }
    std::string localFragmentProgram;
    try{
        localFragmentProgram = getShaderProgram(fragmentFile);
    } catch(ShaderReadFailureException e){
        std::cout << "Exception in Fragment Program" << std::endl;
        std::cout << e.what() << std::endl;
        throw e;
    }
    
    return new Shader(localVertexProgram, localFragmentProgram);
    
    //return nullptr;
}

const char* Shader::getVertexProgram(){
    return this->vertexProgram.c_str();
}
const char* Shader::getFragmentProgram(){
    return this->fragmentProgram.c_str();
}

void Shader::setGlShaderId(unsigned int glShaderId){
    this->glShaderId = glShaderId;
}
unsigned int Shader::getGlShaderId(){
    return this->glShaderId;
}