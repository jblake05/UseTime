# Instructions

Top level build, installs CPM, JUCE, sets up build and lib folders that are excluded with .gitignore: cmake -S . -B build

Plugin build: cmake --build build

Test: cd build | ctest
