
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

#endif // ___SPHERE_H____
