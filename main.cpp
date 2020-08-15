#include <iostream>

#include <boost/asio.hpp>
//#include <boost/thread/thread.hpp>
#include <thread>
#include <cstdint>


#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <array>
#include "linmath.h"
#include <ft2build.h>
#include FT_FREETYPE_H

using boost::asio::ip::udp;
/*
class TestThread{
    public:
        TestThread(){
            std::cout << "Hello, Thread!\n";
        }
};
*/

/*
struct callable
{
    void operator()();
};
*/

static const struct
{
    float x, y;
    float r, g, b;
    float w, u;
} vertices[6] =
{
    { -1.0f, -1.0f,  1.f, 0.0f, 0.f,  0.f,1.f },
    {  1.0f, -1.0f,  0.f, 0.5f, 0.f,  1.f,1.f },
    { -1.0f,  1.0f,  0.f, 0.0f, 1.f,  0.f,0.f },

    {  1.0f, -1.0f,  0.5f,0.5f,0.5f,  1.f,1.f},
    {  1.0f,  1.0f,  0.5f,0.5f,0.5f,  1.f,0.f},
    { -1.0f,  1.0f,  0.5f,0.5f,0.5f,  0.f,0.f}
    
};


static const char* modern_vertex_shader_text =
"#version 330 core\n"
"uniform mat4 MVP;\n"
"layout(location = 0) in vec3 vCol;\n"
"layout(location = 1) in vec2 vPos;\n"
"layout(location = 2) in vec2 vTex;\n"
"out vec3 color;\n"
"out vec2 texPos;\n"
"void main()\n"
"{\n"
"    gl_Position = MVP * vec4(vPos, 0.0, 1.0);\n"
"    //gl_Position = MVP * vec4(vTex, 0.0, 1.0);\n"
"    color = vCol;\n"
"    texPos = vTex;\n"
"}\n";

static const char* modern_fragment_shader_text =
"#version 330 core\n"
"in vec3 color;\n"
"in vec2 texPos;\n"
"uniform sampler2D tex;\n"
"out vec4 out_color;"
"void main()\n"
"{\n"
"    //out_color = vec4(color, 1.0);\n"
"    out_color = texture(tex,texPos);\n"
"}\n";

static const char* vertex_shader_text =
"#version 110\n"
"uniform mat4 MVP;\n"
"attribute vec3 vCol;\n"
"attribute vec2 vPos;\n"
"attribute vec2 vTex;\n"
"varying vec3 color;\n"
"varying vec2 texPos;\n"
"void main()\n"
"{\n"
"    gl_Position = MVP * vec4(vPos, 0.0, 1.0);\n"
"    color = vCol;\n"
"    texPos = vTex;\n"
"}\n";
 
static const char* fragment_shader_text =
"#version 110\n"
"varying vec3 color;\n"
"varying vec2 texPos;\n"
"uniform sampler2D texture;\n"
"void main()\n"
"{\n"
"    //gl_FragColor = vec4(color, 1.0);\n"
"    gl_FragColor = texture2D(texture,texPos);\n"
"}\n";

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

struct PacketHeader
{
    uint16_t    m_packetFormat;             // 2020
    uint8_t     m_gameMajorVersion;         // Game major version - "X.00"
    uint8_t     m_gameMinorVersion;         // Game minor version - "1.XX"
    uint8_t     m_packetVersion;            // Version of this packet type, all start from 1
    uint8_t     m_packetId;                 // Identifier for the packet type, see below
    uint64_t    m_sessionUID;               // Unique identifier for the session
    float     m_sessionTime;              // Session timestamp
    uint32_t    m_frameIdentifier;          // Identifier for the frame the data was retrieved on
    uint8_t     m_playerCarIndex;           // Index of player's car in the array
    
   // ADDED IN BETA 2: 
    uint8_t     m_secondaryPlayerCarIndex;  // Index of secondary player's car in the array (splitscreen)
                                          // 255 if no second player
};

