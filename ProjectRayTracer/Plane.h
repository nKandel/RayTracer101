#ifndef ___PLANE_H____
#define ___PLANE_H____
#include <vector>
#include "Vector.h"
#include "Ray.h"
#include "PointLight.h"
#include "SceneObject.h"
/*

*/

#if defined __linux__ || defined __APPLE__

#else
// Windows doesn't define these values by default, Linux does
#define M_PI 3.141592653589793
#endif

using namespace chromeball;

class Plane : public SceneObject {
    private:
        Vector _position;
        Vector _normalDirection;
        Color _color;
    public:
        Plane();
        Plane(Vector, Vector, Color);

        float intersection(const Ray& r) const;
        const Color getColor(const Vector&, const vector<PointLight*>);
        ~Plane(){};
};

Plane::Plane()
{
    // initialize the variable
}

Plane::Plane(Vector position, Vector normalDirection, Color color):
_position(position), _normalDirection(normalDirection.normal()), _color(color)
{
}

const Color Plane::getColor(const Vector& intersectionPoint, const vector<PointLight*> pointLights)
{
    Color c_sum({0, 0, 0}) ;
    for(unsigned int i=0; i<pointLights.size(); ++i)
    {
        PointLight* pointLight = pointLights[i];
        Vector L = intersectionPoint-pointLight->getPosition();
        L.normalize();
        // confusion: normal direction (ns ?)
        float ri = std::max((-_normalDirection*L)/M_PI, 0.0);
        Color tempColor = pointLight->getColor()*ri;
        c_sum = c_sum+tempColor;
    }
    return _color*c_sum;
}

float Plane::intersection(const Ray& r) const{
    // no intersection
    // https://stackoverflow.com/a/23976134/1406040
    Vector rayPosition = r.getPosition();
    Vector rayDirection = r.getDirection().normal();
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
