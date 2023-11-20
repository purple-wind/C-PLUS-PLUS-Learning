cmake_minimum_required(VERSION 2.6)
project(general)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -O0 -fpermissive -fno-elide-constructors ")
add_definitions(
                -Wno-overflow #去掉写溢出警告，比如把long long型数据赋值给int
                -Wno-write-strings #去掉字符初始化std::string警告
               )
aux_source_directory(./ SRC_FILE)
add_executable(${PROJECT_NAME} ${SRC_FILE})
