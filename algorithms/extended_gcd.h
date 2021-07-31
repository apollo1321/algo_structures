#include <cstdint>

struct Gcd {
  int64_t gcd;
  int64_t a_quotient;
  int64_t b_quotient;
};

/*
 * Computes gcd of integers a and b and the coefficients of
 * Bezout's identity:
 * a * a_quotient + b * b_quotient = gcd
 */
Gcd ExtendedGcd(int64_t a, int64_t b) {
  /*
   *  q_i = r_(i - 1) / r_i
   *  r_(i + 1) = r_(i - 1) - q_i * r_i
   *  s_(i + 1) = s_(i - 1) - q_i * s_i
   *  t_(i + 1) = t_(i - 1) - q_i * t_i
   *
   * Invariant: a * s_i + b * t_i == r_i
   * Base:
   *   s_0 = 1, t_0 = 0, r_0 = a -> a * s_0 + b * t_0 = r_0
   *   s_1 = 0, t_1 = 1, r_1 = b -> a * s_1 + b * t_1 = r_1
   * Step:
   *   r_(i + 1) = r_(i - 1) - r_i * q_i
   *             = a * (s_(i - 1) - s_i * q_i) + b * (t_(i - 1) - t_i * q_i)
   *             = a * s_(i + 1) * b * t_(i + 1)
   *
   * If gcd(a, b) != min(a, b), a, b > 0:
   *   |s_i| <= b / (2 * gcd(a, b)) && |t_i| <= a / (2 * gcd(a, b)),
   * for 0 <= i <= k, where k is such, that r_k = gcd(a, b).
   * So there is no integer overflow.
   */
  int64_t old_r = a < 0 ? -a : a;
  int64_t r = b < 0 ? -b : b;

  int64_t old_s = 1;
  int64_t s = 0;

  int64_t old_t = 0;
  int64_t t = 1;

  while (r != 0) {
    int64_t quotient = old_r / r;

    int64_t temp = old_r;
    old_r = r;
    r = temp - quotient * r;

    temp = old_s;
    old_s = s;
    s = temp - quotient * s;

    temp = old_t;
    old_t = t;
    t = temp - quotient * t;
  }

  return Gcd{old_r, a < 0 ? -old_s : old_s, b < 0 ? -old_t : old_t};
}

/*
 * Precondition:
 * - gcd(value, module) == 1
 *
 * Returns:
 * - The multiplicative inverse of the value, i.e.
 *   value * inverse == 1 (mod module)
 */
int64_t ComputeInverse(int64_t value, int64_t module) {
  auto gcd = ExtendedGcd(value, module);
  return (gcd.a_quotient + module) % module;
}
