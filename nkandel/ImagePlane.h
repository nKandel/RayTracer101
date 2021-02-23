#ifndef ___IMAGEPLANE_H____
#define ___IMAGEPLANE_H____
#include <vector>
#include "Vector.h"

using namespace chromeball;

class ImagePlane
{
    private:
        int _Nx, _Ny;
        // single array color data i+nx*j
        std::vector<Color> _data;
    public:
        ImagePlane();
        ImagePlane(int Nx, int Ny);
        ~ImagePlane(){};
        Color get(int, int) const;
        void set(int i, int j, const Color& c);
        int getNx() const;
        int getNy() const;
        int getRowValue(int i, int j) const;

};
#endif // ___IMAGEPLANE_H____
