#include <fstream>
#include <iostream>
#include <stdio.h>

void genGraphFile(int nodes, float probability, std::string fileName)
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

int main()
{
    int nodes = 2000;
    int fileNameIncrement = 1;
    std::string tempFileName;

    for(float i = 0.0001; i <= 0.005; i+=0.0001)
    {
        tempFileName = "random" + std::to_string(fileNameIncrement) + ".txt";

        genGraphFile(nodes, i, tempFileName);

        fileNameIncrement++;
    }

    return 0;
}
