import random

import matplotlib.pyplot as plt
import networkx as nx

graph = nx.Graph() #無向グラフを作成 
a=0
b=0
ran=100
for i in range(ran):
  b=random.randint(0,ran-1)
  while a==b:
    b=random.randint(0,ran-1)
  graph.add_edge(a,b)
  a=b

nx.draw(graph)
plt.show()
