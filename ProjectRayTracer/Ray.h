#ifndef ___RAY_H____
#define ___RAY_H____

#include "Vector.h"

using namespace chromeball;

class Ray{
    private:
        Vector _position, _direction;
    public:
    	Ray ();
        Ray (Vector, Vector);
        ~Ray(){};
        const Vector& get_position() const;
        const Vector get_direction() const;
};
#endif // ___RAY_H____
