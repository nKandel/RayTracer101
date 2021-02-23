raytrace: raytrace.o ray.o camera.o imageplane.o plane.o sphere.o pointlight.o
	g++ raytrace.o ray.o camera.o imageplane.o plane.o sphere.o pointlight.o -o raytrace

raytrace.o: raytrace.cpp
	g++ -Wall -O2 -c raytrace.cpp -o raytrace.o -std=c++11

ray.o: Ray.cpp
	g++ -Wall -O2 -c Ray.cpp -o ray.o -std=c++11

camera.o: Camera.cpp
	g++ -Wall -O2 -c Camera.cpp -o camera.o -std=c++11

imageplane.o: ImagePlane.cpp
	g++ -Wall -O2 -c ImagePlane.cpp -o imageplane.o -std=c++11

plane.o: Plane.cpp
	g++ -Wall -O2 -c Plane.cpp -o plane.o -std=c++11

sphere.o: Sphere.cpp
	g++ -Wall -O2 -c Sphere.cpp -o sphere.o -std=c++11

pointlight.o: PointLight.cpp
	g++ -Wall -O2 -c PointLight.cpp -o pointlight.o -std=c++11


clean:
	rm *.o raytrace

run:
	./raytrace
