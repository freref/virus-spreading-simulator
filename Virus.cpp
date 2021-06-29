//
// Created by frehml on 29/06/2021.
//

#include "Virus.h"

Virus::Virus(std::string path){
    json info;
    ifstream input(path);
    input >> info;
    makeProperties(info);
}

void Virus::makeProperties(json &info) {
    for (json::iterator it = info.begin(); it != info.end(); ++it){
        Correctness::correctVirus(it);
        //properties[it.key()] = makeProperty(it.value());
    }
}

DFA Virus::makeProperty(json::iterator::value_type chance) {
    switch (chance.size()){
        case 2:
            return makeDFA(chance[0], chance[1]);
        case 1:
            return makeDFA(0, chance[0]);
        default:
            throw("Wrong input");
    }
}

DFA Virus::makeDFA(int a, int b) {

}