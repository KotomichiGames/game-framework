#=======================================================================================================================
project(platform_window)
#=======================================================================================================================
add_executable(${PROJECT_NAME})
#=======================================================================================================================
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG   "${CMAKE_SOURCE_DIR}/build/engine/platform/${PROJECT_NAME}"
                                                 RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/build/engine/platform/${PROJECT_NAME}")
#=======================================================================================================================
target_link_libraries(${PROJECT_NAME}   PRIVATE platform)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)
target_sources(${PROJECT_NAME}          PRIVATE main.cpp)
#=======================================================================================================================