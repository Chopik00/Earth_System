#pragma once 
#include <string>
namespace innards{
    class Asset {
    public:
        virtual ~Asset();
        const std::string _path;
    protected:
        explicit Asset(const std::string &path);

    };


}
