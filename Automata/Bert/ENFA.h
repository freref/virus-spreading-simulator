#ifndef CLION_ENFA_H
#define CLION_ENFA_H


#include <string>
#include <utility>
#include <vector>
#include <iomanip>
#include <fstream>
#include <iostream>
#include "../../json.hpp"
#include <string>
#include "state.h"

using strvec = std::vector<std::string>;


class ENFA{
public:
    std::string type;
    strvec alfabet;
    std::vector<State> states;
    State startstaat;
    std::string eps;

    bool accepts(std::string input);
    void print();
    ENFA lees(std::string file);
    ENFA toDFA();
    void toDFArec(ENFA* dfa, ENFA nfa, std::vector<State> staat);

    strvec volgende(State staat, std::string input);

    ENFA();

    ENFA(const std::string file) {
        ENFA temp = lees(file);
        type = temp.type;
        alfabet = temp.alfabet;
        states = temp.states;
        startstaat = temp.startstaat;
        eps = temp.eps;
    }

    std::vector<State> epsTransRes(State start);
};



#endif //CLION_ENFA_H
