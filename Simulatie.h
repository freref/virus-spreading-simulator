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
    Virus virus;
    World world;

    Simulatie();
    Simulatie(Virus &vir, World &wereld);
};


#endif //VSS_SIMULATIE_H
