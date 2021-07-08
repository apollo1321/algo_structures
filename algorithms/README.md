## Counting sort

#### `counting_sort.h`

Implementation of the counting sorting algorithm for objects of any type in the STL style. The algorithm does not make
any assumptions about the objects being sorted, instead the user must provide it with a function that converts the
object to an unsigned number.

### Complexity

Time and space complexity is `O(n + k)`, where `n = std::distance(begin, end)`, `k` is the maximum value of the
converted element.

## Extended Euclidean algorithm

#### `extended_gcd.h`

Computes gcd of integers and the coefficients of Bezout's identity.

### Complexity

Time complexity is `O(log(b))`, where `b` is the smaller number.
