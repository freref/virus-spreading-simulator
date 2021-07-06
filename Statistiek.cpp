//
// Created by twijg on 7/5/21.
//

#include "Statistiek.h"


Statistiek::Statistiek(int& pop) {
    populatie = pop;
}


void Statistiek::printOverzicht() {
    std::cout << "Van de volledige populatie van " << populatie << " mensen zijn er momenteel:\n";
    std::cout << totOpnames + totZelfGenezen << "\tdie ziek zijn geworden waarvan\n"; // dit gaat er vanuit dat iedereen die sterft opgenomen wordt
    std::cout << totDoden << "\thelaas overleden zijn.\n";
    std::cout << totVerlaters + totZelfGenezen << "\tmensen zijn ziek geworden en zijn succesvol genezen waarvan\n";
    std::cout << totVerlaters << "\tmensen genezen zijn in het ziekenhuis en\n";
    std::cout << totZelfGenezen << "\tmensen thuis zijn uitgeziekt\n";
}


void Statistiek::printTijdsOverzicht(unsigned int& dagen) {
    int opgentot = 0;
    int gestorvtot = 0;
    int ontslagentot = 0;
    int genezentot = 0;
    int verstrekenDagen = logOpnames.size();

    for (unsigned int i = 1; i <= std::min((double) dagen, (double) verstrekenDagen-1); i++) {
        opgentot += logOpnames[verstrekenDagen-i];
        gestorvtot += logDoden[verstrekenDagen-i];
        ontslagentot += logVerlaters[verstrekenDagen-i];
        genezentot += logZelfGenezen[verstrekenDagen-i];
    }
    std::cout << "De afgelopen " << dagen << " dagen zijn er\n";
    std::cout << opgentot << "\tmensen opgenomen in het ziekenhuis\n";
    std::cout << gestorvtot << "\tmensen helaas overleden\n";
    std::cout << ontslagentot << "\tmensen uit het ziekenhuis ontslagen\n";
    std::cout << genezentot << "\tmensen thuis genezen\n";
}

void Statistiek::addDoden(int &dag, int &doden) {
    totDoden += doden;

    // de log aanvullen indien nodig (niemand gestorven de laatste dagen)
    while (logDoden.size() < dag) {
        logDoden.push_back(0);
    }
    logDoden[dag] += doden;
}

void Statistiek::addOpnames(int& dag, int& opnames) {
    totOpnames += opnames;

    // de log aanvullen indien nodig (niemand opgenomen de laatste dagen)
    while (logOpnames.size() < dag) {
        logOpnames.push_back(0);
    }
    logOpnames[dag] += opnames;
}

void Statistiek::addVerlaters(int &dag, int &verlaters) {
    totVerlaters += verlaters;

    // de log aanvullen indien nodig (niemand verlaten de laatste dagen)
    while (logVerlaters.size() < dag) {
        logVerlaters.push_back(0);
    }
    logVerlaters[dag] += verlaters;
}

void Statistiek::addZelfGenezen(int &dag, int &zelfGenezen) {
    totZelfGenezen += zelfGenezen;

    // de log aanvullen indien nodig (niemand opgenomen de laatste dagen)
    while (logZelfGenezen.size() < dag) {
        logZelfGenezen.push_back(0);
    }
    logZelfGenezen[dag] += zelfGenezen;
}
