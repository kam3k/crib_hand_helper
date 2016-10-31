cmake_minimum_required(VERSION 2.8.12)

project(crib_hand_helper)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Cribbage library
add_library(cribbage
    src/card.cpp
    src/hand_counter.cpp
    src/hand_statistics.cpp
    )
target_include_directories(cribbage PUBLIC ${PROJECT_SOURCE_DIR}/include)

# Main executable
add_executable(crib_hand_helper apps/crib_hand_helper.cpp)
target_link_libraries(crib_hand_helper PRIVATE cribbage)

# Install
install(TARGETS crib_hand_helper DESTINATION bin)

# Tests
add_executable(test_card test/main.cpp test/test_card.cpp)
target_link_libraries(test_card cribbage)
target_include_directories(test_card PRIVATE ${PROJECT_SOURCE_DIR}/test)

add_executable(test_hand_counter test/main.cpp test/test_hand_counter.cpp)
target_link_libraries(test_hand_counter cribbage)
target_include_directories(test_hand_counter PRIVATE ${PROJECT_SOURCE_DIR}/test)

add_executable(test_hand_statistics test/main.cpp test/test_hand_statistics.cpp)
target_link_libraries(test_hand_statistics cribbage)
target_include_directories(test_hand_statistics PRIVATE ${PROJECT_SOURCE_DIR}/test)

enable_testing()
add_test(NAME CardTests COMMAND test_card)
add_test(NAME HandCounterTests COMMAND test_hand_counter)
add_test(NAME HandStatisticsTests COMMAND test_hand_statistics)
