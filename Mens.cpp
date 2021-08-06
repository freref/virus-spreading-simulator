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

string Mens::print() {
    string output;
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

    output+= "=====================================\n";

    if(name.size() >= 7)
        output += "   naam: " + name + "\t\t\t\t\n";
    else
        output += "   naam: " + name + "\t\t\t\t\t\n" ;

    output += "   leeftijd: " + to_string(age) + "\t\t\t\t\t\n";
    if(toestand != "H")
        output += "   toestand: " + t + "\t\t\t\t\n";
    else
        output += "   toestand: " + t + "\t\t\t\n";

    output += "--------------------------------------------------------------\n   aantal keer geinfecteerd: " +
            to_string(infectie) + "\t\t\t  \n   gezondheidsgraad: " +
            to_string(gezondheidsgraad) + "\t\t\t  \n   duur tot genezing: " +
            to_string(recovery) + "\t\t\t\t  \n   incubatie duur: " +
            to_string(incubatie) + "\t\t\t\t  \n   tijd van infectie: " +
            to_string(it) + "\t\t\t\t\n=====================================\n";

    return output;
}