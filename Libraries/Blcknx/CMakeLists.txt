# Library
include_directories(include)
add_library(blcknx STATIC
        src/Challenge.cpp
        src/EditDistance.cpp
        src/EditDistanceAlignment.cpp
        src/Blosum62.cpp
        )

# Testing
include(CTest)
add_executable(ChallengeTest
        include/Challenge.h
        tests/ChallengeTest.cpp
        )
target_link_libraries(ChallengeTest gtest gtest_main blcknx)
add_test(NAME Challenge COMMAND ChallengeTest)

add_executable(EditDistanceTest include/EditDistance.h
        tests/EditDistanceTest.cpp)
target_link_libraries(EditDistanceTest gtest gtest_main blcknx)
add_test(NAME EditDistance COMMAND EditDistanceTest)

add_executable(EditDistanceAlignmentTest include/EditDistanceAlignment.h
        tests/EditDistanceAlignmentTest.cpp
        )
target_link_libraries(EditDistanceAlignmentTest gtest gtest_main blcknx)
add_test(NAME EditDistanceAlignment COMMAND EditDistanceAlignmentTest)

add_executable(Blosum62Test include/Blosum62.h tests/Blosum62Test.cpp)
target_link_libraries(Blosum62Test gtest gtest_main blcknx)
add_test(NAME Blosum62 COMMAND Blosum62Test)
