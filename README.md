# Useful Structures and Algorithms
This repository is dedicated to structures and algorithms that I found interesting and useful. It is assumed that it will be replenished over time. 

The code is written in C++17. When writing the code, I followed the Google style guide: https://google.github.io/styleguide/cppguide.html

## Annotated Disjoint Set Union
DSU is a data structure that stores the collection of non-overlapping sets. It provides two operations:
* Test(x, y) - checks whether the numbers x and y are in the same set
* Unite(x, y) - unites the set that contains x and the set that contains y

Annotated DSU among these two functions contains 2 more operations:
* Annotate(x) - set the label to the set that contains x
* Inspect(x) - get the label of the set that contains x

### Complexity
Two heuristics were used in the implementation: path compression and rank heuristic. So the amortized time complexity for all operations is O(f(n)), where f(n) is inverse Ackermann function. Space complexity is O(n).
