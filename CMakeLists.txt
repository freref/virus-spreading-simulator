cmake_minimum_required(VERSION 3.17)
project(VSS)

set(CMAKE_CXX_STANDARD 14)

add_executable(VSS main.cpp
        Automata/Frederic/DFA.cpp Automata/Frederic/DFA.h
        Automata/Frederic/ENFA.cpp Automata/Frederic/ENFA.h
        Automata/Frederic/NFA.cpp Automata/Frederic/NFA.h
        Automata/Frederic/RE.cpp Automata/Frederic/RE.h
        Automata/Frederic/json.hpp
        json.hpp)