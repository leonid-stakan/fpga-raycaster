#ifndef _COMMONS_H_
#define _COMMONS_H_

#include "types_3d.h"

#ifndef MPI
#define M_PI 3.14159265358979323846
#endif

enum{
	NO_INTRSCT,	/*0*/
	INTRSCT		/*1*/
};
/*To output debug info define this macros */
//#define DEBUG_INF
#ifdef DEBUG_INF
	#define DEBUG(M,...) printf(M"\n", ##__VA_ARGS__)
#else
	#define DEBUG(M,...)
#endif

/* Framebuffer */
#define IMAGE_WIDTH		120
#define IMAGE_HEIGHT	60

#define PIXEL(x,y) (x + IMAGE_WIDTH * y)
extern int image[];

/* Camera */
typedef struct {
	tPoint position;
	tPoint target;
	tPoint up; // top of image plane
	float fov;
} tCamera;
extern tCamera camera;
extern tSphere my_sphere;
extern tTriangle triangle;

/* Scene data */
extern tPoint *vertices;
extern unsigned short *indices;
extern unsigned short nobjects;
extern unsigned short nindices;

/* Availible functions*/
void ray_generator(void);
int SimpleSphereIntersect(tRay *, tSphere *);
int TriangleIntersect(tRay r, tTriangle tri, tPoint *p);


#endif // _COMMONS_H_
