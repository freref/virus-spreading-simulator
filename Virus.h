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
#include "Automata/Frederic/DFA.h"
#include "Automata/Frederic/ENFA.h"
#include "Correctness.h"
#include <iomanip>
#include "Tools.h"

using json = nlohmann::json;

class Virus {
public:
    json info;
    std::map<std::string, ENFA> properties;
    string name;
    ENFA virus_enfa;
    DFA virus_dfa;

    Virus(){};
    Virus(std::string path);

    string calculateName();
    void makeProperties(json &info);
    DFA makeProperty(json::iterator::value_type chance);
    DFA makeDFA(int a, int b);
    void correctness();
    void makeVirus(int counter);
    void makeProperties();
    void makeProperty(json::iterator it);
    void rangeNFA(json::iterator &it, std::string &name, std::string &title);
    void booleanNFA(json::iterator &it, std::string &name, std::string &title);
    void percentageNFA(json::iterator &it, std::string &name, std::string &title);
    void reload(json j);
};


#endif //VSS_VIRUS_H
