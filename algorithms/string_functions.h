#include <string_view>
#include <vector>

template <class Container>
std::vector<size_t> ComputePrefixFunction(const Container& string) {
  std::vector<size_t> border_sizes(std::size(string));
  border_sizes[0] = 0;
  for (size_t index = 1; index < border_sizes.size(); ++index) {
    size_t border_size = border_sizes[index - 1];
    while (border_size > 0 && string[border_size] != string[index]) {
      border_size = border_sizes[border_size - 1];
    }
    border_sizes[index] = border_size + (string[border_size] == string[index]);
  }
  return border_sizes;
}

template <class Container>
std::vector<size_t> ComputeZFunction(const Container& string) {
  if (std::size(string) == 0) {
    return {};
  }
  std::vector<size_t> result(std::size(string));
  size_t max_index = 0;
  for (size_t z_index = 1; z_index < result.size(); ++z_index) {
    size_t offset = z_index - max_index;
    if (offset + result[offset] < result[max_index]) {
      result[z_index] = result[offset];
    } else {
      size_t z_val =
          result[max_index] == 0 ? 0 : max_index + result[max_index] - z_index;
      while (z_index + z_val < string.size() &&
             string[z_val] == string[z_val + z_index]) {
        ++z_val;
      }
      result[z_index] = z_val;
      max_index = z_index;
    }
  }
  result[0] = string.size();

  return result;
}
