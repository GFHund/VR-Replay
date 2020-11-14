#include "Replay.h"
#include "../EventSystem/EventManager.h"
#include "../Data/DataLayer.h"
#include "../shader/VectorShaderParam.h"
#include "../Exceptions/DatabaseNotOpenException.h"

Replay::Replay(){
    std::cout << "Replay Class Constructor" << std::endl;
    EventManager::getInstance()->subscribe("DataOpened",this);
    EventManager::getInstance()->subscribe("PlayEvent",this);
    EventManager::getInstance()->subscribe("PauseEvent",this);
    mReplayTime = 0.0f;
}
void Replay::init(Renderer renderer){
    this->mPlay = false;
    this->mReplayTime = 0.0f;
    Shader* shader = Shader::getShaderPrograms("./vertexProgramColor.glsl","./fragmentProgramColor.glsl");
    //this->test = new Cube();
    //this->test->setShader(shader);
    //renderer.init3DObject(test);
    
    for(int i=0;i<22;i++){
        cars[i] = new Cube();
        cars[i]->setShader(shader);
        //cars[i]->addShaderParam("color",new VectorShaderParam(dogEngine::CVector3(1.0,0,0)));
        renderer.init3DObject(cars[i]);
    }
     
}
void Replay::render(float deltaTime, Renderer renderer){
  renderer.setCameraPos(dogEngine::CVector3(0,0,0));
  renderer.setCameraRot(dogEngine::CQuaternion());
  if(this->mPlay && this->mReplayTime < this->mMaxReplayTime){
      this->mReplayTime += deltaTime;
  }
  //renderer.render3DObject(test);
  
	try{
		std::vector<CarMotionData> carMotionData = DataLayer::getInstance()->getMotionDataFromeSessionTime(this->mReplayTime);
		for(int i=0;i<22;i++){
			std::cout << "render Car" << i << std::endl;
			dogEngine::CVector3 pos = dogEngine::CVector3(carMotionData[i].m_worldPositionX,carMotionData[i].m_worldPositionY,carMotionData[i].m_worldPositionZ);
			cars[i]->setPos(pos);
			
			dogEngine::CVector3 dir = dogEngine::CVector3(carMotionData[i].m_worldForwardDirX,carMotionData[i].m_worldForwardDirY,carMotionData[i].m_worldForwardDirZ);
			dogEngine::CVector3 originDir = dogEngine::CVector3(0,0,-1);
			dogEngine::CVector3 rotationVec = dir.crossProduct(originDir);
			float angle = dir * originDir;
			dogEngine::CQuaternion rot = dogEngine::CQuaternion(rotationVec,angle);
			cars[i]->setRotation(rot);
			cars[i]->setScale(dogEngine::CVector3(0,0,2));
			
			renderer.render3DObject(cars[i]);
		}
	}catch(DatabaseNotOpenException e){
		for(int i=0;i<22;i++){
			std::cout << "render Car" << i << std::endl;
			renderer.render3DObject(cars[i]);
		}
     
	}
    
    
}
void Replay::finish(Renderer renderer){
  
  for(int i=0;i<22;i++){
    delete cars[i];    
  }
   
   //delete test;
}
void Replay::event(std::string eventName,EventParam* param){
    //std::cout << eventName << std::endl;
    if(eventName.compare("DataOpened") == 0){
        mReplayTime = 0.0f;
		try{
			DataLayer::getInstance()->getMotionDataFromeSessionTime(0.0f);
			this->mMaxReplayTime = DataLayer::getInstance()->getMaxTime();
		}catch(DatabaseNotOpenException e){
			std::cout << "Error Database not opened. Event: DataOpened" << std::endl;
		}
        
    }
    else if(eventName.compare("PlayEvent") == 0){
        this->mPlay = true;
    }
    else if(eventName.compare("PauseEvent") == 0){
        this->mPlay = false;
    }
    else if(eventName.compare("StopEvent") == 0){
        this->mPlay = false;
        this->mReplayTime = 0.0f;
    }
}