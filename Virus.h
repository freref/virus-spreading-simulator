//
// Created by frehml on 29/06/2021.
//

#ifndef VSS_VIRUS_H
#define VSS_VIRUS_H

#include <fstream>
#include <ostream>
#include <iomanip>
#include <string>
#include "json.hpp"
#include "Automata/Working/DFA.h"
#include "Automata/Working/NFA.h"
#include "Correctness.h"
#include <iomanip>

using json = nlohmann::json;

class Virus {
public:
    json info;
    std::map<std::string, NFA> properties;
    NFA virus;

    std::string giveName();
    Virus();
    Virus(std::string path);
    void makeProperties(json &info);
    DFA makeProperty(json::iterator::value_type chance);
    DFA makeDFA(int a, int b);
    void correctness();
    void makeVirus();
    void makeProperties();
    void makeProperty(json::iterator it);
    void rangeNFA(json::iterator &it, std::string &name, std::string &title);
    void integerNFA(json::iterator &it, std::string &name, std::string &title);
    void percentageNFA(json::iterator &it, std::string &name, std::string &title);

};


#endif //VSS_VIRUS_H
