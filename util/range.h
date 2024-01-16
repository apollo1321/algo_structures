template <class Integral>
class Range {
  class Iterator;

 public:
  constexpr Range(Integral begin, Integral end) noexcept : Begin_{begin}, End_{end} {
  }

  explicit constexpr Range(Integral end) noexcept : Begin_{}, End_{end} {
  }

  constexpr Iterator begin() const noexcept {
    return Iterator{Begin_};
  }

  constexpr Iterator end() const noexcept {
    return Iterator{End_};
  }

 private:
  class Iterator {
   public:
    constexpr Iterator(Integral value) noexcept : Value_{value} {
    }

    constexpr Iterator& operator++() noexcept {
      ++Value_;
      return *this;
    }

    constexpr Integral operator*() const noexcept {
      return Value_;
    }

    constexpr bool operator==(const Iterator& other) const noexcept {
      return Value_ == other.Value_;
    }

    constexpr bool operator!=(const Iterator& other) const noexcept {
      return !(*this == other);
    }

   private:
    Integral Value_;
  };

 private:
  const Integral Begin_;
  const Integral End_;
};
