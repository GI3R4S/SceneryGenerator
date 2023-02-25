#include "BasicLevelGeneratorImpl.hpp"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <map>
#include <memory>
#include <random>
#include <set>

#include "GeometryUtils.hpp"
#include "RandomNumberGenerator.hpp"
#include "RoadNetworkBuilder.hpp"
namespace SceneryGenerator::LevelGenerator {

BasicLevelGeneratorImpl::BasicLevelGeneratorImpl(
    BasicLevelGenerator::Configuration configuration)
    : configuration_(std::move(configuration)) {}

LevelData BasicLevelGeneratorImpl::GenerateLevel() {
  LevelData level_data;

  AddTerrain(level_data);
  AddRoadNetwork(level_data);

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

void BasicLevelGeneratorImpl::AddRoadNetwork(LevelData& level_data) const {
  auto terrain_object_it =
      std::find_if(level_data.objects.cbegin(), level_data.objects.cend(),
                   [](const Object& object) {
                     return object.object_type == ObjectType::kTerrain;
                   });

  if (terrain_object_it == level_data.objects.cend()) {
    return;
  }

  RoadNetworkBuilder road_network_builder(
      level_data, configuration_.scenery_type);
  road_network_builder.BuildRoadNetwork();

  switch (configuration_.scenery_type) {
    case SceneryType::kCityCenter: {
      break;
    }
    case SceneryType::kCityOutskirts: {
      break;
    }
    case SceneryType::kIndustialArea: {
      break;
    }
    case SceneryType::kSettlement: {
      break;
    }
    case SceneryType::kVillage: {
      break;
    }
  }
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

//! Checks terrain coverage against chosen object type.
double CheckAreaCoverage(LevelData& level_data, ObjectType object_type) {
  auto terrain_object_it =
      std::find_if(level_data.objects.cbegin(), level_data.objects.cend(),
                   [](const Object& object) {
                     return object.object_type == ObjectType::kTerrain;
                   });

  assert(terrain_object_it != level_data.objects.cend());

  const auto terrain_size =
      Utils::Compute2dPolygonSize(terrain_object_it->GetXDimensionValues(),
                                  terrain_object_it->GetZDimensionValues());

  double total_surface = 0;
  // TODO: there's need to compute correctly intersected areas
  for (const auto& object : level_data.objects) {
    if (object.object_type == object_type) {
      total_surface += Utils::Compute2dPolygonSize(
          object.GetXDimensionValues(), object.GetZDimensionValues());
    }
  }

  return (total_surface / terrain_size) * 100;
}

}  // namespace SceneryGenerator::LevelGenerator
