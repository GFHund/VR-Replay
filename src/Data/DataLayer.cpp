#include "DataLayer.h"
#include "../EventSystem/EventManager.h"
#include "../Exceptions/FileNotFoundException.h"
#include "../Exceptions/DatabaseNotOpenException.h"
#include "../Exceptions/SQLErrorException.h"
#include "PacketMotionData.h"
#include <iostream>


DataLayer* DataLayer::instance = nullptr;

DataLayer::DataLayer(){
    mDb = nullptr;
}
DataLayer::DataLayer(DataLayer& copy){}
DataLayer::~DataLayer(){
    sqlite3_close(mDb);
}

DataLayer* DataLayer::getInstance(){
    if(instance == nullptr){
        instance = new DataLayer();
    }
    return instance;
}

void DataLayer::openFileEvent(std::string filePathName,std::string filePath){
    if(mDb != nullptr){
        sqlite3_close(mDb);
    }
    int rc;
    std::cout << filePath << std::endl;
    rc = sqlite3_open(filePath.c_str(),&mDb);
    if(rc){
        std::cout << "Can't open database: " << sqlite3_errmsg(mDb) << std::endl;
        sqlite3_close(mDb);
        mDb = nullptr;
        throw FileNotFoundException(filePath);
    }
    EventManager::getInstance()->fireEvent("DataOpened",nullptr);    
}

void DataLayer::init(){
    EventManager::getInstance()->subscribe("FileOpenEvent",this);
}
std::vector<const char*> DataLayer::getSessions(){
    if(mDb == nullptr){
		std::cout << "getSessions" << std::endl;
        throw DatabaseNotOpenException();
    }
    std::string sql = std::string("SELECT sessionUID FROM packets GROUP BY sessionUID");
    sqlite3_stmt* stmt;
    if(sqlite3_prepare_v2(mDb,sql.c_str(),sql.size(),&stmt,NULL) != SQLITE_OK){
        throw SQLErrorException(sqlite3_errmsg(mDb));
    }
    int ret_code = 0;
    std::vector<const char*> ret;
    while((ret_code = sqlite3_step(stmt)) == SQLITE_ROW){
        const char* uid = (const char*) sqlite3_column_text(stmt,0);
        std::cout << uid << std::endl;
        ret.push_back(uid);
    }
    return ret;
}
template<typename T>
T changeEndian(T insert){
    char* origin = (char*) &insert;
    T ret;
    char* result = (char*) &ret;
    for(int i=0;i < sizeof(T);i++){
        int reverseIndex = sizeof(T) - 1;
        reverseIndex = reverseIndex - i;
        result[i] = origin[reverseIndex];
    }
    return ret;
}

CarMotionData convertEndianMotionData(CarMotionData carMotionData){
    return carMotionData;
}

template<typename T>
T interpolateValues(T min,T max, float minSessionTime,float maxSessionTime,float sessionTime){
    float newMaxSessionTime = maxSessionTime - minSessionTime;
    float percentage = sessionTime/newMaxSessionTime;
    float newMaxValue = max - min;
    return percentage * newMaxValue;
}

CarMotionData interpolateMotionData(CarMotionData min,CarMotionData max,float minSessionTime,float maxSessionTime, float sessionTime){
    min = convertEndianMotionData(min);
    max = convertEndianMotionData(max);
    CarMotionData ret;
    ret.m_worldPositionX = interpolateValues<float>(min.m_worldPositionX,max.m_worldPositionX,minSessionTime,maxSessionTime,sessionTime);
    ret.m_worldPositionY = interpolateValues<float>(min.m_worldPositionY,max.m_worldPositionY,minSessionTime,maxSessionTime,sessionTime);
    ret.m_worldPositionZ = interpolateValues<float>(min.m_worldPositionZ,max.m_worldPositionZ,minSessionTime,maxSessionTime,sessionTime);

    ret.m_worldForwardDirX = interpolateValues<float>(min.m_worldForwardDirX,max.m_worldForwardDirX,minSessionTime,maxSessionTime,sessionTime);
    ret.m_worldForwardDirY = interpolateValues<float>(min.m_worldForwardDirY,max.m_worldForwardDirY,minSessionTime,maxSessionTime,sessionTime);
    ret.m_worldForwardDirZ = interpolateValues<float>(min.m_worldForwardDirZ,max.m_worldForwardDirZ,minSessionTime,maxSessionTime,sessionTime);

    return ret;
}


