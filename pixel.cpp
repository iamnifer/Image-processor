#include "pixel.h"
#include <math.h>

const uint8_t MAX_COLOR = 255;

Pixel::Pixel() : r_(0), g_(0), b_(0) {
}

Pixel::Pixel(float r, float g, float b) : r_(r), g_(g), b_(b) {
}

Pixel::Pixel(uint8_t r, uint8_t g, uint8_t b) {
    r_ = static_cast<float>(r) / MAX_COLOR;
    g_ = static_cast<float>(g) / MAX_COLOR;
    b_ = static_cast<float>(b) / MAX_COLOR;
}

const uint8_t Pixel::GetRed() const {
    return static_cast<uint8_t>(std::round(r_ * MAX_COLOR));
}

const uint8_t Pixel::GetGreen() const {
    return static_cast<uint8_t>(std::round(g_ * MAX_COLOR));
}

const uint8_t Pixel::GetBlue() const {
    return static_cast<uint8_t>(std::round(b_ * MAX_COLOR));
}

const float Pixel::GetRedF() const {
    return r_;
}

const float Pixel::GetGreenF() const {
    return g_;
}

const float Pixel::GetBlueF() const {
    return b_;
}

void Pixel::Normalize() {
    r_ = std::min(1.F, std::max(0.F, r_));
    g_ = std::min(1.F, std::max(0.F, g_));
    b_ = std::min(1.F, std::max(0.F, b_));
}

Pixel Pixel::operator*(float k) const {
    return Pixel(r_ * k, g_ * k, b_ * k);
}

Pixel Pixel::operator+(const Pixel& sec) const {
    Pixel res = *this;
    res += sec;
    return res;
}

Pixel& Pixel::operator+=(const Pixel& sec) {
    r_ += sec.r_;
    g_ += sec.g_;
    b_ += sec.b_;
    return *this;
}
