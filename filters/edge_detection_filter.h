#pragma once

#include "filter.h"

const int32_t EDGE_ARG_NUMBER = 1;

class EdgeDetectionFilter : public Filter {
private:
    float threshold_;

public:
    explicit EdgeDetectionFilter(float threshold);

    void Apply(Image& img) const override;

    int32_t GetArgNumber() const override;
};