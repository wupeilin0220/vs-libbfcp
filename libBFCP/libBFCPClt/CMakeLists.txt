cmake_minimum_required(VERSION 2.8)
project(bfcpclt)

# 设置编译器
set(CMAKE_C_COMPILER gcc)

# 设置编译选项和宏定义
add_compile_options(-Wall -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -O2 -fPIC -ggdb -D_LINUX_ -DLINUX)

# 检查 CMAKE_SYSTEM_PROCESSOR 并修改为 arm64
if(CMAKE_SYSTEM_PROCESSOR STREQUAL "aarch64")
	set(CMAKE_SYSTEM_PROCESSOR "arm64")
endif()

# 设置生成的动态库路径
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Bin/${CMAKE_SYSTEM_PROCESSOR})

# 设置库路径
link_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/Depends/OpenSSL/lib/${CMAKE_SYSTEM_PROCESSOR}
	${CMAKE_CURRENT_SOURCE_DIR}/Depends/libBFCPMsg/lib/${CMAKE_SYSTEM_PROCESSOR}
)

# 设置库
set(LIBS bfcpmsg pthread ssl crypto)

# 设置源文件
set(SOURCES bfcp_participant.c)

# 生成共享库
add_library(${PROJECT_NAME} SHARED ${SOURCES})
set_target_properties(${PROJECT_NAME} PROPERTIES VERSION 0.0.7 SOVERSION 0)

# 设置头文件路径
target_include_directories(${PROJECT_NAME} PRIVATE 
	${CMAKE_CURRENT_SOURCE_DIR}/Depends/OpenSSL/include
	${CMAKE_CURRENT_SOURCE_DIR}/Depends/libBFCPMsg/include
)

