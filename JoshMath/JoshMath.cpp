#include "JoshMath.h"
#include <cmath>

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

float Math::VectorMath::dotProduct(const Vector2D & vecA, const Vector2D & vecB)
{
	return (vecA.x * vecB.x) + (vecA.y * vecB.y);
}

float Math::VectorMath::dotProduct(const Vector3D & vecA, const Vector3D & vecB)
{
	return (vecA.x * vecB.x) + (vecA.y * vecB.y) + (vecA.z * vecB.z);
}

Vector2D Math::VectorMath::crossProduct(const Vector2D & vecA, const Vector2D & vecB)
{
	Vector2D rv;
	rv.x = (vecA.y * 0.0f) - (0.0f * vecB.y);
	rv.y = (0.0f * vecB.x) - (vecA.x * 0.0f);
	return rv;
}

Vector3D Math::VectorMath::crossProduct(const Vector3D & vecA, const Vector3D & vecB)
{
	Vector3D rv;
	rv.x = (vecA.y * vecB.z) - (vecA.z * vecB.y);
	rv.y = (vecA.z * vecB.x) - (vecA.x * vecB.z);
	rv.z = (vecA.x * vecB.y) - (vecA.y * vecB.x);
	return rv;
}

Vector2D Math::VectorMath::add (const Vector2D & a, const Vector2D & b)
{
	Vector2D returnVal;
	returnVal.x = a.x + b.x;
	returnVal.y = a.y + b.y;
	return returnVal;
}

Vector2D Math::VectorMath::subtract (const Vector2D & a, const Vector2D & b)
{
	Vector2D rv;
	rv.x = a.x - b.x;
	rv.y = a.y - b.y;
	return rv;
}

Vector3D Math::VectorMath::add (const Vector3D & a, const Vector3D & b)
{
	Vector3D rv;
	rv.x = a.x + b.x;
	rv.y = a.y + b.y;
	rv.z = a.z + b.z;
	return rv;
}

Vector3D Math::VectorMath::subtract (const Vector3D & a, const Vector3D & b)
{
	Vector3D rv;
	rv.x = a.x - b.x;
	rv.y = a.y - b.y;
	rv.z = a.z - b.z;
	return rv;
}

Vector2D Math::VectorMath::wayToVector(const Vector2D & pointA, const Vector2D & pointB)
{
	return subtract(pointB, pointA);
}

Vector3D Math::VectorMath::wayToVector(const Vector3D & pointA, const Vector3D & pointB)
{
	return subtract(pointB, pointA);
}

float Math::VectorMath::magnitude (const Vector2D & a)
{
	float rv = (a.x * a.x) + (a.y * a.y);
	rv = sqrtf(rv);
	return rv;
}

float Math::VectorMath::magnitude (const Vector3D & a)
{
	float rv = (a.x * a.x) + (a.y * a.y) + (a.z * a.z);
	rv = sqrtf(rv);
	return rv;
}

float Math::VectorMath::magnitudeSquared(const Vector2D & a)
{
	return (a.x * a.x) + (a.y * a.y);
}

float Math::VectorMath::magnitudeSquared(const Vector3D & a)
{
	return (a.x * a.x) + (a.y * a.y) + (a.z * a.z);
}

Vector2D Math::VectorMath::scaled(float scale, const Vector2D & toScale)
{
	Vector2D rv;
	rv.x = toScale.x * scale;
	rv.y = toScale.y * scale;
	return rv;
}

Vector3D Math::VectorMath::scaled(float scale, const Vector3D & toScale)
{
	Vector3D rv; // rv = Return Value
	rv.x = toScale.x * scale;
	rv.y = toScale.y * scale;
	rv.z = toScale.z * scale;
	return rv;
}

Vector2D Math::VectorMath::unitVector(const Vector2D & a)
{
	float mag = magnitude(a);
	float unitScale = 1.0f / mag;
	return scaled(unitScale, a);
}

Vector3D Math::VectorMath::unitVector(const Vector3D & a)
{
	float mag = magnitude(a);
	float unitScale = 1.0f / mag;
	return scaled(unitScale, a);
}

float Math::VectorMath::lookAt2D(const Vector2D & currentlyLookingAtPos, const Vector2D & toLookAtPos, const Vector2D & currentPos)// note the parameters passed should be points to look at
{
	// need unit vectors from eye position to currently facing position & eye position to position want to look at
	Vector2D eye2OldAt = wayToVector(currentPos, currentlyLookingAtPos);
	Vector2D eye2NewAt = wayToVector(currentPos, toLookAtPos);
	eye2OldAt = unitVector(eye2OldAt);
	eye2NewAt = unitVector(eye2NewAt);

	float dp = dotProduct(eye2OldAt, eye2NewAt);

	return acosf(dp);
}

Matrix4x4 Math::VectorMath::lookAt3D(Vector3D & position, Vector3D & targetPosition, Vector3D & upVec)
{
	Vector3D zAxis = subtract(position, targetPosition);
	zAxis = unitVector(zAxis);

	Vector3D xAxis = crossProduct(upVec, zAxis);
	Vector3D yAxis = crossProduct(zAxis, xAxis);

	Matrix4x4 rv;

	rv.r1c1 = xAxis.x;
	rv.r2c1 = xAxis.y;
	rv.r3c1 = xAxis.z;
	rv.r4c1 = 0.0f;

	rv.r1c2 = yAxis.x;
	rv.r2c2 = yAxis.y;
	rv.r3c2 = yAxis.z;
	rv.r4c2 = 0.0f;

	rv.r1c3 = zAxis.x;
	rv.r2c3 = zAxis.y;
	rv.r3c3 = xAxis.z;
	rv.r4c3 = 0.0f;

	rv.r1c4 = position.x;
	rv.r2c4 = position.y;
	rv.r3c4 = position.z;
	rv.r4c4 = 1.0f;

	return rv;
}

float Math::degreesToRadians(float valueInDegrees)
{
	return valueInDegrees * (3.14159265359 / 180);
}

float Math::radiansToDegrees(float valueInRadians)
{
	return valueInRadians * (180 / 3.14159265359);
}

PolarCoordinate Math::PolarCoordinateMath::CartesianToPolar(Vector2D & cartVal)
{
	PolarCoordinate rv;
	rv.radius = VectorMath::magnitude(cartVal);
	rv.angle = atanf(cartVal.x / cartVal.y);
	rv.angle = radiansToDegrees(rv.angle);
	return rv;
}

Vector2D Math::PolarCoordinateMath::PolarToCartesian(PolarCoordinate & PolarVal)
{
	Vector2D rv;
	float angleAsRads = degreesToRadians(PolarVal.angle);
	rv.x = PolarVal.radius * cosf(angleAsRads);
	rv.y = PolarVal.radius * sinf(angleAsRads);
	return rv;
}


Matrix2x1 Math::MatrixMath::add(const Matrix2x1 & a, const Matrix2x1 & b)
{
	Matrix2x1 rv;
	rv.r1c1 = a.r1c1 + b.r1c1;
	rv.r2c1 = a.r2c1 + b.r2c1;
	return rv;
}

Matrix2x2 Math::MatrixMath::add(const Matrix2x2 & a, const Matrix2x2 & b)
{
	Matrix2x2 rv;
	rv.r1c1 = a.r1c1 + b.r1c1;
	rv.r1c2 = a.r1c2 + b.r1c2;
	rv.r2c1 = a.r2c1 + b.r2c1;
	rv.r2c2 = a.r2c2 + b.r2c2;
	return rv;
}

Matrix3x1 Math::MatrixMath::add(const Matrix3x1 & a, const Matrix3x1 & b)
{
	Matrix3x1 rv;
	rv.r1c1 = a.r1c1 + b.r1c1;
	rv.r2c1 = a.r2c1 + b.r2c1;
	rv.r3c1 = a.r3c1 + b.r3c1;
	return rv;
}

Matrix3x3 Math::MatrixMath::add(const Matrix3x3 & a, const Matrix3x3 & b)
{
	Matrix3x3 rv;
	rv.r1c1 = a.r1c1 + b.r1c1;
	rv.r1c2 = a.r1c2 + b.r1c2;
	rv.r1c3 = a.r1c3 + b.r1c3;

	rv.r2c1 = a.r2c1 + b.r2c1;
	rv.r2c2 = a.r2c2 + b.r2c2;
	rv.r2c3 = a.r2c3 + b.r2c3;

	rv.r3c1 = a.r3c1 + b.r3c1;
	rv.r3c2 = a.r3c2 + b.r3c2;
	rv.r3c3 = a.r3c3 + b.r3c3;
	return rv;
}

