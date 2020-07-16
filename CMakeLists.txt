cmake_minimum_required(VERSION 3.2)

if($ENV{TRAVIS_BUILD_NUMBER})
	project(matrix VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
	project(matrix VERSION 0.0.1)
endif()

set(LIB_DIR ${CMAKE_SOURCE_DIR}/lib)
add_subdirectory(${LIB_DIR})

add_executable(matrix main.cpp)

set_target_properties(matrix PROPERTIES
	CXX_STANDART 17
	CXX_STANDART_REQUIRED ON
)

target_include_directories(matrix PRIVATE ${LIB_DIR})

target_link_libraries(matrix PRIVATE matrix_lib)

if(MSVC)
	target_compile_options(matrix PRIVATE
		/W4
	)
else()
	target_compile_options(matrix PRIVATE
		-Wall -Wextra -pedantic -Werror
	)
endif()

install(TARGETS matrix RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)

enable_testing()