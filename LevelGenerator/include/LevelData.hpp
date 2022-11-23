#ifndef SCENERY_GENERATOR_LEVEL_GENERATOR_LEVEL_DATA_HPP
#define SCENERY_GENERATOR_LEVEL_GENERATOR_LEVEL_DATA_HPP

#include <cstdint>
#include <iostream>
#include <vector>

namespace SceneryGenerator::LevelGenerator {

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
  int64_t x;

  //! Position of vertex on y axis.
  int64_t y;

  //! Position of vertex on z axis.
  int64_t z;
};

//! Representation of level's object
struct Object {
  //! Type of object.
  ObjectType object_type;

  //! List of vertexes forming object.
  std::vector<Vertex> vertexes;

  //! Extracts values of vertexex in `X` dimension.
  std::vector<int64_t> GetXDimensionValues() const;

  //! Extracts values of vertexex in `Y` dimension.
  std::vector<int64_t> GetYDimensionValues() const;

  //! Extracts values of vertexex in `Z` dimension.
  std::vector<int64_t> GetZDimensionValues() const;
};

//! Structure holding data relevant for generated level.
struct LevelData {
  // List of object that is available in scope of this level.
  std::vector<Object> objects;
};

std::ostream& operator<<(std::ostream& stream, const ObjectType& object_type);
std::ostream& operator<<(std::ostream& stream, const Vertex& vertex);
std::ostream& operator<<(std::ostream& stream, const Object& object);
std::ostream& operator<<(std::ostream& stream, const LevelData& level_data);

}  // namespace SceneryGenerator::LevelGenerator

#endif