Matrix4x1 Math::MatrixMath::add(const Matrix4x1 & a, const Matrix4x1 & b)
{
	Matrix4x1 rv;
	rv.r1c1 = a.r1c1 + b.r1c1;
	rv.r2c1 = a.r2c1 + b.r2c1;
	rv.r3c1 = a.r3c1 + b.r3c1;
	rv.r4c1 = a.r4c1 + b.r4c1;
	return rv;
}

Matrix4x3 Math::MatrixMath::add(const Matrix4x3 & a, const Matrix4x3 & b)
{
	Matrix4x3 rv;

	rv.r1c1 = a.r1c1 + b.r1c1;
	rv.r1c2 = a.r1c2 + b.r1c2;
	rv.r1c3 = a.r1c3 + b.r1c3;

	rv.r2c1 = a.r2c1 + b.r2c1;
	rv.r2c2 = a.r2c2 + b.r2c2;
	rv.r2c3 = a.r2c3 + b.r2c3;

	rv.r3c1 = a.r3c1 + b.r3c1;
	rv.r3c2 = a.r3c2 + b.r3c2;
	rv.r3c3 = a.r3c3 + b.r3c3;

	rv.r4c1 = a.r4c1 + b.r4c1;
	rv.r4c2 = a.r4c2 + b.r4c2;
	rv.r4c3 = a.r4c3 + b.r4c3;

	return rv;
}

Matrix4x4 Math::MatrixMath::add(const Matrix4x4 & a, const Matrix4x4 & b)
{
	Matrix4x4 rv;

	rv.r1c1 = a.r1c1 + b.r1c1;
	rv.r1c2 = a.r1c2 + b.r1c2;
	rv.r1c3 = a.r1c3 + b.r1c3;
	rv.r1c4 = a.r1c4 + b.r1c4;

	rv.r2c1 = a.r2c1 + b.r2c1;
	rv.r2c2 = a.r2c2 + b.r2c2;
	rv.r2c3 = a.r2c3 + b.r2c3;
	rv.r2c4 = a.r2c4 + b.r2c4;

	rv.r3c1 = a.r3c1 + b.r3c1;
	rv.r3c2 = a.r3c2 + b.r3c2;
	rv.r3c3 = a.r3c3 + b.r3c3;
	rv.r3c4 = a.r3c4 + b.r3c4;

	rv.r4c1 = a.r4c1 + b.r4c1;
	rv.r4c2 = a.r4c2 + b.r4c2;
	rv.r4c3 = a.r4c3 + b.r4c3;
	rv.r4c4 = a.r4c4 + b.r4c4;

	return rv;
}


Matrix2x1 Math::MatrixMath::subtract(const Matrix2x1 & a, const Matrix2x1 & b)
{
	Matrix2x1 rv;
	rv.r1c1 = a.r1c1 - b.r1c1;
	rv.r2c1 = a.r2c1 - b.r2c1;
	return rv;
}

Matrix2x2 Math::MatrixMath::subtract(const Matrix2x2 & a, const Matrix2x2 & b)
{
	Matrix2x2 rv;
	rv.r1c1 = a.r1c1 - b.r1c1;
	rv.r1c2 = a.r1c2 - b.r1c2;
	rv.r2c1 = a.r2c1 - b.r2c1;
	rv.r2c2 = a.r2c2 - b.r2c2;
	return rv;
}

Matrix3x1 Math::MatrixMath::subtract(const Matrix3x1 & a, const Matrix3x1 & b)
{
	Matrix3x1 rv;
	rv.r1c1 = a.r1c1 - b.r1c1;
	rv.r2c1 = a.r2c1 - b.r2c1;
	rv.r3c1 = a.r3c1 - b.r3c1;
	return rv;
}

Matrix3x3 Math::MatrixMath::subtract(const Matrix3x3 & a, const Matrix3x3 & b)
{
	Matrix3x3 rv;
	rv.r1c1 = a.r1c1 - b.r1c1;
	rv.r1c2 = a.r1c2 - b.r1c2;
	rv.r1c3 = a.r1c3 - b.r1c3;

	rv.r2c1 = a.r2c1 - b.r2c1;
	rv.r2c2 = a.r2c2 - b.r2c2;
	rv.r2c3 = a.r2c3 - b.r2c3;

	rv.r3c1 = a.r3c1 - b.r3c1;
	rv.r3c2 = a.r3c2 - b.r3c2;
	rv.r3c3 = a.r3c3 - b.r3c3;

	return rv;
}

Matrix4x1 Math::MatrixMath::subtract(const Matrix4x1 & a, const Matrix4x1 & b)
{
	Matrix4x1 rv;
	rv.r1c1 = a.r1c1 - b.r1c1;
	rv.r2c1 = a.r2c1 - b.r2c1;
	rv.r3c1 = a.r3c1 - b.r3c1;
	rv.r4c1 = a.r4c1 - b.r4c1;

	return rv;
}

Matrix4x3 Math::MatrixMath::subtract(const Matrix4x3 & a, const Matrix4x3 & b)
{
	Matrix4x3 rv;

	rv.r1c1 = a.r1c1 - b.r1c1;
	rv.r1c2 = a.r1c2 - b.r1c2;
	rv.r1c3 = a.r1c3 - b.r1c3;

	rv.r2c1 = a.r2c1 - b.r2c1;
	rv.r2c2 = a.r2c2 - b.r2c2;
	rv.r2c3 = a.r2c3 - b.r2c3;

	rv.r3c1 = a.r3c1 - b.r3c1;
	rv.r3c2 = a.r3c2 - b.r3c2;
	rv.r3c3 = a.r3c3 - b.r3c3;

	rv.r4c1 = a.r4c1 - b.r4c1;
	rv.r4c2 = a.r4c2 - b.r4c2;
	rv.r4c3 = a.r4c3 - b.r4c3;

	return rv;
}

Matrix4x4 Math::MatrixMath::subtract(const Matrix4x4 & a, const Matrix4x4 & b)
{
	Matrix4x4 rv;

	rv.r1c1 = a.r1c1 - b.r1c1;
	rv.r1c2 = a.r1c2 - b.r1c2;
	rv.r1c3 = a.r1c3 - b.r1c3;
	rv.r1c4 = a.r1c4 - b.r1c4;

	rv.r2c1 = a.r2c1 - b.r2c1;
	rv.r2c2 = a.r2c2 - b.r2c2;
	rv.r2c3 = a.r2c3 - b.r2c3;
	rv.r2c4 = a.r2c4 - b.r2c4;

	rv.r3c1 = a.r3c1 - b.r3c1;
	rv.r3c2 = a.r3c2 - b.r3c2;
	rv.r3c3 = a.r3c3 - b.r3c3;
	rv.r3c4 = a.r3c4 - b.r3c4;

	rv.r4c1 = a.r4c1 - b.r4c1;
	rv.r4c2 = a.r4c2 - b.r4c2;
	rv.r4c3 = a.r4c3 - b.r4c3;
	rv.r4c4 = a.r4c4 - b.r4c4;

	return rv;
}


Matrix2x1 Math::MatrixMath::multiply(float scale, const Matrix2x1 & a)
{
	Matrix2x1 rv;
	rv.r1c1 = a.r1c1 * scale;
	rv.r2c1 = a.r2c1 * scale;
	return rv;
}

Matrix2x2 Math::MatrixMath::multiply(float scale, const Matrix2x2 & a)
{
	Matrix2x2 rv;
	rv.r1c1 = a.r1c1 * scale;
	rv.r1c2 = a.r1c2 * scale;
	rv.r2c1 = a.r2c1 * scale;
	rv.r2c2 = a.r2c2 * scale;
	return rv;
}

Matrix3x1 Math::MatrixMath::multiply(float scale, const Matrix3x1 & a)
{
	Matrix3x1 rv;
	rv.r1c1 = a.r1c1 * scale;
	rv.r2c1 = a.r2c1 * scale;
	rv.r3c1 = a.r3c1 * scale;
	return rv;
}

