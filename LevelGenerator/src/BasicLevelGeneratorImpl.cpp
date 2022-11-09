#include "BasicLevelGeneratorImpl.hpp"

#include <algorithm>
#include <map>
#include <memory>
#include <random>
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

class RandomIntegerGenerator {
 public:
  RandomIntegerGenerator(std::pair<int64_t, int64_t> range)
      : min_(std::min(range.first, range.second)),
        max_(std::max(range.first, range.second)),
        random_device_(),
        random_engine_(random_device_()),
        distribution_(min_, max_) {}

  int64_t GetInteger() { return distribution_(random_engine_); }

  std::vector<int64_t> GetIntegers(int number_of_integers) {
    std::vector<int64_t> integers;
    while (number_of_integers--) {
      integers.push_back(distribution_(random_engine_));
    };

    return integers;
  }

 private:
  int64_t min_;
  int64_t max_;
  std::random_device random_device_;
  std::mt19937 random_engine_;
  std::uniform_int_distribution<int64_t> distribution_;
};

BasicLevelGenerator::Impl::Impl(Configuration configuration)
    : configuration_(std::move(configuration)) {}

LevelData BasicLevelGenerator::Impl::GenerateLevel() {
  LevelData level_data;

  AddTerrain(level_data);

  switch (configuration_.scenery_type) {
    case SceneryType::kCityCenter: {
      return GenerateCityCenter(level_data);
    }
    case SceneryType::kCityOutskirts: {
      return GenerateCityOutskirts(level_data);
    }
    case SceneryType::kVillage: {
      return GenerateVillage(level_data);
    }
    case SceneryType::kSettlement: {
      return GenerateSettlement(level_data);
    }
    case SceneryType::kIndustialArea: {
      return GenerateIndustialArea(level_data);
    }
  }
  return {};
}

void BasicLevelGenerator::Impl::AddTerrain(LevelData& level_data) const {
  bool is_terrain_initialized =
      std::find_if(level_data.objects.cbegin(), level_data.objects.cend(),
                   [](const Object& object) {
                     return object.object_type == ObjectType::kTerrain;
                   }) != level_data.objects.cend();

  if (is_terrain_initialized) {
    return;
  }
}

LevelData BasicLevelGenerator::Impl::GenerateCityCenter(
    LevelData& level_data) const {
  return level_data;
}

LevelData BasicLevelGenerator::Impl::GenerateCityOutskirts(
    LevelData& level_data) const {
  return level_data;
}
LevelData BasicLevelGenerator::Impl::GenerateVillage(
    LevelData& level_data) const {
  return level_data;
}

LevelData BasicLevelGenerator::Impl::GenerateSettlement(
    LevelData& level_data) const {
  return level_data;
}

LevelData BasicLevelGenerator::Impl::GenerateIndustialArea(
    LevelData& level_data) const {
  return level_data;
}

void BasicLevelGenerator::Impl::AddRoadNetwork(LevelData& level_data,
                                               SceneryType scenery_type) const {
  //! If level data is empty, architecture of level will be decided with road
  //! distribution.
  if (level_data.objects.empty()) {
  }
}

}  // namespace SceneryGenerator
