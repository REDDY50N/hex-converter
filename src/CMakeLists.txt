add_executable(${EXEC_NAME} main.cpp)

target_link_libraries(${EXEC_NAME} Qt::Core CoreLib)

add_subdirectory(core)