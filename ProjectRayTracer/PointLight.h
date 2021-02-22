#ifndef ___POINTLIGHT_H____
#define ___POINTLIGHT_H____
#include "Vector.h"

using namespace chromeball;
using namespace std;

class PointLight{
    private:
        Vector _position;
        Color _color;
    public:
        PointLight();
        PointLight(Vector, Color);
        ~PointLight(){};
        const Vector& getPosition() const;
        const Color getColor() const;
};

PointLight::PointLight(Vector position, Color color){
    _position = position;
    _color = color;
}
const Vector& PointLight::getPosition() const{
    return _position;
}

const Color PointLight::getColor() const{
    return _color;
}

#endif // ___POINTLIGHT_H____
