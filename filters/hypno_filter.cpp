#include "hypno_filter.h"
#include <cmath>

HypnoFilter::HypnoFilter() {
}

const float R_K = 0.299 * 3;
const float G_K = 0.587 * 3;
const float B_K = 0.114 * 3;

const float HYPNO_CIRCLES = 10;
const float HALF = 0.5;

void HypnoFilter::Apply(Image& img) const {
    Image res = img;

    int32_t height = img.GetHeight();
    int32_t width = img.GetWidth();
    int32_t midx = height / 2;
    int32_t midy = width / 2;
    for (int32_t i = 0; i < height; ++i) {
        for (int32_t j = 0; j < width; ++j) {
            float r = res.data_[i][j].GetRedF();
            float g = res.data_[i][j].GetGreenF();
            float b = res.data_[i][j].GetBlueF();
            float shift = sqrtf(static_cast<float>((i - midx) * (i - midx) + (j - midy) * (j - midy)));
            shift /= (static_cast<float>((height + width) / 2) / HYPNO_CIRCLES);
            r += shift * R_K;
            g += shift * G_K;
            b += shift * B_K;
            r = r - floorf(r);
            g = g - floorf(g);
            b = b - floorf(b);

            res.data_[i][j] = (Pixel(r, g, b) + res.data_[i][j]) * HALF;
        }
    }

    img = res;
}

int32_t HypnoFilter::GetArgNumber() const {
    return HYPNO_ARG_NUMBER;
}