
#include <iostream>
#include "StraightLine.h"
#include "../calc/PlaneCalc.h"
namespace voxcgeom
{
	namespace base
	{
		Vec3D StraightLine::__tAv{};
		StraightLine::StraightLine() :tv(1.0f, 0.0f, 0.0f) {}
		void StraightLine::update()
		{
			tv.normalize();
		}
		void StraightLine::updateFast()
		{
			tv.normalize();
		}
		/*
		 *计算空间中一点到空间某直线的距离的平方
		 *@param			ltv				空间直线的切向
		 *@param			lpv				空间直线上的某一点
		 *@param			spCV			空间中的一点
		 */
		VCG_Number StraightLine::CalcPVSquaredSquaredDis2(const Vec3D& ltv, const Vec3D& lpv, const Vec3D& spCV)
		{
			auto& pv = __tAv;
			pv.x = spCV.x - lpv.x;
			pv.y = spCV.y - lpv.y;
			pv.z = spCV.z - lpv.z;
			pv.w = pv.dot(ltv);
			pv.x -= pv.w * ltv.x;
			pv.y -= pv.w * ltv.y;
			pv.z -= pv.w * ltv.z;
			return pv.getLengthSquared();
		}
		//计算空间中一点到空间某直线的距离
		VCG_Number StraightLine::CalcPVDis(const Vec3D& ltv, const Vec3D& lpv, const Vec3D& spCV)
		{
			auto& pv = __tAv;
			pv.x = spCV.x - lpv.x;
			pv.y = spCV.y - lpv.y;
			pv.z = spCV.z - lpv.z;
			//
			VCG_Number da = pv.dot(ltv);
			pv.x = da * ltv.x + lpv.x;
			pv.y = da * ltv.y + lpv.y;
			pv.z = da * ltv.z + lpv.z;
			//
			pv.x = spCV.x - pv.x;
			pv.y = spCV.y - pv.y;
			pv.z = spCV.z - pv.z;
			return pv.getLength();
		}

		/**
		 * 计算空间中一点到空间直线最近的点
		 * @param			lpv		直线上的某一点
		 * @param			ltv		直线的切向
		 * @param			spCV			空间中的一点
		 * */
		void StraightLine::CalcPVCloseV2(const Vec3D& lpv, const Vec3D& ltv, const Vec3D& spCV, Vec3D& outV)
		{
			outV.x = spCV.x - lpv.x;
			outV.y = spCV.y - lpv.y;
			outV.z = spCV.z - lpv.z;
			VCG_Number da = outV.dot(ltv);
			outV.x = da * ltv.x + lpv.x;
			outV.y = da * ltv.y + lpv.y;
			outV.z = da * ltv.z + lpv.z;
		}
		/**
		 * calculate intersection point of two straight line in the same plane
		 * @param			latv	tv of line a
		 * @param			lapv	pv of line a
		 * @param			lbtv	tv of line b
		 * @param			lbpv	Sphere.__tsAv of line b
		 * @param			outV	result: intersection point
		 */
		void StraightLine::IntersectionCopSLV2(const Vec3D& lapv, const Vec3D& latv, const Vec3D& lbpv, const Vec3D& lbtv, Vec3D& outV)
		{
			Vec3D::Cross(latv, lbtv, GeomBase::__tV1);
			Vec3D::Cross(latv, GeomBase::__tV1, GeomBase::__tV2);
			GeomBase::__tV2.normalize();
			PlaneCalc::IntersectionSLV2(GeomBase::__tV2, GeomBase::__tV2.dot(lapv), lbpv, lbtv, outV);
		}
		// 计算两条异面直线距离最近的点,而且这个点落在空间直线b线上
		void StraightLine::CalcTwoSLCloseV2(const Vec3D& lapv, const Vec3D& latv, const Vec3D& lbpv, const Vec3D& lbtv, Vec3D& outV)
		{
			Vec3D::Cross(latv, lbtv, GeomBase::__tV1);
			Vec3D::Cross(latv, GeomBase::__tV1, GeomBase::__tV2);
			GeomBase::__tV2.normalize();
			PlaneCalc::IntersectionSLV2(GeomBase::__tV2, GeomBase::__tV2.dot(lapv), lbpv, lbtv, outV);
			// 计算点在空间直线a上的投影
			outV.subtractBy(lapv);
			outV.w = outV.dot(latv);
			outV.x = outV.w * latv.x + lapv.x;
			outV.y = outV.w * latv.y + lapv.y;
			outV.z = outV.w * latv.z + lapv.z;
			outV.w = 1.0;
		}
		// 计算两条异面直线距离最近的点,而且这个点落在这两个空间直线上
		void StraightLine::CalcTwoSLDualCloseV2(const Vec3D& lapv, const Vec3D& latv, const Vec3D& lbpv, const Vec3D& lbtv, Vec3D& outVa, Vec3D& outVb)
		{
			Vec3D::Cross(latv, lbtv, GeomBase::__tV1);
			Vec3D::Cross(latv, GeomBase::__tV1, GeomBase::__tV2);
			GeomBase::__tV2.normalize();
			PlaneCalc::IntersectionSLV2(GeomBase::__tV2, GeomBase::__tV2.dot(lapv), lbpv, lbtv, outVa);
			outVb.copyFrom(lbpv);
			// 计算点在空间直线a上的投影
			outVa.subtractBy(lapv);
			outVa.w = outVa.dot(latv);
			outVa.x = outVa.w * latv.x + lapv.x;
			outVa.y = outVa.w * latv.y + lapv.y;
			outVa.z = outVa.w * latv.z + lapv.z;
			outVa.w = 1.0;
			// 计算点在空间直线b上的投影
			//GeomBase::__tV1.normalize();
			outVb.subtractBy(outVa);
			outVb.w = outVb.dot(GeomBase::__tV1);
			outVb.x = outVb.w * GeomBase::__tV1.x + outVa.x;
			outVb.y = outVb.w * GeomBase::__tV1.y + outVa.y;
			outVb.z = outVb.w * GeomBase::__tV1.z + outVa.z;
			outVb.w = 1.0;
		}
	}
}