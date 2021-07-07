//
// Created by frehml on 29/06/2021.
//

#include "Virus.h"

Virus::Virus(std::string path){
    ifstream input(path);
    input >> info;
}

void Virus::correctness() {
    for (json::iterator it = info.begin(); it != info.end(); ++it){
        Correctness::correctVirus(it);
    }
}

void Virus::makeVirus() {
    makeProperties();

    DFA a = NFA("Virus/mutatie%.json").toDFA();
    DFA b = NFA("Virus/mutatie%.json").toDFA();
    DFA ab(a, b, true);

    //DFA d = NFA("Virus/incubatietijdN.json").toDFA();
    //DFA e = NFA("Virus/mutatie%.json").toDFA();
    //DFA f = NFA("Virus/mutatieR.json").toDFA();
    //DFA g = NFA("Virus/sterftegraad%.json").toDFA();
    //DFA h = NFA("Virus/ziekte%.json").toDFA();


    //DFA abc(ab, c, true);
    //DFA abcd(abc, d, true);
    //DFA abcde(abcd, e, true);
    //DFA abcdef(abcde, f, true);
    //DFA abcdefg(abcdef, g, true);
    //DFA abcdefh(abcdefg, h, true);

    //std::ofstream o("lol");
    //o << std::setw(4) << n << std::endl;
}

void Virus::makeProperties() {
    for (json::iterator it = info.begin(); it != info.end(); ++it){
        makeProperty(it);
    }
}

void Virus::makeProperty(json::iterator it) {
    std::string name = "Virus/"+it.key()+".json";

    if(percentageKey.toENFA().accepts(it.key()) || questionKey.toENFA().accepts(it.key())){
        percentageNFA(it, name);
    }
    else if (integersKey.toENFA().accepts(it.key())){
        integerNFA(it, name);
    }
    else if (rangeKey.toENFA().accepts(it.key())){
        rangeNFA(it, name);
    }
}


void Virus::rangeNFA(json::iterator &it, std::string &name){
    double c1 = it.value()[0].get<double>();
    double c2 = it.value()[1].get<double>();

    json n;
    n["type"] = "NFA";
    n["alphabet"] = {c1, c2};
    n["states"] = {{{"name", "a"}, {"starting", true}, {"accepting", false}},
                   {{"name", "b"}, {"starting", false}, {"accepting", false}},
                   {{"name", "c"}, {"starting", false}, {"accepting", true}}};
    n["transitions"] = {{{"from", "a"}, {"to", "b"}, {"input", c1}},
                        {{"from", "b"}, {"to", "c"}, {"input", c2}}};

    std::ofstream o(name);
    o << std::setw(4) << n << std::endl;
}


void Virus::integerNFA(json::iterator &it, std::string &name) {
    double integer = it.value().get<double>();

    json n;
    n["type"] = "NFA";
    n["alphabet"] = {integer};
    n["states"] = {{{"name", "a"}, {"starting", true}, {"accepting", false}},
                   {{"name", "b"}, {"starting", false}, {"accepting", true}}};
    n["transitions"] = {{{"from", "a"}, {"to", "b"}, {"input", integer}}};

    std::ofstream o(name);
    o << std::setw(4) << n << std::endl;
}


void Virus::percentageNFA(json::iterator &it, std::string &name) {
    double c1 = it.value().get<double>();
    double c2 = 1.0-c1;

    json n;
    n["type"] = "NFA";
    n["alphabet"] = {c1, c2};
    n["states"] = {{{"name", "a"}, {"starting", true}, {"accepting", false}},
                   {{"name", "b"}, {"starting", false}, {"accepting", true}},
                   {{"name", "c"}, {"starting", false}, {"accepting", false}}};
    n["transitions"] = {{{"from", "a"}, {"to", "b"}, {"input", c1}},
                        {{"from", "a"}, {"to", "c"}, {"input", c2}}};

    std::ofstream o(name);
    o << std::setw(4) << n << std::endl;
}

std::string Virus::giveName() {

    return std::string();
}

Virus::Virus() {

}
