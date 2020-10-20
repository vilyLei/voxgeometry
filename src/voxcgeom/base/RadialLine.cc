
#include <iostream>
#include "RadialLine.h"

namespace voxcgeom
{
	namespace base
	{
		Vec3D RadialLine::__tAv{};
		RadialLine::RadialLine() :tv(1.0f, 0.0f, 0.0f) {}

		void RadialLine::update()
		{
			tv.normalize();
		}
		void RadialLine::updateFast()
		{
			tv.normalize();
		}
		// 射线和三个点表示的三角形是否相交
		int RadialLine::IntersectionTri(const Vec3D& rlpv, const Vec3D& rltv, const Vec3D& triva, const Vec3D& trivb, const Vec3D& trivc, Vec3D& outV)
		{
			return 0;
		}
		// 射线和两个点表示的线段是否相交
		int RadialLine::IntersectionLS(const Vec3D& rlpv, const Vec3D& rltv, const Vec3D& lspva, const Vec3D& lspvb, Vec3D& outV, VCG_Number radius)
		{
			auto& pv = __tAv;
			pv.copyFrom(lspvb);
			pv.subtractBy(lspva);
			pv.normalize();

			Vec3D::Cross(rltv, pv, outV);
			outV.normalize();
			pv.w = outV.dot(rlpv) - outV.dot(lspvb);
			if (abs(pv.w) <= radius)
			{
				// 两条直线已经相交
				// outV 和 rlpv rltv 计算构成了一个平面
				outV.crossBy(rltv);
				outV.normalize();
				outV.w = outV.dot(rlpv);
				// 计算 lspva 所在的直线与平面的交点
				//let tv2:Vec3D = AbsGeomBase.__tV1;
				pv.w = (outV.w - outV.dot(lspva)) / (pv.dot(outV));
				outV.copyFrom(pv);
				outV.scaleBy(pv.w);
				outV.addBy(lspva);

				pv.copyFrom(outV);
				pv.subtractBy(lspva);
				auto& pv1 = GeomBase::__tV1;
				pv1.copyFrom(outV);
				pv1.subtractBy(lspvb);
				if (pv.dot(pv1) <= 0.0f)
				{
					return 1;
				}

			}
			return 0;
		}
		// @return 检测得到距离射线起点最近的点, 1表示相交,1表示不相交
		int RadialLine::IntersectioNearSphere2(const Vec3D& rlpv, const Vec3D& rltv, Vec3D& cv, VCG_Number radius, Vec3D& outV)
		{
			auto& pv = __tAv;
			pv.x = cv.x - rlpv.x;
			pv.y = cv.y - rlpv.y;
			pv.z = cv.z - rlpv.z;

			pv.w = pv.dot(rltv);
			radius *= radius;
			if (pv.w > VCG_MATH_MIN_POSITIVE)
			{
				outV.copyFrom(rltv);
				outV.scaleBy(pv.w);
				outV.subtractBy(pv);
				pv.x = outV.getLengthSquared();

				if (pv.x <= radius)
				{
					// 远距离
					//outV.w = pv.w + sqrt(radius * radius - outV.getLengthSquared());
					// 取近距离
					pv.w -= sqrt(radius - pv.x);
					outV.copyFrom(rltv);
					outV.scaleBy(pv.w);
					outV.addBy(rlpv);
					outV.w = 1.0f;
					return 1;
				}
			}
			else if (pv.getLengthSquared() <= radius)
			{
				outV.copyFrom(rltv);
				outV.scaleBy(pv.w);
				outV.subtractBy(pv);
				pv.x = outV.getLengthSquared();

				if (pv.x <= radius)
				{
					// 取远距离
					pv.w += sqrt(radius - pv.x);
					outV.copyFrom(rltv);
					outV.scaleBy(pv.w);
					outV.addBy(rlpv);
					outV.w = 1.0f;
					return 1;
				}
			}
			return 0;
		}
		// @return 检测得到距离射线起点最近的点, 1表示相交,0表示不相交
		int RadialLine::IntersectioNearSphere(const Vec3D& rlpv, const Vec3D& rltv, Vec3D& cv, VCG_Number radius, Vec3D& outV)
		{
			auto& pv = __tAv;
			pv.x = cv.x - rlpv.x;
			pv.y = cv.y - rlpv.y;
			pv.z = cv.z - rlpv.z;
			pv.w = pv.dot(rltv);
			if (pv.w > VCG_MATH_MIN_POSITIVE)
			{
				outV.x = pv.x - pv.w * rltv.x;
				outV.y = pv.y - pv.w * rltv.y;
				outV.z = pv.z - pv.w * rltv.z;
				outV.x = outV.getLengthSquared();
				outV.w = radius * radius;
				if (outV.x <= outV.w)
				{
					// rlpv到远交点记作XP, rlpv到球心记作CP, CP到远交点记作RP
					// 通过余弦定律得到一元二次方程得并且解这个方程得到 XP 的距离
					// 获得CP距离的平方值
					outV.x = pv.getLengthSquared();
					// RP距离的平方值 减去 CP距离的平方值
					outV.z = outV.w - outV.x;
					//	// 获得CP距离值
					//	outV.w = sqrt(outV.x);
					// 准备计算 CP和XP 之间夹角a的余弦值, cos(a)值
					pv.normalize();
					// cos(a) 值 和 CP距离值相乘
					//pv.y = pv.dot(rltv) * outV.w;
					outV.y = pv.dot(rltv) * sqrt(outV.x);
					// 求解方程的根,得到近些的距离
					pv.w = (-outV.y + sqrt(outV.y * outV.y + 4.0f * outV.z)) * 0.5f;
					outV.copyFrom(rltv);
					outV.scaleBy(pv.w);
					outV.addBy(rlpv);
					outV.w = 1.0f;
					return 1;
				}
			}
			else
			{
				outV.x = pv.getLengthSquared();
				outV.w = radius * radius;
				if (outV.x <= outV.w)
				{
					outV.z = outV.w - outV.x;
					pv.normalize();
					outV.y = pv.dot(rltv) * sqrt(outV.x);
					// 求解方程的根,得到远些的距离
					pv.w = (-outV.y + sqrt(outV.y * outV.y + 4.0f * outV.z)) * 0.5f;
					outV.copyFrom(rltv);
					outV.scaleBy(pv.w);
					outV.addBy(rlpv);
					outV.w = 1.0f;
					return 1;
				}
			}
			return 0;
		}
		bool RadialLine::IntersectSphere(const Vec3D& rlpv, const Vec3D& rltv, const Vec3D& cv, VCG_Number radius)
		{
			auto& pv = __tAv;
			pv.x = cv.x - rlpv.x;
			pv.y = cv.y - rlpv.y;
			pv.z = cv.z - rlpv.z;
			pv.w = pv.dot(rltv);
			if (pv.w < VCG_MATH_MIN_POSITIVE)
			{
				return pv.getLengthSquared() <= (radius * radius);
			}
			pv.x -= pv.w * rltv.x;
			pv.y -= pv.w * rltv.y;
			pv.z -= pv.w * rltv.z;
			return pv.getLengthSquared() <= (radius * radius);
		}
	}
}