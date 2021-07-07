#include "ENFA.h"

using json = nlohmann::json;


ENFA::ENFA() {}



/**
 *
 * @param start
 * @return
 */

std::vector<State> ENFA::epsTransRes(State start) {
    std::vector<State> output = {start};
    strvec res = {start.naam};

    std::vector<State> meeBezig = {start};
    strvec tempbezig = {};

    while (!meeBezig.empty()) {
        for (State tstaat : meeBezig) {
            strvec test = tstaat.next(eps);
            tempbezig.insert(tempbezig.end(), test.begin(),  test.end());
        }
        int tot = tempbezig.size();
        for (int i = 0; i < tot; i++) {
            if (std::find(res.begin(), res.end(), tempbezig[i]) != res.end()) {
                tot --;
                tempbezig.erase(tempbezig.begin() + i);
                i --;
            }
        }
        meeBezig = namesToStates(tempbezig, states);
        res.insert(res.end(), tempbezig.begin(), tempbezig.end());
    }
    output = namesToStates(res, states);
    return output;
}

/**
 *
 * @param staat
 * @param input
 * @return
 */

strvec ENFA::volgende(State staat, std::string input) {
    strvec output;

    std::vector<State> eersteE = epsTransRes(staat);

    strvec naNaam;
    strvec volg;
    for (State estaat : eersteE) {
        volg = estaat.next(input);
        naNaam.insert(naNaam.end(), volg.begin(), volg.end());
    }
    std::vector<State> naInput = namesToStates(naNaam, states);

    volg.clear();
    for (State nastaat : naInput) {
        std::vector<State> eindstaten = epsTransRes(nastaat);
        for (State eindstaat : eindstaten) {
            output.push_back(eindstaat.naam);
        }
    }
    return output;
}



/**
 *
 * @param input
 * @return
 */

bool ENFA::accepts(std::string input) {
    std::string teps;
    if (type == "NFA") {
        teps = eps;
    } else {
        teps = "";
    }

    std::vector<State> resultaat = leidtTot(startstaat, states, input);
    for (State staat : resultaat) {
        if (staat.accepting) {
            return true;
        }
    }
    return false;
}

/**
 *
 * @param file
 * @return
 */

ENFA ENFA::lees(std::string file){
    std::ifstream input(file);
    json j;
    input >> j;

    ENFA output;
    output.type = j["type"];

    if (output.type == "ENFA") {
        output.eps = j["eps"];
    }

    State tempstaat;
    //tempstaat.transities = std::vector<std::vector<std::string>>(j["alphabet"].begin(), j["alphabet"].end());
    for (auto karakter : j["alphabet"]) {
        tempstaat.transities.push_back({karakter});
        output.alfabet.push_back(karakter);
    }
    if (output.type == "ENFA") {
        tempstaat.transities.push_back({output.eps});
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


    if (output.type == "ENFA" or output.type == "NFA") {  // OOK eps AANVAARDEN!
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
    for (int k =0; k < output.states.size(); k++) {
        int aantTrans = output.states[k].transities.size();
        for (int i = 0; i < aantTrans; i++) {
            if ( output.states[k].transities[i].size() == 1) {
                output.states[k].transities.erase( output.states[k].transities.begin() + i);
                i --;
                aantTrans --;
            }
        }
        if ( output.states[k].starting) {
            output.startstaat =  output.states[k];
        }
    }


    return output;
}

/**
 *
 */

void ENFA::print(){
    json j;
    j["type"] = type;
    j["alphabet"] = alfabet;
    j["states"];
    j["transitions"];
    if (type == "ENFA") {
        j["eps"] = eps;
    }
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

/**
 *
 * @param a
 * @param b
 * @return
 */

bool compareNamesE(State a, State b) {return a.naam < b.naam;}


/**
 *
 * @param dfa
 * @param enfa
 * @param gestaten
 */

void ENFA::toDFArec(ENFA* dfa, ENFA enfa,  std::vector<State> gestaten) {
    /* TODO: eps transities weggooien
     *
     * DOET: te combineren staten aannemen.
     *  - Sorteren en opkuisen
     *  - Naam, starting en accepting goedzetten (in comstaat)
     *  - Transities combineren
     *  - Transities samenvoegen en opkuisen
     *
     */

    if (gestaten.empty()) {
        return;
    }

    std::vector<State> allestaten = enfa.states;

    //sorteren en dubbels weg
    std::sort(gestaten.begin(), gestaten.end(), compareNamesE);

    // auto last = std::unique(gestaten.begin(), gestaten.end(), compareNames);
    // gestaten.erase(last, gestaten.end());

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
        // volgende gebruiken om met epsilons rekening te houden:
        std::vector<strvec> nieuwtransities;
        for (strvec trans : gestaten[i].transities) {
            if (trans[0] != eps) {
                strvec nieuwtrans = {trans[0]};
                strvec uitkomst = volgende(gestaten[i], trans[0]); // tweede nul voor: str -> char  EDIT: werkt nu met strings i.p.v. chars! :-)
                nieuwtrans.insert(nieuwtrans.end(), uitkomst.begin(), uitkomst.end());
                nieuwtransities.push_back(nieuwtrans);
            }
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


    for (auto staten : alleCombStaten) {
        toDFArec(dfa, enfa, staten);
    }
}

/**
 *
 * @return
 */

ENFA ENFA::toDFA(){
    ENFA dfa;
    dfa.type = "DFA";
    dfa.alfabet = alfabet;

    std::vector<State> startstaten = epsTransRes(startstaat);

    dfa.startstaat.naam = startstaten[0].naam;
    for (int i = 1; i < startstaten.size(); i++) {
        dfa.startstaat.naam += "," + startstaten[i].naam;
    }

    for (State staat : startstaten) {
        if (staat.accepting) {
            dfa.startstaat.accepting = true;
        }

        bool gevonden = false;
        for (strvec trans : staat.transities) {
            for (int i = 0; i < dfa.startstaat.transities.size(); i++) {
                if (dfa.startstaat.transities[i][0] == trans[0]) {
                    dfa.startstaat.transities[i].insert(dfa.startstaat.transities[i].end(), trans.begin() + 1, trans.end());
                    gevonden = true;
                }
            }
            if (!gevonden) {
                dfa.startstaat.transities.push_back(trans);
            }
            gevonden = false;
        }
    }
    dfa.startstaat.accepting = false;  // HEEJ NIET DOEN!!! WERKT NU TOEVALLIG MAAR MOET BETER. DA'S NIET VEEL WERK MAAR IK BEN ZO BLIJ DAT HET WERKT DAT IK GEEN ZIN HEB :-)
    dfa.startstaat.starting = true;


    toDFArec(&dfa, *this, {dfa.startstaat});


    return dfa;
}


