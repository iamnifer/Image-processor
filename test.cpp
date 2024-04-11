#include <catch.hpp>

#include "image.h"
#include "pixel.h"
#include "filters/crop_filter.h"
#include "filters/grayscale_filter.h"
#include "filters/negative_filter.h"
#include "filters/sharpening_filter.h"
#include "filters/gaussian_blur_filter.h"


namespace {

}  // namespace

TEST_CASE("fuck") {
    std::string inkok = "C:\\Users\\iamnifer\\Desktop\\plusiki\\pmi-232-2-Aleksandr-Reznichenko-iamnifer\\tasks\\image_processor\\test_script\\data\\lenna.bmp";
    Image z(inkok);
    std::string outkok = "C:\\Users\\iamnifer\\Desktop\\plusiki\\pmi-232-2-Aleksandr-Reznichenko-iamnifer\\tasks\\image_processor\\lenna2.bmp";
//    CropFilter sus1(999, 1999);
//    z = sus1.Apply(z);

//    GrayscaleFilter sus2;
//    z = sus2.Apply(z);

//    NegativeFilter sus3;
//    z = sus3.Apply(z);

//    SharpeningFilter sus4;
//    z = sus4.Apply(z);

    GaussianBlurFilter sus6(7.5);
    sus6.Apply(z);
    z.Write(outkok);



//    std::string_view query = "typesetting release";
//    std::vector<std::string_view> expected = {"electronic typesetting, remaining essentially"};
//
//    const auto& actual = Search(text, query, 1);
//
//    REQUIRE(expected == actual);
//    SECTION("Result can not use extra memory") {
//        for (const auto& doc : actual) {
//            REQUIRE(Belongs(text, doc));
//        }
//    }
}
