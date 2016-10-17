cmake_minimum_required(VERSION 2.8.12)

project(crib_hand_helper)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CRIB_HAND_HELPER_SOURCES apps/crib_hand_helper.cpp src/card.cpp src/hand_counter.cpp)

add_executable(crib_hand_helper ${CRIB_HAND_HELPER_SOURCES})

target_include_directories(crib_hand_helper PUBLIC ${PROJECT_SOURCE_DIR}/include)
