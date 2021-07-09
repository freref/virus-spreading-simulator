#include <string>



#ifndef CLION_RE_H
#define CLION_RE_H

#include <vector>
#include "ENFA.h"

class REnode {
public:
    std::string naam;
    REnode(std::string& name);

};

class RE {
public:
    std::string eps;
    std::vector<REnode> startnodes;
    std::vector<REnode> eindnodes;
    std::vector<std::string> alfabet;
    std::string expressie;
    std::vector<REnode> nodes;

    void addToAlphabet(std::string& in);

    RE(std::string);
    void print();
    ENFA toENFA();
    bool accepts();


};

#endif //CLION_RE_H
