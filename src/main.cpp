#include <iostream>
//#include <sstring>
#include "Asset.hpp"
#include "Shader.hpp"
//#include "Texture.hpp"
//#include "Mesh.hpp"
#include <fstream>
#include <string>
#include <sstream>


#define GLFW_INCLUDE_NONE
#include <glad/gl.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

using namespace std;
using namespace innards;



constexpr const int RETURN_RESULT = 0;

const int OPEN_GL_VERSION_MAJOR = 3;
const int OPEN_GL_VERSION_MINOR = 2;
const int WINDOW_H = 600;
const int WINDOW_W = 800;



GLFWwindow *mWindow;
int mFrameBufferHeight = 0;
int mFrameBufferWidth = 0;

// X Y Z | R G B A | U V
const float mVertices[] = {
   0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,  // Up Right
   0.5f, -0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,  // Down Right
  -0.0f, -0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,  // Down Left
  -0.0f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f   // Up Left
};

const float mVertices2[] = {
   0.00f,  0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,  // Up Right
   0.0f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,  // Down Right
  -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,  // Down Left
  -0.5f,  0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f   // Up Left
};

const unsigned int mIndices[] = {
  0, 1, 3,   
  1, 2, 3    
};


constexpr const int NUMBER_OF_VERTICES = 4;
constexpr const int VERTEX_SIZE        = 9;
constexpr const int VERTEX_LENGTH      = sizeof(float) * VERTEX_SIZE;
constexpr const int MESH_LENGTH        = NUMBER_OF_VERTICES * VERTEX_LENGTH;
constexpr const int NUMBER_OF_INDICES  = 6;
constexpr const int INDICES_LENGTH     = NUMBER_OF_INDICES * sizeof(unsigned int);

constexpr const int VERTEX_STRIDE       = VERTEX_LENGTH;
constexpr const int VERTEX_POS_INDEX    = 0;
constexpr const int VERTEX_POS_SIZE     = 3;
constexpr const int VERTEX_POS_LENGTH   = VERTEX_POS_SIZE * sizeof(float);

constexpr const int VERTEX_COLOR_INDEX  = 1;
constexpr const int VERTEX_COLOR_SIZE   = 4;
constexpr const int VERTEX_COLOR_OFFSET = VERTEX_POS_LENGTH;
constexpr const int VERTEX_COLOR_LENGTH = VERTEX_COLOR_SIZE * sizeof(float);

constexpr const int VERTEX_TEX_INDEX    = 2;
constexpr const int VERTEX_TEX_SIZE     = 2;
constexpr const int VERTEX_TEX_OFFSET   = VERTEX_COLOR_OFFSET + VERTEX_COLOR_LENGTH;

GLuint mIndexBufferObject;
GLuint mVertexArrayObject;
GLuint mVertexBufferObject;

GLuint mProgramShaderID;
GLuint mFragmentShaderID;
GLuint mVertexShaderID;

//Earth

//GLuint meTextureID;
//int meNumberOfTextureChannels;
//int meTextureHeight;
//int meTextureWidth;

//Moon


GLuint mTextureID;
int mNumberOfTextureChannels;
int mTextureHeight;
int mTextureWidth;


static void handleGLFWErrors(int error, const char* description)
{
  std::cout << "error_callback: " << description << "\n";
}

static void handleKeyEvents(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  if (!mWindow)
  {
    return;
  }

  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
  {
    glfwSetWindowShouldClose(mWindow, GLFW_TRUE);
  }
}

void handleFramebufferSizeChange(GLFWwindow *pWindow, int width, int height)
{
  if (!mWindow)
  {
    return;
  }

  mFrameBufferWidth = width;
  mFrameBufferHeight = height;
  glViewport(0, 0, mFrameBufferWidth, mFrameBufferHeight);


}

