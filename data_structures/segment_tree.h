#include <functional>
#include <numeric>
#include <vector>

template <class T>
struct Min {
  static constexpr T kNeutral = std::numeric_limits<T>::max();

  T operator()(const T& left, const T& right) const {
    return std::min(left, right);
  }
};

template <class T>
struct Max {
  static constexpr T kNeutral = std::numeric_limits<T>::min();

  T operator()(const T& left, const T& right) const {
    return std::max(left, right);
  }
};

template <class T>
struct Plus {
  static constexpr T kNeutral = 0;

  T operator()(const T& left, const T& right) const {
    return std::plus(left, right);
  }
};

template <class T, class Combiner = Plus<T>>
class SegmentTree {
 public:
  explicit SegmentTree(size_t size, Combiner combiner = Combiner{})
      : tree_(2 * size), combiner_(combiner) {
  }

  explicit SegmentTree(const std::vector<T>& data, Combiner combiner = Combiner{})
      : tree_(data.size()), combiner_(combiner) {
    tree_.reserve(data.size() * 2);
    tree_.insert(tree_.end(), data.begin(), data.end());
    for (size_t index = data.size() - 1; index > 0; --index) {
      tree_[index] = combiner_(tree_[index << 1], tree_[index << 1 | 1]);
    }
  }

  T Query(size_t from, size_t to) const {
    T left_res{Combiner::kNeutral};
    T right_res{Combiner::kNeutral};

    from += tree_.size() >> 1;
    to += tree_.size() >> 1;

    for (; from < to; from >>= 1, to >>= 1) {
      if (from & 1) {
        left_res = combiner_(left_res, tree_[from++]);
      }
      if (to & 1) {
        right_res = combiner_(tree_[--to], right_res);
      }
    }

    return combiner_(left_res, right_res);
  }

  void Modify(size_t index, const T& value) {
    index += tree_.size() >> 1;
    tree_[index] = value;
    for (; index >>= 1;) {
      tree_[index] = combiner_(tree_[index << 1], tree_[index << 1 | 1]);
    }
  }

  T Get(size_t index) const {
    return tree_[index + (tree_.size() >> 1)];
  }

 private:
  std::vector<T> tree_;
  Combiner combiner_;
};
