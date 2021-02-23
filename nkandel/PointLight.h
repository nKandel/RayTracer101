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

#endif // ___POINTLIGHT_H____
