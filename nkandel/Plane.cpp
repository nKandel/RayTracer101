#include "Plane.h"

Plane::Plane()
{
    // initialize the variable
}

Plane::Plane(Vector position, Vector normalDirection, Color color):
    _position(position),
    _normalDirection(normalDirection.normal()),
    _color(color)
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

float Plane::intersection(const Ray& r) const
{
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
