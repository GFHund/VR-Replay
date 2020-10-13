#include "EventManager.h"
#include <stdexcept>

EventManager* EventManager::instance = nullptr;

EventManager::EventManager(){

}

EventManager* EventManager::getInstance(){
    if(instance == nullptr){
        instance = new EventManager();
    }
    return instance;
}

void EventManager::subscribe(std::string name,AbstractEvent* event){
    try{
        std::vector<AbstractEvent*> vec = mEvents.at(name);
        vec.push_back(event);
    }catch(std::out_of_range e){
        std::vector<AbstractEvent*> vec;
        vec.push_back(event);
        mEvents.insert(std::pair<std::string,std::vector<AbstractEvent*>>(name,vec));
    }
}
void EventManager::fireEvent(std::string name,EventParam* param){
    try{
        std::vector<AbstractEvent*> vec = mEvents.at(name);
        for(auto it = vec.begin();it != vec.end();++it){
            (*it)->event(name,param);
            
        }
    } catch(std::out_of_range e){
        throw e;
    }
}