SET(BINARY ${CMAKE_PROJECT_NAME}_test)
SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/build )

file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false ../test/*.h ../test/*.cpp)
SET(SOURCES ${TEST_SOURCES})

add_executable(${BINARY} ${TEST_SOURCES})
add_test(NAME ${BINARY} COMMAND ${BINARY})


target_link_libraries(${BINARY} PUBLIC staticSample gtest)