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
			// 变换为 "限制集" 欧拉角
			void canonize();
			// 从四元数转换到欧拉角
			// 假设为物体 -- 惯性或者惯性 -- 物体四元数, 如其名所示
			void fromObjectToInertialQuaternion(const Quaternion &q);
			void fromInertialToObjectQuaternion(const Quaternion &q);
			// 从矩阵转换到欧拉角
			// 输入矩阵假设为物体 -- 世界或者世界 -- 物体转换矩阵
			// 平移部分被省略, 并假设矩阵是正交的
			//	void fromObjectToWorldMatrix(const Matrix4x3 &m);
			//	void fromWorldToObjectMatrix(const Matrix4x3 &m);
			//	// 从旋转矩阵转换到欧拉角
			//	void fromRotationMatrix(const RotationMatrix &m);
			//
			//std::string toString()const;
		private:

		};
		// 全局的 "单位" 欧拉角
		extern const EulerAngles kEulerAnglersIdentity;
	}
}
typedef voxcgeom::math::EulerAngles EulerAngles;