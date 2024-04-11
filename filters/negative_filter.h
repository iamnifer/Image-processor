#pragma once

#include "filter.h"

const int32_t NEG_ARG_NUMBER = 0;

class NegativeFilter : public Filter {
private:
public:
    NegativeFilter();

    void Apply(Image& img) const override;

    int32_t GetArgNumber() const override;
};