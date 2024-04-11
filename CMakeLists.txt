#set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -static-libgcc -static-libstdc++")
#add_catch(
#        test_MY2_image_processor
#        test.cpp
#        image.cpp
#        pixel.cpp
#        filters/crop_filter.cpp
#        filters/grayscale_filter.cpp
#        filters/negative_filter.cpp
#        filters/sharpening_filter.cpp
#        filters/edge_detection_filter.cpp
#        filters/gaussian_blur_filter.cpp
#)

add_executable(
    image_processor
    image_processor.cpp
        image.cpp
        pixel.cpp
        filters/crop_filter.cpp
        filters/grayscale_filter.cpp
        filters/negative_filter.cpp
        filters/sharpening_filter.cpp
        filters/edge_detection_filter.cpp
        filters/gaussian_blur_filter.cpp
        filters/hypno_filter.cpp filters/hypno_filter.h)

#add_catch(test_abobus test_script/test_image_processor.py image_processor.cpp image.cpp pixel.cpp filters/crop_filter.cpp)