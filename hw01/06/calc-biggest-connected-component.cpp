#include <vector>
#include <fstream>
#include <iostream>
#include <list>
#include <stdio.h>

// Graph class represents a undirected graph
// using adjacency list representation
class Graph
{
    // number of vertices
    int V;

    // pointer to an array containing adjacency lists
    std::list<int> *adj;

    // DFS algorithm function
    void DFSUtil(int v, bool visited[], std::vector<int> &tempVector);

    std::vector<std::vector<int>> connectedComponents;

private:
    void exportTotalConnectedComponents(float xValue, std::string exportFileName);

public:
    Graph(int V);
    ~Graph();
    void addEdge(int v, int w);
    void getConnectedComponents(float xValue, std::string exportFileName);
    int biggestConnectedComponentSize();
};

// method to add an undirected edge to the graph
void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w);
    adj[w].push_back(v);
}

// DFS algorithm function to recursively visit all the nodes once
void Graph::DFSUtil(int v, bool visited[], std::vector<int> &tempVector)
{
    // mark the current node as visited and add it to the vector
    visited[v] = true;
    tempVector.push_back(v);

    // check all the vertices adjacent to this vertex
    std::list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
    {
        if (!visited[*i])
        {
            DFSUtil(*i, visited, tempVector);
        }
    }
}

// method to get the connected components in the undirected graph,
// print all components, or print total number of elements of the biggest (default)
void Graph::getConnectedComponents(float xValue, std::string exportFileName)
{
    connectedComponents.clear();
    std::vector<int> tempVector;

    // mark all vertices as not visited
    bool *visited = new bool[V];
    for (int v = 0; v < V; v++)
    {
        visited[v] = false;
    }

    for (int v = 0; v < V; v++)
    {
        if (visited[v] == false)
        {
            tempVector.clear();
            // check all reachable vertices from v
            DFSUtil(v, visited, tempVector);
            connectedComponents.push_back(tempVector);
        }
    }

    exportTotalConnectedComponents(xValue, exportFileName);

    delete[] visited;
}

// print the total number of elements of the biggest connected component into the console
void Graph::exportTotalConnectedComponents(float xValue, std::string exportFileName)
{
    int totalConnectedComponents = 0;
    int totalConnectedComponentsTemp = 0;

    for (int i = 0; i < connectedComponents.size(); i++)
    {
        for (int j = 0; j < connectedComponents[i].size(); j++)
        {
            totalConnectedComponentsTemp++;
        }

        if (totalConnectedComponentsTemp > totalConnectedComponents)
        {
            totalConnectedComponents = totalConnectedComponentsTemp;
        }

        totalConnectedComponentsTemp = 0;
    }

    std::ofstream dataFile;
    dataFile.open(exportFileName, std::ios::out | std::ios::app);

    dataFile << xValue << " " << totalConnectedComponents << std::endl;

    dataFile.close();
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

int main()
{
    // the import file name (random1.txt, random2.txt...)
    std::string fileName;

    // the exprt file with the data to plot
    std::string exportFileName = "data.dat";

    int fileNameIncrement = 1;

    for(float i = 0.0001; i <= 0.005; i+=0.0001)
    {
        fileName = "random" + std::to_string(fileNameIncrement) + ".txt";
        fileNameIncrement++;

        // create the graph
        Graph g(getVerticesNumber(fileName));

        // add edges to the graph
        addEdges(g, fileName);

        // print the biggest connected component
        g.getConnectedComponents(i, exportFileName);
    }

    return 0;
}
