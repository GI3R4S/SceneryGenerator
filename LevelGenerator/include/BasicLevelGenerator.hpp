#include <cstdint>

#include "LevelGenerator.hpp"

namespace SceneryGenerator {

//! Basic implementation of level generator.
class BasicLevelGenerator : public LevelGenerator {
 public:
  //! Structure allowing to inject parameters required to parametrize
  //! BasicLevelGenerator
  struct Configuration {

    //! Minimal vertex for generated level. It is required for both minimalVertex and maximalVertex to have same 'y' value. 
    std::int32_t minimalVertex;

    //!Maximal vertex for generated level. It is required for both minimalVertex and maximalVertex to have same 'y' value.
    std::int32_t maximalVertex;
  };

  // A method returning generated level.
  virtual LevelData GenerateLevel() override;
};

}  // namespace SceneryGenerator