Matrix3x3 Math::MatrixMath::multiply(float scale, const Matrix3x3 & a)
{
	Matrix3x3 rv;

	rv.r1c1 = a.r1c1 * scale;
	rv.r1c2 = a.r1c2 * scale;
	rv.r1c3 = a.r1c3 * scale;

	rv.r2c1 = a.r2c1 * scale;
	rv.r2c2 = a.r2c2 * scale;
	rv.r2c3 = a.r2c3 * scale;

	rv.r3c1 = a.r3c1 * scale;
	rv.r3c2 = a.r3c2 * scale;
	rv.r3c3 = a.r3c3 * scale;

	return rv;
}

Matrix4x1 Math::MatrixMath::multiply(float scale, const Matrix4x1 & a)
{
	Matrix4x1 rv;
	rv.r1c1 = a.r1c1 * scale;
	rv.r2c1 = a.r2c1 * scale;
	rv.r3c1 = a.r3c1 * scale;
	rv.r4c1 = a.r4c1 * scale;
	return rv;
}

Matrix4x3 Math::MatrixMath::multiply(float scale, const Matrix4x3 & a)
{
	Matrix4x3 rv;

	rv.r1c1 = a.r1c1 * scale;
	rv.r1c2 = a.r1c2 * scale;
	rv.r1c3 = a.r1c3 * scale;

	rv.r2c1 = a.r2c1 * scale;
	rv.r2c2 = a.r2c2 * scale;
	rv.r2c3 = a.r2c3 * scale;

	rv.r3c1 = a.r3c1 * scale;
	rv.r3c2 = a.r3c2 * scale;
	rv.r3c3 = a.r3c3 * scale;

	rv.r4c1 = a.r4c1 * scale;
	rv.r4c2 = a.r4c2 * scale;
	rv.r4c3 = a.r4c3 * scale;

	return rv;
}

Matrix4x4 Math::MatrixMath::multiply(float scale, const Matrix4x4 & a)
{
	Matrix4x4 rv;

	rv.r1c1 = a.r1c1 * scale;
	rv.r1c2 = a.r1c2 * scale;
	rv.r1c3 = a.r1c3 * scale;
	rv.r1c4 = a.r1c4 * scale;

	rv.r2c1 = a.r2c1 * scale;
	rv.r2c2 = a.r2c2 * scale;
	rv.r2c3 = a.r2c3 * scale;
	rv.r2c4 = a.r2c4 * scale;

	rv.r3c1 = a.r3c1 * scale;
	rv.r3c2 = a.r3c2 * scale;
	rv.r3c3 = a.r3c3 * scale;
	rv.r3c4 = a.r3c4 * scale;

	rv.r4c1 = a.r4c1 * scale;
	rv.r4c2 = a.r4c2 * scale;
	rv.r4c3 = a.r4c3 * scale;
	rv.r4c4 = a.r4c4 * scale;

	return rv;
}


Matrix2x1 Math::MatrixMath::multiply(const Matrix2x2 & a, const Matrix2x1 & b)
{
	Matrix2x1 rv;
	rv.r1c1 = (a.r1c1 * b.r1c1) + (a.r1c2 * b.r2c1);
	rv.r2c1 = (a.r2c1 * b.r1c1) + (a.r2c2 * b.r2c1);
	return rv;
}

Matrix2x2 Math::MatrixMath::multiply(const Matrix2x2 & a, const Matrix2x2 & b)
{
	Matrix2x2 rv;

	rv.r1c1 = (a.r1c1 * b.r1c1) + (a.r1c2 * b.r2c1);
	rv.r1c2 = (a.r1c1 * b.r1c2) + (a.r1c2 * b.r2c2);

	rv.r2c1 = (a.r2c1 * b.r1c1) + (a.r2c2 * b.r2c1);
	rv.r2c2 = (a.r2c1 * b.r1c2) + (a.r2c2 * b.r2c2);

	return rv;
}


Matrix3x1 Math::MatrixMath::multiply(const Matrix3x3 & a, const Matrix3x1 & b)
{
	Matrix3x1 rv;
	rv.r1c1 = (a.r1c1 * b.r1c1) + (a.r1c2 * b.r2c1) + (a.r1c3 * b.r3c1);
	rv.r2c1 = (a.r2c1 * b.r1c1) + (a.r2c2 * b.r2c1) + (a.r2c3 * b.r3c1);
	rv.r3c1 = (a.r3c1 * b.r1c1) + (a.r3c2 * b.r2c1) + (a.r3c3 * b.r3c1);
	return rv;
}

Matrix3x3 Math::MatrixMath::multiply(const Matrix3x3 & a, const Matrix3x3 & b)
{
	Matrix3x3 rv;

	rv.r1c1 = (a.r1c1 * b.r1c1) + (a.r1c2 * b.r2c1) + (a.r1c3 * b.r3c1);
	rv.r1c2 = (a.r1c1 * b.r1c2) + (a.r1c2 * b.r2c2) + (a.r1c3 * b.r3c2);
	rv.r1c3 = (a.r1c1 * b.r1c3) + (a.r1c2 * b.r2c3) + (a.r1c3 * b.r3c3);

	rv.r2c1 = (a.r2c1 * b.r1c1) + (a.r2c2 * b.r2c1) + (a.r2c3 * b.r3c1);
	rv.r2c2 = (a.r2c1 * b.r1c2) + (a.r2c2 * b.r2c2) + (a.r2c3 * b.r3c2);
	rv.r2c3 = (a.r2c1 * b.r1c3) + (a.r2c2 * b.r2c3) + (a.r2c3 * b.r3c3);

	rv.r3c1 = (a.r3c1 * b.r1c1) + (a.r3c2 * b.r2c1) + (a.r3c3 * b.r3c1);
	rv.r3c2 = (a.r3c1 * b.r1c2) + (a.r3c2 * b.r2c2) + (a.r3c3 * b.r3c2);
	rv.r3c3 = (a.r3c1 * b.r1c3) + (a.r3c2 * b.r2c3) + (a.r3c3 * b.r3c3);

	return rv;
}


Matrix4x1 Math::MatrixMath::multiply(const Matrix4x4 & a, const Matrix4x1 & b)
{
	Matrix4x1 rv;
	rv.r1c1 = (a.r1c1 * b.r1c1) + (a.r1c2 * b.r2c1) + (a.r1c3 * b.r3c1) + (a.r1c4 * b.r4c1);
	rv.r2c1 = (a.r2c1 * b.r1c1) + (a.r2c2 * b.r2c1) + (a.r2c3 * b.r3c1) + (a.r2c4 * b.r4c1);
	rv.r3c1 = (a.r3c1 * b.r1c1) + (a.r3c2 * b.r2c1) + (a.r3c3 * b.r3c1) + (a.r3c4 * b.r4c1);
	rv.r4c1 = (a.r4c1 * b.r1c1) + (a.r4c2 * b.r2c1) + (a.r4c3 * b.r3c1) + (a.r4c4 * b.r4c1);

	return rv;
}

Matrix4x3 Math::MatrixMath::multiply(const Matrix4x4 & a, const Matrix4x3 & b)
{
	Matrix4x3 rv;
	rv.r1c1 = (a.r1c1 * b.r1c1) + (a.r1c2 * b.r2c1) + (a.r1c3 * b.r3c1) + (a.r1c4 * b.r4c1);
	rv.r1c2 = (a.r1c1 * b.r1c2) + (a.r1c2 * b.r2c2) + (a.r1c3 * b.r3c2) + (a.r1c4 * b.r4c2);
	rv.r1c3 = (a.r1c1 * b.r1c3) + (a.r1c2 * b.r2c3) + (a.r1c3 * b.r3c3) + (a.r1c4 * b.r4c3);

	rv.r2c1 = (a.r2c1 * b.r1c1) + (a.r2c2 * b.r2c1) + (a.r2c3 * b.r3c1) + (a.r2c4 * b.r4c1);
	rv.r2c2 = (a.r2c1 * b.r1c2) + (a.r2c2 * b.r2c2) + (a.r2c3 * b.r3c2) + (a.r2c4 * b.r4c2);
	rv.r2c3 = (a.r2c1 * b.r1c3) + (a.r2c2 * b.r2c3) + (a.r2c3 * b.r3c3) + (a.r2c4 * b.r4c3);

	rv.r3c1 = (a.r3c1 * b.r1c1) + (a.r3c2 * b.r2c1) + (a.r3c3 * b.r3c1) + (a.r3c4 * b.r4c1);
	rv.r3c2 = (a.r3c1 * b.r1c2) + (a.r3c2 * b.r2c2) + (a.r3c3 * b.r3c2) + (a.r3c4 * b.r4c2);
	rv.r3c3 = (a.r3c1 * b.r1c3) + (a.r3c2 * b.r2c3) + (a.r3c3 * b.r3c3) + (a.r3c4 * b.r4c3);

	rv.r4c1 = (a.r4c1 * b.r1c1) + (a.r4c2 * b.r2c1) + (a.r4c3 * b.r3c1) + (a.r4c4 * b.r4c1);
	rv.r4c2 = (a.r4c1 * b.r1c2) + (a.r4c2 * b.r2c2) + (a.r4c3 * b.r3c2) + (a.r4c4 * b.r4c2);
	rv.r4c3 = (a.r4c1 * b.r1c3) + (a.r4c2 * b.r2c3) + (a.r4c3 * b.r3c3) + (a.r4c4 * b.r4c3);

	return rv;
}

