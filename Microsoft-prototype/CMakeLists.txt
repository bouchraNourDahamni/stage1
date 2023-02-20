cmake_minimum_required (VERSION 3.14 FATAL_ERROR)
project(SpeechRecMicrosoft LANGUAGES CXX)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if (NOT DEFINED CMAKE_CXX_STANDARD)
	set(CMAKE_CXX_STANDARD 17)
	set(CMAKE_CXX_STANDARD_REQUIRED True)
endif()

add_executable(SpeechRecMicrosoft
 	main.cpp
	Data.h
	Feature.h
	Feature.cpp
	filterSpeech.cpp
	filterSpeech.h
	SpeechRecognizer.h
	SpeechRecognizer.cpp
	Tool.h
	Tool.cpp
    ToolHandleType.h
    ToolPropertySearch.h
    StringData.h
    SurgeryType.h
    SurgeryType.cpp
    ToolWithSizes.cpp
    ToolWithSizes.h
    Screw.h
    Screw.cpp
    ScrewSizes.h
    TextToSpeech.h
    FormatResult.h
    Data.cpp
    AttentionUser.h
    TextTospeech.cpp
    ScrewTrauma.cpp
    StringData.cpp
    ScrewTrauma.h
)
enable_testing()
add_subdirectory(test)

