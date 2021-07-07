#include "DFA.h"


using json = nlohmann::json;


/**
 *
 * @param names
 * @param statelist
 * @return
 */



/**
 *
 * @param input
 * @return
 */
bool DFA::accepts(std::string input) {
    State current = startstaat;
    std::string tnaam;
    for (char c : input) {
        std::string temp = "";
        temp += c;
        tnaam = current.next(temp)[0];
        for (State tstaat : states) {
            if (tstaat.naam == tnaam) {
                current = tstaat;
                break;
            }
        }
    }
    return current.accepting;
}


/**
 *
 * @param file
 * @return
 */
DFA DFA::lees(std::string file){
    std::ifstream input(file);
    json j;
    input >> j;

    DFA output;
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

    for (State staat : output.states) {
        if (staat.starting) {
            output.startstaat = staat;
        }
    }
    return output;
}

/**
 *
 */
void DFA::print(){
    json j;
    j["type"] = type;
    j["alphabet"] = alfabet;
    j["states"];
    j["transitions"];
    for (State staat : states) {
        j["states"].push_back({{"name", staat.naam}, {"starting", staat.starting}, {"accepting", staat.accepting}});
        for (auto trans : staat.transities) {
            j["transitions"].push_back({{"from", staat.naam}, {"to", trans[1]}, {"input", trans[0]}}) ;
        }
    }
    std::cout << std::setw(4) << j << std::endl;
}


/**
 *
 */
DFA::DFA() {}



void DFA::maal(State s1, State s2, bool doorsnede, std::vector<State> df1, std::vector<State> df2) {
    State combstaat;
    combstaat.naam = "(" + s1.naam + "," + s2.naam + ")";

    for (State staat : states) {
        if (staat.naam == combstaat.naam) {
            return; // we zijn hier al geweest
        }
    }
    combstaat.starting = false;
    if (!doorsnede) { // verwarrend he, ik weet het, ik zou het beter hebben omgedraaid
        combstaat.accepting = (s1.accepting or s2.accepting);
    } else {
        combstaat.accepting = (s1.accepting and s2.accepting);
    }
    std::vector<std::vector<State>> teCombStaten;

    for (std::string letter : alfabet) {
        teCombStaten.push_back({namesToStates(s1.next((letter)), df1)[0], namesToStates(s2.next((letter)), df2)[0]});
        combstaat.transities.push_back({letter, "(" + s1.next(letter)[0] + "," + s2.next(letter)[0]+ ")"});
    }
    states.push_back(combstaat);
    for (auto teComb : teCombStaten) {
        maal(teComb[0], teComb[1], doorsnede, df1, df2);
    }
}


/**
 *
 * @param dfa1
 * @param dfa2
 * @param doorsnede
 */
//product:
DFA::DFA(DFA dfa1, DFA dfa2, bool doorsnede) {
    std::vector<State> alleStaten = dfa1.states;
    alleStaten.insert(alleStaten.end(), dfa2.states.begin(), dfa2.states.end());

    startstaat.starting = true;
    startstaat.naam = "(" + dfa1.startstaat.naam + "," + dfa2.startstaat.naam + ")";
    alfabet = dfa1.alfabet;
    type = dfa1.type; // hopelijk DFA...
    if (!doorsnede) { // verwarrend he, ik weet het, ik zou het beter hebben omgedraaid
        startstaat.accepting = (dfa1.startstaat.accepting or dfa2.startstaat.accepting);
    } else {
        startstaat.accepting = (dfa1.startstaat.accepting and dfa2.startstaat.accepting);
    }
    states.push_back(startstaat);

    std::vector<State> teCombStaten;
    for (std::string letter : alfabet) {
        teCombStaten = namesToStates(dfa1.startstaat.next((letter)), dfa1.states);
        teCombStaten.push_back(namesToStates(dfa2.startstaat.next((letter)), dfa2.states)[0]);
        startstaat.transities.push_back({letter, "(" + teCombStaten[0].naam + "," + teCombStaten[1].naam+ ")"});
        maal(teCombStaten[0], teCombStaten[1], doorsnede, dfa1.states, dfa2.states);
    }

    states[0] = startstaat;

}
