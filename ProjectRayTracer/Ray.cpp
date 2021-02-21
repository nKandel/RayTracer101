
#include "Ray.h"


Ray::Ray():_position(Vector(0,0,0)), _direction(Vector(1,0,0))
{}

Ray::Ray(Vector position, Vector direction):_position(position), _direction(direction)
{
    _direction.normalize();
}

const Vector Ray::get_direction() const{
    return _direction;
}
const Vector& Ray::get_position() const{
    return _position;
}
