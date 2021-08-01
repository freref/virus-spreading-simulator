//
// Created by frehml on 29/06/2021.
//

#ifndef VSS_WORLD_H
#define VSS_WORLD_H

#include "json.hpp"
#include "Mens.h"
#include "Correctness.h"
#include <fstream>
#include <ostream>

//the following are UBUNTU/LINUX, and MacOS ONLY terminal color codes.
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

using json = nlohmann::json;

class World {
public:
    int populatie;
    int bevolkingsdichtheid;
    double gezondheidsgraad;
    double agrens;
    double zgrens;
    double hgrens;

    json info;
    vector<vector<Mens*>> grid;

    World(){};
    World(std::string path);
    ~World();

    void correctness();
    void makeWorld();
    void populateProperties();
    void populateGrid();
    void print();
};


#endif //VSS_WORLD_H
