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
			// 这四个值通常不需要处理他们，但是这里设置为public是为了降低某些操作的复杂性
			VCG_Number x=0.0f,y=0.0f,z=0.0f,w=1.0f;
			// 设置单位四元数
			void identity() {x = y = z = 0.0f; w = 1.0f;}
			// 构造执行旋转的四元数
			void setToRotateAboutX(VCG_Number rad_theta);
			void setToRotateAboutY(VCG_Number rad_theta);
			void setToRotateAboutZ(VCG_Number rad_theta);
			void setToRotateAboutAxis(const Vec3D &axis,VCG_Number rad_theta);
			// 构造物体--惯性旋转的四元数,方位参数用euler的形式给出
			void setToRotateObjectToIntertial(const EulerAngles &orientation);
			void setToRotateIntertialToObject(const EulerAngles &orientation);
			// 叉乘
			Quaternion operator *(const Quaternion &a) const;
			// 赋值乘法
			Quaternion &operator *=(const Quaternion &a);
			// 将四元数正则化
			void normalize();
			// 提取旋转角和旋转轴
			VCG_Number getRotationAngle() const;
			Vec3D getTotationAxis() const;
			//
			//std::string toString()const;
		};
		// 全局单位化的四元数
		extern const Quaternion kQuaternionIdentity;
		// 四元数点乘
		extern VCG_Number dotProduct(const Quaternion &a, const Quaternion &b);
		// 球面线性插值
		extern Quaternion slerp(const Quaternion &p, const Quaternion &q, VCG_Number t);
		// 四元数共轭
		extern Quaternion conjugate(const Quaternion &q);
		// 四元数的幂
		extern Quaternion pow(const Quaternion &q, VCG_Number exponent);

	}
}