#include <fstream>
#include <iostream>
#include <list>
#include <stdio.h>
#include <vector>

// Graph class represents a undirected graph
// using adjacency list representation
class Graph
{
    // number of vertices
    int V;

    // pointer to an array containing adjacency lists
    std::list<int> *adj;

public:
    Graph(int V);
    ~Graph();
    void addEdge(int v, int w);
    void exportDegreeDistPlot(std::string fileName);
};

// method to add an undirected edge to the graph
void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w);
    adj[w].push_back(v);
}

void Graph::exportDegreeDistPlot(std::string fileName)
{
    std::ofstream graphFile;
    graphFile.open(fileName);

    int maxDegree = 0;

    for (int i = 0; i < V; i++)
    {
        if (adj[i].size() > maxDegree)
        {
            maxDegree = adj[i].size();
        }
    }

    int degreeDistribution[maxDegree + 1] = {};

    for (int i = 0; i < V; i++)
    {
        degreeDistribution[adj[i].size()]++;
    }

    for (int i = 0; i <= maxDegree; i++)
    {
        graphFile << i << " " << degreeDistribution[i] << std::endl;
    }

    graphFile.close();
}

Graph::Graph(int V)
{
    this->V = V;
    adj = new std::list<int>[V];
}

Graph::~Graph()
{
    delete[] adj;
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
    // the import file name (ba1.txt, ba2.txt...)
    std::string fileName;

    // the export file with the data to plot
    std::string exportFileName;

    // arguments: #1 is the file with the graph data (e.g. random1.txt), #2 is the export file (e.g. data1.dat)
    if (argc == 3)
    {
        fileName = argv[1];
        exportFileName = argv[2];
    }
    else
    {
        std::cout << "Usage: " << argv[0] << " <import name>"
                  << " <export file>" << std::endl;
        
        return 0;
    }

    // create the graph
    Graph g(getVerticesNumber(fileName));

    // add edges to the graph
    addEdges(g, fileName);

    g.exportDegreeDistPlot(exportFileName);

    return 0;
}
