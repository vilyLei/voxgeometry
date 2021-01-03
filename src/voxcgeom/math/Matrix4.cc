
#include <iostream>
#include <cmath>
#include "assert.h"
#include "Matrix4.h"
namespace voxcgeom
{
	namespace math
	{
		/// <summary>
		/// class OrientationType
		/// </summary>
		const unsigned int OrientationType::AXIS_ANGLE { 0 };
		const unsigned int OrientationType::QUATERNION { 1 };
		const unsigned int OrientationType::EULER_ANGLES{ 2 };


		/// <summary>
		/// class Matrix4
		/// </summary>
		
		int Matrix4::s_uid{0};
		Matrix4 Matrix4::s_tmat4{};
		const VCG_Number Matrix4::s_initData[16]{
				1.0f,0.0f,0.0f,0.0f,
				0.0f,1.0f,0.0f,0.0f,
				0.0f,0.0f,1.0f,0.0f,
				0.0f,0.0f,0.0f,1.0f
		};
		Matrix4::Matrix4()
		{
			m_uid = s_uid++;
			m_fs32 = new VCG_Number[16]{
				1.0,0.0,0.0,0.0,
				0.0,1.0,0.0,0.0,
				0.0,0.0,1.0,0.0,
				0.0,0.0,0.0,1.0
			};
			m_index = 0;
			m_localFS32 = m_fs32;
			m_type = 0;
		}
		Matrix4::Matrix4(VCG_Number* pfs32, unsigned int index) 
			: m_uid(s_uid++)
			, m_index(index)
			, m_fs32(pfs32)
		{
			assert(pfs32 != nullptr);
			m_localFS32 = pfs32 + index;
			m_type = 1;
		}
		Matrix4::~Matrix4()
		{
			destroy();
		}

		unsigned int Matrix4::getCapacity()
		{
			return 16;
		}
		int Matrix4::getUid()
		{
			return m_uid;
		}


		void Matrix4::getAxisRotation(VCG_Number x, VCG_Number y, VCG_Number z, VCG_Number radian)
		{
			radian = -radian;
			auto s = std::sin(radian);
			auto c = std::cos(radian);
			auto t = 1.0f - c;
			m_localFS32[0] = c + x * x * t;
			m_localFS32[5] = c + y * y * t;
			m_localFS32[10] = c + z * z * t;
			auto tmp1 = x * y * t;
			auto tmp2 = z * s;
			m_localFS32[4] = tmp1 + tmp2;
			m_localFS32[1] = tmp1 - tmp2;
			tmp1 = x * z * t;
			tmp2 = y * s;
			m_localFS32[8] = tmp1 - tmp2;
			m_localFS32[2] = tmp1 + tmp2;
			tmp1 = y * z * t;
			tmp2 = x * s;
			m_localFS32[9] = tmp1 + tmp2;
			m_localFS32[6] = tmp1 - tmp2;
		}

