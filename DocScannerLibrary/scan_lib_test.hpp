#ifndef SCAN_LIB_TEST_HPP
#define SCAN_LIB_TEST_HPP
#include "scan_lib.hpp"

namespace scanlib {
    void sort_points_clockwise(std::vector<Point> &points);
    double get_h_w_ratio(const std::vector<Point> &points,
                         int img_width, int img_height, double focus);
}
#endif // SCAN_LIB_TEST_HPP
