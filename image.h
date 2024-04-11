#pragma once

#include "pixel.h"
#include <cstdint>
#include <string>
#include <vector>

const uint16_t BM_TYPE = 0x4d42;
const uint32_t INFO_HEADER_SIZE = 40;

struct BitmapFileHeader {
    uint16_t file_type;
    uint32_t file_size;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t offset_data;
    BitmapFileHeader() {
        file_type = BM_TYPE;
        file_size = 0;
        reserved1 = 0;
        reserved2 = 0;
        offset_data = 0;
    }
} __attribute__((packed));

struct InfoHeader {
    uint32_t size;
    int32_t width;
    int32_t height;
    uint16_t planes;
    uint16_t bit_count;
    uint32_t compression;
    uint32_t size_image;
    int32_t x_pixels_per_meter;
    int32_t y_pixels_per_meter;
    uint32_t colors_used;
    uint32_t colors_important;
    InfoHeader() {
        size = INFO_HEADER_SIZE;
        width = 0;
        height = 0;
        planes = 1;
        bit_count = 0;
        compression = 0;
        size_image = 0;
        x_pixels_per_meter = 0;
        y_pixels_per_meter = 0;
        colors_used = 0;
        colors_important = 0;
    }
} __attribute__((packed));

class Image {
private:
    BitmapFileHeader file_header_;
    InfoHeader info_header_;
    std::vector<std::vector<Pixel>> data_;

public:
    Image();

    explicit Image(std::string filename);

    const int32_t GetWidth() const;

    const int32_t GetHeight() const;

    void Clear();

    void Read(std::string filename);

    void Write(std::string filename);

    //    std::vector<Pixel>& operator[](const size_t i);

    friend class CropFilter;
    friend class GrayscaleFilter;
    friend class NegativeFilter;
    friend class SharpeningFilter;
    friend class EdgeDetectionFilter;
    friend class GaussianBlurFilter;
    friend class HypnoFilter;
    friend const Pixel& GetClosest(int32_t i, int32_t j, const Image& img);
};
