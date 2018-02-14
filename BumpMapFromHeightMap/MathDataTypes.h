#ifndef _DATA_TYPES_H_
#define _DATA_TYPES_H_

struct Vector2D
{
	float x, y;
};

struct Vector3D
{
	float x, y, z;
};

struct Quaternion
{
	// figure out components, rotations only
	float theta,x, y, z;
	// other way of writing it down, x, y, z, w
	
	// x, y, z are imaginary, theta is real


	// w = a, x = ib, y = jc, z = kd
	// a + ib + jc + kd


	// look at Maths for 3D Game Programming and Computer Graphics, 2rd edit

	// at: http://www.cprogramming.com/tutorial/3d/quaternions.html

	// other example http://www.euclideanspace.com/maths/algebra/realNormedAlgebra/quaternions/code/sfrotation_cpp.htm
	
	// also described as vector with an angle
};

struct PolarCoordinate // store angle as degrees, convert to rad when needed
{
	float angle;
	float radius;
};

// 4x4 matrix max, (num rows)x(num columns)

// 2x1
struct Matrix2x1
{
	float r1c1;
	float r2c1;
	// x, y
};

// 2x2 (might be needed)
struct Matrix2x2
{
	float r1c1, r1c2;
	float r2c1, r2c2;
}; 

// 3x1
struct Matrix3x1
{
	float r1c1, r2c1, r3c1;
	// x, y, z
};

// 3x3
struct Matrix3x3
{
	float r1c1, r2c1, r3c1;
	float r1c2, r2c2, r3c2;
	float r1c3, r2c3, r3c3;
};

// 4x1 is a colum vector
struct Matrix4x1
{
	float r1c1, r2c1, r3c1, r4c1;
	//	x, y, z, w?
};

// 4x3
struct Matrix4x3
{
	float r1c1, r2c1, r3c1, r4c1;
	float r1c2, r2c2, r3c2, r4c2;
	float r1c3, r2c3, r3c3, r4c3;
};

// 4x4
struct Matrix4x4
{
	float r1c1, r2c1, r3c1, r4c1;
	float r1c2, r2c2, r3c2, r4c2;
	float r1c3, r2c3, r3c3, r4c3;
	float r1c4, r2c4, r3c4, r4c4;
};

#endif