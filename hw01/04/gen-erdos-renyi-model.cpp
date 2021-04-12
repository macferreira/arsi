#include <fstream>
#include <iostream>
#include <stdio.h>

int nodes;
float probability;
std::string fileName;

void genGraphFile()
{
    std::ofstream graphFile;
    graphFile.open(fileName);

    graphFile << nodes << std::endl;

    for (int i = 0; i < nodes; i++)
    {
        for (int j = i; j < nodes; j++)
        {
            // generate a random float between 0 and 1 and compare it against the probability
            if (float(rand()) / (float(RAND_MAX) + 1.0) <= probability) {
                graphFile << i << " " << j << std::endl;
            }
        }           
    }

    graphFile.close();
}

int main(int argc, char *argv[])
{
    // arguments: #1 is n number of nodes, #2 is p probability of node connection, #3 is the name of the file to be generated.
    if (argc == 4)
    {
        nodes = std::atoi(argv[1]);
        probability = std::atof(argv[2]);
        fileName = argv[3];
    }
    else
    {
        std::cout << "Usage: " << argv[0] << " <number of nodes> <probability> <file name>" << std::endl;
    }

    genGraphFile();

    return 0;
}
