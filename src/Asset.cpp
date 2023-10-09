#include "Asset.hpp"

namespace innards {
    Asset::Asset(const std::string &path)
        :_path(path)
    {

    };

    Asset::~Asset() = default;
};