Matrix4x4 Math::MatrixMath::multiply(const Matrix4x4 & a, const Matrix4x4 & b)
{
	Matrix4x4 rv;

	rv.r1c1 = (a.r1c1 * b.r1c1) + (a.r1c2 * b.r2c1) + (a.r1c3 * b.r3c1) + (a.r1c4 * b.r4c1);
	rv.r1c2 = (a.r1c1 * b.r1c2) + (a.r1c2 * b.r2c2) + (a.r1c3 * b.r3c2) + (a.r1c4 * b.r4c2);
	rv.r1c3 = (a.r1c1 * b.r1c3) + (a.r1c2 * b.r2c3) + (a.r1c3 * b.r3c3) + (a.r1c4 * b.r4c3);
	rv.r1c4 = (a.r1c1 * b.r1c4) + (a.r1c2 * b.r2c4) + (a.r1c3 * b.r3c4) + (a.r1c4 * b.r4c4);

	rv.r2c1 = (a.r2c1 * b.r1c1) + (a.r2c2 * b.r2c1) + (a.r2c3 * b.r3c1) + (a.r2c4 * b.r4c1);
	rv.r2c2 = (a.r2c1 * b.r1c2) + (a.r2c2 * b.r2c2) + (a.r2c3 * b.r3c2) + (a.r2c4 * b.r4c2);
	rv.r2c3 = (a.r2c1 * b.r1c3) + (a.r2c2 * b.r2c3) + (a.r2c3 * b.r3c3) + (a.r2c4 * b.r4c3);
	rv.r2c4 = (a.r2c1 * b.r1c4) + (a.r2c2 * b.r2c4) + (a.r2c3 * b.r3c4) + (a.r2c4 * b.r4c4);

	rv.r3c1 = (a.r3c1 * b.r1c1) + (a.r3c2 * b.r2c1) + (a.r3c3 * b.r3c1) + (a.r3c4 * b.r4c1);
	rv.r3c2 = (a.r3c1 * b.r1c2) + (a.r3c2 * b.r2c2) + (a.r3c3 * b.r3c2) + (a.r3c4 * b.r4c2);
	rv.r3c3 = (a.r3c1 * b.r1c3) + (a.r3c2 * b.r2c3) + (a.r3c3 * b.r3c3) + (a.r3c4 * b.r4c3);
	rv.r3c4 = (a.r3c1 * b.r1c4) + (a.r3c2 * b.r2c4) + (a.r3c3 * b.r3c4) + (a.r3c4 * b.r4c4);

	rv.r4c1 = (a.r4c1 * b.r1c1) + (a.r4c2 * b.r2c1) + (a.r4c3 * b.r3c1) + (a.r4c4 * b.r4c1);
	rv.r4c2 = (a.r4c1 * b.r1c2) + (a.r4c2 * b.r2c2) + (a.r4c3 * b.r3c2) + (a.r4c4 * b.r4c2);
	rv.r4c3 = (a.r4c1 * b.r1c3) + (a.r4c2 * b.r2c3) + (a.r4c3 * b.r3c3) + (a.r4c4 * b.r4c3);
	rv.r4c4 = (a.r4c1 * b.r1c4) + (a.r4c2 * b.r2c4) + (a.r4c3 * b.r3c4) + (a.r4c4 * b.r4c4);

	return rv;
}

Matrix4x1 Math::MatrixMath::multiply(const Matrix4x3 & a, const Matrix3x1 & b)
{
	Matrix4x1 rv;
	rv.r1c1 = (a.r1c1 * b.r1c1) + (a.r1c2 * b.r2c1) + (a.r1c3 * b.r3c1);
	rv.r2c1 = (a.r2c1 * b.r1c1) + (a.r2c2 * b.r2c1) + (a.r2c3 * b.r3c1);
	rv.r3c1 = (a.r3c1 * b.r1c1) + (a.r3c2 * b.r2c1) + (a.r3c3 * b.r3c1);
	rv.r4c1 = (a.r4c1 * b.r1c1) + (a.r4c2 * b.r2c1) + (a.r4c3 * b.r3c1);
	return rv;
}

Matrix4x3 Math::MatrixMath::multiply(const Matrix4x3 & a, const Matrix3x3 & b)
{
	Matrix4x3 rv;

	rv.r1c1 = (a.r1c1 * b.r1c1) + (a.r1c2 * b.r2c1) + (a.r1c3 * b.r3c1);
	rv.r1c2 = (a.r1c1 * b.r1c2) + (a.r1c2 * b.r2c2) + (a.r1c3 * b.r3c2);
	rv.r1c3 = (a.r1c1 * b.r1c3) + (a.r1c2 * b.r2c3) + (a.r1c3 * b.r3c3);

	rv.r2c1 = (a.r2c1 * b.r1c1) + (a.r2c2 * b.r2c1) + (a.r2c3 * b.r3c1);
	rv.r2c2 = (a.r2c1 * b.r1c2) + (a.r2c2 * b.r2c2) + (a.r2c3 * b.r3c2);
	rv.r2c3 = (a.r2c1 * b.r1c3) + (a.r2c2 * b.r2c3) + (a.r2c3 * b.r3c3);

	rv.r3c1 = (a.r3c1 * b.r1c1) + (a.r3c2 * b.r2c1) + (a.r3c3 * b.r3c1);
	rv.r3c2 = (a.r3c1 * b.r1c2) + (a.r3c2 * b.r2c2) + (a.r3c3 * b.r3c2);
	rv.r3c3 = (a.r3c1 * b.r1c3) + (a.r3c2 * b.r2c3) + (a.r3c3 * b.r3c3);

	rv.r4c1 = (a.r4c1 * b.r1c1) + (a.r4c2 * b.r2c1) + (a.r4c3 * b.r3c1);
	rv.r4c2 = (a.r4c1 * b.r1c2) + (a.r4c2 * b.r2c2) + (a.r4c3 * b.r3c2);
	rv.r4c3 = (a.r4c1 * b.r1c3) + (a.r4c2 * b.r2c3) + (a.r4c3 * b.r3c3);

	return rv;
}


float Math::MatrixMath::determinant(const Matrix2x2 & a)
{
	return (a.r1c1 * a.r2c2) - (a.r1c2 * a.r2c1);
}

float Math::MatrixMath::determinant(const Matrix3x3 & a)
{
	float aa, ab, ac, ba,bb, bc;

	aa = a.r1c1 * a.r2c2 * a.r3c3;
	ab = a.r1c2 * a.r2c3 * a.r3c1;
	ac = a.r1c3 * a.r2c1 * a.r3c2;

	ba = a.r1c3 * a.r2c2 * a.r3c1;
	bb = a.r1c2 * a.r2c1 * a.r3c3;
	bc = a.r1c1 * a.r2c3 * a.r3c2;

	return (aa + ab + ac) - (ba + bb + bc);
}

float Math::MatrixMath::determinant(const Matrix4x4 & a)
{
	// https://www.khanacademy.org/math/linear-algebra/matrix_Transformations/determinant_depth/v/linear-algebra--simpler-4x4-determinant
	float aa, ab, ac, ad,
		ba, bb, bc, bd;
	aa = a.r1c1 * a.r2c2 * a.r3c3 * a.r4c4;
	ab = a.r1c2 * a.r2c3 * a.r3c4 * a.r4c1;
	ac = a.r1c3 * a.r2c4 * a.r3c1 * a.r4c2;
	ad = a.r1c4 * a.r2c1 * a.r3c2 * a.r4c3;

	ba = a.r1c4 * a.r2c3 * a.r3c2 * a.r4c1;
	bb = a.r1c3 * a.r2c2 * a.r3c1 * a.r4c4;
	bc = a.r1c2 * a.r2c1 * a.r3c4 * a.r4c3;
	bd = a.r1c1 * a.r2c4 * a.r3c3 * a.r4c2;
	return (aa + ab + ac + ad) - (ba + bb + bc + bd);
}


