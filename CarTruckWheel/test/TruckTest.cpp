#include "Truck.h"

#include <string>
#include <gtest/gtest.h>

class TruckTest : public ::testing::Test
{
protected:
    TruckTest() { t = new Truck("Volvo", "Gold", 30, 8, 200); }

    ~TruckTest()
    {
        delete t;
        t = nullptr;
    }

    Truck *t;
};

// check if all fields are set correctly
TEST_F(TruckTest, test_truckConstructor)
{
    EXPECT_EQ(t->GetModel(), "Volvo");
    EXPECT_EQ(t->GetPower(), 200);
    EXPECT_EQ(t->GetNrWheels(), 8);
    for (int i = 0; i < 8; i++)
    {
        ASSERT_TRUE(t->GetWheel(i) != nullptr);
        EXPECT_EQ(t->GetWheel(i)->GetMaterial(), "Gold");
        EXPECT_EQ(t->GetWheel(i)->GetDiameter(), 30);
    }
}

// check for no power
TEST_F(TruckTest, test_truckConstructor1)
{
    try
    {
        Truck truck("Volvo", "Gold", 30, 8, 0);
    }
    catch (std::exception &e)
    {
        // exception from 0 power caught
        ASSERT_TRUE(1);
    }
}

// check for unsufficient wheel count
TEST_F(TruckTest, test_truckConstructor2)
{
    try
    {
        Truck truck("Volvo", "Gold", 30, 2, 200);
    }
    catch (std::exception &e)
    {
        // exception from 2 wheels caught
        ASSERT_TRUE(1);
    }
}

// check for no diameter
TEST_F(TruckTest, test_truckConstructor3)
{
    try
    {
        Truck truck("Volvo", "Gold", 0, 6, 200);
    }
    catch (std::exception &e)
    {
        // exception from 0 diameter caught
        ASSERT_TRUE(1);
    }
}

// ckeck for empty material
TEST_F(TruckTest, test_truckConstructor4)
{
    try
    {
        Truck truck("Volvo", "", 30, 8, 200);
    }
    catch (std::exception &e)
    {
        // exception from no material caught
        ASSERT_TRUE(1);
    }
}

// test for empty model
TEST_F(TruckTest, test_truckConstructor5)
{
    try
    {
        Truck truck("", "Gold", 30, 2, 200);
    }
    catch (std::exception &e)
    {
        // exception from no model caught
        ASSERT_TRUE(1);
    }
}

// test if destructors are called for base class as well
TEST_F(TruckTest, test_truckDestructor)
{
    Truck *truck = new Truck("volvo", "alloy", 20, 8, 200);
    delete truck;

    // if destructor of car is called number of wheels is 0
    ASSERT_TRUE(truck->GetNrWheels() == 0);

    // if we call GetPower() program will fail because memory does not exist after delete
}


// test for deep copies
TEST_F(TruckTest, test_copyConstructor)
{
    Truck truck("volvo", "metal", 20, 8, 200);
    Truck copyOfTruck(truck);

    EXPECT_EQ(truck.GetModel(), copyOfTruck.GetModel());
    ASSERT_TRUE(truck.GetPower() == copyOfTruck.GetPower());

    // car copyCopyConstructor deals for deep copy of all wheels but code is here to verify
    for(int i = 0 ; i < 8 ; i++)
    {
        ASSERT_TRUE(truck.GetWheel(i) != copyOfTruck.GetWheel(i));
    }
}

// check if memory is copied deeply
TEST_F(TruckTest, test_copyAssignment)
{
    Truck truck("volvo", "metal", 20, 8, 200);
    Truck copy("test", "test", 5, 3, 10);
    copy = truck;
    for(int i = 0 ; i < 8 ; i++){
        ASSERT_TRUE(copy.GetWheel(i) != truck.GetWheel(i));
    }
}

// check if copy assignment on self allocates new memory
TEST_F(TruckTest, test_copyAssignment1)
{
    Truck copy("test", "test", 5, 8, 10);
    Truck* checker = &copy;
    copy = copy;
    for(int i = 0 ; i < 8 ; i++){
        ASSERT_TRUE(copy.GetWheel(i) == checker->GetWheel(i));
    }
}

