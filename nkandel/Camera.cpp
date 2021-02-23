#include "Camera.h"
Camera::Camera():
    _position(Vector(0,0,0)),
    _viewDirection(Vector (0,0,0)),
    _upDirection(Vector (0,0,0)),
    _aspectRatio(1.0),
    _hFov(0.0)
{}

Camera::Camera(Vector position, Vector viewDirection, Vector upDirection, float hfov, float aspectRatio):
    _position(position),
    _viewDirection(viewDirection.normal()), // nc
    _upDirection(upDirection.normal()),  // direction in the 3D world that is up in the image plane
    _aspectRatio(aspectRatio),
    _hFov(hfov*M_PI/180.0)
{}

Vector Camera::view(float x, float y) const
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

Vector Camera::getPosition()
{
    return _position;
}

Vector Camera::getUpDirection()
{
    return _upDirection;
}
