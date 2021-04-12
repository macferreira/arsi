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
    void printConnectedComponents();
    void printTotalConnectedComponents();

public:
    Graph(int V);
    ~Graph();
    void addEdge(int v, int w);
    void getConnectedComponents(bool printAll, bool printTotal);
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
void Graph::getConnectedComponents(bool printAll = false, bool printTotal = true)
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

    if (printAll)
    {
        printConnectedComponents();
    }

    if (printTotal)
    {
        printTotalConnectedComponents();
    }

    delete[] visited;
}

// print all the connected components to the console
void Graph::printConnectedComponents()
{
    std::cout << "Following are connected components:" << std::endl;

    for (int i = 0; i < connectedComponents.size(); i++)
    {
        for (int j = 0; j < connectedComponents[i].size(); j++)
        {
            std::cout << connectedComponents[i][j];
            if (j + 1 != connectedComponents[i].size())
            {
                std::cout << ", ";
            }
        }
        std::cout << std::endl;
    }

    std::cout << "Number of Components: " << connectedComponents.size() << std::endl;
}

// print the total number of elements of the biggest connected component into the console
void Graph::printTotalConnectedComponents()
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

    std::cout << totalConnectedComponents << std::endl;
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
    std::string fileName;

    // arguments: #1 is the file with the graph data (e.g. random1.txt)
    if (argc == 2)
    {
        fileName = argv[1];
    }
    else
    {
        std::cout << "Usage: " << argv[0] << " <file name>" << std::endl;
    }

    // create the graph
    Graph g(getVerticesNumber(fileName));

    // add edges to the graph
    addEdges(g, fileName);

    // print the biggest connected component
    g.getConnectedComponents();

    return 0;
}
