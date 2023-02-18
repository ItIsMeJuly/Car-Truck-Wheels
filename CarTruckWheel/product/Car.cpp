#include "Car.h"
#include "Wheel.h"

#include <iostream>
#include <stdexcept>

#ifdef SHOW_CTORS
#define TRACE(txt) std::cout << txt << std::endl
#else
#define TRACE(txt)
#endif

Car::Car(const std::string &model, const std::string &material, int diameter,
         int nrWheels)
{
    TRACE("car constructor called!");
    if (diameter > 0 && nrWheels > 2 && model != "")
    {
        this->model = model;
        for (int i = 0; i < nrWheels; i++)
        {
            wheels.push_back(new Wheel(diameter, material));
        }
    }
    else{
        throw std::invalid_argument("invalid argument");
    }
}

Car::Car(const Car &other) : model(other.GetModel()), licencePlate(other.GetLicencePlate())
{
    TRACE("car copy constructor called!");
    for (auto &wheel : other.wheels)
    {
        wheels.push_back(new Wheel(wheel->GetDiameter(), wheel->GetMaterial()));
    }
}

Car &Car::operator=(const Car &obj)
{
    if (&obj == this)
    {
        return *this;
    }
    // delete old data
    for (auto &wheel : wheels)
    {
        delete wheel;
        wheel = nullptr;
    }
    wheels.clear();
    
    this->model = obj.model;
    this->licencePlate = obj.licencePlate;
    for (int i = 0; i < obj.GetNrWheels(); i++)
    {
        this->wheels.push_back(new Wheel(obj.GetWheel(i)->GetDiameter(), obj.GetWheel(i)->GetMaterial()));
    }
    return *this;
}

Car::~Car()
{
    TRACE("car destructor called!");
    for(auto& wheel : wheels)
    {
        delete wheel;
        wheel = nullptr;
    }
    wheels.clear();
}

const Wheel *Car::GetWheel(int index) const
{
    if (index < 0 || GetNrWheels() <= index)
    {
        throw std::invalid_argument("illegal index");
    }
    return wheels[index];
}

// /////////////////////////////////////////////////////////////////////////////
// TODO: implement all other methods

std::string Car::GetModel() const
{
    return model;
}

void Car::SetLicencePlate(const std::string &licencePlate)
{
    this->licencePlate = licencePlate;
}

std::string Car::GetLicencePlate() const
{
    return licencePlate;
}

int Car::GetNrWheels() const
{
    return wheels.size();
}

// delete the wheel on an index
void Car::RemoveWheel(int index)
{
    if (index < 0 || index > GetNrWheels())
    {
        throw std::out_of_range("index out of range");
    }
    delete wheels.at(index);
    wheels.at(index) = nullptr;
}

// find the nullptr wheel index and initialize it with new wheel
void Car::AddWheel(int diameter, const std::string &material)
{
    for (auto &wheel : wheels)
    {
        if (wheel == nullptr)
        {
            wheel = new Wheel(diameter, material);
            return;
        }
    }
    // if no wheel is missing just return
}