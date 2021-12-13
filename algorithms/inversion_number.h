#include <functional>
#include <iterator>
#include <utility>
#include <vector>

template <class RandomIt1, class RandomIt2, class OutputIt,
          class Compare = std::less<>>
std::pair<OutputIt, size_t> MergeWithInversions(
    RandomIt1 first1, RandomIt1 last1, RandomIt2 first2, RandomIt2 last2,
    OutputIt d_first, Compare compare = Compare{}) {
  size_t inversion_number{};

  while (first1 != last1 && first2 != last2) {
    if (compare(*first2, *first1)) {
      inversion_number += std::distance(first1, last1);
      *d_first++ = std::move(*first2++);
    } else {
      *d_first++ = std::move(*first1++);
    }
  }

  while (first1 != last1) {
    *d_first++ = std::move(*first1++);
  }

  while (first2 != last2) {
    *d_first++ = std::move(*first2++);
  }

  return {d_first, inversion_number};
}

template <class RandomIt, class Compare = std::less<>>
size_t MergeSortWithInversions(RandomIt first, RandomIt last,
                               Compare compare = Compare{}) {
  using ValueType = typename std::iterator_traits<RandomIt>::value_type;

  const size_t size = std::distance(first, last);

  size_t inversion_number{};

  std::vector<ValueType> buffer;
  buffer.reserve(size);

  for (size_t length = 1; length < size; length *= 2) {
    const size_t block_count = (size + length - 1) / length;

    for (size_t index = 0; index + 1 < block_count; index += 2) {
      const auto first1 = std::next(first, index * length);
      const auto last1 = std::next(first1, length);

      const auto first2 = last1;
      const size_t second_size =
          std::min<size_t>(length, std::distance(first2, last));
      const auto last2 = std::next(first2, second_size);

      const auto first_buffer = std::back_inserter(buffer);
      const auto [_, current_inversions] = MergeWithInversions(
          first1, last1, first2, last2, first_buffer, compare);

      inversion_number += current_inversions;
    }
    std::move(buffer.begin(), buffer.end(), first);
    buffer.clear();
  }

  return inversion_number;
}
