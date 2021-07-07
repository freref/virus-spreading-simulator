//
// Created by frehml on 29/06/2021.
//

#include "World.h"

World::World(std::string path){
    json info;
    std::ifstream input(path);
    input >> info;
    makeWorld(info);
}

void World::makeWorld(json &info) {
    for (json::iterator it = info.begin(); it != info.end(); ++it){
        Correctness::correctWorld(it);
    }
}

int World::getPopulatie() {
    return populatie;
}

void World::setPopulatie(int pop) {
    if (pop >= 0) {
        populatie = pop;
    } else {
        std::cerr << "populatie kan niet negatief zijn\n";
    }
}

int World::getBevolkingsdichtheid() {
    return bevolkingsdichtheid;
}

void World::setBevolkingsdichtheid(int bev) {
    if (bev >= 0) {
        bevolkingsdichtheid = bev;
    } else {
        std::cerr << "bevolkingsdichtheid kan niet negatief zijn\n";
    }
}

double World::getGezondeidsgraad() {
    return gezonheidsgraad;
}

void World::setGezondheidsgraad(double gez) {
    if (gez >= 0.0) {
        gezonheidsgraad = gez;
    } else {
        std::cerr << "gezonheidsgraad kan niet negatief zijn\n";
    }
}

double World::getAgrens(){
    return agrens;
}

void World::setAgrens(double ag) {
    if (1.0 >= ag >= 0.0) {
        agrens = ag;
    } else {
        std::cerr << "agrens has to be a number between 0.0 and 1.0\n";
    }
}

World::World() {

}

