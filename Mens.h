//
// Created by twijg on 7/6/21.
//

#ifndef VSS_MENS_H
#define VSS_MENS_H

#include <string>
#include <iostream>
#include <cmath>
#include "Tools.h"
#include "Virus.h"
#include "fstream"

struct Neighbours {
    pair<int, int> up;
    pair<int, int> down;
    pair<int, int> left;
    pair<int, int> right;
};

class Mens {
public:
    string name;
    int age;
    //gezond, asymptotisch, ziek, hospitaal, incuberend, dood
    std::string toestand = "G"; //G, A, Z, H, I, X
    int it;
    int infectie = 0;

    double gezondheidsgraad;

    int rightDistance;
    int downDistance;

    int leftDistance;
    int upDistance;

    int recovery = 0;
    int incubatie = 0;

    Neighbours n;

    Mens(){};
    Mens(double gg, double down, double right);

    static Mens* generateHuman(double gg, double d);
    void calculateValues(Virus &v);
    void print();
};

#endif //VSS_MENS_H
