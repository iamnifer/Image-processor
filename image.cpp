#include "image.h"
#include <fstream>

Image::Image() : file_header_(), info_header_(), data_() {
}

Image::Image(std::string filename) {
    Read(filename);
}

const int32_t Image::GetWidth() const {
    return info_header_.width;
}

const int32_t Image::GetHeight() const {
    return info_header_.height;
}

void Image::Clear() {
    file_header_ = BitmapFileHeader();
    info_header_ = InfoHeader();
    data_.clear();
}

void Image::Read(std::string filename) {
    Clear();

    std::ifstream file(filename, std::ifstream::binary);
    if (file.fail()) {
        throw std::runtime_error("Input file doesn't exist");
    }

    file_header_.file_type = 3;
    try {  // reading file header
        file.read(reinterpret_cast<char*>(&file_header_), sizeof(file_header_));
        if (file_header_.file_type != BM_TYPE) {
            throw std::runtime_error("");
        }
    } catch (...) {
        throw std::runtime_error("Error reading file header, wrong file format");
    }

    try {  // reading info header
        file.read(reinterpret_cast<char*>(&info_header_), sizeof(info_header_));
    } catch (...) {
        throw std::runtime_error("Error reading info header, wrong file format");
    }

    int32_t rows = info_header_.height;
    int32_t cols = info_header_.width;
    data_.assign(rows, std::vector<Pixel>(cols));
    uint32_t padding_size = (4 - cols * 3 % 4) % 4;
    std::vector<uint8_t> padding_data(padding_size, 0);
    try {  // reading pixel array
        for (int32_t i = rows - 1; i >= 0; --i) {
            for (int32_t j = 0; j < cols; ++j) {
                uint8_t b = 0;
                uint8_t g = 0;
                uint8_t r = 0;
                file.read(reinterpret_cast<char*>(&b), sizeof(b));
                file.read(reinterpret_cast<char*>(&g), sizeof(g));
                file.read(reinterpret_cast<char*>(&r), sizeof(r));
                data_[i][j] = Pixel(r, g, b);
            }
            file.read(reinterpret_cast<char*>(padding_data.data()), padding_size);
        }
    } catch (...) {
        throw std::runtime_error("Error reading pixel array, wrong file format");
    }
}

void Image::Write(std::string filename) {
    std::ofstream file(filename, std::ofstream::out | std::ofstream::binary | std::ofstream::trunc);
    //    if (file.fail()) {
    //        throw std::runtime_error(".!.");
    //    }

    try {  // writing file header
        file.write(reinterpret_cast<char*>(&file_header_), sizeof(file_header_));
    } catch (...) {
        throw std::runtime_error("Error writing file, in file header");
    }

    try {  // writing info header
        file.write(reinterpret_cast<char*>(&info_header_), sizeof(info_header_));
    } catch (...) {
        throw std::runtime_error("Error writing file, in info header");
    }

    int32_t rows = info_header_.height;
    int32_t cols = info_header_.width;
    uint32_t padding_size = (4 - cols * 3 % 4) % 4;
    std::vector<uint8_t> padding_data(padding_size, 0);
    try {  // writing pixel array
        for (int32_t i = rows - 1; i >= 0; --i) {
            for (int32_t j = 0; j < cols; ++j) {
                uint8_t b = data_[i][j].GetBlue();
                uint8_t g = data_[i][j].GetGreen();
                uint8_t r = data_[i][j].GetRed();
                file.write(reinterpret_cast<char*>(&b), sizeof(b));
                file.write(reinterpret_cast<char*>(&g), sizeof(g));
                file.write(reinterpret_cast<char*>(&r), sizeof(r));
            }
            file.write(reinterpret_cast<char*>(padding_data.data()), padding_size);
        }
    } catch (...) {
        throw std::runtime_error("Error writing file, in pixel array");
    }
}

// std::vector<Pixel>& Image::operator[](const size_t i) {
//     return data_[i];
// }