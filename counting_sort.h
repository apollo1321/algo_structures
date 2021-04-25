#include <vector>

class CountingSort {
public:
    template <class RandomIt, class Unary>
    void Sort(RandomIt begin, RandomIt end, Unary to_unsigned) {
        size_t max = 0;
        std::for_each(begin, end, [&](const auto& value) {
            max = std::max(max, to_unsigned(value));
        });

        counts_.assign(max + 2, 0);

        std::for_each(begin, end, [&](const auto& value) {
            ++counts_[to_unsigned(value) + 1];
        });

        for (size_t i = 1; i < counts_.size(); ++i) {
            counts_[i] += counts_[i - 1];
        }

        indexes_.resize((std::distance(begin, end)));

        for (size_t index = 0; index < indexes_.size(); ++index) {
            auto counts_index = to_unsigned(begin[index]);
            indexes_[counts_[counts_index]] = index;
            ++counts_[counts_index];
        }

        MakeSorted(begin);
    }

private:
    template <class RandomIt>
    void MakeSorted(RandomIt begin) {
        inverse_indexes_.resize(indexes_.size());
        for (size_t i = 0; i < inverse_indexes_.size(); ++i) {
            inverse_indexes_[indexes_[i]] = i;
        }

        for (size_t index = 0; index < indexes_.size(); ++index) {
            std::swap(begin[index], begin[indexes_[index]]);
            indexes_[inverse_indexes_[index]] = indexes_[index];
            inverse_indexes_[indexes_[index]] = inverse_indexes_[index];
        }
    }

private:
    std::vector<size_t> counts_;
    std::vector<size_t> indexes_;
    std::vector<size_t> inverse_indexes_;
};
