#include <iostream>
#include "json.hpp"
#include "Virus.h"
#include "World.h"
#include "Statistiek.h"
#include "Simulatie.h"
#include <QApplication>
#include "Window.h"
#include <QLabel>

using json = nlohmann::json;

//GUI gebaseerd op schaakspel

int main(int argc, char *argv[]) {
    std::string virus = "Virus/virus1.json";
    std::string world = "World/world1.json";

    Virus v(virus);
    v.correctness();
    v.makeVirus(0);

    World w(world);
    w.correctness();
    w.makeWorld();

    Simulatie sim(v, w);

    QApplication a(argc, argv);
    Window wn(new QWidget, sim);
    wn.show();
    return a.exec();
}
