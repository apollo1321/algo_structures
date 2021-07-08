#include <cstdint>

/*
 * Computes gcd of integers first and second and the coefficients of
 * Bezout's identity:
 * first * first_quotient + second * second_quotient = gcd
 */
void ExtendedGcd(int64_t first, int64_t second, int64_t& gcd,
                 int64_t& first_quotient, int64_t& second_quotient) {
  /*
   *  q_i = r_(i - 1) / r_i
   *  r_(i + 1) = r_(i - 1) - q_i * r_i
   *  s_(i + 1) = s_(i - 1) - q_i * s_i
   *  t_(i + 1) = t_(i - 1) - q_i * t_i
   *
   * Invariant: first * s_i + second * t_i == r_i
   * Base:
   *   s_0 = 1, t_0 = 0, r_0 = first -> first * s_0 + second * t_0 = r_0
   *   s_1 = 0, t_1 = 1, r_1 = second -> first * s_1 + second * t_1 = r_1
   * Step:
   *   r_(i + 1) = r_(i - 1) - r_i * q_i
   *             = a * (s_(i - 1) - s_i * q_i) + b * (t_(i - 1) - t_i * q_i)
   *             = a * s_(i + 1) * b * t_(i + 1)
   */
  int64_t old_r = first < 0 ? -first : first;
  int64_t r = second < 0 ? -second : second;

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

  gcd = old_r;
  first_quotient = first < 0 ? -old_s : old_s;
  second_quotient = second < 0 ? -old_t : old_t;
}
