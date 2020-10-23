#pragma once
#include "Vec3D.h"
//#include <string>
namespace voxcgeom
{
	namespace math
	{
		class Quaternion;
		//	class Matrix4x3;
		//	class RotationMatrix;

		class EulerAngles
		{
		public:
			EulerAngles();
			EulerAngles(VCG_Number h, VCG_Number p, VCG_Number b);
			~EulerAngles() = default;

			VCG_Number heading;
			VCG_Number pitch;
			VCG_Number bank;
			//
			void identity() { heading = pitch = bank = 0.0f; }
			// �任Ϊ "���Ƽ�" ŷ����
			void canonize();
			// ����Ԫ��ת����ŷ����
			// ����Ϊ���� -- ���Ի��߹��� -- ������Ԫ��, ��������ʾ
			void fromObjectToInertialQuaternion(const Quaternion &q);
			void fromInertialToObjectQuaternion(const Quaternion &q);
			// �Ӿ���ת����ŷ����
			// ����������Ϊ���� -- ����������� -- ����ת������
			// ƽ�Ʋ��ֱ�ʡ��, �����������������
			//	void fromObjectToWorldMatrix(const Matrix4x3 &m);
			//	void fromWorldToObjectMatrix(const Matrix4x3 &m);
			//	// ����ת����ת����ŷ����
			//	void fromRotationMatrix(const RotationMatrix &m);
			//
			//std::string toString()const;
		private:

		};
		// ȫ�ֵ� "��λ" ŷ����
		extern const EulerAngles kEulerAnglersIdentity;
	}
}
typedef voxcgeom::math::EulerAngles EulerAngles;