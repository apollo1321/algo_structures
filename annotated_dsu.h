#include <limits>
#include <vector>

class DisjointSetUnion {
public:
    static constexpr size_t kNoLabel = std::numeric_limits<size_t>::max();

public:
    explicit DisjointSetUnion(size_t element_count)
        : parent_(element_count, kNoParent),
          rank_(element_count),
          labels_(element_count, kNoLabel) {
    }

    bool Test(size_t first, size_t second) {
        return FindRoot(first) == FindRoot(second);
    }

    void Unite(size_t first, size_t second) {
        size_t first_root = FindRoot(first);
        size_t second_root = FindRoot(second);
        if (first_root == second_root) {
            return;
        }
        if (rank_[first_root] == rank_[second_root]) {
            parent_[first_root] = second_root;
            ++rank_[second_root];
        } else if (rank_[first_root] < rank_[second_root]) {
            parent_[first_root] = second_root;
        } else {
            parent_[second_root] = first_root;
        }
    }

    void Annotate(size_t element, size_t label) {
        size_t root = FindRoot(element);
        labels_[root] = label;
    }

    size_t Inspect(size_t element) {
        size_t root = FindRoot(element);
        return labels_[root];
    }

private:
    static constexpr size_t kNoParent = std::numeric_limits<size_t>::max();

private:
    size_t FindRoot(size_t element) {
        size_t root = element;
        while (parent_[root] != kNoParent) {
            root = parent_[root];
        }
        CompressPath(element, root);
        return root;
    }

    void CompressPath(size_t from, size_t root) {
        while (parent_[from] != kNoParent) {
            size_t next = parent_[from];
            parent_[from] = root;
            from = next;
        }
    }

private:
    std::vector<size_t> parent_;
    std::vector<size_t> rank_;
    std::vector<size_t> labels_;
};
