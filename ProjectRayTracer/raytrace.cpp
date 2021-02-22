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

bool DEBUG = true;

void savePpm(ImagePlane& imagePlane)
{
    FILE *fp;
    fp = fopen("output/raytrace.ppm","w");
    fprintf(fp,"P3\n%d %d\n%d\n", imagePlane.getNx(), imagePlane.getNy(), 255);

    for (int j = 0; j < imagePlane.getNy(); ++j)
        for (int i = 0; i < imagePlane.getNx(); ++i)
        {
            Color c = imagePlane.get(i, j);
            fprintf(fp, "%d %d %d\n", int(min(double(1), c.r)*255), int(min(double(1), c.g)*255), int(min(double(1), c.b)*255));       // red, green, blue
        }


     fclose(fp);
}

Color trace( const Ray& r, const vector<SceneObject*> sceneObjects, const vector<PointLight*> pointLights){

    // check for the intersection. if found any then return the color of nearest object

    float nearestIntersectionDistance = 1000000.0;
    // initialize with black color
    Color intersectionColor = Color({0, 0, 0});
    for(unsigned int i=0; i<sceneObjects.size(); ++i){
        // cout<<"DEBUG::Trace:"<<i+2<<", ["<<scene_objects.size()<<"]"<<endl;
        SceneObject* obj = sceneObjects[i];
        float intersectionDistance = obj->intersection(r);
        //cout<<"i: "<<i<<" , Scene obje size: "<<scene_objects.size()<<" |intersectionDistance: " <<intersectionDistance<< " |nearestIntersectionDistance: "<<nearestIntersectionDistance<<endl;
        if(intersectionDistance>0  && intersectionDistance<nearestIntersectionDistance){
            intersectionColor = obj->getColor(r.getIntersectionPoint(intersectionDistance), pointLights);
            nearestIntersectionDistance = intersectionDistance;
            //if(true)cout<<"DEBUG::Intersection:"<<i<<" Distance: "<<nearestIntersectionDistance<<endl;
        }
    };
    //cout<<"DEBUG :: TRACE: RETURN ";intersectionColor.printColor();
    return intersectionColor;
};

void raytrace(Camera& camera, ImagePlane& imagePlane, const vector<SceneObject*> sceneObjects, const vector<PointLight*> pointLights){
    if (DEBUG)cout<<"DEBUG::RayTrace:1"<<endl;
    for(int j=0; j<imagePlane.getNy(); j++){
        for (int i=0; i<imagePlane.getNx(); i++){
            // 1. call cameras view(x,y) method for a givem pixel. returning a pixel direction vector
            Vector pixelDirection = camera.view(float(i)/imagePlane.getNx(), float(j)/imagePlane.getNy());
            // 2. initialize a ray with a camera position and pixel direction
            Ray ray = Ray(camera.getPosition(), pixelDirection);
            // 3. call the Trace function which return color of the intersection
            Color color = trace(ray, sceneObjects, pointLights);
            // why is same value returning by the object?
            //cout<<"DEBUG :: RAYTRACE :: TRACE";color.printColor();
            imagePlane.set(i, j, color);
            if(false){
                cout<<"DEBUG::RayTrace: (i, j) = ("<<i<<", "<<j<<") => Color:"<<endl;
                color.printColor();
            }
        }
    }
    if (DEBUG)cout<<"DEBUG::RayTrace:10"<<endl;
    // 4. set the color of the pixel
}


int main()
{

    // do ray tracing and save image
    if(DEBUG)
        cout << "Ray Tracing..." << endl;

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