		VCG_Number* Matrix4::getLocalFS32() const
		{
			return m_localFS32;
		}
		VCG_Number* Matrix4::getFS32()
		{
			return m_fs32;
		}
		unsigned int Matrix4::getFSIndex()
		{
			return m_index;
		}
		void Matrix4::identity()
		{
			std::memcpy(m_localFS32, &s_initData, VCG_MATRIX4_DATA_SIZE);
		}
		VCG_Number Matrix4::determinant()
		{
			return (m_localFS32[0] * m_localFS32[5] - m_localFS32[4] * m_localFS32[1])
				*
				(m_localFS32[10] * m_localFS32[15] - m_localFS32[14] * m_localFS32[11])
				-
				(m_localFS32[0] * m_localFS32[9] - m_localFS32[8] * m_localFS32[1])
				*
				(m_localFS32[6] * m_localFS32[15] - m_localFS32[14] * m_localFS32[7])
				+
				(m_localFS32[0] * m_localFS32[13] - m_localFS32[12] * m_localFS32[1])
				*
				(m_localFS32[6] * m_localFS32[11] - m_localFS32[10] * m_localFS32[7])
				+
				(m_localFS32[4] * m_localFS32[9] - m_localFS32[8] * m_localFS32[5])
				*
				(m_localFS32[2] * m_localFS32[15] - m_localFS32[14] * m_localFS32[3])
				-
				(m_localFS32[4] * m_localFS32[13] - m_localFS32[12] * m_localFS32[5])
				*
				(m_localFS32[2] * m_localFS32[11] - m_localFS32[10] * m_localFS32[3])
				+
				(m_localFS32[8] * m_localFS32[13] - m_localFS32[12] * m_localFS32[9])
				*
				(m_localFS32[2] * m_localFS32[7] - m_localFS32[6] * m_localFS32[3]);
		}
		void Matrix4::append(const Matrix4& lhs)
		{
			auto lfs32 = lhs.getLocalFS32();
			auto sfs32 = m_localFS32;

			auto m111 = sfs32[0];
			auto m121 = sfs32[4];
			auto m131 = sfs32[8];
			auto m141 = sfs32[12];
			auto m112 = sfs32[1];
			auto m122 = sfs32[5];
			auto m132 = sfs32[9];
			auto m142 = sfs32[13];
			auto m113 = sfs32[2];
			auto m123 = sfs32[6];
			auto m133 = sfs32[10];
			auto m143 = sfs32[14];
			auto m114 = sfs32[3];
			auto m124 = sfs32[7];
			auto m134 = sfs32[11];
			auto m144 = sfs32[15];
			auto m211 = lfs32[0];
			auto m221 = lfs32[4];
			auto m231 = lfs32[8];
			auto m241 = lfs32[12];
			auto m212 = lfs32[1];
			auto m222 = lfs32[5];
			auto m232 = lfs32[9];
			auto m242 = lfs32[13];
			auto m213 = lfs32[2];
			auto m223 = lfs32[6];
			auto m233 = lfs32[10];
			auto m243 = lfs32[14];
			auto m214 = lfs32[3];
			auto m224 = lfs32[7];
			auto m234 = lfs32[11];
			auto m244 = lfs32[15];
			sfs32[0] = m111 * m211 + m112 * m221 + m113 * m231 + m114 * m241;
			sfs32[1] = m111 * m212 + m112 * m222 + m113 * m232 + m114 * m242;
			sfs32[2] = m111 * m213 + m112 * m223 + m113 * m233 + m114 * m243;
			sfs32[3] = m111 * m214 + m112 * m224 + m113 * m234 + m114 * m244;
			sfs32[4] = m121 * m211 + m122 * m221 + m123 * m231 + m124 * m241;
			sfs32[5] = m121 * m212 + m122 * m222 + m123 * m232 + m124 * m242;
			sfs32[6] = m121 * m213 + m122 * m223 + m123 * m233 + m124 * m243;
			sfs32[7] = m121 * m214 + m122 * m224 + m123 * m234 + m124 * m244;
			sfs32[8] = m131 * m211 + m132 * m221 + m133 * m231 + m134 * m241;
			sfs32[9] = m131 * m212 + m132 * m222 + m133 * m232 + m134 * m242;
			sfs32[10] = m131 * m213 + m132 * m223 + m133 * m233 + m134 * m243;
			sfs32[11] = m131 * m214 + m132 * m224 + m133 * m234 + m134 * m244;
			sfs32[12] = m141 * m211 + m142 * m221 + m143 * m231 + m144 * m241;
			sfs32[13] = m141 * m212 + m142 * m222 + m143 * m232 + m144 * m242;
			sfs32[14] = m141 * m213 + m142 * m223 + m143 * m233 + m144 * m243;
			sfs32[15] = m141 * m214 + m142 * m224 + m143 * m234 + m144 * m244;
		}
		void Matrix4::append3x3(const Matrix4& lhs)
		{
			auto lfs32 = lhs.getLocalFS32();
			auto sfs32 = m_localFS32;

			auto m111 = sfs32[0];
			auto m121 = sfs32[4];
			auto m131 = sfs32[8];
			auto m112 = sfs32[1];
			auto m122 = sfs32[5];
			auto m132 = sfs32[9];
			auto m113 = sfs32[2];
			auto m123 = sfs32[6];
			auto m133 = sfs32[10];
			auto m211 = lfs32[0];
			auto m221 = lfs32[4];
			auto m231 = lfs32[8];
			auto m212 = lfs32[1];
			auto m222 = lfs32[5];
			auto m232 = lfs32[9];
			auto m213 = lfs32[2];
			auto m223 = lfs32[6];
			auto m233 = lfs32[10];

			sfs32[0] = m111 * m211 + m112 * m221 + m113 * m231;
			sfs32[1] = m111 * m212 + m112 * m222 + m113 * m232;
			sfs32[2] = m111 * m213 + m112 * m223 + m113 * m233;
			sfs32[4] = m121 * m211 + m122 * m221 + m123 * m231;
			sfs32[5] = m121 * m212 + m122 * m222 + m123 * m232;
			sfs32[6] = m121 * m213 + m122 * m223 + m123 * m233;
			sfs32[8] = m131 * m211 + m132 * m221 + m133 * m231;
			sfs32[9] = m131 * m212 + m132 * m222 + m133 * m232;
			sfs32[10] = m131 * m213 + m132 * m223 + m133 * m233;
		}
		void Matrix4::appendRotationPivot(VCG_Number radian, const Vec3D& axis)
		{
			auto& pivotPoint = Vec3D::Z_AXIS;
			Matrix4::s_tmat4.identity();
			Matrix4::s_tmat4.getAxisRotation(axis.x, axis.y, axis.z, radian);
			Matrix4::s_tmat4.appendTranslationXYZ(pivotPoint.x, pivotPoint.y, pivotPoint.z);
			append(Matrix4::s_tmat4);
		}
		void Matrix4::appendRotationPivot(VCG_Number radian, const Vec3D& axis, const Vec3D& pivotPoint)
		{
			Matrix4::s_tmat4.identity();
			Matrix4::s_tmat4.getAxisRotation(axis.x, axis.y, axis.z, radian);
			Matrix4::s_tmat4.appendTranslationXYZ(pivotPoint.x, pivotPoint.y, pivotPoint.z);
			append(Matrix4::s_tmat4);
		}
		void Matrix4::appendRotation(VCG_Number radian, const Vec3D& axis)
		{
			Matrix4::s_tmat4.identity();
			Matrix4::s_tmat4.getAxisRotation(axis.x, axis.y, axis.z, radian);
			append(Matrix4::s_tmat4);
		}
		void Matrix4::appendRotationX(VCG_Number radian)
		{
			Matrix4::s_tmat4.rotationX(radian);
			append3x3(Matrix4::s_tmat4);
		}
		void Matrix4::appendRotationY(VCG_Number radian)
		{
			Matrix4::s_tmat4.rotationY(radian);
			append3x3(Matrix4::s_tmat4);
		}
		void Matrix4::appendRotationZ(VCG_Number radian)
		{
			Matrix4::s_tmat4.rotationZ(radian);
			append3x3(Matrix4::s_tmat4);
		}



