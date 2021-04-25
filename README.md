# Useful Algorithms and Data Structures
This repository is dedicated to structures and algorithms that I found interesting and useful. It is assumed that it will be replenished over time. 

The code is written in C++17. When writing the code, I followed the Google style guide: https://google.github.io/styleguide/cppguide.html

## Annotated Disjoint Set Union
#### annotated_dsu.h

DSU is a data structure that stores the collection of non-overlapping sets. It provides two operations:
* Test(x, y) - check whether the numbers x and y are in the same set
* Unite(x, y) - unite the set that contains x and the set that contains y

Annotated DSU among these two functions contains 2 more operations:
* Annotate(x) - set the label to the set that contains x
* Inspect(x) - get the label of the set that contains x

### Complexity
Two heuristics were used in the implementation: path compression and rank heuristic. So the amortized time complexity for all operations is O(f(n)), where f(n) is inverse Ackermann function. Space complexity is O(n).

## Treap with implicit key
#### implicit_key_treap.h

Treap with implicit key is a structure that that implements a dynamic array. Following operations are provided:
* Insert(i, x) - insert the element x in dynamic array at index i
* Remove(i) - remove the element with index i from dynamic array
* operator\[\](i) - get the element at the i-th position
* InsertSubArray(i, arr) - insert the dynamic array arr at position i
* CutSubarray(i, s) - cut subarray that begins from i'th element and has the size s

This implementation supports move-semantics, so it is possible to insert subarray without its copying.

### Complexity
All of the enumerated operations have O(log(n)) randomized time complexity. Space complexity is O(n).

## Heap with custom swapper
#### custom_heap.h

## Counting sort
#### counting_sort.h

Implementation of the counting sorting algorithm for objects of any type in the STL style. The algorithm does not make any assumptions about the objects being sorted, instead the user must provide it with a function that converts the object to an unsigned number.

### Complexity
Time and space complexity is O(n + k), where n = std::distance(begin, end), k is the maximum value of the converted element.
