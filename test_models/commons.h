#ifndef _COMMONS_H_
#define _COMMONS_H_

#include "types_3d.h"

#ifndef MPI
#define M_PI 3.14159265358979323846
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

/* Scene data */
extern tPoint *vertices;
extern unsigned short *indices;
extern unsigned short nobjects;
extern unsigned short nindices;

/* Availible functions*/
void do_render(void);
int SimpleSphereIntersect(tRay *, tSphere *);

#endif // _COMMONS_H_
