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
    int populatie;
    int bevolkingsdichtheid;
    double gezonheidsgraad;
    double agrens;
    double zgrens;
    double hgrens;
    //double sgrens; //overbodig

public:
    World(std::string path);

    void makeWorld(json &info);

    int getPopulatie();
    void setPopulatie(int pop);
    int getBevolkingsdichtheid();
    void setBevolkingsdichtheid(int bev);
    void setGezondheidsgraad(double gez);
    double getGezondeidsgraad();
    double getAgrens();
    void setAgrens(double ag);


};


#endif //VSS_WORLD_H
