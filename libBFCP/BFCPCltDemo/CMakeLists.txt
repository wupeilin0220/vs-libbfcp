cmake_minimum_required(VERSION 2.8)
project(bfcp_participant)

# 设置编译器
set(CMAKE_C_COMPILER gcc)

# 设置编译选项和宏定义
add_compile_options(-Wall -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -O2 -fPIC -ggdb -D_LINUX_ -DLINUX)

# 检查 CMAKE_SYSTEM_PROCESSOR 并修改为 arm64
if(CMAKE_SYSTEM_PROCESSOR STREQUAL "aarch64")
	set(CMAKE_SYSTEM_PROCESSOR "arm64")
endif()

# 设置库路径
link_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/../libBFCPClt/Depends/OpenSSL/lib/${CMAKE_SYSTEM_PROCESSOR}
	${CMAKE_CURRENT_SOURCE_DIR}/../libBFCPClt/Depends/libBFCPMsg/lib/${CMAKE_SYSTEM_PROCESSOR}
	${CMAKE_CURRENT_SOURCE_DIR}/../libBFCPClt/Bin/${CMAKE_SYSTEM_PROCESSOR}
)

# 设置安装路径
set(INSTALL_PATH ${CMAKE_CURRENT_SOURCE_DIR}/Bin/${CMAKE_SYSTEM_PROCESSOR})

# 设置运行时的动态库路径
set(CMAKE_INSTALL_RPATH
        ${CMAKE_CURRENT_SOURCE_DIR}/../libBFCPClt/Depends/OpenSSL/lib/${CMAKE_SYSTEM_PROCESSOR}
	${CMAKE_CURRENT_SOURCE_DIR}/../libBFCPClt/Depends/libBFCPMsg/lib/${CMAKE_SYSTEM_PROCESSOR}
	${CMAKE_CURRENT_SOURCE_DIR}/../libBFCPClt/Bin/${CMAKE_SYSTEM_PROCESSOR}
)

# 设置源文件
set(SOURCE main.c)

# 生成可执行文件
add_executable(${PROJECT_NAME} ${SOURCE})

# 设置头文件路径
target_include_directories(${PROJECT_NAME} PRIVATE 
	${CMAKE_CURRENT_SOURCE_DIR}/../libBFCPClt/Depends/OpenSSL/include
	${CMAKE_CURRENT_SOURCE_DIR}/../libBFCPClt/Depends/libBFCPMsg/include
	${CMAKE_CURRENT_SOURCE_DIR}/../libBFCPClt
)

target_link_libraries(${PROJECT_NAME} PRIVATE
	bfcpclt
	bfcpmsg
	pthread
	ssl
	crypto
)

# 安装可执行文件
install(TARGETS ${PROJECT_NAME} DESTINATION ${INSTALL_PATH})

# CLEAN
add_custom_target(clean-all
	COMMAND ${CMAKE_COMMAND} -P ${CMAKE_BINARY_DIR}/clean-all.cmake
	)

# 在这个文件中，我们将包含所有需要删除的文件
file(WRITE ${CMAKE_BINARY_DIR}/clean-all.cmake "
file(REMOVE_RECURSE ${CMAKE_BINARY_DIR}/${PROJECT_NAME})
file(REMOVE_RECURSE ${CMAKE_BINARY_DIR}/CMakeCache.txt)
file(REMOVE_RECURSE ${CMAKE_BINARY_DIR}/CMakeFiles)
file(REMOVE_RECURSE ${CMAKE_BINARY_DIR}/Makefile)
file(REMOVE_RECURSE ${CMAKE_BINARY_DIR}/cmake_install.cmake)
file(REMOVE_RECURSE ${CMAKE_BINARY_DIR}/install_manifest.txt)
file(REMOVE_RECURSE ${INSTALL_PATH}/${PROJECT_NAME}) # 删除安装目录下的可执行文件
")