		// 用欧拉角形式旋转(heading->pitch->bank) => (y->x->z)
		void Matrix4::appendRotationEulerAngle(VCG_Number radianX, VCG_Number radianY, VCG_Number radianZ)
		{
			Matrix4::s_tmat4.rotationY(radianY);
			append3x3(Matrix4::s_tmat4);
			Matrix4::s_tmat4.rotationX(radianX);
			append3x3(Matrix4::s_tmat4);
			Matrix4::s_tmat4.rotationZ(radianZ);
			append3x3(Matrix4::s_tmat4);
		}
		void Matrix4::setScaleXYZ(VCG_Number xScale, VCG_Number yScale, VCG_Number zScale)
		{
			auto sfs32 = m_localFS32;
			sfs32[0] = xScale; sfs32[5] = yScale; sfs32[10] = zScale;
		}
		void Matrix4::setRotationEulerAngle(VCG_Number radianX, VCG_Number radianY, VCG_Number radianZ)
		{
			auto sfs32 = m_localFS32;
			//auto sx = sfs32[0];
			//auto sy = sfs32[5];
			//auto sz = sfs32[10];

			auto cosX = std::cos(radianX);
			auto sinX = std::sin(radianX);
			auto cosY = std::cos(radianY);
			auto sinY = std::sin(radianY);
			auto cosZ = std::cos(radianZ);
			auto sinZ = std::sin(radianZ);
			auto cosZsinY = cosZ * sinY;
			auto sinZsinY = sinZ * sinY;
			auto cosYscaleX = cosY * sfs32[0];
			auto sinXscaleY = sinX * sfs32[5];
			auto cosXscaleY = cosX * sfs32[5];
			auto cosXscaleZ = cosX * sfs32[10];
			auto sinXscaleZ = sinX * sfs32[10];

			sfs32[1] = sinZ * cosYscaleX;
			sfs32[2] = -sinY * sfs32[0];
			sfs32[0] = cosZ * cosYscaleX;
			sfs32[4] = cosZsinY * sinXscaleY - sinZ * cosXscaleY;
			sfs32[8] = cosZsinY * cosXscaleZ + sinZ * sinXscaleZ;
			sfs32[5] = sinZsinY * sinXscaleY + cosZ * cosXscaleY;
			sfs32[9] = sinZsinY * cosXscaleZ - cosZ * sinXscaleZ;
			sfs32[6] = cosY * sinXscaleY;
			sfs32[10] = cosY * cosXscaleZ;
		}
		void Matrix4::setRotationEulerAngle2(VCG_Number cosX, VCG_Number sinX, VCG_Number cosY, VCG_Number sinY, VCG_Number cosZ, VCG_Number sinZ)
		{
			auto sfs32 = m_localFS32;
			auto cosZsinY = cosZ * sinY;
			auto sinZsinY = sinZ * sinY;
			auto cosYscaleX = cosY * sfs32[0];
			auto sinXscaleY = sinX * sfs32[5];
			auto cosXscaleY = cosX * sfs32[5];
			auto cosXscaleZ = cosX * sfs32[10];
			auto sinXscaleZ = sinX * sfs32[10];

			sfs32[1] = sinZ * cosYscaleX;
			sfs32[2] = -sinY * sfs32[0];
			sfs32[0] = cosZ * cosYscaleX;
			sfs32[4] = cosZsinY * sinXscaleY - sinZ * cosXscaleY;
			sfs32[8] = cosZsinY * cosXscaleZ + sinZ * sinXscaleZ;
			sfs32[5] = sinZsinY * sinXscaleY + cosZ * cosXscaleY;
			sfs32[9] = sinZsinY * cosXscaleZ - cosZ * sinXscaleZ;
			sfs32[6] = cosY * sinXscaleY;
			sfs32[10] = cosY * cosXscaleZ;
		}
		void Matrix4::setTranslationXYZ(VCG_Number px, VCG_Number py, VCG_Number pz)
		{
			m_localFS32[12] = px;
			m_localFS32[13] = py;
			m_localFS32[14] = pz;
		}
		void Matrix4::setTranslation(const Vec3D& v3)
		{
			m_localFS32[12] = v3.x;
			m_localFS32[13] = v3.y;
			m_localFS32[14] = v3.z;
		}
		void Matrix4::appendScaleXYZ(VCG_Number xScale, VCG_Number yScale, VCG_Number zScale)
		{
			auto sfs32 = m_localFS32;
			sfs32[0] *= xScale; sfs32[1] *= xScale; sfs32[2] *= xScale; sfs32[3] *= xScale;
			sfs32[4] *= yScale; sfs32[5] *= yScale; sfs32[6] *= yScale; sfs32[7] *= yScale;
			sfs32[8] *= zScale; sfs32[9] *= zScale; sfs32[10] *= zScale; sfs32[11] *= zScale;
		}
		void Matrix4::appendScaleXY(VCG_Number xScale, VCG_Number yScale)
		{
			m_localFS32[0] *= xScale; m_localFS32[1] *= xScale; m_localFS32[2] *= xScale; m_localFS32[3] *= xScale;
			m_localFS32[4] *= yScale; m_localFS32[5] *= yScale; m_localFS32[6] *= yScale; m_localFS32[7] *= yScale;
		}
		void Matrix4::appendTranslationXYZ(VCG_Number px, VCG_Number py, VCG_Number pz)
		{
			m_localFS32[12] += px;
			m_localFS32[13] += py;
			m_localFS32[14] += pz;
		}
		void Matrix4::appendTranslation(const Vec3D& v3)
		{
			m_localFS32[12] += v3.x;
			m_localFS32[13] += v3.y;
			m_localFS32[14] += v3.z;
		}
		void Matrix4::copyColumnFrom(unsigned int column_index, const Vec3D& v3)
		{
			switch (column_index) {
			case 0:
			{
				m_localFS32[0] = v3.x;
				m_localFS32[1] = v3.y;
				m_localFS32[2] = v3.z;
				m_localFS32[3] = v3.w;
			}
			break;
			case 1:
			{
				m_localFS32[4] = v3.x;
				m_localFS32[5] = v3.y;
				m_localFS32[6] = v3.z;
				m_localFS32[7] = v3.w;
			}
			break;
			case 2:
			{
				m_localFS32[8] = v3.x;
				m_localFS32[9] = v3.y;
				m_localFS32[10] = v3.z;
				m_localFS32[11] = v3.w;
			}
			break;
			case 3:
			{
				m_localFS32[12] = v3.x;
				m_localFS32[13] = v3.y;
				m_localFS32[14] = v3.z;
				m_localFS32[15] = v3.w;
			}
			break;
			default:
				break;
			}
		}
		void Matrix4::copyColumnTo(unsigned int column_index, Vec3D& v3)
		{
			column_index <<= 2;
			v3.x = m_localFS32[column_index];
			v3.y = m_localFS32[1 + column_index];
			v3.z = m_localFS32[2 + column_index];
			v3.w = m_localFS32[3 + column_index];
		}
		void Matrix4::setF32ArrAndIndex(VCG_Number* fs32Arr, unsigned int index)
		{
			if (fs32Arr != nullptr)
			{
				m_fs32 = fs32Arr;
				m_index = index;
				m_localFS32 = m_fs32 + index;
			}
		}
		void Matrix4::setF32ArrIndex(unsigned int index)
		{
			m_index = index;
			m_localFS32 = m_fs32 + index;
		}
		void Matrix4::setF32Arr(VCG_Number* fs32Arr)
		{
			if (fs32Arr != nullptr)
			{
				m_fs32 = fs32Arr;
			}
		}
		void Matrix4::copyFromF32Arr(VCG_Number* fs32Arr, unsigned int index)
		{
			std::memcpy(m_localFS32, fs32Arr + index, VCG_MATRIX4_DATA_SIZE);
		}
		void Matrix4::copyToF32Arr(VCG_Number* fs32Arr, unsigned int index)
		{
			std::memcpy(fs32Arr + index, m_localFS32, VCG_MATRIX4_DATA_SIZE);
		}
		void Matrix4::copyFrom(const Matrix4& mat_other)
		{
			std::memcpy(m_localFS32, mat_other.getLocalFS32(), VCG_MATRIX4_DATA_SIZE);
		}