bool loadMesh()
{
    glGenVertexArrays(1, &mVertexArrayObject);
    glBindVertexArray(mVertexArrayObject);

    glGenBuffers(1, &mVertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferObject);
    glBufferData(
        GL_ARRAY_BUFFER,
        MESH_LENGTH,
        mVertices2,
        GL_STATIC_DRAW
    );


    glVertexAttribPointer(
        VERTEX_POS_INDEX,
        VERTEX_POS_SIZE,
        GL_FLOAT,
        GL_FALSE,
        VERTEX_STRIDE,
        0
    );
    glEnableVertexAttribArray(VERTEX_POS_INDEX);
    glVertexAttribPointer(
        VERTEX_COLOR_INDEX,
        VERTEX_COLOR_SIZE,
        GL_FLOAT,
        GL_FALSE,
        VERTEX_STRIDE,
        (GLvoid*)(VERTEX_COLOR_OFFSET)
    );
    glEnableVertexAttribArray(VERTEX_COLOR_INDEX);
    glVertexAttribPointer(
        VERTEX_TEX_INDEX,
        VERTEX_TEX_SIZE,
        GL_FLOAT,
        GL_FALSE,
        VERTEX_STRIDE,
        (GLvoid*)(VERTEX_TEX_OFFSET)
    );
    glEnableVertexAttribArray(VERTEX_TEX_INDEX);

    glGenBuffers(1, &mIndexBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBufferObject);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        INDICES_LENGTH,
        mIndices,
        GL_STATIC_DRAW
    );

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

   



    return true;
}

bool loadTexture()
{
    stbi_set_flip_vertically_on_load(true);

;
    unsigned char* textureData;
    try
    {
        textureData = stbi_load(
            "Earth.jpg",
            &mTextureWidth,
            &mTextureHeight,
            &mNumberOfTextureChannels,
            0
        );
    }
    catch (const std::exception& stlExc)
    {
        std::cerr << "loadTexture: " << stlExc.what() << '\n';

        return false;
    }

    if (!textureData)
    {
        std::cout << "\n";
        return false;
    }

    glGenTextures(1, &mTextureID);
    if (!mTextureID)
    {
        std::cout << "loadTexture:  generation failed id\n";
        stbi_image_free(textureData);
        return false;
    }

    glBindTexture(GL_TEXTURE_2D, mTextureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGB,
        mTextureWidth,
        mTextureHeight,
        0,
        GL_RGB,
        GL_UNSIGNED_BYTE,
        textureData
    );
    glGenerateMipmap(GL_TEXTURE_2D);

    
    stbi_image_free(textureData);

    return true;
}


bool loadShaders()
{
    std::cout << "loadShaders: loading vertex shader\n";
    Shader vs("VertexShader.glsl");
    vs.path = "VertexShader.glsl";
    vs.Load();
    const char* const vertexShaderCode = vs.shaderText.c_str();
    mVertexShaderID = vs.loadShader(GL_VERTEX_SHADER, vertexShaderCode);
    if (!mVertexShaderID)
    {
        std::cout << "loadShaders: failed to load vertex shader\n";
        return false;
    }
    std::cout << "loadShaders: vertex shader loaded\n";


    std::cout << "loadShaders: loading fragment shader\n";
    Shader fs("FragmentShader.glsl");
    fs.path = "FragmentShader.glsl";
    fs.Load();
    const char* const fragmentShaderCode = fs.shaderText.c_str();
    mFragmentShaderID = fs.loadShader(GL_FRAGMENT_SHADER, fragmentShaderCode);
    if (!mFragmentShaderID)
    {
        std::cout << "loadShaders: fragment generation failed\n";
        return false;
    }
    std::cout << "loadShaders: fragment shader loaded\n";

    mProgramShaderID = glCreateProgram();
    if (!mProgramShaderID)
    {
        std::cout << "loadShaders: program generation failed\n";
        return false;
    }
    glAttachShader(mProgramShaderID, mVertexShaderID);
    glAttachShader(mProgramShaderID, mFragmentShaderID);
    glLinkProgram(mProgramShaderID);

    GLint linkResult;
    GLint linkLogLength;
    glGetProgramiv(mProgramShaderID, GL_LINK_STATUS, &linkResult);
    glGetProgramiv(mProgramShaderID, GL_INFO_LOG_LENGTH, &linkLogLength);
    if (linkLogLength > 0)
    {
        char* const linkMsg = static_cast<char*>(malloc(linkLogLength));

        glGetProgramInfoLog(
            mProgramShaderID,
            linkLogLength,
            nullptr,
            linkMsg
        );
        std::cout << "loadShaders: link failed with message: " << linkMsg << "\n";

        free(linkMsg);

        return false;
    }

    glDetachShader(mProgramShaderID, mVertexShaderID);
    glDetachShader(mProgramShaderID, mFragmentShaderID);

    glDeleteShader(mVertexShaderID);
    mVertexShaderID = 0;
    glDeleteShader(mFragmentShaderID);
    mFragmentShaderID = 0;

    return true;
}

