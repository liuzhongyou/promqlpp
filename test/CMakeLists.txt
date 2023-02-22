find_package(GTest)

if (GTEST_FOUND)
    include(GoogleTest)

    set(HEADERS
            ${PROJECT_SOURCE_DIR}/include)

    file(GLOB SOURCES
            # Unit Tests
            time/duration.cpp
            time/time.cpp

            ast/expr.cpp

            parser/lex.cpp
            parser/parser.cpp

            main.cpp)

    add_executable(unittest ${SOURCES})
    target_include_directories(unittest PRIVATE ${HEADERS})
    target_link_libraries(unittest gtest)

    gtest_add_tests(TARGET unittest)
endif ()
