cmake_minimum_required(VERSION 2.8)
project(boost)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++11 ")
include_directories("/usr/include/boost/threadpool")

add_executable(asio_s boost_asio/boost_asio3.cpp)
target_link_libraries(asio_s pthread boost_system boost_thread )


add_executable(concurrent   
                boost_concurrent/lockfree/global.cpp
                boost_concurrent/lockfree/lockfree_queue.cpp
                boost_concurrent/lockfree/lockfree_spsc_queue.cpp
                boost_concurrent/lockfree/main.cpp
    )
target_link_libraries(concurrent boost_thread boost_system pthread)

add_executable(numa_and_core boost_concurrent/lockfree/numa_and_core.cpp)
target_link_libraries(numa_and_core pthread)
