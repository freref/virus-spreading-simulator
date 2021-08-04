//
// Created by twijg on 7/6/21.
//

#include "Mens.h"

Mens::Mens(double gg, double down, double right) {
    gezondheidsgraad = gg;
    downDistance =  (int)round(down);
    rightDistance =  (int)round(right);

    //https://www.codespeedy.com/fetch-a-random-line-from-a-text-file-in-cpp/
    string line;
    vector<string> lines;
    //input file stream
    ifstream file("World/names.txt");
    //count number of total lines in the file and store the lines in the string vector
    int total_lines=0;
    while(getline(file,line))
    {
        total_lines++;
        lines.push_back(line);
    }
    //generate a random number between 0 and count of total lines
    int random_number=generator()%total_lines;
    //fetch the line where line index (starting from 0) matches with the random number
    name = lines[random_number];
    age = generator()%122;
}

Mens* Mens::generateHuman(double gg, double d) {
    std::normal_distribution<double> gezondheid (gg,1.0);
    std::normal_distribution<double> up (d,d);
    std::normal_distribution<double> right (d,d);

    Mens* m = new Mens(fabs(gezondheid(generator)), fabs(up(generator)), fabs(right(generator)));
    return m;
}

void Mens::calculateValues(Virus &v) {
    string i_string = (v.properties["incubatietijdN"].enfa["alphabet"][0]);
    double i = stod(i_string);
    string r_string = (v.properties["recoveryN"].enfa["alphabet"][0]);
    double r = stod(i_string);

    std::normal_distribution<double> r_r (r,1);
    std::normal_distribution<double> i_r (i,1);

    recovery = (int)round(fabs(r_r(generator)));
    incubatie = (int)round(fabs(i_r(generator)));
}

void Mens::print() {
    string t;
    if(toestand == "G"){
        t = "Gezond";
    }
    else if(toestand == "A"){
        t = "Asymptomatisch";
    }
    else if(toestand == "X"){
        t = "Dood";
    }
    else if(toestand == "Z"){
        t = "Ziek";
    }
    else if(toestand == "H"){
        t = "Gehospitaliseerd";
    }
    else if(toestand == "I"){
        t = "Incuberend";
    }

    std::cout   << "==================================================" << std::endl;

    if(name.size() >= 7)
        std::cout << "|| naam: " << name << "\t\t\t\t||" << std::endl;
    else
        std::cout << "|| naam: " << name << "\t\t\t\t\t||" << std::endl;

    std::cout << "|| leeftijd: " << age << "\t\t\t\t\t||" << std::endl;
    if(toestand != "H")
        std::cout << "|| toestand: " << t << "\t\t\t\t||" << std::endl;
    else
        std::cout << "|| toestand: " << t << "\t\t\t||" << std::endl;

    std::cout<< "--------------------------------------------------" << std::endl
    << "|| aantal keer geinfecteerd: " << infectie << "\t\t\t||" << std::endl
    << "|| gezondheidsgraad: " << gezondheidsgraad << "\t\t\t||" << std::endl
    << "|| duur tot genezing: " << recovery << "\t\t\t\t||" << std::endl
    << "|| incubatie duur: " << incubatie << "\t\t\t\t||" << std::endl
    << "|| tijd van infectie: " << it << "\t\t\t\t||" << std::endl
    << "==================================================" << std::endl;
}