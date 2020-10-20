
#include <iostream>
#include "Sphere.h"

namespace voxcgeom
{
	namespace base
	{
		Vec3D Sphere::__sphAv{};
		Vec3D Sphere::__sphBv{};

		Sphere::Sphere() :radius(100.0f) {}
		void Sphere::update()
		{
		}
		void Sphere::updateFast()
		{
		}

		bool Sphere::IntersectionRLByV2(const Vec3D& lpv, const Vec3D& ltv, const Vec3D& spCV, VCG_Number spRadius, Vec3D& outV)
		{
			auto& bv = __sphBv;
			bv.copyFrom(spCV);
			bv.subtractBy(lpv);
			// 判定lpv是否包含在球体内
			spRadius *= spRadius;
			if (bv.getLengthSquared() <= spRadius)
			{
				outV.copyFrom(lpv);
				return true;
			}
			if (bv.dot(ltv) > 0.0)
			{
				outV.x = spCV.x - lpv.x;
				outV.y = spCV.y - lpv.y;
				outV.z = spCV.z - lpv.z;
				VCG_Number f = outV.dot(ltv);
				outV.x = f * ltv.x + lpv.x;
				outV.y = f * ltv.y + lpv.y;
				outV.z = f * ltv.z + lpv.z;

				bv.copyFrom(outV);
				bv.subtractBy(spCV);
				f = bv.getLengthSquared();
				if (f <= spRadius) {
					// outV 是射线上的点
					bv.copyFrom(ltv);
					// 因为这里是直角三角形，所以才这么计算(已知斜边和距离最近的两点之间的直角边)
					f = sqrt(spRadius - f);
					bv.scaleBy(f);
					outV.subtractBy(bv);
					return true;
				}
			}
			return false;
		}
		bool Sphere::IntersectionTwoRLByV2(const Vec3D& lpv, const Vec3D& ltv, const Vec3D& spCV, VCG_Number spRadius, Vec3D& outV, Vec3D& outV2)
		{
			auto& bv = __sphBv;
			bv.copyFrom(spCV);
			bv.subtractBy(lpv);
			// test sphere contains lpv yes or no
			spRadius *= spRadius;
			if (bv.getLengthSquared() <= spRadius)
			{
				outV.copyFrom(lpv);
				return true;
			}
			if (bv.dot(ltv) > 0.0f)
			{
				outV.x = spCV.x - lpv.x;
				outV.y = spCV.y - lpv.y;
				outV.z = spCV.z - lpv.z;
				VCG_Number f = outV.dot(ltv);
				outV.x = f * ltv.x + lpv.x;
				outV.y = f * ltv.y + lpv.y;
				outV.z = f * ltv.z + lpv.z;

				bv.copyFrom(outV);
				bv.subtractBy(spCV);
				f = bv.getLengthSquared();
				if (f <= spRadius) {
					// outV 是射线上的点
					bv.copyFrom(ltv);
					// 因为这里是直角三角形，所以才这么计算
					f = sqrt(spRadius - f);
					bv.scaleBy(f);
					outV2.copyFrom(outV);
					outV.subtractBy(bv);
					outV2.addBy(bv);
					return true;
				}
			}
			return false;
		}
	}
}