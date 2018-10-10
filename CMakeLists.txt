cmake_minimum_required(VERSION 3.10)
project(HERORM2019)

set(CMAKE_CXX_STANDARD 11)

add_executable(HERORM2019 src/main.cpp)

include_directories(
        ${OPENCV_INCLUDE_DIRS}
        ./header/
        )

target_link_libraries(HERORM2019
        -pthread
        ${OpenCV_LIBRARIES}
        /usr/local/lib
        /usr/local/lib/libopencv_calib3d.so
        /usr/local/lib/libopencv_imgcodecs.so
        /usr/local/lib/libopencv_stitching.so
        /usr/local/lib/libopencv_core.so
        /usr/local/lib/libopencv_imgproc.so
        /usr/local/lib/libopencv_superres.so
        /usr/local/lib/libopencv_dnn.so
        /usr/local/lib/libopencv_ml.so
        /usr/local/lib/libopencv_videoio.so
        /usr/local/lib/libopencv_features2d.so
        /usr/local/lib/libopencv_objdetect.so
        /usr/local/lib/libopencv_video.so
        /usr/local/lib/libopencv_flann.so
        /usr/local/lib/libopencv_photo.so
        /usr/local/lib/libopencv_videostab.so
        /usr/local/lib/libopencv_highgui.so
        /usr/local/lib/libopencv_shape.so
        /usr/local/lib/libopencv_viz.so
        )
