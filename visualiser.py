import random

import matplotlib.pyplot as plt
import networkx as nx
from networkx.utils.decorators import nodes_or_number

graph = nx.Graph() #無向グラフを作成 
f=open("hoge.col","r")
nodeNum=0
edgeNum=0
datalist=f.readlines()
for s in datalist:
  line=s.split()
  if line[0]=="p":
    nodeNum=int(line[1])
    edgeNum=int(line[2])
  if line[0]=="e":
    graph.add_edge(int(line[1]),int(line[2]))

for i in range(nodeNum):
  graph.add_node(i+1)

c=["red" if n==1 else "aqua" for n in graph.nodes()]
nx.draw_networkx(graph, node_color=c)
plt.show()
