# Library
include_directories(include)
add_library(blcknx STATIC
        src/Challenge.cpp
        src/CharacterTable.cpp
        src/AlignmentScoreMeasurer.cpp
        src/Aligner.cpp
        src/TableReader.cpp
        src/Alignment.cpp
        src/AlignmentScoreProviders/Blosum62ScoreProvider.cpp
        src/AlignmentScoreProviders/Pam250ScoreProvider.cpp
        src/AlignmentScoreProviders/LongestCommenSubsequenceScoreProvider.cpp
        src/AlignmentScoreProviders/EditDistanceScoreProvider.cpp
        src/AlignmentScoreProviders/MismatchScoreProvider.cpp
        )

# Testing
include(CTest)
add_executable(ChallengeTest
        include/Challenge.h
        tests/ChallengeTest.cpp
        )
target_link_libraries(ChallengeTest gtest gtest_main blcknx)
add_test(NAME Challenge COMMAND ChallengeTest)

include(CTest)
add_executable(CharacterTableTest
        include/CharacterTable.h
        tests/CharacterTableTest.cpp
        )
target_link_libraries(CharacterTableTest gtest gtest_main blcknx)
add_test(NAME CharacterTable COMMAND CharacterTableTest)

add_executable(AlignmentScoreMeasurerTest include/AlignmentScoreMeasurer.h
        tests/AlignmentScoreMeasurerTest.cpp)
target_link_libraries(AlignmentScoreMeasurerTest gtest gtest_main blcknx)
add_test(NAME AlignmentScoreMeasurer COMMAND AlignmentScoreMeasurerTest)

add_executable(AlignerTest include/Aligner.h
        tests/AlignerTest.cpp)
target_link_libraries(AlignerTest gtest gtest_main blcknx)
add_test(NAME Aligner COMMAND AlignerTest)

add_executable(TableReaderTest
        tests/TableReaderTest.cpp
        include/TableReader.h
        )
target_link_libraries(TableReaderTest gtest gtest_main blcknx)
add_test(NAME TableReader COMMAND TableReaderTest)

add_executable(Pam250ScoreProviderTest
        tests/Pam250ScoreProviderTest.cpp
        include/AlignmentScoreProviderInterface.h
        include/Pam250ScoreProvider.h
        )
target_link_libraries(Pam250ScoreProviderTest gtest gtest_main blcknx)
add_test(NAME Pam250ScoreProvider COMMAND Pam250ScoreProviderTest)

add_executable(Blosum62ScoreProviderTest
        tests/Blosum62ScoreProviderTest.cpp
        include/AlignmentScoreProviderInterface.h
        include/Blosum62ScoreProvider.h
        )
target_link_libraries(Blosum62ScoreProviderTest gtest gtest_main blcknx)
add_test(NAME Blosum62ScoreProvider COMMAND Blosum62ScoreProviderTest)

add_executable(LongestCommenSubsequenceScoreProviderTest
        tests/LongestCommenSubsequenceScoreProviderTest.cpp
        include/AlignmentScoreProviderInterface.h
        include/LongestCommenSubsequenceScoreProvider.h
        )
target_link_libraries(LongestCommenSubsequenceScoreProviderTest gtest gtest_main blcknx)
add_test(NAME LongestCommenSubsequenceScoreProvider COMMAND LongestCommenSubsequenceScoreProviderTest)

add_executable(EditDistanceScoreProviderTest
        tests/EditDistanceScoreProviderTest.cpp
        include/AlignmentScoreProviderInterface.h
        include/EditDistanceScoreProvider.h
        )
target_link_libraries(EditDistanceScoreProviderTest gtest gtest_main blcknx)
add_test(NAME EditDistanceScoreProvider COMMAND EditDistanceScoreProviderTest)

add_executable(MismatchScoreProviderTest
        tests/MismatchScoreProviderTest.cpp
        include/AlignmentScoreProviderInterface.h
        include/MismatchScoreProvider.h
        )
target_link_libraries(MismatchScoreProviderTest gtest gtest_main blcknx)
add_test(NAME MismatchScoreProvider COMMAND MismatchScoreProviderTest)

add_executable(AlignmentTest
        tests/AlignmentTest.cpp
        include/AlignmentScoreProviderInterface.h
        include/Alignment.h
        )
target_link_libraries(AlignmentTest gtest gtest_main blcknx)
add_test(NAME Alignment COMMAND AlignmentTest)
