#include "LevelData.hpp"

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <vector>

namespace SceneryGenerator::LevelGenerator {

std::vector<int64_t> Object::GetXDimensionValues() const {
  std::vector<int64_t> x_values(vertexes.size());

  std::for_each(
      vertexes.cbegin(), vertexes.cend(),
      [&x_values](const Vertex& vertex) { x_values.push_back(vertex.x); });

  return std::move(x_values);
}

std::vector<int64_t> Object::GetYDimensionValues() const {
  std::vector<int64_t> y_values(vertexes.size());

  std::for_each(
      vertexes.cbegin(), vertexes.cend(),
      [&y_values](const Vertex& vertex) { y_values.push_back(vertex.y); });

  return std::move(y_values);
}

std::vector<int64_t> Object::GetZDimensionValues() const {
  std::vector<int64_t> z_values(vertexes.size());

  std::for_each(
      vertexes.cbegin(), vertexes.cend(),
      [&z_values](const Vertex& vertex) { z_values.push_back(vertex.z); });

  return std::move(z_values);
}

double CartesianDistance(const Vertex& first_vertex,
                         const Vertex& second_vertex) {
  return std::sqrt(std::pow(second_vertex.x - first_vertex.x, 2) +
                   std::pow(second_vertex.y - first_vertex.y, 2) +
                   std::pow(second_vertex.z - first_vertex.z, 2)
  );
}

std::ostream& operator<<(std::ostream& stream, const ObjectType& object_type) {
  switch (object_type) {
    case ObjectType::kBuilding: {
      stream << "ObjectType::kBuilding";
      break;
    }
    case ObjectType::kRoad: {
      stream << "ObjectType::kRoad";
      break;
    }
    case ObjectType::kRiver: {
      stream << "ObjectType::kRiver";
      break;
    }
    case ObjectType::kPath: {
      stream << "ObjectType::kPath";
      break;
    }
    case ObjectType::kPavement: {
      stream << "ObjectType::kPavement";
      break;
    }
    case ObjectType::kField: {
      stream << "ObjectType::kField";
      break;
    }
    case ObjectType::kTerrain: {
      stream << "ObjectType::kTerrain";
      break;
    }
    case ObjectType::kFence: {
      stream << "ObjectType::kFence";
      break;
    }
    case ObjectType::kMeadow: {
      stream << "ObjectType::kMeadow";
      break;
    }
  }

  return stream;
}

std::ostream& operator<<(std::ostream& stream, const Vertex& vertex) {
  stream << "{x: " << vertex.x << ", y: " << vertex.y << ", z: " << vertex.z
         << " }";
  return stream;
}

std::ostream& operator<<(std::ostream& stream, const Object& object) {
  stream << "{object_type: " << object.object_type << ", vertexes: {";

  for (const Vertex& vertex : object.vertexes) {
    stream << vertex << ", ";
  }

  stream << "}}";

  return stream;
}

std::ostream& operator<<(std::ostream& stream, const LevelData& level_data) {
  stream << "{objects: {";
  for (const Object& object : level_data.objects) {
    stream << object << ", ";
  }

  stream << " }}";

  return stream;
}

}  // namespace SceneryGenerator::LevelGenerator
