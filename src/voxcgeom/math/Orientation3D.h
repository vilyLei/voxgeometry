#pragma once
//#include <string>
namespace voxcgeom
{
	namespace math
	{
			
		class Orientation3D
		{
		public:
			//	enum class OrientationType
			//	{
			//		AXIS_ANGLE,
			//		QUATERNION,
			//		EULER_ANGLES
			//	};
			Orientation3D()								= delete;
			~Orientation3D()							= default;

			static const char							NONE;
			static const char							AXIS_ANGLE;
			static const char							QUATERNION;
			static const char							EULER_ANGLES;
		};
	}
}
typedef voxcgeom::math::Orientation3D Orientation3D;