
#include "Ray.h"


Ray::Ray():_position(Vector(0,0,0)), _direction(Vector(1,0,0))
{}

Ray::Ray(Vector position, Vector direction):_position(position), _direction(direction)
{
    _direction.normalize();
}

const Vector Ray::getDirection() const{
    return _direction;
}
const Vector& Ray::getPosition() const{
    return _position;
}

const Vector Ray::getIntersectionPoint(float t) const{
    return _position+t*_direction;
}
