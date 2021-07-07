#include "state.h"


strvec State::next(std::string input) {
    strvec volg;
    if (input == "") {
        return volg;
    }
    std::string inp;
    inp += input;
    for (auto trans : transities) {
        if(trans[0] == inp) {
            volg = {trans.begin() + 1, trans.end()};
        }
    }
    return volg;
}

std::vector<State> namesToStates(strvec names, std::vector<State>statelist) {
    std::vector<State> output;
    for (std::string naam : names) {
        for (State staat : statelist) {
            if (staat.naam == naam) {
                output.push_back(staat);
                break;
            } else {
            }
        }
    }
    return  output;
}


std::vector<State> leidtTot(State staat, std::vector<State> statelist, std::string input) {
    std::vector<State> output;
    if (input.empty()) {
        output.push_back(staat);
        return output;
    } else {
        strvec volgende = staat.next(input);

        for (std::string nstnaam : volgende) {
            for (State nstaat : statelist) {
                if (nstaat.naam == nstnaam) {
                    std::vector<State> tempres = leidtTot(nstaat, statelist, input.substr(1));
                    output.insert( output.end(), tempres.begin(), tempres.end());
                }
            }
        }
        return output;
    }
}
