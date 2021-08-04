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
#include "Tools.h"

class Simulatie {
public:
    Virus virus;
    World world;
    int it = 0;
    int counter = 1;

    Simulatie();
    Simulatie(Virus &vir, World &wereld);

    void infect(int x, int y);
    void simulate(int n);
    void breakout(Mens* m);
    void spread(Mens* m);
    void muteer();
};


#endif //VSS_SIMULATIE_H
