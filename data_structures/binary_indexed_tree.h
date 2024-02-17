#include <vector>

template <class T, size_t Dimensions>
class BinaryIndexedTree {};

struct BinaryIndexedTreeBase {
  static size_t GetSumStartIndex(size_t index) {
    return index & (index + 1);
  }

  static size_t GetNextAddIndex(size_t index) {
    return index | (index + 1);
  }
};


template <class T>
class BinaryIndexedTree<T, 1> : private BinaryIndexedTreeBase {
 public:
  explicit BinaryIndexedTree(size_t size) : tree_(size) {
  }

  T GetSum(size_t index) const {
    T result{};
    --index;
    while (index < tree_.size()) {
      result += tree_[index];
      index = GetSumStartIndex(index) - 1;
    }
    return result;
  }

  T GetSum(size_t from, size_t to) const {
    return GetSum(to) - GetSum(from);
  }

  T Get(size_t index) const {
    return GetSum(index, index + 1);
  }

  void Set(size_t index, const T& value) {
    Add(index, value - Get(index));
  }

  void Add(size_t index, const T& value) {
    while (index < tree_.size()) {
      tree_[index] += value;
      index = GetNextAddIndex(index);
    }
  }

 private:
  std::vector<T> tree_;
};

template <class T>
class BinaryIndexedTree<T, 2> : private BinaryIndexedTreeBase {
 public:
  BinaryIndexedTree(size_t x_size, size_t y_size)
      : tree_(x_size * y_size), x_size_{x_size}, y_size_{y_size} {
  }

  T GetSum(size_t x_index, size_t y_index) const {
    T result{};
    for (size_t x = x_index - 1; x < x_size_; x = GetSumStartIndex(x) - 1) {
      for (size_t y = y_index - 1; y < y_size_; y = GetSumStartIndex(y) - 1) {
        result += tree_[y + x * y_size_];
      }
    }
    return result;
  }

  T GetSum(size_t x_from, size_t y_from, size_t x_to, size_t y_to) const {
    return GetSum(x_to, y_to) - GetSum(x_to, y_from) - GetSum(x_from, y_to) +
           GetSum(x_from, y_from);
  }

  T Get(size_t x_index, size_t y_index) const {
    return GetSum(x_index, y_index, x_index + 1, y_index + 1);
  }

  void Set(size_t x_index, size_t y_index, const T& value) {
    Add(x_index, y_index, value - Get(x_index, y_index));
  }

  void Add(size_t x_index, size_t y_index, const T& value) {
    for (size_t x = x_index; x < x_size_; x = GetNextAddIndex(x)) {
      for (size_t y = y_index; y < y_size_; y = GetNextAddIndex(y)) {
        tree_[y + x * y_size_] += value;
      }
    }
  }

 private:
  std::vector<T> tree_;
  size_t x_size_, y_size_;
};

template <class T>
class BinaryIndexedTree<T, 3> : private BinaryIndexedTreeBase {
 public:
  BinaryIndexedTree(size_t x_size, size_t y_size, size_t z_size)
      : tree_(x_size * y_size * z_size), x_size_{x_size}, y_size_{y_size}, z_size_{z_size} {
  }

  T GetSum(size_t x_index, size_t y_index, size_t z_index) const {
    T result{};
    for (size_t x = x_index - 1; x < x_size_; x = GetSumStartIndex(x) - 1) {
      for (size_t y = y_index - 1; y < y_size_; y = GetSumStartIndex(y) - 1) {
        for (size_t z = z_index - 1; z < y_size_; z = GetSumStartIndex(z) - 1) {
          result += tree_[z + y * z_size_ + x * y_size_ * z_size_];
        }
      }
    }
    return result;
  }

  T GetSum(size_t x_from, size_t y_from, size_t z_from, size_t x_to,
           size_t y_to, size_t z_to) const {
    return GetSum(x_to, y_to, z_to) - GetSum(x_from, y_to, z_to) -
           GetSum(x_to, y_from, z_to) - GetSum(x_to, y_to, z_from) +
           GetSum(x_from, y_from, z_to) + GetSum(x_to, y_from, z_from) +
           GetSum(x_from, y_to, z_from) - GetSum(x_from, y_from, z_from);
  }

  T Get(size_t x_index, size_t y_index, size_t z_index) const {
    return GetSum(x_index, y_index, z_index, x_index + 1, y_index + 1,
                  z_index + 1);
  }

  void Set(size_t x_index, size_t y_index, size_t z_index, const T& value) {
    Add(x_index, y_index, z_index, value - Get(x_index, y_index, z_index));
  }

  void Add(size_t x_index, size_t y_index, size_t z_index, const T& value) {
    for (size_t x = x_index; x < x_size_; x = GetNextAddIndex(x)) {
      for (size_t y = y_index; y < y_size_; y = GetNextAddIndex(y)) {
        for (size_t z = z_index; z < z_size_; z = GetNextAddIndex(z)) {
          tree_[z + y * z_size_ + x * y_size_ * z_size_] += value;
        }
      }
    }
  }

 private:
  std::vector<T> tree_;
  size_t x_size_, y_size_, z_size_;
};
