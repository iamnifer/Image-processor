#pragma once

#include "filter.h"

const int32_t HYPNO_ARG_NUMBER = 0;

class HypnoFilter : public Filter {
private:
public:
    HypnoFilter();

    void Apply(Image& img) const override;

    int32_t GetArgNumber() const override;
};