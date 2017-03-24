#include <iostream>
#include <gtest/gtest.h>

#include <scan_lib_test.hpp>

namespace sl = scanlib;


TEST(SortClockwise, test)
{
    std::vector<sl::Point> pts = {{1, 1}, {-1, 1}, {-1, -1}, {1, -1}};
    std::vector<sl::Point> srt = {{-1, -1}, {1, -1}, {1, 1}, {-1, 1}};
    sl::sort_points_clockwise(pts);

    for (size_t i = 0; i < pts.size(); ++i) {
        EXPECT_EQ(pts[i].x, srt[i].x);
        EXPECT_EQ(pts[i].y, srt[i].y);
    }
}


TEST(GetImageRatio, test)
{
    std::vector<sl::Point> pts = {{100, 100}, {1100, 100},
                                  {393, 686}, {807, 686}};
    double ratio = sl::get_h_w_ratio(pts, 1200, 1200, 500);
    double exp_ratio = 1.0;
    std::cout << ratio << std::endl;
    EXPECT_NEAR(ratio, exp_ratio, 0.02);

    pts = {{200, 0}, {1000, 0}, {452, 692}, {748, 692}};
    ratio = sl::get_h_w_ratio(pts, 1200, 1200, 500);
    exp_ratio = 1.5;
    std::cout << ratio << std::endl;
    EXPECT_NEAR(ratio, exp_ratio, 0.02);


    pts = {{100, 0}, {0, 100}, {0, 0}, {100, 100}};
    ratio = sl::get_h_w_ratio(pts, 1200, 1200, 500);
    exp_ratio = 1.0;
    std::cout << ratio << std::endl;
    EXPECT_NEAR(ratio, exp_ratio, 0.02);
}



int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();
    return EXIT_SUCCESS;
}

