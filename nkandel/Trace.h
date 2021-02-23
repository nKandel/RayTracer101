#ifndef ___TRACE_H____
#define ___TRACE_H____
#include<vector>
#include "Vector.h"
#include "Ray.h"
#include "SceneObject.h"
#include "PointLight.h"


Color Trace(const Ray& r, const std::vector<SceneObject*> sceneObjects, const std::vector<PointLight*> pointLights)
{

    // check for the intersection. if found any then return the color of nearest object

    float nearestIntersectionDistance = 1000000.0;
    // initialize with black color
    Color intersectionColor = Color({0, 0, 0});
    for(unsigned int i=0; i<sceneObjects.size(); ++i)
    {
        // cout<<"DEBUG::Trace:"<<i+2<<", ["<<scene_objects.size()<<"]"<<endl;
        SceneObject* obj = sceneObjects[i];
        float intersectionDistance = obj->intersection(r);
        //cout<<"i: "<<i<<" , Scene obje size: "<<scene_objects.size()<<" |intersectionDistance: " <<intersectionDistance<< " |nearestIntersectionDistance: "<<nearestIntersectionDistance<<endl;
        if(intersectionDistance>0  && intersectionDistance<nearestIntersectionDistance)
        {
            intersectionColor = obj->getColor(r.getIntersectionPoint(intersectionDistance), pointLights);
            nearestIntersectionDistance = intersectionDistance;
            //if(true)cout<<"DEBUG::Intersection:"<<i<<" Distance: "<<nearestIntersectionDistance<<endl;
        }
    };
    //cout<<"DEBUG :: TRACE: RETURN ";intersectionColor.printColor();
    return intersectionColor;
};

#endif // ___TRACE_H____
