#include "Renderer.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "../linmath.h"
#include "../shader/ImageShaderParam.h"
#include "../shader/VectorShaderParam.h"

void Renderer::init(int width,int height){
  //---------------------- GLEW Commands
  std::cout << "GLEW Init" << std::endl;
  glewExperimental = GL_TRUE;
  GLenum err = glewInit();
  if (GLEW_OK != err)
  {
      std::cout << glewGetErrorString(err);
      return;
      fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
  }
  mWidth = width;
  mHeight = height;

  glClearColor(0,1,0,1);
  GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);
}

void getError(std::string funcName){
  GLenum glError = glGetError();
  switch(glError){
    case GL_INVALID_ENUM:
      std::cout << funcName;
      std::cout << " Invalid Enum" << std::endl;
      break;
    case GL_INVALID_VALUE:
      std::cout << funcName;
      std::cout << " Invalid Value" << std::endl;
      break;
    case GL_INVALID_OPERATION:
      std::cout << funcName;
      std::cout << " Invalid Operation" << std::endl;
      break;
    //case GL_INVALID:
    case GL_OUT_OF_MEMORY:
      std::cout << funcName;
      std::cout << " Out Of Memory" << std::endl;
      break;
    case GL_STACK_UNDERFLOW:
      std::cout << funcName;
      std::cout << " Stack Underflow" << std::endl;
      break;
    case GL_STACK_OVERFLOW:
      std::cout << funcName;
      std::cout << " Stack Overflow" << std::endl;
      break;
  }
}

int initShader(const char* vertexProgram,const char* fragmentProgram){
  GLuint vertex_buffer, vertex_shader, fragment_shader, program;
  std::cout << "Compile Shaders" << std::endl;
  //compile and Links programs
  vertex_shader = glCreateShader(GL_VERTEX_SHADER);

  glShaderSource(vertex_shader, 1, &vertexProgram, NULL);
  glCompileShader(vertex_shader);
  char shaderLog[1000];
  int sizeLog;
  glGetShaderInfoLog(vertex_shader,1000,&sizeLog,shaderLog);
  std::cout << shaderLog << std::endl;

  fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

  glShaderSource(fragment_shader, 1, &fragmentProgram, NULL);
  glCompileShader(fragment_shader);

  glGetShaderInfoLog(fragment_shader,1000,&sizeLog,shaderLog);
  std::cout << shaderLog << std::endl;

  std::cout << "Link Shaders" << std::endl;

  program = glCreateProgram();
  std::cout << "createdProgram: " << program << std::endl;
  glAttachShader(program, vertex_shader);
  glAttachShader(program, fragment_shader);
  glLinkProgram(program);

  glGetProgramInfoLog(program,1000,&sizeLog,shaderLog);
  std::cout << shaderLog << std::endl;
  return program;
}

void Renderer::init3DObject(Abstract3dObject* obj){
  GLuint vertex_buffer, vertex_shader, fragment_shader, program,index_buffer;
  
  GLenum glError;
  unsigned int size = 0;
  unsigned int indexSize = 0;
  ModelData* vertices = obj->getModelData(size);
  unsigned short* indices = obj->getIndexData(indexSize);

  Shader* shader = obj->getShader();

  glGenBuffers(1, &vertex_buffer);
  getError("glGenBuffers");

  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
  getError("glBindBuffer");

  glBufferData(GL_ARRAY_BUFFER, sizeof(ModelData) * size, vertices, GL_STATIC_DRAW);
  getError("glBufferData");

  obj->setVertexBuffer(vertex_buffer);

  glGenBuffers(1,&index_buffer);
  getError("glGen Index Buffers");

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,index_buffer);
  getError("glBind Index Buffer");

  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * indexSize, indices, GL_STATIC_DRAW);
  getError("glBufferData");

  obj->setIndiceBuffer(index_buffer);

  unsigned int textureId = 0;
  glGenTextures(1, &textureId);
  getError("glGenTextures");

  glBindTexture(GL_TEXTURE_2D, textureId);
  getError("glBindTexture");

  std::map<std::string,AbstractShaderParam*> paramMap = obj->getShaderParamMap();
  for(auto it = paramMap.begin(); it != paramMap.end();it++){
    if(it->second->getClass().compare("Image") == 0){
      ImageShaderParam* shaderParam = (ImageShaderParam*)it->second;
      Image* image1 = shaderParam->getImage();
      GLint imageWidth = image1->getWidth();
      GLint imageHeight = image1->getHeight();
      unsigned char* image1Data = image1->getPixels();
      glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
      std::cout << "image Width: " << imageWidth << std::endl;
      std::cout << "image Height: " << imageHeight << std::endl;
      glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,imageWidth,imageHeight,0,GL_RGBA,GL_UNSIGNED_BYTE,image1Data);
      getError("glTexImage2d");

      image1->setGlTexId(textureId);
    }
  }

  program = initShader(shader->getVertexProgram(), shader->getFragmentProgram());

  shader->setGlShaderId(program);
}

