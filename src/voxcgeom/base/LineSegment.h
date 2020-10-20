
/**
Author: Vily

*/
#pragma once
#include "GeomBase.h"

namespace voxcgeom
{
	namespace base
	{
		class LineSegment : public GeomBase
		{
		public:
			LineSegment();
			virtual ~LineSegment()			= default;


			VCG_Number length;
			VCG_Number radiusSquared;
			Vec3D tv;											// diretion normalized vec3d
			Vec3D center;										// segment line's center
			Vec3D anotherPosition;								// a 3d point's another position in straightLine
			virtual void update()		override;
			virtual void updateFast()	override;
			void intersectionCopSLV2(const Vec3D& lsbpv, const Vec3D& lsbtv, Vec3D& outV);

		protected:
				static Vec3D __tAv;
		private:

		};
	}
}
typedef voxcgeom::base::LineSegment LineSegment;