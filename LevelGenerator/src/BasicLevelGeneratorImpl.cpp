#include "BasicLevelGeneratorImpl.hpp"

#include <map>
#include <set>

namespace SceneryGenerator {

namespace {
const std::map<SceneryType, std::set<ObjectType>>
    kObjectTypesToSceneryTypeMapping{
        {SceneryType::kCityCenter,
         {ObjectType::kBuilding, ObjectType::kRoad, ObjectType::kPavement}},
        {SceneryType::kCityOutskirts,
         {ObjectType::kBuilding, ObjectType::kRoad, ObjectType::kPavement,
          ObjectType::kMeadow}},
        {SceneryType::kCountryside,
         {ObjectType::kBuilding, ObjectType::kRoad, ObjectType::kPath,
          ObjectType::kRiver, ObjectType::kField, ObjectType::kMeadow}},
        {SceneryType::kIndustialArea,
         {ObjectType::kBuilding, ObjectType::kRoad, ObjectType::kPavement}}};
}

BasicLevelGenerator::Impl::Impl(Configuration configuration)
    : configuration_(std::move(configuration)) {}

LevelData BasicLevelGenerator::Impl::GenerateCityCenter(){
    
}

LevelData BasicLevelGenerator::Impl::GenerateLevel() { 


    
    
    return {}; }

}  // namespace SceneryGenerator
