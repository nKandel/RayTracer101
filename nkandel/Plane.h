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

#endif
