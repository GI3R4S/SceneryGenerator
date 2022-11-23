#include "BasicLevelGeneratorImpl.hpp"

#include <algorithm>
#include <cmath>
#include <map>
#include <memory>
#include <random>
#include <set>

#include "RandomNumberGenerator.hpp"

namespace SceneryGenerator::LevelGenerator {

namespace {
const std::map<SceneryType, std::pair<float, float>> kRoadCoverageMap{
    {SceneryType::kCityCenter, {0.1f, 0.2f}},
    {SceneryType::kCityOutskirts, {0.05f, 0.15f}},
    {SceneryType::kVillage, {0.01f, 0.05f}},
    {SceneryType::kSettlement, {0.05f, 0.15f}},
    {SceneryType::kIndustialArea, {0.1f, 0.2f}}};

}  // namespace

BasicLevelGeneratorImpl::BasicLevelGeneratorImpl(
    BasicLevelGenerator::Configuration configuration)
    : configuration_(std::move(configuration)) {}

LevelData BasicLevelGeneratorImpl::GenerateLevel() {
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

void BasicLevelGeneratorImpl::AddTerrain(LevelData& level_data) const {
  bool is_terrain_initialized =
      std::find_if(level_data.objects.cbegin(), level_data.objects.cend(),
                   [](const Object& object) {
                     return object.object_type == ObjectType::kTerrain;
                   }) != level_data.objects.cend();

  if (is_terrain_initialized) {
    return;
  }
  const auto size_of_map_in_square_centimeters =
      configuration_.size_of_map * 10000;

  double root = sqrt(size_of_map_in_square_centimeters);

  Utils::RandomNumberGenerator<double> rng({0.2 * root, 0.8 * root});
  auto first_side = rng.GetNumber();
  auto second_side = size_of_map_in_square_centimeters / first_side;

  first_side = round(first_side);
  second_side = round(second_side);

  Object object;
  object.object_type = ObjectType::kTerrain;
  object.vertexes = {
      {0, 0, 0},
      {static_cast<int64_t>(first_side), 0, 0},
      {static_cast<int64_t>(first_side), 0, static_cast<int64_t>(second_side)},
      {0, 0, static_cast<int64_t>(second_side)},
  };

  level_data.objects.push_back(object);
}

LevelData BasicLevelGeneratorImpl::GenerateCityCenter(
    LevelData& level_data) const {
  return level_data;
}

LevelData BasicLevelGeneratorImpl::GenerateCityOutskirts(
    LevelData& level_data) const {
  return level_data;
}
LevelData BasicLevelGeneratorImpl::GenerateVillage(
    LevelData& level_data) const {
  return level_data;
}

LevelData BasicLevelGeneratorImpl::GenerateSettlement(
    LevelData& level_data) const {
  return level_data;
}

LevelData BasicLevelGeneratorImpl::GenerateIndustialArea(
    LevelData& level_data) const {
  return level_data;
}

void BasicLevelGeneratorImpl::AddRoadNetwork(LevelData& level_data,
                                             SceneryType scenery_type) const {
  //! If level data is empty, architecture of level will be decided with road
  //! distribution.
  if (level_data.objects.empty()) {
  }
}

}  // namespace SceneryGenerator::LevelGenerator
