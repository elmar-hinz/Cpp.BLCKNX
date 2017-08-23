# Library
include_directories(include)
add_library(blcknx STATIC
        src/Challenge.cpp
        src/AlignmentScoreMeasurer.cpp
        src/EditDistanceAlignment.cpp
        src/AlignmentScoreEvalutators/Blosum62ScoreEvaluator.cpp
        src/AlignmentScoreEvalutators/LongestCommenSubsequenceScoreEvaluator.cpp
        )

# Testing
include(CTest)
add_executable(ChallengeTest
        include/Challenge.h
        tests/ChallengeTest.cpp
        )
target_link_libraries(ChallengeTest gtest gtest_main blcknx)
add_test(NAME Challenge COMMAND ChallengeTest)

add_executable(AlignmentScoreMeasurerTest include/AlignmentScoreMeasurer.h
        tests/AlignmentScoreMeasurerTest.cpp)
target_link_libraries(AlignmentScoreMeasurerTest gtest gtest_main blcknx)
add_test(NAME AlignmentScoreMeasurer COMMAND AlignmentScoreMeasurerTest)

add_executable(EditDistanceAlignmentTest include/EditDistanceAlignment.h
        tests/EditDistanceAlignmentTest.cpp)
target_link_libraries(EditDistanceAlignmentTest gtest gtest_main blcknx)
add_test(NAME EditDistanceAlignment COMMAND EditDistanceAlignmentTest)

add_executable(Blosum62ScoreEvaluatorTest
        tests/Blosum62ScoreEvaluatorTest.cpp
        include/AlignmentScoreEvaluatorInterface.h
        include/Blosum62ScoreEvaluator.h
        )
target_link_libraries(Blosum62ScoreEvaluatorTest gtest gtest_main blcknx)
add_test(NAME Blosum62ScoreEvaluator COMMAND Blosum62ScoreEvaluatorTest)

add_executable(LongestCommenSubsequenceScoreEvaluatorTest
        tests/LongestCommenSubsequenceScoreEvaluatorTest.cpp
        include/AlignmentScoreEvaluatorInterface.h
        include/LongestCommenSubsequenceScoreEvaluator.h
        )
target_link_libraries(LongestCommenSubsequenceScoreEvaluatorTest gtest gtest_main blcknx)
add_test(NAME LongestCommenSubsequenceScoreEvaluator COMMAND LongestCommenSubsequenceScoreEvaluatorTest)
