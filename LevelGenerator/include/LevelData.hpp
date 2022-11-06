#ifndef SCENERY_GENERATOR_LEVEL_GENERATOR_LEVEL_DATA_HPP
#define SCENERY_GENERATOR_LEVEL_GENERATOR_LEVEL_DATA_HPP

#include <cstdint>
#include <vector>

namespace SceneryGenerator {

//! Type of scenery.
enum class SceneryType {
  kCityCenter,
  kCityOutskirts,
  kIndustialArea,
  kSettlement,
  kVillage
};

//! Type of object.
enum class ObjectType {
  kBuilding,
  kRoad,
  kRiver,
  kPath,
  kPavement,
  kField,
  kTerrain,
  kFence,
  kMeadow
};

//! Representation of vertex.
struct Vertex {
  //! Position of vertex on x axis.
  std::int32_t x;

  //! Position of vertex on y axis.
  std::int32_t y;

  //! Position of vertex on z axis.
  std::int32_t z;
};

//! Representation of level's object
struct Object {
  //! Type of object.
  ObjectType object_type;

  //! List of vertexes forming object.
  std::vector<Vertex> vertexes;
};

//! Structure holding data relevant for generated level.
struct LevelData {
  //! Default value for axis y. Generated structures
  //! will have base at this y axis value.
  std::int32_t default_y_value;

  // List of object that is available in scope of this level.
  std::vector<Object> objects;
};
}  // namespace SceneryGenerator

#endif