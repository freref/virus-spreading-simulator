cmake_minimum_required(VERSION 3.6)
project(VSS)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)

set(CMAKE_CXX_STANDARD 11)

#add_compile_options(-Wall)

set(Qt5Core_DIR "C:\\Qt\\5.9.3\\mingw53_32\\lib\\cmake\\Qt5Core")
set(Qt5Widgets_DIR "C:\\Qt\\5.9.3\\mingw53_32\\lib\\cmake\\Qt5Widgets")
set(Qt5Gui_DIR "C:\\Qt\\5.9.3\\mingw53_32\\lib\\cmake\\Qt5Gui")

find_package( Qt5Core REQUIRED )
find_package( Qt5Widgets REQUIRED )
find_package( Qt5Gui REQUIRED )

add_executable(VSS main.cpp
        Automata/Frederic/DFA.cpp Automata/Frederic/DFA.h
        Automata/Frederic/ENFA.cpp Automata/Frederic/ENFA.h
        Automata/Frederic/NFA.cpp Automata/Frederic/NFA.h
        Automata/Frederic/RE.cpp Automata/Frederic/RE.h
        json.hpp Virus.cpp Virus.h Correctness.cpp
        Correctness.h World.cpp World.h Statistiek.cpp
        Statistiek.h Mens.cpp Mens.h Simulatie.cpp Simulatie.h
        Tools.h Window.cpp Window.h UI.cpp UI.h)

qt5_use_modules(VSS Core Widgets Gui)
