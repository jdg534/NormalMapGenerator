#ifndef _VECTOR_MATH_SOL_H_
#define _VECTOR_MATH_SOL_H_

#include "MathDataTypes.h"

namespace Math
{
	namespace VectorMath
	{
		float dotProduct(const Vector2D & vecA, const Vector2D & vecB);
		float dotProduct(const Vector3D & vecA, const Vector3D & vecB);

		Vector2D crossProduct(const Vector2D & vecA, const Vector2D & vecB);
		Vector3D crossProduct(const Vector3D & vecA, const Vector3D & vecB);

		Vector2D add (const Vector2D & a, const Vector2D & b);
		Vector2D subtract (const Vector2D & a, const Vector2D & b);

		Vector3D add (const Vector3D & a, const Vector3D & b);
		Vector3D subtract (const Vector3D & a, const Vector3D & b);

		Vector2D wayToVector(const Vector2D & pointA, const Vector2D & pointB);
		Vector3D wayToVector(const Vector3D & pointA, const Vector3D & pointB);

		float magnitude (const Vector2D & a);
		float magnitude (const Vector3D & a);

		Vector2D scaled(float scale, const Vector2D & toScale);
		Vector3D scaled(float scale, const Vector3D & toScale);

		Vector2D unitVector(const Vector2D & a);
		Vector3D unitVector(const Vector3D & a);

		float lookAt2D(const Vector2D & currentlyLookingAtPos, const Vector2D & toLookAtPos, const Vector2D & currentPos);// return angle to rotate by in radians
		Matrix4x4 lookAt3D(Vector3D & position, Vector3D & targetPosition, Vector3D & upVec);
	}

	
	float degreesToRadians(float valueInDegrees);
	float radiansToDegrees(float valueInRadians);
	

	namespace PolarCoordinateMath
	{
		PolarCoordinate CartesianToPolar(Vector2D & cartVal);
		Vector2D PolarToCartesian(PolarCoordinate & Polarval);
	}

	namespace MatrixMath
	{
		// http://en.wikipedia.org/wiki/Matrix_%28mathematics%29#Addition.2C_scalar_multiplication_and_transposition

		// addition
		Matrix2x1 add(const Matrix2x1 & a, const Matrix2x1 & b);
		Matrix2x2 add(const Matrix2x2 & a, const Matrix2x2 & b);
		Matrix3x1 add(const Matrix3x1 & a, const Matrix3x1 & b);
		Matrix3x3 add(const Matrix3x3 & a, const Matrix3x3 & b);
		Matrix4x1 add(const Matrix4x1 & a, const Matrix4x1 & b);
		Matrix4x3 add(const Matrix4x3 & a, const Matrix4x3 & b);
		Matrix4x4 add(const Matrix4x4 & a, const Matrix4x4 & b);
		
		// is a "direct sum" (two matercies concaternated in two 1)
		// http://en.wikipedia.org/wiki/Matrix_addition
		// direct sum not included in this library

		// subtraction
		Matrix2x1 subtract(const Matrix2x1 & a, const Matrix2x1 & b);
		Matrix2x2 subtract(const Matrix2x2 & a, const Matrix2x2 & b);
		Matrix3x1 subtract(const Matrix3x1 & a, const Matrix3x1 & b);
		Matrix3x3 subtract(const Matrix3x3 & a, const Matrix3x3 & b);
		Matrix4x1 subtract(const Matrix4x1 & a, const Matrix4x1 & b);
		Matrix4x3 subtract(const Matrix4x3 & a, const Matrix4x3 & b);
		Matrix4x4 subtract(const Matrix4x4 & a, const Matrix4x4 & b);

		// multerplication

		// scaler mul
		Matrix2x1 multiply(float scale, const Matrix2x1 & a);
		Matrix2x2 multiply(float scale, const Matrix2x2 & a);
		Matrix3x1 multiply(float scale, const Matrix3x1 & a);
		Matrix3x3 multiply(float scale, const Matrix3x3 & a);
		Matrix4x1 multiply(float scale, const Matrix4x1 & a);
		Matrix4x3 multiply(float scale, const Matrix4x3 & a);
		Matrix4x4 multiply(float scale, const Matrix4x4 & a);


		// matrix mul
		// 2x2 x 2x1 = 2x1
		// 2x2 x 2x2 = 2x2
		Matrix2x1 multiply(const Matrix2x2 & a, const Matrix2x1 & b);
		Matrix2x2 multiply(const Matrix2x2 & a, const Matrix2x2 & b);

		// 3x3 x 3x1 = 3x1
		// 3x3 x 3x3 = 3x3
		Matrix3x1 multiply(const Matrix3x3 & a, const Matrix3x1 & b);
		Matrix3x3 multiply(const Matrix3x3 & a, const Matrix3x3 & b);