void wait(int seconds)
{
  //boost::this_thread::sleep_for(boost::chrono::seconds{seconds});

}
bool run = true;
void threadFunction()
{
  while(run)
  {
    //wait(1);
    //std::cout << i << '\n';
    boost::asio::io_context io_context;
    udp::socket s(io_context,udp::endpoint(udp::v4(),20777));
    char reply[1500];
    //s.receive(boost::asio::buffer(reply,1500));
    udp::endpoint sender_endpoint;
    s.receive_from(boost::asio::buffer(reply,1500),sender_endpoint);
    //short year = ((short)reply[0] >> 8) | reply[1];
    //std::cout << year << '\n';
    PacketHeader* header = (PacketHeader*)reply;
    std::cout << header->m_packetFormat << '\n';
  }
}

std::array<float,8> getCube(){
  std::array<float,8> ret;
}

int main(int, char**) {
  /*
    std::cout << "Hello, world!123\n";
    //TestThread th = TestThread();
    //callable th;
    //boost::thread t(threadFunction);
    //t.join();
    //getchar();
    std::thread th(threadFunction);
    getchar();
    run = false;
    th.join();
    */

  std::cout << "Hallo Welt";

  //---------------------
  GLFWwindow* window;
  GLuint vertex_buffer, vertex_shader, fragment_shader, program;
  GLint mvp_location, vpos_location, vcol_location,vtex_location,texture_location;
  GLenum glError;
  glfwSetErrorCallback(error_callback);
  if (!glfwInit()){
    std::cout << "glfwInit failed"; 
    exit(EXIT_FAILURE);
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);

  window = glfwCreateWindow(640, 480, "My Title",  NULL, NULL);
  if (!window)
  {
    glfwTerminate();
    // Window or context creation failed
    std::cout << "window creation failed"<<'\n';
    return 1;
  }
  glfwSetKeyCallback(window, key_callback);
  glfwMakeContextCurrent(window);

    //---------------------- GLEW Commands
    std::cout << "GLEW Init" << std::endl;
  glewExperimental = GL_TRUE;
  GLenum err = glewInit();
  if (GLEW_OK != err)
  {
    std::cout << glewGetErrorString(err);
    return 1;
    fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    
  }
  
  //------------------Free Type 2 Commands
  const int imageWidth = 1024;//640;
  const int imageHeight = 480; 
  std::array<unsigned char, imageWidth*imageHeight> image;
  std::array<unsigned char, imageWidth*imageHeight*3> image2;
  std::cout << "Init Pic" << std::endl;
  for(int i=0;i<imageWidth*imageHeight;i++){
    image[i] = 250;
    image2[i*3] = 250;
    image2[i*3+1] = 250;
    image2[i*3+2] = 250;
  }
  /*
  std::cout << "Free Type2 Init" << std::endl;
  FT_Library library;
  FT_Face face;
  FT_GlyphSlot slot;
  FT_Matrix matrix;
  FT_Vector pen;
  int target_height = imageHeight;
  double angle;
  FT_Error error = FT_Init_FreeType(&library);
  if(error){
    std::cout << "Fehler in Free Type2";
    return 1;
  }
  error = FT_New_Face(library,"Dosis-Medium.ttf",0,&face);
  if ( error == FT_Err_Unknown_File_Format )
  {
    std::cout << "Font Format is unsupported";
    return 1;
  }
  else if ( error )
  {
    std::cout << "Font could not be Opened";
    return 1;
  }
  error = FT_Set_Char_Size(face,50 * 64,0,100,0);
  if(error){
    std::cout << "Could not set Char Size";
  }
  slot = face->glyph;
  angle = (25.0 /360)*3.14159 *2; // Use 25 degrees
  matrix.xx = (FT_Fixed) (cos(angle)*0x10000L);
  matrix.xy = (FT_Fixed)(-sin(angle)*0x10000L);
  matrix.yx = (FT_Fixed)(sin(angle)*0x10000L);
  matrix.yy = (FT_Fixed)(cos(angle)*0x10000L);

  pen.x = 300*64;
  pen.y = (target_height - 200)* 64;

  char test[] = "Hallo Welt";
  
  //unsigned char image[imageWidth*imageHeight];
  //unsigned char image2[imageWidth*imageHeight*3];
  
  std::cout << "Insert Char" << std::endl;
  for(int i=0;i<sizeof(test);i++){
    FT_Set_Transform(face,&matrix,&pen);

    //std::cout << test[i] << std::endl;

    error = FT_Load_Char(face, test[i],FT_LOAD_RENDER);
    if(error){
      continue;
    }
    //drawBitmap
    FT_Int x = slot->bitmap_left;
    FT_Int y = imageHeight - slot->bitmap_top;
    FT_Bitmap* bitmap = &slot->bitmap;
    FT_Int xMax = x + bitmap->width;
    FT_Int yMax = y + bitmap->rows;
    /*
    std::cout << x << std::endl;
    std::cout << y << std::endl;
    std::cout << xMax << std::endl;
    std::cout << yMax << std::endl;
    */
   /*
    FT_Int k,j,p,q;
    for(k=x,p=0;k<xMax;k++,p++){
      for(j=y,q=0;j<yMax;j++,q++){
        if(i<0 || j<0 || i >= 640 ||j>= 480) continue;
        int index = j*640+k;
        int index2 = q* bitmap->width +p;
        image[index] = bitmap->buffer[index2];
      }
    }
    */
    
/*
    pen.x += slot->advance.x;
    pen.y += slot->advance.y;
  }
  */
  //-------------- Open GL Commands
  std::cout << "OpenGL init" << std::endl;
  glClearColor(0,1,0,1);

  //glEnable(GL_DEPTH_TEST);
  //glDepthFunc(GL_LESS);

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
  glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,imageWidth,imageHeight,0,GL_RGB,GL_UNSIGNED_BYTE,image2.data());
  glError = glGetError();
  if(glError = GL_INVALID_ENUM){
    std::cout << "glTexImage2D has invalid Enum"<< std::endl;
  }

