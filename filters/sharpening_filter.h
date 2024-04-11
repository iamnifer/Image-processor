#pragma once

#include "filter.h"

const int32_t SHARP_ARG_NUMBER = 0;

class SharpeningFilter : public Filter {
private:
public:
    SharpeningFilter();

    void Apply(Image& img) const override;

    int32_t GetArgNumber() const override;
};