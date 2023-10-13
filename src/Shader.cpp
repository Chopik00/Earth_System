#include "Shader.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

#define GLFW_INCLUDE_NONE
#include <glad/gl.h>
#include <GLFW/glfw3.h>

using namespace std;

namespace innards {
    Shader::Shader(const std::string& path)
        :Asset(path) 
    {
        isLoad = false;
    };


    GLuint Shader::loadShader(const GLenum _type, const char* const _src)
    {
        GLint compilationStatus;

        GLuint shaderId = glCreateShader(_type);
        if (!shaderId)
        {
            std::cout << "loadShaders: vertex generation failed\n";
            return false;
        }

        glShaderSource(shaderId, 1, &_src, nullptr);
        glCompileShader(shaderId);
        glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compilationStatus);

        if (!compilationStatus)
        {
            GLint infoLen;

            glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infoLen);
            if (infoLen)
            {
                char* const infoLog = static_cast<char*>(
                    malloc(sizeof(char) * infoLen)
                    );
                glGetShaderInfoLog(shaderId, infoLen, nullptr, infoLog);

                std::cout << "loadShader: " << infoLog << "\n";

                free(infoLog);

                glDeleteShader(shaderId);
                shaderId = 0;
            }
        }

        return shaderId;
    }


    void Shader::Load() {

        if (isLoad) {
            return;
        }

        Shader::isLoad = true;
        ifstream fin;
        stringstream ss;

        try
        {
            fin.open(path);


            while (!fin.eof()) {
                string ShaderData = "";
                getline(fin, ShaderData);
                ss << ShaderData<<"\n";
            }
            shaderText = ss.str();
            

            fin.close();
        }
        catch (const std::exception& e)
        {
            fin.close();
            cout << e.what();
        }

    };

   
    void Shader::Unload() {

        if (!isLoad) {
            return;
        }
        
        Shader::isLoad = false;
    }

    Shader::~Shader() = default;
};