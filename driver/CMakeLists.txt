cmake_minimum_required(VERSION 3.30)

# 项目信息 #需修改
project(Easyx)

# 设置 C 和 C++ 语言标准
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 23)

#设置工具链（要在设置中的CMAKE中切换）#需修改
#使用g++
#set(CMAKE_C_COMPILER "D:/mingw64/bin/gcc.exe")
#set(CMAKE_CXX_COMPILER "D:/mingw64/bin/g++.exe")
#使用MSCV
#set(CMAKE_C_COMPILER "D:\\vs\\VC\\Tools\\MSVC\\14.41.34120\\bin\\Hostx64\\x64\\cl.exe")
#set(CMAKE_C_COMPILER "D:\\vs\\VC\\Tools\\MSVC\\14.41.34120\\bin\\Hostx64\\x64\\cl.exe")

# 包含头文件路径 #需修改
include_directories("./include/EasyX")
#include_directories("./include/头文件所在目录")

# 链接库路径
link_directories("./lib")

include_directories(${PROJECT_SOURCE_DIR}/include/Easyx)
include_directories(${PROJECT_SOURCE_DIR}/include)
# 遍历 src 文件夹下的所有源文件
file(GLOB_RECURSE src_dir "./src/*.cpp" "./src/*.c" "./src/*.h" "./src/*.hpp")
file(GLOB_RECURSE include_dir "./include/Easyx/*.h")
file(GLOB_RECURSE include_dir "./include/*.h")
# 添加可执行文件
add_executable(${PROJECT_NAME} ${src_dir} ${include_dir}
        src/game.cpp
        src/draw.cpp
        include/draw.h
        include/Player.h
        include/Chess.h
        src/Chess.cpp
        src/Player.cpp
        src/Gomoku.cpp
        src/Go.cpp
        src/main.cpp
)

# 链接库 #需修改
# 方法一：什么都不做，会自动查找环境变量中的库
# 方法二：会根据库名称在指定的库路径寻找该名称的库应该包含的库文件 target_link_libraries(${PROJECT_NAME} freeglut OpenGL32)
# 方法三手动指定库文件路径 target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/lib/对应库文件名称)
# target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/lib/EasyXa.lib)
target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/lib/libeasyx.a)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include/Easyx)

#设定构建运行路径，避免污染
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/.archive)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/.library)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/.runtime)#设置运行目录
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/.runtime)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/.library)

#自动复制资源文件到运行目录（.runtime）
file(COPY ${PROJECT_SOURCE_DIR}/src/ DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
