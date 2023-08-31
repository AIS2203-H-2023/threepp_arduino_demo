cmake_minimum_required(VERSION 3.15)
project(threepp_arduino_demo)

set(CMAKE_CXX_STANDARD 17)

find_package(threepp CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(serial CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

add_executable(demo main.cpp)
target_link_libraries(demo PRIVATE threepp::threepp imgui::imgui serial::serial nlohmann_json::nlohmann_json)
