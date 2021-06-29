cmake_minimum_required(VERSION 3.17)
project(VSS)

set(CMAKE_CXX_STANDARD 14)

add_executable(VSS main.cpp
        #Automata/Frederic/DFA.cpp Automata/Frederic/DFA.h
        #Automata/Frederic/ENFA.cpp Automata/Frederic/ENFA.h
        #Automata/Frederic/NFA.cpp Automata/Frederic/NFA.h
        #Automata/Frederic/RE.cpp Automata/Frederic/RE.h
        Automata/Working/DFA.cpp Automata/Working/DFA.h
        Automata/Working/ENFA.cpp Automata/Working/ENFA.h
        Automata/Working/NFA.cpp Automata/Working/NFA.h
        Automata/Working/RE.cpp Automata/Working/RE.h
        Automata/Working/FA.cpp Automata/Working/FA.h
        json.hpp Virus.cpp Virus.h Correctness.cpp Correctness.h World.cpp World.h)