
/**
Author: Vily

*/
#pragma once
#include "GeomBase.h"

namespace voxcgeom
{
	namespace base
	{
		class StraightLine : public GeomBase
		{
		public:
			StraightLine();
			virtual ~StraightLine()			= default;

			Vec3D tv;						// diretion normalized vec3d
			virtual void update()			override;
			virtual void updateFast()		override;

			static VCG_Number CalcPVSquaredSquaredDis2(const Vec3D& ltv, const Vec3D& lpv, const Vec3D& spCV);
			static VCG_Number CalcPVDis(const Vec3D& ltv, const Vec3D& lpv, const Vec3D& spCV);
			static void CalcPVCloseV2(const Vec3D& lpv, const Vec3D& ltv, const Vec3D& spCV, Vec3D& outV);
			static void IntersectionCopSLV2(const Vec3D& lapv, const Vec3D& latv, const Vec3D& lbpv, const Vec3D& lbtv, Vec3D& outV);
			static void CalcTwoSLCloseV2(const Vec3D& lapv, const Vec3D& latv, const Vec3D& lbpv, const Vec3D& lbtv, Vec3D& outV);
			static void CalcTwoSLDualCloseV2(const Vec3D& lapv, const Vec3D& latv, const Vec3D& lbpv, const Vec3D& lbtv, Vec3D& outVa, Vec3D& outVb);

		protected:
			static Vec3D __tAv;
		private:

		};
	}
}
typedef voxcgeom::base::StraightLine StraightLine;