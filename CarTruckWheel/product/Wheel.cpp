#include "Wheel.h"
#include <stdexcept>

//TODO implment all methods

Wheel::Wheel(int diameter, const std::string& material)
{
    if(diameter > 0 && material != "")
    {
        this->diameter = diameter;
        this->material = material;
    }
    else
    {
        throw std::invalid_argument("invalid argument");
    }
}

std::string Wheel::GetMaterial() const
{
    return material;
}

void Wheel::SetMaterial(const std::string& material)
{
    this->material = material;
}

int Wheel::GetDiameter() const
{
    return diameter;
}