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

	VECT_SUB(vect, sphere->centr, ray->o);
	VECT_SUB(norm_ray, ray->d, ray->o );

	#ifdef DEBUG_INF
		printf("\nSphereInersect: in_ray.x = %f\n", norm_ray.x);
		printf("SphereInersect: in_ray.y = %f\n", norm_ray.y);
		printf("SphereInersect: in_ray.z = %f\n\n", norm_ray.z);
	#endif

	VECT_NORMALIZE( norm_ray );

	#ifdef DEBUG_INF
		printf("SphereInersect: norm_in_ray.x = %f\n", norm_ray.x);
		printf("SphereInersect: norm_in_ray.y = %f\n", norm_ray.y);
		printf("SphereInersect: norm_in_ray.z = %f\n", norm_ray.z);
	#endif

	proection = VECT_DOTP( norm_ray, vect ); // proection of sphere center on normalize fector

	VECT_TIMES_CONST(norm_ray, proection);

	#ifdef DEBUG_INF
		printf("SphereInersect: proection.x = %f\n", norm_ray.x);
		printf("SphereInersect: proection.y = %f\n", norm_ray.y);
		printf("SphereInersect: proection.z = %f\n", norm_ray.z);
	#endif

	VECT_SUB(vect, norm_ray, vect );
	distance = VECT_LEN(vect);
	if(distance < sphere->rad)
		return 1;
	return 0;
}

