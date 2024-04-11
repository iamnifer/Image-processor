#include "crop_filter.h"

CropFilter::CropFilter(int32_t width, int32_t height) : width_(width), height_(height) {
}

const uint32_t HEADER_SIZE = 54;

void CropFilter::Apply(Image& img) const {
    Image res = img;

    int32_t orig_height = img.GetHeight();
    int32_t orig_width = img.GetWidth();
    res.info_header_.width = std::min(orig_width, width_);
    res.info_header_.height = std::min(orig_height, height_);
    res.data_.resize(res.info_header_.height);
    for (auto& i : res.data_) {
        i.resize(res.info_header_.width);
    }
    int32_t row_size = res.info_header_.width * 3;
    row_size += (4 - row_size % 4) % 4;
    int32_t new_data_size = row_size * res.info_header_.height;
    res.info_header_.size_image = new_data_size;
    res.file_header_.file_size = new_data_size + HEADER_SIZE;

    img = res;
}

int32_t CropFilter::GetArgNumber() const {
    return CROP_ARG_NUMBER;
}