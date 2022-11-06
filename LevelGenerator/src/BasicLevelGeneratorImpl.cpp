#include "BasicLevelGeneratorImpl.hpp"

#include <map>
#include <set>

namespace SceneryGenerator {

namespace {
// const std::map<SceneryType, std::set<ObjectType>>
//     kObjectTypesToSceneryTypeMapping{
//         {SceneryType::kCityCenter,
//          {ObjectType::kBuilding, ObjectType::kRoad, ObjectType::kPavement}},
//         {SceneryType::kCityOutskirts,
//          {ObjectType::kBuilding, ObjectType::kRoad, ObjectType::kPavement,
//           ObjectType::kMeadow}},
//         {SceneryType::kCountryside,
//          {ObjectType::kBuilding, ObjectType::kRoad, ObjectType::kPath,
//           ObjectType::kRiver, ObjectType::kField, ObjectType::kMeadow}},
//         {SceneryType::kIndustialArea,
//          {ObjectType::kBuilding, ObjectType::kRoad, ObjectType::kPavement}}};

const std::map<SceneryType, std::pair<float, float>> kRoadCoverageMap{
    {SceneryType::kCityCenter, {0.1f, 0.2f}},
    {SceneryType::kCityOutskirts, {0.05f, 0.15f}},
    {SceneryType::kVillage, {0.01f, 0.05f}},
    {SceneryType::kSettlement, {0.05f, 0.15f}},
    {SceneryType::kIndustialArea, {0.1f, 0.2f}}};

}  // namespace

BasicLevelGenerator::Impl::Impl(Configuration configuration)
    : configuration_(std::move(configuration)) {}

LevelData BasicLevelGenerator::Impl::GenerateLevel() {
  switch (configuration_.scenery_type) {
    case SceneryType::kCityCenter: {
      return GenerateCityCenter();
    }
    case SceneryType::kCityOutskirts: {
      return GenerateCityOutskirts();
    }
    case SceneryType::kVillage: {
      return GenerateVillage();
    }
    case SceneryType::kSettlement: {
      return GenerateSettlement();
    }
    case SceneryType::kIndustialArea: {
      return GenerateIndustialArea();
    }
  }
  return {};
}

LevelData BasicLevelGenerator::Impl::GenerateCityCenter() const {
  LevelData level_data;

  return level_data;
}

LevelData BasicLevelGenerator::Impl::GenerateCityOutskirts() const {
  return {};
}
LevelData BasicLevelGenerator::Impl::GenerateVillage() const { return {}; }

LevelData BasicLevelGenerator::Impl::GenerateSettlement() const { return {}; }

LevelData BasicLevelGenerator::Impl::GenerateIndustialArea() const {
  return {};
}

void BasicLevelGenerator::Impl::AddRoadNetwork(LevelData& level_data,
                                               SceneryType scenery_type) const {
  //! If level data is empty, architecture of level will be decided with road
  //! distribution.
  if (level_data.objects.empty()) {
  }
}

}  // namespace SceneryGenerator
