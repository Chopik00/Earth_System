#pragma once 
using namespace std;

//#include "eShaderType.hpp"
#include "Asset.hpp"
#include <string>

namespace innards {
    class Mesh final : public Asset {
    public:
        ~Mesh() override;
        explicit Mesh(const std::string& path);

        GLuint mIndexBufferObject;
        GLuint mVertexArrayObject;
        GLuint mVertexBufferObject;
  
    };


}