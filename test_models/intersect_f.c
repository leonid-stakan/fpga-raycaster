#include <stdio.h>
#include <string.h>
#include "commons.h"

/* Global variables */
int image[IMAGE_WIDTH * IMAGE_HEIGHT]; 
tCamera camera;
tSphere my_sphere;


int 
TriangleIntersect(tRay r, tTriangle tri, tPoint *p)
{
	float d, t;

	/*  auxiliary vectors */
	tPoint v1, v2, v3, n; 

	tPoint ray = {
		(r.d.x - r.o.x),
		(r.d.y - r.o.y),
		(r.d.z - r.o.z)
	};
	tPoint ray_prev = ray;

	/* computing of normal to triangle plane: n = {A,B,C} */
	VECT_SUB(v1, tri.b, tri.a);
	VECT_SUB(v2, tri.c, tri.a);
	VECT_CROSSP(n, v1, v2);

	/* Computing of number d,that number from plane equal Ax+By+Cz=d */
	d = VECT_DOTP(n, tri.a);

 	/* ray doesn't intersect plane, hence ray is parallel to plane */
	if (VECT_DOTP(n, ray) == 0.0)
		return -1;
 
	/* computing number t, it's from line 	
	 * equal R(t)= P0 + t*d, where P0 - origin point,
	 * and in this case d is vector of ray direction
	 */
	t = (d - VECT_DOTP(n, camera.position)) / VECT_DOTP(n, ray);

	/* cause we're not considering intercect at apposite direction */
	VECT_TIMES_CONST(ray, t);
	if( VECT_DOTP(ray, ray_prev) < 0.0)
		return NO_INTRSCT;

	/* It's intersect point with plane */
	VECT_ADD((*p), camera.position, ray); 
	
	/* inside-outside testing */
	VECT_SUB(v2, (*p), tri.a);
	VECT_CROSSP(v3, v1, v2);
	if (VECT_DOTP(v3, n) >= 0.0) {
		
		VECT_SUB(v1, tri.c, tri.b);
		VECT_SUB(v2, (*p), tri.b);
		VECT_CROSSP(v3, v1, v2);
		if (VECT_DOTP(v3, n) >= 0.0) {
			
			VECT_SUB(v1, tri.a, tri.c);
			VECT_SUB(v2, (*p), tri.c);
			VECT_CROSSP(v3, v1, v2);
			if (VECT_DOTP(v3, n) >= 0.0) {
			/* point is inside triangle */
				return INTRSCT;
			}
		}
	}
	/* point is outside triangle */
	return NO_INTRSCT;
}


int
SimpleSphereIntersect( tRay *ray, tSphere *sphere)
{
	tPoint vect, norm_ray;
	float distance, proection;

	VECT_SUB(vect, sphere->centr, ray->o);
	VECT_SUB(norm_ray, ray->d, ray->o);

	DEBUG("SphereInersect: input_ray(x,y,z) = %f\t%f\t%f\n", \
		   norm_ray.x, norm_ray.y, norm_ray.z);

	VECT_NORMALIZE(norm_ray);

	DEBUG("SphereInersect: norm_input_ray(x,y,z) = %f\t%f\t%f\n", \
		   norm_ray.x, norm_ray.y, norm_ray.z);

	/* proection of sphere centre on normalize fector */
	proection = VECT_DOTP(norm_ray, vect);

	VECT_TIMES_CONST(norm_ray, proection);

	DEBUG("SphereInersect: proejection(x,y,z) = %f\t%f\t%f\n", \
		   norm_ray.x, norm_ray.y, norm_ray.z);

	VECT_SUB(vect, norm_ray, vect);
	distance = VECT_LEN(vect);

	return (distance < sphere->rad) ? INTRSCT : NO_INTRSCT;
}

