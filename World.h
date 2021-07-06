//
// Created by frehml on 29/06/2021.
//

#ifndef VSS_WORLD_H
#define VSS_WORLD_H

#include "json.hpp"
#include "Correctness.h"
#include <fstream>
#include <ostream>

using json = nlohmann::json;

class World {
public:
    json info;

    World(std::string path);

    void correctness();
};


#endif //VSS_WORLD_H
