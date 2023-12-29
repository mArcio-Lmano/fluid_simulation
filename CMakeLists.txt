cmake_minimum_required(VERSION 3.5)
project(FluidSimulation)

set(CMAKE_CXX_STANDARD 14)  # Adjust this based on your project's requirements

# Find SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Find OpenCL
find_package(OpenCL REQUIRED)

# Add your source files
add_executable(fluid_app src/main.cpp)

# Include OpenCL headers using target_include_directories
target_include_directories(fluid_app PRIVATE /usr/include/CL)


# Link against SFML and OpenCL libraries
target_link_libraries(fluid_app PRIVATE sfml-graphics sfml-window sfml-system OpenCL::OpenCL )
