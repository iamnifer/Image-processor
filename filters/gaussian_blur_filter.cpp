#include "gaussian_blur_filter.h"
#include <cmath>

GaussianBlurFilter::GaussianBlurFilter(float sigma) : sigma_(sigma) {
}

void GaussianBlurFilter::Apply(Image& img) const {
    Image res = img;
    int32_t height = img.GetHeight();
    int32_t width = img.GetWidth();
    float ssigma2 = sigma_ * sigma_ * 2;
    float multiplier = 1.F / (static_cast<float>(M_PI) * ssigma2);

    int32_t max_step = std::floor(sigma_ * 3);

    for (int32_t i = 0; i < height; ++i) {
        for (int32_t j = 0; j < width; ++j) {
            res.data_[i][j] = Pixel(0.F, 0.F, 0.F);
            for (int32_t dx = -max_step; dx <= max_step; ++dx) {
                float pwer = -static_cast<float>(dx * dx) / ssigma2;
                res.data_[i][j] += GetClosest(i + dx, j, img) * expf(pwer);
            }
        }
    }

    for (int32_t i = 0; i < height; ++i) {
        for (int32_t j = 0; j < width; ++j) {
            img.data_[i][j] = Pixel(0.F, 0.F, 0.F);
            for (int32_t dy = -max_step; dy <= max_step; ++dy) {
                float pwer = -static_cast<float>(dy * dy) / ssigma2;
                img.data_[i][j] += GetClosest(i, j + dy, res) * expf(pwer);
            }
        }
    }

    for (int32_t i = 0; i < height; ++i) {
        for (int32_t j = 0; j < width; ++j) {
            img.data_[i][j] = img.data_[i][j] * multiplier;
            img.data_[i][j].Normalize();
        }
    }
}

int32_t GaussianBlurFilter::GetArgNumber() const {
    return BLUR_ARG_NUMBER;
}