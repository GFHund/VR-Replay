#include "EventParam.h"
#include <utility>
#include <exception>

EventParam::~EventParam(){
    for(std::map<std::string,ParamValue>::iterator it = mParams.begin();
    it!=mParams.end();++it){
        delete[] it->second.value;
    }
}
void EventParam::insertIntoMap(std::string name,char* value,int bytes){
    ParamValue obj;
    obj.num = bytes;
    obj.value = value;

    std::pair<std::string, ParamValue> insert;
    insert = std::make_pair(name, obj);
    mParams.insert( insert );
}
void EventParam::setInt( std::string name,int value){
    int bytes = sizeof(value);
    char* byteArray = (char *)&value;
    char* byteArray2 = new char[bytes];
    for(int i=0;i<bytes;i++){
        byteArray2[i] = byteArray[i];
    }
    insertIntoMap(name,byteArray2,bytes);
}
void EventParam::setFloat(std::string name,float value){
    int bytes = sizeof(value);
    char* floatArray = (char*)&value;
    char* copyArray = new char[bytes];
    for(int i=0;i<bytes;i++){
        copyArray[i] = floatArray[i];
    }
    insertIntoMap(name,copyArray,bytes);
}
void EventParam::setString(std::string name,std::string value){
    int bytes = value.length();
    const char* floatArray = value.c_str();
    char* copyArray = new char[bytes];
    for(int i=0;i<bytes;i++){
        copyArray[i] = floatArray[i];
    }
    insertIntoMap(name,copyArray,bytes);
}
int EventParam::getInt(std::string name){
    ParamValue val = mParams.at(name);
    if(val.num != sizeof(int)){
        throw std::exception();
    }
    int* value = (int*)val.value;
    return *value;
}
float EventParam::getFloat(std::string name){
    ParamValue val = mParams.at(name);
    if(val.num != sizeof(float)){
        throw std::exception();
    }
    float* value = (float*)val.value;
    return *value;
}
std::string EventParam::getString(std::string name){
    ParamValue val = mParams.at(name);
    return std::string(val.value);
}