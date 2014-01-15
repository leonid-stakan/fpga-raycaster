#include <stdio.h>
#include <string.h>
#include "commons.h"

/* Global variables */
int image[IMAGE_WIDTH * IMAGE_HEIGHT]; // Framebuffer
tCamera camera;


void 
ray_generator(void)
{	

	float image_dist = VECT_LEN2(camera.position, camera.target); // the distance between camera and screen
	float delta = 2 * (tan((float)GRAD_TO_RAD(camera.fov / 2)) * image_dist) / IMAGE_WIDTH; // the step 
	
	#ifdef DEBUG_INF
		printf("Ray_generator: image_dist= %lf\n", image_dist);
		printf("Ray_generator: delta= %lf\n", delta);
	#endif

	tPoint left;
	tPoint eye; // templorary vector to create left
	VECT_SUB(eye, camera.target, camera.position);
	VECT_CROSSP(left, camera.up, eye);
	VECT_NORMALIZE(left);

	#ifdef DEBUG_INF
		printf("Ray_generator: left.x = %f\n",left.x);
		printf("Ray_generator: left.y = %f\n",left.y);
		printf("Ray_generator: left.z = %f\n",left.z);
	#endif
			
	tPoint a = left, b = camera.up;

	VECT_TIMES_CONST(a, delta * IMAGE_WIDTH / 2);
	VECT_TIMES_CONST(b, delta * IMAGE_HEIGHT / 2);
	VECT_ADD(a, a, b);

	tPoint screen_begin;	// It's one of upper corners of screen
	VECT_ADD(screen_begin, camera.target, a);

	#ifdef DEBUG_INF
		printf("Ray_generator: screen_begin.x = %f\n",screen_begin.x);
		printf("Ray_generator: screen_begin.y = %f\n",screen_begin.y);
		printf("Ray_generator: screen_begin.z = %f\n",screen_begin.z);
	#endif

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
		}
	}

}

