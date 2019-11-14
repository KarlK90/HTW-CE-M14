PROJECT(RobotControlLib)

set(SOURCES
        Axis.cpp
        Robot.cpp
        RobotControl.cpp
        Ui.cpp
        )

set(HEADERS
        Axis.h
        Robot.h
        RobotControl.h
        Ui.h
        )

add_library(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Make sure the compiler can find include files for our library
# when other libraries or executables link to it
target_include_directories (${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})