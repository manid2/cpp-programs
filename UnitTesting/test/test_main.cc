// gtest and gmock example, main functions
#include "test_precomp.hh"

int main(int argc, char **argv)
{
    // The following line must be executed to initialize Google Mock
    // (and Google Test) before running the tests.
    ::testing::InitGoogleMock(&argc, argv);
    //::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
