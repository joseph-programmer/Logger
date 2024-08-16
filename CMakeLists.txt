cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(Logger VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Option to build shared or static library (default to static)
option(BUILD_SHARED_LIBS "Build shared libraries instead of static" OFF)

# Define the source files for the Logger library
set(SOURCES
    LoggerManager.cpp
    LogFormatter.cpp
    LogDestination.cpp  
)

# Define the header files for the Logger library
set(HEADERS
    Logger.h
    LoggerManager.h
    LogFormatter.h
    LogDestination.h
    LogLevel.h
    LoggerPCH.h
    LoggerCore.h
    LoggerCore.inl
    LoggerMacros.h
)

# Create the Logger library (static by default)
add_library(Logger ${SOURCES} ${HEADERS})

# Set up the precompiled header (PCH)
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_precompile_headers(Logger PRIVATE LoggerPCH.h)
elseif(MSVC)
    target_precompile_headers(Logger PRIVATE LoggerPCH.h)
endif()

# Set properties for the library based on the build type
if(BUILD_SHARED_LIBS)
    target_compile_definitions(Logger PRIVATE LOGGER_COMPILED_LIB LOGGER_SHARED_LIB)
    set_target_properties(Logger PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    )
else()
    set_target_properties(Logger PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    )
endif()

# Specify include directories for the Logger library
target_include_directories(Logger PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Optionally, create an install target for the library
install(TARGETS Logger
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    PUBLIC_HEADER DESTINATION include
)