Matrix2x2 Math::MatrixMath::transpose(const Matrix2x2 & a)
{
	Matrix2x2 rv;
	rv.r1c1 = a.r1c1;
	rv.r1c2 = a.r2c1;
	rv.r2c1 = a.r1c2;
	rv.r2c2 = a.r2c2;
	return rv;
}

Matrix3x3 Math::MatrixMath::transpose(const Matrix3x3 & a)
{
	Matrix3x3 rv;
	rv.r1c1 = a.r1c1;
	rv.r1c2 = a.r2c1;
	rv.r1c3 = a.r3c1;

	rv.r2c1 = a.r1c2;
	rv.r2c2 = a.r2c2;
	rv.r2c3 = a.r3c2;

	rv.r3c1 = a.r1c3;
	rv.r3c2 = a.r2c3;
	rv.r3c3 = a.r3c3;

	return rv;
}

Matrix4x4 Math::MatrixMath::transpose(const Matrix4x4 & a)
{
	Matrix4x4 rv;
	rv.r1c1 = a.r1c1;
	rv.r1c2 = a.r2c1;
	rv.r1c3 = a.r3c1;
	rv.r1c4 = a.r4c1;

	rv.r2c1 = a.r1c2;
	rv.r2c2 = a.r2c2;
	rv.r2c3 = a.r3c2;
	rv.r2c4 = a.r4c2;

	rv.r3c1 = a.r1c3;
	rv.r3c2 = a.r2c3;
	rv.r3c3 = a.r3c3;
	rv.r3c4 = a.r4c3;

	rv.r4c1 = a.r1c4;
	rv.r4c2 = a.r2c4;
	rv.r4c3 = a.r3c4;
	rv.r4c4 = a.r4c4;

	return rv;
}


Matrix2x2 Math::MatrixMath::inverse(const Matrix2x2 & a)
{
	Matrix2x2 toMul;
	toMul.r1c1 = a.r2c2;
	toMul.r2c2 = a.r1c1;
	toMul.r1c2 = 0.0f - a.r1c2;
	toMul.r2c1 = 0.0f - a.r2c1;
	float mul = 1.0f / determinant(a);
	return multiply(mul, toMul);
}

Matrix3x3 Math::MatrixMath::inverse(const Matrix3x3 & a)
{
	Matrix3x3 toMul;
	toMul.r1c1 = (a.r2c2 * a.r3c3) - (a.r2c3 * a.r3c2);
	toMul.r1c2 = (a.r1c3 * a.r3c2) - (a.r1c2 * a.r3c3);
	toMul.r3c3 = (a.r1c2 * a.r2c3) - (a.r1c3 * a.r2c2);

	toMul.r2c1 = (a.r2c3 * a.r3c1) - (a.r2c1 * a.r3c3);
	toMul.r2c2 = (a.r1c1 * a.r3c3) - (a.r1c3 * a.r3c1);
	toMul.r2c3 = (a.r1c3 * a.r2c1) - (a.r1c1 * a.r2c3);

	toMul.r3c1 = (a.r2c1 * a.r3c2) - (a.r2c2 * a.r3c1);
	toMul.r3c2 = (a.r1c2 * a.r3c1) - (a.r1c1 * a.r3c2);
	toMul.r3c3 = (a.r1c1 * a.r2c2) - (a.r1c2 * a.r2c1);
	float mul = 1.0f / determinant(a);
	return multiply(mul, toMul);
}

Matrix4x4 Math::MatrixMath::inverse(const Matrix4x4 & a)
{
	float mul = 1.0f / determinant(a);
	Matrix4x4 b;

	b.r1c1 = (a.r2c2 * a.r3c3 * a.r4c4) + (a.r2c3 * a.r3c4 * a.r4c2) + (a.r2c4 * a.r3c2 * a.r4c3)
		- (a.r2c2 * a.r3c4 * a.r4c3) - (a.r2c3 * a.r3c2 * a.r4c4) - (a.r2c4 * a.r3c3 * a.r4c2);
	b.r1c2 = (a.r1c2 * a.r3c4 * a.r4c3) + (a.r1c3 * a.r3c2 * a.r4c4) + (a.r1c4 * a.r3c3 * a.r4c2)
		- (a.r1c2 * a.r3c3 * a.r4c4) - (a.r1c3 * a.r3c4 * a.r4c2) - (a.r1c4 * a.r3c2 * a.r4c3);
	b.r1c3 = (a.r1c2 * a.r2c3 * a.r4c4) + (a.r1c3 * a.r2c4 * a.r4c2) + (a.r1c4 * a.r2c2 * a.r4c3)
		- (a.r1c2 * a.r2c4 * a.r4c3) - (a.r1c3 * a.r2c2 * a.r4c4) - (a.r1c4 * a.r2c3 * a.r4c2);
	b.r1c4 = (a.r1c2 * a.r2c4 * a.r3c3) + (a.r1c3 * a.r2c2 * a.r3c4) + (a.r1c4 * a.r2c3 * a.r3c2)
		- (a.r1c2 * a.r2c3 * a.r3c4) - (a.r1c3 * a.r2c4 * a.r3c2) - (a.r1c4 * a.r2c2 * a.r3c3);

	b.r2c1 = (a.r2c1 * a.r3c4 * a.r4c3) + (a.r2c3 * a.r3c1 * a.r4c4) + (a.r2c4 * a.r3c3 * a.r4c1)
		- (a.r2c1 * a.r3c3 * a.r4c4) - (a.r2c3 * a.r3c4 * a.r4c1) - (a.r2c4 * a.r3c1 * a.r4c3);
	b.r2c2 = (a.r1c1 * a.r3c3 * a.r4c4) + (a.r1c3 * a.r3c4 * a.r4c1) + (a.r1c4 * a.r3c1 * a.r4c3)
		- (a.r1c1 * a.r3c4 * a.r4c3) - (a.r1c3 * a.r3c1 * a.r4c4) - (a.r1c4 * a.r3c3 * a.r4c1);
	b.r2c3 = (a.r1c1 * a.r2c4 * a.r4c3) + (a.r1c3 * a.r2c1 * a.r4c4) + (a.r1c4 * a.r2c3 * a.r4c1)
		- (a.r1c1 * a.r2c3 * a.r4c4) - (a.r1c3 * a.r2c4 * a.r4c1) - (a.r1c4 * a.r2c1 * a.r4c3);
	b.r2c4 = (a.r1c1 * a.r2c3 * a.r3c4) + (a.r1c3 * a.r2c4 * a.r3c1) + (a.r1c4 * a.r2c1 * a.r3c3)
		- (a.r1c1 * a.r2c4 * a.r3c3) - (a.r1c3 * a.r2c1 * a.r3c4) - (a.r1c4 * a.r2c3 * a.r3c1);

	b.r3c1 = (a.r2c1 * a.r3c2 * a.r4c4) + (a.r2c2 * a.r3c4 * a.r4c1) + (a.r2c4 * a.r3c1 * a.r4c2)
		- (a.r2c1 * a.r3c4 * a.r4c2) - (a.r2c2 * a.r3c1 * a.r4c4) - (a.r2c4 * a.r3c2 * a.r4c1);
	b.r3c2 = (a.r1c1 * a.r3c4 * a.r4c2) + (a.r1c2 * a.r3c1 * a.r4c4) + (a.r1c4 * a.r3c2 * a.r4c1)
		- (a.r1c1 * a.r3c2 * a.r4c4) - (a.r1c2 * a.r3c4 * a.r4c1) - (a.r1c4 * a.r3c1 * a.r4c2);
	b.r3c3 = (a.r1c1 * a.r2c2 * a.r4c4) + (a.r1c2 * a.r2c4 * a.r4c1) + (a.r1c4 * a.r2c1 * a.r4c2)
		- (a.r1c1 * a.r2c4 * a.r4c2) - (a.r1c2 * a.r2c1 * a.r4c4) - (a.r1c4 * a.r2c2 * a.r4c1);
	b.r3c4 = (a.r1c1 * a.r2c4 * a.r3c2) + (a.r1c2 * a.r2c1 * a.r3c4) + (a.r1c4 * a.r2c2 * a.r3c1)
		- (a.r1c1 * a.r2c2 * a.r3c4) - (a.r1c2 * a.r2c4 * a.r3c1) - (a.r1c4 * a.r2c1 * a.r3c2);

	b.r4c1 = (a.r2c1 * a.r3c3 * a.r4c2) + (a.r2c2 * a.r3c1 * a.r4c3) + (a.r2c3 * a.r3c2 * a.r4c1)
		- (a.r2c1 * a.r3c2 * a.r4c3) - (a.r2c2 * a.r3c3 * a.r4c1) - (a.r2c3 * a.r3c1 * a.r4c2);
	b.r4c2 = (a.r1c1 * a.r3c2 * a.r4c3) + (a.r1c2 * a.r3c3 * a.r4c1) + (a.r1c3 * a.r3c1 * a.r4c2)
		- (a.r1c1 * a.r3c3 * a.r4c2) - (a.r1c2 * a.r3c1 * a.r4c3) - (a.r1c3 * a.r3c2 * a.r4c1);
	b.r4c3 = (a.r1c1 * a.r2c3 * a.r4c2) + (a.r1c2 * a.r2c1 * a.r4c3) + (a.r1c3 * a.r2c2 * a.r4c1)
		- (a.r1c1 * a.r2c2 * a.r4c3) - (a.r1c2 * a.r2c3 * a.r4c1) - (a.r1c3 * a.r2c1 * a.r4c2);
	b.r4c4 = (a.r1c1 * a.r2c2 * a.r3c3) + (a.r1c2 * a.r2c3 * a.r3c1) + (a.r1c3 * a.r2c1 * a.r3c2)
		- (a.r1c1 * a.r2c3 * a.r3c2) - (a.r1c2 * a.r2c1 * a.r3c3) - (a.r1c3 * a.r2c2 * a.r3c1);

	return multiply(mul, b);
}


