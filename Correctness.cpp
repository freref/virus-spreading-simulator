//
// Created by frehml on 29/06/2021.
//

#include "Correctness.h"

void Correctness::correctValue(const json::iterator &it) {
    if (percentageKey.toENFA().accepts(it.key()))
        percentageCheck(it.value());
    else if (questionKey.toENFA().accepts(it.key()))
        questionCheck(it.value());
    else if (rangeKey.toENFA().accepts(it.key())){
        rangeCheck(it.value()[0]);
        rangeCheck(it.value()[1]);
    }
    else if (commaKey.accepts(it.key()))
        rangeCheck(it.value());
    else if (integersKey.toENFA().accepts(it.key()))
        integerCheck(it.value());
}

void Correctness::correctWorld(json::iterator const &it) {
    if(not validWorld.toENFA().accepts(it.key()))
        std::cerr << it.key() << " is not a valid input type" << std::endl;
    else
        correctValue(it);
}

void Correctness::correctVirus(json::iterator const &it) {
    if(not validVirus.toENFA().accepts(it.key()))
        std::cerr << it.key() << " is not a valid input type" << std::endl;
    else
        correctValue(it);
}

void Correctness::percentageCheck(const json::iterator::value_type &value) {
    std::string p = std::to_string(value.get<double>());
    if(not percentageValue.accepts(p))
        std::cerr << p + " is not a valid percentage" << std::endl;
}

void Correctness::questionCheck(const json::iterator::value_type &value) {
    std::string q = std::to_string(value.get<double>());
    if(not questionValue.accepts(q))
        std::cerr << q + " is not a valid boolean" << std::endl;
}

void Correctness::rangeCheck(const json::iterator::value_type &value) {
    std::string r = std::to_string(value.get<double>());
    if(not rangeValue.accepts(r))
        std::cerr << r + " is not a valid range" << std::endl;
}

void Correctness::integerCheck(const json::iterator::value_type &value) {
    std::string i = std::to_string(value.get<double>());
    if(not integerValue.accepts(i))
        std::cerr << i + " is not a valid integer" << std::endl;
}