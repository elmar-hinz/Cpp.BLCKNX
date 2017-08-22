cmake_minimum_required(VERSION 3.8)
project(BLCKNX)

# Compiler
set(CMAKE_CXX_STANDARD 11)

# Directories
set(stronghold_dir ${CMAKE_CURRENT_LIST_DIR}/Challenges)
set(gtest_dir ${CMAKE_CURRENT_LIST_DIR}/Lib/GTest)

# Macros
macro(subdirlist result curdir)
    file(GLOB children RELATIVE ${curdir} ${curdir}/*)
    set(dirlist "")
    foreach (child ${children})
        if (IS_DIRECTORY ${curdir}/${child})
            list(APPEND dirlist ${child})
        endif ()
    endforeach ()
    set(${result} ${dirlist})
endmacro()

macro(ucfirst result word)
    string(SUBSTRING ${word} 0 1 a)
    string(SUBSTRING ${word} 1 100 b)
    string(TOUPPER ${a} A)
    string(CONCAT c ${A} ${b})
    set(${result} ${c})
endmacro()

# Challenges
include_directories(Lib/Blcknx)
add_library(challenges STATIC "Lib/Blcknx/Challenge.cpp")

# Tests
include(CTest)
add_subdirectory(${gtest_dir})
include_directories(${gtest_SOURCE_DIR}/include)

add_executable(ChallengeTest Lib/Blcknx/ChallengeTest.cpp)
target_link_libraries(ChallengeTest gtest gtest_main challenges)

# Proces challenges
subdirlist(challenges ${stronghold_dir})
foreach (upper ${challenges})
    string(TOLOWER ${upper} lower)
    ucfirst(ucfirst ${lower})
    set(challenge_dir ${stronghold_dir}/${upper})
    set(class ${challenge_dir}/${ucfirst}.cpp)
    set(test ${challenge_dir}/${ucfirst}Test.cpp)
    set(main ${challenge_dir}/main.cpp)
    # Challenge
    if (EXISTS ${class} AND EXISTS ${main})
        set(target ${lower})
        add_executable(${target} ${class} ${main})
        target_link_libraries(${target} challenges)
        message("+ ${lower}")
    else ()
        message("- ${lower}")
    endif ()
    # Test
    if (EXISTS ${class} AND EXISTS ${test})
        set(target ${lower}_test)
        add_executable(${target} ${class} ${test})
        target_link_libraries(${target} gtest gtest_main challenges)
        set(name "${ucfirst}")
        add_test(NAME ${name} COMMAND ${target})
        message("+ ${lower} test")
    else ()
        message("- ${lower} test")
    endif ()
endforeach ()


