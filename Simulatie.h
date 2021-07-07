//
// Created by twijg on 7/6/21.
//

#ifndef VSS_SIMULATIE_H
#define VSS_SIMULATIE_H

#include "Virus.h"
#include "World.h"
#include "Mens.h"
#include <vector>
#include <array>

class Simulatie {
public:

    Simulatie();

    Simulatie(Virus &vir, World &wereld, bool mut);

    Virus virus;
    World world;
    bool mutate;
    unsigned int dag = 0;
    std::vector<std::vector<Mens>> worldgrid;
    void buildGrid();
    void step();
};


#endif //VSS_SIMULATIE_H
