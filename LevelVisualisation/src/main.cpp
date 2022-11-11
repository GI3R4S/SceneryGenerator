#include <iostream>

#include "BasicLevelGenerator.hpp"
#include "LevelData.hpp"
#include "RandomNumberGenerator.hpp"

int main() {
  SceneryGenerator::LevelGenerator::BasicLevelGenerator::Configuration
      configuration;

  SceneryGenerator::LevelGenerator::BasicLevelGenerator basic_level_generator(
      configuration);

  SceneryGenerator::Utils::RandomNumberGenerator<int16_t> rng({1, 20});

  auto result = rng.GetNumbers(10);

  for (const auto& number : result) {
    std::cout << number << ", " << std::endl;
  }

  std::cout << "\n\n\n\n\n\n\n";

  SceneryGenerator::Utils::RandomNumberGenerator<float> rng_float({2.1, 3.7});

  auto result_float = rng_float.GetNumbers(10);

  for (const auto& number : result_float) {
    std::cout << number << ", " << std::endl;
  }
}