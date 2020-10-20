
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
		// ���ߺ��������ʾ���������Ƿ��ཻ
		int RadialLine::IntersectionTri(const Vec3D& rlpv, const Vec3D& rltv, const Vec3D& triva, const Vec3D& trivb, const Vec3D& trivc, Vec3D& outV)
		{
			return 0;
		}
		// ���ߺ��������ʾ���߶��Ƿ��ཻ
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
				// ����ֱ���Ѿ��ཻ
				// outV �� rlpv rltv ���㹹����һ��ƽ��
				outV.crossBy(rltv);
				outV.normalize();
				outV.w = outV.dot(rlpv);
				// ���� lspva ���ڵ�ֱ����ƽ��Ľ���
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
		// @return ���õ����������������ĵ�, 1��ʾ�ཻ,1��ʾ���ཻ
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
					// Զ����
					//outV.w = pv.w + sqrt(radius * radius - outV.getLengthSquared());
					// ȡ������
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
					// ȡԶ����
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
		// @return ���õ����������������ĵ�, 1��ʾ�ཻ,0��ʾ���ཻ
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
					// rlpv��Զ�������XP, rlpv�����ļ���CP, CP��Զ�������RP
					// ͨ�����Ҷ��ɵõ�һԪ���η��̵ò��ҽ�������̵õ� XP �ľ���
					// ���CP�����ƽ��ֵ
					outV.x = pv.getLengthSquared();
					// RP�����ƽ��ֵ ��ȥ CP�����ƽ��ֵ
					outV.z = outV.w - outV.x;
					//	// ���CP����ֵ
					//	outV.w = sqrt(outV.x);
					// ׼������ CP��XP ֮��н�a������ֵ, cos(a)ֵ
					pv.normalize();
					// cos(a) ֵ �� CP����ֵ���
					//pv.y = pv.dot(rltv) * outV.w;
					outV.y = pv.dot(rltv) * sqrt(outV.x);
					// ��ⷽ�̵ĸ�,�õ���Щ�ľ���
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
					// ��ⷽ�̵ĸ�,�õ�ԶЩ�ľ���
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