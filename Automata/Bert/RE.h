#include <string>


#ifndef CLION_RE_H
#define CLION_RE_H



class RE {
public:
    std::string expressie;
    char eps;
    RE(std::string a, std::string b) {
        expressie = a;
        eps = b[0];
    }

};

#endif //CLION_RE_H
