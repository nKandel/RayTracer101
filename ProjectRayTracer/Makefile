raytracer: raytrace.o ray.o
	g++ raytrace.o ray.o -o raytracer

raytrace.o: raytrace.cpp
	g++ -Wall -O2 -c raytrace.cpp -o raytrace.o -std=c++11

ray.o: Ray.cpp
	g++ -Wall -O2 -c Ray.cpp -o ray.o -std=c++11

clean:
	rm *.o raytracer
