# CMakeList.txt: Projekt CMake pro Elektronicky diar, sem přidejte logiku zdrojového
# kódu a definic specifickou pro projekt.
#
cmake_minimum_required (VERSION 3.8)

project ("Elektronicky diar")

# Přidejte zdrojový kód ke spustitelnému souboru tohoto projektu.
add_executable (CMakeTarget "el_diar_main.cpp" "el_diar.h" "el_diar.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CMakeTarget PROPERTY CXX_STANDARD 20)
endif()

# TODO: V případě potřeby přidejte testy a cíle instalace.
