"""
Program name : adjacency list container
@author      : Induaditya3

"""
from typing import Union

# storing edges
class Edge:
    def __init__(self, to_node: int, from_node: int = -1, weight: float = 1):
        self.to_node: int = to_node
        # -1 value of from_node means that it is not specified
        self.from_node: int = from_node
        # by default edges are unweighted, so edges have 1 weight by default
        self.weight: float = weight


# storing nodes
class Node:
    def __init__(self, index: int, label = None):
        self.index: int = index
        # edges is stored as dict instead of list to enable quick querying whether there is an link between current node and given node
        # key : index of the other node which is connected to current node
        # value: Edge object
        self.edges: dict[int, Edge] = {}
        self.label = label

    @property
    def num_edges(self) -> int:
        return len(self.edges)

    def get_edge(self, neighbor: int) -> Union[Edge, None]:
        if neighbor in self.edges:
            return self.edges[neighbor]
        return None

    def add_edge(self, to_node: int, weight: float = 1):
        self.edges[to_node] = Edge(to_node, self.index, weight)

    def remove_edge(self, to_node: int):
        if to_node in self.edges:
            del self.edges[to_node]

    @property
    def edge_list(self) -> list[Edge]:
        return list(self.edges.values())

    @property
    def sorted_edge_list(self) -> list[Edge]:
        sorted_keys = list(self.edges.keys()).sort()
        return [self.edges[key] for key in sorted_keys]

    
