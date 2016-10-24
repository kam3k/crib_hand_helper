cmake_minimum_required(VERSION 2.8.12)

project(crib_hand_helper)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_library(card src/card.cpp)
target_include_directories(card PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_library(hand_counter src/hand_counter.cpp)
target_include_directories(hand_counter PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(hand_counter PUBLIC card)

add_executable(crib_hand_helper apps/crib_hand_helper.cpp)
target_include_directories(crib_hand_helper PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(crib_hand_helper card hand_counter)

set(TEST_SOURCES test/main.cpp test/test_card.cpp)

add_executable(test_card ${TEST_SOURCES})
target_include_directories(test_card PUBLIC test)
target_link_libraries(test_card card)

enable_testing()
add_test(NAME CardTests COMMAND test_card)
