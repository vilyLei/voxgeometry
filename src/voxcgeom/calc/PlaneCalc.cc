
#include <iostream>
#include "PlaneCalc.h"

namespace voxcgeom
{
	namespace calc
	{
		bool PlaneCalc::IntersectBoo = false;
		int PlaneCalc::IntersectSatus = 0;
		void PlaneCalc::PlaneCalcIntersectSphere(const Vec3D& pnv, VCG_Number pdis, const Vec3D& cv, VCG_Number radius)
		{
			IntersectBoo = false;
			IntersectSatus = 0;
			pdis = pnv.dot(cv) - pdis;
			if (pdis > VCG_MATH_MIN_POSITIVE)
			{
				IntersectBoo = pdis <= radius;
				IntersectSatus = 1;
			}
			else if (pdis < VCG_MATH_MAX_NEGATIVE)
			{
				IntersectBoo = -pdis <= radius;
				IntersectSatus = -1;
			}
		}
		void PlaneCalc::CalcPVCloseV(const Vec3D& planeNV, VCG_Number planeDis, const Vec3D& posV, Vec3D& outV)
		{
			VCG_Number value = planeDis - posV.dot(planeNV);
			outV.setXYZ(value * planeNV.x, value * planeNV.y, value * planeNV.z);
			outV.addBy(posV);
		}
		void PlaneCalc::CalcPVCloseV2(const Vec3D& pnv, VCG_Number pd, const Vec3D& posV, Vec3D& outV)
		{
			VCG_Number value = pd - posV.dot(pnv);
			outV.setXYZ(value * pnv.x, value * pnv.y, value * pnv.z);
			//outV.scaleBy(value);
			outV.addBy(posV);
		}
		int PlaneCalc::IntersectionSLV2(const Vec3D& planeNV, VCG_Number planeDis, const Vec3D& sl_pos, const Vec3D& sl_tv, Vec3D& outV)
		{
			// intersection or parallel
			VCG_Number td = planeNV.dot(sl_tv);
			if (td > VCG_MATH_MIN_POSITIVE || td < VCG_MATH_MAX_NEGATIVE)
			{
				// intersection
				VCG_Number dis = planeNV.dot(sl_pos) - planeDis;
				outV.x = sl_tv.x * 100000.0f + sl_pos.x;
				outV.y = sl_tv.y * 100000.0f + sl_pos.y;
				outV.z = sl_tv.z * 100000.0f + sl_pos.z;
				//
				td = planeNV.dot(outV) - planeDis;
				td = dis / (dis - td);
				outV.subtractBy(sl_pos);
				outV.scaleBy(td);
				outV.addBy(sl_pos);
				return 1;
			}
			td = planeNV.dot(sl_pos) - planeDis;
			if (td <= VCG_MATH_MIN_POSITIVE || td >= VCG_MATH_MAX_NEGATIVE)
			{
				// plane contains line
				outV.copyFrom(sl_pos);
				return 2;
			}
			return 0;
		}
	}
}