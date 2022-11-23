#include "GeometryUtils.hpp"

namespace SceneryGenerator::Utils {

double Compute2dPolygonSize(std::vector<int64_t> first_dimension,
                            std::vector<int64_t> second_dimension) {
  assert(first_dimension.size() == second_dimension.size());

  double area = 0.0;

  int j = first_dimension.size() - 1;
  for (int i = 0; i < first_dimension.size(); i++) {
    area += (first_dimension[j] + first_dimension[i]) *
            (second_dimension[j] - second_dimension[i]);
    j = i;
  }

  return std::abs(area / 2.0);
}

}  // namespace SceneryGenerator::Utils
