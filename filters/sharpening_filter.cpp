#include "sharpening_filter.h"

SharpeningFilter::SharpeningFilter() {
}

const std::vector<std::vector<float>> MAT = {{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}};

const Pixel& GetClosest(int32_t i, int32_t j, const Image& img) {
    int32_t height = img.GetHeight();
    int32_t width = img.GetWidth();
    i = std::max(0, std::min(height - 1, i));
    j = std::max(0, std::min(width - 1, j));
    return img.data_[i][j];
}

void SharpeningFilter::Apply(Image& img) const {
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
            res.data_[i][j] = new_p;
        }
    }

    img = res;
}

int32_t SharpeningFilter::GetArgNumber() const {
    return SHARP_ARG_NUMBER;
}