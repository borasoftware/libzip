CHECK_FUNCTION_EXISTS(getopt HAVE_GETOPT)
IF(NOT HAVE_GETOPT)
  SET(SRC_EXTRA_FILES ../src/getopt.c)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/../src)
ENDIF(NOT HAVE_GETOPT)

ADD_EXECUTABLE(in-memory in-memory.c)
TARGET_LINK_LIBRARIES(in-memory zip)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../lib
	${CMAKE_CURRENT_SOURCE_DIR}/../src
	${CMAKE_CURRENT_BINARY_DIR}/..)

ADD_EXECUTABLE(race race.c)
TARGET_LINK_LIBRARIES(race zip pthread)

add_custom_target(
	RunHelgrind
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/examples
	COMMAND sh valgrind --tool=helgrind --vgdb=no --trace-children=yes --read-inline-info=yes --fair-sched=yes ./race > helgrind2.log 2>&1
)
