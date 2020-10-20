
/**
Author: Vily

*/
#pragma once
#include "GeomBase.h"

namespace voxcgeom
{
	namespace base
	{
		class Plane : public GeomBase
		{
		public:
			Plane();
			virtual ~Plane()			= default;


			VCG_Number distance;
			Vec3D nv;
			bool intersectBoo;

			int intersectStraightLinePos(const StraightLine& straightL, Vec3D& outV);
			int intersectStraightLinePos2(const Vec3D& sl_pos, const Vec3D& sl_tv, Vec3D& outV);
			int intersectRadialLinePos(const RadialLine& radL, Vec3D& outV);
			int intersectRadialLinePos2(const Vec3D& rl_pos, const Vec3D& rl_tv, Vec3D& outV);
			int containsPoint(const Vec3D& pos);
			int intersectSphere(const Vec3D& cv, VCG_Number radius);
			void intersectSphNegSpace(const Vec3D& cv, VCG_Number radius);

			virtual void update()		override;
			virtual void updateFast()	override;
			

			static bool IntersectBoo;
			static int IntersectSatus;
			static void PlaneIntersectSphere(const Vec3D& pnv, VCG_Number pdis, const Vec3D& cv, VCG_Number radius);
			static void CalcPVCloseV(const Plane& plane, const Vec3D& posV, Vec3D& outV);
			void CalcPVCloseV2(const Vec3D& pnv, VCG_Number pd, const Vec3D& posV, Vec3D& outV);
			static int IntersectionSLV2(const Vec3D& planeNV, VCG_Number planeDis, const Vec3D& sl_pos, const Vec3D& sl_tv, Vec3D& outV);

		protected:

		private:

		};
	}
}
typedef voxcgeom::base::Plane Plane;