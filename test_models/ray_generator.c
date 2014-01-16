#include <stdio.h>
#include <string.h>
#include "commons.h"

/* Global variables */
int image[IMAGE_WIDTH * IMAGE_HEIGHT]; // Framebuffer
tCamera camera;
tTriangle triangle = {
    3,0,0,
    0,3,0,
    -3,0,0
};

tPoint test_point;

void 
ray_generator(void)
{	
	tPoint screen_begin;
	/*vector to simplify computing*/
	tPoint left;
	/* templorary vectors*/
	tPoint a,b;
	/* the distance between camera and screen */
	float image_dist = VECT_LEN2(camera.position, camera.target);
	/* step of ray movement on the screen*/
	float delta = 2 * (tan((float)GRAD_TO_RAD(camera.fov / 2)) \
					* image_dist) / IMAGE_WIDTH;

	DEBUG("Ray_generator: image_dist = %lf\n", image_dist);
	DEBUG("Ray_generator: delta = %lf\n", delta);

	VECT_SUB(a, camera.target, camera.position);
	VECT_CROSSP(left, camera.up, a);
	VECT_NORMALIZE(left);

	DEBUG("Ray_generator: left(x,y,z) = %f\t%f\t%f\n", \
           left.x, left.y, left.z);

	a = left;
	b = camera.up;
	VECT_TIMES_CONST(a, delta * IMAGE_WIDTH / 2);
	VECT_TIMES_CONST(b, delta * IMAGE_HEIGHT / 2);
	VECT_ADD(a, a, b);
	VECT_ADD(screen_begin, camera.target, a);

	DEBUG("Ray_generator: screen_begin(x,y,z) = %f\t%f\t%f\n", \
           screen_begin.x, screen_begin.y, screen_begin.z);

	int iy,ix;
	for (iy = 0; iy < IMAGE_HEIGHT; iy++) {
		for (ix = 0; ix < IMAGE_WIDTH; ix++)
		{

			tRay ray = {
				camera.position,
				{
					screen_begin.x - (camera.up.x * iy + left.x * ix) * delta,
					screen_begin.y - (camera.up.y * iy + left.y * ix) * delta,
					screen_begin.z - (camera.up.z * iy + left.z * ix) * delta,
				}
			};
			/*We should make decesion how we are going to use data !!!*/
			if(SimpleSphereIntersect( &ray, &my_sphere))
				printf("%lf\t%lf\t%lf\n",ray.d.x, ray.d.y, ray.d.z);
// 			if(TriangleIntersect(ray, triangle, &test_point))
//				printf("%lf\t%lf\t%lf\n",ray.d.x, ray.d.y, ray.d.z);

		}
	}

}
