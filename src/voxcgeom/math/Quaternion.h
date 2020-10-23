#pragma once
#include "Vec3D.h"
#include "Vec3D.h"
#include "EulerAngles.h"
namespace voxcgeom
{
	namespace math
	{
		//class Vec3D;
		//class EulerAngles;
		class Quaternion
		{
		public:
			// ���ĸ�ֵͨ������Ҫ�������ǣ�������������Ϊpublic��Ϊ�˽���ĳЩ�����ĸ�����
			VCG_Number x=0.0f,y=0.0f,z=0.0f,w=1.0f;
			// ���õ�λ��Ԫ��
			void identity() {x = y = z = 0.0f; w = 1.0f;}
			// ����ִ����ת����Ԫ��
			void setToRotateAboutX(VCG_Number rad_theta);
			void setToRotateAboutY(VCG_Number rad_theta);
			void setToRotateAboutZ(VCG_Number rad_theta);
			void setToRotateAboutAxis(const Vec3D &axis,VCG_Number rad_theta);
			// ��������--������ת����Ԫ��,��λ������euler����ʽ����
			void setToRotateObjectToIntertial(const EulerAngles &orientation);
			void setToRotateIntertialToObject(const EulerAngles &orientation);
			// ���
			Quaternion operator *(const Quaternion &a) const;
			// ��ֵ�˷�
			Quaternion &operator *=(const Quaternion &a);
			// ����Ԫ������
			void normalize();
			// ��ȡ��ת�Ǻ���ת��
			VCG_Number getRotationAngle() const;
			Vec3D getTotationAxis() const;
			//
			//std::string toString()const;
		};
		// ȫ�ֵ�λ������Ԫ��
		extern const Quaternion kQuaternionIdentity;
		// ��Ԫ�����
		extern VCG_Number dotProduct(const Quaternion &a, const Quaternion &b);
		// �������Բ�ֵ
		extern Quaternion slerp(const Quaternion &p, const Quaternion &q, VCG_Number t);
		// ��Ԫ������
		extern Quaternion conjugate(const Quaternion &q);
		// ��Ԫ������
		extern Quaternion pow(const Quaternion &q, VCG_Number exponent);

	}
}