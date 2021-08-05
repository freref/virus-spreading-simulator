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

    for(int x = 0; x < sqrt(populatie); x++){
        vector<Mens*> row;
        for(int y = 0; y < sqrt(populatie); y++){
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

    for(int y = 0; y < grid.size(); y++){
        for(int x = 0; x < grid[y].size(); x++){
            int minus_x_coord = x-1;
            int minus_y_coord = y-1;

            int plus_x_coord = x+1;
            int plus_y_coord = y+1;

            if(minus_x_coord < 0){
                minus_x_coord = grid[y].size()-1;
            }

            if(minus_y_coord < 0){
                minus_y_coord = grid.size()-1;
                if(x >= grid[minus_y_coord].size())
                    minus_y_coord--;
            }

            if(plus_y_coord >= grid.size()){
                plus_y_coord = 0;
            }

            if(plus_x_coord >= grid[y].size()){
                plus_x_coord = 0;
            }

            grid[y][x]->leftDistance = grid[y][minus_x_coord]->rightDistance;
            grid[y][x]->upDistance = grid[minus_y_coord][x]->downDistance;

            grid[y][x]->n.left = pair<int, int>{y, minus_x_coord};
            grid[y][x]->n.up = pair<int, int>{minus_y_coord, x};
            grid[y][x]->n.down = pair<int, int>{plus_y_coord, x};
            grid[y][x]->n.right = pair<int, int>{y, plus_x_coord};
        }
    }

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
    std::cout << std::endl;
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