/**
 * Precondition:
 * - The numbers in range [begin, end) are partitioned with respect to
 *   predicate, i.e., all numbers for which the predicate is false must precede
 *   all number for which the predicate is true.
 *
 * Returns:
 * - The first number in the range [begin, end) for which the predicate returns
 *   true, end otherwise.
 */
template <class Integral, class Predicate>
Integral BinarySearch(Integral begin, Integral end, Predicate predicate) {
  while (begin < end) {
    auto middle = begin + (end - begin) / 2;
    if (predicate(middle)) {
      end = middle;
    } else {
      begin = middle + 1;
    }
  }
  return begin;
}
