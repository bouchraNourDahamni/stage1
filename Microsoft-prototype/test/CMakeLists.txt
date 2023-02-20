cmake_minimum_required (VERSION 3.14 FATAL_ERROR)

include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.10.0
)
FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED)
    FetchContent_Populate(googletest)
    set(CMAKE_SUPPRESS_DEVELOPER_WARNINGS 1 CACHE BOOL "")
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
    unset(CMAKE_SUPPRESS_DEVELOPER_WARNINGS)
endif()

set_target_properties(gtest gtest_main gmock gmock_main
    PROPERTIES FOLDER "Extern")

add_executable(SpeechRecMicrosoftTest
	main.cpp

	filterSpeechTest.h
    filterSpeechTestTrauma.h
    filterSpeechTestTraumaAnkle.h

	../Data.h
	../Feature.h
	../Feature.cpp
	../filterSpeech.cpp
	../filterSpeech.h
	../SpeechRecognizer.h
	../SpeechRecognizer.cpp
	../Tool.h
    ../Data.cpp
    ../AttentionUser.h
	../Tool.cpp
    ../stringData.h
    ../stringData.cpp
    ../ToolHandleType.h
    ../ToolPropertySearch.h
    ../SurgeryType.h
    ../SurgeryType.cpp
    ../ToolWithSizes.cpp
    ../ToolWithSizes.h
    ../Screw.h
    ../Screw.cpp
    ../ScrewSizes.h
    ../TextToSpeech.h
    ../TextTospeech.cpp
    ../ScrewTrauma.cpp
    ../ScrewTrauma.h
    ../FormatResult.h
)

target_link_libraries(SpeechRecMicrosoftTest gtest gmock gtest_main)
add_test(SpeechRecMicrosoftTest SpeechRecMicrosoftTest)