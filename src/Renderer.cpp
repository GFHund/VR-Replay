#include "Renderer.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "linmath.h"

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
}

void Renderer::init3DObject(Abstract3dObject* obj){
  GLuint vertex_buffer, vertex_shader, fragment_shader, program;
  
  GLenum glError;
  unsigned int size = 0;
  ModelData* vertices = obj->getModelData(size);
  Image* image1 = obj->getImage(0);
  Shader* shader = obj->getShader();
  glGenBuffers(1, &vertex_buffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
  glError = glGetError();
  if(glError == GL_INVALID_VALUE){
    std::cout << "glBindBuffer Invalid value" << std::endl;
  }
  else if(glError == GL_INVALID_ENUM){
    std::cout << "glBindBuffer has invalid Enum"<< std::endl;
  }
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glError = glGetError();
  if(glError == GL_INVALID_VALUE){
    std::cout << "glBufferData Invalid value" << std::endl;
  }
  else if(glError == GL_INVALID_ENUM){
    std::cout << "glBufferData has invalid Enum"<< std::endl;
  }

  unsigned int textureId = 0;
  glGenTextures(1, &textureId);
  glError = glGetError();
  if(glError == GL_INVALID_VALUE){
    std::cout << "glGenTextures Invalid value" << std::endl;
  }else if(glError == GL_INVALID_ENUM){
    std::cout << "glBufferData has invalid Enum"<< std::endl;
  }
  glBindTexture(GL_TEXTURE_2D, textureId);
  glError = glGetError();
  if(glError = GL_INVALID_ENUM){
    std::cout << "glBindTexture has invalid Enum"<< std::endl;
  }
  //glTexImage2D(GL_TEXTURE_2D,0,GL_RED,640,480,0,GL_RED,GL_UNSIGNED_BYTE,image);
  GLint imageWidth = image1->getWidth();
  GLint imageHeight = image1->getHeight();
  unsigned char* image1Data = image1->getPixels();
  glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,imageWidth,imageHeight,0,GL_RGB,GL_UNSIGNED_BYTE,image1Data);
  glError = glGetError();
  if(glError = GL_INVALID_ENUM){
    std::cout << "glTexImage2D has invalid Enum"<< std::endl;
  }
  image1->setGlTexId(textureId);

std::cout << "Compile Shaders" << std::endl;
  //compile and Links programs
  vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  //glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
  const char* vertexProgram = shader->getVertexProgram();
  glShaderSource(vertex_shader, 1, &vertexProgram, NULL);
  glCompileShader(vertex_shader);
  char shaderLog[1000];
  int sizeLog;
  glGetShaderInfoLog(vertex_shader,1000,&sizeLog,shaderLog);
  std::cout << shaderLog << std::endl;

  fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  //glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
  const char* fragmentProgram = shader->getFragmentProgram();
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

  shader->setGlShaderId(program);



  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0,2,GL_FLOAT, GL_FALSE,
                        sizeof(vertices[0]), (void*) 0);
  glError = glGetError();
  if(glError = GL_INVALID_ENUM){
    std::cout << "glVertexAttribPointer No1 has invalid Enum"<< std::endl;
  }
  /*
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                        sizeof(vertices[0]), (void*) (sizeof(float) * 2));
  glError = glGetError();
  if(glError = GL_INVALID_ENUM){
    std::cout << "glVertexAttribPointer No2 has invalid Enum"<< std::endl;
  }
  */
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,
                        sizeof(vertices[0]),(void*)(sizeof(float) * 3));
  glError = glGetError();
  if(glError = GL_INVALID_ENUM){
    std::cout << "glVertexAttribPointer No3 has invalid Enum"<< std::endl;
  }
}

void Renderer::render(){

}

void Renderer::render3DObject(Abstract3dObject* obj){
  float ratio;
  int width = mWidth, height = mHeight;
  mat4x4 m, p, mvp;
  unsigned int size = 0;
  ModelData* vertices = obj->getModelData(size);
  Image* image1 = obj->getImage(0);
  Shader* shader = obj->getShader();
  GLuint program = shader->getGlShaderId();
  GLint mvp_location, texture_location;//vpos_location, vcol_location,vtex_location,
  GLenum glError;
  unsigned int textureId = image1->getGlTexId();

  mvp_location = glGetUniformLocation(program, "MVP");
  texture_location = glGetUniformLocation(program, "tex");
      
  ratio = width / (float) height;

  glViewport(0, 0, width, height);
  glClear(GL_COLOR_BUFFER_BIT);
  GLenum error = glGetError();
  if(error = GL_INVALID_ENUM){
    //std::cout << "glClear has invalid Enum"<< std::endl;
  }

  mat4x4_identity(m);
  //mat4x4_rotate_Z(m, m, (float) glfwGetTime());
  mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
  mat4x4_mul(mvp, p, m);

  glUseProgram(program);
  glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*) mvp);
  glError = glGetError();
  if(glError = GL_INVALID_ENUM){
    //std::cout << "glUniformMatrix4fv has invalid Enum"<< std::endl;
  }

  glActiveTexture(GL_TEXTURE0);
  glError = glGetError();
  if(glError = GL_INVALID_ENUM){
    //std::cout << "GL_TEXTURE0 is not right"<< std::endl;
  }
  glBindTexture(GL_TEXTURE_2D,textureId);
  glError = glGetError();
  if(glError = GL_INVALID_ENUM){
    //std::cout << "Target is not one of the allowable values"<< std::endl;
  }
  else if(glError == GL_INVALID_VALUE){
    std::cout << "GL_INVALID_VALUE: texture is not a name returned from a previous call to glGenTextures"<<std::endl;
  }
  else if(glError = GL_INVALID_OPERATION){
    std::cout << "GL_INVALID_Operation: texutre was previously created with a target that doesn't match that of target"<<std::endl;
  }
  glUniform1i(texture_location,0);
  glError = glGetError();
  if(glError == GL_INVALID_OPERATION){
    std::cout << "GL_INVALID_Operation" << std::endl;
  }

  glDrawArrays(GL_TRIANGLES, 0, size);
}