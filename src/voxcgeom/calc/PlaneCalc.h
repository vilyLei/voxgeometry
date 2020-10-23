
/**
Author: Vily

*/
#pragma once
#include "../math/Vec3D.h"

namespace voxcgeom
{
	namespace calc
	{
		class PlaneCalc
		{
		public:
			PlaneCalc()						= delete;
			~PlaneCalc()					= delete;

			static bool IntersectBoo;
			static int IntersectSatus;

			static void PlaneCalcIntersectSphere(const Vec3D& pnv, VCG_Number pdis, const Vec3D& cv, VCG_Number radius);
			static void CalcPVCloseV(const Vec3D& planeNV, VCG_Number planeDis, const Vec3D& posV, Vec3D& outV);
			static void CalcPVCloseV2(const Vec3D& pnv, VCG_Number pd, const Vec3D& posV, Vec3D& outV);
			static int IntersectionSLV2(const Vec3D& planeNV, VCG_Number planeDis, const Vec3D& sl_pos, const Vec3D& sl_tv, Vec3D& outV);
		protected:

		private:

		};
	}
}
typedef voxcgeom::calc::PlaneCalc PlaneCalc;