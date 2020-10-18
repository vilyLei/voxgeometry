
#include <iostream>
#include "AABB.h"

namespace voxcgeom
{
	namespace base
	{
		AABB::AABB(const Vec3D& minV, const Vec3D& maxV)
			:min(minV)
			, max(maxV)
			, m_width(0.0f)
			, m_height(0.0f)
			, m_long(0.0f)
		{
		}
		AABB::AABB(VCG_Number minX, VCG_Number minY, VCG_Number minZ, VCG_Number maxX, VCG_Number maxY, VCG_Number maxZ)
			:min(minX, minY, minZ)
			, max(maxX, maxY, maxZ)
			, m_width(0.0f)
			, m_height(0.0f)
			, m_long(0.0f)
		{
		}
		bool AABB::intersect(const AABB& ab)
		{
			auto& pmin = ab.min;
			auto& pmax = ab.max;

			if (pmin.x < min.x) return false;
			if (pmin.y < min.y) return false;
			if (pmin.z < min.z) return false;

			if (pmax.x > max.x) return false;
			if (pmax.y > max.y) return false;
			if (pmax.z > max.z) return false;

			return true;
		}
		void AABB::unionThis(const AABB& ab)
		{
			addPosition(ab.min);
			addPosition(ab.max);
		}
		void AABB::addPosition(const Vec3D& pv)
		{
			if (min.x > pv.x) min.x = pv.x;
			if (min.y > pv.y) min.y = pv.y;
			if (min.z > pv.z) min.z = pv.z;
			if (max.x < pv.x) max.x = pv.x;
			if (max.y < pv.y) max.y = pv.y;
			if (max.z < pv.z) max.z = pv.z;
		}
		void AABB::update()
		{
			// x
			m_width = max.x;
			if (min.x > max.x)
			{
				max.x = min.x;
				min.x = m_width;
			}
			m_width = max.x - min.x;
			// y
			m_height = max.y;
			if (min.y > max.y)
			{
				max.y = min.y;
				min.y = m_height;
			}
			m_height = max.y - min.y;
			// z
			m_long = max.z;
			if (min.z > max.z)
			{
				max.z = min.z;
				min.z = m_long;
			}
			m_long = max.z - min.z;

			center.x = 0.5f * m_width;
			center.y = 0.5f * m_height;
			center.z = 0.5f * m_long;

			radius2 = center.getLengthSquared();
			radius = sqrt(radius2);

			center.x += min.x;
			center.y += min.y;
			center.z += min.z;
		}
		void AABB::coutThis()
		{
			std::cout << "AABB(min(x="<<min.x<<",y="<< min.y<<",z="<< min.z<<",w="<< min.w<<"), max(x = "<<max.x<<", y = "<< max.y<<", z = "<< max.z<<", w = "<< max.w<<"), " << std::endl;
		}

		bool AABB::IntersectionRL(std::vector<Vec3D>& vecs, unsigned int rsigns[4], Vec3D& ltInvtv, Vec3D& ltv, const Vec3D& lpv, Vec3D& outV)
		{
			ltInvtv.w = (vecs[rsigns[0]].x - lpv.x) * ltInvtv.x;
			ltv.w = (vecs[1 - rsigns[0]].x - lpv.x) * ltInvtv.x;
			outV.x = (vecs[rsigns[1]].y - lpv.y) * ltInvtv.y;
			outV.y = (vecs[1 - rsigns[1]].y - lpv.y) * ltInvtv.y;

			if ((ltInvtv.w > outV.y) || (outV.x > ltv.w))
				return false;
			if (outV.x > ltInvtv.w)
				ltInvtv.w = outV.x;
			if (outV.y < ltv.w)
				ltv.w = outV.y;

			outV.x = (vecs[rsigns[2]].z - lpv.z) * ltInvtv.z;
			outV.y = (vecs[1 - rsigns[2]].z - lpv.z) * ltInvtv.z;
			if (ltInvtv.w > outV.y || outV.x > ltv.w)
				return false;
			if (outV.x > ltInvtv.w)
				ltInvtv.w = outV.x;
			if (outV.y < ltv.w)
				ltv.w = outV.y;

			outV.copyFrom(ltv);
			outV.scaleBy(ltInvtv.w);
			outV.addBy(lpv);
			ltv.w = 1.0f;

			return true;
		}

	}
}