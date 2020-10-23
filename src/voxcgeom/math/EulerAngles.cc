
#include <cmath>
#include "EulerAngles.h"
#include "Quaternion.h"
namespace voxcgeom
{
	namespace math
	{
		/**
			���ǶȵĻ���ֵ������ -pi �� pi ֮��
			@param			rad_theta		����ֵ
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
		��euler angleת�������Ƽ���
		@returen		���Ƽ��е�euler angleֵ
		*/
		void EulerAngles::canonize()
		{
			pitch = wrapPi(pitch);
			// �� pitch ת���� -pi/2 �� pi/2��
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
			// ��� ������, �������һ�������
			if (abs(pitch) > VCG_MATH_PI_OVER_2 - 1e-4)
			{
				// ����������, �������ƴ�ֱ�����ת����heading
				heading += bank;
				bank = 0.0f;
			}
			else
			{
				// ��������,��bankת�������Ƽ���
				bank = wrapPi(bank);
			}
			// ��headingת�������Ƽ���
			heading = wrapPi(heading);
		}
		/////////////////////////////////////////////////////
		//
		//������--������Ԫ����ŷ����
		//
		/////////////////////////////////////////////////////
		void EulerAngles::fromObjectToInertialQuaternion(const Quaternion &q)
		{
			// ���� sin(pitch)
			VCG_Number sp = -2.0f * (q.y * q.z - q.w*q.x);
			// ������������������һ�����
			if (fabs(sp) > 0.9999f)
			{
				// �����Ϸ������·���
				pitch = VCG_MATH_PI_OVER_2 * sp;
				// bank��0,����heading
				heading = atan2(-q.x*q.z + q.w*q.y,0.5f-q.y*q.y-q.z*q.z);
				bank = 0.0f;
			}
			else
			{
				//����Ƕ�, ����ʹ�� safe asin,��Ϊǰ������������Ѿ���֤safe��
				pitch = asin(sp);
				heading = atan2(q.x*q.z + q.w*q.y, 0.5f - q.x*q.x - q.y*q.y);
				bank = atan2(q.x*q.y + q.w*q.z, 0.5f - q.x*q.x - q.z*q.z);
			}
		}
		// �ӹ��� -- ������Ԫ����ŷ����
		void EulerAngles::fromInertialToObjectQuaternion(const Quaternion &q)
		{
			// ���� sin(pitch)
			VCG_Number sp = -2.0f * (q.y * q.z + q.w*q.x);
			// ������������������һ�����
			if (fabs(sp) > 0.9999f)
			{
				// �����Ϸ������·���
				pitch = VCG_MATH_PI_OVER_2 * sp;
				// bank��0,����heading
				heading = atan2(-q.x*q.z - q.w*q.y, 0.5f - q.y*q.y - q.z*q.z);
				bank = 0.0f;
			}
			else
			{
				//����Ƕ�, ����ʹ�� safe asin,��Ϊǰ������������Ѿ���֤safe��
				pitch = asin(sp);
				heading = atan2(q.x*q.z - q.w*q.y, 0.5f - q.x*q.x - q.y*q.y);
				bank = atan2(q.x*q.y - q.w*q.z, 0.5f - q.x*q.x - q.z*q.z);
			}
		}
		/*
		// ����--��������ϵ�任���� �� ŷ����, ��������������ĺ���ƽ�Ʋ���
		void EulerAngles::fromObjectToWorldMatrix(const Matrix4x3 &m)
		{
			VCG_Number sp = -m.m32;
			// ���������
			// ���������
			if (fabs(sp) > 0.99999f)
			{
				// �����Ϸ������·���
				pitch = VCG_MATH_PI_OVER_2 * sp;
				heading = atan2(-m.m23, m.m11);
				bank = 0.0f;
			}
			else
			{
				// ����Ƕ�
				heading = atan2(m.m31, m.m33);
				pitch = asin(sp);
				bank = atan2(m.m12, m.m22);
			}
		}

		// ����--��������ϵ�任���� �� ŷ����, ��������������ĺ���ƽ�Ʋ���
		void EulerAngles::fromWorldToObjectMatrix(const Matrix4x3 &m)
		{
			VCG_Number sp = -m.m32;
			// ���������
			// ���������
			if (fabs(sp) > 0.99999f)
			{
				// �����Ϸ������·���
				pitch = VCG_MATH_PI_OVER_2 * sp;
				heading = atan2(-m.m31, m.m11);
				bank = 0.0f;
			}
			else
			{
				// ����Ƕ�
				heading = atan2(m.m13, m.m33);
				pitch = asin(sp);
				bank = atan2(m.m21, m.m22);
			}
		}
		// ͨ����ת������ŷ����
		void EulerAngles::fromRotationMatrix(const RotationMatrix &m)
		{
			// ���� m32 ����sin(pitch)
			VCG_Number sp = -m.m32;
			// ���������
			if (fabs(sp) > 0.99999f)
			{
				// �����Ϸ������·���
				pitch = VCG_MATH_PI_OVER_2 * sp;
				heading = atan2(-m.m31,m.m11);
				bank = 0.0f;
			}
			else
			{
				// ����Ƕ�
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