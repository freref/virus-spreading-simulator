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
}

void Virus::makeProperties() {
    for (json::iterator it = info.begin(); it != info.end(); ++it){
        makeProperty(it);
    }
}

void Virus::makeProperty(json::iterator it) {
    std::string name = "Virus/"+it.key()+".json";
    std::string title = it.key();

    if(percentageKey.toENFA().accepts(it.key()) || questionKey.toENFA().accepts(it.key())){
        percentageNFA(it, name, title);
    }
    else if (integersKey.toENFA().accepts(it.key())){
        integerNFA(it, name, title);
    }
    else if (rangeKey.toENFA().accepts(it.key())){
        rangeNFA(it, name, title);
    }
}


void Virus::rangeNFA(json::iterator &it, std::string &name, std::string &title){
    double c1 = it.value()[0].get<double>();
    double c2 = it.value()[1].get<double>();

    json n;
    n["type"] = "NFA";
    n["alphabet"] = {to_string(c1), to_string(c2)};
    n["states"] = {{{"name", "a"}, {"starting", true}, {"accepting", false}},
                   {{"name", "b"}, {"starting", false}, {"accepting", false}},
                   {{"name", "c"}, {"starting", false}, {"accepting", true}}};
    n["transitions"] = {{{"from", "a"}, {"to", "b"}, {"input", to_string(c1)}},
                        {{"from", "b"}, {"to", "c"}, {"input", to_string(c2)}}};

    std::ofstream o(name);
    o << std::setw(4) << n << std::endl;
    properties[title] = NFA(name);
}


void Virus::integerNFA(json::iterator &it, std::string &name, std::string &title) {
    double integer = it.value().get<double>();

    json n;
    n["type"] = "NFA";
    n["alphabet"] = {to_string(integer)};
    n["states"] = {{{"name", "a"}, {"starting", true}, {"accepting", false}},
                   {{"name", "b"}, {"starting", false}, {"accepting", true}}};
    n["transitions"] = {{{"from", "a"}, {"to", "b"}, {"input", to_string(integer)}}};

    std::ofstream o(name);
    o << std::setw(4) << n << std::endl;
    properties[title] = NFA(name);
}


void Virus::percentageNFA(json::iterator &it, std::string &name, std::string &title) {
    double c1 = it.value().get<double>();
    double c2 = 1.0-c1;

    json n;
    n["type"] = "NFA";
    n["alphabet"] = {to_string(c1), to_string(c2)};
    n["states"] = {{{"name", "a"}, {"starting", true}, {"accepting", false}},
                   {{"name", "b"}, {"starting", false}, {"accepting", true}},
                   {{"name", "c"}, {"starting", false}, {"accepting", false}}};
    n["transitions"] = {{{"from", "a"}, {"to", "b"}, {"input", to_string(c1)}},
                        {{"from", "a"}, {"to", "c"}, {"input", to_string(c2)}}};

    std::ofstream o(name);
    o << std::setw(4) << n << std::endl;
    properties[title] = NFA(name);
}

std::string Virus::giveName() {
    return std::string();
}

Virus::Virus() {

}

void Virus::muteer() {

}
