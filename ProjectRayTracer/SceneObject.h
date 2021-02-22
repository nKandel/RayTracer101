#ifndef ___SCENE_OBJECT_H____
#define ___SCENE_OBJECT_H____
#include <vector>
#include "Vector.h"
#include "PointLight.h"
#include "Ray.h"

// rename it SceneObject with abstract intersect class; lecture-7
class SceneObject{
    private:
        Color _color;
    public:
        virtual float intersection(const Ray& r) const=0;
        virtual const Color getColor(const Vector& intersectionPoint, const vector<PointLight*> pointLights)=0;
};

#endif
