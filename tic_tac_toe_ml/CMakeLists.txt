cmake_minimum_required(VERSION 3.10)
project(TicTacToeML)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")
set(CMAKE_CXX_FLAGS_DEBUG "-g -DDEBUG")

# Add executable
add_executable(tic_tac_toe_ml
    main.cpp
    TicTacToe.cpp
    QLearningAgent.cpp
)

# Set output directory
set_target_properties(tic_tac_toe_ml PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)
