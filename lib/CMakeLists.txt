cmake_minimum_required(VERSION 3.2)

project(matrix_lib)

add_library(matrix_lib matrix_lib.cpp)

set_target_properties(matrix_lib PROPERTIES
	CXX_STANDART 17
	CXX_STANDART_REQUIRED ON
)

if(MSVC)
	target_compile_options(matrix_lib PRIVATE
		/W4
	)
else()
	target_compile_options(matrix_lib PRIVATE
		-Wall -Wextra -pedantic -Werror
	)
endif()