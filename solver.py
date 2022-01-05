import networkx as nx
import matplotlib.pyplot as plt
import random
graph = nx.Graph() #無向グラフを作成 
a=0
b=0
for i in range(100):
  b=random.randint(0,99)
  while a==b:
    b=random.randint(0,99)
  graph.add_edge(a,b)
  a=b

nx.draw(graph)
plt.show()