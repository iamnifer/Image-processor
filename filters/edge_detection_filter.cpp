#include "edge_detection_filter.h"
#include "grayscale_filter.h"

EdgeDetectionFilter::EdgeDetectionFilter(float threshold) : threshold_(threshold) {
}

const std::vector<std::vector<float>> MAT = {{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}};

void EdgeDetectionFilter::Apply(Image& img) const {
    GrayscaleFilter f;
    f.Apply(img);

    Image res = img;
    int32_t height = img.GetHeight();
    int32_t width = img.GetWidth();

    for (int32_t i = 0; i < height; ++i) {
        for (int32_t j = 0; j < width; ++j) {
            Pixel new_p;
            for (int32_t dx = -1; dx <= 1; ++dx) {
                for (int32_t dy = -1; dy <= 1; ++dy) {
                    float coef = MAT[dx + 1][dy + 1];
                    new_p += GetClosest(i + dx, j + dy, img) * coef;
                }
            }
            new_p.Normalize();

            if (new_p.GetRedF() > threshold_) {
                new_p = Pixel(1.F, 1.F, 1.F);
            } else {
                new_p = Pixel(0.F, 0.F, 0.F);
            }

            res.data_[i][j] = new_p;
        }
    }

    img = res;
}

int32_t EdgeDetectionFilter::GetArgNumber() const {
    return EDGE_ARG_NUMBER;
}