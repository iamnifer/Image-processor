#pragma once

#include "filter.h"

const int32_t GS_ARG_NUMBER = 0;

class GrayscaleFilter : public Filter {
private:
public:
    GrayscaleFilter();

    void Apply(Image& img) const override;

    int32_t GetArgNumber() const override;
};