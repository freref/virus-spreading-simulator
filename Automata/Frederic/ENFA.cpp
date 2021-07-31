//
// Created by frehml on 26/03/2021.
//

#include "ENFA.h"
#include "../../json.hpp"
#include <fstream>
#include <map>


using namespace std;
using json = nlohmann::json;

/**
 *
 * @param p
 */
//constructor
ENFA::ENFA(string p) {
    path = p;
    ifstream input(path);
    input >> enfa;
    eps = enfa["eps"];
}

/**
 *
 * @param nodes
 * @param input
 */
//zoekt de volgende nodes adhv een input
void ENFA::nextNodes(vector<int> *nodes, string input) {
    vector<int> new_states;
    for (auto const &node : *nodes) {
        for (auto const &transition : enfa["transitions"]) {
            if (transition["from"] == node && transition["input"] == input &&
                count(new_states.begin(), new_states.end(), transition["to"]) == 0)
                new_states.push_back(transition["to"]);
        }
    }
    *nodes = new_states;
}

/**
 *
 * @param nodes
 */
//probeert een epsilon transitie voor alle states
void ENFA::tryEps(vector<int> &nodes) {
    for (auto const &node : nodes) {
        if(std::find(triedNodes.begin(), triedNodes.end(), node) == triedNodes.end()){
            for (auto const &transition : enfa["transitions"]) {
                if (transition["from"] == node && transition["input"] == eps &&
                    count(nodes.begin(), nodes.end(), transition["to"]) == 0) {
                    nodes.push_back(transition["to"]);
                    return tryEps(nodes);
                }
            }
        }
        triedNodes.push_back(node);
    }
}

/**
 *
 * @param input
 * @return
 */
//checkt of een string accepterend is in de ENFA
bool ENFA::accepts(string input) {
    vector<int> states = {0};
    tryEps(states);
    for (auto const &c : input) {
        string character(1, c);
        nextNodes(&states, character);
        triedNodes = {};
        tryEps(states);
    }
    return (count(states.begin(), states.end(), enfa["states"].size() - 1) == 1);
}

/**
 *
 * @param elem
 * @return
 */
//telt hoeveelt transities er zijn
int ENFA::transitionCount(string elem) {
    int count = 0;
    for (auto transition : enfa["transitions"]) {
        if (transition["input"] == elem)
            count++;
    }
    return count;
}

//print de graad
int ENFA::printDegree(int degree) {
    vector<int> vec(enfa["states"].size());
    for (int i = 0; i < enfa["states"].size(); i++) {
        for (auto transition : enfa["transitions"]) {
            if (enfa["states"][i]["name"] == transition["from"] && transition["from"] != transition["to"])
                vec[i]++;
        }
    }

    return count(vec.begin(), vec.end(), degree);
}

//print alle stats
void ENFA::printStats() {
    cout << "no_of_states=" << enfa["states"].size() << endl;

    cout << "no_of_transitions[" << eps << "]=" << transitionCount(eps) << endl;

    vector<string> alph = enfa["alphabet"];
    for (auto const &elem : alph) {
        cout << "no_of_transitions[" << elem << "]=" << transitionCount(elem) << endl;
    }

    int check = 0;
    int i = 0;
    while (check < enfa["states"].size()) {
        int result = printDegree(i);
        cout << "degree[" << i << "]=" << result << endl;
        check += result;
        i++;
    }
}
/**
 *
 * @param new_state
 * @return
 */
//checkt of state een accepterende state is
bool ENFA::accept(vector<string> new_state) {
    bool accepting = false;
    for (int i = 0; i < enfa["states"].size(); i++) {
        if (enfa["states"][i]["accepting"] == true) {
            if (count(new_state.begin(), new_state.end(), enfa["states"][i]["name"]))
                accepting = true;
        }
    }
    return accepting;
}

/**
 *
 * @param new_state
 * @return
 */
//zet vector om in string
string ENFA::vecToString(vector<string> new_state) {
    if (new_state.empty())
        return "{}";

    string name = "{" + new_state[0];
    for (int i = 1; i < new_state.size(); i++) {
        name += ",";
        name += new_state[i];
    }
    name += "}";
    return name;
}

/**
 *
 * @param name
 * @param starting
 * @param accepting
 */
//voegt state toe aan het json bestand
void ENFA::addState(string name, bool starting, bool accepting) {
    dfa["states"].push_back(
            {{"name",      name},
             {"starting",  starting},
             {"accepting", accepting}});
}

/**
 *
 * @param from
 * @param to
 * @param input
 */
//voegt transitie toe aan het json bestand
void ENFA::addTransition(string from, string to, string input) {
    dfa["transitions"].push_back(
            {{"from",  from},
             {"to",    to},
             {"input", input}});
}

/**
 *
 * @param state
 * @param input
 * @return
 */
