# Library
include_directories(include)
add_library(blcknx STATIC
        src/Challenge.cpp
        src/EditDistanceAlignment.cpp
        )

# Testing
add_executable(ChallengeTest
        include/Challenge.h
        tests/ChallengeTest.cpp
        )
target_link_libraries(ChallengeTest gtest gtest_main blcknx)
add_test(NAME Challenge COMMAND ChallengeTest)

add_executable(EditDistanceAlignmentTest
        include/EditDistanceAlignment.h
        tests/EditDistanceAlignmentTest.cpp
        )
target_link_libraries(EditDistanceAlignmentTest gtest gtest_main blcknx)
add_test(NAME EditDistanceAlignmentTest COMMAND EditDistanceAlignmentTest)

