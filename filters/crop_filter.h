#pragma once

#include "filter.h"

const int32_t CROP_ARG_NUMBER = 2;

class CropFilter : public Filter {
private:
    int32_t width_;
    int32_t height_;

public:
    CropFilter(int32_t width, int32_t height);

    void Apply(Image& img) const override;

    int32_t GetArgNumber() const override;
};