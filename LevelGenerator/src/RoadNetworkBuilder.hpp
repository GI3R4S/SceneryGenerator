#ifndef SCENERY_GENERATOR_LEVEL_GENERATOR_ROADNETWORKBUILDERIMPL_HPP
#define SCENERY_GENERATOR_LEVEL_GENERATOR_ROADNETWORKBUILDERIMPL_HPP

#include <map>
#include <set>

#include "LevelData.hpp"

namespace SceneryGenerator::LevelGenerator {

enum RoadType {
  kAlley = 1,
  kDirtRoad = 2,
  kSuburbanRoad = 3,
  kNarrowRoad = 4,
  kNormalRoad = 5,
  kMultilaneRoadway = 6,
  kHighway = 7,
};

struct RoadGraphElement {
  //! Type of road, determines width of road to be constructed from this
  //! element.
  RoadType road_type;

  //! List of vertexes holding geometry info; used for purpose of routing,
  //! expansion of road network.
  std::vector<Vertex> vertexes;

  //! List of vertexes of intersections. Groups ordinal segment number with
  //! assosciated intersections.
  std::map<size_t, std::set<Vertex>> intersections;
};

class RoadNetworkBuilder {
 public:
  RoadNetworkBuilder(LevelData& level_data, SceneryType scenery_type)
      : level_data_(level_data), scenery_type_(scenery_type) {}

  ~RoadNetworkBuilder() = default;

  void BuildRoadNetwork();

 private:
  void AddFirstRoad();
  void ExtendRoadNetwork();

  LevelData& level_data_;
  SceneryType scenery_type_;
  std::vector<std::vector<RoadGraphElement>> road_graph_;
};

//! Generate road object vertexes for vertexes of simple road graph element.
std::vector<Vertex> GenerateRoadObjectVertexes(
    const std::vector<Vertex>& road_graph_element_vertexes, double width);

Vertex GenerateIntersectionCandidate(const Vertex& start_vertex,
                                     const Vertex& end_vertex);

Object BuildRoadObject(const RoadGraphElement& road_graph_element);

}  // namespace SceneryGenerator::LevelGenerator

#endif  // SCENERY_GENERATOR_LEVEL_GENERATOR_ROADNETWORKBUILDERIMPL_HPP