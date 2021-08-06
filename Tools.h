//
// Created by Frederic on 29/07/2021.
//

#ifndef VSS_TOOLS_H
#define VSS_TOOLS_H

#include "Automata/Frederic/RE.h"
#include <chrono>
#include <random>
#include <QTime>
#include <QCoreApplication>

static std::string alphabet = "(a+b+c+d+e+f+g+h+i+j+k+l+m+n+o+p+q+r+s+t+u+v+w+x+y+z)";
static std::string numbers = "(1+2+3+4+5+6+7+8+9+0)";
static std::string numbers_non_zero = "(1+2+3+4+5+6+7+8+9)";

static RE validVirus = RE("ziekte%+incubatietijdN+asymptomatischB+mutatie%+mutatieR+infectieN+recoveryN", 'Q');
static RE validWorld = RE("populatieN+bevolkingsdictheidN+gezondheidsgraadZ+agrens%+zgrens%+hgrens%", 'Q');

static RE percentageKey = RE(alphabet+"*(%)+("+alphabet+"(%))", 'Q');
static RE questionKey = RE(alphabet+"*(B)+("+alphabet+"(B))", 'Q');
static RE rangeKey = RE(alphabet+"*(R)+("+alphabet+"(R))", 'Q');
static RE integersKey = RE(alphabet+"*(N)+("+alphabet+"(N))", 'Q');
static RE commaKey = RE(alphabet+"*(Z)+("+alphabet+"(Z))", 'Q');

static RE percentageValue = RE("((1.)(0)*)+((0.)"+numbers+"*)", 'Q');
static RE questionValue = RE("(0.(0)*)+(1.(0)*)", 'Q');
static RE rangeValue = RE("("+numbers_non_zero+numbers+"*."+numbers+"*)+(0."+numbers+"*)", 'Q');
static RE integerValue = RE("(0.(0)*)+("+numbers_non_zero+numbers+"*.(0)*)", 'Q');

static ENFA validVirusENFA = validVirus.toENFA("../Output/Correctness/validVirus.json");
static ENFA validWorldENFA = validWorld.toENFA("../Output/Correctness/validWorld.json");
static ENFA percentageKeyENFA = percentageKey.toENFA("../Output/Correctness/percentageKey.json");
static ENFA questionKeyENFA = questionKey.toENFA("../Output/Correctness/questionKey.json");
static ENFA rangeKeyENFA = rangeKey.toENFA("../Output/Correctness/rangeKey.json");
static ENFA integersKeyENFA = integersKey.toENFA("../Output/Correctness/integersKey.json");
static ENFA commaKeyENFA = commaKey.toENFA("../Output/Correctness/commaKey.json");
static ENFA percentageValueENFA = percentageValue.toENFA("../Output/Correctness/percentageValue.json");
static ENFA questionValueENFA = questionValue.toENFA("../Output/Correctness/questionValue.json");
static ENFA rangeValueENFA = rangeValue.toENFA("../Output/Correctness/rangeValue.json");
static ENFA integerValueENFA = integerValue.toENFA("../Output/Correctness/integerValue.json");

static unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
static std::default_random_engine generator (seed);

#endif //VSS_TOOLS_H
