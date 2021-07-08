## Annotated Disjoint Set Union

#### `annotated_dsu.h`

DSU is a data structure that stores the collection of non-overlapping sets. It provides two operations:

* `Test(x, y)` - check whether the numbers `x` and `y` are in the same set
* `Unite(x, y)` - unite the set containing element `x` and the set containing element `y`

Annotated DSU among these two functions contains 2 more operations:

* `Annotate(x, label)` - set the `label` to the set that contains `x`
* `Inspect(x)` - get the label of the set that contains `x`

### Complexity

Two heuristics were used in the implementation: path compression and rank heuristic. So the amortized time complexity
for all operations is `O(f(n))`, where `f(n)` is inverse Ackermann function. Space complexity is `O(n)`.

## Treap with implicit key

#### `implicit_key_treap.h`

Treap with implicit key is a structure that that implements a dynamic array. Following operations are provided:

* `Insert(i, x)` - insert the element `x` in dynamic array at index `i`
* `Remove(i)` - remove the element with index `i` from dynamic array
* `operator\[\](i)` - get the element at the `i'th` position
* `InsertSubArray(i, arr)` - insert the dynamic array arr at position `i`
* `CutSubarray(i, s)` - cut subarray that begins from `i'th` element and has the size `s`

This implementation supports move-semantics, so it is possible to insert subarray without its copying.

### Complexity

All the enumerated operations have `O(log(n))` randomized time complexity. Space complexity is `O(n)`.

## Heap with custom swapper

#### `custom_heap.h`
