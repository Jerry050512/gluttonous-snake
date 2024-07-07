cmake_minimum_required(VERSION 3.10)

# 项目信息
project(GluttounousSnake)

# 设置编译器
set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)

# 设置 C 标准
set(CMAKE_C_STANDARD 99)

# 包含头文件目录
include_directories(src/include)

# 查找所有源文件
file(GLOB_RECURSE SOURCES "src/*.c")

# 添加可执行文件
add_executable(game ${SOURCES})

# 查找测试文件
file(GLOB_RECURSE TEST_SOURCES "tests/*.c")

# 添加测试可执行文件
add_executable(test ${TEST_SOURCES} ${SOURCES})