//
// Created by twijg on 7/5/21.
//

#ifndef VSS_STATISTIEK_H
#define VSS_STATISTIEK_H

#include <vector>
#include <iostream>
#include <fstream>
#include "World.h"

class Statistiek {
public:
    string log;

    Statistiek(){};

    void add(std::string line);
    void update(World w);
    void print();
};

#endif //VSS_STATISTIEK_H