void Math::MatrixMath::makeIdentity(Matrix2x2 & a)
{
	a.r1c1 = 1.0f; a.r1c2 = 0.0f;
	a.r2c1 = 0.0f; a.r2c2 = 1.0f;
}

void Math::MatrixMath::makeIdentity(Matrix3x3 & a)
{
	a.r1c1 = 1.0f; a.r1c2 = 0.0f; a.r1c3 = 0.0f;
	a.r2c1 = 0.0f; a.r2c2 = 1.0f; a.r2c3 = 0.0f;
	a.r3c1 = 0.0f; a.r3c2 = 0.0f; a.r3c3 = 1.0f;
}

void Math::MatrixMath::makeIdentity(Matrix4x4 & a)
{
	a.r1c1 = 1.0f; a.r1c2 = 0.0f; a.r1c3 = 0.0f; a.r1c4 = 0.0f;
	a.r2c1 = 0.0f; a.r2c2 = 1.0f; a.r2c3 = 0.0f; a.r2c4 = 0.0f;
	a.r3c1 = 0.0f; a.r3c2 = 0.0f; a.r3c3 = 1.0f; a.r3c4 = 0.0f;
	a.r4c1 = 0.0f; a.r4c2 = 0.0f; a.r4c3 = 0.0f; a.r4c4 = 1.0f;
}


Quaternion Math::QuaternionMath::conjugate(const Quaternion & original)
{
	Quaternion rv;

	rv.w = original.w;
	rv.x = 0.0f - original.x;
	rv.y = 0.0f - original.y;
	rv.z = 0.0f - original.z;

	return rv;
}

Quaternion Math::QuaternionMath::normalise(Quaternion & toNormalise)
{
	Quaternion rv;
	float normVal = norm(toNormalise);
	if (normVal == 0.0f)
	{
		rv.x = 0.0f;
		rv.y = 0.0f;
		rv.z = 0.0f;
		rv.w = 1.0f;
	}
	else
	{
		float scale = 1.0f / normVal;
		rv.x = toNormalise.x * scale;
		rv.y = toNormalise.y * scale;
		rv.z = toNormalise.z * scale;
	}

	// rv.theta = toNormalise.theta * dev;
	return rv;
}

Quaternion Math::QuaternionMath::scale(const Quaternion & toScale, float scale)
{
	Quaternion rv;
	rv.x = toScale.x * scale;
	rv.y = toScale.y * scale;
	rv.z = toScale.z * scale;
	rv.w = toScale.w * scale;
	return rv;
}

Quaternion Math::QuaternionMath::multiply(const Quaternion & a, const Quaternion & b)
{
	Quaternion rv;
	rv.x = a.x * b.w + a.y * b.z - a.z * b.y + a.w * b.x;
	rv.y = -a.x * b.z + a.y * b.w + a.z * b.x + a.w * b.y;
	rv.z = a.x * b.y - a.y * b.x + a.z * b.w + a.w * b.z;
	rv.w = -a.x * b.x - a.y * b.y - a.z * b.z + a.w * b.w;
	return rv;
}

Quaternion Math::QuaternionMath::add(const Quaternion & a, const Quaternion & b)
{
	Quaternion rv;
	rv.w = a.w + b.w;
	rv.x = a.x + b.x;
	rv.y = a.y + b.y;
	rv.z = a.z + b.z;
	return rv;
}

Quaternion Math::QuaternionMath::subtract(const Quaternion & a, const Quaternion & b)
{
	Quaternion rv;
	rv.w = a.w - b.w;
	rv.x = a.x - b.x;
	rv.y = a.y - b.y;
	rv.z = a.z - b.z;
	return rv;
}

void Math::QuaternionMath::identityForMul(Quaternion & a)
{
	a.w = 1.0f;
	a.x = 0.0f;
	a.y = 0.0f;
	a.z = 0.0f;
}

void Math::QuaternionMath::identityForAdd(Quaternion & a)
{
	a.w = 0.0f;
	a.x = 0.0f;
	a.y = 0.0f;
	a.z = 0.0f;
}

float Math::QuaternionMath::norm(Quaternion & a)
{
	return sqrtf(a.x * a.x
		+ a.y * a.y
		+ a.z * a.z
		+ a.w * a.w);
}

Quaternion Math::QuaternionMath::inverse(Quaternion & a)
{
	Quaternion aConj = conjugate(a);
	float n = norm(aConj);
	return scale(aConj, 1.0f / n);
}

Matrix4x4 Math::QuaternionMath::toMatrix4x4(Quaternion & a)
{
	Matrix4x4 rv;
	float tx, ty, tz, xx, yy, yz, xy, xz, zz;
	xx = a.x * a.x;
	xy = a.x * a.y;
	xz = a.x * a.z;
	yy = a.y * a.y;
	zz = a.z * a.z;
	yz = a.y * a.z;
	tx = a.w * a.x;
	ty = a.w * a.y;
	tz = a.w * a.z;

	rv.r1c1 = 1.0f - 2.0f * (yy + zz);
	rv.r2c1 = 2.0f * (xy - tz);
	rv.r3c1 = 2.0f * (xz + ty);
	rv.r4c1 = 0.0f;

	rv.r1c2 = 2.0f * (xy + tz);
	rv.r2c2 = 1.0f - 2.0f * (xx + zz);
	rv.r3c2 = 2.0f * (yz - tx);
	rv.r4c2 = 0.0f;

	rv.r1c3 = 2.0f*(xz - ty);
	rv.r2c3 = 2.0f*(yz + tx);
	rv.r3c3 = 1.0f - 2.0f*(xx + yy);
	rv.r4c3 = 0.0;

	rv.r1c4 = 0.0f;
	rv.r2c4 = 0.0f;
	rv.r3c4 = 0.0f;
	rv.r4c4 = 1.0f;

	return rv;
}

Matrix3x3 Math::QuaternionMath::toMatrix3x3(Quaternion & a)
{
	Matrix3x3 rv;
	rv.r1c1 = 1.0f - (2.0f * (a.y * a.y)) - (2.0f * (a.z * a.z));
	rv.r1c2 = (2.0f * a.x * a.y) - (2.0f * a.w * a.z);
	rv.r1c3 = (2.0f * a.x * a.z) + (2.0f * a.w * a.y);

	rv.r2c1 = (2.0f * a.x * a.y) + (2.0f * a.w * a.z);
	rv.r2c2 = 1.0f - (2.0f * (a.x * a.x)) - (2.0f * (a.z * a.z));
	rv.r2c3 = (2.0f * (a.y * a.z)) - (2.0f * a.w * a.x);

	rv.r3c1 = (2.0f * a.x * a.z) - (2.0f * a.w * a.y);
	rv.r3c2 = (2.0f * a.y * a.z) + (2.0f * a.w * a.x);
	rv.r3c3 = 1.0f - (2.0f * (a.x * a.x)) - (2.0f * (a.y * a.y));

	return rv;
}