		void Matrix4::copyRawDataFrom(VCG_Number* float_rawDataArr, unsigned int rawDataLength, unsigned int index, bool bool_tp)
		{
			if (bool_tp) transpose();
			rawDataLength = rawDataLength - index;
			unsigned int c = 0;
			while (c < rawDataLength)
			{
				m_fs32[m_index + c] = float_rawDataArr[c + index];
				++c;
			}
			if (bool_tp) transpose();
		}
		void Matrix4::copyRawDataTo(VCG_Number* float_rawDataArr, unsigned int rawDataLength, unsigned int index, bool bool_tp)
		{
			if (bool_tp) transpose();
			unsigned int c = 0;
			while (c < rawDataLength)
			{
				float_rawDataArr[c + index] = m_fs32[m_index + c];
				++c;
			}
			if (bool_tp) transpose();
		}
		void Matrix4::copyRowFrom(unsigned int row_index, const Vec3D& v3)
		{
			switch (row_index) {
			case 0:
			{
				m_localFS32[0] = v3.x;
				m_localFS32[4] = v3.y;
				m_localFS32[8] = v3.z;
				m_localFS32[12] = v3.w;
			}
			break;
			case 1:
			{
				m_localFS32[1] = v3.x;
				m_localFS32[5] = v3.y;
				m_localFS32[9] = v3.z;
				m_localFS32[13] = v3.w;
			}
			break;
			case 2:
			{
				m_localFS32[2] = v3.x;
				m_localFS32[6] = v3.y;
				m_localFS32[10] = v3.z;
				m_localFS32[14] = v3.w;
			}
			break;
			case 3:
			{
				m_localFS32[3] = v3.x;
				m_localFS32[7] = v3.y;
				m_localFS32[11] = v3.z;
				m_localFS32[15] = v3.w;
			}
			break;
			default:
				break;
			}
		}
		void Matrix4::copyRowTo(unsigned int row_index, Vec3D& v3)
		{
			v3.x = m_localFS32[row_index];
			v3.y = m_localFS32[4 + row_index];
			v3.z = m_localFS32[8 + row_index];
			v3.w = m_localFS32[12 + row_index];
		}
		void Matrix4::decompose(unsigned int orientationStyle, Vec3D(&outvecs)[3])
		{
			// TODO: optimize after 4 lines
			auto& vec = outvecs;
			auto& mr = Matrix4::s_tmat4;
			auto mrfs32 = mr.getFS32();

			mr.copyFrom(*this);

			auto& pos = vec[0];
			auto& rot = vec[1];
			auto& scale = vec[2];
			pos.setXYZ(mrfs32[12], mrfs32[13], mrfs32[14]);
			scale.x = std::sqrt(mrfs32[0] * mrfs32[0] + mrfs32[1] * mrfs32[1] + mrfs32[2] * mrfs32[2]);
			scale.y = std::sqrt(mrfs32[4] * mrfs32[4] + mrfs32[5] * mrfs32[5] + mrfs32[6] * mrfs32[6]);
			scale.z = std::sqrt(mrfs32[8] * mrfs32[8] + mrfs32[9] * mrfs32[9] + mrfs32[10] * mrfs32[10]);
			if (mrfs32[0] * (mrfs32[5] * mrfs32[10] - mrfs32[6] * mrfs32[9]) - mrfs32[1] * (mrfs32[4] * mrfs32[10] - mrfs32[6] * mrfs32[8]) + mrfs32[2] * (mrfs32[4] * mrfs32[9] - mrfs32[5] * mrfs32[8]) < 0) scale.z = -scale.z;
			mrfs32[0] /= scale.x;
			mrfs32[1] /= scale.x;
			mrfs32[2] /= scale.x;
			mrfs32[4] /= scale.y;
			mrfs32[5] /= scale.y;
			mrfs32[6] /= scale.y;
			mrfs32[8] /= scale.z;
			mrfs32[9] /= scale.z;
			mrfs32[10] /= scale.z;

			switch (orientationStyle) {
			case OrientationType::AXIS_ANGLE:
			{
				rot.w = SafeACos((mrfs32[0] + mrfs32[5] + mrfs32[10] - 1) / 2);
				auto len = std::sqrt((mrfs32[6] - mrfs32[9]) * (mrfs32[6] - mrfs32[9]) + (mrfs32[8] - mrfs32[2]) * (mrfs32[8] - mrfs32[2]) + (mrfs32[1] - mrfs32[4]) * (mrfs32[1] - mrfs32[4]));
				if (len > VCG_MATH_MIN_POSITIVE) {
					rot.x = (mrfs32[6] - mrfs32[9]) / len;
					rot.y = (mrfs32[8] - mrfs32[2]) / len;
					rot.z = (mrfs32[1] - mrfs32[4]) / len;
				}
				else rot.x = rot.y = rot.z = 0.0f;
			}
			break;
			case OrientationType::QUATERNION:
			{
				auto tr = (mrfs32[0] + mrfs32[5] + mrfs32[10]);
				if (tr > 0) {
					rot.w = std::sqrt(1.0f + tr) * 0.5f;
					rot.x = (mrfs32[6] - mrfs32[9]) / (4.0f * rot.w);
					rot.y = (mrfs32[8] - mrfs32[2]) / (4.0f * rot.w);
					rot.z = (mrfs32[1] - mrfs32[4]) / (4.0f * rot.w);
				}
				else if (mrfs32[0] > mrfs32[5] && mrfs32[0] > mrfs32[10]) {
					rot.x = std::sqrt(1.0f + mrfs32[0] - mrfs32[5] - mrfs32[10]) * 0.5f;
					rot.w = (mrfs32[6] - mrfs32[9]) / (4.0f * rot.x);
					rot.y = (mrfs32[1] + mrfs32[4]) / (4.0f * rot.x);
					rot.z = (mrfs32[8] + mrfs32[2]) / (4.0f * rot.x);
				}
				else if (mrfs32[5] > mrfs32[10]) {
					rot.y = std::sqrt(1.0f + mrfs32[5] - mrfs32[0] - mrfs32[10]) * 0.5f;
					rot.x = (mrfs32[1] + mrfs32[4]) / (4.0f * rot.y);
					rot.w = (mrfs32[8] - mrfs32[2]) / (4.0f * rot.y);
					rot.z = (mrfs32[6] + mrfs32[9]) / (4.0f * rot.y);
				}
				else
				{
					rot.z = std::sqrt(1.0f + mrfs32[10] - mrfs32[0] - mrfs32[5]) * 0.5f;
					rot.x = (mrfs32[8] + mrfs32[2]) / (4.0f * rot.z);
					rot.y = (mrfs32[6] + mrfs32[9]) / (4.0f * rot.z);
					rot.w = (mrfs32[1] - mrfs32[4]) / (4.0f * rot.z);
				}
			}
			break;
			case OrientationType::EULER_ANGLES:
			{
				rot.y = std::asin(-mrfs32[2]);
				if (mrfs32[2] != 1 && mrfs32[2] != -1) {
					rot.x = std::atan2(mrfs32[6], mrfs32[10]);
					rot.z = std::atan2(mrfs32[1], mrfs32[0]);
				}
				else {
					rot.z = 0;
					rot.x = std::atan2(mrfs32[4], mrfs32[5]);
				}
			}
			break;
			default:
				break;
			};
		}
		bool Matrix4::invert()
		{
			auto d = determinant();
			auto invertable = std::abs(d) > VCG_MATH_MIN_POSITIVE;
			if (invertable)
			{
				auto sfs32 = m_localFS32;
				d = 1.0 / d;
				auto& m11 = sfs32[0];
				auto& m21 = sfs32[4];
				auto& m31 = sfs32[8];
				auto& m41 = sfs32[12];
				auto& m12 = sfs32[1];
				auto& m22 = sfs32[5];
				auto& m32 = sfs32[9];
				auto& m42 = sfs32[13];
				auto& m13 = sfs32[2];
				auto& m23 = sfs32[6];
				auto& m33 = sfs32[10];
				auto& m43 = sfs32[14];
				auto& m14 = sfs32[3];
				auto& m24 = sfs32[7];
				auto& m34 = sfs32[11];
				auto& m44 = sfs32[15];
				sfs32[0] = d * (m22 * (m33 * m44 - m43 * m34) - m32 * (m23 * m44 - m43 * m24) + m42 * (m23 * m34 - m33 * m24));
				sfs32[1] = -d * (m12 * (m33 * m44 - m43 * m34) - m32 * (m13 * m44 - m43 * m14) + m42 * (m13 * m34 - m33 * m14));
				sfs32[2] = d * (m12 * (m23 * m44 - m43 * m24) - m22 * (m13 * m44 - m43 * m14) + m42 * (m13 * m24 - m23 * m14));
				sfs32[3] = -d * (m12 * (m23 * m34 - m33 * m24) - m22 * (m13 * m34 - m33 * m14) + m32 * (m13 * m24 - m23 * m14));
				sfs32[4] = -d * (m21 * (m33 * m44 - m43 * m34) - m31 * (m23 * m44 - m43 * m24) + m41 * (m23 * m34 - m33 * m24));
				sfs32[5] = d * (m11 * (m33 * m44 - m43 * m34) - m31 * (m13 * m44 - m43 * m14) + m41 * (m13 * m34 - m33 * m14));
				sfs32[6] = -d * (m11 * (m23 * m44 - m43 * m24) - m21 * (m13 * m44 - m43 * m14) + m41 * (m13 * m24 - m23 * m14));
				sfs32[7] = d * (m11 * (m23 * m34 - m33 * m24) - m21 * (m13 * m34 - m33 * m14) + m31 * (m13 * m24 - m23 * m14));
				sfs32[8] = d * (m21 * (m32 * m44 - m42 * m34) - m31 * (m22 * m44 - m42 * m24) + m41 * (m22 * m34 - m32 * m24));
				sfs32[9] = -d * (m11 * (m32 * m44 - m42 * m34) - m31 * (m12 * m44 - m42 * m14) + m41 * (m12 * m34 - m32 * m14));
				sfs32[10] = d * (m11 * (m22 * m44 - m42 * m24) - m21 * (m12 * m44 - m42 * m14) + m41 * (m12 * m24 - m22 * m14));
				sfs32[11] = -d * (m11 * (m22 * m34 - m32 * m24) - m21 * (m12 * m34 - m32 * m14) + m31 * (m12 * m24 - m22 * m14));
				sfs32[12] = -d * (m21 * (m32 * m43 - m42 * m33) - m31 * (m22 * m43 - m42 * m23) + m41 * (m22 * m33 - m32 * m23));
				sfs32[13] = d * (m11 * (m32 * m43 - m42 * m33) - m31 * (m12 * m43 - m42 * m13) + m41 * (m12 * m33 - m32 * m13));
				sfs32[14] = -d * (m11 * (m22 * m43 - m42 * m23) - m21 * (m12 * m43 - m42 * m13) + m41 * (m12 * m23 - m22 * m13));
				sfs32[15] = d * (m11 * (m22 * m33 - m32 * m23) - m21 * (m12 * m33 - m32 * m13) + m31 * (m12 * m23 - m22 * m13));
			};
			return invertable;
		}
		void Matrix4::pointAt(const Vec3D& pos, const Vec3D& at, const Vec3D& up)
		{
			//TODO: need optimize
			//	if (at == nullptr || at == nullptr) at = new Vec3D(0.0f, 0.0f, -1.0f);
			//	if (up == nullptr || up == nullptr) up = new Vec3D(0.0f, -1.0f, 0.0f);
			auto&& dir = at.subtract(pos);
			Vec3D vup(up.x, up.y, up.z);//up->clone();
			//Vector3D right;
			dir.normalize();
			vup.normalize();
			Vec3D dir2(dir.x, dir.y, dir.z);
			dir2.scaleBy(vup.dot(dir));
			//
			vup.subtractBy(dir2);
			if (vup.getLength() > VCG_MATH_MIN_POSITIVE) vup.normalize();
			else if (dir.x != 0)vup.setXYZ(-dir.y, dir.x, 0.0f);
			else vup.setXYZ(1.0f, 0.0f, 0.0f);
			auto&& right = vup.crossProduct(dir);
			right.normalize();
			auto sfs32 = m_localFS32;
			sfs32[0] = right.x;
			sfs32[4] = right.y;
			sfs32[8] = right.z;
			sfs32[12] = 0.0f;
			sfs32[1] = vup.x;
			sfs32[5] = vup.y;
			sfs32[9] = vup.z;
			sfs32[13] = 0.0f;
			sfs32[2] = dir.x;
			sfs32[6] = dir.y;
			sfs32[10] = dir.z;
			sfs32[14] = 0.0f;
			sfs32[3] = pos.x;
			sfs32[7] = pos.y;
			sfs32[11] = pos.z;
			sfs32[15] = 1.0f;
		}
		void Matrix4::prepend(const Matrix4& rhs)
		{
			auto rfs32 = rhs.getLocalFS32();
			auto sfs32 = m_localFS32;

			auto m111 = rfs32[0];
			auto m121 = rfs32[4];
			auto m131 = rfs32[8];
			auto m141 = rfs32[12];
			auto m112 = rfs32[1];
			auto m122 = rfs32[5];
			auto m132 = rfs32[9];
			auto m142 = rfs32[13];
			auto m113 = rfs32[2];
			auto m123 = rfs32[6];
			auto m133 = rfs32[10];
			auto m143 = rfs32[14];
			auto m114 = rfs32[3];
			auto m124 = rfs32[7];
			auto m134 = rfs32[11];
			auto m144 = rfs32[15];
			auto m211 = sfs32[0];
			auto m221 = sfs32[4];
			auto m231 = sfs32[8];
			auto m241 = sfs32[12];
			auto m212 = sfs32[1];
			auto m222 = sfs32[5];
			auto m232 = sfs32[9];
			auto m242 = sfs32[13];
			auto m213 = sfs32[2];
			auto m223 = sfs32[6];
			auto m233 = sfs32[10];
			auto m243 = sfs32[14];
			auto m214 = sfs32[3];
			auto m224 = sfs32[7];
			auto m234 = sfs32[11];
			auto m244 = sfs32[15];
			sfs32[0] = m111 * m211 + m112 * m221 + m113 * m231 + m114 * m241;
			sfs32[1] = m111 * m212 + m112 * m222 + m113 * m232 + m114 * m242;
			sfs32[2] = m111 * m213 + m112 * m223 + m113 * m233 + m114 * m243;
			sfs32[3] = m111 * m214 + m112 * m224 + m113 * m234 + m114 * m244;
			sfs32[4] = m121 * m211 + m122 * m221 + m123 * m231 + m124 * m241;
			sfs32[5] = m121 * m212 + m122 * m222 + m123 * m232 + m124 * m242;
			sfs32[6] = m121 * m213 + m122 * m223 + m123 * m233 + m124 * m243;
			sfs32[7] = m121 * m214 + m122 * m224 + m123 * m234 + m124 * m244;
			sfs32[8] = m131 * m211 + m132 * m221 + m133 * m231 + m134 * m241;
			sfs32[9] = m131 * m212 + m132 * m222 + m133 * m232 + m134 * m242;
			sfs32[10] = m131 * m213 + m132 * m223 + m133 * m233 + m134 * m243;
			sfs32[11] = m131 * m214 + m132 * m224 + m133 * m234 + m134 * m244;
			sfs32[12] = m141 * m211 + m142 * m221 + m143 * m231 + m144 * m241;
			sfs32[13] = m141 * m212 + m142 * m222 + m143 * m232 + m144 * m242;
			sfs32[14] = m141 * m213 + m142 * m223 + m143 * m233 + m144 * m243;
			sfs32[15] = m141 * m214 + m142 * m224 + m143 * m234 + m144 * m244;
		}
		void Matrix4::prepend3x3(const Matrix4& rhs)
		{
			auto rfs32 = rhs.getLocalFS32();
			auto sfs32 = m_localFS32;

			auto m111 = rfs32[0];
			auto m121 = rfs32[4];
			auto m131 = rfs32[8];
			auto m112 = rfs32[1];
			auto m122 = rfs32[5];
			auto m132 = rfs32[9];
			auto m113 = rfs32[2];
			auto m123 = rfs32[6];
			auto m133 = rfs32[10];
			auto m211 = sfs32[0];
			auto m221 = sfs32[4];
			auto m231 = sfs32[8];
			auto m212 = sfs32[1];
			auto m222 = sfs32[5];
			auto m232 = sfs32[9];
			auto m213 = sfs32[2];
			auto m223 = sfs32[6];
			auto m233 = sfs32[10];

			sfs32[0] = m111 * m211 + m112 * m221 + m113 * m231;
			sfs32[1] = m111 * m212 + m112 * m222 + m113 * m232;
			sfs32[2] = m111 * m213 + m112 * m223 + m113 * m233;
			sfs32[4] = m121 * m211 + m122 * m221 + m123 * m231;
			sfs32[5] = m121 * m212 + m122 * m222 + m123 * m232;
			sfs32[6] = m121 * m213 + m122 * m223 + m123 * m233;
			sfs32[8] = m131 * m211 + m132 * m221 + m133 * m231;
			sfs32[9] = m131 * m212 + m132 * m222 + m133 * m232;
			sfs32[10] = m131 * m213 + m132 * m223 + m133 * m233;
		}
		void Matrix4::prependRotationPivot(VCG_Number radian, const Vec3D& axis, const Vec3D& pivotPoint)
		{
			Matrix4::s_tmat4.identity();
			Matrix4::s_tmat4.getAxisRotation(axis.x, axis.y, axis.z, radian);
			Matrix4::s_tmat4.appendTranslationXYZ(pivotPoint.x, pivotPoint.y, pivotPoint.z);
			prepend(Matrix4::s_tmat4);
		}
		void Matrix4::prependRotation(VCG_Number radian, const Vec3D& axis)
		{
			Matrix4::s_tmat4.identity();
			Matrix4::s_tmat4.getAxisRotation(axis.x, axis.y, axis.z, radian);
			prepend(Matrix4::s_tmat4);
		}
		void Matrix4::prependRotationX(VCG_Number radian)
		{
			//s_tempMat.identity();
			Matrix4::s_tmat4.rotationX(radian);
			prepend3x3(Matrix4::s_tmat4);
		}
		void Matrix4::prependRotationY(VCG_Number radian)
		{
			//s_tempMat.identity();
			Matrix4::s_tmat4.rotationY(radian);
			prepend3x3(Matrix4::s_tmat4);
		}
		void Matrix4::prependRotationZ(VCG_Number radian)
		{
			//s_tempMat.identity();
			Matrix4::s_tmat4.rotationZ(radian);
			prepend3x3(Matrix4::s_tmat4);
		}
		// 用欧拉角形式旋转(heading->pitch->bank) => (y->x->z)
		void Matrix4::prependRotationEulerAngle(VCG_Number radianX, VCG_Number radianY, VCG_Number radianZ)
		{
			//s_tempMat.identity();
			Matrix4::s_tmat4.rotationY(radianY);
			prepend3x3(Matrix4::s_tmat4);
			//s_tempMat.identity();
			Matrix4::s_tmat4.rotationX(radianX);
			prepend3x3(Matrix4::s_tmat4);
			//s_tempMat.identity();
			Matrix4::s_tmat4.rotationZ(radianZ);
			prepend3x3(Matrix4::s_tmat4);
		}
		void Matrix4::prependScale(VCG_Number xScale, VCG_Number yScale, VCG_Number zScale)
		{
			auto sfs32 = m_localFS32;
			sfs32[0] *= xScale; sfs32[1] *= yScale; sfs32[2] *= zScale;
			sfs32[4] *= xScale; sfs32[5] *= yScale; sfs32[6] *= zScale;
			sfs32[8] *= xScale; sfs32[9] *= yScale; sfs32[10] *= zScale;
			sfs32[12] *= xScale; sfs32[13] *= yScale; sfs32[14] *= zScale;
		}
		void Matrix4::prependScaleXY(VCG_Number xScale, VCG_Number yScale)
		{
			m_localFS32[0] *= xScale; m_localFS32[1] *= yScale;
			m_localFS32[4] *= xScale; m_localFS32[5] *= yScale;
			m_localFS32[8] *= xScale; m_localFS32[9] *= yScale;
			m_localFS32[12] *= xScale; m_localFS32[13] *= yScale;
		}
		void Matrix4::prependTranslationXYZ(VCG_Number px, VCG_Number py, VCG_Number pz)
		{
			Matrix4::s_tmat4.identity();
			//Matrix4::s_tmat4.setPositionXYZ(px, py, pz);
			prepend(Matrix4::s_tmat4);
		}
		void Matrix4::prependTranslation(const Vec3D& v3)
		{
			Matrix4::s_tmat4.identity();
			//Matrix4::s_tmat4.setPositionXYZ(v3.x, v3.y, v3.z);
			prepend(Matrix4::s_tmat4);
		}
		bool Matrix4::recompose(Vec3D(&components)[3], unsigned int orientationStyle)
		{
			if (components[2].x == 0.0f || components[2].y == 0.0f || components[2].z == 0.0f) return false;
			identity();
			auto scale = Matrix4::s_tmat4.getFS32();
			scale[0] = scale[1] = scale[2] = components[2].x;
			scale[4] = scale[5] = scale[6] = components[2].y;
			scale[8] = scale[9] = scale[10] = components[2].z;
			auto sfs32 = m_localFS32;
			switch (orientationStyle) {
			case OrientationType::EULER_ANGLES:
			{
				auto cx = std::cos(components[1].x);
				auto cy = std::cos(components[1].y);
				auto cz = std::cos(components[1].z);
				auto sx = std::sin(components[1].x);
				auto sy = std::sin(components[1].y);
				auto sz = std::sin(components[1].z);
				sfs32[0] = cy * cz * scale[0];
				sfs32[1] = cy * sz * scale[1];
				sfs32[2] = -sy * scale[2];
				sfs32[3] = 0.0f;
				sfs32[4] = (sx * sy * cz - cx * sz) * scale[4];
				sfs32[5] = (sx * sy * sz + cx * cz) * scale[5];
				sfs32[6] = sx * cy * scale[6];
				sfs32[7] = 0.0f;
				sfs32[8] = (cx * sy * cz + sx * sz) * scale[8];
				sfs32[9] = (cx * sy * sz - sx * cz) * scale[9];
				sfs32[10] = cx * cy * scale[10];
				sfs32[11] = 0.0f;
				sfs32[12] = components[0].x;
				sfs32[13] = components[0].y;
				sfs32[14] = components[0].z;
				sfs32[15] = 1.0f;
			}
			break;
			default:
			{
				auto x = components[1].x;
				auto y = components[1].y;
				auto z = components[1].z;
				auto w = components[1].w;
				if (orientationStyle == OrientationType::AXIS_ANGLE) {
					auto halfW = 0.5f * w;
					x *= std::sin(halfW);
					y *= std::sin(halfW);
					z *= std::sin(halfW);
					w = std::cos(halfW);
				};
				sfs32[0] = (1.0 - 2.0 * y * y - 2.0 * z * z) * scale[0];
				sfs32[1] = (2.0 * x * y + 2.0 * w * z) * scale[1];
				sfs32[2] = (2.0 * x * z - 2.0 * w * y) * scale[2];
				sfs32[3] = 0.0f;
				sfs32[4] = (2.0 * x * y - 2.0 * w * z) * scale[4];
				sfs32[5] = (1.0 - 2.0 * x * x - 2.0 * z * z) * scale[5];
				sfs32[6] = (2.0 * y * z + 2.0 * w * x) * scale[6];
				sfs32[7] = 0.0f;
				sfs32[8] = (2.0 * x * z + 2.0 * w * y) * scale[8];
				sfs32[9] = (2.0 * y * z - 2.0 * w * x) * scale[9];
				sfs32[10] = (1.0 - 2.0 * x * x - 2.0 * y * y) * scale[10];
				sfs32[11] = 0.0f;
				sfs32[12] = components[0].x;
				sfs32[13] = components[0].y;
				sfs32[14] = components[0].z;
				sfs32[15] = 1.0f;
			}
			break;
			};
			//TODO: need thinking
			if (components[2].x == 0.0f)m_localFS32[0] = 0.0f;// 1e-15f;
			if (components[2].y == 0.0f)m_localFS32[5] = 0.0f;// 1e-15f;
			if (components[2].z == 0.0f)m_localFS32[10] = 0.0f;// 1e-15f;
			scale = nullptr;
			return true;
		}
		Vec3D Matrix4::deltaTransformVector(const Vec3D& v3)
		{
			auto x = v3.x;
			auto y = v3.y;
			auto z = v3.z;
			return Vec3D(
				x * m_localFS32[0] + y * m_localFS32[4] + z * m_localFS32[8]
				, x * m_localFS32[1] + y * m_localFS32[5] + z * m_localFS32[9]
				, x * m_localFS32[2] + y * m_localFS32[6] + z * m_localFS32[10]
				, 0.0f);
		}
		void Matrix4::deltaTransformVectorSelf(Vec3D& v3)
		{
			auto sfs32 = m_localFS32;
			auto x = v3.x;
			auto y = v3.y;
			auto z = v3.z;
			v3.x = x * sfs32[0] + y * sfs32[4] + z * sfs32[8];
			v3.y = x * sfs32[1] + y * sfs32[5] + z * sfs32[9];
			v3.z = x * sfs32[2] + y * sfs32[6] + z * sfs32[10];
		}
		void Matrix4::deltaTransformOutVector(const Vec3D& v3, Vec3D& out_v3)
		{
			auto sfs32 = m_localFS32;
			out_v3.x = v3.x * sfs32[0] + v3.y * sfs32[4] + v3.z * sfs32[8];
			out_v3.y = v3.x * sfs32[1] + v3.y * sfs32[5] + v3.z * sfs32[9];
			out_v3.z = v3.x * sfs32[2] + v3.y * sfs32[6] + v3.z * sfs32[10];
		}
		Vec3D Matrix4::transformVector(const Vec3D& v3)
		{
			auto sfs32 = m_localFS32;
			auto x = v3.x;
			auto y = v3.y;
			auto z = v3.z;
			return Vec3D(
				x * sfs32[0] + y * sfs32[4] + z * sfs32[8] + sfs32[12]
				, x * sfs32[1] + y * sfs32[5] + z * sfs32[9] + sfs32[13]
				, x * sfs32[2] + y * sfs32[6] + z * sfs32[10] + sfs32[14]
				, x * sfs32[3] + y * sfs32[7] + z * sfs32[11] + sfs32[15]
			);
		}
		void Matrix4::transformOutVector(const Vec3D& v3, Vec3D& out_v3)
		{
			auto x = v3.x;
			auto y = v3.y;
			auto z = v3.z;
			auto sfs32 = m_localFS32;
			out_v3.setXYZW(
				x * sfs32[0] + y * sfs32[4] + z * sfs32[8] + sfs32[12]
				, x * sfs32[1] + y * sfs32[5] + z * sfs32[9] + sfs32[13]
				, x * sfs32[2] + y * sfs32[6] + z * sfs32[10] + sfs32[14]
				, x * sfs32[3] + y * sfs32[7] + z * sfs32[11] + sfs32[15]
			);
		}
		void Matrix4::transformOutVector3(const Vec3D& v3, Vec3D& out_v3)
		{
			auto sfs32 = m_localFS32;
			out_v3.x = v3.x * sfs32[0] + v3.y * sfs32[4] + v3.z * sfs32[8] + sfs32[12];
			out_v3.y = v3.x * sfs32[1] + v3.y * sfs32[5] + v3.z * sfs32[9] + sfs32[13];
			out_v3.z = v3.x * sfs32[2] + v3.y * sfs32[6] + v3.z * sfs32[10] + sfs32[14];
		}
		void Matrix4::transformVector3Self(Vec3D& v3)
		{
			auto x = v3.x;
			auto y = v3.y;
			auto z = v3.z;
			auto sfs32 = m_localFS32;
			v3.x = x * sfs32[0] + y * sfs32[4] + z * sfs32[8] + sfs32[12];
			v3.y = x * sfs32[1] + y * sfs32[5] + z * sfs32[9] + sfs32[13];
			v3.z = x * sfs32[2] + y * sfs32[6] + z * sfs32[10] + sfs32[14];
		}
		void Matrix4::transformVectorSelf(Vec3D& v3)
		{
			auto x = v3.x;
			auto y = v3.y;
			auto z = v3.z;
			auto sfs32 = m_localFS32;
			v3.setXYZW(
				x * sfs32[0] + y * sfs32[4] + z * sfs32[8] + sfs32[12],
				x * sfs32[1] + y * sfs32[5] + z * sfs32[9] + sfs32[13],
				x * sfs32[2] + y * sfs32[6] + z * sfs32[10] + sfs32[14],
				x * sfs32[3] + y * sfs32[7] + z * sfs32[11] + sfs32[15]
			);
		}
		void Matrix4::transformVectors(VCG_Number* float_vinArr, unsigned int vinLength, VCG_Number* float_voutArr)
		{
			auto i = 0;
			auto x = float_vinArr[0], y = float_vinArr[0], z = float_vinArr[0];
			auto pfs = m_localFS32;
			while ((i + 3) <= vinLength) {
				x = float_vinArr[i];
				y = float_vinArr[i + 1];
				z = float_vinArr[i + 2];
				float_voutArr[i] = x * pfs[0] + y * pfs[4] + z * pfs[8] + pfs[12];
				float_voutArr[i + 1] = x * pfs[1] + y * pfs[5] + z * pfs[9] + pfs[13];
				float_voutArr[i + 2] = x * pfs[2] + y * pfs[6] + z * pfs[10] + pfs[14];
				i += 3;
			}
		}
		void Matrix4::transpose()
		{
			Matrix4::s_tmat4.copyFrom(*this);
			auto fs32 = Matrix4::s_tmat4.getFS32();
			auto sfs32 = m_localFS32;
			sfs32[1] = fs32[4];
			sfs32[2] = fs32[8];
			sfs32[3] = fs32[12];
			sfs32[4] = fs32[1];
			sfs32[6] = fs32[9];
			sfs32[7] = fs32[13];
			sfs32[8] = fs32[2];
			sfs32[9] = fs32[6];
			sfs32[11] = fs32[14];
			sfs32[12] = fs32[3];
			sfs32[13] = fs32[7];
			sfs32[14] = fs32[11];
		}

