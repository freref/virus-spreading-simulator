//
// Created by frehml on 29/06/2021.
//

#ifndef VSS_CORRECTNESS_H
#define VSS_CORRECTNESS_H

#include "json.hpp"
#include "Automata.h"

using json = nlohmann::json;

class Correctness {
public:
    static void correctVirus(json::iterator const &it);
    static void correctValue(json::iterator const &it);
    static void correctWorld(json::iterator const &it);
    static void percentageCheck(json::iterator::value_type const &i);
    static void questionCheck(json::iterator::value_type const &i);
    static void rangeCheck(json::iterator::value_type const &i);
    static void integerCheck(json::iterator::value_type const &i);
};


#endif //VSS_CORRECTNESS_H
