//
// Created by frehml on 29/06/2021.
//

#ifndef VSS_VIRUS_H
#define VSS_VIRUS_H

#include <fstream>
#include <ostream>
#include "json.hpp"
#include "Automata/Working/DFA.h"
#include "Correctness.h"

using json = nlohmann::json;

class Virus {
public:
    //DFA virus;
    std::map<std::string, DFA> properties;

    Virus(std::string path);
    void makeProperties(json &info);
    DFA makeProperty(json::iterator::value_type chance);
    DFA makeDFA(int a, int b);
};


#endif //VSS_VIRUS_H
