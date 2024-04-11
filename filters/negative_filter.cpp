#include "negative_filter.h"

NegativeFilter::NegativeFilter() {
}

void NegativeFilter::Apply(Image& img) const {
    Image res = img;

    int32_t height = img.GetHeight();
    int32_t width = img.GetWidth();
    for (int32_t i = 0; i < height; ++i) {
        for (int32_t j = 0; j < width; ++j) {
            float r = res.data_[i][j].GetRedF();
            float g = res.data_[i][j].GetBlueF();
            float b = res.data_[i][j].GetGreenF();
            res.data_[i][j] = Pixel(1 - r, 1 - g, 1 - b);
        }
    }

    img = res;
}

int32_t NegativeFilter::GetArgNumber() const {
    return NEG_ARG_NUMBER;
}