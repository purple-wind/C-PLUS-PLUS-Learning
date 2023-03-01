cmake_minimum_required(VERSION 2.6)
project(exception)
aux_source_directory(./ SRC_FILE)
add_executable(${PROJECT_NAME} ${SRC_FILE})
