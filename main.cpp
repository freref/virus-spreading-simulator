#include <iostream>
#include "json.hpp"
#include "Virus.h"
#include "World.h"
#include "Statistiek.h"
#include "Simulatie.h"

using json = nlohmann::json;


int main() {

    std::string virus = "Virus/virus1.json";
    std::string world = "World/world1.json";

    Virus v(virus);
    //v.correctness();
    v.makeVirus(0);

    World w(world);
    //w.correctness();
    w.makeWorld();

    Simulatie sim(v, w);

    //===========================================================================

    std::cout << "Er zijn verschillende commando's beschikbaar:\n"
                 "'stap' laat de simulatie n dagen vooruit gaan,\n"
                 "'print' geeft de huidige staat van de wereld weer,\n"
                 "'infecteer' infecteert een gegeven persson op rij x en plaats y, \n"
                 "'mens' geeft de toestand van een persoon weer, \n"
                 "'virus' geeft de naam van het huidig virus weer, \n"
                 "'exit' stopt het programma.\n";
    std::string input;
    std::cout << "> ";
    std::getline(std::cin, input);

    while (input != "exit") {
        if(input == "print"){
            sim.world.print();
        }
        else if (input == "infecteer"){
            string x;
            string y;
            std::cout << "Rij coordinaat:" << std::endl <<"> ";
            std::getline(std::cin, x);
            std::cout << "Rij positie:" << std::endl <<"> ";
            std::getline(std::cin, y);
            sim.infect(stoi(x), stoi(y));
        }
        else if (input  == "stap") {
            string step;
            std::cout << "Stappen:" << std::endl <<"> ";
            std::getline(std::cin, step);
            sim.simulate(stoi(step));
        }
        else if (input  == "virus") {
            sim.virus.calculateName();
            std::cout << "Virus naam: " <<sim.virus.name << std::endl;
        }
        else if (input == "mens"){
            string x;
            string y;
            std::cout << "Rij coordinaat:" << std::endl <<"> ";
            std::getline(std::cin, x);
            std::cout << "Rij positie:" << std::endl <<"> ";
            std::getline(std::cin, y);
            sim.world.grid[stoi(x)][stoi(y)]->print();
        }
        std::cout << "> ";
        std::getline(std::cin, input);
    }

    return 0;
}
