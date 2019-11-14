PROJECT(RobotSimulateLib)

set(SOURCES
        RobotSimulate.cpp
        )

set(HEADERS
        RobotSimulate.h
        )

add_library(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Make sure the compiler can find include files for our library
# when other libraries or executables link to it
target_include_directories (${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} RobotControlLib)