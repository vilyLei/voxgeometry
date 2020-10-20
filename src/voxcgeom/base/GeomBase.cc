
#include <iostream>
#include "GeomBase.h"

namespace voxcgeom
{
	namespace base
	{
		Vec3D GeomBase::__tV0{};
		Vec3D GeomBase::__tV1{};
		Vec3D GeomBase::__tV2{};
		GeomBase::GeomBase()
			:uid(-1)
			, position{}
		{
		}
	}
}