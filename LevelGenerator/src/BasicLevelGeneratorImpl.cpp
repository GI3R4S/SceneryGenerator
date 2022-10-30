#include "BasicLevelGeneratorImpl.hpp"

namespace SceneryGenerator {

BasicLevelGenerator::Impl::Impl(Configuration configuration)
    : configuration_(std::move(configuration)) {}

LevelData BasicLevelGenerator::Impl::GenerateLevel() { return {}; }

}  // namespace SceneryGenerator
