#include "Texture.hpp"
#include <fstream>
#include <iostream>

//#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
using namespace std;

namespace innards {
    Texture::Texture(const std::string& path)
        :Asset(path)
    {

    };

    void Texture::Load() {
        
        try
        {
            textureData = stbi_load(
                path.c_str(),
                &mTextureWidth,
                &mTextureHeight,
                &mNumberOfTextureChannels,
                0
            );
        }
        catch (const std::exception& stlExc)
        {
            std::cerr << "loadTexture " << path << ": " << stlExc.what() << '\n';

            return;
        }

        if (!textureData)
        {
            std::cout << "\n";
            return;
        }
    }


    void Texture::Unload() {

        if (!isLoad) {
            return;
        }
        Texture::isLoad = false;
    }

    Texture::~Texture() = default;
};