//
// Created by twijg on 7/6/21.
//

#ifndef VSS_MENS_H
#define VSS_MENS_H

#include <string>
#include <chrono>
#include <random>
#include <iostream>
#include <cmath>
#include "Tools.h"

class Mens {
public:
    std::string toestand = "G"; //G, Z, H, X
    double gezondheidsgraad;
    int rightDistance;
    int downDistance;

    Mens(){};
    Mens(double gg, double down, double right);

    static Mens* generateHuman(double gg, double d);
};

#endif //VSS_MENS_H
