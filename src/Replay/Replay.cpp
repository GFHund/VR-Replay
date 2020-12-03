#include "Replay.h"
#include "../EventSystem/EventManager.h"
#include "../Data/DataLayer.h"
#include "../shader/VectorShaderParam.h"
#include "../Exceptions/DatabaseNotOpenException.h"
#include "../OpenGLHeaders.h"

Replay::Replay(){
    std::cout << "Replay Class Constructor" << std::endl;
    EventManager::getInstance()->subscribe("DataOpened",this);
    EventManager::getInstance()->subscribe("PlayEvent",this);
    EventManager::getInstance()->subscribe("PauseEvent",this);
    EventManager::getInstance()->subscribe("CursorPosCallback",this);
    EventManager::getInstance()->subscribe("KeyCallback",this);
    EventManager::getInstance()->subscribe("MouseButtonCallback",this);
    mReplayTime = 0.0f;
    cameraPos = dogEngine::CVector3();
    mMouseButtonPressed = false;
    mYRot=0.0;
    mXRot=0.0;
}

void Replay::handleKeyInput(int key, int scancode, int action, int mods){
  if(key == GLFW_KEY_W && action == GLFW_RELEASE){
    cameraPos += dogEngine::CVector3(0,0,-1);
  }
  if(key == GLFW_KEY_S && action == GLFW_RELEASE){
    cameraPos += dogEngine::CVector3(0,0,1);
  }
}

void Replay::init(Renderer renderer){
    this->mPlay = false;
    this->mReplayTime = 0.0f;
    Shader* shader = Shader::getShaderPrograms("./vertexProgramColor.glsl","./fragmentProgramColor.glsl");
    
    for(int i=0;i<22;i++){
        cars[i] = new Cube();
        cars[i]->setShader(shader);
        renderer.init3DObject(cars[i]);
    }
     
}
void Replay::render(float deltaTime, Renderer renderer){
  renderer.setCameraPos(cameraPos);
  dogEngine::CQuaternion rot = dogEngine::CQuaternion(dogEngine::CVector3(0,1,0),mYRot) 
    * dogEngine::CQuaternion(dogEngine::CVector3(1,0,0),mXRot);
  renderer.setCameraRot(rot);
  if(this->mPlay && this->mReplayTime < this->mMaxReplayTime){
      this->mReplayTime += deltaTime;
  }
  
	try{
		std::vector<CarMotionData> carMotionData = DataLayer::getInstance()->getMotionDataFromeSessionTime(this->mReplayTime);
		for(int i=0;i<22;i++){
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
    else if(eventName.compare("KeyCallback") == 0){
      try{
        int key = param->getInt("key");
        int scancode = param->getInt("scancode");
        int action = param->getInt("action");
        int mods = param->getInt("mods");
        handleKeyInput(key,scancode,action,mods);
      }catch(std::out_of_range e){
        std::cout << "Error while reading the params" << std::endl;
      }
    }
    else if(eventName.compare("MouseButtonCallback") == 0){
      int button = param->getInt("button");
      int action = param->getInt("action");
      if(button == GLFW_MOUSE_BUTTON_LEFT && action==GLFW_PRESS){
        mMouseButtonPressed = true;
        mXPos = -1.0;
        mYPos = -1.0;
      }
      if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE){
        mMouseButtonPressed = false;
        mXPos = -1.0;
        mYPos = -1.0;
      }
    }
    else if(eventName.compare("CursorPosCallback") == 0){
      double xPos = param->getDouble("xPos");
      double yPos = param->getDouble("yPos");
      if(mMouseButtonPressed){
        if(mXPos < 0.0 && mYPos < 0.0){
          mXPos = xPos;
          mYPos = yPos;
        } else {
          double deltaX = xPos - mXPos;
          double deltaY = yPos - mYPos;
          
          const double PI = 3.14159;
          mYRot += deltaX * PI/1800;
          
          if(mYRot > PI){
            mYRot -= 2*PI;
          }else if(mYRot < -PI){
            mYRot += 2*PI;
          }
          
          if((mXRot > -PI/2 && mXRot <= 0) || 
          (mXRot < -PI/2 && deltaY > 0) || 
          (mXRot > 0 && deltaY < 0) ){
            mXRot += deltaY * PI/1800;
          }
          
          mXPos = xPos;
          mYPos = yPos;
        }
        
      }
    }
}