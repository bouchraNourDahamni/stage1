#include <gtest/gtest.h>

#include "filterSpeechTest.h"
#include "filterSpeechTestTrauma.h"
#include "filterSpeechTestTraumaAnkle.h"

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}