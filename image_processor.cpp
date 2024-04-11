#include "filters/crop_filter.h"
#include "filters/grayscale_filter.h"
#include "filters/negative_filter.h"
#include "filters/sharpening_filter.h"
#include "filters/edge_detection_filter.h"
#include "filters/gaussian_blur_filter.h"
#include "filters/hypno_filter.h"
#include "image.h"
#include <iostream>

int main(int argc, char** argv) {
    if (argc <= 2) {
        std::cout << "Help:\n"
                     "./image_processor <input file> <output file> [-filter1 [<filter1 params>] -filter2 [<filter2 "
                     "params>] ...]\n"
                     "Filters:\n"
                     "-crop <width> <height> - crop image to width x height\n"
                     "-gs - turns image gray \n"
                     "-neg - makes image negative\n"
                     "-sharpening - sharpens up image\n"
                     "-edge <threshold> - highlights edges, threshold controls sensitivity\n"
                     "-blur <sigma> - blurs image depending on sigma\n"
                     "-hypno - adds a hypno effect to image\n";
        return 0;
    }

    std::string input_file;
    std::string output_file;
    try {
        input_file = static_cast<std::string>(argv[1]);
        output_file = static_cast<std::string>(argv[2]);
        if (input_file.empty() || output_file.empty()) {
            throw std::invalid_argument("Invalid input/output files");
        }
    } catch (...) {
        throw std::invalid_argument("Invalid input/output files");
    }

    Image img(input_file);

    for (int32_t i = 3; i < argc;) {
        std::string arg = static_cast<std::string>(argv[i]);
        if (arg.empty()) {
            throw std::invalid_argument("Empty argument #" + std::to_string(i));
        }
        if (argv[i][0] != '-') {
            throw std::invalid_argument("Filter expected, found \"" + arg + "\"");
        }

        if (arg == "-crop") {
            if (i + CROP_ARG_NUMBER >= argc) {
                throw std::invalid_argument("Not enough crop filter parameters provided");
            }

            int32_t width = 0;
            int32_t height = 0;
            try {
                width = std::stoi(static_cast<std::string>(argv[i + 1]));
                height = std::stoi(static_cast<std::string>(argv[i + 2]));
                if (width < 0 || height < 0) {
                    throw std::invalid_argument("Invalid crop parameters, int32_t expected");
                }
            } catch (...) {
                throw std::invalid_argument("Invalid crop parameters, int32_t expected");
            }

            CropFilter f(width, height);
            f.Apply(img);

            i += CROP_ARG_NUMBER + 1;
        } else if (arg == "-gs") {
            if (i + GS_ARG_NUMBER >= argc) {
                throw std::invalid_argument("Not enough grayscale filter parameters provided");
            }

            GrayscaleFilter f;
            f.Apply(img);

            i += GS_ARG_NUMBER + 1;
        } else if (arg == "-neg") {
            if (i + NEG_ARG_NUMBER >= argc) {
                throw std::invalid_argument("Not enough negative filter parameters provided");
            }

            NegativeFilter f;
            f.Apply(img);

            i += NEG_ARG_NUMBER + 1;
        } else if (arg == "-sharp") {
            if (i + SHARP_ARG_NUMBER >= argc) {
                throw std::invalid_argument("Not enough sharpening filter parameters provided");
            }

            SharpeningFilter f;
            f.Apply(img);

            i += SHARP_ARG_NUMBER + 1;
        } else if (arg == "-edge") {
            if (i + EDGE_ARG_NUMBER >= argc) {
                throw std::invalid_argument("Not enough edge detection filter parameters provided");
            }

            float threshold = 0;
            try {
                threshold = std::stof(static_cast<std::string>(argv[i + 1]));
                if (!(threshold >= 0 && threshold <= 1)) {
                    throw std::invalid_argument("Invalid edge detection parameters, float in [0; 1] expected");
                }
            } catch (...) {
                throw std::invalid_argument("Invalid edge detection parameters, float in [0; 1] expected");
            }

            EdgeDetectionFilter f(threshold);
            f.Apply(img);

            i += EDGE_ARG_NUMBER + 1;
        } else if (arg == "-blur") {
            if (i + BLUR_ARG_NUMBER >= argc) {
                throw std::invalid_argument("Not enough gaussian blur filter parameters provided");
            }
            const float max_working_value = 1e9F;
            float sigma = 0;
            try {
                sigma = std::stof(static_cast<std::string>(argv[i + 1]));
                if (sigma <= 0 || sigma > max_working_value) {
                    throw std::invalid_argument("Invalid gaussian blur parameters, float in (0; 1e9) expected");
                }
            } catch (...) {
                throw std::invalid_argument("Invalid gaussian blur parameters, float in (0; 1e9) expected");
            }

            GaussianBlurFilter f(sigma);
            f.Apply(img);

            i += BLUR_ARG_NUMBER + 1;
        } else if (arg == "-hypno") {
            if (i + HYPNO_ARG_NUMBER >= argc) {
                throw std::invalid_argument("Not enough hypno filter parameters provided");
            }

            HypnoFilter f;
            f.Apply(img);

            i += HYPNO_ARG_NUMBER + 1;
        } else {
            throw std::invalid_argument("Unknown filter \"" + arg + "\"");
        }
    }

    img.Write(output_file);

    return 0;
}
