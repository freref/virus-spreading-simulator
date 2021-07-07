//
// Created by twijg on 7/6/21.
//

#include "Simulatie.h"


void Simulatie::buildGrid() {
    int pop = world.getPopulatie();
    int x  = std::floor(std::sqrt(pop));
    int y = std::ceil(pop/x);

    Mens mens;
    Mens dood;
    dood.toestand = "Dood";

    for (int i = 0; i < x-1; i++) {
        std::fill (worldgrid[i].begin(), worldgrid[i].begin()+y-1, mens);
    }
    pop -= (x-1)*y;
    std::fill (worldgrid[x-1].begin(), worldgrid[x-1].begin()+pop-1, mens);
    std::fill (worldgrid[x-1].begin()+pop, worldgrid[x-1].begin()+y-1, mens);
}

void Simulatie::step() {
    // maak een nieuw worldgrid aan waar alle nieuwe dingen komen te staan en vervang daarna het oude
    std::vector<std::vector<Mens>> newgrid = worldgrid;


}

Simulatie::Simulatie() {


}

Simulatie::Simulatie(Virus& vir, World& wereld, bool mut) {
    virus = vir;
    world = wereld;
    mutate = mut;
}
