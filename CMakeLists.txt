cmake_minimum_required(VERSION 3.10)  # 设置 CMake 的最低版本要求
project(AngleGauge)  # 定义项目名称

# 设置可执行文件的全局输出路径
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
# 添加可执行文件
add_executable(main src/main.cpp)
add_executable(detector src/detector.cpp)

# 设置头文件包含目录
target_include_directories(main PRIVATE
    "D:/codeConfiguration/C_Packages/OpenCV-MinGW-Build-OpenCV-4.5.2-x64/include"
)
target_include_directories(detector PRIVATE
    "D:/codeConfiguration/C_Packages/OpenCV-MinGW-Build-OpenCV-4.5.2-x64/include"
)
# 设置库路径
target_link_directories(main PRIVATE
    "D:/codeConfiguration/C_Packages/OpenCV-MinGW-Build-OpenCV-4.5.2-x64/x64/mingw/bin"
)
target_link_directories(detector PRIVATE
    "D:/codeConfiguration/C_Packages/OpenCV-MinGW-Build-OpenCV-4.5.2-x64/x64/mingw/bin"
)


# 设置链接库
target_link_libraries(main
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
target_link_libraries(detector
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

# 设置编译选项
target_compile_options(main PRIVATE
    -fdiagnostics-color=always
    -g
    -fexec-charset=GBK
)