//
// Created by frehml on 29/06/2021.
//

#include "Virus.h"

Virus::Virus(std::string path){
    ifstream input(path);
    input >> info;
}

void Virus::reload(json j) {
    info = j;
}

void Virus::correctness() {
    std::cout << "Correctheid van het virus aan het controleren..." << std::endl;
    for (json::iterator it = info.begin(); it != info.end(); ++it){
        Correctness::correctVirus(it);
    }
}

string Virus::calculateName() {
    vector<string> alphabet = {"a","b","c","d","e","f",
                               "g","h","i","j","k","l","m","n","o","p",
                               "q","r","s","t","u","v","w","x","y","z"};
    vector<string> ALPHABET = {
            "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M",
            "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};
    string r = virus_dfa.toRE().regex;
    string n = "";

    for(auto &alph : virus_enfa.enfa["alphabet"]){
        r += alph;
    }

    for(int idx = 0; idx < r.size(); idx++){
        char c = r[idx];
        if(c == '+'){
            n += ALPHABET[idx];
        }
        else if (c == '*'){
            n += "-"+to_string(idx);
        }
        else if (c == '('){
            n += "FrE";
        }
        else if (c == ')'){
            n += "BeR";
        }
        else if (c == '.'){
            n += "-";
        }
        else if (std::count(alphabet.begin(), alphabet.end(), string(1, c)) ||
        std::count(ALPHABET.begin(), ALPHABET.end(), string(1, c))){
            n += string(1, c);
        }
        else if (c != '0'){
            int i = c - '0';
            n += alphabet[i];
        }
    }
    return n;
}

void Virus::makeVirus(int counter) {
    makeProperties();

    vector<ENFA> p;
    for(auto &property : properties){
        p.push_back(property.second);
    }

    virus_enfa = p[0].product(p, counter);
    virus_dfa = virus_enfa.toDFA();
    name = calculateName();
}

void Virus::makeProperties() {
    for (json::iterator it = info.begin(); it != info.end(); ++it){
        makeProperty(it);
    }
}

void Virus::makeProperty(json::iterator it) {
    std::string name = "../Output/Virus/"+it.key()+".json";
    std::string title = it.key();

    if(integersKeyENFA.accepts(it.key()) || percentageKeyENFA.accepts(it.key())){
        percentageNFA(it, name, title);
    }
    else if(questionKeyENFA.accepts(it.key())){
        string b =  "../Output/Virus/besmettelijk.json";
        booleanNFA(it,b, title);
        percentageNFA(it, name, title);
    }
    else if (rangeKeyENFA.accepts(it.key())){
        rangeNFA(it, name, title);
    }
    properties[title] = ENFA(name);
}


void Virus::rangeNFA(json::iterator &it, std::string &name, std::string &title){
    double c1 = it.value()[0].get<double>();
    double c2 = it.value()[1].get<double>();

    json n;
    n["type"] = "ENFA";
    n["eps"] = "Q";
    n["alphabet"] = {to_string(c1), to_string(c2)};
    n["states"] = {{{"name", "0"}, {"starting", true}, {"accepting", false}},
                   {{"name", "1"}, {"starting", false}, {"accepting", false}},
                   {{"name", "2"}, {"starting", false}, {"accepting", true}}};
    n["transitions"] = {{{"from", "0"}, {"to", "1"}, {"input", to_string(c1)}},
                        {{"from", "1"}, {"to", "2"}, {"input", to_string(c2)}}};

    std::ofstream o(name);
    o << std::setw(4) << n << std::endl;
}


void Virus::booleanNFA(json::iterator &it, std::string &name, std::string &title) {
    int integer = it.value().get<int>();

    json n;
    n["type"] = "ENFA";
    n["eps"] = "Q";

    if(integer == 1) {
        n["alphabet"] = {"A", "Z", "H", "I"};
        n["states"] = {{{"name", 0}, {"starting", true},  {"accepting", false}},
                       {{"name", 1}, {"starting", false}, {"accepting", true}}};
        n["transitions"] = {{{"from", 0}, {"to", 1}, {"input", "A"}},
                            {{"from", 0}, {"to", 1}, {"input", "H"}},
                            {{"from", 0}, {"to", 1}, {"input", "Z"}},
                            {{"from", 0}, {"to", 1}, {"input", "I"}}};
    }
    else {
        n["alphabet"] = {"A", "Z", "H", "I"};
        n["states"] = {{{"name", 0}, {"starting", true}, {"accepting", false}},
                       {{"name", 1}, {"starting", false}, {"accepting", true}}};
        n["transitions"] = {{{"from", 0}, {"to", 1}, {"input", "H"}},
                            {{"from", 0}, {"to", 1}, {"input", "Z"}}};
    }

    std::ofstream o(name);
    o << std::setw(4) << n << std::endl;
}


void Virus::percentageNFA(json::iterator &it, std::string &name, std::string &title) {
    double c1 = it.value().get<double>();

    json n;
    n["type"] = "ENFA";
    n["eps"] = "Q";
    n["alphabet"] = {to_string(c1)};
    n["states"] = {{{"name", "0"}, {"starting", true}, {"accepting", false}},
                   {{"name", "1"}, {"starting", false}, {"accepting", true}}};
    n["transitions"] = {{{"from", "0"}, {"to", "1"}, {"input", to_string(c1)}}};

    std::ofstream o(name);
    o << std::setw(4) << n << std::endl;
}