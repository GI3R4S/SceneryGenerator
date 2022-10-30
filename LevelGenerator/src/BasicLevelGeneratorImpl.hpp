#include "BasicLevelGenerator.hpp"

namespace SceneryGenerator {

class BasicLevelGenerator::Impl {
 public:
  Impl(Configuration Configuration);

  ~Impl() = default;

  LevelData GenerateLevel();

 private:
  Configuration configuration_;
};
};  // namespace SceneryGenerator
