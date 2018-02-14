#include "Math.h"
#include <cmath>

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
	rv.x = (vecA.y * vecB.z) - (vecB.z * vecA.y);
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
	Vector2D ao;
	ao.x = 0.0f - pointA.x;
	ao.y = 0.0f - pointA.y;
	return add(ao, pointB);
}

Vector3D Math::VectorMath::wayToVector(const Vector3D & pointA, const Vector3D & pointB)
{
	Vector3D ao;
	ao.x = 0.0f - pointA.x;
	ao.y = 0.0f - pointA.y;
	ao.z = 0.0f - pointA.z;
	return add(ao,  pointB);
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

Vector2D Math::VectorMath::scaled(float scale, const Vector2D & toScale)
{
	// mul the components
	Vector2D rv;
	rv.x = toScale.x * scale;
	rv.y = toScale.y * scale;
	return toScale;
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

// based off: http://www.phatcode.net/articles.php?id=216
// and: http://games.greggman.com/game/webgl-3d-cameras/
// also http://3dgep.com/understanding-the-view-matrix/
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


// matrix stuff here
// http://en.wikipedia.org/wiki/Matrix_%28mathematics%29#Addition.2C_scalar_multiplication_and_transposition

// addition
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
	Matrix4x3 rv; // return value
	
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
		
		// is a "direct sum" (two matercies concaternated in two 1)
		// http://en.wikipedia.org/wiki/Matrix_addition
		// direct sum not included in this library

// subtraction
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

		// multerplication

		// scaler mul
Matrix2x1 Math::MatrixMath::multiply(float scale, const Matrix2x1 & a)
{
	Matrix2x1 rv; // return value
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


		// matrix mul
		// 2x2 x 2x1 = 2x1
		// 2x2 x 2x2 = 2x2
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

		// 3x3 x 3x1 = 3x1
		// 3x3 x 3x3 = 3x3
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

		// 4x4 x 4x1 = 4x1
		// 4x4 x 4x3 = 4x3
		// 4x4 x 4x4 = 4x4
		// 4x3 x 3x1 = 4x1
		// 4x3 x 3x3 = 4x3		

Matrix4x1 Math::MatrixMath::multiply(const Matrix4x4 & a, const Matrix4x1 & b)
{
	Matrix4x1 rv;
	rv.r1c1 = (a.r1c1 * b.r1c1) + (a.r1c2 * b.r2c1) + (a.r1c3 * b.r3c1) + (a.r1c4 * b.r4c1);
	rv.r2c1 = (a.r2c1 * b.r1c1) + (a.r2c2 * b.r2c1) + (a.r1c3 * b.r3c1) + (a.r1c4 * b.r4c1);
	rv.r3c1 = (a.r3c1 * b.r1c1) + (a.r3c2 * b.r2c1) + (a.r1c3 * b.r3c1) + (a.r1c4 * b.r4c1);
	rv.r4c1 = (a.r4c1 * b.r1c1) + (a.r4c2 * b.r2c1) + (a.r1c3 * b.r3c1) + (a.r1c4 * b.r4c1);

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
	rv.r4c2 = (a.r3c1 * b.r1c2) + (a.r4c2 * b.r2c2) + (a.r4c3 * b.r3c2) + (a.r4c4 * b.r4c2);
	rv.r4c3 = (a.r3c1 * b.r1c3) + (a.r4c2 * b.r2c3) + (a.r4c3 * b.r3c3) + (a.r4c4 * b.r4c3);
	rv.r4c4 = (a.r3c1 * b.r1c4) + (a.r4c2 * b.r2c4) + (a.r4c3 * b.r3c4) + (a.r4c4 * b.r4c4);

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


		// Determinant (2x2, 3x3,4x4 only)
		// denoted by det(A) or |A|
		// http://en.wikipedia.org/wiki/Determinant
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
	// https://www.khanacademy.org/math/linear-algebra/matrix_transformations/determinant_depth/v/linear-algebra--simpler-4x4-determinant
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

		// transpose
		// http://en.wikipedia.org/wiki/Matrix_%28mathematics%29#Addition.2C_scalar_multiplication_and_transposition
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

		// inverse
		// http://en.wikipedia.org/wiki/Invertible_matrix
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
	/*
	float det = determinant(a);

	Matrix3x3 toMul;
	// https://www.youtube.com/watch?v=pKZyszzmyeQ
	*/

	

	// float mulVal = 1.0f / determinant(a);
	// Matrix3x3 aTrans = transpose(a);

	// return multiply(mulVal, aTrans);

	// WRONG USE: http://www.cg.info.hiroshima-cu.ac.jp/~miyazaki/knowledge/teche23.html

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
	// as done on: http://www.cg.info.hiroshima-cu.ac.jp/~miyazaki/knowledge/teche23.html
}

Matrix4x4 Math::MatrixMath::inverse(const Matrix4x4 & a)
{
	// http://en.wikipedia.org/wiki/Invertible_matrix#Inversion_of_2.C3.972_matrices
	float mul = 1.0f / determinant(a);
	Matrix4x4 b;
	// off the sheet
	// http://www.cg.info.hiroshima-cu.ac.jp/~miyazaki/knowledge/teche23.html

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

	// may need to rewrite the 3x3 version of this func
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

// identity
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

// Quaternion
Quaternion Math::quaternion::conjugate(const Quaternion & original)
{
	Quaternion rv;

	rv.theta = original.theta;
	rv.x = 0.0f - original.x;
	rv.y = 0.0f - original.y;
	rv.z = 0.0f - original.z;

	return rv;
}

Quaternion Math::quaternion::normalise(const Quaternion & toNormalise)
{
	/* ORIGINAL
	float dev = sqrtf(
		toNormalise.x * toNormalise.x +
		toNormalise.y * toNormalise.y +
		toNormalise.z * toNormalise.z +
		toNormalise.theta * toNormalise.theta);
	*/
	float dev = sqrtf(
		toNormalise.x * toNormalise.x +
		toNormalise.y * toNormalise.y +
		toNormalise.z * toNormalise.z);
	dev = 1.0f / dev;
	Quaternion rv;
	rv.x = toNormalise.x * dev;
	rv.y = toNormalise.y * dev;
	rv.z = toNormalise.z * dev;
	rv.theta = toNormalise.theta;
	return rv;
}

Quaternion Math::quaternion::scale(const Quaternion & toScale, float scale)
{
	Quaternion rv;
	rv.x = toScale.x * scale;
	rv.y = toScale.y * scale;
	rv.z = toScale.z * scale;
	rv.theta = toScale.theta * scale;
	return rv;
}

Quaternion Math::quaternion::multiply(const Quaternion & a, const Quaternion & b)
{
	Quaternion rv; // rv short for return value
	// http://www.euclideanspace.com/maths/algebra/realNormedAlgebra/quaternions/code/#conjugate
	rv.x = a.x * b.theta + a.y * b.z - a.z * b.y + a.theta * b.x;
	rv.y = -a.x * b.z + a.y * b.theta + a.z * b.x + a.theta * b.y;
	rv.z = a.x * b.y - a.y * b.x + a.z * b.theta + a.theta * b.z;
	rv.theta = -a.x * b.x - a.y * b.y - a.z * b.z + a.theta * b.theta;
	return rv;
}

Quaternion Math::quaternion::add(const Quaternion & a, const Quaternion & b)
{
	Quaternion rv;
	rv.theta = a.theta + b.theta;
	rv.x = a.x + b.x;
	rv.y = a.y + b.y;
	rv.z = a.z + b.z;
	return rv;
}

Quaternion Math::quaternion::subtract(const Quaternion & a, const Quaternion & b)
{
	Quaternion rv;
	rv.theta = a.theta - b.theta;
	rv.x = a.x - b.x;
	rv.y = a.y - b.y;
	rv.z = a.z - b.z;
	return rv;
}

void Math::quaternion::identityForMul(Quaternion & a)
{
	a.theta = 1.0f;
	a.x = 0.0f;
	a.y = 0.0f;
	a.z = 0.0f;
}

void Math::quaternion::identityForAdd(Quaternion & a)
{
	a.theta = 0.0f;
	a.x = 0.0f;
	a.y = 0.0f;
	a.z = 0.0f;
}

float Math::quaternion::norm(Quaternion & a)
{
	return sqrtf(a.x * a.x 
		+ a.y * a.y
		+ a.z * a.z
		+ a.theta * a.theta);
}

Quaternion Math::quaternion::inverse(Quaternion & a)
{
	float n = norm(a);
			Quaternion aConj = conjugate(a);
			aConj.x /= n;
			aConj.y /= n;
			aConj.z /= n;
			aConj.theta /= n;
			return aConj;
		}

Matrix4x4 Math::quaternion::toMatrix4x4(Quaternion & a)
{
	Matrix4x4 rv;
	float tx, ty, tz, xx, yy, yz, xy, xz, zz;
	xx = a.x * a.x;
	xy = a.x * a.y;
	xz = a.x * a.z;
	yy = a.y * a.y;
	zz = a.z * a.z;
	yz = a.y * a.z;
	tx = a.theta * a.x;
	ty = a.theta * a.y;
	tz = a.theta * a.z;

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

Matrix3x3 Math::quaternion::toMatrix3x3(Quaternion & a)
{
	Matrix3x3 rv;
	rv.r1c1 = 1.0f - (2.0f * (a.y * a.y)) - (2.0f * (a.z * a.z));
	rv.r1c2 = (2.0f * a.x * a.y) - (2.0f * a.theta * a.z);
	rv.r1c3 = (2.0f * a.x * a.z) + (2.0f * a.theta * a.y);

	rv.r2c1 = (2.0f * a.x * a.y) + (2.0f * a.theta * a.z);
	rv.r2c2 = 1.0f - (2.0f * (a.x * a.x)) - (2.0f * (a.z * a.z));
	rv.r2c3 = (2.0f * (a.y * a.z)) - (2.0f * a.theta * a.x);

	rv.r3c1 = (2.0f * a.x * a.z) - (2.0f * a.theta * a.y);
	rv.r3c2 = (2.0f * a.y * a.z) + (2.0f * a.theta * a.x);
	rv.r3c3 = 1.0f - (2.0f * (a.x * a.x)) - (2.0f * (a.y * a.y));

	return rv;
}

// transforms
void Math::transform::scale2D(Matrix2x1 & toScale, float xScale, float yScale)
{
	Matrix2x2 mul;
	Math::MatrixMath::makeIdentity(mul);
	mul.r1c1 = xScale;
	mul.r2c2 = yScale;
	toScale = Math::MatrixMath::multiply(mul, toScale);
}

void Math::transform::scale3D(Matrix3x1 & toScale, float xScale, float yScale, float zScale)
{
	Matrix3x3 mul;
	Math::MatrixMath::makeIdentity(mul);
	mul.r1c1 = xScale;
	mul.r2c2 = yScale;
	mul.r3c3 = zScale;
	toScale = Math::MatrixMath::multiply(mul, toScale);
}

void Math::transform::scale4D(Matrix4x1 & toScale, float xScale, float yScale, float zScale, float wScale)
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

void Math::transform::rotate2DClkWise(Matrix2x1 & toRot, float thetaRads)
{
	float cosTheta = cos(thetaRads);
	float sinTheta = sin(thetaRads);
	float negitiveSinTheta = 0.0f - sinTheta;
	Matrix2x2 rot;
	rot.r1c1 = cosTheta;
	rot.r1c2 = sinTheta;
	rot.r2c1 = negitiveSinTheta;
	rot.r2c2 = cosTheta;
	toRot = Math::MatrixMath::multiply(rot, toRot);
}

void Math::transform::rotate2DAntiClkWise(Matrix2x1 & toRot, float thetaRads)
{
	float cosTheta = cos(thetaRads);
	float sinTheta = sin(thetaRads);
	float negitiveSinTheta = 0.0f - sinTheta;
	Matrix2x2 rot;
	rot.r1c1 = cosTheta;
	rot.r1c2 = negitiveSinTheta;
	rot.r2c1 = sinTheta;
	rot.r2c2 = cosTheta;
	toRot = Math::MatrixMath::multiply(rot, toRot);
}

// 3d rotation matrix versions
void Math::transform::rotate3DX(Matrix3x1 & toRotate, float thetaRads)
{
	float cosTheta = cos(thetaRads);
	float sinTheta = sin(thetaRads);
	float negSinTheta = 0.0f - sinTheta;
	Matrix3x3 rot;
	Math::MatrixMath::makeIdentity(rot);
	rot.r2c2 = cosTheta;
	rot.r2c3 = negSinTheta;
	rot.r3c2 = sinTheta;
	rot.r3c3 = cosTheta;
	toRotate = Math::MatrixMath::multiply(rot, toRotate);
}

void Math::transform::rotate3DY(Matrix3x1 & toRotate, float thetaRads)
{
	float cosTheta = cos(thetaRads);
	float sinTheta = sin(thetaRads);
	float negSinTheta = 0.0f - sinTheta;
	Matrix3x3 rot;
	Math::MatrixMath::makeIdentity(rot);
	rot.r1c1 = cosTheta;
	rot.r1c3 = sinTheta;
	rot.r3c1 = negSinTheta;
	rot.r3c3 = cosTheta;
	toRotate = Math::MatrixMath::multiply(rot, toRotate);
}

void Math::transform::rotate3DZ(Matrix3x1 & toRotate, float thetaRads)
{
	float cosTheta = cos(thetaRads);
	float sinTheta = sin(thetaRads);
	float negSinTheta = 0.0f - sinTheta;
	Matrix3x3 rot;
	Math::MatrixMath::makeIdentity(rot);
	rot.r1c1 = cosTheta;
	rot.r1c2 = negSinTheta;
	rot.r2c1 = sinTheta;
	rot.r2c2 = cosTheta;
	toRotate = Math::MatrixMath::multiply(rot, toRotate);
}
	
void Math::transform::rotateCustomAxis(Vector3D & axis, float thetaRads, Matrix3x1 & toRotate) // axis must be unit lenght
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

Matrix3x3 Math::transform::getRotationMatrixForCustomAxis(Vector3D & axis, float thetaRads)
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

void Math::transform::translate2D(Matrix2x1 & toTranslate, Vector2D & translateBy)
{
	toTranslate.r1c1 += translateBy.x;
	toTranslate.r2c1 += translateBy.y;
}

void Math::transform::translate3D(Matrix3x1 & toTranslate, Vector3D & translateBy)
{
	toTranslate.r1c1 += translateBy.x;
	toTranslate.r2c1 += translateBy.y;
	toTranslate.r3c1 += translateBy.z;
}

float Math::interpolation::lerp(float valueA, float valueB, float targetPoint) // target point should be between 0.0f & 1.0f
{
	return (1.0f - targetPoint) * valueA + targetPoint * valueB;
}
		
// vector lerp
Vector2D Math::interpolation::lerp(const Vector2D & vectorA, const Vector2D & vectorB, float targetPoint)
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
		
Vector3D Math::interpolation::lerp(const Vector3D & vectorA, const Vector3D & vectorB, float targetPoint)
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

Quaternion Math::interpolation::lerp(const Quaternion & qa, const Quaternion & qb, float targetPoint)
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
	rv.theta = lerp(qa.theta, qb.theta, targetPoint);
	rv.x = lerp(qa.x, qb.x, targetPoint);
	rv.y = lerp(qa.y, qb.y, targetPoint);
	rv.z = lerp(qa.z, qb.z, targetPoint);

	rv = quaternion::normalise(rv);

	return rv;
}

// slep
Quaternion Math::interpolation::slerp(const Quaternion & a, const Quaternion & b, float t)
{
	if (t <= 0.0f)
	{
		return a;
	}
	else if(t >= 1.0f)
	{
		return b;
	}
	/* original, now going for geometric slerp
	float dotProduct; // the dot product for the two axies
	dotProduct = a.x * b.x
		+ a.y * b.y
		+ a.z * b.z
		+ a.theta * b.theta;
	float theta = acosf(dotProduct);

	// rest as in the equasion
	float sinTheta = sinf(theta);
	float sinThetaT = sinTheta * t;
	float sinTheta1SubT = sinTheta * (1.0f - t);
	float mul1, mul2;
	mul1 = sinTheta1SubT / sinTheta;
	mul2 = sinThetaT / sinTheta;
	Quaternion rv = quaternion::add(quaternion::scale(a, mul1), quaternion::scale(b, mul2));
	// need to normalise the vector component

	// make the vector bit unit length, a.k.a Normalised
	// return quaternion::normalise(rv);
	Vector3D nor;
	nor.x = rv.x;
	nor.y = rv.y;
	nor.z = rv.z;
	nor = VectorMath::unitVector(nor);
	rv.x = nor.x;
	rv.y = nor.y;
	rv.z = nor.z;
	return rv;
	*/


	float dotProduct; // the dot product for the two axies
	dotProduct = a.x * b.x
		+ a.y * b.y
		+ a.z * b.z
		+ a.theta * b.theta;
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

	Quaternion rvA = quaternion::scale(a, aScale);
	Quaternion rvB = quaternion::scale(b, bScale);
	Quaternion rv = quaternion::add(rvA, rvB);
	rv = quaternion::normalise(rv);
	return rv;
}