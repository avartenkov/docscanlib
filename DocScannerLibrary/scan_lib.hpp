#ifndef SCAN_LIB_H
#define SCAN_LIB_H
#include <vector>



namespace scanlib {

enum ImprovementOptions {


};


struct Size {
    int height;
    int width;
};


struct Image {
    int channels;
    int width;
    int height;
    char *data;
};


struct Point {
    int x;
    int y;
};



std::vector<Point> get_document_rectangle(const Image &image);


Image restore_image_size(const Image &image, const std::vector<Point> &points,
                         const Size result_size = {-1, -1});


Image postprocess(const Image &image, int options);
}


#endif // SCAN_LIB_H
