#include <iterator>
#include <utility>

struct Swapper {
  template <class T>
  void operator()(T& left, T& right) {
    std::swap(left, right);
  }
};

template <typename RandIt>
RandIt GetLeftChild(RandIt begin, RandIt iter) {
  auto distance = std::distance(begin, iter);
  return std::next(begin, 2 * distance + 1);
}

template <typename RandIt>
RandIt GetRightChild(RandIt begin, RandIt iter) {
  auto distance = std::distance(begin, iter);
  return std::next(begin, 2 * distance + 2);
}

template <typename RandIt>
RandIt GetParent(RandIt begin, RandIt iter) {
  auto distance = std::distance(begin, iter);
  return std::next(begin, (distance + 1) / 2 - 1);
}

template <typename RandIt>
bool HasLeftChild(RandIt begin, RandIt end, RandIt iter) {
  return 2 * std::distance(begin, iter) + 1 < std::distance(begin, end);
}

template <typename RandIt>
bool HasRightChild(RandIt begin, RandIt end, RandIt iter) {
  return 2 * std::distance(begin, iter) + 2 < std::distance(begin, end);
}

template <class RandIt, class Comparator = std::less<>, class Swapper = Swapper>
void SiftUp(RandIt begin, RandIt iter, Comparator comp = Comparator(),
            Swapper swap = Swapper()) {
  while (iter != begin && comp(*GetParent(begin, iter), *iter)) {
    auto parent = GetParent(begin, iter);
    swap(*iter, *parent);
    iter = parent;
  }
}

template <class RandIt, class Comparator = std::less<>, class Swapper = Swapper>
void SiftDown(RandIt begin, RandIt end, RandIt iter,
              Comparator comp = Comparator(), Swapper swap = Swapper()) {
  while ((HasLeftChild(begin, end, iter) &&
          comp(*iter, *GetLeftChild(begin, iter))) ||
         (HasRightChild(begin, end, iter) &&
          comp(*iter, *GetRightChild(begin, iter)))) {
    if (!HasRightChild(begin, end, iter) ||
        comp(*GetRightChild(begin, iter), *GetLeftChild(begin, iter))) {
      auto left_child = GetLeftChild(begin, iter);
      swap(*iter, *left_child);
      iter = left_child;
    } else {
      auto right_child = GetRightChild(begin, iter);
      swap(*iter, *right_child);
      iter = right_child;
    }
  }
}

template <class RandIt, class Comparator = std::less<>, class Swapper = Swapper>
void RestoreHeap(RandIt begin, RandIt end, RandIt iter,
                 Comparator comp = Comparator(), Swapper swap = Swapper()) {
  SiftUp(begin, iter, comp, swap);
  SiftDown(begin, end, iter, comp, swap);
}

template <class RandIt, class Comparator = std::less<>, class Swapper = Swapper>
void PopHeap(RandIt begin, RandIt end, Comparator comp = Comparator(),
             Swapper swap = Swapper()) {
  swap(*begin, *std::prev(end));
  SiftDown(begin, std::prev(end), begin, comp, swap);
}

template <class RandIt, class Comparator = std::less<>, class Swapper = Swapper>
void PushHeap(RandIt begin, RandIt end, Comparator comp = Comparator(),
              Swapper swap = Swapper()) {
  SiftUp(begin, std::prev(end), comp, swap);
}

template <class RandIt, class Comparator = std::less<>, class Swapper = Swapper>
void MakeHeap(RandIt begin, RandIt end, Comparator comp = Comparator(),
              Swapper swap = Swapper()) {
  auto iter = begin + std::distance(begin, end) / 2;
  while (iter != begin) {
    SiftDown(begin, end, std::prev(iter), comp, swap);
    --iter;
  }
}
