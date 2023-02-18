#include "Truck.h"
#include <iostream>

// TODO : implement all methods
Truck::Truck(const std::string &model, const std::string &material, int diameter, int nrWheels, int power) : Car(model, material, diameter, nrWheels)
{
    if (power > 0)
    {
        this->power = new int(power);
    }
}

Truck::Truck(const Truck &obj) : Car(obj.GetModel(), obj.GetWheel(0)->GetMaterial(), obj.GetWheel(0)->GetDiameter(), obj.GetNrWheels())
{
    this->power = new int(obj.GetPower());
}

Truck::~Truck()
{
    delete power;
    power = nullptr;
}

Truck &Truck::operator=(const Truck &other) 
{
    if (&other == this)
    {
        return *this;
    }
    
    // call copy assignment explicitly
    Car::operator=(other);

    delete power;
    power = new int(other.GetPower());
    
    return *this;
}

int Truck::GetPower() const
{
    return *power;
}