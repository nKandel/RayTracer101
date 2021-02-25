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
    Color sumLightColorOnSurface({0, 0, 0}) ;
    for(unsigned int i=0; i<pointLights.size(); ++i)
    {
        PointLight* pointLight = pointLights[i];
        Vector lightDirection = intersectionPoint-pointLight->getPosition();
        lightDirection.normalize();        
        float surfaceReflectivityForLightSource = std::max((-_normalDirection*lightDirection)/M_PI, 0.0);
        Color surfaceColorForLightSource = pointLight->getColor()*surfaceReflectivityForLightSource;
        sumLightColorOnSurface = sumLightColorOnSurface+surfaceColorForLightSource;
    }
    // total color = surface's color * color due to refelectivity of the light source
    return _color*sumLightColorOnSurface;
}

float Plane::intersection(const Ray& r) const
{
    Vector rayPosition = r.getPosition();
    Vector rayDirection = r.getDirection().normal();
    double denom = _normalDirection*rayDirection;
    // checking whether ray parallel to the plane or not (divide by zero)
    if (abs(denom) > 0.0001f) {
        float t = (_position - rayPosition)*_normalDirection / denom;
        if (t >= 0){
            return t;
        }
    }
    return -1.0;
}
