#ifndef _TYPES_3D_H_
#define _TYPES_3D_H_

#include <math.h>

/* Point type */
typedef struct {
	float x;
	float y;
	float z;
} tPoint;

/* Ray type */
typedef struct {
	tPoint o; // origin
	tPoint d; // direction
} tRay;

typedef struct {
	tPoint a;
	tPoint b;
	tPoint c;
} tTriangle;

typedef struct {
	tPoint centr;
	float rad;
} tSphere;

#define GRAD_TO_RAD(x) (2 * x * M_PI / 360.0f)
#define VECT_ADD(N,A,B)	N.x = (float)(A.x + B.x); \
						N.y = (float)(A.y + B.y); \
						N.z = (float)(A.z + B.z);
#define VECT_SUB(N,A,B)	N.x = (float)(A.x - B.x); \
						N.y = (float)(A.y - B.y); \
						N.z = (float)(A.z - B.z);
#define VECT_CROSSP(N,A,B)	N.x = A.y*B.z - B.y*A.z; \
							N.y = A.z*B.x - B.z*A.x; \
							N.z = A.x*B.y - B.x*A.y;

#define VECT_DOTP(A,B)		(A.x*B.x + A.y*B.y + A.z*B.z)

#define VECT_TIMES_CONST(A,CONST)	A.x = (float)(CONST*A.x); \
									A.y = (float)(CONST*A.y); \
									A.z = (float)(CONST*A.z);


#define VECT_LEN2(A,B) (sqrt( pow( (B.x - A.x), 2) + pow( (B.y - A.y), 2) + pow( (B.z - A.z), 2))) 
#define VECT_LEN(v)  (sqrt( pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2)))
#define VECT_NORMALIZE(v) { float len = VECT_LEN(v); v.x /= len; v.y /= len; v.z /= len; }

#endif // _TYPES_3D_H_
