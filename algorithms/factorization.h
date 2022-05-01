#include <cstdint>
#include <map>
#include <vector>

/**
 * Precondition:
 * - number > 0
 *
 * Finds all prime divisors of a number in non-decreasing order and passes each
 * of them to callback
 */
template <class Callback>
void Factorize(uint64_t number, Callback callback) {
  while (number % 2 == 0) {
    number /= 2;
    callback(2);
  }
  for (uint64_t divisor = 3; divisor * divisor <= number; divisor += 2) {
    while (number % divisor == 0) {
      number /= divisor;
      callback(divisor);
    }
  }
  if (number > 1) {
    callback(number);
  }
}

std::vector<std::pair<uint64_t, size_t>> FactorizeInVector(uint64_t number) {
  std::vector<std::pair<uint64_t, size_t>> result;
  Factorize(number, [&result](uint64_t value) {
    if (result.empty() || result.back().first != value) {
      result.emplace_back(value, 0);
    }
    result.back().second += 1;
  });
  return result;
}

std::map<uint64_t, size_t> FactorizeInMap(uint64_t number) {
  std::map<uint64_t, size_t> result;
  Factorize(number, [&result](uint64_t value) {
    ++result[value];
  });
  return result;
}
