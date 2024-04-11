#pragma once

#include "filter.h"

const int32_t BLUR_ARG_NUMBER = 1;

class GaussianBlurFilter : public Filter {
private:
    float sigma_;

public:
    explicit GaussianBlurFilter(float sigma);

    void Apply(Image& img) const override;

    int32_t GetArgNumber() const override;
};