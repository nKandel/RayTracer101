#include "Sphere.h"

Sphere::Sphere(): 
    _position(Vector(0,0,0)), 
    _radius(0.0), 
    _color(Color({0,0,0}))
{}

Sphere::Sphere(Vector p, float r, Color c): 
    _position(p), 
    _radius(r), 
    _color(c)
{}

float Sphere::intersection(const Ray& r) const
{    
    Vector rayPosition = r.getPosition();
    Vector rayDirection = r.getDirection();
    Vector oc = rayPosition-_position;    
    float intersectionDistance = -1;
    float a = rayDirection*rayDirection;
    float b = 2.0*(rayDirection*oc);
    float c = oc*oc - _radius*_radius;
    float discriminant = b*b-4*a*c;
    
    if(discriminant<0){
        // no intersection
    } else {
        float t_minus = (-b-std::sqrt(discriminant))/(2*a);
        float t_plus = (-b+std::sqrt(discriminant))/(2*a);
        if(t_minus>=0){
            // intersection at tangent or double intersection or light source at surface
            intersectionDistance = t_minus;
        } else if (t_plus>0){
            // light source inside the sphere
            intersectionDistance = t_plus;
        }else{
            // no intersection, light source infront of sphere but pointing toward opposite direction
        }
    }
    return intersectionDistance;

}

const Color Sphere::getColor(const Vector& intersectionPoint, const vector<PointLight*> pointLights)
{
    Color sumLightColorOnSurface({0, 0, 0}) ;
    for(unsigned int i=0; i<pointLights.size(); ++i)
    {
        PointLight* pointLight = pointLights[i];
        Vector lightDirection = intersectionPoint - pointLight->getPosition();
        lightDirection.normalize();

        // surface normal
        Vector surfaceNormal = intersectionPoint - _position;
        surfaceNormal.normalize();
        float surfaceReflectivityForLightSource = std::max((-surfaceNormal*lightDirection)/M_PI, 0.0);
        Color surfaceColorForLightSource = pointLight->getColor()*surfaceReflectivityForLightSource;
        sumLightColorOnSurface = sumLightColorOnSurface+surfaceColorForLightSource;
    }
    // total color = surface's color * color due to refelectivity of the light source
    return _color*sumLightColorOnSurface;
}
