#include <cstdint>

#include "LevelData.hpp"

namespace SceneryGenerator {

//! Interface for level generator.
class LevelGenerator {

  // A method returning generated level.
  virtual LevelData GenerateLevel() = 0;
};

}  // namespace SceneryGenerator