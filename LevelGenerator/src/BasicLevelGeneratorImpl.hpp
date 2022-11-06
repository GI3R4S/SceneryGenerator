#include "BasicLevelGenerator.hpp"

namespace SceneryGenerator {

class BasicLevelGenerator::Impl {
 public:
  Impl(Configuration Configuration);

  ~Impl() = default;

  LevelData GenerateLevel();

 protected:
  LevelData GenerateCityCenter() const;
  LevelData GenerateCityOutskirts() const;
  LevelData GenerateVillage() const;
  LevelData GenerateSettlement() const;
  LevelData GenerateIndustialArea() const;

  //! This function adds network of roads to the level data. Term 'road' includes different types of roads:
  //! - consisted of one or multiple roadways
  //! - including pavement or bikeway along roadway
  //! - green belts
  //! 
  //! Structure of roads is determined depending of scenery type chosen for given level.
  //! Can be used with empty or partially filled level data.
  void AddRoadNetwork(LevelData& level_data, SceneryType scenery_type) const;

 private:
  Configuration configuration_;
};

};  // namespace SceneryGenerator
