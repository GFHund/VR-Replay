#ifndef __DATA_LAYER__
#define __DATA_LAYER__

#include "../EventSystem/AbstractEvent.h"
#include "../vendor/sqlite/sqlite3.h"
#include "CarMotionData.h"
#include <vector>

class DataLayer: public AbstractEvent{
    private:
    DataLayer();
    DataLayer(DataLayer & copy);
    ~DataLayer();


    static DataLayer* instance;

    protected:
    sqlite3* mDb;
    void openFileEvent(std::string filePathName,std::string filePath);

    public:
    void init();
    std::vector<const char*> getSessions();
    std::vector<CarMotionData> getMotionDataFromeSessionTime(float sessionTime);
    float getMaxTime();
    void event(std::string eventName,EventParam* param = nullptr);
    static DataLayer* getInstance();
};

#endif