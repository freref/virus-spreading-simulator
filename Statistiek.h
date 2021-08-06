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
    map<int, map<string, int>> stats;
    vector<string> names;

    Statistiek(){};
    Statistiek(std::string name){ names = {name};};

    string print();
};

#endif //VSS_STATISTIEK_H
