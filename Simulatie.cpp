//
// Created by twijg on 7/6/21.
//

#include "Simulatie.h"

Simulatie::Simulatie(Virus& vir, World& wereld) {
    virus = vir;
    world = wereld;
}

void Simulatie::infect(int x, int y) {
    Mens* m = world.grid[x][y];
    string i_string = (virus.properties["infectieN"].enfa["alphabet"][0]);
    double i = stod(i_string);

    if(m->infectie < i && m->toestand == "G"){
        m->toestand = "I";
        m->it = it;
        m->infectie++;
        m->calculateValues(virus);
    }
}

void Simulatie::spread(Mens* human){
    if((human->toestand == "Z" || human->toestand == "H" || (human->toestand == "A" || human->toestand == "I") && virus.properties["asymptomatischB"].accepts("1"))){
        std::cout << "spread inside" << std::endl;
        if(it - human->it == human->leftDistance){
            infect(human->n.left.first, human->n.left.second);
        }
        if(it - human->it == human->rightDistance){
            infect(human->n.right.first, human->n.right.second);
        }
        if(it - human->it == human->upDistance){
            infect(human->n.up.first, human->n.up.second);
        }
        if(it - human->it == human->downDistance){
            infect(human->n.down.first, human->n.down.second);
        }
    }
}

void Simulatie::simulate(int n){
    for(int i = 0; i < n; i++){
        for(auto &row : world.grid){
            for(auto &human : row){
                if(human->toestand != "G" && human->toestand != "X"){
                    if(it - human->it == human->incubatie + human->recovery){
                        human->toestand = "G";
                    }
                    if(it - human->it == human->incubatie){
                        breakout(human);
                    }

                    spread(human);
                }
            }
        }
        it++;
    }
}

void Simulatie::breakout(Mens *m) {
    string z_string = (virus.properties["ziekte%"].enfa["alphabet"][0]);
    double z = stod(z_string);
    double sickness = m->gezondheidsgraad*z;

    if(sickness < world.agrens){
        m->toestand = "A";
    }
    else if (sickness < world.zgrens){
        m->toestand = "Z";
    }
    else if (sickness < world.hgrens){
        m->toestand = "H";
    }
    else{
        m->toestand = "X";
    }
}