std::cout << "Compile Shaders" << std::endl;
  //compile and Links programs
  vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  //glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
  glShaderSource(vertex_shader, 1, &modern_vertex_shader_text, NULL);
  glCompileShader(vertex_shader);
  char shaderLog[1000];
  int sizeLog;
  glGetShaderInfoLog(vertex_shader,1000,&sizeLog,shaderLog);
  std::cout << shaderLog << std::endl;

  fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  //glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
  glShaderSource(fragment_shader, 1, &modern_fragment_shader_text, NULL);
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

  mvp_location = glGetUniformLocation(program, "MVP");
  /*
  vpos_location = glGetAttribLocation(program, "vPos");
  vcol_location = glGetAttribLocation(program, "vCol");
  vtex_location = glGetAttribLocation(program, "texPos");
  */
  texture_location = glGetUniformLocation(program, "tex");

  /*
  glEnableVertexAttribArray(vpos_location);
  glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE,
                        sizeof(vertices[0]), (void*) 0);
  glEnableVertexAttribArray(vcol_location);
  glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE,
                        sizeof(vertices[0]), (void*) (sizeof(float) * 2));

  glVertexAttribPointer(vtex_location,2,GL_FLOAT,GL_FALSE,
                        sizeof(vertices[0]),(void*)(sizeof(float) * 5));
  */
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1,2,GL_FLOAT, GL_FALSE,
                        sizeof(vertices[0]), (void*) 0);
  glError = glGetError();
  if(glError = GL_INVALID_ENUM){
    std::cout << "glVertexAttribPointer No1 has invalid Enum"<< std::endl;
  }
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                        sizeof(vertices[0]), (void*) (sizeof(float) * 2));
  glError = glGetError();
  if(glError = GL_INVALID_ENUM){
    std::cout << "glVertexAttribPointer No2 has invalid Enum"<< std::endl;
  }
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,
                        sizeof(vertices[0]),(void*)(sizeof(float) * 5));
  glError = glGetError();
  if(glError = GL_INVALID_ENUM){
    std::cout << "glVertexAttribPointer No3 has invalid Enum"<< std::endl;
  }


  std::cout << "Start Render Loop" << std::endl;

  while (!glfwWindowShouldClose(window))
  {
    
      float ratio;
      int width, height;
      mat4x4 m, p, mvp;

      glfwGetFramebufferSize(window, &width, &height);
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

      glDrawArrays(GL_TRIANGLES, 0, 6);

      glfwSwapBuffers(window);
      glfwPollEvents();
  }
  //FT_Done_Face    ( face );
  //FT_Done_FreeType( library );

  glfwDestroyWindow(window);

  glfwTerminate();
  exit(EXIT_SUCCESS);
  //return 0;
}
