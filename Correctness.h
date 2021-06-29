//
// Created by frehml on 29/06/2021.
//

#ifndef VSS_CORRECTNESS_H
#define VSS_CORRECTNESS_H

#include "json.hpp"
#include "Automata/Working/RE.h"

using json = nlohmann::json;

static std::string alphabet = "(a+b+c+d+e+f+g+h+i+j+k+l+m+n+o+p+q+r+s+t+u+v+w+x+y+z)";
static std::string numbers = "(1+2+3+4+5+6+7+8+9+0)";
static std::string numbers_non_zero = "(1+2+3+4+5+6+7+8+9)";

static RE validVirus = RE("besmettingsgraad%+sterftegraad%+incubatietijdN+ziekte%+incubatie?+asymptomatisch?+mutatie%+mutatieR", 'Q');
static RE validWorld = RE("populatieN+bevolkingsdictheidN+gezondheidsgraadZ+agrens%+zgrens%+hgrens%+sgrens%", 'Q');

static RE percentageKey = RE(alphabet+"*(%)+("+alphabet+"(%))", 'Q');
static RE questionKey = RE(alphabet+"*(?)+("+alphabet+"(?))", 'Q');
static RE rangeKey = RE(alphabet+"*(R)+("+alphabet+"(R))", 'Q');
static RE integersKey = RE(alphabet+"*(N)+("+alphabet+"(N))", 'Q');
static RE commaKey = RE(alphabet+"*(Z)+("+alphabet+"(Z))", 'Q');

static RE percentageValue = RE("((1.)(0)*)+((0.)"+numbers+"*)", 'Q');
static RE questionValue = RE("(0.(0)*)+(1.(0)*)", 'Q');
static RE rangeValue = RE("("+numbers_non_zero+numbers+"*."+numbers+"*)+(0."+numbers+"*)", 'Q');
static RE integerValue = RE("(0.(0)*)+("+numbers_non_zero+numbers+"*.(0)*)", 'Q');

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
