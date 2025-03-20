cmake_minimum_required(VERSION 3.10)  # 设置 CMake 的最低版本要求
project(AngleGauge)  # 定义项目名称

# 设置可执行文件的全局输出路径
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
# 设置 OpenCV 库路径变量
set(OpenCV_DIR "D:/codeConfiguration/C_Packages/OpenCV-MinGW-Build-OpenCV-4.5.2-x64")
# 设置链接库列表
set(OPENCV_LIBS
    libopencv_calib3d452
    libopencv_photo452
    libopencv_core452
    libopencv_stitching452
    libopencv_dnn452
    libopencv_video452
    libopencv_features2d452
    libopencv_videoio452
    libopencv_flann452
    libopencv_gapi452
    libopencv_highgui452
    libopencv_imgcodecs452
    libopencv_imgproc452
    libopencv_ml452
    opencv_videoio_ffmpeg452_64
    libopencv_objdetect452
)

# 定义一个函数来设置目标的属性
function(setup_target target_name)
    target_include_directories(${target_name} PRIVATE "${OpenCV_DIR}/include")
    target_link_directories(${target_name} PRIVATE "${OpenCV_DIR}/x64/mingw/bin")
    target_link_libraries(${target_name} ${OPENCV_LIBS})
    target_compile_options(${target_name} PRIVATE -fdiagnostics-color=always -g -fexec-charset=GBK)
endfunction()

# 添加可执行文件并设置属性
add_executable(main src/main.cpp)
setup_target(main)

add_executable(detector src/detector.cpp)
setup_target(detector)

add_executable(testCornerDetector src/testCornerDetector.cpp)
setup_target(testCornerDetector)