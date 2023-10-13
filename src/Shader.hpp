#pragma once 
using namespace std;

#include "eShaderType.hpp"
#include "Asset.hpp"
#include <string>

namespace innards {
    class Shader final : public Asset {
    private:
        
    public:
        ~Shader () override; 
        explicit Shader (const std::string &path);


        void Load() override;
        void Unload() override;
        GLuint loadShader(const GLenum _type, const char* const _src);

        string shaderText;
        bool isLoad;
        string path;

    };


}