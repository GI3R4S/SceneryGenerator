#include "BasicLevelGenerator.hpp"

#include <cstdint>
#include <set>

#include "BasicLevelGeneratorImpl.hpp"

namespace SceneryGenerator::LevelGenerator {

//! Constructor for the BasicLevelGenerator
BasicLevelGenerator::BasicLevelGenerator(Configuration configuration)
    : impl_(std::make_unique<BasicLevelGenerator::Impl>(configuration)) {}

BasicLevelGenerator::~BasicLevelGenerator() = default;

// A method returning generated level.
LevelData BasicLevelGenerator::GenerateLevel() {
  return impl_->GenerateLevel();
}

}  // namespace SceneryGenerator::LevelGenerator