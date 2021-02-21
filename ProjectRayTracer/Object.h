#ifndef ___OBJECT_H____
#define ___OBJECT_H____

#include "Vector.h"
#include "Ray.h"

// rename it SceneObject with abstract intersect class; lecture-7
class Object{
    private:
        Color _color;
    public:
        virtual float intersection(const Ray& r) const=0;
        virtual const Color& getColor() const;
};


const Color& Object::getColor() const{
    return _color;
}
#endif
