#include <iostream>
#include "json.hpp"
#include "Virus.h"
#include "World.h"
#include "Statistiek.h"
#include "Simulatie.h"

using json = nlohmann::json;


int main() {
    std::string virus = "../Input/Virus/virus1.json";
    std::string world = "../Input/World/world1.json";

    Virus v(virus);
    v.correctness();
    v.makeVirus();

    World w(world);

    Statistiek s(w.getPopulatie());

    Simulatie sim(v, w, true);

    std::cout << "Er zijn verschillende commando's beschikbaar:\n"
                 "'step n' laat de simulatie n dagen vooruit gaan,\n"
                 "'stat n' geeft een statistisch overzicht van de voorbije n dagen, als n nul is geeft het een overzicht van de hele periode,\n"
                 "'virus' geeft de karakteristiek van het huidige virus,\n"
                 "'mutate on/off' zet het muteren van het virus aan of af (standaard aan),\n"
                 "'exit' stopt het programma.\n";
    std::string input;
    std::cout << "> ";
    std::getline(std::cin, input);

    while (input != "exit") {
        if (input.substr(0,4) == "step") {
            int steps = std::stoi(input.substr(5));
            for (int i = 0; i < steps; i++) {
                sim.step();
            }
        } else if (input.substr(0, 4) == "stat") {
            unsigned int dagen = std::stoi(input.substr(5));
            if (dagen == 0) {
                s.printOverzicht();
            } else {
                s.printTijdsOverzicht(dagen);
            }
        } else if (input == "virus") {
            std::cout << sim.virus.giveName() << "\n";
        } else if (input.substr(0, 6) == "mutate") {
            if (input.substr(7, 2) == "on") {
                sim.mutate = true;
            } else {
                sim.mutate = false;
            }
        } else {
                std::cout << input << " is geen geldig commando.\n";
        }

        std::cout << "> ";
        std::getline(std::cin, input);
    }
    //std::cout << "Nog een fijne dag!\n";

    return 0;
}
