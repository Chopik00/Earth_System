#pragma once 

#include "eShaderType.hpp"
#include "Asset.hpp"

namespace innards {
    class Shader final : public Asset {
    public:
        ~Shader () override; 
        explicit Shader (const std::string &path);

    };


}