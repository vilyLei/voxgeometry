
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
		bool AABB::containsPosition(const Vec3D& v) const
		{
			if (v.x < max.x || v.x > max.x) return false;
			if (v.y < max.y || v.y > max.y) return false;
			if (v.z < max.z || v.z > max.z) return false;
			return true;
		}
		// �Ƿ����ĳһ��(ͬһ����ռ�ĵ�)
		bool AABB::containsXY(VCG_Number vx, VCG_Number vy) const
		{
			if (vx < min.x || vx > max.x) return false;
			if (vy < min.y || vy > max.y) return false;
			return true;
		}
		// �Ƿ����ĳһ��(ͬһ����ռ�ĵ�)
		bool AABB::containsXZ(VCG_Number vx, VCG_Number vz) const
		{
			if (vx < min.x || vx > max.x) return false;
			if (vz < min.z || vz > max.z) return false;
			return true;
		}
		// �Ƿ����ĳһ��(ͬһ����ռ�ĵ�)
		bool AABB::containsYZ(VCG_Number vy, VCG_Number vz) const
		{
			if (vy < min.y || vy > max.y) return false;
			if (vz < min.z || vz > max.z) return false;
			return true;
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

		void AABB::addXYZ(VCG_Number pvx, VCG_Number pvy, VCG_Number pvz)
		{
			if (min.x > pvx) min.x = pvx;
			if (min.y > pvy) min.y = pvy;
			if (min.z > pvz) min.z = pvz;
			if (max.x < pvx) max.x = pvx;
			if (max.y < pvy) max.y = pvy;
			if (max.z < pvz) max.z = pvz;
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

		bool AABB::IntersectionRL2(std::vector<Vec3D>& vecs, unsigned int rsigns[4], Vec3D& ltInvtv, Vec3D& ltv, const Vec3D& lpv, Vec3D& outV)
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

		// ������ߺ�AABB�Ƿ��ཻ,����ཻ������������� outV ��, ����������Ǿ�׼��Ч��
		// @param				ltv		���ߵ�����
		// @param				lpv		�����ϵ�һ��
		// @param				ab		updateFast() ���� AABB ʵ��
		// @param				outV	��Ž���� Vector3Dʵ��
		//
		bool AABB::IntersectionRL(const Vec3D& ltv, const Vec3D& lpv, const AABB& ab, Vec3D& outV)
		{
			// �����Χ��
			//let dis = StraightLine.CalcPVSquaredDis2(ltv, lpv, ab.center);
			outV.x = ab.center.x - lpv.x;
			outV.y = ab.center.y - lpv.y;
			outV.z = ab.center.z - lpv.z;
			//
			VCG_Number dis = outV.dot(ltv);

			outV.x -= dis * ltv.x;
			outV.y -= dis * ltv.y;
			outV.z -= dis * ltv.z;

			if (outV.getLengthSquared() > ab.radius2)
			{
				return false;
			}
			// ������㣬��һ���ཻ
			if (ab.containsPosition(lpv))
			{
				outV.copyFrom(lpv);
				return true;
			}
			// ȷ�� x ����
			if (lpv.x < ab.min.x)
			{
				// ˵�� ����� ab �� -x ��
				if (ltv.x > 0.0)
				{
					// �п��ܺ�min x���ཻ
					dis = (ab.min.x - lpv.x) / ltv.x;
					outV.copyFrom(ltv);
					outV.scaleBy(dis);
					outV.addBy(lpv);
					if (ab.containsYZ(outV.y, outV.z))
					{
						return true;
					}
				}
			}
			else if (lpv.x > ab.max.x)
			{
				// ˵�� ����� ab �� +x ��
				if (ltv.x < 0.0)
				{
					// �п��ܺ�max x���ཻ
					dis = (ab.max.x - lpv.x) / ltv.x;
					outV.copyFrom(ltv);
					outV.scaleBy(dis);
					outV.addBy(lpv);
					if (ab.containsYZ(outV.y, outV.z))
					{
						return true;
					}
				}
			}
			// ȷ�� y ����
			if (lpv.y < ab.min.y)
			{
				// ˵�� ����� ab �� -y ��
				if (ltv.y > 0.0)
				{
					// �п��ܺ�min y���ཻ
					dis = (ab.min.y - lpv.y) / ltv.y;
					outV.copyFrom(ltv);
					outV.scaleBy(dis);
					outV.addBy(lpv);
					if (ab.containsXZ(outV.x, outV.z))
					{
						return true;
					}
				}
			}
			else if (lpv.y > ab.max.y)
			{
				// ˵�� ����� ab �� +y ��
				if (ltv.y < 0.0)
				{
					// �п��ܺ�max y���ཻ
					dis = ab.max.y;
					dis = (ab.max.y - lpv.y) / ltv.y;
					outV.copyFrom(ltv);
					outV.scaleBy(dis);
					outV.addBy(lpv);
					if (ab.containsXZ(outV.x, outV.z))
					{
						return true;
					}
				}
			}
			// ȷ�� z ����
			if (lpv.z < ab.min.z)
			{
				// ˵�� ����� ab �� -z ��
				if (ltv.z > 0.0)
				{
					// �п��ܺ�min y���ཻ
					dis = (ab.min.z - lpv.z) / ltv.z;
					outV.copyFrom(ltv);
					outV.scaleBy(dis);
					outV.addBy(lpv);
					if (ab.containsXY(outV.x, outV.y))
					{
						return true;
					}
				}
			}
			else if (lpv.z > ab.max.z)
			{
				// ˵�� ����� ab �� +z ��
				if (ltv.z < 0.0)
				{
					// �п��ܺ�max z���ཻ
					dis = (ab.max.z - lpv.z) / ltv.z;
					outV.copyFrom(ltv);
					outV.scaleBy(dis);
					outV.addBy(lpv);
					if (ab.containsXY(outV.x, outV.y))
					{
						return true;
					}
				}
			}

			return false;
		}
	}
}