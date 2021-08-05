//
// Created by twijg on 7/5/21.
//

#include "Statistiek.h"



void Statistiek::add(std::string line) {
    log += line;
}

void Statistiek::update(World w) {
    map<string, int> stats;

    for(auto &row : w.grid){
        for(auto &human : row){
            stats[human->toestand] += 1;
        }
    }

    log += "Gezond: " + to_string(stats["G"]) + "\n";
    log += "Asymptomatisch: " + to_string(stats["A"]) + "\n";
    log += "Incuberend: " + to_string(stats["I"]) + "\n";
    log += "Ziek: " + to_string(stats["Z"]) + "\n";
    log += "Gehospitaliseerd: " + to_string(stats["H"]) + "\n";
    log += "Dood: " + to_string(stats["X"]) + "\n\n";
}

void Statistiek::print(){
    std::cout << log << std::endl;
}