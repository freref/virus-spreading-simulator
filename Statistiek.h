//
// Created by twijg on 7/5/21.
//

#ifndef VSS_STATISTIEK_H
#define VSS_STATISTIEK_H

#include <vector>
#include <iostream>

class Statistiek {
public:
    std::vector<int> logDoden;
    int totDoden;
    std::vector<int> logOpnames;
    int totOpnames;
    std::vector<int> logVerlaters;
    int totVerlaters;
    std::vector<int> logZelfGenezen;
    int totZelfGenezen;

    int populatie;

    Statistiek(int populatie);
    void printOverzicht();
    void printTijdsOverzicht(unsigned int dagen); // print overzicht van de laatse n dagen

};

#endif //VSS_STATISTIEK_H
