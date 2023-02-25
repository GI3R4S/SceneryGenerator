#include "RoadNetworkBuilder.hpp"

#include <algorithm>
#include <cassert>
#include <map>
#include <memory>
#include <set>

#include "BasicLevelGeneratorImpl.hpp"
#include "RandomNumberGenerator.hpp"

namespace SceneryGenerator::LevelGenerator {

namespace {

const std::map<SceneryType, std::pair<float, float>> kRoadCoverageMap{
    {SceneryType::kCityCenter, {0.1f, 0.2f}},
    {SceneryType::kCityOutskirts, {0.05f, 0.15f}},
    {SceneryType::kVillage, {0.01f, 0.05f}},
    {SceneryType::kSettlement, {0.05f, 0.15f}},
    {SceneryType::kIndustialArea, {0.1f, 0.2f}}};

const std::map<SceneryType, std::set<RoadType>> kRoadTypesMap{
    {SceneryType::kCityCenter,
     {
         kAlley,
         kNormalRoad,
         kMultilaneRoadway,
     }},
    {SceneryType::kCityOutskirts,
     {
         kSuburbanRoad,
         kNarrowRoad,
         kNormalRoad,
     }},
    {SceneryType::kVillage,
     {
         kDirtRoad,
         kNarrowRoad,
         kNormalRoad,
     }},
    {SceneryType::kSettlement,
     {
         kNarrowRoad,
         kNormalRoad,
     }},
    {SceneryType::kIndustialArea,
     {
         kNarrowRoad,
         kNormalRoad,
         kHighway,
     }}};

// Average lane width will be set to 3.5 m(350 cm)
constexpr double kLaneWidth = 350;

constexpr double kMinimalIntersectionInterval = kLaneWidth * 10;
}  // namespace

class ParentSelector {
 public:
  ParentSelector(std::vector<std::vector<RoadGraphElement>>& road_graph) {
    for (auto& road_graph_vector : road_graph) {
      for (auto& road_graph_element : road_graph_vector) {
        flatenned_road_graph_elements_.push_back(road_graph_element);
      }
    }

    assert(flatenned_road_graph_elements_.size() > 0);

    parent_randomizer_ = std::make_unique<Utils::RandomNumberGenerator<size_t>>(
        std::pair<size_t, size_t>{0,
                                  flatenned_road_graph_elements_.size() - 1});
  }

  RoadGraphElement& SelectRandomParent() {
    return flatenned_road_graph_elements_[parent_randomizer_->GetNumber()];
  };

