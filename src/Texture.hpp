#pragma once 
using namespace std;

//#include "eShaderType.hpp"
#include "Asset.hpp"
#include <string>

namespace innards {
    class Texture final : public Asset {
    private:

    public:
        GLuint mTextureID;
        int mNumberOfTextureChannels;
        int mTextureHeight, mTextureWidth;
        bool isLoad;
        string path;
        unsigned char m_LocalBuffer;
        

    
        ~Texture() override;
        explicit Texture(const std::string& path);
        //bool loadTexture;// override;
        void Load() override;
        void Unload() override;
        unsigned char* textureData;



    };


}