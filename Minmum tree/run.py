from disjoint_set import Disjoint_Set
from prims import Prims
from kruskals import Kruskals

import random

import time


def main():
    example_verticies, example_edges = generate_random_ex()
    prim_solver = Prims(example_verticies, example_edges)

    kruskal_solver = Kruskals(example_verticies, example_edges)

    print("")

    start = time.time()
    print("cost of MST from your Prims:", prim_solver.find_mst()[1])
    end = time.time()
    print("and it took Prims", end - start, "seconds to find a solution \n")

    start = time.time()
    print("cost of MST from your Kruskals:", kruskal_solver.find_mst()[1])
    end = time.time()
    print("and it took Kruskals", end - start, "seconds to find a solution\n")


# adding a param with the equals like this sets the default (in this case size is default 10)
def generate_random_ex(size=10, weight_range=10):
    example_verticies = set()
    example_edges = []

    for elem in range(size):
        example_verticies.update(str(elem))

    temp_set = example_verticies.copy()

    for elem in example_verticies:
        temp_set.remove(elem)
        for other in temp_set:
            weight = random.randrange(weight_range)
            edge = (weight, elem, other)
            example_edges.append(edge)

    return example_verticies, example_edges


if __name__ == "__main__":
    main()
