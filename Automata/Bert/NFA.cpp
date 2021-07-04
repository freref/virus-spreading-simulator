#include "NFA.h"


using json = nlohmann::json;
using strvec = std::vector<std::string>;


NFA::NFA() {}


bool NFA::accepts(std::string input) {

    std::vector<State> resultaat = leidtTot(startstaat,states, input);
    for (State staat : resultaat) {
        if (staat.accepting) {
            return true;
        }
    }
    return false;
}


NFA NFA::lees(std::string file){
    std::ifstream input(file);
    json j;
    input >> j;

    NFA output;
    output.type = j["type"];

    State tempstaat;
    //tempstaat.transities = std::vector<std::vector<std::string>>(j["alphabet"].begin(), j["alphabet"].end());
    for (auto karakter : j["alphabet"]) {
        tempstaat.transities.push_back({karakter});
        output.alfabet.push_back(karakter);
    }
    for (int i = 0; i < j["states"].size(); i++) {
        tempstaat.naam = j["states"].at(i)["name"];
        tempstaat.starting = j["states"].at(i)["starting"];
        tempstaat.accepting = j["states"].at(i)["accepting"];
        output.states.push_back(tempstaat);
    }
    for (int i = 0; i < j["transitions"].size(); i++){
        for (int k = 0; k < output.states.size(); k++) {
            if(output.states.at(k).naam == j["transitions"].at(i)["from"]) {
                for(int l = 0; l <  output.states.at(k).transities.size(); l++) {
                    if (output.states.at(k).transities.at(l).at(0) == j["transitions"].at(i)["input"])
                        output.states.at(k).transities.at(l).push_back(j["transitions"].at(i)["to"]);
                }
            }
        }
    }

    if (output.type == "NFA" or output.type == "ENFA") {
        for (State staati : output.states) {
            for (strvec transi : staati.transities) {
                for (int k = 0; k < staati.transities.size(); k++) {
                    if (transi != staati.transities[k] and transi[0] == staati.transities[k][0]) {
                        transi.insert(transi.end(), staati.transities[k].begin() + 1, staati.transities[k].end());
                        staati.transities.erase(staati.transities.begin() + k);
                    }
                }
            }
        }
    }

    for (State staat : output.states) {
        if (staat.starting) {
            output.startstaat = staat;
        }
    }
    return output;
}


void NFA::print(){
    json j;
    j["type"] = type;
    j["alphabet"] = alfabet;
    j["states"];
    j["transitions"];
    for (State staat : states) {
        j["states"].push_back({{"name", staat.naam}, {"starting", staat.starting}, {"accepting", staat.accepting}});
        for (strvec trans : staat.transities) {
            strvec tweetrans = trans;
            tweetrans.erase(tweetrans.begin());
            for (std::string el : tweetrans) {
                j["transitions"].push_back({{"from", staat.naam}, {"to", el}, {"input", trans[0]}}) ;
            }
        }
    }
    std::cout << std::setw(4) << j << std::endl;
}


bool compareNamesN(State a, State b) {return a.naam < b.naam;}



void NFA::toDFArec(NFA* dfa, NFA nfa,  std::vector<State> gestaten) {
    /*
     * DOET: te combineren staten aannemen.
     *  - Sorteren en opkuisen
     *  - Naam, starting en accepting goedzetten (in comstaat)
     *  - Transities combineren
     *  - Transities samenvoegen en opkuisen
     */

    if (gestaten.empty()) {
        return;
    }

    std::vector<State> allestaten = nfa.states;

    //sorteren en dubbels weg
    std::sort(gestaten.begin(), gestaten.end(), compareNamesN);
    // TODO: dubbels verwijderen !!


    State comstaat;
    comstaat.accepting = false;
    comstaat.starting = false;

    // start
    if (gestaten.size() == 1 and gestaten[0].starting) {
        comstaat.starting = true;
    }

    // naam, accepting en transities
    std::vector<strvec> geztransities;
    std::string geznaam = "{";
    geznaam += gestaten[0].naam;

    for (int i = 1; i <gestaten.size() ; ++i) {
        geznaam += ",";
        geznaam += gestaten[i].naam;
    }
    geznaam += "}";
    comstaat.naam = geznaam;
    // als we het al gedaan hebben voor deze staat, stop maar.
    for (State staat : dfa->states) {
        if (staat.naam == comstaat.naam) {
            return;
        }
    }

    // transities
    for (int i = 0; i < gestaten.size(); i++) {
        if (gestaten[i].accepting) {
            comstaat.accepting = true;
        }
        std::vector<strvec> nieuwtransities;
        for (strvec trans : gestaten[i].transities) {
            strvec nieuwtrans = {trans[0]};
            strvec uitkomst = gestaten[i].next(trans[0][0]); // tweede nul voor: str -> char
            nieuwtrans.insert(nieuwtrans.end(), uitkomst.begin(), uitkomst.end());
            nieuwtransities.push_back(nieuwtrans);
        }
        geztransities.insert(geztransities.end(), nieuwtransities.begin(), nieuwtransities.end());
    }


    // transities met zelfde input samen zetten
    for (strvec trans : geztransities) {
        unsigned int i = 0;
        while (i < comstaat.transities.size() and comstaat.transities[i][0] != trans[0]) {
            i++;
        }
        if (i == comstaat.transities.size()) {
            comstaat.transities.push_back(trans);
        } else {
            comstaat.transities[i].insert(comstaat.transities[i].end(), trans.begin() + 1, trans.end());
        }
    }

    // dubbels halen uit een transitie (bijv. ["a", "0", "1", "0"])
    for (int i = 0; i < comstaat.transities.size(); i++) {
        std::sort(comstaat.transities[i].begin() + 1, comstaat.transities[i].end(), [](std::string a, std::string b) {
            return (std::stoi(a) < std::stoi(b));
        });
        auto last = std::unique(comstaat.transities[i].begin() + 1, comstaat.transities[i].end());
        comstaat.transities[i].erase(last, comstaat.transities[i].end());
    }

    // recursie voorbereiden
    std::vector<State> statesTeComb;
    std::vector<std::vector<State>> alleCombStaten;

    // transities van naam veranderen (combineren van to:'s) en te combineren staten voor recursie klaar zetten.
    for (int i = 0; i < comstaat.transities.size(); i++) {
        strvec teCombNamen;
        std::string combinaam = "{" + comstaat.transities[i].at(1);
        teCombNamen.push_back(comstaat.transities[i].at(1));
        for (int k = 2; k < comstaat.transities[i].size(); k++) {
            combinaam += "," + comstaat.transities[i][k];
            teCombNamen.push_back(comstaat.transities[i][k]);
        }
        combinaam += "}";
        // transitie aanpassen naar gecombineerde vorm:
        comstaat.transities[i].erase(comstaat.transities[i].begin() + 1, comstaat.transities[i].end());
        comstaat.transities[i].push_back(combinaam);
        // de te combineren staten voor deze input toevoegen aan de te recursiveren dingen
        alleCombStaten.push_back(namesToStates(teCombNamen, allestaten));
    }

    dfa->states.push_back(comstaat);
    allestaten.push_back(comstaat);


    for (std::vector<State> staten : alleCombStaten) {
        toDFArec(dfa, nfa, staten);
    }
}


NFA NFA::toDFA(){
    NFA dfa;
    dfa.type = "DFA";
    dfa.alfabet = alfabet;
    dfa.startstaat = startstaat;
    toDFArec(&dfa, *this, {startstaat});


    return dfa;
}

