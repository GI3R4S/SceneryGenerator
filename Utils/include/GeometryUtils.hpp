#ifndef SCENERY_GENERATOR_UTILS_GEOMETRY_UTILS_HPP
#define SCENERY_GENERATOR_UTILS_GEOMETRY_UTILS_HPP

#include <cassert>
#include <cstdlib>
#include <vector>

namespace SceneryGenerator::Utils {


// This function is based on Shoelace formula.
double Compute2dPolygonSize(std::vector<int64_t> first_dimension,
                            std::vector<int64_t> second_dimension);

}  // namespace SceneryGenerator::Utils

#endif  // SCENERY_GENERATOR_UTILS_GEOMETRY_UTILS_HPP