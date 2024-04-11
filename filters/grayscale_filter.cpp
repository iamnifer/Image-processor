#include "grayscale_filter.h"

GrayscaleFilter::GrayscaleFilter() {
}

const float R_K = 0.299;
const float G_K = 0.587;
const float B_K = 0.114;

void GrayscaleFilter::Apply(Image& img) const {
    Image res = img;

    int32_t height = img.GetHeight();
    int32_t width = img.GetWidth();
    for (int32_t i = 0; i < height; ++i) {
        for (int32_t j = 0; j < width; ++j) {
            float r = res.data_[i][j].GetRedF();
            float g = res.data_[i][j].GetGreenF();
            float b = res.data_[i][j].GetBlueF();
            float new_val = r * R_K + g * G_K + b * B_K;
            res.data_[i][j] = Pixel(new_val, new_val, new_val);
            res.data_[i][j].Normalize();
        }
    }

    img = res;
}

int32_t GrayscaleFilter::GetArgNumber() const {
    return GS_ARG_NUMBER;
}