#include <random>
#include <tuple>
#include <vector>

template <class T>
class ImplicitKeyTreap {
  struct Node {
    Node(const T& value, int priority)
        : value{value}, priority{priority}, left{}, right{}, subtree_size{1} {
    }
    T value;
    int priority;
    Node* left;
    Node* right;

    size_t subtree_size;
  };

 public:
  ImplicitKeyTreap() = default;

  ImplicitKeyTreap(const ImplicitKeyTreap& other) {
    for (size_t index = 0; index < other.Size(); ++index) {
      Insert(index, other[index]);
    }
  }

  ImplicitKeyTreap(ImplicitKeyTreap&& other) {
    std::swap(other.root_, root_);
  }

  ImplicitKeyTreap& operator=(ImplicitKeyTreap other) {
    std::swap(*this, other);
  }

  void Insert(size_t index, const T& value) {
    Node* node = new Node{value, priority_(generator_)};
    auto [first_root, second_root] = Split(root_, index);
    root_ = Merge(first_root, Merge(node, second_root));
  }

  void Remove(size_t index) {
    auto [left, temp] = Split(root_, index);
    auto [node, right] = Split(temp, 1);
    root_ = Merge(left, right);
    delete node;
  }

  const T& operator[](size_t index) const {
    return FindNode(index)->value;
  }

  T& operator[](size_t index) {
    return FindNode(index)->value;
  }

  size_t Size() const {
    if (root_ == nullptr) {
      return 0;
    }
    return root_->subtree_size;
  }

  bool Empty() const {
    return root_ == nullptr;
  }

  void InsertSubArray(size_t index, ImplicitKeyTreap treap) {
    auto [left, right] = Split(root_, index);
    root_ = Merge(left, Merge(treap.root_, right));
    treap.root_ = nullptr;
  }

  ImplicitKeyTreap CutSubarray(size_t from, size_t size) {
    auto [first, temp] = Split(root_, from);
    auto [middle, second] = Split(temp, size);
    root_ = Merge(first, second);
    ImplicitKeyTreap result;
    result.root_ = middle;
    return result;
  }

  ~ImplicitKeyTreap() {
    if (root_) {
      FreeSubtree(root_);
      delete root_;
    }
  }

 private:
  Node* root_{};
  std::mt19937 generator_{42};
  std::uniform_int_distribution<int> priority_{std::numeric_limits<int>::min(),
                                               std::numeric_limits<int>::max()};

 private:
  static void FreeSubtree(Node* root) {
    if (root->left) {
      FreeSubtree(root->left);
      delete root->left;
    }
    if (root->right) {
      FreeSubtree(root->right);
      delete root->right;
    }
  }

  Node* FindNode(size_t index) const {
    Node* node = root_;
    size_t current_index = GetRootIndex(node);
    while (current_index != index) {
      if (index < current_index) {
        node = node->left;
      } else {
        node = node->right;
        index -= current_index + 1;
      }
      current_index = GetRootIndex(node);
    }
    return node;
  }

  static Node* Merge(Node* first_root, Node* second_root) {
    if (second_root == nullptr) {
      return first_root;
    }
    if (first_root == nullptr) {
      return second_root;
    }
    if (first_root->priority < second_root->priority) {
      first_root->subtree_size += second_root->subtree_size;
      first_root->right = Merge(first_root->right, second_root);
      return first_root;
    } else {
      second_root->subtree_size += first_root->subtree_size;
      second_root->left = Merge(first_root, second_root->left);
      return second_root;
    }
  }

  static std::tuple<Node*, Node*> Split(Node* root, size_t index) {
    if (root == nullptr) {
      return {nullptr, nullptr};
    }
    size_t current_index = GetRootIndex(root);
    if (current_index == index) {
      Node* left = root->left;
      root->left = nullptr;
      RestoreSubtreeSize(root);
      return {left, root};
    } else if (current_index < index) {
      auto [left_tree, right_tree] =
          Split(root->right, index - current_index - 1);
      root->right = left_tree;
      RestoreSubtreeSize(root);
      return {root, right_tree};
    } else {
      auto [left_tree, right_tree] = Split(root->left, index);
      root->left = right_tree;
      RestoreSubtreeSize(root);
      return {left_tree, root};
    }
  }

  static size_t GetRootIndex(const Node* root) {
    if (root->left == nullptr) {
      return 0;
    }
    return root->left->subtree_size;
  }

  static void RestoreSubtreeSize(Node* node) {
    node->subtree_size = 1;
    if (node->right) {
      node->subtree_size += node->right->subtree_size;
    }
    if (node->left) {
      node->subtree_size += node->left->subtree_size;
    }
  }
};
