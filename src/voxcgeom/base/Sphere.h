
/**
Author: Vily

*/
#pragma once
#include "GeomBase.h"

namespace voxcgeom
{
	namespace base
	{
		class Sphere : public GeomBase
		{
		public:
			Sphere();
			virtual ~Sphere()			= default;


			VCG_Number radius;
			virtual void update()		override;
			virtual void updateFast()	override;
			/**
			 * 判定射线是否和球体相交,如果相交则将距离射线起点最近的交点记录在 outV 中
			 * @param			lpv			直线上的一点
			 * @param			ltv			直线的切向
			 * @param			spCV		球心点
			 * @param			spRadius	球体半径
			 * @param			outV		存放距离射线发射点最近的这个点
			 * @return			返回 true 表示相交, 返回false 表示不相交
			 * */
			static bool IntersectionRLByV2(const Vec3D& lpv, const Vec3D& ltv, const Vec3D& spCV, VCG_Number spRadius, Vec3D& outV);
			/**
			 * 判定射线是否和球体相交,如果相交则将距离射线起点最近的交点记录在 outV 中
			 * @param			lpv			直线上的一点
			 * @param			ltv			直线的切向
			 * @param			spCV		球心点
			 * @param			spRadius	球体半径
			 * @param			outV		存放距离射线发射点最近的这个点
			 * @param			outV		如果有两个交点存放距离射线发射点较远的这个点
			 * @return			返回 true 表示相交, 返回false 表示不相交
			 * */
			static bool IntersectionTwoRLByV2(const Vec3D& lpv, const Vec3D& ltv, const Vec3D& spCV, VCG_Number spRadius, Vec3D& outV, Vec3D& outV2);
		protected:
				static Vec3D __sphAv;
				static Vec3D __sphBv;
		private:

		};
	}
}
typedef voxcgeom::base::Sphere Sphere;