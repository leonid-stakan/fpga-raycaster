#include <stdio.h>
#include <string.h>
#include "commons.h"

/* Global RAM variables */
int image[IMAGE_WIDTH * IMAGE_HEIGHT]; // Framebuffer
tCamera camera;
tPoint *vertices; // vertices array
unsigned short *indices; // indices array
unsigned short nobjects;
unsigned short nindices;
tSphere my_sphere;

#if 0
int 
intersect(tRay r, tTriangle tri, tPoint *p)
{
	float d, t;
	tPoint v1, v2, v3, n; // auxiliary vectors

	tPoint ray = {
		{r.d.x - r.o.x},
		{r.d.y - r.o.y},
		{r.d.z - r.o.z}
	};
	tPoint ray_prev = ray;
/***computing of normal to triangle plane: n = {A,B,C}***/
	VECT_SUB(v1, tri.b, tri.a);
	VECT_SUB(v2, tri.c, tri.a);
	VECT_CROSSP(n, v1, v2);

/***Computing of number d,that number from plane equal Ax+By+Cz=d ***/
	d = VECT_DOTP(n, tri.a);

/***compute t,it's from line equal R(t)= P0 + t*d ***/
	if (VECT_DOTP(n, ray) == 0)
		return -1; // ray doesn't intersect plane, hence ray is parallel to plane

	t = (d - VECT_DOTP(n, camera.position)) / VECT_DOTP(n, ray);
	VECT_TIMES_CONST(ray, t);
	if( VECT_DOTP(ray, ray_prev) < 0) // cause we're not considering intercect at apposite direction  
		return 0;
	VECT_ADD((*p), camera.position, ray); //It's intersect point with plane
	
/***inside-outside testing***/
//	VECT_SUB(v1, tri.b, tri.a);
	VECT_SUB(v2, (*p), tri.a);
	VECT_CROSSP(v3, v1, v2);
	if (VECT_DOTP(v3, n) >= 0) {
		
		VECT_SUB(v1, tri.c, tri.b);
		VECT_SUB(v2, (*p), tri.b);
		VECT_CROSSP(v3, v1, v2);
		if (VECT_DOTP(v3, n) >= 0) {
			
			VECT_SUB(v1, tri.a, tri.c);
			VECT_SUB(v2, (*p), tri.c);
			VECT_CROSSP(v3, v1, v2);
			if (VECT_DOTP(v3, n) >= 0) {
				
				return 1;	// point is inside triangle
			}
			else return 0;	// point is outside triangle
		}
		else	return 0;	// point is outside triangle
	}
	else 
		return 0;	// point is outside triangle
}
#endif

int
SimpleSphereIntersect( tRay *ray, tSphere *sphere)
{
	tPoint vect, norm_ray;
	float distance, proection;

	VECT_SUB(vect, sphere->centr, ray->o); //
	VECT_SUB(norm_ray, ray->d, ray->o );

//	printf("norm_ray.x = %f\n", norm_ray.x);
//	printf("norm_ray.y = %f\n", norm_ray.y);
//	printf("norm_ray.z = %f\n\n", norm_ray.z);
	VECT_NORMALIZE( norm_ray );
//	printf("norm_ray.x = %f\n", norm_ray.x);
//	printf("norm_ray.y = %f\n", norm_ray.y);
//	printf("norm_ray.z = %f\n", norm_ray.z);
	proection = VECT_DOTP( norm_ray, vect ); // proection of sphere center on normalize fector
	VECT_TIMES_CONST(norm_ray, proection);
//	printf("proection.x = %f\n", norm_ray.x);
//	printf("proection.y = %f\n", norm_ray.y);
//	printf("proection.z = %f\n", norm_ray.z);
	VECT_SUB(vect, norm_ray, vect );
	distance = VECT_LEN(vect);
	if(distance < sphere->rad)
		return 1;
	return 0;
}

void 
do_render(void)
{	

	float image_dist = VECT_LEN2(camera.position, camera.target); // the distance between camera and screen
	printf("image_dist: %lf\n", image_dist);

	float delta = 2 * (tan((float)GRAD_TO_RAD(camera.fov / 2)) * image_dist) / IMAGE_WIDTH; // the step 
	printf("delta: %lf\n", delta);

	tPoint left;
	tPoint eye; // templorary vector to create left
	VECT_SUB(eye, camera.target, camera.position);
	VECT_CROSSP(left, camera.up, eye);
	VECT_NORMALIZE(left);
	printf("left.x = %f\n",left.x);
	printf("left.y = %f\n",left.y);
	printf("left.z = %f\n",left.z);

			
	tPoint a = left, b = camera.up;

	VECT_TIMES_CONST(a, delta * IMAGE_WIDTH / 2);
	VECT_TIMES_CONST(b, delta * IMAGE_HEIGHT / 2);
	VECT_ADD(a, a, b);

	tPoint screen_begin;	// It's one of upper corners of screen
	VECT_ADD(screen_begin, camera.target, a);

	printf("screen_begin.x = %f\n",screen_begin.x);
	printf("screen_begin.y = %f\n",screen_begin.y);
	printf("screen_begin.z = %f\n",screen_begin.z);


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
			if(SimpleSphereIntersect( &ray, &my_sphere))
				printf("%lf\t%lf\t%lf\n",ray.d.x, ray.d.y, ray.d.z);
		}
	}

}

