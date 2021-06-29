#include <iostream>
#include "json.hpp"
#include "Virus.h"
#include "World.h"

using json = nlohmann::json;

int main() {
    std::string virus = "../Input/Virus/virus1.json";
    std::string world = "../Input/World/world1.json";

    Virus v(virus);
    World w(world);
    return 0;
}
