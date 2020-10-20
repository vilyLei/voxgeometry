
#include <iostream>
#include "StraightLine.h"
#include "RadialLine.h"
#include "Plane.h"

namespace voxcgeom
{
	namespace base
	{
		bool Plane::IntersectBoo = false;
		int Plane::IntersectSatus = 0;

		Plane::Plane()
			: distance(100.0f)
			, nv(0.0f,1.0f,0.0f)
			, intersectBoo(false)
		{
		}
		int Plane::intersectStraightLinePos(const StraightLine& straightL, Vec3D& outV)
		{
			// intersection or parallel
			VCG_Number td = nv.dot(straightL.tv);
			if (td > VCG_MATH_MIN_POSITIVE || td < VCG_MATH_MAX_NEGATIVE)
			{
				// intersection
				VCG_Number dis = nv.dot(straightL.position) - distance;

				outV.x = straightL.tv.x * 100000.0f + straightL.position.x;
				outV.y = straightL.tv.y * 100000.0f + straightL.position.y;
				outV.z = straightL.tv.z * 100000.0f + straightL.position.z;
				//
				td = nv.dot(outV) - distance;

				td = dis / (dis - td);

				outV.subtractBy(straightL.position);
				outV.scaleBy(td);
				outV.addBy(straightL.position);
				return 1;
			}
			td = nv.dot(straightL.position) - distance;
			if (td <= VCG_MATH_MIN_POSITIVE || td >= VCG_MATH_MAX_NEGATIVE)
			{
				// plane contains line
				outV.copyFrom(straightL.position);
				return 2;
			}

			return 0;
		}
		int Plane::intersectStraightLinePos2(const Vec3D& sl_pos, const Vec3D& sl_tv, Vec3D& outV)
		{
			// intersection or parallel
			VCG_Number td = nv.dot(sl_tv);

			if (td > VCG_MATH_MIN_POSITIVE || td < VCG_MATH_MAX_NEGATIVE)
			{
				// intersection
				VCG_Number dis = nv.dot(sl_pos) - distance;

				outV.x = sl_tv.x * 100000.0f + sl_pos.x;
				outV.y = sl_tv.y * 100000.0f + sl_pos.y;
				outV.z = sl_tv.z * 100000.0f + sl_pos.z;
				//
				td = nv.dot(outV) - distance;

				td = dis / (dis - td);

				outV.subtractBy(sl_pos);
				outV.scaleBy(td);
				outV.addBy(sl_pos);
				return 1;
			}
			td = nv.dot(sl_pos) - distance;
			if (td <= VCG_MATH_MIN_POSITIVE || td >= VCG_MATH_MAX_NEGATIVE)
			{
				// plane contains line
				outV.copyFrom(sl_pos);
				return 2;
			}

			return 0;
		}
		int Plane::intersectRadialLinePos(const RadialLine& radL, Vec3D& outV)
		{
			VCG_Number dis = nv.dot(radL.position) - distance;
			if (dis > VCG_MATH_MIN_POSITIVE) {
				// radL position in plane positive space
				VCG_Number td = nv.dot(radL.tv);
				if (td < 0.0) {
					// calc intersection position
					return intersectStraightLinePos2(radL.position, radL.tv, outV);
				}
			}
			else if (dis < VCG_MATH_MAX_NEGATIVE)
			{
				// radL position in plane negative space
				VCG_Number td2 = nv.dot(radL.tv);
				if (td2 > 0.0f) {
					// calc intersection position
					return intersectStraightLinePos2(radL.position, radL.tv, outV);
				}
			}
			else {
				VCG_Number td3 = nv.dot(radL.tv);
				if (td3 > VCG_MATH_MIN_POSITIVE || td3 < VCG_MATH_MAX_NEGATIVE)
				{
					outV.copyFrom(radL.position);
					return 1;
				}
				outV.copyFrom(radL.position);
				return 2;
			}
			return -1;
		}
		int Plane::intersectRadialLinePos2(const Vec3D& rl_pos, const Vec3D& rl_tv, Vec3D& outV)
		{
			VCG_Number dis = nv.dot(rl_pos) - distance;
			if (dis > VCG_MATH_MIN_POSITIVE) {
				// radL position in plane positive space
				VCG_Number td = nv.dot(rl_tv);
				if (td < 0.0)
				{
					// calc intersection position
					return intersectStraightLinePos2(rl_pos, rl_tv, outV);
				}
			}
			else if (dis < VCG_MATH_MAX_NEGATIVE)
			{
				// radL position in plane negative space
				VCG_Number td = nv.dot(rl_tv);
				if (td > 0.0f)
				{
					// calc intersection position
					return intersectStraightLinePos2(rl_pos, rl_tv, outV);
				}
			}
			else {
				VCG_Number td3 = nv.dot(rl_tv);
				if (td3 > VCG_MATH_MIN_POSITIVE || td3 < VCG_MATH_MAX_NEGATIVE)
				{
					outV.copyFrom(rl_pos);
					return 1;
				}
				outV.copyFrom(rl_pos);
				return 2;
			}

			return -1;
		}
		int Plane::containsPoint(const Vec3D& pos)
		{
			VCG_Number f = nv.dot(pos) - distance;
			if (f > VCG_MATH_MIN_POSITIVE)
			{
				return 1;
			}
			else if (f < VCG_MATH_MAX_NEGATIVE)
			{
				return -1;
			}
			return 0;
		}
		int Plane::intersectSphere(const Vec3D& cv, VCG_Number radius)
		{
			intersectBoo = false;
			VCG_Number f = nv.dot(cv) - distance;
			if (f > VCG_MATH_MIN_POSITIVE)
			{
				intersectBoo = f <= radius;
				return 1;
			}
			else if (f < VCG_MATH_MAX_NEGATIVE)
			{
				intersectBoo = -f <= radius;
				return -1;
			}
			return 0;
		}
		// 判断一个球体是否和一个平面的负空间相交
		void Plane::intersectSphNegSpace(const Vec3D& cv, VCG_Number radius)
		{			
			intersectBoo = abs(nv.dot(cv) - distance) < radius;
		}
		void Plane::update()
		{
			nv.normalize();
		}
		void Plane::updateFast()
		{
			nv.normalize();
		}

		void Plane::PlaneIntersectSphere(const Vec3D& pnv, VCG_Number pdis, const Vec3D& cv, VCG_Number radius)
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
		void Plane::CalcPVCloseV(const Plane& plane, const Vec3D& posV, Vec3D& outV)
		{
			auto& nv = plane.nv;
			VCG_Number value = plane.distance - posV.dot(nv);
			outV.setXYZ(value * nv.x, value * nv.y, value * nv.z);
			outV.addBy(posV);
		}
		void Plane::CalcPVCloseV2(const Vec3D& pnv, VCG_Number pd, const Vec3D& posV, Vec3D& outV)
		{
			VCG_Number value = pd - posV.dot(pnv);
			outV.setXYZ(value * pnv.x, value * pnv.y, value * pnv.z);

			outV.addBy(posV);
		}
		int Plane::IntersectionSLV2(const Vec3D& planeNV, VCG_Number planeDis, const Vec3D& sl_pos, const Vec3D& sl_tv, Vec3D& outV)
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