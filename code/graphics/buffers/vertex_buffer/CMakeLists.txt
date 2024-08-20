#=======================================================================================================================
project(vertex_buffer)
#=======================================================================================================================
add_executable(${PROJECT_NAME})
#=======================================================================================================================
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG   "${BUILD_FOLDER_PATH}/buffers/${PROJECT_NAME}"
                                                 RUNTIME_OUTPUT_DIRECTORY_RELEASE "${BUILD_FOLDER_PATH}/buffers/${PROJECT_NAME}")
#=======================================================================================================================
target_link_libraries(${PROJECT_NAME}   PRIVATE engine::core engine::platform glad)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)
target_sources(${PROJECT_NAME}          PRIVATE main.cpp)
#=======================================================================================================================