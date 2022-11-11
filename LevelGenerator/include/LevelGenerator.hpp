#ifndef SCENERY_GENERATOR_LEVEL_GENERATOR_LEVEL_GENERATOR_HPP
#define SCENERY_GENERATOR_LEVEL_GENERATOR_LEVEL_GENERATOR_HPP

#include <cstdint>

#include "LevelData.hpp"

namespace SceneryGenerator::LevelGenerator {

//! Interface for level generator.
class LevelGenerator {
  // A method returning generated level.
  virtual LevelData GenerateLevel() = 0;
};

}  // namespace SceneryGenerator::LevelGenerator

#endif