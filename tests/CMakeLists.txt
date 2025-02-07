set(TEST_SOURCES
        testeur.cpp
        ${PROJECT_SOURCE_DIR}/ContratException.cpp
        ${PROJECT_SOURCE_DIR}/Bottin.cpp
        ${PROJECT_SOURCE_DIR}/TableHachage.hpp
        ${PROJECT_SOURCE_DIR}/FoncteurHachage.hpp
)

add_executable(testeur ${TEST_SOURCES})

target_include_directories(testeur PRIVATE ${PROJECT_SOURCE_DIR})

target_link_libraries(testeur gtest gtest_main)

include(GoogleTest)
gtest_discover_tests(testeur)
add_custom_command(
        TARGET testeur POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${PROJECT_SOURCE_DIR}/Bottin.txt
        $<TARGET_FILE_DIR:testeur>
)