#include <iostream>
#include <fstream>
#include <vector>
#include "Object.h"
#include "Vector.h"
#include "ImagePlane.h"
#include "PointLight.h"
#include "Camera.h"
#include "Plane.h"
#include "Sphere.h"
#include "Ray.h"
/*
Using the ray tracer described above, the scene you must render consists of
five infinite planes and one sphere as follows:

All of the planes and sphere have Lambertian reflectivity.
*/
// Color Trace( const Ray& r, const Scene& s );


// --------------------------------------------------------------
// PROCESS
// --------------------------------------------------------------
/*
    1. Call the camera’s view(x,y) method with the x,y for the given pixel,
        returning the pixel direction vector.
    2. Initialize a ray with the position of the camera and the pixel direction.
    3. Call the Trace function, which returns a color following the outcome of
        its intersection tests (as described above).
    4. Set the color of the pixel to be the color returned by Trace.
*/


/*
Class: Camera, Ray, Vector, ImagePlane, Geometry, SceneObject, SceneContainer
Method: Trace
Main File: read input parameters, setup render, output image

Output Image in PPM format
*/
using namespace std;
using namespace chromeball;

bool DEBUG = false;

Color& Trace( const Ray& r, const vector<Object*> scene_objects){

    // check for the intersection. if found any then return the color of nearest object

    float nearestIntersectionDistance = 100000000.0;
    // initialize with black color
    Color intersectionColor = Color({0, 0, 0});
    for(int i=0; i<scene_objects.size(); i++){
        // cout<<"DEBUG::Trace:"<<i+2<<", ["<<scene_objects.size()<<"]"<<endl;
        Object* obj = scene_objects[i];
        float intersectionDistance = obj->intersection(r);
        if(intersectionDistance>0  && intersectionDistance<nearestIntersectionDistance){
            intersectionColor = obj->getColor();
            nearestIntersectionDistance = intersectionDistance;
            if(true)cout<<"DEBUG::Intersection:"<<i+1<<" Distance: "<<nearestIntersectionDistance<<endl;
        }
    }

    return intersectionColor;
};

void raytrace(Camera* camera, ImagePlane imagePlane, const vector<Object*> scene_objects){
    if (DEBUG)cout<<"DEBUG::RayTrace:1"<<endl;
    for (int i=0; i<imagePlane.get_Nx(); i++){
        for(int j=0; j<imagePlane.get_Ny(); j++){
            // 1. call cameras view(x,y) method for a givem pixel. returning a pixel direction vector
            Vector pixelDirection = camera->view(i/imagePlane.get_Nx(), j/imagePlane.get_Ny());
            // 2. initialize a ray with a camera position and pixel direction
            Ray ray = Ray(camera->getPosition(), pixelDirection);
            // 3. call the Trace function which return color of the intersection
            Color color = Trace(ray, scene_objects);
            // why is same value returning by the object?
            imagePlane.set(i, j, color);
            if(true){
                cout<<"DEBUG::RayTrace: (i, j) = ("<<i<<", "<<j<<") => Color:"<<endl;
                color.printColor();
                if(j>100) break;
            }
        }
        if(i>10) break;
    }
    if (DEBUG)cout<<"DEBUG::RayTrace:10"<<endl;
    // 4. set the color of the pixel
}

void save_ppm(ImagePlane& imagePlane)
{
    FILE *fp;
    fp = fopen("raytrace.ppm","w");
    fprintf(fp,"P3\n%d %d\n%d\n", imagePlane.get_Nx(), imagePlane.get_Ny(), 255);

    for (int j = 0; j < imagePlane.get_Ny(); ++j)
        for (int i = 0; i < imagePlane.get_Nx(); ++i)
        {
            Color c = imagePlane.get(i, j);
            fprintf(fp, "%d %d %d\n", int(min(double(1), c.r)*256), int(min(double(1), c.g)*256), int(min(double(1), c.b)*256));       // red, green, blue
        }


     fclose(fp);
}

int main()
{

    // do ray tracing and save image
    if(DEBUG)
        cout << "Ray Tracing..." << endl;

    PointLight pointLight = PointLight(Vector(-1, -1, 7), Color({2, 2, 2}));

    Plane plane0 = Plane(Vector(0.0, 2.0, 0.0), Vector(0, -1, 0), Color({1.0, 1.0, 1.0}));
    Plane plane1 = Plane(Vector(0, -2, 0), Vector(0, 1, 0), Color({1.0, 1.0, 1.0}));
    Plane plane2 = Plane(Vector(-2, 0, 0), Vector(1, 0, 0), Color({1.0, 0.0, 0.0}));
    Plane plane3 = Plane(Vector(2, 0, 0), Vector(-1, 0, 0), Color({0.0, 1.0, 0}));
    Plane plane4 = Plane(Vector(0, 0, 10), Vector(0, 0, -1), Color({1.0, 1.0, 1.0}));

    Sphere sphere1 = Sphere(Vector(1.1, 1.25, 7), 1.0, Color({0.5, 0.5, 1}));

    vector<Object*> scene_objects;

    scene_objects.push_back(dynamic_cast<Object*>(&plane0));
    scene_objects.push_back(dynamic_cast<Object*>(&plane1));
    scene_objects.push_back(dynamic_cast<Object*>(&plane2));
    scene_objects.push_back(dynamic_cast<Object*>(&plane3));
    scene_objects.push_back(dynamic_cast<Object*>(&plane4));
    scene_objects.push_back(dynamic_cast<Object*>(&sphere1));

    ImagePlane imagePlane = ImagePlane(1024, 768);

    Camera camera = Camera(Vector(0,0,0), Vector(0,0,1), Vector(0,1,0), 90, 1.3333);

    // fire ray from camera to the image plane. for each pixel on the imageplane find the nearest interaction
    if(DEBUG)
        cout<<"DEBUG::MAIN:1"<<endl;
    raytrace(&camera, imagePlane, scene_objects);

    // save image
    save_ppm(imagePlane);
    return 0;
}
