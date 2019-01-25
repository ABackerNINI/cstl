cmake_minimum_required (VERSION 3.8)

project ("cstl")

add_executable(test_cforward_list test/test_cforward_list.c
	cstl/cforward_list.h
)

add_executable(test_cstring test/test_cstring.c
	cstl/cstring.h
)

add_executable(test_cstack test/test_cstack.c
	cstl/cstack.h
)

add_executable(test_cvector test/test_cvector.c
	cstl/cvector.h
)