//
// Created by frehml on 29/06/2021.
//

#ifndef VSS_WORLD_H
#define VSS_WORLD_H

#include "json.hpp"
#include "Mens.h"
#include "Correctness.h"
#include <fstream>
#include <ostream>


using json = nlohmann::json;

class World {
public:
    int populatie;
    int bevolkingsdichtheid;
    double gezondheidsgraad;
    double agrens;
    double zgrens;
    double hgrens;

    json info;
    vector<vector<Mens*>> grid;

    World(){};
    World(std::string path);
    ~World();

    void correctness();
    void makeWorld();
    void populateProperties();
    void populateGrid();
    void print();
};


#endif //VSS_WORLD_H
