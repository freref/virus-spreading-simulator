//
// Created by twijg on 7/5/21.
//

#include "Statistiek.h"

string Statistiek::print(){
    std::string output;
    for(auto &pair : stats){
        output += "Dag: " + to_string(pair.first) + "\n\n";
        output += "Nieuwe gevallen:\n\n";
        output += "Infecties: " + to_string(pair.second["infectie"]) + "\n";
        output += "Genezen: " + to_string(pair.second["genezen"]) + "\n";
        output += "Ziek: " + to_string(pair.second["ziek"]) + "\n";
        output += "Asymptomatisch: " + to_string(pair.second["asymptomatisch"]) + "\n";
        output += "Gestorven: " + to_string(pair.second["dood"]) + "\n";
        output += "Gehospitaliseerd: " + to_string(pair.second["gehospitaliseerd"]) + "\n\n";

        if(pair.second["mutatie"] != 0){
            output += "Het virus is geverifieerd door het TFA algoritme en er is een mutatie gedetecteerd\n";
            output += "Het nieuwe virus heet: " + names[pair.second["naam"]] + "\n\n";
        }
        else
            output += "Er is geen mutatie gedetecteerd\n\n";

        if(pair.first == 0){
            output += "Virus startnaam: " + names[0] + "\n\n";
        }
        output += "============================================\n\n";
    }
    return output;
}