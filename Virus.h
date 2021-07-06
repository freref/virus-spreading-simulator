//
// Created by frehml on 29/06/2021.
//

#ifndef VSS_VIRUS_H
#define VSS_VIRUS_H

#include <fstream>
#include <ostream>
#include "Automata/Working/RE.h"
#include "json.hpp"
#include "Automata/Working/NFA.h"
#include "Correctness.h"

using json = nlohmann::json;

class Virus {
public:
    json info;

    Virus(std::string path);
    void correctness();
    void makeVirus();
    void makeProperties();
    void makeProperty(json::iterator it);
    void integerNFA(json::iterator &it, std::string &name);
    void percentageNFA(json::iterator &it, std::string &name);
    void rangeNFA(json::iterator &it, std::string &name);
};


#endif //VSS_VIRUS_H
