#ifndef SCENERY_GENERATOR_LEVEL_GENERATOR_BASIC_LEVEL_GENERATOR_HPP
#define SCENERY_GENERATOR_LEVEL_GENERATOR_BASIC_LEVEL_GENERATOR_HPP

#include <cstdint>
#include <memory>
#include <set>

#include "LevelGenerator.hpp"

namespace SceneryGenerator {

//! Basic implementation of level generator.
class BasicLevelGenerator : public LevelGenerator {
 public:
  //!
  //! Structure allowing to inject parameters required to parametrize
  //! BasicLevelGenerator. Current assumption is that all object has base at
  //! same 'y' value.
  struct Configuration {
    //! Minimal vertex for generated level. It is required for both
    //! minimal_vertex and maximal_vertex to have same 'y' value.
    std::int32_t minimal_vertex;

    //! Maximal vertex for generated level. It is required for both
    //! minimal_vertex and maximal_vertex to have same 'y' value.
    std::int32_t maximal_vertex;

    //! Type of scenery to be generated.
    SceneryType scenery_type;
  };

  //! Constructor for the BasicLevelGenerator.
  BasicLevelGenerator(Configuration configuration);

  //! Destructor for the BasicLevelGenerator.
  ~BasicLevelGenerator();

  // A method returning generated level.
  virtual LevelData GenerateLevel() override;

 private:
  class Impl;
  std::unique_ptr<Impl> impl_;
};

}  // namespace SceneryGenerator

#endif