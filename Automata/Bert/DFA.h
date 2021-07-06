#ifndef CLION_DFA_H
#define CLION_DFA_H

#include <string>
#include <utility>
#include <vector>
#include <iomanip>
#include <fstream>
#include <iostream>
#include "../../json.hpp"
#include <string>
#include "state.h"


class DFA{
public:
    DFA(DFA dfa1, DFA dfa2, bool doorsnede); //product

    std::string type;
    std::vector<std::string> alfabet;
    std::vector<State> states;
    State startstaat;

    bool accepts(std::string input);
    void print();

    DFA();

    DFA(const std::string file) {
        DFA temp = lees(file);
        type = temp.type;
        alfabet = temp.alfabet;
        states = temp.states;
        startstaat = temp.startstaat;
    }

    DFA lees(std::string file);

    void maal(State s1, State s2, bool doorsnede, std::vector<State> df1, std::vector<State> df2);
};

#endif