from disjoint_set import Disjoint_Set
import math


class Kruskals(object):
    '''
    This is a class for a kruskals algorithm solver
    '''

    def __init__(self, verticies, edges):

        '''
        Takes a set of verticies and a list of tuples 'edges' and initializes a graph and
        all necessary elements to use kruskals algorithm

        verticies is of type set() with each vertex being represented by a string (e.g. "A")
        '''

        self.V = verticies
        self.E = edges
        self.chosen_edges = set()
        self.verticies = Disjoint_Set()
        self.chosen_verticies = Disjoint_Set()


        for ver in self.V:
            if ver not in self.chosen_verticies.sets:
                self.verticies.make_set(ver)


    def possible_edges(self):

        '''
        This Method will look at our Disjoint set and decide which possible edges may be possibly chosen
        determined by Prims Alogorithm

        It should only use our self variables and will return a list of edges
        '''

        all_edges = self.E
        possible_edges = []

        for edges in all_edges:
            for i in self.chosen_verticies.representatives:
                if (edges[1] in self.chosen_verticies.Find_set(i)) and (edges[2] in self.chosen_verticies.Find_set(i)):
                    a = list(all_edges)
                    a.remove(edges)
                    all_edges = a

        for edges in all_edges:
            possible_edges.append(edges)

        return possible_edges

    def choose_next(self):

        '''
        This method will decide which vertex should be added to our current MST 

        It must update our Disjoint Set and chosen_edges as well to reflect the update

        It will return the vertex that was chosen and its cost
        '''

        chosen_vertex = ""

        # First we get the possible edges we could take
        possible_edges = self.possible_edges()

        # Then we determine which one would to take by Prims
        chosen_edge = None
        cost = math.inf


        for edges in possible_edges:
            if edges[0] < cost:
                cost = edges[0]
                chosen_edge = edges

        # Then we update self.chosen_edges and self.verticies appropriately
        self.chosen_edges.add(chosen_edge)


        for i in range(1, 3):
            if chosen_edge[i] in self.verticies.sets:
                del self.verticies.sets[chosen_edge[i]]
                self.chosen_verticies.make_set(chosen_edge[i])

        for i in self.chosen_verticies.representatives:
            if chosen_edge[1] in self.chosen_verticies.sets[i]:
                represent1 = i
            if chosen_edge[2] in self.chosen_verticies.sets[i]:
                represent2 = i

        if len(self.chosen_verticies.representatives) > 1:
            self.chosen_verticies.Union(represent1, represent2)


        return chosen_edge, cost

    def find_mst(self):

        '''
        This method will iteratively call choose_next() until the MST is completed 

        Once it has finished it must return the list of edges that were chosen

        '''

        total_cost = 0


        for i in range(len(self.V) - 1):
            a = self.choose_next()
            total_cost += a[1]

        return self.chosen_edges, total_cost