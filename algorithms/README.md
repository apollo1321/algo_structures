## Binary search

#### `binary_search.h`

Template implementation of binary search for integer types.

### Complexity

Time complexity is `O(log(n))`, where `n = end - begin`.

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

* `ExtendedGcd(a, b)` - computes gcd of integers and the coefficients of Bezout's identity,
  i.e. `a * a_q + b * b_q = gcd(a, b)`
* `ComputeInverse(a, m)` - computes the multiplicative inverse of the value, i.e. `a * inv == 1 (mod m)`.

### Complexity

Time complexity is `O(log(b))`, where `b` is the smaller number.

## Number of inversions

#### `iversion_number.h`

* `MergeSortWithInversions` - sorts elements in range `[first, last)` and computes the number of inversions in range,
  i.e. the number of pairs `(i, j)` such that `i < j, *(first + i) > *(first + j)` (
  or `i < j, compare(*(first + j), *(first + i)) == true`). Sort is stable.

### Complexity

Time complexity is `O(n * log(n))`, where `n = distance(first, last)`. Space complexity is `O(n)`.
