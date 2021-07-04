#ifndef PROJECTTA_STATE_H
#define PROJECTTA_STATE_H

#include <string>
#include <vector>
#include <algorithm>
#include <array>
#include <iostream>

using strvec = std::vector<std::string>;




class State{
public:
    std::string naam;
    std::vector<strvec> transities;   // [["0", "Q1", "Q3"], ["1", "Q2"]...]
    strvec next(char input);
    bool accepting;
    bool starting;
};

std::vector<State> namesToStates(strvec names, std::vector<State>statelist);

std::vector<State> leidtTot(State staat, std::vector<State> statelist, std::string input);

#endif