void Renderer::render3DObject(Abstract3dObject* obj){
  float ratio;
  int width = mWidth, height = mHeight;
  mat4x4 m, p, mvp;
  unsigned int size = 0;
  unsigned int indiceSize = 0;
  ModelData* vertices = obj->getModelData(size);
  unsigned short* indices = obj->getIndexData(indiceSize);

  Shader* shader = obj->getShader();
  GLuint program = shader->getGlShaderId();
  GLint mvp_location, texture_location;//vpos_location, vcol_location,vtex_location,
  GLenum glError;
  int vertex_buffer = obj->getVertexBuffer();
  int index_buffer = obj->getIndiceBuffer();

  mvp_location = glGetUniformLocation(program, "MVP");
      
  ratio = width / (float) height;
  getError("Vor glViewport");
  glViewport(0, 0, width, height);
  getError("glViewport");
  glClear(GL_COLOR_BUFFER_BIT);
  getError("glClear");

  glEnableVertexAttribArray(1);
  getError("glEnableVertexAttribArray");
  getError("glBindBuffer");
  glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,
                        sizeof(vertices[0]),(void*)(sizeof(float) * 3));
  getError("glVertexAttribPointer");
  
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE,
                        sizeof(vertices[0]), (void*) 0);
  getError("glVertexAttribPointer");

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,index_buffer);

  dogEngine::CMatrix4 mMat = obj->getTransformationMatrix();
  dogEngine::CMatrix4 viewMat = this->mCameraRot.getMatrix() * dogEngine::CMatrix4::getTranslationMatrix(dogEngine::CVector4(this->mCameraPos));
  viewMat = viewMat.inverse();

  dogEngine::CMatrix4 perspectiv = dogEngine::CMatrix4::getPerspective(60,ratio,0.1f,2000.0f);

  dogEngine::CMatrix4 mvpMat = perspectiv * viewMat * mMat;
  float mvpArray[16]; 
  mvpMat.getArray(mvpArray,true);

  glUseProgram(program);
  getError("glUseProgram");
  glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*) mvpArray);
  getError("glUniformMatrix4fv");

  glActiveTexture(GL_TEXTURE0);
  getError("glActiveTexture");
  std::map<std::string,AbstractShaderParam*> paramMap = obj->getShaderParamMap();

  for(auto it = paramMap.begin(); it != paramMap.end();it++){
    if(it->second->getClass().compare("Image") == 0){
      texture_location = glGetUniformLocation(program,it->first.c_str());
      ImageShaderParam* imageParam = (ImageShaderParam*)it->second;
      Image* image1 = imageParam->getImage();
      
      unsigned int textureId = image1->getGlTexId();

      glBindTexture(GL_TEXTURE_2D,textureId);
      getError("glBindTexture");
      glUniform1i(texture_location,0);
      getError("glUniform1i");
    }
    else if(it->second->getClass().compare("Vector") == 0){

      int varLocation = glGetUniformLocation(program,it->first.c_str());
      VectorShaderParam* vectorParam = (VectorShaderParam*)it->second;
      dogEngine::CVector3 vec = vectorParam->getVector();
      std::array<float,3> vecArray = vec.getArray();

      glUniform3fv(varLocation,3,vecArray.data());
      
    }
  }

  glDrawElements(GL_TRIANGLES, indiceSize,GL_UNSIGNED_SHORT,(void*)0);
  getError("glDrawElements");

  glDisableVertexAttribArray(0);
  getError("glDisableVertexAttribArray(0)");
  glDisableVertexAttribArray(1);
  getError("glDisableVertexAttribArray(1)");
}

void Renderer::setCameraPos(dogEngine::CVector3 pos){
  this->mCameraPos = pos;
}
void Renderer::setCameraRot(dogEngine::CQuaternion rot){
  this->mCameraRot = rot;
}
void Renderer::setCameraToPos(dogEngine::CVector3 pos, float angleX,float angleY, float distance){
  dogEngine::CVector3 originPos = dogEngine::CVector3(0,0,-1);
  dogEngine::CQuaternion quad1 = dogEngine::CQuaternion(dogEngine::CVector3(1,0,0),angleX);
  dogEngine::CQuaternion quad2 = dogEngine::CQuaternion(dogEngine::CVector3(0,1,0),angleY);
  dogEngine::CQuaternion result = quad1 * quad2;
  this->mCameraRot = result;

  dogEngine::CVector3 dirVec = result.getMatrix().multiplyVec3(originPos);
  dogEngine::CVector3 resultPos = pos + dirVec * (-1 * distance);
  this->mCameraPos = resultPos;
}