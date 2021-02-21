#ifndef ___PLANE_H____
#define ___PLANE_H____

#include "Vector.h"
#include "Ray.h"
#include "Object.h"
/*

*/
using namespace chromeball;

class Plane : public Object {
    private:
        Vector _position;
        Vector _normalDirection;
        Color _color;
    public:
        Plane();
        Plane(Vector, Vector, Color);

        float intersection(const Ray& r) const;
        const Color& getColor() const;
        ~Plane(){};
};

Plane::Plane(){
    // initialize the variable
}

Plane::Plane(Vector position, Vector normalDirection, Color color):
_position(position), _normalDirection(normalDirection.normal()), _color(color)
{
}

const Color& Plane::getColor() const{
    return _color;
}

float Plane::intersection(const Ray& r) const{
    // no intersection
    // https://stackoverflow.com/a/23976134/1406040
    Vector rayPosition = r.get_position();
    Vector rayDirection = r.get_direction().normal();
    double denom = _normalDirection*rayDirection;
    if (abs(denom) > 0.0001f) {
        float t = (_position - rayPosition)*_normalDirection / denom;
        if (t >= 0){
            return t;
        }
    }
    return -1.0;
}
#endif
