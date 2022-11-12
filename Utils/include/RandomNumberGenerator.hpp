#ifndef SCENERY_GENERATOR_UTILS_RANDOMNUMBERGENERATOR_HPP
#define SCENERY_GENERATOR_UTILS_RANDOMNUMBERGENERATOR_HPP

#include <chrono>
#include <concepts>
#include <cstdlib>
#include <random>
#include <tuple>

namespace SceneryGenerator::Utils {

template <typename T>
concept IsNumeric = std::integral<T> || std::floating_point<T>;

template <typename tNumberType>
  requires IsNumeric<tNumberType>
class RandomNumberGenerator {
 public:
  RandomNumberGenerator(std::pair<tNumberType, tNumberType> range)
      : min_(std::min(range.first, range.second)),
        max_(std::max(range.first, range.second)),
        random_engine_(
            std::chrono::system_clock::now().time_since_epoch().count()),
        distribution_(min_, max_) {}

  tNumberType GetNumber() { return distribution_(random_engine_); }

  std::vector<tNumberType> GetNumbers(uint32_t count_of_numbers) {
    std::vector<tNumberType> numbers;
    while (count_of_numbers--) {
      numbers.push_back(distribution_(random_engine_));
    };

    return numbers;
  }

  tNumberType GetMinimum() const { return min_; }

  tNumberType GetMaximum() const { return max_; }

 private:
  using tDistributionType = typename std::conditional<
      std::is_integral<tNumberType>::value,
      std::uniform_int_distribution<tNumberType>,
      std::uniform_real_distribution<tNumberType>>::type;

  tNumberType min_;
  tNumberType max_;
  std::mt19937 random_engine_;
  tDistributionType distribution_;
};

}  // namespace SceneryGenerator::Utils

#endif  // SCENERY_GENERATOR_UTILS_RANDOMNUMBERGENERATOR_HPP