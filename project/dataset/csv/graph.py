import csv
import networkx as nx
import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt

Data  = open('edges.csv', "r", encoding='utf8')
next(Data, None)  # skip the first line in the input file
read = csv.reader(Data)
Graphtype=nx.Graph()   # use net.Graph() for undirected graph

G = nx.parse_edgelist(Data, comments='S', delimiter=',', create_using=Graphtype,
                      nodetype=int, data=(('weight', float),))

for x in G.nodes():
    print("Node:", x, "has total #degree:", G.degree(x))
for u, v in G.edges():
    print("Weight of Edge ("+str(u)+","+str(v)+")", G.get_edge_data(u, v))

nx.draw(G)
plt.savefig('myfilename.png')