void Math::Transform::scale2D(Matrix2x1 & toScale, float xScale, float yScale)
{
	Matrix2x2 mul;
	Math::MatrixMath::makeIdentity(mul);
	mul.r1c1 = xScale;
	mul.r2c2 = yScale;
	toScale = Math::MatrixMath::multiply(mul, toScale);
}

void Math::Transform::scale3D(Matrix3x1 & toScale, float xScale, float yScale, float zScale)
{
	Matrix3x3 mul;
	Math::MatrixMath::makeIdentity(mul);
	mul.r1c1 = xScale;
	mul.r2c2 = yScale;
	mul.r3c3 = zScale;
	toScale = Math::MatrixMath::multiply(mul, toScale);
}

void Math::Transform::scale4D(Matrix4x1 & toScale, float xScale, float yScale, float zScale, float wScale)
{
	Matrix4x4 mul;
	Math::MatrixMath::makeIdentity(mul);
	// W = r4c4
	mul.r1c1 = xScale;
	mul.r2c2 = yScale;
	mul.r3c3 = zScale;
	mul.r4c4 = wScale;
	toScale = Math::MatrixMath::multiply(mul, toScale);
}

void Math::Transform::rotate2DClkWise(Matrix2x1 & toRot, float thetaRads)
{
	float cosTheta = cosf(thetaRads);
	float sinTheta = sinf(thetaRads);
	float negitiveSinTheta = 0.0f - sinTheta;
	Matrix2x2 rot;
	rot.r1c1 = cosTheta;
	rot.r1c2 = sinTheta;
	rot.r2c1 = negitiveSinTheta;
	rot.r2c2 = cosTheta;
	toRot = Math::MatrixMath::multiply(rot, toRot);
}

void Math::Transform::rotate2DAntiClkWise(Matrix2x1 & toRot, float thetaRads)
{
	float cosTheta = cosf(thetaRads);
	float sinTheta = sinf(thetaRads);
	float negitiveSinTheta = 0.0f - sinTheta;
	Matrix2x2 rot;
	rot.r1c1 = cosTheta;
	rot.r1c2 = negitiveSinTheta;
	rot.r2c1 = sinTheta;
	rot.r2c2 = cosTheta;
	toRot = Math::MatrixMath::multiply(rot, toRot);
}

// 3d rotation matrix versions
void Math::Transform::rotate3DX(Matrix3x1 & toRotate, float thetaRads)
{
	float cosTheta = cosf(thetaRads);
	float sinTheta = sinf(thetaRads);
	float negSinTheta = 0.0f - sinTheta;
	Matrix3x3 rot;
	Math::MatrixMath::makeIdentity(rot);
	rot.r2c2 = cosTheta;
	rot.r2c3 = negSinTheta;
	rot.r3c2 = sinTheta;
	rot.r3c3 = cosTheta;
	toRotate = Math::MatrixMath::multiply(rot, toRotate);
}

void Math::Transform::rotate3DY(Matrix3x1 & toRotate, float thetaRads)
{
	float cosTheta = cosf(thetaRads);
	float sinTheta = sinf(thetaRads);
	float negSinTheta = 0.0f - sinTheta;
	Matrix3x3 rot;
	Math::MatrixMath::makeIdentity(rot);
	rot.r1c1 = cosTheta;
	rot.r1c3 = sinTheta;
	rot.r3c1 = negSinTheta;
	rot.r3c3 = cosTheta;
	toRotate = Math::MatrixMath::multiply(rot, toRotate);
}

void Math::Transform::rotate3DZ(Matrix3x1 & toRotate, float thetaRads)
{
	float cosTheta = cosf(thetaRads);
	float sinTheta = sinf(thetaRads);
	float negSinTheta = 0.0f - sinTheta;
	Matrix3x3 rot;
	Math::MatrixMath::makeIdentity(rot);
	rot.r1c1 = cosTheta;
	rot.r1c2 = negSinTheta;
	rot.r2c1 = sinTheta;
	rot.r2c2 = cosTheta;
	toRotate = Math::MatrixMath::multiply(rot, toRotate);
}

void Math::Transform::rotateCustomAxis(Vector3D & axis, float thetaRads, Matrix3x1 & toRotate) // axis must be unit lenght
{
	float cosTheta, sinTheta;
	Matrix3x3 rot;
	cosTheta = cosf(thetaRads);
	sinTheta = sinf(thetaRads);
	rot.r1c1 = cosTheta + (1.0f - cosTheta) * (axis.x * axis.x);
	rot.r1c2 = (1.0f - cosTheta) * (axis.x * axis.y) - (sinTheta *  axis.z);
	rot.r1c3 = (1.0f - cosTheta) * (axis.x * axis.z) + (sinTheta * axis.y);

	rot.r2c1 = (1.0f - cosTheta) * (axis.x * axis.y) + (sinTheta * axis.z);
	rot.r2c2 = cosTheta + (1.0f - cosTheta) * (axis.y * axis.y);
	rot.r2c3 = (1.0f - cosTheta) * (axis.y * axis.z) - (sinTheta * axis.z);

	rot.r3c1 = (1.0f - cosTheta) * (axis.x * axis.z) - (sinTheta * axis.y);
	rot.r3c2 = (1.0f - cosTheta) * (axis.y * axis.z) + (sinTheta * axis.x);
	rot.r3c3 = cosTheta + (1.0f - cosTheta) * (axis.z * axis.z);

	toRotate = Math::MatrixMath::multiply(rot, toRotate);
}

Matrix2x2 Math::Transform::get2dRotationMatrixClkWise(float thetaRads)
{
	float cosTheta = cosf(thetaRads);
	float sinTheta = sinf(thetaRads);
	float negitiveSinTheta = 0.0f - sinTheta;
	Matrix2x2 rv;
	rv.r1c1 = cosTheta;
	rv.r1c2 = sinTheta;
	rv.r2c1 = negitiveSinTheta;
	rv.r2c2 = cosTheta;
	return rv;
}

Matrix2x2 Math::Transform::get2dRotationMatrixAntiClkWise(float thetaRads)
{
	float cosTheta = cosf(thetaRads);
	float sinTheta = sinf(thetaRads);
	float negitiveSinTheta = 0.0f - sinTheta;
	Matrix2x2 rv;
	rv.r1c1 = cosTheta;
	rv.r1c2 = negitiveSinTheta;
	rv.r2c1 = sinTheta;
	rv.r2c2 = cosTheta;
	return rv;
}

Matrix3x3 Math::Transform::get3x3Rotate3DXMatrix(float thetaRads)
{
	float cosTheta = cosf(thetaRads);
	float sinTheta = sinf(thetaRads);
	float negSinTheta = 0.0f - sinTheta;
	Matrix3x3 rv;
	Math::MatrixMath::makeIdentity(rv);
	rv.r2c2 = cosTheta;
	rv.r2c3 = negSinTheta;
	rv.r3c2 = sinTheta;
	rv.r3c3 = cosTheta;
	return rv;
}

Matrix3x3 Math::Transform::get3x3Rotate3DYMatrix(float thetaRads)
{
	float cosTheta = cosf(thetaRads);
	float sinTheta = sinf(thetaRads);
	float negSinTheta = 0.0f - sinTheta;
	Matrix3x3 rv;
	Math::MatrixMath::makeIdentity(rv);
	rv.r1c1 = cosTheta;
	rv.r1c3 = sinTheta;
	rv.r3c1 = negSinTheta;
	rv.r3c3 = cosTheta;
	return rv;
}

Matrix3x3 Math::Transform::get3x3Rotate3DZMatrix(float thetaRads)
{
	float cosTheta = cosf(thetaRads);
	float sinTheta = sinf(thetaRads);
	float negSinTheta = 0.0f - sinTheta;
	Matrix3x3 rv;
	Math::MatrixMath::makeIdentity(rv);
	rv.r1c1 = cosTheta;
	rv.r1c2 = negSinTheta;
	rv.r2c1 = sinTheta;
	rv.r2c2 = cosTheta;
	return rv;
}

