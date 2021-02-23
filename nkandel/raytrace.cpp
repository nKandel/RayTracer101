#include <iostream>
#include <fstream>
#include <vector>
#include "SceneObject.h"
#include "Vector.h"
#include "ImagePlane.h"
#include "PointLight.h"
#include "Camera.h"
#include "Plane.h"
#include "Sphere.h"
#include "Ray.h"
#include "Trace.h"

using namespace std;
using namespace chromeball;

#if defined __linux__ || defined __APPLE__

#else
// Windows doesn't define these values by default, Linux does
#define M_PI 3.141592653589793
#define INFINITY 1e6
#endif

bool DEBUG = true;

void savePpm(ImagePlane& imagePlane)
{
    FILE *fp;
    fp = fopen("output.ppm","w");
    fprintf(fp,"P3\n%d %d\n%d\n", imagePlane.getNx(), imagePlane.getNy(), 255);

    for (int j = 0; j < imagePlane.getNy(); ++j)
        for (int i = 0; i < imagePlane.getNx(); ++i)
        {
            Color c = imagePlane.get(i, j);
            fprintf(fp, "%d %d %d\n", int(min(double(1), c.r)*255), int(min(double(1), c.g)*255), int(min(double(1), c.b)*255));       // red, green, blue
        }


     fclose(fp);
}

void raytrace(Camera& camera, ImagePlane& imagePlane, const vector<SceneObject*> sceneObjects, const vector<PointLight*> pointLights){
    if (DEBUG)cout<<"DEBUG::RayTrace:1"<<endl;
    for(int j=0; j<imagePlane.getNy(); j++)
    {
        for (int i=0; i<imagePlane.getNx(); i++)
        {
            // 1. call cameras view(x,y) method for a givem pixel. returning a pixel direction vector
            Vector pixelDirection = camera.view(float(i)/imagePlane.getNx(), float(j)/imagePlane.getNy());
            // 2. initialize a ray with a camera position and pixel direction
            Ray ray = Ray(camera.getPosition(), pixelDirection);
            // 3. call the Trace function which return color of the intersection
            Color color = Trace(ray, sceneObjects, pointLights);
            //cout<<"DEBUG :: RAYTRACE :: TRACE";color.printColor();
            // 4. set the color of the pixel
            imagePlane.set(i, j, color);
            if(false)
            {
                cout<<"DEBUG::RayTrace: (i, j) = ("<<i<<", "<<j<<") => Color:"<<endl;
                color.printColor();
            }
        }
    }
    if (DEBUG)cout<<"DEBUG::RayTrace:10"<<endl;

}


int main()
{

    // do ray tracing and save image
    PointLight pointLight1 = PointLight(Vector(-1, -1, 7), Color({2, 2, 2}));
    vector<PointLight*> pointLights;
    pointLights.push_back(&pointLight1);

    Plane plane0 = Plane(Vector(0.0, 2.0, 0.0), Vector(0, -1, 0), Color({1.0, 1.0, 1.0}));
    Plane plane1 = Plane(Vector(0, -2, 0), Vector(0, 1, 0), Color({1.0, 1.0, 1.0}));
    Plane plane2 = Plane(Vector(-2, 0, 0), Vector(1, 0, 0), Color({1.0, 0.0, 0.0}));
    Plane plane3 = Plane(Vector(2, 0, 0), Vector(-1, 0, 0), Color({0.0, 1.0, 0}));
    Plane plane4 = Plane(Vector(0, 0, 10), Vector(0, 0, -1), Color({1.0, 1.0, 1.0}));

    Sphere sphere1 = Sphere(Vector(1.1, 1.25, 7), 1.0, Color({0.5, 0.5, 1}));

    vector<SceneObject*> sceneObjects;

    sceneObjects.push_back(dynamic_cast<SceneObject*>(&plane0));
    sceneObjects.push_back(dynamic_cast<SceneObject*>(&plane1));
    sceneObjects.push_back(dynamic_cast<SceneObject*>(&plane2));
    sceneObjects.push_back(dynamic_cast<SceneObject*>(&plane3));
    sceneObjects.push_back(dynamic_cast<SceneObject*>(&plane4));
    sceneObjects.push_back(dynamic_cast<SceneObject*>(&sphere1));

    ImagePlane imagePlane = ImagePlane(1024, 768);

    Camera camera = Camera(Vector(0,0,0), Vector(0,0,1), Vector(0,1,0), 90, 1.3333);

    // fire ray from camera to the image plane. for each pixel on the imageplane find the nearest interaction
    if(DEBUG)
        cout<<"DEBUG::MAIN:1"<<endl;
    raytrace(camera, imagePlane, sceneObjects, pointLights);

    // save image
    savePpm(imagePlane);
    return 0;
}
