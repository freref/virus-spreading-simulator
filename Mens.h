//
// Created by twijg on 7/6/21.
//

#ifndef VSS_MENS_H
#define VSS_MENS_H

#include <string>

class Mens {
public:
    std::string toestand = "gezond"; //gezond, ziek, hospitaal, dood
    bool besmettelijk = false;
    int dagenSymp = 0;
    double ziekte = 0.0;
};

#endif //VSS_MENS_H
