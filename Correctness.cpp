//
// Created by frehml on 29/06/2021.
//

#include "Correctness.h"

void Correctness::correctValue(const json::iterator &it) {
    if (percentageKeyENFA.accepts(it.key()))
        percentageCheck(it.value());
    else if (questionKeyENFA.accepts(it.key()))
        questionCheck(it.value());
    else if (rangeKeyENFA.accepts(it.key())){
        rangeCheck(it.value()[0]);
        rangeCheck(it.value()[1]);
    }
    else if (commaKeyENFA.accepts(it.key()))
        rangeCheck(it.value());
    else if (integersKeyENFA.accepts(it.key()))
        integerCheck(it.value());
}

void Correctness::correctWorld(json::iterator const &it) {
    if(not validWorldENFA.accepts(it.key()))
        std::cerr << it.key() << " is not a valid input type" << std::endl;
    else
        correctValue(it);
}

void Correctness::correctVirus(json::iterator const &it) {
    if(not validVirusENFA.accepts(it.key()))
        std::cerr << it.key() << " is not a valid input type" << std::endl;
    else
        correctValue(it);
}

void Correctness::percentageCheck(const json::iterator::value_type &value) {
    std::string p = std::to_string(value.get<double>());
    if(not percentageValueENFA.accepts(p))
        std::cerr << p + " is not a valid percentage" << std::endl;
}

void Correctness::questionCheck(const json::iterator::value_type &value) {
    std::string q = std::to_string(value.get<double>());
    if(not questionValueENFA.accepts(q))
        std::cerr << q + " is not a valid boolean" << std::endl;
}

void Correctness::rangeCheck(const json::iterator::value_type &value) {
    std::string r = std::to_string(value.get<double>());
    if(not rangeValueENFA.accepts(r))
        std::cerr << r + " is not a valid range" << std::endl;
}

void Correctness::integerCheck(const json::iterator::value_type &value) {
    std::string i = std::to_string(value.get<double>());
    if(not integerValueENFA.accepts(i))
        std::cerr << i + " is not a valid integer" << std::endl;
}