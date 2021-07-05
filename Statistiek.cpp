//
// Created by twijg on 7/5/21.
//

#include "Statistiek.h"


Statistiek::Statistiek(int pop) {
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


void Statistiek::printTijdsOverzicht(unsigned int dagen) {
    int opgentot = 0;
    int gestorvtot = 0;
    int ontslagentot = 0;
    int genezentot = 0;
    int verstrekenDagen = logOpnames.size();

    for (unsigned int i = 1; i <= dagen; i++) {
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
