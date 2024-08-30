#=======================================================================================================================
project(uniform_buffer)
#=======================================================================================================================
add_executable(${PROJECT_NAME})
#=======================================================================================================================
target_link_libraries(${PROJECT_NAME} PRIVATE editor_tools)
target_link_libraries(${PROJECT_NAME} PRIVATE engine_core engine_platform engine_graphics glad)
target_sources(${PROJECT_NAME}        PRIVATE main.cpp)
#=======================================================================================================================
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG   "${BUILD_FOLDER_PATH}/buffers/${PROJECT_NAME}"
                                                 RUNTIME_OUTPUT_DIRECTORY_RELEASE "${BUILD_FOLDER_PATH}/buffers/${PROJECT_NAME}")
#=======================================================================================================================