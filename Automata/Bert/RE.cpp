
#include "RE.h"

void RE::print() {
    std::cout << expressie;
}

void RE::addToAlphabet(std::string& in) {

}

REnode::REnode(std::string& name) {
    naam = name;
}

RE::RE(std::string inp) {
    char c;
    for (int i = 0; i <= inp.size(); i++) {
        c= inp[i];
        if (c == '(') {
            int haakjescounter = 1;
            std::string subexp;
            int j = 1;
            while (haakjescounter != 0) {
                if (inp[i+j] == '(') {
                    haakjescounter ++;
                    subexp += inp[i+j];
                } else if (inp[i+j] == ')') {
                    haakjescounter --;
                    if (haakjescounter != 0) {
                        subexp += inp[i+j];
                    }
                }
            }


        } else if (c == '+') {

        } else if (c == '*') {

        } else { // gewoon karakter
            std::string naam;


            while (inp[i] != '(' and inp[i] != ')' and inp[i] != '+' and inp[i] != '*') {
                naam += c;
                i++;
            }
            addToAlphabet(naam);
            i--;
            REnode nieuw(naam);

            nodes.push_back(nieuw);
        }
    }
}