//zoek transitie
vector<string> ENFA::findTransition(vector<string> state, string input) {
    vector<string> new_state;
    for (int i = 0; i < enfa["transitions"].size(); i++) {
        if (count(state.begin(), state.end(), enfa["transitions"][i]["from"]) &&
            enfa["transitions"][i]["input"] == input) {
            new_state.push_back(enfa["transitions"][i]["to"]);
        }
    }
    return new_state;
}

/**
 *
 * @param state1
 * @return
 */
//probeert voor elke state een epsilion transitie
vector<string> ENFA::tryEpsilon(vector<string> state1) {
    vector<string> new_state = state1;

    for (auto transition : enfa["transitions"]) {
        if (count(state1.begin(), state1.end(), transition["from"]) && transition["input"] == eps)
            new_state.push_back(transition["to"]);
    }
    sort(new_state.begin(), new_state.end());
    new_state.erase(unique(new_state.begin(), new_state.end()), new_state.end());

    if (new_state == state1)
        return new_state;
    else
        return tryEpsilon(new_state);
}

/**
 *
 * @param state
 */
//vind ttransities en bijgevolg states recursief
void ENFA::subsetConstruction(vector<string> const &state) {
    vector<vector<string>> states;

    if (allStates.find(state) != allStates.end())
        return;
    allStates.insert(state);

    for (auto const &alph : dfa["alphabet"]) {
        vector<string> new_state = tryEpsilon(findTransition(state, alph));
        states.push_back(new_state);
        addTransition(vecToString(state), vecToString(new_state), alph);
    }

    for (auto const &s : states) {
        subsetConstruction(s);
    }
}

/**
 *
 * @return
 */
//zet dfa om in nfa
DFA ENFA::toDFA() {
    vector<string> startState;
    dfa = {
            {"type",     "DFA"},
            {"alphabet", enfa["alphabet"]}
    };

    for (int i = 0; i < enfa["states"].size(); i++) {
        if (enfa["states"][i]["starting"] == true) {
            startState = {enfa["states"][i]["name"]};
            startState = tryEpsilon(startState);
            dfa["states"] = {"", ""};
        }
    }
    dfa["transitions"] = {"", ""};
    subsetConstruction(startState);

    for (auto const &elem : allStates) {
        if (elem == startState)
            addState(vecToString(elem), true, accept(elem));
        else
            addState(vecToString(elem), false, accept(elem));
    }

    //verwijder de blank spaces
    dfa["states"].erase(dfa["states"].begin());
    dfa["states"].erase(dfa["states"].begin());
    dfa["transitions"].erase(dfa["transitions"].begin());
    dfa["transitions"].erase(dfa["transitions"].begin());

    ofstream file(path + ".2DFA.json");
    file << dfa;
    file.close();
    return DFA(path + ".2DFA.json");
}

ENFA ENFA::product(vector<ENFA> &enfas){
    json new_enfa = {
            {"type", "ENFA"},
            {"alphabet", {"", ""}},
            {"eps", enfas[0].eps},
            {"states", {{{"name", "start"},
                        {"starting", true},
                        {"accepting", false}},

                        {{"name", "end"},
                        {"starting", false},
                        {"accepting", true}}}},
             {"transitions", {"", ""}}
            };

    for(ENFA &e : enfas){
        for(auto &sta : e.enfa["transitions"]){
            new_enfa["transitions"].push_back({{"from", sta["from"]}, {"to", sta["to"]}, {"input", sta["input"]}});
        }
        for(auto &sta : e.enfa["alphabet"]){
            new_enfa["alphabet"].push_back(sta);
        }
        for(auto &sta : e.enfa["states"]){
            new_enfa["states"].push_back({{"name", sta["name"]}, {"starting", sta["starting"]}, {"accepting", sta["accepting"]}});
            if(sta["starting"] == true){
                new_enfa["transitions"].push_back({{"to", sta["name"]}, {"from", "start"}, {"input", e.eps}});
            }
            else if(sta["accepting"] == true){
                new_enfa["transitions"].push_back({{"to", "end"}, {"from", sta["name"]}, {"input", e.eps}});
            }
        }
    }

    for(auto &sta : new_enfa["states"]){
        if(sta["name"] != "start"){
            sta["starting"] = false;
        }
        if(sta["name"] != "end"){
            sta["accepting"] = false;
        }
    }

    new_enfa["transitions"].erase(new_enfa["transitions"].begin());
    new_enfa["transitions"].erase(new_enfa["transitions"].begin());
    new_enfa["alphabet"].erase(new_enfa["alphabet"].begin());
    new_enfa["alphabet"].erase(new_enfa["alphabet"].begin());

    ofstream file("../Output/virus"+to_string(counter)+".json");
    file << new_enfa;
    file.close();
    counter++;
    return ENFA("../Output/virus"+to_string(counter-1)+".json");
}