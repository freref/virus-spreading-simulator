
#include "RE.h"

void RE::print() {
    std::cout << expressie;
}

void RE::addToAlphabet(std::string& in) {
    for (int i = 0; i < alfabet.size(); i++) { // we gaan door het alfabet, komen we "in" tegen, dan stoppen we de hele functie, zijn we op het einde "in" nog niet tegen gekomen, dan voegen we het toe.
        if (alfabet[i] == in) {
            return;
        }
    }
    alfabet.push_back(in);
}

REnode::REnode(std::string name, int num) {
    naam = name;
    nummer = num;
    vriendje = -1;
}


RE::RE(std::string inp, std::string& epsin) {
    char c;
    std::vector<int> lhaakjes;
    eps = epsin;


    for (int i = 0; i <= inp.size(); i++) {
        c= inp[i];
        if (c == '(') {
            REnode nieuw("(", nodes.size());
            lhaakjes.push_back(nodes.size());
            nodes.push_back(nieuw);
        } else if (c == ')') {
            REnode nieuw(")", nodes.size());
            nieuw.vriendje = lhaakjes.back();
            nodes[lhaakjes.back()].vriendje = nodes.size();
            lhaakjes.pop_back();
            nodes.push_back(nieuw);
        } else if (c == '+') {
                REnode nieuw("+", nodes.size());
            nodes.push_back(nieuw);
        } else if (c == '*') {
            REnode nieuw("*", nodes.size());
            nodes.push_back(nieuw);
        } else { // gewoon karakter
            std::string naam;

            while (inp[i] != '(' and inp[i] != ')' and inp[i] != '+' and inp[i] != '*') {
                naam += c;
                i++;
            }
            if (naam != eps) {
                addToAlphabet(naam);
            }
            i--;
            REnode nieuw(naam, nodes.size());

            nodes.push_back(nieuw);
        }
    }

}


