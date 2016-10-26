cmake_minimum_required(VERSION 2.8.12)

project(crib_hand_helper)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_library(card src/card.cpp)
target_include_directories(card PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_library(hand_counter src/hand_counter.cpp)
target_include_directories(hand_counter PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(hand_counter PUBLIC card)

add_library(hand_statistics src/hand_statistics.cpp)
target_include_directories(hand_statistics PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(hand_statistics PUBLIC card hand_counter)

add_executable(crib_hand_helper apps/crib_hand_helper.cpp)
target_include_directories(crib_hand_helper PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(crib_hand_helper card hand_counter hand_statistics)

add_executable(test_card test/main.cpp test/test_card.cpp)
target_include_directories(test_card PUBLIC test)
target_link_libraries(test_card card)

add_executable(test_hand_counter test/main.cpp test/test_hand_counter.cpp)
target_include_directories(test_hand_counter PUBLIC test)
target_link_libraries(test_hand_counter card hand_counter)

add_executable(test_hand_statistics test/main.cpp test/test_hand_statistics.cpp)
target_include_directories(test_hand_statistics PUBLIC test)
target_link_libraries(test_hand_statistics card hand_counter hand_statistics)

enable_testing()
add_test(NAME CardTests COMMAND test_card)
add_test(NAME HandCounterTests COMMAND test_hand_counter)
add_test(NAME HandStatisticsTests COMMAND test_hand_statistics)
