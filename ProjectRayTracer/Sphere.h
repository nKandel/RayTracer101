
#ifndef ___SPHERE_H____
#define ___SPHERE_H____
#include<cmath>
#include <vector>
#include "Vector.h"
#include "PointLight.h"
#include "SceneObject.h"

using namespace chromeball;

class Sphere: public SceneObject{
    private:
        Vector _position;
        float _radius;
        Color _color;
    public:
        Sphere();
        Sphere(Vector, float, Color);
        ~Sphere(){};
        float intersection(const Ray&) const;
        const Color getColor(const Vector&, const vector<PointLight*> pointLights);
};

Sphere::Sphere(): _position(Vector(0,0,0)), _radius(0.0), _color(Color({0,0,0}))
{
    // initialize position and radius
}

Sphere::Sphere(Vector p, float r, Color c): _position(p), _radius(r), _color(c)
{
}
// TODO: VERIFY INTERSECTION FORMULA
float Sphere::intersection(const Ray& r) const{
    // implement intersection logic here
    // if no intersection
    Vector rayPosition = r.getPosition();
    Vector rayDirection = r.getDirection();
    Vector r0_pc = rayPosition-_position;
    float f = pow(rayDirection*r0_pc,2)+pow(_radius, 2)-pow(r0_pc.magnitude(), 2);
    float intersectionDistance =-1;
    if(f==0.0){
        // do we get exact 0.0 on computer's double point calculation?
        intersectionDistance = rayDirection*r0_pc;
    }else if(f>0){
        float t_minus = -rayDirection*r0_pc - std::sqrt(f);
        if(t_minus>0){
            intersectionDistance = t_minus;
        }else{
            intersectionDistance = -rayDirection*r0_pc + std::sqrt(f);
        }
    }
    return intersectionDistance;

}

const Color Sphere::getColor(const Vector& intersectionPoint, const vector<PointLight*> pointLights)
{
    Color c_sum({0, 0, 0}) ;
    for(unsigned int i=0; i<pointLights.size(); ++i)
    {
        PointLight* pointLight = pointLights[i];
        Vector L = intersectionPoint-pointLight->getPosition();
        L.normalize();

        // surface normal
        Vector surfaceNormal = intersectionPoint-_position;
        // confusion: normal direction (ns ?)
        float ri = std::max((-surfaceNormal.normal()*L)/M_PI, 0.0);
        Color tempColor = pointLight->getColor()*ri;
        c_sum = c_sum+tempColor;
    }
    return _color*c_sum;
}
#endif // ___SPHERE_H____
