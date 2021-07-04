#ifndef CLION_NFA_H
#define CLION_NFA_H


#include <string>
#include <utility>
#include <vector>
#include <iomanip>
#include <fstream>
#include <iostream>
#include "json.hpp"
#include <string>
#include "state.h"


class NFA{
public:
    std::string type;
    strvec alfabet;
    std::vector<State> states;
    State startstaat;

    bool accepts(std::string input);
    void print();
    NFA lees(std::string file);
    NFA toDFA();
    void toDFArec(NFA* dfa, NFA nfa, std::vector<State> staat);



    NFA();
    NFA(const std::string file) {
        NFA temp = lees(file);
        type = temp.type;
        alfabet = temp.alfabet;
        states = temp.states;
        startstaat = temp.startstaat;
    }
};
#endif