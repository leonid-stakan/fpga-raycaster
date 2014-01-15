#include "commons.h"
#include "stdio.h"


int main(int argc, char *argv[])
{

	/* Initianal camera parametrs */	
	camera.position.x = 0.0f;
	camera.position.y = 0.0f;
	camera.position.z = -100.0f;
	
	camera.target.x = 0.0f;
	camera.target.y = 0.0f;
	camera.target.z = 0.0f;

	camera.fov = 45.0f;

	camera.up.x = 0.0f;
	camera.up.y = 1.0f;
	camera.up.z = 0.0f;

	/*Defining of sphere for example*/
	my_sphere.centr.x = 15.0f;
	my_sphere.centr.y = 15.0f;
	my_sphere.centr.z = 0.0f;
	my_sphere.rad = 30.0f;
	
/*	tRay my_ray;
	my_ray.o = camera.position;
	my_ray.d = camera.target;
	my_ray.d.x = 7;

	if (SimpleSphereIntersect( &my_ray, &my_sphere))
		printf("Intersect\n");
	else printf("Do not intersect\n");
*/
	/* Rendering scene */
	ray_generator();
	return 0;
}
