#include <gtest/gtest.h>

#include <algorithm>
#include <set>
#include <unordered_set>

#include "RandomNumberGenerator.hpp"

namespace SceneryGenerator::Utils::Test {

TEST(RandomGeneratorTest, RangeShouldBeAssignedToMinMax) {
  constexpr int32_t kRangeMin = -10;
  constexpr int32_t kRangeMax = 10;

  RandomNumberGenerator<int32_t> rng({kRangeMin, kRangeMax});

  EXPECT_EQ(rng.GetMinimum(), kRangeMin);
  EXPECT_EQ(rng.GetMaximum(), kRangeMax);
}

TEST(RandomGeneratorTest, RangeShouldBeFixedAndAssignedToMinMax) {
  constexpr int32_t kInvaliRangeMax = -10;
  constexpr int32_t kInvalidRangeMin = 10;

  RandomNumberGenerator<int32_t> rng({kInvalidRangeMin, kInvaliRangeMax});

  EXPECT_EQ(rng.GetMinimum(), kInvaliRangeMax);
  EXPECT_EQ(rng.GetMaximum(), kInvalidRangeMin);
}

TEST(RandomGeneratorTest, GetNumberShouldReturnValuesWithinDeclaredRange) {
  constexpr int32_t kRangeMin = -10;
  constexpr int32_t kRangeMax = 10;

  RandomNumberGenerator<int32_t> rng({kRangeMin, kRangeMax});

  std::vector<int32_t> randomized_values;
  int32_t number_of_iterations = 100;

  while (number_of_iterations--) {
    randomized_values.push_back(rng.GetNumber());
  }

  EXPECT_TRUE(std::all_of(randomized_values.cbegin(), randomized_values.cend(),
                          [](auto randomized_value) {
                            return randomized_value >= kRangeMin &&
                                   randomized_value <= kRangeMax;
                          }));
}

TEST(RandomGeneratorTest, GetNumbersShouldReturnValuesWithinDeclaredRange) {
  constexpr int32_t kRangeMin = -10;
  constexpr int32_t kRangeMax = 10;

  RandomNumberGenerator<int32_t> rng({kRangeMin, kRangeMax});
  std::vector<int32_t> randomized_values = rng.GetNumbers(100);

  EXPECT_TRUE(std::all_of(randomized_values.cbegin(), randomized_values.cend(),
                          [](auto randomized_value) {
                            return randomized_value >= kRangeMin &&
                                   randomized_value <= kRangeMax;
                          }));
}

TEST(RandomGeneratorTest, GetNumberShouldReturnDistinctValues) {
  constexpr int32_t kRangeMin = -10;
  constexpr int32_t kRangeMax = 10;
  constexpr int32_t kMinimalNumberOfUniqueElements = 10;

  RandomNumberGenerator<int32_t> rng({kRangeMin, kRangeMax});

  std::unordered_set<int32_t> unique_values;
  int32_t number_of_iterations = 100;

  while (number_of_iterations--) {
    unique_values.insert(rng.GetNumber());
  }

  EXPECT_GT(unique_values.size(), kMinimalNumberOfUniqueElements);
}

TEST(RandomGeneratorTest, GetNumbersShouldReturnDistinctValues) {
  constexpr int32_t kRangeMin = -10;
  constexpr int32_t kRangeMax = 10;
  constexpr int32_t kMinimalNumberOfUniqueElements = 10;

  RandomNumberGenerator<int32_t> rng({kRangeMin, kRangeMax});
  auto result = rng.GetNumbers(100);
  std::unordered_set<int32_t> unique_values;

  for (auto value : result) {
    unique_values.insert(value);
  }

  EXPECT_GT(unique_values.size(), kMinimalNumberOfUniqueElements);
}

}  // namespace SceneryGenerator::Utils::Test