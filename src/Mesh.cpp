#include "Mesh.hpp"
#include <fstream>
#include <iostream>
#include <math.h>
#include <stdlib.h>
using namespace std;

namespace innards {
    Mesh::Mesh(const std::string& path)
        :Asset(path)
    {

    };
    
   


    Mesh::~Mesh() = default;
};