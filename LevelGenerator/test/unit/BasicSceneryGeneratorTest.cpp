#include <gtest/gtest.h>

#include <algorithm>
#include <limits>
#include <set>
#include <unordered_set>

#include "BasicLevelGenerator.hpp"
#include "BasicLevelGeneratorImpl.hpp"
#include "GeometryUtils.hpp"

namespace SceneryGenerator::LevelGenerator::Test {

namespace {
constexpr double kSizeOfMap = 20000;
constexpr double kMaxSizeDifference = kSizeOfMap * 0.001;
constexpr double kNumberOfIterations = 1000;

}  // namespace

TEST(BasicSceneryGeneratorTest, GeneratedLevelTerrainMustHaveCorrectSize) {
  BasicLevelGenerator::Configuration config;
  config.scenery_type = SceneryType::kSettlement;
  config.size_of_map = kSizeOfMap;

  BasicLevelGeneratorImpl basic_level_generator_impl(config);
  LevelData level_data;

  for (int i = 0; i < kNumberOfIterations; ++i) {
    level_data.objects.clear();
    basic_level_generator_impl.AddTerrain(level_data);

    auto terrain_object_it =
        std::find_if(level_data.objects.cbegin(), level_data.objects.cend(),
                     [](const Object& object) {
                       return object.object_type == ObjectType::kTerrain;
                     });

    ASSERT_TRUE(terrain_object_it != level_data.objects.cend());

    double size =
        Utils::Compute2dPolygonSize(terrain_object_it->GetXDimensionValues(),
                                    terrain_object_it->GetZDimensionValues()) /
        10000.0;

    double size_difference = abs(size - config.size_of_map);

    EXPECT_LT(size_difference, kMaxSizeDifference);
  }
}

}  // namespace SceneryGenerator::LevelGenerator::Test