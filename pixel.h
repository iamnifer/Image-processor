#pragma once

#include <cstdint>

class Pixel {
private:
    float r_;
    float g_;
    float b_;

public:
    Pixel();

    Pixel(float r, float g, float b);

    Pixel(uint8_t r, uint8_t g, uint8_t b);

    const uint8_t GetRed() const;

    const uint8_t GetGreen() const;

    const uint8_t GetBlue() const;

    const float GetRedF() const;

    const float GetGreenF() const;

    const float GetBlueF() const;

    void Normalize();

    Pixel operator*(float k) const;

    Pixel operator+(const Pixel& sec) const;

    Pixel& operator+=(const Pixel& sec);
};
