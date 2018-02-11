#ifndef _DATA_TYPES_H_
#define _DATA_TYPES_H_

/*
Copyright (c) 2015 Joshua Gibson

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

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
	float w, x, y, z;
};

struct PolarCoordinate
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

// 2x2
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

// 4x1
struct Matrix4x1
{
	float r1c1, r2c1, r3c1, r4c1;
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