		void Matrix4::interpolateTo(Matrix4& toMat, VCG_Number float_percent)
		{
			auto fs32 = toMat.getFS32();
			auto fsI = toMat.getFSIndex();
			auto _g = 0;
			auto i = m_index;
			while (_g < 16)
			{
				m_fs32[i] += (fs32[fsI + _g] - m_fs32[i]) * float_percent;
				++i;
				++_g;
			}
		}
		void Matrix4::rotationX(VCG_Number radian)
		{
			auto s = std::sin(radian), c = std::cos(radian);
			m_localFS32[0] = 1.0; m_localFS32[1] = 0.0; m_localFS32[2] = 0.0;
			m_localFS32[4] = 0.0; m_localFS32[5] = c; m_localFS32[6] = s;
			m_localFS32[8] = 0.0; m_localFS32[9] = -s; m_localFS32[10] = c;
		}
		void Matrix4::rotationY(VCG_Number radian)
		{
			auto s = std::sin(radian);
			auto c = std::cos(radian);
			m_localFS32[0] = c; m_localFS32[1] = 0.0f; m_localFS32[2] = -s;
			m_localFS32[4] = 0.0f; m_localFS32[5] = 1.0f; m_localFS32[6] = 0.0f;
			m_localFS32[8] = s; m_localFS32[9] = 0.0f; m_localFS32[10] = c;
		}
		void Matrix4::rotationZ(VCG_Number radian)
		{
			auto s = std::sin(radian), c = std::cos(radian);
			m_localFS32[0] = c; m_localFS32[1] = s; m_localFS32[2] = 0.0f;
			m_localFS32[4] = -s; m_localFS32[5] = c; m_localFS32[6] = 0.0f;
			m_localFS32[8] = 0.0f; m_localFS32[9] = 0.0f; m_localFS32[10] = 1.0f;
		}

		void Matrix4::transformPerspV4Self(Vec3D& v4)
		{

		}
		void Matrix4::destroy()
		{
			if (m_localFS32 != nullptr)
			{
				if (m_type < 1)
				{
					delete[] m_fs32;
				}
				m_type = -1;
				m_localFS32 = nullptr;
				m_fs32 = nullptr;
				m_index = -1;
			}
		}

		void Matrix4::coutThis()
		{
			std::cout << "\n" << m_localFS32[0] << "," << m_localFS32[1] << "," << m_localFS32[2] << "," << m_localFS32[3]<<"\n"
			<< m_localFS32[4]<<"," << m_localFS32[5]<<"," << m_localFS32[6]<<"," << m_localFS32[7]<<"\n"
			<< m_localFS32[8]<<"," << m_localFS32[9]<<"," << m_localFS32[10] << "," << m_localFS32[11]<<"\n"
			<< m_localFS32[12] << "," << m_localFS32[13] << "," << m_localFS32[14] << "," << m_localFS32[15]<<"\n";
		}
	}
}