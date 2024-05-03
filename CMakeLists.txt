cmake_minimum_required(VERSION 3.10)
project(GLOApp)

set(CMAKE_CXX_STANDARD 11)

# Locate wxWidgets library
find_package(wxWidgets REQUIRED COMPONENTS core base media)
include(${wxWidgets_USE_FILE})

# Add executable targetp
add_executable(GLOApp main.cpp ImageSlideshow.cpp VideoPlayer.cpp)

# Link wxWidgets libraries
target_link_libraries(GLOApp ${wxWidgets_LIBRARIES})


