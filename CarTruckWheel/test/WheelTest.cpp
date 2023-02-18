#include "Wheel.h"

#include <string>
#include <gtest/gtest.h>
#include <stdexcept>

class WheelTest : public ::testing::Test
{

protected:
    WheelTest() { c = new Wheel(20, "Alloy"); }

    virtual ~WheelTest()
    {
        delete c;
        c = NULL;
    }

    
    Wheel *c;
};

// check if constructor initializes correctly
TEST_F(WheelTest, test_wheelConstructor)
{
    Wheel wheel(20, "Metal");
    ASSERT_EQ(wheel.GetMaterial(), "Metal");
    ASSERT_EQ(wheel.GetDiameter(), 20);
}

// check for no diameter
TEST_F(WheelTest, test_wheelConstructor1)
{
    try
    {
        Wheel wheel(-1, "Metal");
    }
    catch(std::exception& e)
    {
        // if exception is caught construction failed because of the invalid argument
        ASSERT_TRUE(1);
    }
}

// check for no material
TEST_F(WheelTest, test_wheelConstructor2)
{
    try
    {
        Wheel wheel(18, "");
    }
    catch(std::exception& e)
    {
        // if exception is caught construction failed because of the invalid argument
        ASSERT_TRUE(1);
    }
}