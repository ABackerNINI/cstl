cmake_minimum_required (VERSION 3.8)

project ("cstl")

set(CLIST_SRC
	clist/clist.h
	clist/clist.c
)

set(CFORWARD_LIST_SRC
	cforward_list/cforward_list.h
)

set(CSTRING_SRC
	cstring/cstring.h
)

set(CSTACK_SRC
	cstack/cstack.h
)

add_executable(test_cforward_list test/test_cforward_list.c
	${CFORWARD_LIST_SRC}
)

add_executable(test_cstring test/test_cstring.c
	${CSTRING_SRC}
)

add_executable(test_cstack test/test_cstack.c
	${CSTACK_SRC}
)