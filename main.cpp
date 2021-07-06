#include <iostream>
#include "json.hpp"
#include "Virus.h"
#include "World.h"
#include "Statistiek.h"

using json = nlohmann::json;


int main() {
    std::string virus = "../Input/Virus/virus1.json";
    std::string world = "../Input/World/world1.json";

    Virus v(virus);
    World w(world);
    Statistiek s(w.getPopulatie());

    std::cout << "Er zijn verschillende commando's beschikbaar, 'step n' laat de simulatie n dagen vooruit gaan, 'stat n' "
                 "geeft een statistisch overzicht van de voorbije n dagen, als n nul is geeft het een overzicht van de "
                 "hele periode, 'exit' stopt het programma.\n";
    std::string input;
    std::cout << "> ";
    std::cin >> input;

    while (input != "exit") {
        if (input.substr(0,4) == "step") {
            int steps = std::stoi(input.substr(5));
            // TODO: 'steps' stappen in de simulatie
            for (int i = 0; i < steps; i++) {
                //simualtie +1
            }
        } else if (input.substr(0, 4) == "stat") {
            unsigned int dagen = std::stoi(input.substr(5));
            if (dagen == 0) {
                s.printOverzicht();
            } else {
                s.printTijdsOverzicht(dagen);
            }
        }
    }

    return 0;
}
