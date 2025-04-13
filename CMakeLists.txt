cmake_minimum_required(VERSION 3.10)
project(ShapeMixer)

# Set wxWidgets version and configuration
set(wxWidgets_ROOT_DIR "C:/wxWidgets")
set(wxWidgets_LIB_DIR "C:/wxWidgets/lib/vc14x_x64_dll")
set(wxWidgets_CONFIGURATION mswu)

# Find required packages
find_package(wxWidgets REQUIRED gl core base)
find_package(OpenGL REQUIRED)

# Include wxWidgets
include(${wxWidgets_USE_FILE})

# Add executable with WIN32 flag
add_executable(ShapeMixer WIN32
    src/main.cpp
    src/GLCanvas.cpp
    src/MainWindow.cpp
)

# Link libraries
target_link_libraries(ShapeMixer PRIVATE
    ${wxWidgets_LIBRARIES}
    ${OPENGL_LIBRARIES}
)

# Print wxWidgets variables for debugging
message(STATUS "wxWidgets_LIBRARIES: ${wxWidgets_LIBRARIES}")
message(STATUS "wxWidgets_INCLUDE_DIRS: ${wxWidgets_INCLUDE_DIRS}")
message(STATUS "wxWidgets_LIBRARY_DIRS: ${wxWidgets_LIBRARY_DIRS}")

# Copy resources
file(COPY ${PROJECT_SOURCE_DIR}/resources DESTINATION ${CMAKE_BINARY_DIR})