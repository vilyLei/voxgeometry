/**
Author: Vily

*/

#pragma once
#include <string>
#include "Vec3D.h"

namespace voxcgeom
{
    namespace math
    {
		class OrientationType
		{
		public:
			const static unsigned int AXIS_ANGLE;// = 0;
			const static unsigned int QUATERNION;// = 1;
			const static unsigned int EULER_ANGLES;// = 2;

			OrientationType() = delete;
		};
		/////////////////////////////////////////////////////////////////////////////////////////////////
		class Matrix4
		{
		private:
			static int s_uid;
			const static VCG_Number s_initData[16];
			static Matrix4 s_tmat4;
			int m_uid;
			int m_index;
			VCG_Number* m_fs32;
			VCG_Number* m_localFS32;

			void getAxisRotation(VCG_Number x, VCG_Number y, VCG_Number z, VCG_Number radian);
		public:
			std::string name;// = "Matrix4";

			Matrix4();
			Matrix4(VCG_Number *pfs32, unsigned int index);
			unsigned int getCapacity();
			int getUid();
			VCG_Number* getLocalFS32() const;
			VCG_Number* getFS32();
			unsigned int getFSIndex();
			void identity();
			VCG_Number determinant();
			void append(const Matrix4& lhs);
			void append3x3(const Matrix4& lhs);
			void appendRotationPivot(VCG_Number radian, const Vec3D& axis);
			void appendRotationPivot(VCG_Number radian, const Vec3D& axis, const Vec3D& pivotPoint);
			void appendRotation(VCG_Number radian, const Vec3D& axis);
			void appendRotationX(VCG_Number radian);
			void appendRotationY(VCG_Number radian);
			void appendRotationZ(VCG_Number radian);
    		// 用欧拉角形式旋转(heading->pitch->bank) => (y->x->z)
			void appendRotationEulerAngle(VCG_Number radianX, VCG_Number radianY, VCG_Number radianZ);
			
			void setScaleXYZ(VCG_Number xScale, VCG_Number yScale, VCG_Number zScale);
			void setRotationEulerAngle(VCG_Number radianX, VCG_Number radianY, VCG_Number radianZ);
			
			void setRotationEulerAngle2(VCG_Number cosX, VCG_Number sinX, VCG_Number cosY, VCG_Number sinY, VCG_Number cosZ, VCG_Number sinZ);

			void setTranslationXYZ(VCG_Number px, VCG_Number py, VCG_Number pz);

			void setTranslation(const Vec3D& v3);
			void appendScaleXYZ(VCG_Number xScale, VCG_Number yScale, VCG_Number zScale);
			
			void appendScaleXY(VCG_Number xScale, VCG_Number yScale);
			void appendTranslationXYZ(VCG_Number px, VCG_Number py, VCG_Number pz);
			void appendTranslation(const Vec3D& v3);
			void copyColumnFrom(unsigned int column_index, const Vec3D& v3);
			void copyColumnTo(unsigned int column_index, Vec3D& v3);
			void setF32ArrAndIndex(VCG_Number* fs32Arr, unsigned int index = 0);
			void setF32ArrIndex(unsigned int index);
			void setF32Arr(VCG_Number* fs32Arr);
			void copyFromF32Arr(VCG_Number* fs32Arr, unsigned int index = 0);
			void copyToF32Arr(VCG_Number* fs32Arr, unsigned int index = 0);
			void copyFrom(const Matrix4& mat_other);

			void copyRawDataFrom(VCG_Number* float_rawDataArr, unsigned int rawDataLength = 16, unsigned int index = 0,bool bool_tp = false);
			void copyRawDataTo(VCG_Number* float_rawDataArr, unsigned int rawDataLength = 16, unsigned int index = 0, bool bool_tp = false);

			void copyRowFrom(unsigned int row_index, const Vec3D& v3);
			void copyRowTo(unsigned int row_index, Vec3D& v3);
			void decompose(unsigned int orientationStyle, Vec3D(&outvecs)[3]);

			bool invert();
			void pointAt(const Vec3D& pos, const Vec3D& at, const Vec3D& up);
			void prepend(const Matrix4& rhs);
	
			void prepend3x3(const Matrix4& rhs);
			void prependRotationPivot(VCG_Number radian, const Vec3D& axis, const Vec3D& pivotPoint);
			void prependRotation(VCG_Number radian, const Vec3D& axis);
			void prependRotationX(VCG_Number radian);
			void prependRotationY(VCG_Number radian);
			void prependRotationZ(VCG_Number radian);
			// 用欧拉角形式旋转(heading->pitch->bank) => (y->x->z)
			void prependRotationEulerAngle(VCG_Number radianX, VCG_Number radianY, VCG_Number radianZ);
			void prependScale(VCG_Number xScale, VCG_Number yScale, VCG_Number zScale);
			void prependScaleXY(VCG_Number xScale, VCG_Number yScale);
			void prependTranslationXYZ(VCG_Number px, VCG_Number py, VCG_Number pz);
			void prependTranslation(const Vec3D& v3);
			bool recompose(Vec3D(&components)[3], unsigned int orientationStyle);

			Vec3D deltaTransformVector(const Vec3D& v3);
			
			void deltaTransformVectorSelf(Vec3D& v3);
			void deltaTransformOutVector(const Vec3D& v3, Vec3D& out_v3);
			Vec3D transformVector(const Vec3D& v3);
			void transformOutVector(const Vec3D& v3, Vec3D& out_v3);
			void transformOutVector3(const Vec3D& v3, Vec3D& out_v3);
			void transformVector3Self(Vec3D& v3);
			void transformVectorSelf(Vec3D& v3);
			void transformVectors(VCG_Number* float_vinArr, unsigned int vinLength, VCG_Number* float_voutArr);
			void transpose();

			void interpolateTo(Matrix4& toMat, VCG_Number float_percent);
			void rotationX(VCG_Number radian);
			void rotationY(VCG_Number radian);
			void rotationZ(VCG_Number radian);
		    
			void transformPerspV4Self(Vec3D& v4);
		    
			void destroy();

			void coutThis();
		};
	}
}

typedef voxcgeom::math::OrientationType OrientationType;
typedef voxcgeom::math::Matrix4 Matrix4;