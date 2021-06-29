//
// Created by frehml on 29/06/2021.
//

#include "World.h"

World::World(std::string path){
    json info;
    std::ifstream input(path);
    input >> info;
    makeWorld(info);
}

void World::makeWorld(json &info) {
    for (json::iterator it = info.begin(); it != info.end(); ++it){
        Correctness::correctWorld(it);
    }
}