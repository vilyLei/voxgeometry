
/**
Author: Vily

*/
#pragma once
#include "../math/Vec3D.h"

namespace voxcgeom
{
	namespace base
	{
		class GeomBase
		{
		public:
			GeomBase();
			GeomBase(const GeomBase& v3)						= delete;
			GeomBase(GeomBase&& rhs)							= delete;
			GeomBase& operator=(const GeomBase& rhs)			= delete;
			GeomBase& operator=(GeomBase&& rhs)					= delete;
			virtual ~GeomBase()									= default;


			int uid;
			Vec3D position;
			virtual void update() = 0;
			virtual void updateFast() = 0;

		protected:
				static Vec3D __tV0;
				static Vec3D __tV1;
				static Vec3D __tV2;
		private:

		};
	}
}
typedef voxcgeom::base::GeomBase GeomBase;