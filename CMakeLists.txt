cmake_minimum_required(VERSION 3.10)
project(Conways_Game_Of_Life)

# Set the C++ standard
set(CMake_CXX_STANDARD 17)

# Set the source files
set(SOURCES 
    main.cpp 
    ConwaysGameOfLife.cpp
    ExperimentManager.cpp
    Grid.cpp
    PatternDetector.cpp
    StringUtils.cpp
    )

set(HEADERS
    ConsoleUtils.h
    ConwaysGameOfLife.h
    ExperimentManager.h
    GameConfig.h
    Grid.h
    PatternDetector.h
    PauseController.h
    StringUtils.h
)

# Define the executable target
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})