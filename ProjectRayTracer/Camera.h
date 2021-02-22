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
        Camera():

        _position(Vector(0,0,0)), _viewDirection(Vector (0,0,0)), _upDirection(Vector (0,0,0)), _aspectRatio(1.0), _hFov(0.0)
        {}

        Camera(Vector position, Vector viewDirection, Vector upDirection, float hfov, float aspectRatio):
            _position(position),
            _viewDirection(viewDirection.normal()), // nc
            _upDirection(upDirection.normal()),  // direction in the 3D world that is up in the image plane
            _aspectRatio(aspectRatio),
            _hFov(hfov*M_PI/180.0)
        {}

        Vector view(float x, float y) const
        {
            Vector right = _upDirection^_viewDirection;
            // portrait or landscape
            float u = (2.0*x - 1)*std::tan(_hFov/2);
            float v = (2.0*y - 1)*std::tan(_hFov/2)/_aspectRatio;

            Vector X = right.normal()*u + _upDirection*v;
            Vector n = X + _viewDirection;
            n.normalize();
            return n;
        }

        Vector getPosition(){
            return _position;
        }

        Vector getUpDirection(){
            return _upDirection;
        }

        string str(){
            return "Camera Class";
        }

        ~Camera(){}

};

#endif