Matrix3x3 Math::Transform::getRotationMatrixForCustomAxis(Vector3D & axis, float thetaRads)
{
	float cosTheta, sinTheta;
	Matrix3x3 rot;
	cosTheta = cosf(thetaRads);
	sinTheta = sinf(thetaRads);

	rot.r1c1 = cosTheta + (1.0f - cosTheta) * (axis.x * axis.x);
	rot.r1c2 = (1.0f - cosTheta) * (axis.x * axis.y) - (sinTheta *  axis.z);
	rot.r1c3 = (1.0f - cosTheta) * (axis.x * axis.z) + (sinTheta * axis.y);

	rot.r2c1 = (1.0f - cosTheta) * (axis.x * axis.y) + (sinTheta * axis.z);
	rot.r2c2 = cosTheta + (1.0f - cosTheta) * (axis.y * axis.y);
	rot.r2c3 = (1.0f - cosTheta) * (axis.y * axis.z) - (sinTheta * axis.z);

	rot.r3c1 = (1.0f - cosTheta) * (axis.x * axis.z) - (sinTheta * axis.y);
	rot.r3c2 = (1.0f - cosTheta) * (axis.y * axis.z) + (sinTheta * axis.x);
	rot.r3c3 = cosTheta + (1.0f - cosTheta) * (axis.z * axis.z);

	return rot;
}

Matrix4x4 Math::Transform::get4x4RotationMatrixForCustomAxis(Vector3D & axis, float thetaRads)
{
	Matrix4x4 rv;
	float cosTheta, sinTheta;
	cosTheta = cosf(thetaRads);
	sinTheta = sinf(thetaRads);

	rv.r1c1 = cosTheta + (1.0f - cosTheta) * (axis.x * axis.x);
	rv.r1c2 = (1.0f - cosTheta) * (axis.x * axis.y) - (sinTheta *  axis.z);
	rv.r1c3 = (1.0f - cosTheta) * (axis.x * axis.z) + (sinTheta * axis.y);
	rv.r1c4 = 0.0f;

	rv.r2c1 = (1.0f - cosTheta) * (axis.x * axis.y) + (sinTheta * axis.z);
	rv.r2c2 = cosTheta + (1.0f - cosTheta) * (axis.y * axis.y);
	rv.r2c3 = (1.0f - cosTheta) * (axis.y * axis.z) - (sinTheta * axis.z);
	rv.r2c4 = 0.0f;

	rv.r3c1 = (1.0f - cosTheta) * (axis.x * axis.z) - (sinTheta * axis.y);
	rv.r3c2 = (1.0f - cosTheta) * (axis.y * axis.z) + (sinTheta * axis.x);
	rv.r3c3 = cosTheta + (1.0f - cosTheta) * (axis.z * axis.z);
	rv.r3c4 = 0.0f;

	rv.r4c1 = 0.0f;
	rv.r4c2 = 0.0f;
	rv.r4c3 = 0.0f;
	rv.r4c4 = 1.0f;
	return rv;
}

Matrix2x2 Math::Transform::get2x2ScalingMatrix(float x, float y)
{
	Matrix2x2 rv;
	Math::MatrixMath::makeIdentity(rv);
	rv.r1c1 = x;
	rv.r2c2 = y;
	return rv;
}

Matrix3x3 Math::Transform::get3x3ScalingMatrix(float x, float y, float z)
{
	Matrix3x3 rv;
	Math::MatrixMath::makeIdentity(rv);
	rv.r1c1 = x;
	rv.r2c2 = y;
	rv.r3c3 = z;
	return rv;
}

Matrix4x4 Math::Transform::get4x4ScalingMatrix(float x, float y, float z, float w)
{
	Matrix4x4 rv;
	Math::MatrixMath::makeIdentity(rv);
	rv.r1c1 = x;
	rv.r2c2 = y;
	rv.r3c3 = z;
	rv.r4c4 = w;
	return rv;
}

Matrix4x4 Math::Transform::get4x4TranslationMatrix(Vector3D & trans)
{
	Matrix4x4 rv;
	Math::MatrixMath::makeIdentity(rv);
	rv.r1c4 = trans.x;
	rv.r2c4 = trans.y;
	rv.r3c4 = trans.z;
	return rv;
}

void Math::Transform::translate2D(Matrix2x1 & toTranslate, Vector2D & translateBy)
{
	toTranslate.r1c1 += translateBy.x;
	toTranslate.r2c1 += translateBy.y;
}

void Math::Transform::translate3D(Matrix3x1 & toTranslate, Vector3D & translateBy)
{
	toTranslate.r1c1 += translateBy.x;
	toTranslate.r2c1 += translateBy.y;
	toTranslate.r3c1 += translateBy.z;
}

float Math::Interpolation::lerp(float valueA, float valueB, float targetPoint) // target point should be between 0.0f & 1.0f
{
	return (1.0f - targetPoint) * valueA + targetPoint * valueB;
}


Vector2D Math::Interpolation::lerp(const Vector2D & vectorA, const Vector2D & vectorB, float targetPoint)
{
	if (targetPoint <= 0.0f)
	{
		return vectorA;
	}
	else if(targetPoint >= 1.0f)
	{
		return vectorB;
	}
	Vector2D rv;
	rv.x = lerp(vectorA.x, vectorB.x, targetPoint);
	rv.y = lerp(vectorA.y, vectorB.y, targetPoint);
	return rv;
}

Vector3D Math::Interpolation::lerp(const Vector3D & vectorA, const Vector3D & vectorB, float targetPoint)
{
	if (targetPoint <= 0.0f)
	{
		return vectorA;
	}
	else if (targetPoint >= 1.0f)
	{
		return vectorB;
	}
	Vector3D rv;
	rv.x = lerp(vectorA.x, vectorB.x, targetPoint);
	rv.y = lerp(vectorA.y, vectorB.y, targetPoint);
	rv.z = lerp(vectorA.z, vectorB.z, targetPoint);
	return rv;
}

Quaternion Math::Interpolation::lerp(const Quaternion & qa, const Quaternion & qb, float targetPoint)
{
	if(targetPoint <= 0.0f)
	{
		return qa;
	}
	else if(targetPoint >= 1.0f)
	{
		return qb;
	}

	Quaternion rv;
	rv.w = lerp(qa.w, qb.w, targetPoint);
	rv.x = lerp(qa.x, qb.x, targetPoint);
	rv.y = lerp(qa.y, qb.y, targetPoint);
	rv.z = lerp(qa.z, qb.z, targetPoint);

	rv = QuaternionMath::normalise(rv);

	return rv;
}

// slep
Quaternion Math::Interpolation::slerp(const Quaternion & a, const Quaternion & b, float t)
{
	if (t <= 0.0f)
	{
		return a;
	}
	else if(t >= 1.0f)
	{
		return b;
	}


	float dotProduct;
	dotProduct = a.x * b.x
		+ a.y * b.y
		+ a.z * b.z
		+ a.w * b.w;
	float omega = acosf(dotProduct);
	float sinO;
	float sinTO;
	float sinOneSubTByO;

	sinO = sinf(omega);
	sinTO = sinf(t * omega);
	sinOneSubTByO = sinf((1.0f - t) * omega);

	float aScale, bScale;
	aScale = sinOneSubTByO / sinO;
	bScale = sinTO / sinO;

	Quaternion rvA = QuaternionMath::scale(a, aScale);
	Quaternion rvB = QuaternionMath::scale(b, bScale);
	Quaternion rv = QuaternionMath::add(rvA, rvB);
	rv = QuaternionMath::normalise(rv);
	return rv;
}

float Math::Interpolation::biLerp(float a0, float a1, float b0, float b1, float tx, float ty)
{
	float ax = lerp(a0, a1, tx);
	float bx = lerp(b0, b1, tx);

	return lerp(ax, bx, ty);
}

float Math::Interpolation::triLerp(float _000, float _100,
	float _010, float _110,

	float _001, float _101,
	float _011, float _111,

	float tx, float ty, float tz)
{
	float frontAx = lerp(_000, _100, tx);
	float frontBx = lerp(_010, _110, tx);

	float backAx = lerp(_001, _101, tx);
	float backBx = lerp(_011, _111, tx);

	float frontPoint = lerp(frontAx, frontBx, ty);
	float backPoint = lerp(backAx, backBx, ty);

	return lerp(frontPoint, backPoint, tz);
}

float Math::Interpolation::interpolationWeight(float min, float max, float x)
{
	float diffMinMax = max - min;
	float diffMinX = x - min;
	if (diffMinMax == 0.0f)
	{
		return 1.0f;
	}
	return diffMinX / diffMinMax;
}