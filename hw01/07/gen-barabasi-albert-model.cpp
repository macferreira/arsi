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

private:
    void connectInitialNodes(int numberNodes);
    void addNewNodeEdgesUntilN(int m0, int m);

public:
    Graph(int V, int m0, int m);
    ~Graph();
    void addEdge(int v, int w);
    void exportGraph(std::string fileName);
};

// method to add an undirected edge to the graph
void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w);
    adj[w].push_back(v);
}

void Graph::addNewNodeEdgesUntilN(int m0, int m)
{
    // the divisor of the probability of a node to connect to another (initially the graph is fully connected)
    int sumKj = m0 * (m0 - 1);

    for (int i = m0; i < V; i++)
    {
        int added = 0;

        while (added < m)
        {
            for (int j = 0; j < i; j++)
            {
                float randomNumber = float(rand()) / (float(RAND_MAX) + 1.0);
                float probability = (float)(adj[j].size())/(float)sumKj;

                if (randomNumber <= probability) {

                    bool alreadyConnected = false;
                    
                    // verify if it is already connected
                    std::list<int>::iterator k;
                    for (k = adj[j].begin(); k != adj[j].end(); ++k)
                    {
                        if (*k == i) {
                            alreadyConnected = true;
                        }
                    }   

                    if (!alreadyConnected) {
                        // node is not already connected so let's connect it and exit the loop if m connections are already made
                        addEdge(j, i);
                        added++;
                        sumKj++;

                        if (added == m)
                            break;
                    }
                }             
            }
        }
    }
}

void Graph::connectInitialNodes(int numberNodes)
{
    for (int i = 0; i < numberNodes; i++)
    {
        for (int j = i+1; j < numberNodes; j++)
        {
            addEdge(i, j);
        }
    }
}

void Graph::exportGraph(std::string fileName)
{
    std::ofstream graphFile;
    graphFile.open(fileName);

    graphFile << V << std::endl;

    for (int i = 0; i < V; i++)
    {
        std::list<int>::iterator j;
        for (j = adj[i].begin(); j != adj[i].end(); ++j)
        {
            if (*j > i) {
                graphFile << i << " " << *j << std::endl;
            }
        }
    }

    graphFile.close();
}

Graph::Graph(int V, int m0, int m)
{
    this->V = V;
    adj = new std::list<int>[V];

    // graph begins with fully connected network of m0 nodes
    connectInitialNodes(m0);

    // add the edges for the new nodes until n is reached
    addNewNodeEdgesUntilN(m0, m);
}

Graph::~Graph()
{
    delete[] adj;
}

int main(int argc, char *argv[])
{
    int n, m0, m;
    std::string fileName;

    /*  arguments:
            #1 is n number of nodes,
            #2 is m0 number of nodes,
            #3 is m number of nodes,
            #4 is the name of the file to be generated.
    */
    if (argc == 5)
    {
        n = std::atoi(argv[1]);
        m0 = std::atoi(argv[2]);
        m = std::atoi(argv[3]);
        fileName = argv[4];
    }
    else
    {
        std::cout << "Usage: " << argv[0] << " <n> <m0> <m> <file name>" << std::endl;
    }

    // create the graph
    Graph g(n, m0, m);

    g.exportGraph(fileName);

    return 0;
}
