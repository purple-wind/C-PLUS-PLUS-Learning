cmake_minimum_required(VERSION 2.8)
project(boost)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++11 ")
add_executable(asio_s boost_asio/boost_asio3.cpp)
target_link_libraries(asio_s pthread boost_system boost_thread )

add_executable(concurrent   
				boost_concurrentqueue/global.cpp 
				boost_concurrentqueue/main.cpp 
				boost_concurrentqueue/lockfree_queue.cpp
				)
target_link_libraries(concurrent boost_thread boost_system pthread)