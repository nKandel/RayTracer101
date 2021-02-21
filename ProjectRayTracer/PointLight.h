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
        const Vector& get_position() const;
        const Color get_color() const;
};

PointLight::PointLight(Vector position, Color color){
    _position = position;
    _color = color;
}
const Vector& PointLight::get_position() const{
    return _position;
}

const Color PointLight::get_color() const{
    return _color;
}

#endif // ___POINTLIGHT_H____
