#target_include_directories(${EXEC_NAME} ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(${EXEC_NAME} main.cpp)


target_link_libraries(${EXEC_NAME} Qt::Core)