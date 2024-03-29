#ifndef SCENERY_GENERATOR_LEVEL_GENERATOR_BASICLEVELGENERATORIMPL_HPP_HPP
#define SCENERY_GENERATOR_LEVEL_GENERATOR_BASICLEVELGENERATORIMPL_HPP_HPP

#include "BasicLevelGenerator.hpp"

namespace SceneryGenerator::LevelGenerator {

class BasicLevelGeneratorImpl {
 public:
  BasicLevelGeneratorImpl(BasicLevelGenerator::Configuration configuration);

  ~BasicLevelGeneratorImpl() = default;

  LevelData GenerateLevel();
  LevelData GenerateCityCenter(LevelData& level_data) const;
  LevelData GenerateCityOutskirts(LevelData& level_data) const;
  LevelData GenerateVillage(LevelData& level_data) const;
  LevelData GenerateSettlement(LevelData& level_data) const;
  LevelData GenerateIndustialArea(LevelData& level_data) const;

  //! Adds terrain to the level. Currently supported terrain shape is flat
  //! surface. Creates object of type kTerrain to match level size expectation
  void AddTerrain(LevelData& level_data) const;

  //! This function adds network of roads to the level data. Term 'road'
  //! includes different types of roads:
  //! - consisted of one or multiple roadways
  //! - including pavement or bikeway along roadway
  //! - green belts
  //!
  //! Structure of roads is determined depending of scenery type chosen for
  //! given level. Can be used with empty or partially filled level data.
  void AddRoadNetwork(LevelData& level_data) const;

  BasicLevelGenerator::Configuration configuration_;
};

//! Checks terrain coverage against chosen object type.
double CheckAreaCoverage(LevelData& level_data, ObjectType object_type);

};  // namespace SceneryGenerator::LevelGenerator

#endif  // SCENERY_GENERATOR_LEVEL_GENERATOR_BASICLEVELGENERATORIMPL_HPP_HPP