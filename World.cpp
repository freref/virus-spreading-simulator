//
// Created by frehml on 29/06/2021.
//

#include "World.h"

World::World(std::string path){
    std::ifstream input(path);
    input >> info;
}

World::~World(){
    for(auto &row : grid){
        for(auto &elem : row){
            delete elem;
        }
    }
}

void World::correctness() {
    for (json::iterator it = info.begin(); it != info.end(); ++it){
        Correctness::correctWorld(it);
    }
}

void World::makeWorld() {
    populateProperties();
    populateGrid();
}

void World::populateGrid() {
    int check = 0;

    for(int i = 0; i < sqrt(populatie); i++){
        vector<Mens*> row;
        for(int i = 0; i < sqrt(populatie); i++){
            row.push_back(Mens::generateHuman(gezondheidsgraad, bevolkingsdichtheid));

            check++;
            if (check >= populatie){
                grid.push_back(row);
                goto endLoop;
            }
        }
        grid.push_back(row);
    }
    endLoop:
    return;
}

void World::populateProperties() {
    for (json::iterator it = info.begin(); it != info.end(); ++it){
        if(it.key() == "agrens%"){
            agrens = it.value();
        }
        else if(it.key() == "populatieN"){
            populatie = it.value();
        }
        else if(it.key() == "bevolkingsdictheidN"){
            bevolkingsdichtheid = it.value();
        }
        else if(it.key() == "gezondheidsgraadZ"){
            gezondheidsgraad = it.value();
        }
        else if(it.key() == "agrens%"){
            agrens = it.value();
        }
        else if(it.key() == "hgrens%"){
            hgrens = it.value();
        }
        else if(it.key() == "zgrens%"){
            zgrens = it.value();
        }
    }
}

void World::print(){
    for(auto &row : grid){
        for(auto &human : row){
            std::cout << human->toestand << "  -" << human->rightDistance << "-  ";
        }
        std::cout << std::endl;
        for(auto &human : row){
            std::cout << "|\t";
        }
        std::cout << std::endl;
        for(auto &human : row){
            std::cout << human->downDistance <<"\t";
        }
        std::cout << std::endl;
        for(auto &human : row){
            std::cout << "|\t";
        }
        std::cout << std::endl;
    }
}