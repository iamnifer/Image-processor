#pragma once

#include "../image.h"

class Filter {
private:
public:
    virtual void Apply(Image& img) const = 0;
    virtual int32_t GetArgNumber() const = 0;
};
