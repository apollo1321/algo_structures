#include <functional>
#include <vector>

struct Min {
  template <class T>
  T operator()(const T& left, const T& right) const {
    return std::min(left, right);
  }
};

struct Max {
  template <class T>
  T operator()(const T& left, const T& right) const {
    return std::max(left, right);
  }
};

template <class T, class Combiner = std::plus<>>
class SegmentTree {
 public:
  explicit SegmentTree(size_t size, const T& initial = T{},
                       Combiner combiner = Combiner{})
      : tree_(2 * size), initial_(initial), combiner_(combiner) {
  }

  explicit SegmentTree(const std::vector<T>& data, const T& initial = T{},
                       Combiner combiner = Combiner{})
      : tree_(data.size()), initial_(initial), combiner_(combiner) {
    tree_.reserve(data.size() * 2);
    tree_.insert(tree_.end(), data.begin(), data.end());
    for (size_t index = data.size() - 1; index > 0; --index) {
      tree_[index] = combiner_(tree_[index << 1], tree_[index << 1 | 1]);
    }
  }

  T Query(size_t from, size_t to) const {
    T left_res{initial_};
    T right_res{initial_};
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

 private:
  std::vector<T> tree_;
  const T initial_;
  Combiner combiner_;
};
