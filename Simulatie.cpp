//
// Created by twijg on 7/6/21.
//

#include "Simulatie.h"

Simulatie::Simulatie(Virus& vir, World& wereld) {
    virus = vir;
    world = wereld;
    log = Statistiek();
}

void Simulatie::muteer(){
    string m_string = (virus.properties["mutatie%"].enfa["alphabet"][0]);
    string range1 = (virus.properties["mutatieR"].enfa["alphabet"][0]);
    string range2 = (virus.properties["mutatieR"].enfa["alphabet"][1]);

    double r = (generator()*1.0) / (generator.max() * 1.0);
    double m = stod(m_string);
    vector<double> range = {stod(range1), stod(range2)};
    sort(range.begin(), range.end());

    vector<string> options = {"incubatietijdN",
                              "recoveryN",
                              "infectieN",
                              "ziekte%",
                              "asymptomatischB",
                              "mutatie%"};

    if(r < m){
        double lower_bound = range[0];
        double upper_bound = range[1];
        std::uniform_real_distribution<double> unif(lower_bound,upper_bound);
        double a_random_double = unif(generator)+1;

        json info;
        ifstream input("Virus/virus1.json");
        input >> info;

        string selected = options[generator()%options.size()];
        int bi = generator()%2;

        if(integersKeyENFA.accepts(selected)){
            int integer;

            if(bi == 0)
                integer = ceil(double(info[selected]) * a_random_double);
            else
                integer = floor(double(info[selected]) / a_random_double);

            info[selected] = integer;
        }
        else if(questionKeyENFA.accepts(selected)){
            if(info[selected].get<int>() == 1){
                info[selected] = 0;
            }
            else{
                info[selected] = 1;
            }
        }
        else if (percentageKeyENFA.accepts(selected)){
            if(bi == 0){
                info[selected] = (double(info[selected]) * a_random_double);
            }
            else{
                info[selected] = (double(info[selected]) / a_random_double);
            }
        }

        if(info[selected] <= 0 && !questionKeyENFA.accepts(selected))
            info[selected] = 0.01;

        ofstream output("Virus/virus1.json");
        output << info;
        virus.reload(info);
        virus.makeVirus(counter);
        counter++;
        confirmMutation();
    }
}

bool Simulatie::confirmMutation() {
    if(counter == 1)
        return false;

    DFA a = DFA("../Output/virus"+to_string(counter-1)+".json").minimize();
    DFA b = DFA("../Output/virus"+to_string(counter-2)+".json").minimize();

    return (!(a==b));
}

void Simulatie::infect(int x, int y) {
    Mens* m = world.grid[x][y];
    string i_string = (virus.properties["infectieN"].enfa["alphabet"][0]);
    double i = stod(i_string);

    if(m->infectie < i && m->toestand == "G"){
        muteer();
        m->toestand = "I";
        m->it = it;
        m->infectie++;
        m->calculateValues(virus);
    }
}

void Simulatie::spread(Mens* human){
    if(ENFA("../Output/Virus/besmettelijk.json").accepts(human->toestand)){
        if(it - human->it >= human->leftDistance){
            infect(human->n.left.first, human->n.left.second);
        }
        if(it - human->it >= human->rightDistance){
            infect(human->n.right.first, human->n.right.second);
        }
        if(it - human->it >= human->upDistance){
            infect(human->n.up.first, human->n.up.second);
        }
        if(it - human->it >= human->downDistance){
            infect(human->n.down.first, human->n.down.second);
        }
    }
}

void Simulatie::simulate(int n){
    for(int i = 0; i < n; i++){
        for(auto &row : world.grid){
            for(auto &human : row){
                if(human->toestand != "G" && human->toestand != "X"){
                    if(it - human->it == human->incubatie + human->recovery){
                        human->toestand = "G";
                    }
                    if(it - human->it == human->incubatie){
                        breakout(human);
                    }
                    spread(human);
                }
            }
        }
        it++;
    }
}

void Simulatie::breakout(Mens *m) {
    string z_string = (virus.properties["ziekte%"].enfa["alphabet"][0]);
    double z = stod(z_string);
    double sickness = m->gezondheidsgraad*z;

    if(sickness < world.agrens){
        m->toestand = "A";
    }
    else if (sickness < world.zgrens){
        m->toestand = "Z";
    }
    else if (sickness < world.hgrens){
        m->toestand = "H";
    }
    else{
        m->toestand = "X";
    }
}