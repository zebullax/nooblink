cmake_minimum_required(VERSION 3.20)

find_package(nlohmann_json 3.11.3 REQUIRED)
find_package(spdlog REQUIRED)
find_package(GTest REQUIRED)
find_package(Boost 1.62 COMPONENTS program_options REQUIRED)

add_executable(nooblink main.cpp)
target_include_directories(nooblink PUBLIC .)

add_executable(nooblink_test "")
target_include_directories(nooblink_test PUBLIC .)

add_subdirectory(io)
add_subdirectory(raw)
add_subdirectory(vocabulary)
add_subdirectory(session)
add_subdirectory(utility)

target_link_libraries(nooblink 
    PRIVATE nlohmann_json::nlohmann_json
    PRIVATE spdlog::spdlog
    PRIVATE Boost::program_options)
target_link_libraries(nooblink_test
    PRIVATE nlohmann_json::nlohmann_json
    PRIVATE spdlog::spdlog
    PRIVATE GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(nooblink_test)