std::vector<CarMotionData> DataLayer::getMotionDataFromeSessionTime(float sessionTime){
    if(mDb == nullptr){
      //std::cout << "getMotionDataFromeSessionTime" << std::endl;
      throw DatabaseNotOpenException();
    }
    std::string maxPositionSql = std::string("SELECT packet, sessionTime FROM packets WHERE sessionTime > ");
    maxPositionSql += std::to_string(sessionTime);
    maxPositionSql += " AND packetId = 0 ORDER BY ABS(";
    maxPositionSql += std::to_string(sessionTime);
    maxPositionSql += " - sessionTime) LIMIT 1";

    sqlite3_stmt* stmtMaxPosition;
    if(sqlite3_prepare_v2(mDb,maxPositionSql.c_str(),maxPositionSql.size(),&stmtMaxPosition,NULL) != SQLITE_OK){
        throw SQLErrorException(sqlite3_errmsg(mDb));
    }
    int ret_code = 0;
    PacketMotionData* maxData = nullptr;
    float maxSessionTime = 0.0f;
    while((ret_code = sqlite3_step(stmtMaxPosition)) == SQLITE_ROW){
        maxData = (PacketMotionData*)sqlite3_column_blob(stmtMaxPosition,0);
        maxSessionTime = sqlite3_column_double(stmtMaxPosition,1);
    }
    std::string minPositionSql = std::string("SELECT packet, sessionTime FROM packets WHERE sessionTime <= ");
    minPositionSql += std::to_string(sessionTime);
    minPositionSql += " AND packetId = 0 ORDER BY ABS(";
    minPositionSql += std::to_string(sessionTime);
    minPositionSql += " - sessionTime) LIMIT 1";
    
    sqlite3_stmt* stmtMinPosition;
    if(sqlite3_prepare_v2(mDb,minPositionSql.c_str(),minPositionSql.size(),&stmtMinPosition,NULL) != SQLITE_OK){
        throw SQLErrorException(sqlite3_errmsg(mDb));
    }
    ret_code = 0;
    PacketMotionData* minData = nullptr;
    float minSessionTime = 0.0f;
    while((ret_code = sqlite3_step(stmtMinPosition)) == SQLITE_ROW){
        minData = (PacketMotionData*)sqlite3_column_blob(stmtMinPosition,0);
        minSessionTime = sqlite3_column_double(stmtMinPosition,1);
    }

    if(maxData != nullptr){
        maxData->m_header.m_sessionTime = changeEndian<float>(maxData->m_header.m_sessionTime);
        std::cout << maxData->m_header.m_sessionTime << std::endl;
    }
    else {
        std::cout << "max data is null" << std::endl;
    }
    if(minData != nullptr){
        std::cout << minData->m_header.m_sessionTime << std::endl;
    } else {
        std::cout << "min data is null" << std::endl;
    }
    std::vector<CarMotionData> ret;
    if(maxData == nullptr || minData == nullptr){
        if(maxData != nullptr){
            for(int i=0;i<22;i++){
                ret.push_back(maxData->m_carMotionData[i]);
            }
        }
        else if(minData != nullptr){
            for(int i=0;i<22;i++){
                ret.push_back(minData->m_carMotionData[i]);
            }
        }
    }
    else {

        for(int i=0;i<22;i++){
            CarMotionData interpolatedData = interpolateMotionData(minData->m_carMotionData[i],maxData->m_carMotionData[i],minSessionTime,maxSessionTime,sessionTime);
            ret.push_back(interpolatedData);
        }
        
    }

    return ret;
}
float DataLayer::getMaxTime(){
    if(mDb == nullptr){
		std::cout << "getMaxTime" << std::endl;
        throw DatabaseNotOpenException();
    }
    std::string sql = std::string("SELECT sessionTime FROM packets ORDER BY sessionTime DESC LIMIT 1");
    sqlite3_stmt* stmt;
    if(sqlite3_prepare_v2(mDb,sql.c_str(),sql.size(),&stmt,NULL) != SQLITE_OK){
        throw SQLErrorException(sqlite3_errmsg(mDb));
    }
    int ret_code = 0;
    float ret;
    while((ret_code = sqlite3_step(stmt)) == SQLITE_ROW){
        ret = sqlite3_column_double(stmt,0);
    }
    return ret;
}
void DataLayer::event(std::string eventName,EventParam* param){
    if(eventName.compare("FileOpenEvent") == 0){
        std::string filePath = param->getString("FilePath");
        std::string filePathName = param->getString("FilePathName");
        openFileEvent(filePath,filePathName);
    }
}