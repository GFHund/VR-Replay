#include "Renderer.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "../linmath.h"

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
  //std::cout << "getError"<<std::endl;
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
  //glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
  //const char* vertexProgram = shader->getVertexProgram();
  glShaderSource(vertex_shader, 1, &vertexProgram, NULL);
  glCompileShader(vertex_shader);
  char shaderLog[1000];
  int sizeLog;
  glGetShaderInfoLog(vertex_shader,1000,&sizeLog,shaderLog);
  std::cout << shaderLog << std::endl;

  fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  //glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
  //const char* fragmentProgram = shader->getFragmentProgram();
  glShaderSource(fragment_shader, 1, &fragmentProgram, NULL);
  glCompileShader(fragment_shader);

  glGetShaderInfoLog(fragment_shader,1000,&sizeLog,shaderLog);
  std::cout << shaderLog << std::endl;

  std::cout << "Link Shaders" << std::endl;

  program = glCreateProgram();
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
  Image* image1 = obj->getImage(0);
  Shader* shader = obj->getShader();

  glGenBuffers(1, &vertex_buffer);
  getError("glGenBuffers");

  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
  getError("glBindBuffer");

  //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
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
  ////glTexImage2D(GL_TEXTURE_2D,0,GL_RED,640,480,0,GL_RED,GL_UNSIGNED_BYTE,image);
  GLint imageWidth = image1->getWidth();
  GLint imageHeight = image1->getHeight();
  unsigned char* image1Data = image1->getPixels();
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
  glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,imageWidth,imageHeight,0,GL_RGBA,GL_UNSIGNED_BYTE,image1Data);
  getError("glTexImage2d");

  image1->setGlTexId(textureId);

  program = initShader(shader->getVertexProgram(), shader->getFragmentProgram());

  shader->setGlShaderId(program);



  //glEnableVertexAttribArray(0);
  
  /*
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                        sizeof(vertices[0]), (void*) (sizeof(float) * 2));
  glError = glGetError();
  if(glError = GL_INVALID_ENUM){
    std::cout << "glVertexAttribPointer No2 has invalid Enum"<< std::endl;
  }
  */
  //glEnableVertexAttribArray(1);
  
  
}

void Renderer::render(){

}

void Renderer::render3DObject(Abstract3dObject* obj){
  float ratio;
  int width = mWidth, height = mHeight;
  mat4x4 m, p, mvp;
  unsigned int size = 0;
  unsigned int indiceSize = 0;
  ModelData* vertices = obj->getModelData(size);
  unsigned short* indices = obj->getIndexData(indiceSize);
  //std::cout << size << std::endl;
  //std::cout << vertices[0].x << std::endl;
  Image* image1 = obj->getImage(0);
  Shader* shader = obj->getShader();
  GLuint program = shader->getGlShaderId();
  GLint mvp_location, texture_location;//vpos_location, vcol_location,vtex_location,
  GLenum glError;
  int vertex_buffer = obj->getVertexBuffer();
  int index_buffer = obj->getIndiceBuffer();
  unsigned int textureId = image1->getGlTexId();

  mvp_location = glGetUniformLocation(program, "MVP");
  texture_location = glGetUniformLocation(program, "tex");
  
      
  ratio = width / (float) height;

  glViewport(0, 0, width, height);
  glClear(GL_COLOR_BUFFER_BIT);
  getError("glClear");

  glEnableVertexAttribArray(1);
  getError("glEnableVertexAttribArray");
  //glBindBuffer(GL_ARRAY_BUFFER,vertex_buffer);
  getError("glBindBuffer");
  glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,
                        sizeof(vertices[0]),(void*)(sizeof(float) * 3));
  getError("glVertexAttribPointer");
  
  glEnableVertexAttribArray(0);
  //glBindBuffer(GL_ARRAY_BUFFER,vertex_buffer);
  glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE,
                        sizeof(vertices[0]), (void*) 0);
  getError("glVertexAttribPointer");

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,index_buffer);

  mat4x4_identity(m);
  //mat4x4_rotate_Z(m, m, (float) glfwGetTime());
  mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 2.f, -2.f);
  mat4x4_mul(mvp, p, m);

  glUseProgram(program);
  glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*) mvp);
  getError("glUniformMatrix4fv");

  

  glActiveTexture(GL_TEXTURE0);
  getError("glActiveTexture");
  
  glBindTexture(GL_TEXTURE_2D,textureId);
  getError("glBindTexture");

  glUniform1i(texture_location,0);
  getError("glUniform1i");

  //glDrawArrays(GL_TRIANGLES, 0, size);
  glDrawElements(GL_TRIANGLES, indiceSize,GL_UNSIGNED_SHORT,(void*)0);

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
}