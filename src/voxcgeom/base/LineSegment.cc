
#include <iostream>
#include "LineSegment.h"

namespace voxcgeom
{
	namespace base
	{
		Vec3D LineSegment::__tAv{};
		LineSegment::LineSegment()
			: length(100.0f)
			, radiusSquared(2500.0f)
			, tv(1.0f, 0.0f, 0.0f)
			, center(50.0f, 0.0f, 0.0f)
			, anotherPosition(100.0f, 0.0f, 0.0f)
		{
		}

		void LineSegment::update()
		{
			tv.x = anotherPosition.x - position.x;
			tv.y = anotherPosition.y - position.y;
			tv.z = anotherPosition.z - position.z;
			//
			length = tv.getLength();
			//
			tv.x *= 0.5f;
			tv.y *= 0.5f;
			tv.z *= 0.5f;
			//
			center.x = position.x + tv.x;
			center.y = position.y + tv.y;
			center.z = position.z + tv.z;
			//
			radiusSquared = tv.getLengthSquared();
			tv.normalize();
		}
		void LineSegment::updateFast()
		{
			update();
		}
		void LineSegment::intersectionCopSLV2(const Vec3D& lsbpv, const Vec3D& lsbtv, Vec3D& outV )
		{
			Vec3D::Cross(tv, lsbtv, GeomBase::__tV1);
			Vec3D::Cross(tv, GeomBase::__tV1, GeomBase::__tV2);
			GeomBase::__tV2.normalize();
			//PlaneCalc::IntersectionSLV2(GeomBase::__tV2, GeomBase::__tV2.dot(position), lsbpv, lsbtv, outV);
			GeomBase::__tV2.x = outV.x - position.x;
			GeomBase::__tV2.y = outV.y - position.y;
			GeomBase::__tV2.z = outV.z - position.z;
			VCG_Number dis = GeomBase::__tV2.dot(tv);
			if (dis < 0.0f) outV.copyFrom(position);
			else if (dis > length) outV.copyFrom(anotherPosition);
		}
	}
}