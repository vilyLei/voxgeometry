
#include <iostream>
#include "Cone.h"
namespace voxcgeom
{
	namespace base
	{

		Vec3D Cone::__cotV0{};
		Vec3D Cone::__cotV1{};
		Vec3D Cone::__cotV2{};
		Cone::Cone()
			: tv(1.0f,0.0f,0.0f)
			, height(100.0f)
			, radius(100.0f)
			, m_rhk(1.0f)
			, m_mcos(1.0f)
			, m_mcos2(1.0f)
		{
		}
		void Cone::update()
		{
			tv.normalize();
			m_rhk = radius / height;
			m_mcos = height / sqrt(height * height + radius * radius);
			m_mcos2 = m_mcos * m_mcos;
		}
		void Cone::updateFast()
		{
			update();
		}
		bool Cone::containsPosition(const Vec3D& pv)
		{
			auto& v3 = __cotV0;
			v3.x = pv.x - position.x;
			v3.y = pv.y - position.y;
			v3.z = pv.z - position.z;
			v3.w = v3.dot(tv);
			std::cout << "v3.w: " << v3.w << std::endl;
			if (v3.w > 0.0)
			{
				v3.normalize();
				return v3.dot(tv) >= (m_mcos - VCG_MATH_MIN_POSITIVE);
			}
			else if (v3.getLengthSquared() < VCG_MATH_MIN_POSITIVE)
			{
				return true;
			}
			return false;
		}
		bool Cone::intersectionSL(const Vec3D& slpv, const Vec3D& sltv, Vec3D& outV0, Vec3D& outV1)
		{
			//thanks for: http://lousodrome.net/blog/light/2017/01/03/intersection-of-a-ray-and-a-cone/
			auto& psltv = __cotV1;
			psltv.copyFrom(sltv);
			psltv.negate();
			auto& tsltv = sltv.dot(tv) > 0.0f ? sltv : psltv;
			auto& coDV = __cotV0;
			coDV.copyFrom(slpv);
			coDV.subtractBy(position);
			VCG_Number pb = sltv.dot(tv);
			VCG_Number pa = pb * pb - m_mcos2;
			VCG_Number pc = coDV.dot(tv);
			pb = 2.0f * (pb * pc - coDV.dot(tsltv) * m_mcos2);
			pc = pc * pc - coDV.dot(coDV) * m_mcos2;
			VCG_Number pt = pb * pb - 4.0f * pa * pc;

			if (pt >= VCG_MATH_MAX_NEGATIVE)
			{
				pa = 1.0f / (2.0f * pa);
				if (pt > VCG_MATH_MIN_POSITIVE)
				{
					pt = sqrt(pt);
					outV0.w = (-pb - pt) * pa;
					outV1.w = (-pb + pt) * pa;

					pt = -1.0f;
					outV0.copyFrom(sltv);
					outV0.scaleBy(outV0.w);
					outV0.addBy(slpv);
					outV0.w = 0.0f;

					auto& v3 = __cotV2;
					v3.x = outV0.x - position.x;
					v3.y = outV0.y - position.y;
					v3.z = outV0.z - position.z;
					v3.w = v3.dot(tv);
					if (v3.w > 0.0f)
					{
						v3.normalize();
						if (v3.dot(tv) >= (m_mcos - VCG_MATH_MIN_POSITIVE))
						{
							pt = 1.0f;
							outV0.w = 1.0f;
						}
					}
					outV1.copyFrom(sltv);
					outV1.scaleBy(outV1.w);
					outV1.addBy(slpv);
					outV1.w = 0.0f;

					v3.x = outV1.x - position.x;
					v3.y = outV1.y - position.y;
					v3.z = outV1.z - position.z;
					v3.w = v3.dot(tv);
					if (v3.w > 0.0f)
					{
						v3.normalize();
						if (v3.dot(tv) >= (m_mcos - VCG_MATH_MIN_POSITIVE))
						{
							pt = 1.0f;
							outV1.w = 1.0f;
						}
					}
				}
				else
				{
					// 穿过锥体顶端 或者 和锥体腰部刚好相交只有一个交点
					//	if (sltv.dot(tv) > m_mcos)
					//	{
					//		//("穿过锥顶.");
					//	}
					//	else
					//	{
					//		//("BBB 过锥顶,但是不和锥体相交, 或在锥面只有唯一交点, 可以认为和锥体不相交.");
					//	}
					outV0.w = -pb * pa;
					pt = -1.0f;
					outV0.copyFrom(sltv);
					outV0.scaleBy(outV0.w);
					outV0.addBy(slpv);
					outV0.w = 0.0f;
					if (containsPosition(outV0))
					{
						pt = 1.0f;
						outV0.w = 1.0f;
					}
				}
			}
			return pt >= 0.0f;
		}
		VCG_Number Cone::getRadiusByHeight(VCG_Number ph)
		{
			return m_rhk * ph;
		}
		VCG_Number Cone::getHalfAngleCos()
		{
			return m_mcos;
		}
	}
}