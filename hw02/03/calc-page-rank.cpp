#include <vector>
#include <fstream>
#include <iostream>
#include <list>
#include <numeric>
#include <stdio.h>

// Graph class represents a undirected graph
// using adjacency list representation
class Graph
{
    // number of vertices
    int V;

    // pointer to an array containing adjacency lists
    std::list<int> *adj;

    // vector to hold the page rank values of the nodes
    std::vector<double> pageRank;

private:
    void pageRankAlgorithm(float dumpingFactor);
    void printPageRank(std::string label);

public:
    Graph(int V);
    ~Graph();
    void addEdge(int v, int w);
    void calcPageRank(int iterations, float dumpingFactor);
};

Graph::Graph(int V)
{
    this->V = V;
    adj = new std::list<int>[V];

    // fill the page ranks with an initial value of 1/n
    for (int i = 0; i < V; i++)
        pageRank.push_back(1.0/V);
}

Graph::~Graph()
{
    delete[] adj;
}

// method to add a directed edge to the graph
void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w);
}

// method to calc the page rank of the nodes
void Graph::calcPageRank(int iterations, float dumpingFactor = 0.85)
{
    for (int it = 0; it < iterations; it++)
    {
        pageRankAlgorithm(dumpingFactor);
        printPageRank(std::to_string(it));
    }
 
}

void Graph::pageRankAlgorithm(float dumpingFactor)
{
    std::list<int>::iterator i;
    double tmpPageRankSum;

    for (int v = 0; v < V; v++)
    {
        tmpPageRankSum = 0.0;
        
        for (i = adj[v].begin(); i != adj[v].end(); ++i)
        {
            tmpPageRankSum += pageRank[*i]/adj[*i].size();
        }

        tmpPageRankSum = dumpingFactor*tmpPageRankSum + (1-dumpingFactor)/V;

        pageRank[v] = tmpPageRankSum;
    }
}

void Graph::printPageRank(std::string label)
{
    std::cout << label + ":" << std::endl;

    for (int i = 0; i < pageRank.size(); i++)
    {
        std::cout << i << " = " << pageRank[i] << std::endl;
    }
}

// get the total number of vertices in the input file (first line)
int getVerticesNumber(std::string fileName)
{
    std::string line;
    std::ifstream graphFile(fileName);

    if (graphFile.is_open())
    {
        getline(graphFile, line);
    }

    graphFile.close();

    return std::stoi(line);
}

// split the edges of the text file (input is string separated by white space)
std::vector<int> splitEdgeValues(std::string str)
{
    std::vector<int> edgesPair;
    std::string word = "";
    for (auto x : str)
    {
        if (x == ' ')
        {
            edgesPair.push_back(std::stoi(word));
            word = "";
        }
        else
        {
            word = word + x;
        }
    }
    edgesPair.push_back(std::stoi(word));

    return edgesPair;
}

// add edges from the input file to the graph
void addEdges(Graph &g, std::string fileName)
{
    std::string line;
    std::vector<int> edgesPairVector;
    std::ifstream graphFile(fileName);

    // Read and throw away the first line as it is the number of vertices
    getline(graphFile, line);

    while (!graphFile.eof())
    {
        getline(graphFile, line);

        if (line != "")
        {
            edgesPairVector = splitEdgeValues(line);
            g.addEdge(edgesPairVector[0], edgesPairVector[1]);
        }
    }
}

int main(int argc, char *argv[])
{
    std::string fileName;
    int iterations;
    float dumpingFactor;

    // arguments: #1 is the file with the graph data (e.g. random1.txt), #2 is number of iterations wanted
    if (argc == 4)
    {
        fileName = argv[1];
        iterations = atoi(argv[2]);
        dumpingFactor = atof(argv[3]);
    }
    else
    {
        std::cout << "Usage: " << argv[0] << " <file name> <iterations> <dumping factor>" << std::endl;
    }

    // create the graph
    Graph g(getVerticesNumber(fileName));

    // add edges to the graph
    addEdges(g, fileName);

    // calulate the graph page rank
    g.calcPageRank(iterations, dumpingFactor);

    return 0;
}
