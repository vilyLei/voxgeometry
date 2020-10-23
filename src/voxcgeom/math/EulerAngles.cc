
#include <cmath>
#include "EulerAngles.h"
#include "Quaternion.h"
namespace voxcgeom
{
	namespace math
	{
		/**
			将角度的弧度值限制在 -pi 到 pi 之间
			@param			rad_theta		弧度值
			*/
		VCG_Number wrapPi(VCG_Number rad_theta)
		{
			rad_theta += VCG_MATH_PI;
			rad_theta -= floor(rad_theta * VCG_MATH_PI_OVER_2) * VCG_MATH_2PI;
			rad_theta -= VCG_MATH_PI;
			return rad_theta;
		}

		EulerAngles::EulerAngles()
			: heading(0.0f), pitch(0.0f), bank(0.0f)
		{
		}
		EulerAngles::EulerAngles(VCG_Number h, VCG_Number p, VCG_Number b) :heading(h), pitch(p), bank(b)
		{
		}
		const EulerAngles kEulerAnglersIdentity(0.0f, 0.0f, 0.0f);
		/**
		将euler angle转换到限制集中
		@returen		限制集中的euler angle值
		*/
		void EulerAngles::canonize()
		{
			pitch = wrapPi(pitch);
			// 将 pitch 转换到 -pi/2 到 pi/2中
			if (pitch < -VCG_MATH_PI_OVER_2)
			{
				pitch = -VCG_MATH_PI - pitch;
				heading += VCG_MATH_PI;
				bank += VCG_MATH_PI;
			}
			else if (pitch > VCG_MATH_PI_OVER_2)
			{
				pitch = VCG_MATH_PI - pitch;
				heading += VCG_MATH_PI;
				bank += VCG_MATH_PI;
			}
			// 检查 万向锁, 允许存在一定的误差
			if (abs(pitch) > VCG_MATH_PI_OVER_2 - 1e-4)
			{
				// 在万向锁中, 将所有绕垂直轴的旋转赋给heading
				heading += bank;
				bank = 0.0f;
			}
			else
			{
				// 非万向锁,将bank转换到限制集中
				bank = wrapPi(bank);
			}
			// 将heading转换到限制集中
			heading = wrapPi(heading);
		}
		/////////////////////////////////////////////////////
		//
		//从物体--惯性四元数到欧拉角
		//
		/////////////////////////////////////////////////////
		void EulerAngles::fromObjectToInertialQuaternion(const Quaternion &q)
		{
			// 计算 sin(pitch)
			VCG_Number sp = -2.0f * (q.y * q.z - q.w*q.x);
			// 检查万象锁，允许存在一定误差
			if (fabs(sp) > 0.9999f)
			{
				// 向正上方或正下方看
				pitch = VCG_MATH_PI_OVER_2 * sp;
				// bank置0,计算heading
				heading = atan2(-q.x*q.z + q.w*q.y,0.5f-q.y*q.y-q.z*q.z);
				bank = 0.0f;
			}
			else
			{
				//计算角度, 不必使用 safe asin,因为前面万象锁检查已经保证safe咯
				pitch = asin(sp);
				heading = atan2(q.x*q.z + q.w*q.y, 0.5f - q.x*q.x - q.y*q.y);
				bank = atan2(q.x*q.y + q.w*q.z, 0.5f - q.x*q.x - q.z*q.z);
			}
		}
		// 从惯性 -- 物体四元数到欧拉角
		void EulerAngles::fromInertialToObjectQuaternion(const Quaternion &q)
		{
			// 计算 sin(pitch)
			VCG_Number sp = -2.0f * (q.y * q.z + q.w*q.x);
			// 检查万象锁，允许存在一定误差
			if (fabs(sp) > 0.9999f)
			{
				// 向正上方或正下方看
				pitch = VCG_MATH_PI_OVER_2 * sp;
				// bank置0,计算heading
				heading = atan2(-q.x*q.z - q.w*q.y, 0.5f - q.y*q.y - q.z*q.z);
				bank = 0.0f;
			}
			else
			{
				//计算角度, 不必使用 safe asin,因为前面万象锁检查已经保证safe咯
				pitch = asin(sp);
				heading = atan2(q.x*q.z - q.w*q.y, 0.5f - q.x*q.x - q.y*q.y);
				bank = atan2(q.x*q.y - q.w*q.z, 0.5f - q.x*q.x - q.z*q.z);
			}
		}
		/*
		// 物体--世界坐标系变换矩阵 到 欧拉角, 假设矩阵是正交的忽略平移部分
		void EulerAngles::fromObjectToWorldMatrix(const Matrix4x3 &m)
		{
			VCG_Number sp = -m.m32;
			// 检查万象锁
			// 检查万象锁
			if (fabs(sp) > 0.99999f)
			{
				// 向正上方或正下方看
				pitch = VCG_MATH_PI_OVER_2 * sp;
				heading = atan2(-m.m23, m.m11);
				bank = 0.0f;
			}
			else
			{
				// 计算角度
				heading = atan2(m.m31, m.m33);
				pitch = asin(sp);
				bank = atan2(m.m12, m.m22);
			}
		}

		// 世界--物体坐标系变换矩阵 到 欧拉角, 假设矩阵是正交的忽略平移部分
		void EulerAngles::fromWorldToObjectMatrix(const Matrix4x3 &m)
		{
			VCG_Number sp = -m.m32;
			// 检查万象锁
			// 检查万象锁
			if (fabs(sp) > 0.99999f)
			{
				// 向正上方或正下方看
				pitch = VCG_MATH_PI_OVER_2 * sp;
				heading = atan2(-m.m31, m.m11);
				bank = 0.0f;
			}
			else
			{
				// 计算角度
				heading = atan2(m.m13, m.m33);
				pitch = asin(sp);
				bank = atan2(m.m21, m.m22);
			}
		}
		// 通过旋转矩阵构造欧拉角
		void EulerAngles::fromRotationMatrix(const RotationMatrix &m)
		{
			// 根据 m32 计算sin(pitch)
			VCG_Number sp = -m.m32;
			// 检查万象锁
			if (fabs(sp) > 0.99999f)
			{
				// 向正上方或正下方看
				pitch = VCG_MATH_PI_OVER_2 * sp;
				heading = atan2(-m.m31,m.m11);
				bank = 0.0f;
			}
			else
			{
				// 计算角度
				heading = atan2(m.m13, m.m33);
				pitch = asin(sp);
				bank = atan2(m.m21, m.m22);
			}
		}
		//*/
		//std::string EulerAngles::toString()const
		//{
		//	return "EulerAngles(heading=" + anyTypeToString(heading) + ",pitch=" + anyTypeToString(pitch) + ",bank=" + anyTypeToString(bank) + ")";
		//}
	}	
}