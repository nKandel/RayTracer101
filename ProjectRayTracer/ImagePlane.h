#ifndef ___IMAGEPLANE_H____
#define ___IMAGEPLANE_H____
#include "Vector.h"
using namespace chromeball;

class ImagePlane
{
    private:
        int _Nx, _Ny;
        // single array color data i+nx*j
        std::vector <Color> _data;
    public:
        ImagePlane();
        ImagePlane(int Nx, int Ny);
        ~ImagePlane(){};
        Color get(int, int) const;
        void set(int i, int j, const Color& c);
        int get_Nx() const;
        int get_Ny() const;
        int getRowValue(int i, int j) const;

};

ImagePlane::ImagePlane(): _Nx(0), _Ny(0)
{
    _data.resize(_Nx*_Ny);
}

ImagePlane::ImagePlane(int Nx, int Ny): _Nx(Nx), _Ny(Ny)
{
    _data.resize(_Nx*_Ny);
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

int ImagePlane::getRowValue(int i, int j) const
{
    return i+j*_Nx;
}

int ImagePlane::get_Nx() const
{
    return _Nx;
}

int ImagePlane::get_Ny() const
{
    return _Ny;
}
#endif // ___IMAGEPLANE_H____
