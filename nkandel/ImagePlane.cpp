#include "ImagePlane.h"

ImagePlane::ImagePlane(): _Nx(0), _Ny(0)
{
    _data.resize(_Nx*_Ny);
}

ImagePlane::ImagePlane(int Nx, int Ny): _Nx(Nx), _Ny(Ny)
{
    _data.resize(_Nx*_Ny);
}

int ImagePlane::getRowValue(int i, int j) const
{
    //std::cout<<"DEBUG:: i,j : "<<i<<", "<<j<<" single dim: "<<i+j*_Nx<<std::endl;
    return i+j*_Nx;
}

void ImagePlane::set(int i, int j, const Color& c)
{
    int val = getRowValue(i, j);
    //std::cout<<"Debug :: ImagePlane:set 1"<<std::endl;
    _data[val] = c;
    //std::cout<<"Debug :: ImagePlane:set 2"<<std::endl;
}

Color ImagePlane::get(int i, int j) const
{
    return _data[getRowValue(i, j)];
}

int ImagePlane::getNx() const
{
    return _Nx;
}

int ImagePlane::getNy() const
{
    return _Ny;
}
