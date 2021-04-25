#include <vector>

class CountingSort {
public:
    template <class RandomIt, class Unary>
    void Sort(RandomIt begin, RandomIt end, Unary to_unsigned) {
        size_t max_value = 0;
        std::for_each(begin, end, [&](const auto& value) {
            max_value = std::max(max_value, to_unsigned(value));
        });

        counts_.assign(max_value + 2, 0);

        std::for_each(begin, end, [&](const auto& value) {
            ++counts_[to_unsigned(value) + 1];
        });

        for (size_t index = 1; index < counts_.size(); ++index) {
            counts_[index] += counts_[index - 1];
        }

        sorted_indexes_.resize((std::distance(begin, end)));

        for (size_t index = 0; index < sorted_indexes_.size(); ++index) {
            auto counts_index = to_unsigned(begin[index]);
            sorted_indexes_[counts_[counts_index]] = index;
            ++counts_[counts_index];
        }

        MakeSorted(begin);
    }

private:
    template <class RandomIt>
    void MakeSorted(RandomIt begin) {
        inverse_indexes_.resize(sorted_indexes_.size());
        for (size_t index = 0; index < inverse_indexes_.size(); ++index) {
            inverse_indexes_[sorted_indexes_[index]] = index;
        }

        for (size_t index = 0; index < sorted_indexes_.size(); ++index) {
            std::swap(begin[index], begin[sorted_indexes_[index]]);
            sorted_indexes_[inverse_indexes_[index]] = sorted_indexes_[index];
            inverse_indexes_[sorted_indexes_[index]] = inverse_indexes_[index];
        }
    }

private:
    std::vector<size_t> counts_;
    std::vector<size_t> sorted_indexes_;
    std::vector<size_t> inverse_indexes_;
};
