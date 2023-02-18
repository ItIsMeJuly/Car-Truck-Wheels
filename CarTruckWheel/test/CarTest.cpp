#include "Car.h"

#include <gtest/gtest.h>
#include <stdexcept>
#include <string>

class CarTest : public ::testing::Test
{

protected:
    CarTest() { c = new Car("Aston Martin Vanquish", "Alloy", 20, 4); }

    virtual ~CarTest()
    {
        delete c;
        c = NULL;
    }

    void CheckWheels(int n); // example of a method within the cartest class

    Car *c;
};

void CarTest::CheckWheels(int n)
{
    // just an example which need to be completed
    for (int i = 0; i < n; i++)
    {
        const Wheel *w = c->GetWheel(i);
        ASSERT_TRUE(w != NULL);
        ASSERT_EQ("Alloy", w->GetMaterial());
        ASSERT_EQ(20, w->GetDiameter());
        // not everything is tested. to be finished
    }
}


TEST_F(CarTest, test_ifAllWheelsAreThere)
{
    Car *car = new Car("Aston Martin Vanquish", "Alloy", 20, 4); // memory leak
    const Wheel *w = car->GetWheel(2);
    ASSERT_TRUE(w != NULL);
    CheckWheels(4);
    delete car;
}

// test for successful construction
TEST_F(CarTest, test_constructorOfCar)
{
    ASSERT_EQ("Aston Martin Vanquish", c->GetModel());
    ASSERT_EQ(4, c->GetNrWheels());
}

// check for no enough wheels
TEST_F(CarTest, test_constructorOfCar2)
{
    try
    {
        Car car("Aston Martin Vanquish", "Alloy", 20, 2);
    }
    catch(std::invalid_argument& arg)
    {
        // if exception is thrown for illegal argument test passes
        ASSERT_TRUE(1);
    }
}

// check for no diameter
TEST_F(CarTest, test_constructorOfCar3)
{
    try
    {
        Car car("Aston Martin Vanquish", "Alloy", 0, 2);
    }
    catch(std::invalid_argument& arg)
    {
        ASSERT_TRUE(1);
    }
}

// check for no model
TEST_F(CarTest, test_constructorOfCar4)
{
    try
    {
        Car car("", "Alloy", 0, 2);
    }
    catch(std::invalid_argument& arg)
    {
        ASSERT_TRUE(1);
    }
}

// accessing deleted data to check for successful deletion
TEST_F(CarTest, test_carDestructor)
{

    ASSERT_TRUE(c->GetWheel(0) != nullptr);
    c->~Car();
    try
    {
        c->GetWheel(3);
    }
    catch(const std::exception& e)
    {
        // if an exception was thrown, that means the destructor successfuly deleted the memory and erased the elemenets
        ASSERT_TRUE(1);
    }
}

// test for deep copy
TEST_F(CarTest, test_copyConstructor)
{
    Car copy("test", " test", 8, 4);
    Car *car = new Car(copy);

    EXPECT_EQ(copy.GetModel(), car->GetModel());
    for (int i = 0; i < 4; i++)
    {
        ASSERT_TRUE(copy.GetWheel(i) != car->GetWheel(i));
        EXPECT_EQ(copy.GetWheel(i)->GetMaterial(), car->GetWheel(i)->GetMaterial());
        EXPECT_EQ(copy.GetWheel(i)->GetDiameter(), car->GetWheel(i)->GetDiameter());
    }

    delete car;
}

// check if we returned the same object without new allocation
TEST_F(CarTest, test_copyAssignment1)
{
    Car copy("test", " test", 8, 4);
    Car* addressOfCopy = &copy;
    copy = copy;
    ASSERT_TRUE(addressOfCopy == &copy);
    for(int i = 0 ; i < 4 ; i++)
    {
        EXPECT_TRUE(addressOfCopy->GetWheel(i) == copy.GetWheel(i));
    }
}

// check for deep copy
TEST_F(CarTest, test_copyAssignment2)
{
    Car car1("test", "test", 8, 4);
    Car copy("non", "non", 3, 3);
    copy = car1;
    for(int i = 0 ; i < 4 ; i++)
    {
        ASSERT_TRUE(car1.GetWheel(i) != copy.GetWheel(i));
        ASSERT_TRUE(car1.GetWheel(i)->GetDiameter() == copy.GetWheel(i)->GetDiameter());
        ASSERT_TRUE(car1.GetWheel(i)->GetMaterial() == copy.GetWheel(i)->GetMaterial());

        // because both objects are the same we check the values of one of them
        ASSERT_EQ(car1.GetWheel(i)->GetDiameter(), 8);
        ASSERT_EQ(car1.GetWheel(i)->GetMaterial(), "test");
    }
    ASSERT_TRUE(car1.GetNrWheels() == copy.GetNrWheels());
}

