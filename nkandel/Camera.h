#ifndef ___CAMERA_H____
#define ___CAMERA_H____
#include "Vector.h"
using namespace chromeball;

#if defined __linux__ || defined __APPLE__

#else
// Windows doesn't define these values by default, Linux does
#define M_PI 3.141592653589793
#define INFINITY 1e6
#endif

class Camera{
    private:
        Vector _position, _viewDirection, _upDirection;
        float _aspectRatio, _hFov;

    public:
        Camera();

        Camera(Vector position, Vector viewDirection, Vector upDirection, float hfov, float aspectRatio);

        Vector view(float x, float y) const;

        Vector getPosition();

        Vector getUpDirection();

        ~Camera(){}

};

#endif
