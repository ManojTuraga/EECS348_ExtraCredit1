#include <fstream>
#include <iostream>
#include <string>
#include "Preference.h"

int main(int argc, char *argv[])
{
    if (argc < 4)
    {
        std::cout << "Not enough command line arguments\n";
    }
    else
    {
        ProgrammerSorter program(argv[1], atoi(argv[2]), atoi(argv[3]));
        program.sort();
    }

    return 0;
}