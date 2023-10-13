#pragma once 
#include <string>

#define GLFW_INCLUDE_NONE
#include <glad/gl.h>
#include <GLFW/glfw3.h>


namespace innards{
    class Asset {
    public:
        virtual ~Asset();
        const std::string _path;
        virtual void Load() = 0;
        virtual void Unload() = 0;
    protected:
        explicit Asset(const std::string &path);

    };


}
