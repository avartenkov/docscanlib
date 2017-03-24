#include <iostream>
#include <array>

#include "scan_lib.hpp"
#include "scan_lib_test.hpp"



// TEMP
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
// END TEMP

const double EDGE_THRESHOLD1 = 1.0;
const double EDGE_THRESHOLD2 = 2.0;
const size_t NUM_ANGLES = 4u;

namespace scanlib {

typedef std::array<double, 3> Vec3;


Vec3 get_vec(const Point &pt) {
    return {pt.x, pt.y, 1.0};
}


std::vector<Point> get_document_rectangle(const Image &image)
{
    /*
    cv::Mat mat(image.height, image.width, CV_8UC(image.channels), image.data);
    cv::Mat edges;
    cv::Canny(mat, edges, EDGE_THRESHOLD1, EDGE_THRESHOLD2);*/
    return {};
}



Vec3 cross(const Vec3 &a, const Vec3 &b)
{
    return {a[1] * b[2] - b[1] * a[2],
            a[2] * b[0] - b[2] * a[0],
            a[0] * b[1] - b[0] * a[1]};
}


double dot(const Vec3 &a, const Vec3 &b)
{
    return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}



double norm(const Vec3 &a)
{
    return std::sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
}


Vec3 operator*(double k, const Vec3 &a)
{
    return {a[0] * k, a[1] * k, a[2] * k};
}


inline Vec3 operator*(const Vec3 &a, double k)
{
    return k * a;
}


Vec3 operator+ (const Vec3 &a, const Vec3 &b)
{
    return {a[0] + b[0], a[1] + b[1], a[2] + b[2]};
}


Vec3 operator- (const Vec3 &a, const Vec3 &b)
{
    return {a[0] - b[0], a[1] - b[1], a[2] - b[2]};
}


Vec3 operator- (const Vec3 &a) {
    return -1.0 * a;
}


void sort_points_clockwise(std::vector<Point> &points)
{
    // Finding a central point
    double x_avg = 0.0, y_avg = 0.0;
    for (auto &pt : points) {
        x_avg += pt.x;
        y_avg += pt.y;
    }
    x_avg /= points.size();
    y_avg /= points.size();

    typedef std::pair<Point, double> Pos;

    std::vector<Pos> angles;

    for (const auto &pt : points) {
        angles.push_back(std::make_pair(pt, std::atan2(pt.y - y_avg, pt.x - x_avg)));
    }
    std::sort(angles.begin(), angles.end(),
              [](const Pos &p1, const Pos &p2) {return p1.second < p2.second;});

    for (size_t i = 0; i < points.size(); ++i) {
        points[i] = angles[i].first;
    }
}



double get_h_w_ratio(const std::vector<Point> &points, int img_width, int img_height,
                     double focus)
{
    if (points.size() != NUM_ANGLES) {
        throw std::logic_error("Wrong number of points in a get_w_h_ratio "\
                               "quadrangle");
    }

    std::vector<Point> pts = points;
    sort_points_clockwise(pts);

    std::array<Vec3, NUM_ANGLES> v;

    for (size_t i = 0; i < NUM_ANGLES; ++i) {
        v[i] = get_vec(pts[i]);
    }
    // TODO: Check v[1] x v[2] != 0, process this situation (it's okay)



    std::array<double, 4> k;
    k[0] = 1.0;
    k[1] = dot(cross(v[0], v[2]), v[3]) / dot(cross(v[1], v[2]), v[3]);
    k[2] = dot(cross(v[0], v[1]), v[3]) / dot(cross(v[1], v[2]), v[3]);
    k[3] = dot(cross(v[0], v[2]), v[1]) / dot(cross(v[3], v[2]), v[1]);

    std::cout << k[0] << " " << k[1] << " " << k[2] << " "
              << k[3] << std::endl;

    Vec3 buf_v0 = k[3] * v[3] - v[0]
                  - (k[3] - 1) * Vec3{img_width / 2.0, img_height / 2.0, 0.0};
    buf_v0[2] *= focus;
    Vec3 buf_v1 = k[1] * v[1] - v[0]
                  - (k[1] - 1) * Vec3{img_width / 2.0, img_height / 2.0, 0.0};
    buf_v1[2] *= focus;

    std::cout << "Buf0: " << buf_v0[0] << " " << buf_v0[1] << " " << buf_v0[2]
              << "\nBuf1: " << buf_v1[0] << " " << buf_v1[1] << " " << buf_v1[2]
              << std::endl;

    double x0 = norm(buf_v0);
    double x1 = norm(buf_v1);

    return x0 / x1;




}



Image restore_image_size(const Image &image,
                         const std::vector<Point> &points,
                         const Size result_size)
{


}


Image postprocess(const Image &image, int options)
{


}
} // namespace scanlib
