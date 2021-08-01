//
// Created by twijg on 7/6/21.
//

#include "Mens.h"

Mens::Mens(double gg, double down, double right) {
    gezondheidsgraad = gg;
    downDistance =  down;
    rightDistance =  right;
}

Mens* Mens::generateHuman(double gg, double d) {
    std::normal_distribution<double> gezondheid (gg,1.0);
    std::normal_distribution<double> up (d,d);
    std::normal_distribution<double> right (d,d);

    Mens* m = new Mens(fabs(gezondheid(generator)), fabs(up(generator)), fabs(right(generator)));
    return m;
}