		// 4x4 x 4x1 = 4x1
		// 4x4 x 4x3 = 4x3
		// 4x4 x 4x4 = 4x4
		// 4x3 x 3x1 = 4x1
		// 4x3 x 3x3 = 4x3		

		Matrix4x1 multiply(const Matrix4x4 & a, const Matrix4x1 & b);
		Matrix4x3 multiply(const Matrix4x4 & a, const Matrix4x3 & b);
		Matrix4x4 multiply(const Matrix4x4 & a, const Matrix4x4 & b);
		Matrix4x1 multiply(const Matrix4x3 & a, const Matrix3x1 & b);
		Matrix4x3 multiply(const Matrix4x3 & a, const Matrix3x3 & b);


		// Determinant (2x2, 3x3,4x4 only)
		// denoted by det(A) or |A|
		// http://en.wikipedia.org/wiki/Determinant
		float determinant(const Matrix2x2 & a);
		float determinant(const Matrix3x3 & a);
		float determinant(const Matrix4x4 & a);

		// transpose
		// http://en.wikipedia.org/wiki/Matrix_%28mathematics%29#Addition.2C_scalar_multiplication_and_transposition
		Matrix2x2 transpose(const Matrix2x2 & a);
		Matrix3x3 transpose(const Matrix3x3 & a);
		Matrix4x4 transpose(const Matrix4x4 & a);

		// inverse
		// http://en.wikipedia.org/wiki/Invertible_matrix
		Matrix2x2 inverse(const Matrix2x2 & a);
		Matrix3x3 inverse(const Matrix3x3 & a);
		Matrix4x4 inverse(const Matrix4x4 & a);

		// identity
		void makeIdentity(Matrix2x2 & a);
		void makeIdentity(Matrix3x3 & a);
		void makeIdentity(Matrix4x4 & a);

		// Eigenvalues & eigenvectors?

	}

	namespace quaternion
	{
		// http://www.euclideanspace.com/maths/algebra/realNormedAlgebra/quaternions/code/
		// http://www.gamasutra.com/view/feature/131686/rotating_objects_using_quaternions.php


		Quaternion conjugate(const Quaternion & original);

		Quaternion normalise(const Quaternion & toNormalise);

		Quaternion scale(const Quaternion & toScale, float scale);

		Quaternion multiply(const Quaternion & a, const Quaternion & b);

		Quaternion add(const Quaternion & a, const Quaternion & b);

		Quaternion subtract(const Quaternion & a, const Quaternion & b);

		void identityForMul(Quaternion & a);

		void identityForAdd(Quaternion & a);

		float norm(Quaternion & a);
		
		Quaternion inverse(Quaternion & a);

		Matrix4x4 toMatrix4x4(Quaternion & a);

		Matrix3x3 toMatrix3x3(Quaternion & a);
	}

	namespace transform
	{
		// http://en.wikipedia.org/wiki/Transformation_matrix
		void scale2D(Matrix2x1 & toScale, float xScale, float yScale);
		void scale3D(Matrix3x1 & toScale, float xScale, float yScale, float zScale);
		void scale4D(Matrix4x1 & toScale, float xScale, float yScale, float zScale, float wScale);
		void rotate2DClkWise(Matrix2x1 & toRot, float thetaRads);
		void rotate2DAntiClkWise(Matrix2x1 & toRot, float thetaRads);
		
		// 3d rotation matrix versions
		void rotate3DX(Matrix3x1 & toRotate, float thetaRads);
		void rotate3DY(Matrix3x1 & toRotate, float thetaRads);
		void rotate3DZ(Matrix3x1 & toRotate, float thetaRads);
		
		void rotateCustomAxis(Vector3D & axis, float thetaRads, Matrix3x1 & toRotate); // axis must be unit lenght

		Matrix3x3 getRotationMatrixForCustomAxis(Vector3D & axis, float thetaRads);

		// 3d rotations quaternion version

		// translations
		void translate2D(Matrix2x1 & toTranslate, Vector2D & translateBy);
		void translate3D(Matrix3x1 & toTranslate, Vector3D & translateBy);
	}

	namespace interpolation
	{
		float lerp(float valueA, float valueB, float targetPoint); // target point should be between 0.0f & 1.0f
		
		// vector lerp
		Vector2D lerp(const Vector2D & vectorA, const Vector2D & vectorB, float targetPoint);
		
		Vector3D lerp(const Vector3D & vectorA, const Vector3D & vectorB, float targetPoint);
		
		// for good mesure a templeted version
		template <typename T>
		T lerp(T valueA, T valueB, float targetPoint)
		{
			return (1.0f - targetPoint) * valueA + targetPoint * valueB;
		}

		Quaternion lerp(const Quaternion & qa, const Quaternion & qb, float targetPoint);

		// slep
		Quaternion slerp(const Quaternion & a, const Quaternion & b, float t);
	}
}

#endif