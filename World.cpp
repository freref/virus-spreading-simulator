//
// Created by frehml on 29/06/2021.
//

#include "World.h"

World::World(std::string path){
    std::ifstream input(path);
    input >> info;
}

void World::correctness() {
    for (json::iterator it = info.begin(); it != info.end(); ++it){
        Correctness::correctWorld(it);
    }
}