bool onSurfaceReady()
{
  glfwGetFramebufferSize(mWindow, &mFrameBufferWidth, &mFrameBufferHeight);
  glViewport(0, 0, mFrameBufferWidth, mFrameBufferHeight);

  Shader vsh("VertexShader.glsl");

  

  glClearColor(0.1f, 0.5f, 0.5f, 1.0f);

  std::cout << "onSurfaceReady: loading shaders\n";
  if (!loadShaders())
  {
    std::cout << "onSurfaceReady: failed to laod shaders\n";
    return false;
  }
  std::cout << "onSurfaceReady: shaders loaded\n";

  std::cout << "onSurfaceReady: loading texture\n";
  if (!loadTexture())
  {
    std::cout << "onSurfaceReady: failed to load texture\n";
    return false;
  }
  std::cout << "onSurfaceReady: texture loaded\n";

  std::cout << "onSurfaceReady: loading mesh\n";
  if (!loadMesh())
  {
    return false;
  }
  std::cout << "onSurfaceReady: mesh loaded\n";

  return true;
}

bool init()
{
  if (!glfwInit())
  {
    std::cout << "init: failed to init\n";
    return false;
  }

  glfwSetErrorCallback(handleGLFWErrors);

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPEN_GL_VERSION_MAJOR);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPEN_GL_VERSION_MINOR);
  mWindow = glfwCreateWindow(WINDOW_W, WINDOW_H, "Earth System", nullptr, nullptr);
  if (!mWindow)
  {
    std::cout << "init: failed to create window\n";
    return false;
  }

  glfwSetKeyCallback(mWindow, handleKeyEvents);

  glfwMakeContextCurrent(mWindow);
  gladLoadGL(glfwGetProcAddress);

  glfwSetFramebufferSizeCallback(mWindow, handleFramebufferSizeChange);
  if (!onSurfaceReady())
  {
    std::cout << "init: failed to load assets\n";
    return false;
  }

  return true;
}

void render()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glUseProgram(mProgramShaderID);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, mTextureID);


  GLint texture0Loc = glGetUniformLocation(mProgramShaderID, "ourTexture");
  if (texture0Loc == -1) {
      std::cout << "failed to retriev texture #0 sampler2d\n";
      glfwSetWindowShouldClose(mWindow, true);
      return;
  }
  glUniform1i(texture0Loc, 0);

  glBindVertexArray(mVertexArrayObject);

  glDrawElements(
    GL_TRIANGLES,
    NUMBER_OF_INDICES,
    GL_UNSIGNED_INT,
    (void*)0
  );

  glDrawElements(
      GL_TRIANGLES,
      NUMBER_OF_INDICES,
      GL_UNSIGNED_INT,
      (void*)0
  );
  


  glBindVertexArray(0);
  glBindTexture(GL_TEXTURE_2D, 0);
  glDisable(GL_BLEND);
  glUseProgram(0);



  
}

void mainLoop()
{
  while (!glfwWindowShouldClose(mWindow))
  {
    render();

    glfwSwapBuffers(mWindow);
    glfwPollEvents();
  }
}

void terminate()
{
  if (mWindow)
  {
    if (mVertexShaderID)
    {
      glDeleteShader(mVertexShaderID);
    }
    mVertexShaderID = 0;

    if (mFragmentShaderID)
    {
      glDeleteShader(mFragmentShaderID);
    }
    mFragmentShaderID = 0;

    if (mProgramShaderID)
    {
      glDeleteProgram(mProgramShaderID);
    }
    mProgramShaderID = 0;

    if (mVertexBufferObject)
    {
      glDeleteBuffers(1, &mVertexBufferObject);
    }
    mVertexBufferObject = 0;

    if (mIndexBufferObject)
    {
      glDeleteBuffers(1, &mIndexBufferObject);
    }
    mIndexBufferObject = 0;

    if (mVertexArrayObject)
    {
      glDeleteVertexArrays(1, &mVertexArrayObject);
    }
    mVertexArrayObject = 0;

    if (mTextureID)
    {
      glDeleteTextures(1, &mTextureID);
    }
    mTextureID = 0;

    glfwDestroyWindow(mWindow);
  }

  glfwTerminate();
}

int main()
{
  if (init())
  {
    mainLoop();
  }

  terminate();

  return RETURN_RESULT;
}