 private:
  std::unique_ptr<Utils::RandomNumberGenerator<size_t>> parent_randomizer_;
  std::vector<std::reference_wrapper<RoadGraphElement>>
      flatenned_road_graph_elements_;
};

void RoadNetworkBuilder::BuildRoadNetwork() {
  if (road_graph_.empty()) {
    AddFirstRoad();
  }

  while (CheckAreaCoverage(level_data_, ObjectType::kRoad) <
         kRoadCoverageMap.at(scenery_type_).first) {
    ExtendRoadNetwork();
  };
}

void RoadNetworkBuilder::AddFirstRoad() {
  assert(road_graph_.empty());

  const auto& allowed_road_types = kRoadTypesMap.at(scenery_type_);
  const auto terrain_it =
      std::find_if(level_data_.objects.cbegin(), level_data_.objects.cend(),
                   [](const Object& object) {
                     return object.object_type == ObjectType::kTerrain;
                   });

  if (terrain_it == level_data_.objects.cend()) {
    return;
  }

  auto terrain_x_values = terrain_it->GetXDimensionValues();
  auto terrain_z_values = terrain_it->GetZDimensionValues();

  const auto terrain_min_x_value =
      *std::min_element(terrain_x_values.cbegin(), terrain_x_values.cend());
  const auto terrain_max_x_value =
      *std::max_element(terrain_x_values.cbegin(), terrain_x_values.cend());

  const auto terrain_min_z_value =
      *std::min_element(terrain_z_values.cbegin(), terrain_z_values.cend());
  const auto terrain_max_z_value =
      *std::max_element(terrain_z_values.cbegin(), terrain_z_values.cend());

  const auto terrain_x_width =
      std::abs(terrain_max_x_value - terrain_min_x_value);
  const auto terrain_z_width =
      std::abs(terrain_max_z_value - terrain_min_z_value);

  Utils::RandomNumberGenerator<int16_t> flag_randomizer({0, 1});
  Utils::RandomNumberGenerator<int16_t> road_type_randomizer(
      {0, allowed_road_types.size() - 1});

  bool is_horizontal_road = static_cast<bool>(flag_randomizer.GetNumber());
  const auto road_type =
      *std::max_element(allowed_road_types.begin(), allowed_road_types.end());

  if (is_horizontal_road) {
    Utils::RandomNumberGenerator<int64_t> z_randomizer(
        {0.1 * terrain_z_width, 0.9 * terrain_z_width});
    const auto z_axis = z_randomizer.GetNumber();
    road_graph_.push_back({RoadGraphElement{
        road_type,
        {{terrain_min_x_value, 0, z_axis}, {terrain_max_x_value, 0, z_axis}}}});
  } else {
    Utils::RandomNumberGenerator<int64_t> x_randomizer(
        {0.1 * terrain_x_width, 0.9 * terrain_x_width});
    const auto x_axis = x_randomizer.GetNumber();
    road_graph_.push_back({RoadGraphElement{
        road_type,
        {{x_axis, 0, terrain_min_z_value}, {x_axis, 0, terrain_max_z_value}}}});
  }

  const auto& latest_road_graph_generation = road_graph_.back();
  assert(latest_road_graph_generation.size() == 1);

  level_data_.objects.push_back(
      BuildRoadObject(latest_road_graph_generation.front()));
}

void RoadNetworkBuilder::ExtendRoadNetwork() {
  assert(!road_graph_.empty());

  Utils::RandomNumberGenerator<int16_t> number_of_new_roads_randomizer({1, 5});

  int16_t number_of_roads_to_be_created =
      number_of_new_roads_randomizer.GetNumber();

  constexpr uint64_t kMaxNumberOfFaildedAttempts = 100;
  uint64_t number_of_failed_attempts = 0;

  ParentSelector parent_selector(road_graph_);

  while (number_of_roads_to_be_created) {
    auto& parent = parent_selector.SelectRandomParent();

    if (parent.vertexes.size() < 2) {
      std::cerr << "Skipping parent due to invalid number of vertexes."
                << std::endl;
      continue;
    }

    size_t selected_segment = 0;

    if (parent.vertexes.size() > 2) {
      Utils::RandomNumberGenerator<size_t> segment_randomizer(
          {0, parent.vertexes.size() - 2});
      const auto selected_segment = segment_randomizer.GetNumber();
    }

    const Vertex intersection_candidate =
        GenerateIntersectionCandidate(parent.vertexes[selected_segment],
                                      parent.vertexes[selected_segment + 1]);

    if (!IsIntersectionIntervalCorrect(parent, intersection_candidate)) {
      ++number_of_failed_attempts;
      if (number_of_failed_attempts > kMaxNumberOfFaildedAttempts) {
        break;
      }
      continue;
    }

    number_of_failed_attempts = 0;
    // TODO
  };
}

std::vector<Vertex> GenerateRoadObjectVertexes(
    const std::vector<Vertex>& road_graph_element_vertexes, double width) {
  assert(width >= 0);

  std::vector<Vertex> road_vertexes;

  // Iterate over vertexes of road graph element.
  // Each iteration continously processes pair of adjacent vertexes.
  // Each pair of processed vertexes produces 4 vertexes of road object.
  for (int i = 0; i < road_graph_element_vertexes.size() - 1; ++i) {
    const Vertex& first_vertex = road_graph_element_vertexes[i];
    const Vertex& second_vertex = road_graph_element_vertexes[i + 1];

    const int64_t x_diff = second_vertex.x - first_vertex.x;
    const int64_t z_diff = second_vertex.z - first_vertex.z;
    const int64_t half_width = std::round(width / 2.0);

    if (x_diff != 0) {
      if (z_diff == 0) {
        Vertex first_vertex_first_child{first_vertex.x, first_vertex.y,
                                        first_vertex.z - half_width};
        Vertex first_vertex_second_child{first_vertex.x, first_vertex.y,
                                         first_vertex.z + half_width};

        Vertex second_vertex_first_child{second_vertex.x, second_vertex.y,
                                         second_vertex.z - half_width};
        Vertex second_vertex_second_child{second_vertex.x, second_vertex.y,
                                          second_vertex.z + half_width};

        road_vertexes.push_back(first_vertex_first_child);
        road_vertexes.push_back(first_vertex_second_child);
        road_vertexes.push_back(second_vertex_first_child);
        road_vertexes.push_back(second_vertex_second_child);
      } else {
        const double a_factor = (z_diff) / (x_diff);
        const double perpendicular_a_factor = -1.0 / a_factor;
        const double perpendicular_b_factor =
            first_vertex.z - perpendicular_a_factor * first_vertex.x;

        const double perpendicular_x_diff =
            width / std::abs(perpendicular_a_factor);

        Vertex first_vertex_first_child{
            static_cast<int64_t>(first_vertex.x - perpendicular_x_diff),  //
            first_vertex.y,                                               //
            static_cast<int64_t>(perpendicular_a_factor *
                                     (first_vertex.x - perpendicular_x_diff) +
                                 perpendicular_b_factor)  //
        };
        Vertex first_vertex_second_child{
            static_cast<int64_t>(first_vertex.x + perpendicular_x_diff),  //
            first_vertex.y,                                               //
            static_cast<int64_t>(perpendicular_a_factor *
                                     (first_vertex.x + perpendicular_x_diff) +
                                 perpendicular_b_factor)  //
        };

        Vertex second_vertex_first_child{
            static_cast<int64_t>(second_vertex.x - perpendicular_x_diff),  //
            second_vertex.y,                                               //
            static_cast<int64_t>(perpendicular_a_factor *
                                     (second_vertex.x - perpendicular_x_diff) +
                                 perpendicular_b_factor)  //
        };
        Vertex second_vertex_second_child{
            static_cast<int64_t>(second_vertex.x + perpendicular_x_diff),  //
            second_vertex.y,                                               //
            static_cast<int64_t>(perpendicular_a_factor *
                                     (second_vertex.x + perpendicular_x_diff) +
                                 perpendicular_b_factor)  //
        };

        road_vertexes.push_back(first_vertex_first_child);
        road_vertexes.push_back(first_vertex_second_child);
        road_vertexes.push_back(second_vertex_first_child);
        road_vertexes.push_back(second_vertex_second_child);
      }
    } else if (z_diff != 0) {
      Vertex first_vertex_first_child{first_vertex.x - half_width,
                                      first_vertex.y, first_vertex.z};
      Vertex first_vertex_second_child{first_vertex.x + half_width,
                                       first_vertex.y, first_vertex.z};

      Vertex second_vertex_first_child{second_vertex.x - half_width,
                                       second_vertex.y, second_vertex.z};
      Vertex second_vertex_second_child{second_vertex.x + half_width,
                                        second_vertex.y, second_vertex.z};

      road_vertexes.push_back(first_vertex_first_child);
      road_vertexes.push_back(first_vertex_second_child);
      road_vertexes.push_back(second_vertex_first_child);
      road_vertexes.push_back(second_vertex_second_child);
    }
  }

  return std::move(road_vertexes);
}

Object BuildRoadObject(const RoadGraphElement& road_graph_element) {
  double width = 0;

  // Temporary predicted widths. No green belts, pavements and other elements
  // are included.
  switch (road_graph_element.road_type) {
    case kAlley: {
      width = kLaneWidth;
      break;
    }
    case kDirtRoad: {
      width = kLaneWidth * 1.5;
      break;
    }
    case kSuburbanRoad: {
      width = kLaneWidth * 1.5;
      break;
    }
    case kNarrowRoad: {
      width = kLaneWidth;
      break;
    }
    case kNormalRoad: {
      width = kLaneWidth * 2;
      break;
    }
    case kMultilaneRoadway: {
      Utils::RandomNumberGenerator<int> number_of_lanes_rng({2, 4});
      const auto no_of_lanes_in_one_direction = number_of_lanes_rng.GetNumber();
      width = no_of_lanes_in_one_direction * 2 * kLaneWidth;
      break;
    }
    case kHighway: {
      Utils::RandomNumberGenerator<int> number_of_lanes_rng({2, 4});
      const auto no_of_lanes_in_one_direction = number_of_lanes_rng.GetNumber();
      width = no_of_lanes_in_one_direction * 2 * kLaneWidth;
      break;
    }
  }

  Object road_object{
      ObjectType::kRoad,
      GenerateRoadObjectVertexes(road_graph_element.vertexes, width)};

  return std::move(road_object);
}

Vertex GenerateIntersectionCandidate(const Vertex& start_vertex,
                                     const Vertex& end_vertex) {
  const int64_t x_diff = end_vertex.x - start_vertex.x;
  const int64_t z_diff = end_vertex.z - start_vertex.z;

  const double a_factor = (z_diff) / (x_diff);
  const double b_factor = start_vertex.z - a_factor * start_vertex.x;

  Utils::RandomNumberGenerator<int64_t> x_randomizer(
      {start_vertex.x, end_vertex.x});
  const int64_t randomized_x = x_randomizer.GetNumber();

  return {randomized_x, 0,
          static_cast<int64_t>(std::round(a_factor * randomized_x + b_factor))};
}

bool IsIntersectionIntervalCorrect(const RoadGraphElement& parent,
                                   const Vertex& intersection_candidate) {
  std::map<std::reference_wrapper<Vertex>, double> distances;

  for (auto& [road_segment_no, intersections] : parent.intersections) {
    for (auto& intersection : intersections) {
      distances.emplace(
          intersection,
          CartesianDistance(intersection, intersection_candidate));
    }
  }

  return std::all_of(distances.cbegin(), distances.cend(),
                     [](const auto& pair) {
                       return pair.second <= kMinimalIntersectionInterval;
                     });
}

}  // namespace SceneryGenerator::LevelGenerator
