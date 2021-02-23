#include "PointLight.h"

PointLight::PointLight(Vector position, Color color)
{
    _position = position;
    _color = color;
}

const Vector& PointLight::getPosition() const
{
    return _position;
}

const Color PointLight::getColor() const
{
    return _color;
}
